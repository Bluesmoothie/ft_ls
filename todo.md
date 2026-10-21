# À faire

Le nom lu par `readdir` est encore le pointeur `d_name`. Ce tampon est réutilisé : `name` en est une copie. `path` se construit à partir du dossier et de ce nom. Si le dossier est exactement `.`, `path` est `name`. Si `name` commence par `/`, `path` est `name`. Sinon les deux sont joints par un seul `/`, et ce `/` n'est pas ajouté quand le dossier se termine déjà par `/`.

Pour un périphérique bloc (`b`) ou caractère (`c`), `ls -l` affiche `major, minor` à la place de la taille. `major(st_rdev)` va dans `size`, `minor(st_rdev)` dans `size2`. L'affichage imprime les deux sous la forme `1, 3` : une virgule puis une espace. Cette colonne est commune au bloc. Le majeur et le mineur sont alignés à droite sur leur plus grande largeur, et l'espace restant est ajouté devant le majeur pour que les virgules tombent sur la même colonne. `/dev/null` affiche `1, 3`. Un lien garde `st_size`, la longueur du chemin cible, et la cible suit le nom : ` -> cible`.

Si `getpwuid` ou `getgrgid` ne renvoie pas de nom, ou si ce nom est vide, la colonne propriétaire ou groupe affiche l'identifiant numérique (`st_uid`, `st_gid`). Seul le champ manquant devient numérique. Un nom est aligné à gauche, un identifiant à droite, dans la largeur de la chaîne réellement affichée, chiffres compris. Ces fonctions renvoient une zone statique : le nom affiché en est une copie.

Si `lstat` échoue sur un nom déjà lu dans un répertoire, le programme écrit `cannot access`, garde le code `1`, et imprime quand même la ligne `-l`. La lettre de type vient de `d_type` : `-` pour `DT_REG`, `d` pour `DT_DIR`, `l` pour `DT_LNK`, `b` pour `DT_BLK`, `c` pour `DT_CHR`, `p` pour `DT_FIFO`, `s` pour `DT_SOCK`. Si `d_type` vaut `DT_UNKNOWN`, cette lettre est `?`. Les neuf droits sont `?????????`. Le nombre de liens, le propriétaire, le groupe, la taille et la date sont chacun un seul `?`. Rien n'est pris dans `st_nlink`, `st_uid`, `st_gid`, `st_size`, `st_rdev` ni `st_mtime`, et un lien n'a pas de ` -> cible`. Le `?` du propriétaire et celui du groupe sont alignés à gauche. Ceux des liens, de la taille et de la date sont alignés à droite dans la largeur de leur colonne. La date garde sa largeur habituelle, celle de `Oct  5 09:05`, donc des espaces précèdent son `?`. Cette entrée n'ajoute rien à `total`. Sans `-l`, il n'y a pas de `?` : seul le nom est affiché.

Sans `-l`, `-t` trie par date, mais les largeurs du propriétaire, du groupe et du mois ne se mesurent que lorsque `-l` a rempli ces chaînes. Les mesurer alors qu'elles sont vides fait une erreur de segmentation, comme avec `ft_ls -t fichier dossier`.

Un argument introuvable produit un seul message `cannot access`, puis le programme passe à l'argument suivant. Le code de sortie est `2`. L'indice de l'argument avance après l'erreur.

Si `opendir` échoue, le programme continue. Pour un argument, il écrit `cannot open directory` avec la raison donnée par le système, et le code de sortie est `2`. Pour un dossier rencontré pendant `-R`, il garde le code `1` et poursuit le reste de l'affichage.

Chaque entrée lue par `readdir` reçoit un type avant la récursion. Seul un dossier, autre que `.` et `..`, est ouvert.

Avec `-R`, et quand plusieurs arguments sont des dossiers, chaque bloc commence par `chemin:` même sans `-l`. Une ligne vide le sépare du bloc précédent.

`opendir` est refermé avec `closedir`. `path`, le `statbuf`, et les copies du propriétaire, du groupe et du mois sont libérés.
