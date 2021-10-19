#include <openssl/bn.h>


void printBN(char *msg, BIGNUM *bn){
    //convert BIGNUM to a decimal number string
    char * number_str = BN_bn2dec(bn);

    //Print the number string
    printf("%s %s \n", msg, number_str);

    //free the dynamically allocated memory (the char *)
    OPENSSL_free(number_str);
}

int main(){
//Background
BN_CTX*ctx = BN_CTX_new();
BIGNUM *a   = BN_new();
BIGNUM *b   = BN_new();
BIGNUM *res = BN_new();

// Assign a value from a decimal number string
BN_dec2bn(&a, "12345678901112231223");

// Assign a value from a hex number string
BN_hex2bn(&b, "2A3B4C55FF77889AED3F");

BN_sub(res, a, b);
printBN("a =:", a);
printBN("b =:", b);
printBN("Sub a and b =:", res);

//Gen rand num of 128 bits
BN_rand(a, 128, 0, 0);

//Gen rand prime num of 128 bits
BN_generate_prime_ex(b, 128, 1, NULL, NULL, NULL);

BN_add(res, a, b);
printBN("a =:", a);
printBN("b =:", b);

printBN("Add a and b =:", res);

//For mul,mod,exp,inv, the CTX object is needed
BN_mul(res,a,b,ctx);
printBN("a =:", a);
printBN("b =:", b);
printBN("mul=",res);

BIGNUM *n=BN_new();
BN_dec2bn(&n, "42");

BN_mod_mul(res,a,b,n,ctx); //a * b mod 42
printBN("a =:", a);
printBN("b =:", b);
printBN("a*b mod 42=",res);

BIGNUM *c=BN_new();
BN_dec2bn(&c, "3");

BN_mod_exp(res,a,c,n,ctx);
printBN("a =:", a);
printBN("a^c mod 42=",res);

BN_mod_inverse(b,a,n,ctx); //inverse mod
printBN("a =:", a);
printBN("find b where a * b mod 42 = 1 :",res);


return 0;
}