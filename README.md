# Cipher Program

## Overview

This program is a simple cipher tool capable of performing block and stream cipher encryption and decryption on input files using a specified key.

## Compilation

To compile the program, run the following command in the directory containing the program files. This will generate a binary named `cipher` in the current directory.

```
make
```

## Usage

The `cipher` program requires five command-line arguments in the following order:

1. **Cipher Function Type**: 'B' for Block cipher or 'S' for Stream cipher.
2. **Input File Name**: Name of the file containing plaintext (for encryption) or ciphertext (for decryption).
3. **Output File Name**: Name of the file where the encrypted or decrypted output will be stored.
4. **Key File Name**: Name of the file containing the symmetric key. Key size should be 128 bits (16 bytes) for Block Encryption. For Stream Encryption, the key can be of any length.
5. **Mode of Operation**: 'E' for encryption or 'D' for decryption.

### Command Structure

```
./cipher [B/S] [Input File] [Output File] [Key File] [E/D]
```

### Example Commands

- Encrypt `plaintext.txt` using a block cipher with `key.txt`:
  ```
  ./cipher B plaintext.txt encrypted.txt key.txt E
  ```
- Decrypt `encrypted.txt` using a stream cipher with `key.txt`:
  ```
  ./cipher S encrypted.txt decrypted.txt key.txt D
  ```

## Program Behavior

- **Argument Checking**: Validates the correct number of arguments and the cipher function type and operation mode.
- **File Handling**: Reads input and key files, checks their existence.
- **Block Cipher**:
  - Encrypts/decrypts in 128-bit blocks.
  - Uses padding (0x81) for blocks smaller than 128 bits.
  - Applies XOR operation and a byte-swap algorithm.
- **Stream Cipher**:
  - Performs an XOR operation of the input data with the key, looping over the key if necessary.

## Error Handling

The program includes basic error handling for invalid arguments and file read/write errors. Error messages are displayed in case of any issues.
