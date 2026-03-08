#define SIZE 256
#define MAX_ACCOUNTS_AMOUNT 128

typedef enum {
    ERR = -1,
    SUCCESS
} Status;

typedef struct ACCOUNT_DATA{
    char platform[256];
    char name[256];
    char pass[256];
} ACCOUNT;

const char alphabet[] = {"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789_-?!. ,:@#$%^&*()[]{}\'\"/\\|+=<>"};//You can add here any symbol, except of '\0' and/or '\n'. Also you can change sequence.
int index_of_char[sizeof(alphabet)];
int startup_key;


int indexInit(void);
int mod(int num);
void clearBuf(void);
char *encrypt(char *str, char *res, int key);


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



#include "files.h"
#include "menu.h"

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
        else if( id > alphabet_size || id <= 0 )
            id = (cur + key + alphabet_size) % alphabet_size;
        
        if( id < alphabet_size && id >= 0)
            res[i] = alphabet[id];
    }
    res[str_size] = '\0';

    return res;
}

int main(void)
{
    indexInit();
    printf("Enter the key: ");
    scanf("%d", &startup_key);

    system("cls");
    menuCreate();

    return SUCCESS;
}
