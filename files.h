#ifndef FILES_MODULE_H
#define FILES_MODULE_H

#define FILE_NAME "data.pass"

typedef struct ACCOUNT_DATA{
    char platform[256];
    char name[256];
    char pass[256];
} ACCOUNT;

int fileAppend(char *text);
char *handleData(char *buf, char *p1, char *p2);
char *readLine(FILE *f, char *buf);
int fileRead(ACCOUNT *data);

#endif


// APPEND(ADD) INFORMATION TO FILE

int fileAppend(char *text)
{
    FILE *f = fopen(FILE_NAME, "a");

    fprintf(f, text);

    fclose(f);
    return 0;
}


// SECTION OF FUNCTIONS READ AND HANDLE INFORMATION FROM THE FILE

char *handleData(char *buf, char *p1, char *p2)
{
    int sub = mod(p2 - p1);

    int j=0;
    for(int i = 11; i<=sub; ++i, ++j){
        if(p1[i] == '\n')
            break;
        buf[j] = p1[i];
    }
    buf[j] = '\0';

    return buf;
}

char *readLine(FILE *f, char *buf)
{
    int i = 0;
    char c = fgetc(f);
    while(c != EOF && i < SIZE){
        if(c == '\n')
            break;
        buf[i] = c; 
        c = fgetc(f);
        ++i;
    }
    buf[i] = '\0';

    return buf;
}

int fileRead(ACCOUNT *data)
{
    char buf[SIZE];
    FILE *f = fopen(FILE_NAME, "r");
    if(f == NULL){puts("File isn't exist at the moment."); return ERR;}
    
    int i = 0;

    char *p1, *p2, *p3;
    do{
    readLine(f, buf);
    
    p1 = strstr(buf, " Platform: ");
    p2 = strstr(buf, " Username: ");
    p3 = strstr(buf, " Password: ");
    handleData(data[i].platform, p1, p2);
    handleData(data[i].name, p2, p3);
    handleData(data[i].pass, p3, p1);

    ++i;
    }while(p1 != p2);
    data[i].platform[0] = '\0';

    fclose(f);
    return SUCCESS;
}

int dataOutput(void)
{
    ACCOUNT data[128];
    if(fileRead(data) == ERR) {puts("dataOutput Error"); return ERR;}

    printf("%-5s  | %30s | %30s | %20s\n", "№", "PLATFORM", "USERNAME", "PASSWORD");
    puts("-----+--------------------------------+--------------------------------+---------------------\n");

    int i = 0;
    while(data[i].platform[0] != '\0'){
        printf("%-5d| %30s | %30s | %20s\n", i+1, data[i].platform, data[i].name, data[i].pass); 
        ++i;
    }

    return SUCCESS;
}