# FT_LS

## Mandatory

### What's working
-l : longformat output\
-R : recursive mode\
-a : show hidden files\
-r : reverse order\
-t : sort by last modification time\

### What's missing

## Bonus

### What's working

### What's missing
-u : sort by access (-ltu : sort by and show) (-lu : show and sort by name)\
-f : do not sort (add -aU and suppress color)\
-g : -l without owner\
-d : list directories ?\

### May add :
-U : needed for -f\
-c : like -u but with creation time\
-A : do not list . and ..\
-G : don't list groups in -l\
-m : comma separated output\
-n : -l with numeric group and owner\
-o : -l without group\
-p : append / to directories\
-S : sort by size\
-x : sort by line, not column\
-X : sort by extension\
-1 : one file per line\
--help --color and --version\

## TODO
Optimization !\
Caching group and user strings

## Notes
Not exactly the same order as ls in recursive mode (-R), for the rest it's an exact copy (I think) !