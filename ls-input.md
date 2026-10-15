# Vérification d'un argument par `ls`

GNU ls 8.32 (le `ls` de cette machine) ne contrôle pas le texte du chemin.
Un argument qui n'est pas une option est passé tel quel à `lstat` ou `stat`.
Il n'y a pas d'appel à `access`. Les droits refusés apparaissent quand
`lstat`, `stat` ou `opendir` échoue.

`stat` suit le lien et décrit la cible. `lstat` décrit le lien lui-même.

## 1. Choisir `stat` ou `lstat`

`-L` n'est pas à gérer.

```text
si le nom a été lu par readdir :
    lstat
sinon si -l :
    lstat
sinon :
    stat
    si succès et répertoire : garder ce résultat
    sinon si succès, ou échec ENOENT : lstat
    sinon : erreur, pas de second appel
```

### Exemple

`link_dir` pointe vers un répertoire, `link_file` vers un fichier,
`link_broken` vers un nom absent.

Sans `-l` :

```text
link_broken
link_file

link_dir:
file
```

Avec `-l`, un seul `lstat` par argument. Les trois lignes commencent par `l`
et `link_dir` n'est pas ouvert :

```text
lrwxrwxrwx ... link_broken -> missing
lrwxrwxrwx ... link_dir -> dir
lrwxrwxrwx ... link_file -> plain
```

## 2. Tester le retour

```c
if (lstat(path, &st) == -1) {   /* ou stat, selon le cas ci-dessus */
    /* cannot access '%s' : %s, strerror(errno) */
    /* argument abandonné, les autres continuent, code de sortie 2 */
}
```

## 3. Les champs de `struct stat`

`<sys/stat.h>` remplit cette structure. L'ordre des champs change selon
l'architecture. On lit les noms, pas la position.

| Champ | Contenu |
|---|---|
| `st_dev` | Périphérique qui contient le fichier. |
| `st_ino` | Numéro d'inode. |
| `st_mode` | Type et droits. Le type se lit avec `S_ISDIR` et les autres macros. |
| `st_nlink` | Nombre de liens physiques. |
| `st_uid` | UID du propriétaire. `getpwuid` donne le nom. |
| `st_gid` | GID du groupe. `getgrgid` donne le nom. |
| `st_rdev` | Pour un périphérique (`b` ou `c`), l'identifiant de ce périphérique. `major` et `minor` le découpent. |
| `st_size` | Taille en octets. Pour un lien, c'est la longueur du chemin cible, pas la taille du fichier pointé. |
| `st_blksize` | Taille de bloc préférée pour les lectures et écritures. |
| `st_blocks` | Place occupée, en blocs de 512 octets. La ligne `total` de `ls -l` en est dérivée. |
| `st_atime` | Dernier accès, en secondes. |
| `st_mtime` | Dernière modification du contenu, en secondes. C'est la date de `ls -l` et la clé de `-t`. |
| `st_ctime` | Dernier changement d'inode (droits, propriétaire, liens). Ce n'est pas la date de création. |

`st_atime`, `st_mtime` et `st_ctime` sont les secondes de `st_atim`, `st_mtim` et `st_ctim`, qui sont des `struct timespec` (`tv_sec`, `tv_nsec`).

Avec `-l`, la ligne vient de `st_mode`, `st_nlink`, `st_uid`, `st_gid`, `st_size` (ou `st_rdev` pour un périphérique), `st_mtime`, puis le nom.

## 4. Classer avec `st_mode`

Les macros sont dans `<sys/stat.h>`. Chacune prend `st.st_mode`.

| Macro | Type |
|---|---|
| `S_ISREG` | fichier ordinaire |
| `S_ISDIR` | répertoire |
| `S_ISLNK` | lien symbolique |
| `S_ISCHR` | périphérique caractère |
| `S_ISBLK` | périphérique bloc |
| `S_ISFIFO` | tube nommé |
| `S_ISSOCK` | socket |

```c
if (S_ISDIR(st.st_mode))
    /* répertoire */
```

`S_ISLNK` n'est vrai qu'après un `lstat`. Un `stat` qui a suivi le lien décrit la cible, donc `S_ISDIR` peut être vrai et `S_ISLNK` faux.

Pour le tri du listing :

- `S_ISLNK` : affiché comme un fichier. Avec `-l`, `readlink` donne la cible.
- `S_ISDIR` : retiré de la liste des fichiers et mis en file. Son contenu est listé ensuite.
- sinon : affiché tout de suite (fichier, fifo, socket, périphérique).

## 5. Ouvrir un répertoire

`opendir` n'est appelé qu'après un `S_ISDIR` confirmé.

```c
dirp = opendir(path);
if (dirp == NULL) {
    /* cannot open directory '%s' : %s, strerror(errno) */
    /* ce répertoire n'est pas lu */
}

errno = 0;
de = readdir(dirp);
if (de == NULL && errno != 0)
    /* reading directory '%s' */
if (de == NULL && errno == 0)
    /* fin normale du répertoire */

if (closedir(dirp) != 0)
    /* closing directory '%s' */
    /* ce qui a déjà été lu est quand même affiché */
```

`.` et `..` ne sont pas descendus avec `-R`. Avec `-a`, ils sont affichés.

## 6. Code de sortie

Le code ne redescend pas. Un `2` déjà posé reste, même si la suite réussit.

`0` : tout a réussi.

`1` : une erreur sur un nom lu dans un répertoire. Ouvrir, lire ou fermer un
sous-dossier pendant le parcours, ou un `lstat` qui échoue sur une entrée.
Le reste du listing est affiché. `ls -R tree` dont un sous-dossier est
interdit sort avec `1`.

`2` : une erreur sur un argument de la ligne de commande. `cannot access`
quand `stat` ou `lstat` échoue, `cannot open directory` quand l'argument
est un dossier qu'on ne peut pas ouvrir. Une option inconnue et une erreur
d'écriture donnent aussi `2`. `ls ok missing` affiche `ok` et sort avec `2`.

Le message `cannot open directory` est donc un `2` si le dossier est un
argument, et un `1` s'il a été trouvé en lisant un autre dossier.
