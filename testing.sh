#!/bin/bash

# Function to run a test case
run_test() {
    echo "Running test: $1"
    ./cipher $2 test_input.txt test_output.txt test_key.txt $3
    if [ $? -ne 0 ]; then
        echo "Test $1 failed."
    else
        echo "Test $1 passed."
    fi
    echo
}

# Compile the cipher program
make

# Test keys
echo -n "COMPUTER76543210" > test_key.txt

# Test 1: Block Cipher Encryption with normal input
echo -n "Hello, World!" > test_input.txt
run_test "Block Cipher Encryption" B E

# Test 2: Block Cipher Decryption with normal input
run_test "Block Cipher Decryption" B D

# Test 3: Stream Cipher Encryption with normal input
run_test "Stream Cipher Encryption" S E

# Test 4: Stream Cipher Decryption with normal input
run_test "Stream Cipher Decryption" S D

# Test 5: Block Cipher Encryption with empty input
echo -n "" > test_input.txt
run_test "Block Cipher Encryption with empty input" B E

# Test 6: Stream Cipher Encryption with empty input
run_test "Stream Cipher Encryption with empty input" S E

# Test 7: Block Cipher Decryption with empty input
run_test "Block Cipher Decryption with empty input" B D

# Test 8: Stream Cipher Decryption with empty input
run_test "Stream Cipher Decryption with empty input" S D

# Test 9: Block Cipher with input smaller than key
echo -n "Short" > test_input.txt
run_test "Block Cipher with short input" B E

# Test 10: Stream Cipher with input smaller than key
run_test "Stream Cipher with short input" S E

# Add more tests for different cases like longer input, special characters, etc.

# Cleanup
rm test_input.txt test_output.txt test_key.txt
