# Block and Stream Encryption/Decrytion Program

## At a glance

This project performs block and stream cipher encryption and decryption on plain text given a key.

## How to Compile

Run the following command in the terminal. Makefile is visited and ran to create an executable called 'cipher' which will make the running of the program easy moving forward.

```
make
```

## How to Use it

The program requires five command-line arguments in order as follows:

1. **Cipher Function Type**: 'B' - Block cipher, or 'S' - Stream cipher. Which method of encryption/decryption are you gonna use?
2. **Input File Name**: Input file that has the plaintext for encryption or ciphertext to be decryption.
3. **Output File Name**: Output file to which the encrypted/decrypted output will be written.
4. **Key File Name**: Key file containing the symmetric key. Key size should be 16 bytes for Block Encryption. For Stream Encryption, can be of any length.
5. **Mode of Operation**: 'E'- encryption or 'D' - decryption.

### Example command line after creating the 'cipher' executable:

```
./cipher [B/S] [Input File Name] [Output File Name] [Key File Name] [E/D]
```

- Encrypt `plaintext.txt` using a block cipher with `key.txt`:
  ```
  ./cipher B plaintext.txt encrypted.txt key.txt E
  ```
- Decrypt `encrypted.txt` using a stream cipher with `key.txt`:
  ```
  ./cipher S encrypted.txt decrypted.txt key.txt D
  ```

## Program Behavior

- **Argument Validation**: Ensures the correct number of arguments, cipher type, and mode of operation are provided.
- **File Processing**: Handles input and key files, verifying that they exist.
- **Block Cipher**:
  - Processes encryption/decryption in 128-bit blocks.
  - Adds padding (0x81) for blocks that are less than 128 bits.
  - Performs an XOR operation followed by a byte-swapping algorithm.
- **Stream Cipher**:
  - Executes an XOR operation on the input data with the key, repeating the key if needed.

## Error Handling

The program features basic error handling for incorrect arguments and file read/write issues. Error messages are generated if any problems occur.
