#!/bin/sh

printf "Making listfun..."
gcc -o ListFun ListFun.c Lists.c Types.c KeyValue.c
printf "done\n"

printf "Making mapfun..."
gcc -o MapFun MapFun.c Map.c Types.c Lists.c KeyValue.c Collection.c
printf "done\n"

printf "Making collectionfun..."
gcc -o CollectionFun CollectionFun.c Collection.c Lists.c Types.c KeyValue.c Map.c
printf "done\n"

printf "Making bitsetfun..."
gcc -o BitSetFun BitSetFun.c BitSet.c
printf "done\n"
