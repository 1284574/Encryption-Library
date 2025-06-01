/* example.c */

#include "rc4.h"
#include <time.h>
#define F fflush(stdout)  // flushes stdout buffer immediately to not wait on delays

int main(void); // function definition

// 1 byte is represented by 2 hexadecimal characters
// Ex: ef20 ac12 ....

void printbin(int8 *input, int16 size)
{
     int16 i; 
     int8 *p;

     // i=32 aa
     // i=31 bb

     assert(size > 0); // function checks if condition is true, if not true, program halts

     for(i = size, p = input; i; i--, p++)
     {
        // if i is even we will print a space
         if(!(i % 2))
         {
            printf(" ");
         }
         printf("%.02x", *p); // otherwise print p
     }
     // flush buffer
     printf("\n");

}


int main()
{
    rc4 *rc; // pointer to struct
    int16 skey, stext; // 16 bits for size of key and text
    char *key, *from;
    int8 *encrypted, *decrypted;
    int key_length = 8; // or however long you want your key to be
    key = malloc(key_length + 1); // +1 for null-terminator (if needed)
    srand(time(NULL)); // seed once at start of program
    // generate a random key using the specified charset
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int charset_size = sizeof(charset) - 1;
    for (int i = 0; i < key_length; ++i)
    {
        key[i] = charset[rand() % charset_size];
    }
    key[key_length] = '\0'; // set end of key string to null terminating character
    //key = "tomatoes"; /* 8 bits -> 2048 bits for encryption key */
    skey = strlen(key);
    from = "Shall I compare thee to a summer's day?"; /* text to encrypt */
    stext = strlen(from);

    printf("Initializing encryption...."); F; // flush stdout buffer here
    rc = rc4init((int8*) key, skey); // initalize with key and size of key
    printf("Done\n");
    printf("'%s'\n ->", from);
    // encrypts with text and size of text
    encrypted = rc4encrypt(rc, (int8*) from, stext);
    printbin(encrypted, stext); // print encrypted text
    rc4uninit(rc); // free memory associated with rc
    printf("Initializing encryption...."); F; // flush stdout buffer here
    rc = rc4init((int8*) key, skey); // initalize with key and size of key
    printf("Done\n");
    // decrypted text
    decrypted = rc4decrypt(rc, encrypted, stext);
    printf(" -> '%s'\n", decrypted);
    //printbin(encrypted, stext);


}