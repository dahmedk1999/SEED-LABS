#include <openssl/bn.h>
#include <stdio.h>
#include <string.h>

void ascii2hex(char*in,char*out)
{
    int loop=0;
    int i=0;
    while(in[loop]!= '\0')
    {
        sprintf((char*)(out+i),"%02x",in[loop]);
        loop+=1;
        i+=2;
    }
    out[i++]='\0';
}
BIGNUM *encrypt(BIGNUM *M, BIGNUM *e,BIGNUM *PU){
    BN_CTX *ctx = BN_CTX_new();
	BIGNUM* M_enc = BN_new();
	BN_mod_exp(M_enc, M, e, PU, ctx);
	BN_CTX_free(ctx);
	return M_enc;
}
BIGNUM *decrypt(BIGNUM *M_enc, BIGNUM *PK,BIGNUM *PU){
    BN_CTX *ctx = BN_CTX_new();
	BIGNUM* M = BN_new();
	BN_mod_exp(M, M_enc, PK, PU, ctx);
	BN_CTX_free(ctx);
	return M;
}
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
char* message="A top secret!";
char* out;
printf("\nTask2\n");
ascii2hex(message,out);
printf("Secret message to encrypt: %s\n",out);

BN_hex2bn(&n,"DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");//PU
BN_hex2bn(&e,"010001"); //modulus
BN_hex2bn(&M,out); //"A top secret!" encoded to hex
BN_hex2bn(&d,"74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");//PK

printBN("Message plaintext\t:",M);

//Task2: Encrypting the top secret
BN_mod_exp(enc,M,e,n,ctx);
printBN("Encrypted M:\t",enc);

BN_mod_exp(dec,enc,d,n,ctx);
printBN("Decrypted M:\t",dec);


// Task3 : Decrypting a Message
printf("\nTask3\n");
BIGNUM *C= BN_new();
BN_hex2bn(&C,"8C0F971DF2F3672B28811407E2DABBE1DA0FEBBBDFC7DCB67396567EA1E2493F");

BN_mod_exp(dec,C,d,n,ctx);
printBN("Ciphertext decryption:",dec);


//Task4
printf("\nTask4\n");
message="I owe you $2000.";
ascii2hex(message,out);
printf("message in hex: %s",out);
BN_hex2bn(&M,out);
BN_mod_exp(enc,M,d,n,ctx);
printBN("\nSigning 'I owe you $2000': ",enc);

BN_mod_exp(dec,enc,e,n,ctx);
printBN("unsigning:",dec);

message="I owe you $3000.";
ascii2hex(message,out);
printf("message in hex: %s",out);

BN_hex2bn(&M,out);
BN_mod_exp(enc,M,d,n,ctx);
printBN("\nSigning 'I owe you $3000': ",enc);

BN_mod_exp(dec,enc,e,n,ctx);
printBN("unsigning:",dec);
}
