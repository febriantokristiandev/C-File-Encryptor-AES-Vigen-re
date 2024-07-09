#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <io.h> // Untuk _unlink() pada Windows

#define AES_BLOCK_SIZE 16
#define MAX_PATH 1024
#define KEY_SIZE 32 // 256-bit key
#define ENCRYPTED_EXT ".encrypted"

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

void encryptFile(const char *inputFile, const char *outputFile, const unsigned char *key) {
    EVP_CIPHER_CTX *ctx;
    FILE *inFile = fopen(inputFile, "rb");
    FILE *outFile = fopen(outputFile, "wb");
    unsigned char iv[AES_BLOCK_SIZE];
    unsigned char buffer[AES_BLOCK_SIZE];
    unsigned char ciphertext[AES_BLOCK_SIZE + AES_BLOCK_SIZE];
    int len;
    int ciphertext_len;

    if (!inFile || !outFile) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }

    // Generate a random IV
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        handleErrors();
    }
    fwrite(iv, 1, AES_BLOCK_SIZE, outFile);

    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        handleErrors();
    }

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
        handleErrors();
    }

    while ((len = fread(buffer, 1, AES_BLOCK_SIZE, inFile)) > 0) {
        if (1 != EVP_EncryptUpdate(ctx, ciphertext, &ciphertext_len, buffer, len)) {
            handleErrors();
        }
        fwrite(ciphertext, 1, ciphertext_len, outFile);
    }

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext, &ciphertext_len)) {
        handleErrors();
    }
    fwrite(ciphertext, 1, ciphertext_len, outFile);

    EVP_CIPHER_CTX_free(ctx);
    fclose(inFile);
    fclose(outFile);

    // Hapus file input setelah enkripsi selesai
    if (_unlink(inputFile) != 0) {
        perror("Error deleting file");
    } else {
        printf("Input file deleted successfully.\n");
    }
}

void decryptFile(const char *inputFile, const char *outputFile, const unsigned char *key) {
    EVP_CIPHER_CTX *ctx;
    FILE *inFile = fopen(inputFile, "rb");
    FILE *outFile = fopen(outputFile, "wb");
    unsigned char iv[AES_BLOCK_SIZE];
    unsigned char buffer[AES_BLOCK_SIZE + AES_BLOCK_SIZE];
    unsigned char plaintext[AES_BLOCK_SIZE];
    int len;
    int plaintext_len;

    if (!inFile || !outFile) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }

    // Read IV from the input file
    fread(iv, 1, AES_BLOCK_SIZE, inFile);

    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        handleErrors();
    }

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
        handleErrors();
    }

    while ((len = fread(buffer, 1, AES_BLOCK_SIZE + AES_BLOCK_SIZE, inFile)) > 0) {
        if (1 != EVP_DecryptUpdate(ctx, plaintext, &plaintext_len, buffer, len)) {
            handleErrors();
        }
        fwrite(plaintext, 1, plaintext_len, outFile);
    }

    if (1 != EVP_DecryptFinal_ex(ctx, plaintext, &plaintext_len)) {
        handleErrors();
    }
    fwrite(plaintext, 1, plaintext_len, outFile);

    EVP_CIPHER_CTX_free(ctx);
    fclose(inFile);
    fclose(outFile);

    // Hapus file input setelah dekripsi selesai
    if (_unlink(inputFile) != 0) {
        perror("Error deleting file");
    } else {
        printf("Input file deleted successfully.\n");
    }
}

void getInput(const char *prompt, char *input) {
    printf("%s", prompt);
    fgets(input, MAX_PATH, stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline character
}

void replaceExtension(char *filename, const char *newExt) {
    char *dot = strrchr(filename, '.');
    if (dot != NULL) {
        *dot = '\0'; // Remove existing extension
    }
    strcat(filename, newExt); // Add new extension
}

void restoreExtension(char *filename, const char *ext) {
    char *dot = strrchr(filename, '.');
    if (dot != NULL) {
        *dot = '\0'; // Remove existing extension
    }
    strcat(filename, ext); // Add original extension
}

int main() {
    char inputFile[MAX_PATH];
    char outputFile[MAX_PATH];
    char operation[MAX_PATH];
    char originalExt[MAX_PATH];
    unsigned char key[KEY_SIZE] = "thisisaverysecurekeyof32bytes!"; // 256-bit key

    while (1) {
        int validOperation = 0;
        while (!validOperation) {
            printf("Enter operation (1 for encrypt, 2 for decrypt, 3 for exit): ");
            getInput("", operation);

            if (strcmp(operation, "3") == 0) {
                printf("Exiting program.\n");
                return 0;
            } else if (strcmp(operation, "1") == 0 || strcmp(operation, "2") == 0) {
                validOperation = 1;
            } else {
                printf("Invalid operation. Please enter '1' for encrypt, '2' for decrypt, or '3' for exit.\n");
            }
        }

        printf("Enter file path: ");
        getInput("", inputFile);

        if (strcmp(operation, "1") == 0) {
            // Simpan ekstensi asli
            strcpy(originalExt, strrchr(inputFile, '.'));
            strcpy(outputFile, inputFile);
            replaceExtension(outputFile, ENCRYPTED_EXT);
            encryptFile(inputFile, outputFile, key);
            printf("Encryption complete. Encrypted file: %s\n", outputFile);
        } else if (strcmp(operation, "2") == 0) {
            if (strlen(inputFile) < strlen(ENCRYPTED_EXT) ||
                strcmp(inputFile + strlen(inputFile) - strlen(ENCRYPTED_EXT), ENCRYPTED_EXT) != 0) {
                printf("Invalid file for decryption. It should have %s extension.\n", ENCRYPTED_EXT);
                continue;
            }
            // Kembalikan ekstensi asli
            strcpy(outputFile, inputFile);
            outputFile[strlen(outputFile) - strlen(ENCRYPTED_EXT)] = '\0'; // Remove .encrypted extension
            restoreExtension(outputFile, originalExt); // Restore original extension
            decryptFile(inputFile, outputFile, key);
            printf("Decryption complete. Decrypted file: %s\n", outputFile);
        }
    }

    return 0;
}
