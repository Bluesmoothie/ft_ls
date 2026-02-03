# FT_LS

Just like ls

## Usage

```bash
ls <options> <directories>
```

## Mandatory

### What's working

-l : longformat output\
-R : recursive mode\
-a : show hidden files\
-r : reverse order\
-t : sort by last modification time

### What's missing

## Bonus

### What's working

-u : sort by access (-ltu : sort by and show) (-lu : show and sort by name)\
-c : like -u but with creation time\
-f : add -aU and suppress color\
-U : dot not sort\
-g : -l without owner\
-o : -l without group\
--help and --version

### What's missing

-d : list directories ?

### May add

-A : do not list . and ..\
-G : don't list groups in -l\
-m : comma separated output\
-n : -l with numeric group and owner\
-p : append / to directories\
-S : sort by size\
-x : sort by line, not column\
-X : sort by extension\
-1 : one file per line\
--color

## TODO

Optimizations !

> [!NOTE]
> Not exactly the same order as ls in recursive mode (-R), for the rest it's an exact copy (I think) !
