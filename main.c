#define SIZE 256

typedef enum {
    ERR = -1,
    SUCCESS
} Status;

const char alphabet[] = {"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789_-?!. ,:@#$%^&*()[]{}\'\"/\\|+=<>"};

int index_of_char[sizeof(alphabet)];


int indexInit(void);
int mod(int num);
void clearBuf(void);
char *encrypt(char *str, char *res, int key);


#include <stdio.h>
#include <string.h>



#include "files.h"

// END OF THE HEADER


int indexInit(void)
{
    int i;
    for(i = 0; i < sizeof(alphabet); ++i)
        index_of_char[alphabet[i]] = i;

    return i;
}

int mod(int num)
{
    return num >= 0 ? num : -num;
}

void clearBuf(void)
{
    while(getchar() != '\n');
}

char *encrypt(char *str, char *res, int key)
{
    
    int str_size = strlen(str);
    int alphabet_size = strlen(alphabet);
    
    for(int i=0; i<str_size; ++i){
        char c = str[i];
        if(c == '\n' || c == '\0'){
            res[i] = '\0';
            break;
        }

        int cur = index_of_char[c];
        int id = cur + key;

        if(cur == ERR)
            return "ERR";
        else if( id > alphabet_size || id < 0 )
            id = (cur + (key % alphabet_size) + alphabet_size) % alphabet_size;
        
        if( id < alphabet_size && id > 0)
            res[i] = alphabet[id];
    }
    res[str_size] = '\0';

    return res;
}

int main(void)
{
    indexInit();
    int key;
    puts("Enter the key:");
    scanf("%d", &key);

    char str[SIZE];
    char decr[SIZE];
    char encr[SIZE];

    clearBuf();

    printf("\nEnter the message to encrypt\n");
    fgets(str, SIZE, stdin);

    encrypt(str, encr, key);
    encrypt(encr, decr, -key);
    
    printf("%s", encr);

    return SUCCESS;
}
