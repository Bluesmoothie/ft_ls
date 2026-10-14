# Vérification d'un argument par `ls`

GNU ls 8.32 (le `ls` de cette machine) ne contrôle pas le texte du chemin.
Un argument qui n'est pas une option est passé tel quel à `lstat` ou `stat`.
Il n'y a pas d'appel à `access`. Les droits refusés apparaissent quand
`lstat`, `stat` ou `opendir` échoue.

`stat` suit le lien et décrit la cible. `lstat` décrit le lien lui-même.

## 1. Choisir `stat` ou `lstat`

Le choix est fixé par les options, avant de regarder le fichier.

| Options | Appel sur un argument |
|---|---|
| `-l` | `lstat` seulement. Le lien n'est pas suivi. |
| `-L` | `stat` seulement. Le lien est toujours suivi. |
| ni `-l` ni `-L` | `stat` d'abord, puis parfois `lstat` |

Sans `-l` ni `-L`, `ls` veut ouvrir un argument seulement si c'est un
répertoire. Un lien vers un répertoire compte comme un répertoire. Un lien
vers un fichier est affiché comme un nom.

Après le `stat` :

| Retour de `stat` | Suite |
|---|---|
| `0` et `S_ISDIR(st_mode)` | Garder ce résultat. Le répertoire sera listé. |
| `0` et la cible n'est pas un répertoire | Jeter le résultat et appeler `lstat`. |
| `-1` et `errno == ENOENT` | La cible n'existe pas. Appeler `lstat` : le lien, lui, peut exister. |
| `-1` et un autre `errno` (`EACCES`, …) | Échec. Pas de second essai. |

Ce double appel ne concerne que les arguments de la ligne de commande.
Un nom trouvé dans un répertoire est vu avec `lstat`, ou avec le type déjà
fourni par `readdir`. Il n'est pas suivi.

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

Avec `-lL`, seul `stat` est appelé. `link_broken` donne
`cannot access`, et `link_file` est affiché avec les droits de sa cible.

## 2. Tester le retour

```c
if (lstat(path, &st) == -1) {   /* ou stat, selon le cas ci-dessus */
    /* cannot access '%s' : %s, strerror(errno) */
    /* argument abandonné, les autres continuent, code de sortie 2 */
}
```

## 3. Classer avec `st_mode`

Une fois l'appel réussi, le type vient des macros POSIX :

- `S_ISLNK` : lien. Affiché comme un fichier. Avec `-l`, `readlink` donne la cible.
- `S_ISDIR` : répertoire. Retiré de la liste des fichiers et mis en file.
  Son contenu est listé ensuite.
- sinon : affiché tout de suite (fichier, fifo, socket, périphérique).

## 4. Ouvrir un répertoire

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
