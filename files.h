#ifndef FILES_MODULE_H
#define FILES_MODULE_H

#define FILE_NAME "data.pass"
#define TEMP_FILE_NAME "temp.pass"

int fileAppend(char *text);
int addAccount(char *platform, char *name, char *mail, char *pass);
char *handleData(char *buf, char *p1, char *p2);
char *readLine(FILE *file, char *buf);
int fileRead(ACCOUNT *data);

#endif


// APPEND(ADD) INFORMATION TO FILE

int fileAppend(char *text)
{
    FILE *file = fopen(FILE_NAME, "a");

    fprintf(file, "%s", text);

    fclose(file);
    return 0;
}

int addAccount(char *platform, char *name, char *mail, char *pass)
{
    fileAppend(" Platform: ");
    fileAppend(platform);
    fileAppend(" Username: ");
    fileAppend(name);
    fileAppend(" el.-mail: ");
    fileAppend(mail);
    fileAppend(" Password: ");
    fileAppend(pass);
    fileAppend("\n");
 
    return SUCCESS;
}

// SECTION OF FUNCTIONS READ AND HANDLE INFORMATION FROM THE FILE

char *handleData(char *buf, char *p1, char *p2)
{
    int sub = mod(p2 - p1);

    int j=0;
    for(int i = 11; i<sub; ++i, ++j){
        if(p1[i] == '\n')
            break;
        buf[j] = p1[i];
    }
    buf[j] = '\0';

    return buf;
}

char *readLine(FILE *file, char *buf)
{
    int i = 0;
    char c = fgetc(file);
    while(!feof(file) && i < SIZE){
        if(c == '\n')
            break;
        buf[i] = c; 
        c = fgetc(file);
        ++i;
    }
    buf[i] = '\0';

    return buf;
}

int fileRead(ACCOUNT *data)
{
    char buf[SIZE];
    FILE *file = fopen(FILE_NAME, "r");
    if(file == NULL){puts("File isn't exist at the moment."); return ERR;}
    
    int i = 0;

    char *p1, *p2, *p3, *p4;
    do{
    readLine(file, buf);
    
    p1 = strstr(buf, " Platform: ");
    p2 = strstr(buf, " Username: ");
    p3 = strstr(buf, " el.-mail: ");
    p4 = strstr(buf, " Password: ");
    handleData(data[i].platform, p1, p2);
    handleData(data[i].name, p2, p3);
    handleData(data[i].mail, p3, p4);
    handleData(data[i].pass, p4, p1);

    ++i;
    }while(!feof(file));
    data[i].platform[0] = '\0';

    fclose(file);
    return SUCCESS;
}

// TO DELETE THE LINE

int deleteLine(int del_line){
    FILE *file = fopen(FILE_NAME, "r");
    FILE *temp = fopen(TEMP_FILE_NAME, "w");
    char buf[SIZE];

    if(file == NULL || temp == NULL)
    {
        puts("Err: unable to open/read file(s)");
        return ERR;
    }

    char keep_reading = true;
    int cur_line = 1;

    do{
        fgets(buf, SIZE, file);
        if(feof(file)) keep_reading = false;
        else if(cur_line != del_line)
            fputs(buf, temp);

        ++cur_line;
    }while(keep_reading);

    fclose(file);
    fclose(temp);

    remove(FILE_NAME);
    rename(TEMP_FILE_NAME, FILE_NAME);


    return SUCCESS;
}