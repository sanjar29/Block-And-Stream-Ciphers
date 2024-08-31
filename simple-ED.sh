#!/bin/bash
make
echo "ABCDEFGHIJKLMNOPQ" > input.txt
./cipher B input.txt output.txt key.txt E
./cipher B output.txt input.txt key.txt D
cat input.txt
echo
echo "ABCDEFGHIJKLMNOPQ" > input.txt
./cipher S input.txt output.txt key.txt E
./cipher S output.txt input.txt key.txt D
cat input.txt
echo
