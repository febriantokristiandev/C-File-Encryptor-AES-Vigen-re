# C-File-Encryptor-AES-Vigenère

## Description

**C-File-Encryptor-AES-Vigenère** is a simple command-line program that lets you encrypt and decrypt files using the AES-256-CBC method. It also automatically changes the file's extension to show whether it is encrypted or decrypted.

## Features

- Encrypt and decrypt files using AES-256.
- Delete input files after encryption or decryption is completed.
- Retain and restore the original file extension after decryption.
- Provide a simple text-based user interface.

## Installation

### Windows

1. **Install OpenSSL**:
   - Download the installer from the official [OpenSSL website](https://slproweb.com/products/Win32OpenSSL.html).
   - Run the installer and follow the instructions.
   - Add the path to the OpenSSL bin folder (`C:\Program Files\OpenSSL-Win64\bin`) to the `PATH` environment variable.

2. **Compile the Program**:
   - Open Command Prompt or terminal.
   - Navigate to the directory containing the source code.
   - Use the following command to compile the program:
     ```sh
     gcc -o file_encryptor main.c -lssl -lcrypto
     ```

### Linux

1. **Install OpenSSL**:
   - Open a terminal.
   - Install OpenSSL using the package manager:
     ```sh
     sudo apt update
     sudo apt install libssl-dev
     ```

2. **Compile the Program**:
   - Navigate to the directory containing the source code.
   - Use the following command to compile the program:
     ```sh
     gcc -o file_encryptor main.c -lssl -lcrypto
     ```

## Usage

1. **Run the Program**:
   - Open a terminal or Command Prompt.
   - Navigate to the project directory:
     ```sh
     cd c-file-encryptor-aes-vigenere
     ```
   - Run the program with the following command:
     ```sh
     ./main.exe
     ```

2. **Operations**:
   - Select the desired operation:
     - Enter `1` for encryption.
     - Enter `2` for decryption.
     - Enter `3` to exit the program.
   - Enter the path of the file to be processed. The program will automatically add the `.encrypted` extension for encrypted files and restore the original extension for decrypted files.

## Examples

1. **Encrypt a File**:
   - Enter `1` for encryption.
   - Enter the path of the file to be encrypted, e.g., `document.txt`.
   - The encrypted file will be saved as `document.encrypted`.

2. **Decrypt a File**:
   - Enter `2` for decryption.
   - Enter the path of the file to be decrypted, e.g., `document.encrypted`.
   - The decrypted file will be restored to its original name, i.e., `document.txt`.
