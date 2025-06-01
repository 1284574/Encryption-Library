/* rc4.c */
#include "rc4.h"

// setup rc4 algorithm
export rc4 *rc4init(int8 *key, int16 size)
{
    int16 x; // variable for iteration
    int8 tmp1, tmp2; // temporary variables for algorithm
    rc4 *p; // pointer to struct
    int32 n;
    if(!(p = malloc(sizeof(rc4))))
    {
        assert_perror(errno); // check if errored out, displays error message
        // and exits function
    }
    // zero out array element by element
    for(x=0; x < 256; x++)
    {
        p->s[x] = 0;
    }
    // intialize all members of struct to 0
    p->i = p->j = p->k = 0;
    tmp1=tmp2=0;


    // Key scheduling Algorithm:
    // for i from 0 to 255
    //     S[i] := i
    // endfor
    // j := 0
    // for i from 0 to 255
    //     j := (j + S[i] + key[i mod keylength]) mod 256
    //     swap values of S[i] and S[j]
    // endfor

    // Implementation:

    for(p->i = 0; p->i < 256; p->i++)
    {
        p->s[p->i] = p->i;
    }
    for(p->i = 0; p->i < 256; p->i++)
    {
          tmp1 = p->i % size; // i mod keylength
          tmp2 = p->j + p->s[p->i] + key[tmp1]; // j + S[i] + key[i mod keylength] 
          p->j = tmp2 % 256; // j := (j + S[i] + key[i mod keylength]) mod 256
          tmp1 = p->s[p->i]; // S[i]
          tmp2 = p->s[p->j]; // S[j]
          // swap values of S[i] and S[j]
          p->s[p->i] = tmp2;
          p->s[p->j] = tmp1;
    }

    p->i=p->j = 0;
    rc4whitewash(n, p);
    return p;
}

// each time function is called it will produce one byte, encrypts 1 byte at a time
int8 rc4byte(rc4 *p)
{
    int16 tmp1, tmp2; // temporary variables for use in algorithm

    // Pseudo-random generation algorithm:
    // while GeneratingOutput:
    //     i := (i + 1) mod 256
    //     j := (j + S[i]) mod 256
    //     swap values of S[i] and S[j]
    //     t := (S[i] + S[j]) mod 256
    //     K := S[t]
    //     output K
    //     endwhile
    p->i = (p->i + 1) % 256;
    p->j = (p->j + p->s[p->i]) % 256;
    // swap values of S[i] and S[j]
    tmp1 = p->s[p->i];
    tmp2 = p->s[p->j];
    p->s[p->i] = tmp2;
    p->s[p->j] = tmp1;
    tmp1 = (p->s[p->i] + p->s[p->j]) % 256; //  t := (S[i] + S[j]) mod 256
    p->k = p->s[tmp1]; // K := S[t]
    return p->k;
}

// function to encrypt text (cleartext) to ciphered form (ciphertext)
// decrypt is just encrypt called again
export int8 *rc4encrypt(rc4 *p, int8 *cleartext, int16 size)
{
     int8 *ciphertext; // buffer for encrypted text
     int16 x;

     ciphertext = (int8*) malloc(size + 1);
     // if malloc fails assert an error
     if(!ciphertext)
     {
        assert_perror(errno);     
     }

     for(x=0; x < size; x++)
     {
          // to create the ciphertext, we go byte by byte
          // the rc4byte() function will return 1 byte which will be
          // XOR'd with cleartext char
          ciphertext[x] = cleartext[x] ^ rc4byte(p);
          // XOR operation:
          // 0 0 = 0
          // 1 0 = 1
          // 0 1 = 1
          // 1 1 = 0
     }
     return ciphertext;
}