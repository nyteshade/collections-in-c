#!/bin/sh

printf "Making listfun..."
gcc -o listfun listfun.c lists.c types.c keyvalue.c
printf "done\n"

printf "Making mapfun..."
gcc -o mapfun mapfun.c map.c types.c lists.c keyvalue.c
printf "done\n"

printf "Making listfun..."
gcc -o listfun listfun.c lists.c types.c keyvalue.c collection.c
printf "done\n"
