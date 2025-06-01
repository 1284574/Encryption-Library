/* rc4.h */
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

#define MS             500 // 500 million bytes

// explicitly export function
#define export             __attribute__((visibility("default")))

#define rc4decrypt(x, y, z)   rc4encrypt(x, y, z)
// unencrypt text
#define rc4uninit(x)       free(x)
// for many millions of bytes need to "whitewash" away before starting encryption
// volatile - gcc does not apply optimizations (Ex: -O2)
#define rc4whitewash(x, y)    for(x = 0; x < (MS * 1000000); x++) \
                                (volatile int8) rc4byte(y);


typedef unsigned char int8; // 8 bit type
typedef unsigned short int int16; // 16 bit type
typedef unsigned int int32; // 32 bit type

// setup encryption for initialization
typedef struct rc4
{
   int16 i, j, k; // variables used in algorithm
   int8 s[256]; // permutation array

} rc4;

// intialization function rc4 cipher
// take they key, prepare 
export rc4 *rc4init(int8*, int16);
// function to encrypt byte by byte
int8 rc4byte(rc4*);
// encrypts text, decrypt() will just call encrypt again
export int8 *rc4encrypt(rc4*, int8*, int16);

int8 *rc4decrypt(rc4*, int8*, int16);

