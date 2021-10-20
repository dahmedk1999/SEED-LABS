#include <openssl/bn.h>


void printBN(char *msg, BIGNUM *bn){
    //convert BIGNUM to a decimal number string
    char * number_str = BN_bn2dec(bn);

    //Print the number string
    printf("%s %s \n", msg, number_str);

    //free the dynamically allocated memory (the char *)
    OPENSSL_free(number_str);
}


int main()
{
BN_CTX *ctx = BN_CTX_new();
BIGNUM *n= BN_new();
BIGNUM *e= BN_new();
BIGNUM *M= BN_new();
BIGNUM *d= BN_new();
BIGNUM *enc = BN_new();
BIGNUM *dec = BN_new();

BN_hex2bn(&n,"DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
BN_hex2bn(&e,"010001");
BN_hex2bn(&M,"4120746f702073656372657421"); //"A top secret!".encode("utf-8").hex()
BN_hex2bn(&d,"74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");

printBN("Message in dec:",M);

//Encrypting the top secret message and replace original
BN_mod_exp(enc,M,e,n,ctx);
printBN("Encrypted M: ",enc);

BN_mod_exp(dec,enc,d,n,ctx);
printBN("Decrypted M: ",dec);


// Task3
BIGNUM *C= BN_new();
BN_hex2bn(&C,"8C0F971DF2F3672B28811407E2DABBE1DA0FEBBBDFC7DCB67396567EA1E2493F");

BN_mod_exp(dec,C,d,n,ctx);
printBN("Ciphertext decryption:",dec);

}
