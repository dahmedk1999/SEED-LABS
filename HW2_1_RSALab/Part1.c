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
BN_CTX *ctx = BN_CTX_new();
BIGNUM *p= BN_new();
BIGNUM *q= BN_new();
BIGNUM *e= BN_new();
BIGNUM *n= BN_new();
BIGNUM *d= BN_new();
BIGNUM *one= BN_new();
BN_hex2bn(&p,"F7E75FDC469067FFDC4E847C51F452DF");
BN_hex2bn(&q,"E85CED54AF57E53E092113E62F436F4F");
BN_hex2bn(&e,"0D88C3");
BN_hex2bn(&one,"1");

BN_mul(n,p,q,ctx);
printBN("n= p*q: ",n);

//totient n
//p --> p-1
//q --> q-1
//n --> ϕ(n)
BN_sub(p,p,one);
BN_sub(q,q,one);
printBN("p-1: ",p);
printBN("q-1: ",q);
BN_mul(n,p,q,ctx); //p-1 * q-1
printBN("ϕ(n)=",n);

//To find PK d
//d=e^-1 mod ϕ(n)
BN_mod_inverse(d,e,n,ctx); // d*e mod ϕn = 1
printBN("d=",d);

BN_mod_mul(p,d,e,n,ctx);
printBN("d*e mod toi(n) ==",p); //validated
}
