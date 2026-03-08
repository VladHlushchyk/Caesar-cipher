#ifndef MENU_MODULE_H
#define MENU_MODULE_H

#define MENU_SIZE 30
typedef struct Menu_Option{
    char text[64];
    void (*my_func)(void);
} MenuOpt;



void menuEncrypt(void);
void menuAddLine(void);
void menuDeleteLine(void);
void dataOutput(void);
void checkData(void);
int menuCreate(void);

#endif

MenuOpt menu_options[MENU_SIZE] = {
    {"Encrypt own text", menuEncrypt},
    {"Add data about single account to the file", menuAddLine},
    {"Read your data from the file", checkData},
    {"Delete line", menuDeleteLine},
    {"\0", NULL}
};

void menuEncrypt(void)
{
    system("cls");

    char str[SIZE];
    char encr[SIZE];
    char input_key[16];
    int key;

    clearBuf();

    printf("Enter the key: ");
    scanf("%d", &key);

    printf("Enter the message to encrypt:\n");
    fgets(str, SIZE, stdin);

    encrypt(str, encr, key);

    system("cls");
    printf("Result: %s\n\n", encr);
    menuCreate();
}

void menuAddLine(void)
{
    system("cls");
    ACCOUNT normal, encrypted;

    clearBuf();
    puts("Enter the Platform, where account is:");
    fgets(normal.platform, SIZE, stdin);
    puts("\nEnter the Username, of your account:");
    fgets(normal.name, SIZE, stdin);
    puts("\nEnter the Password:");
    fgets(normal.pass, SIZE, stdin);

    encrypt(normal.platform, encrypted.platform, startup_key);
    encrypt(normal.name, encrypted.name, startup_key);
    encrypt(normal.pass, encrypted.pass, startup_key);

    addAccount(encrypted.platform, encrypted.name, encrypted.pass);

    system("cls");
    printf("Line:\n Platform: %s Username: %s Password: %s\n was successfully added\n\n", encrypted.platform, encrypted.name, encrypted.pass);
    menuCreate();
}

void menuDeleteLine(void)
{
    int del_line;
    dataOutput();

    clearBuf();

    puts("\nEnter the number of the line you want to delete");
    scanf("%d", &del_line);

    deleteLine(del_line);

    system("cls");
    printf("\nLine number %d was successfully deleted\n\n", del_line);
    menuCreate();
}

void dataOutput(void)
{
    system("cls");
    ACCOUNT decrypted_data[MAX_ACCOUNTS_AMOUNT];
    ACCOUNT data[MAX_ACCOUNTS_AMOUNT];
    if(fileRead(data) == ERR) {puts("dataOutput Error"); return;}

    printf("%-5s  | %30s | %30s | %20s\n", "№", "PLATFORM", "USERNAME", "PASSWORD");
    puts("-----+--------------------------------+--------------------------------+---------------------\n");

    int i = 0;
    while(data[i].platform[0] != '\0'){
        encrypt(data[i].platform, decrypted_data[i].platform, -startup_key);
        encrypt(data[i].name, decrypted_data[i].name, -startup_key);
        encrypt(data[i].pass, decrypted_data[i].pass, -startup_key);

        printf("%-5d| %30s | %30s | %20s\n", i+1, decrypted_data[i].platform, decrypted_data[i].name, decrypted_data[i].pass);
        ++i;
    }

}

void checkData(void)
{
    dataOutput();

    puts("\n\n");
    menuCreate();
}



int menuCreate(void)
{
    puts("Chose one option from exposed below:");

    int i = 0;
    while(menu_options[i].my_func != NULL && i < MENU_SIZE){
        printf("%2d) %s\n", i+1, menu_options[i].text);
        ++i;
    }

    int opt;
    scanf("%d", &opt);
    (*menu_options[opt-1].my_func)();

    return SUCCESS;
}