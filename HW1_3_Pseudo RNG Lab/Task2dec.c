#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <openssl/aes.h>

#define KEYSIZE 16
int START = 1524013729;
int END = 1524020929;

/* AES key for Encryption and Decryption */
unsigned char aes_key[KEYSIZE];

/* Print Encrypted and Decrypted data packets */
void print_data(const char *tittle, const void *data, int len);

int main()
{
    int found;
    unsigned char plaintext[] = {0x25, 0x50, 0x44, 0x46, 0x2d, 0x31, 0x2e, 0x35, 0x0a, 0x25, 0xd0, 0xd4, 0xc5, 0xd8, 0x0a, 0x34};
    unsigned char ciphertext[] = {0xd0, 0x6b, 0xf9, 0xd0, 0xda, 0xb8, 0xe8, 0xef, 0x88, 0x06, 0x60, 0xd2, 0xaf, 0x65, 0xaa, 0x82};
    const unsigned char Originaliv[] = {0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00, 0xA2, 0xB2, 0xC2, 0xD2, 0xE2, 0xF2};
    int ivSize = sizeof(Originaliv);
    unsigned char iv[ivSize];
    unsigned char encrypted[sizeof(plaintext)];

    unsigned char enc_out[2 * sizeof(plaintext)];
    AES_KEY enc_key;

    for (int i = START; i <= END; i++)
    {
        found = 1;
        printf("Key %d: ", (i - START));
        srand(i); // Generate seed using time
        for (int j = 0; j < KEYSIZE; j++)
        {
            aes_key[j] = rand() % 256; // generate key using seed
            printf("%.2x", (unsigned char)aes_key[j]);
        }
        printf("\n");

        /* AES-128 bit CBC Encryption */
        memcpy(iv, Originaliv, ivSize);
        AES_set_encrypt_key(aes_key, sizeof(aes_key) * 8, &enc_key); // Size of key is in bits
        AES_cbc_encrypt(plaintext, enc_out, sizeof(plaintext), &enc_key, iv, AES_ENCRYPT);

        printf("Encrypted Output: ");
        memcpy(encrypted, enc_out, sizeof(encrypted));
        for (int j = 0; j < sizeof(encrypted); j++)
        {
            printf("%.2x", (unsigned char)encrypted[j]);
        }
        printf("\n");

        for (int j = 0; j < sizeof(ciphertext); j++)
        {
            if (ciphertext[j] != encrypted[j])
                found = 0;
        }
        if (found == 1)
        {
            printf("The correct key is: ");
            for (int j = 0; j < sizeof(aes_key); j++)
            {
                printf("%.2x", (unsigned char)aes_key[j]);
            }
            printf("\n");
            printf("The correct time is: %d\n", i);
            break;
        }
    }
    return 0;
}
