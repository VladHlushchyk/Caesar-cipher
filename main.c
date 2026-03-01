#include <stdio.h>
#include <string.h>

typedef enum {
    ERR = -1,
    SUCCESS
} Status;

const char alphabet[] = {
    'A','a','B','b','C','c','D','d','E','e','F','f','G','g','H','h',
    'I','i','J','j','K','k','L','l','M','m','N','n','O','o','P','p',
    'Q','q','R','r','S','s','T','t','U','u','V','v','W','w','X','x',
    'Y','y','Z','z',
    '0','1','2','3','4','5','6','7','8','9',
    '_','-','?','!','.',' ',',',':',';','@','#','$','%','^','&','*','(',')','[',']','{','}','\'','"','/','\\','|','+','=','<','>','~','`','\0'
};



int mod(int num)
{
    return num >= 0 ? num : -num;
}

void clearBuf(void)
{
    while(getchar() != '\n');
}

int findLetter(char l){

    for(int i=0; i<strlen(alphabet); ++i){
       if(l == alphabet[i])
          return i;
    }

    return ERR;
}

char *encrypt(char *str, char *res, int key)
{
    
    int str_size = strlen(str);
    int alphabet_size = strlen(alphabet);
    
    for(int i=0; i<str_size; ++i){
        if(str[i] == '\n' || str[i] == '\0'){
            res[i] = '\0';
            break;
        }

        int num = findLetter(str[i]);
        int id = num + key;

        if(num == ERR)
            return "ERR";
        else if( id > alphabet_size || id < 0 )
            id = (num + (key % alphabet_size) + alphabet_size) % alphabet_size;
        
        if( id < alphabet_size && id > 0)
            res[i] = alphabet[id];
    }

    return res;
}

int main(void)
{
    int key;
    puts("Enter the key:");
    scanf("%d", &key);

    char str[256];
    char decr[256];
    char encr[256];

    clearBuf();

    printf("\nEnter the message to encrypt\n");
    fgets(str, 256, stdin);

    encrypt(str, encr, key);
    encrypt(encr, decr, -key);
    
    printf("\n\n%s\n", encr);
    printf("%s\n", decr); 

    return SUCCESS;
}
