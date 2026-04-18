#!/bin/sh

bad_functions=("strlen" "strcpy" "strcmp" "strcat" "strdup" "sprintf" "wcscpy" "wcslen")

for i in "${bad_functions[@]}"
do
    echo "checking for $i"
    grep -r $i ./src/*
done

