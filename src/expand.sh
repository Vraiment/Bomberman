#!/bin/bash

find . -type f -exec grep -l '\t' {} \; | while read line; do
    expand -t 4 $line > $line.tmp
    rm $line
    mv $line.tmp $line
done
