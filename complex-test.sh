#!/bin/bash

# Function to run a test case
run_test() {
    echo "Testing with input: '$1'"
    echo -n "$1" > input.txt

    # Test Block Cipher
    ./cipher B input.txt output.txt key.txt E
    ./cipher B output.txt input.txt key.txt D
    echo -n "Block Cipher result: "
    cat input.txt
    echo -e "\n"

    # Test Stream Cipher
    ./cipher S input.txt output.txt key.txt E
    ./cipher S output.txt input.txt key.txt D
    echo -n "Stream Cipher result: "
    cat input.txt
    echo -e "\n"
}

# Compile the cipher program
make

# Test with various inputs
run_test "ABCDEFGHIJKLMNOPQ"          # Basic Alphabet
run_test "The quick brown fox jumps over the lazy dog" # Pangram
run_test "1234567890"                 # Numbers
run_test "!@#$%^&*()_+-=[]{}|;:,.<>/?~" # Special Characters
run_test "Mixed123!@#Content"         # Mixed Content
run_test "Short"                      # Short String
run_test ""                           # Empty String
run_test "A longer string with spaces and different characters." # Longer String
run_test "$(head /dev/urandom | tr -dc 'a-zA-Z0-9' | head -c 64)" # Random String

# Cleanup
rm input.txt output.txt
