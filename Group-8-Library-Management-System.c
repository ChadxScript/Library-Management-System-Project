/*Library Management System By Group 8 - Armand Angelo C. Barrios, Mary Jane P. Calulang, and Andrew R. Oloroso*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <dirent.h>

#define KEY 70
#define LMSFolderDB ".\\LMS Database"
#define LMSLogs ".\\LMS Database\\LMS Logs"
#define LMSFlashDrive "D:\\LMS Details"
#define fill "NONE"
#define adminFillName "LibrarianADMIN"
#define adminFillID "LibrarianADMIN123"

typedef struct accountDetails{
    int skey, lkey;
    char studentID[31], studentName[31];
    char librarianID[31], librarianName[31];
}aREC;
typedef struct bookDetails{
    int bookNum, publicationYear, bookQuant;
    char bookTitle[100], bookAuthor[100], ISBN[15];
}bREC;
typedef struct logDetails{
    char date[50], 
         time[50],
         name[50],
         STATUS[50],
         ITEM[50];
}lREC;

typedef struct node{
    aREC aLib;
    bREC bLib;
    lREC rLogs;
    struct node* next;
}LIST;
LIST *A, *B, *C, *L;

//Function Declaration
void makenull();
int insertcard();
void retrieveAccounts();
void addAccount(aREC x);
void retrieveBooks();
void addBooks(bREC x);
void addBookRequests(bREC x);

void registerStudent();
int registerLibrarian();
void userLOGIN();

void displayBooks();
void displayCurrentBook(bREC *x);
void displayLogs();
void displayDirectoryContent();
int menu(int x);

void borrowBook(int x);
void returnbook();

void insertExistingBook();
void insertNewBook();
void editBooks();
void removeAcopy();
void removeBooks();
void bookRequests();

int checkAccount(int x, char str[31]);
int verifyAccount(int x);
int checkBooks(bREC *x);
int checkISBN(char *ISBN, int x);
int getBookNumber();

void decrypt(int x,char *str,int *num);
void encrypt(int x,char *str,int *num);

void saveBooks();
void saveAccounts();
void saveAccountsFD();
void logs(char status[100], char item[100]);


//Global Vars
int currentSKey, currentLKey;
char currentStudentID[31], currentStudentName[31];
char currentLibrarianID[31], currentLibrarianName[31];


//UI
void printToxy(int x, int y, char *label);
void gotoxy(int x, int y);
void front();
void loading();
int scanScreen(int a);
void delay(int ms);


int main(){
    int userNum;
    bREC bBooks;

    // make folders for database
    mkdir(LMSFolderDB);
    mkdir(LMSLogs);

    makenull();
    system("cls");
    printf("\033[1;33m");
    switch(insertcard()){
        case 1: registerStudent();
                saveAccountsFD();
                saveAccounts();  
                logs("IN",fill);
                break;
        case 2: registerLibrarian();
                saveAccountsFD();
                saveAccounts();  
                logs("IN",fill);
                break;
        case 3: userLOGIN();
                break;
        default: system("cls");
                 printf("\nINVALID INPUT.\n");
                 system("pause"); system("cls");
                 break;
    }

    retrieveBooks();
    system("cls");
    if(currentSKey==1 && currentLKey==0){ //student
        while(1){
            system("cls");
            switch(menu(1)){
                case 1: system("cls");
                        displayBooks();
                        printf("\n\nInput Book ID: ");
                        scanf("%d",&bBooks.bookNum);
                        borrowBook(bBooks.bookNum);
                        break;
                case 2: system("cls");
                        displayBooks();
                        if(verifyAccount(1)==1){
                            returnbook();
                        }else{
                            printf("\nTransaction Cancelled. Your input does not match to your cridentials.\n");
                            system("pause"); system("cls");
                        }
                        break;
                default: logs("OUT",fill); exit(0);
                         break;
            }
        }
    }else if(currentSKey==0 && currentLKey==1){ //librarian
        while(1){
            switch(menu(2)){
                case 1: system("cls");
                        displayBooks();
                        printf("\nInsert existing book?\n");
                        printf("\n[1] YES");
                        printf("\n[2] NO");
                        printf("\n[3] CANCEL");
                        scanf("%d", &userNum);

                        if(userNum==1){
                            insertExistingBook();
                        }else if(userNum==2){
                            insertNewBook();
                        }else{
                            break;
                        }
                        break;
                case 2: system("cls");
                        displayBooks();
                        editBooks();
                        break;
                case 3: system("cls");
                        printf("\n\n[1] Remove x number of copy");
                        printf("\n[2] Remove all book copies");
                        printf("\n[3] Cancel");
                        printf("\n-> ");
                        scanf("%d", &userNum);
                        if(userNum==1){
                            displayBooks();
                            removeAcopy();
                        }else if(userNum==2){
                            displayBooks();
                            removeBooks();
                        }else{
                            printf("\nCANCELLED.\n");
                            system("pause");
                        }
                        break;
                case 4: bookRequests();
                        break;
                case 5: displayBooks();
                        break;
                case 6: displayLogs();
                        break;
                default: logs("OUT",fill); exit(0);
                         break;
            }
        }
    }
}


void makenull(){ //initiate the list to null
    A = NULL;
    B = NULL;
    C = NULL;
    L = NULL;
}
int insertcard(){
    int num, i;
    HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,06);
    FILE *fp;
    //will check if the flashdrive is inserted to the device or not
    do{
        fp=fopen("D:\\LMS_Check.txt","w");
        loading();
    }while(fp==NULL);
    fclose(fp);
    mkdir(LMSFlashDrive);
    front();

    char fileName[50];
    snprintf(fileName, sizeof(fileName), "%s\\userDetails.csv", LMSFlashDrive);

    fp=fopen(fileName,"r");
    if(fp==NULL){
        retrieveAccounts();
        scanScreen(1);
        do{
            system("cls");
            printToxy(22,2," \xdc\xdc    \xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc     \xdc\xdc      \xdc\xdc    \xdc\xdc  \xdc\xdc\xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc\xdc   ");
            printToxy(22,3," \xdc\xdc\xdc   \xdc\xdc  \xdc\xdc      \xdc\xdc     \xdc\xdc      \xdc\xdc    \xdc\xdc  \xdc\xdc     \xdc\xdc      \xdc\xdc    \xdc\xdc  ");
            printToxy(22,4," \xdc\xdc \xdc\xdc \xdc\xdc  \xdc\xdc\xdc\xdc\xdc   \xdc\xdc  \xdc  \xdc\xdc      \xdc\xdc    \xdc\xdc  \xdc\xdc\xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc   \xdc\xdc\xdc\xdc\xdc\xdc\xdc   ");
            printToxy(22,5," \xdc\xdc  \xdc\xdc\xdc\xdc  \xdc\xdc      \xdc\xdc\xdc   \xdc\xdc\xdc      \xdc\xdc    \xdc\xdc     \xdc\xdc  \xdc\xdc      \xdc\xdc  \xdc\xdc    ");
            printToxy(22,6," \xdc\xdc   \xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc     \xdc\xdc      \xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc   \xdc\xdc   ");
            SetConsoleTextAttribute(h,15); printToxy(22,8,"  S   E   L   E   C   T            C   A   T   E   G   O   R   Y");
            printToxy(32,16,"[1]"); printToxy(30,12,"STUDENT");printToxy(75,16,"[2]");printToxy(72,12,"LIBRARIAN");
            SetConsoleTextAttribute(h,05);gotoxy(24,10); for(i=0;i<19;i++) printf("%c",220); gotoxy(24,14); for(i=0;i<19;i++) printf("%c",220);
            for(i=0;i<4;i++){gotoxy(24,11+i);printf("%c",219);} for(i=0;i<4;i++){gotoxy(42,11+i);printf("%c",219);}
            gotoxy(67,10); for(i=0;i<19;i++) printf("%c",220); gotoxy(67,14); for(i=0;i<19;i++) printf("%c",220);
            for(i=0;i<4;i++){gotoxy(67,11+i);printf("%c",219);} for(i=0;i<4;i++){gotoxy(85,11+i);printf("%c",219);}
            SetConsoleTextAttribute(h,15); printToxy(50,18,"Are you a: ");
            gotoxy(61,18); scanf("%d",&num);
        }while(num<1||num>3);
        return num;
    }else{
        retrieveAccounts();
        scanScreen(2);
        return 3;
    }
    fclose(fp);
}
void retrieveAccounts(){
    FILE *fp;
    aREC aLibn;

    // In Database
    char fileName[50];
    snprintf(fileName, sizeof(fileName), "%s\\Accounts.csv", LMSFolderDB);
    fp=fopen(fileName,"r+");
    if(fp!=NULL){
        while(!feof(fp)){
            fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%d,%d\n",
                    aLibn.studentID, aLibn.librarianID, aLibn.studentName,
                    aLibn.librarianName, &aLibn.skey, &aLibn.lkey);

            decrypt(1,aLibn.studentID,0);
            decrypt(1,aLibn.studentName,0);
            decrypt(1,aLibn.librarianID,0);
            decrypt(1,aLibn.librarianName,0);
            decrypt(2,"",&aLibn.skey);
            decrypt(2,"",&aLibn.lkey);

            addAccount(aLibn);
        }fclose(fp);
    }

    // flashdrive
    snprintf(fileName, sizeof(fileName), "%s\\userDetails.csv", LMSFlashDrive);
    fp=fopen(fileName, "r+");
    if(fp!=NULL){
        fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%d,%d",
                currentStudentID, currentLibrarianID, currentStudentName,
                currentLibrarianName, &currentSKey, &currentLKey);
        
        decrypt(1,currentStudentID,0);
        decrypt(1,currentStudentName,0);
        decrypt(1,currentLibrarianID,0);
        decrypt(1,currentLibrarianName,0);
        decrypt(2,"",&currentSKey);
        decrypt(2,"",&currentLKey);

        fclose(fp);
    }
}
void addAccount(aREC x){
    LIST *p, *q, *temp;
    q=p=A;
    temp = (LIST*) malloc(sizeof(LIST));
    temp->aLib = x;
    while (p!=NULL && x.lkey < p->aLib.lkey){
        q=p;
        p=p->next;
    }
    if(p==A){
        A = temp;
    }else{
        q->next = temp;
    }temp->next = p;
}
void retrieveBooks(){
    FILE *fp;
    bREC bLibn;
    
    char fileName[50];
    snprintf(fileName, sizeof(fileName), "%s\\Books.txt", LMSFolderDB);
    fp=fopen(fileName,"r+");
    if(fp==NULL){
        if(currentSKey==1 && currentLKey==0){
            printf("\nLIBRARY IS CURRENTLY EMPTY");
            printf("\nNO BOOKS TO BE FOUND :(");
            printf("\nPLEASE COME BACK LATER. SORRY FOR INCONVENIENCE.\n");
            system("pause"); 
            fclose(fp); 
            logs("OUT", fill);
            exit(0);
        }else if(currentSKey==0 && currentLKey==1){
            printf("\nLIBRARY IS CURRENTLY EMPTY");
            printf("\nNO BOOKS TO BE FOUND :(");
            printf("\nPLEASE ADD BOOKS.\n");
            system("pause");
        }else{
            printf("\nSYSTEM ERROR.");
            system("pause");
            fclose(fp); 
        }
    }else{
        while(!feof(fp)){
            fscanf(fp,"%d,%[^,],%[^,],%[^,],%d,%d\n",
                    &bLibn.bookNum, bLibn.ISBN, bLibn.bookTitle,
                    bLibn.bookAuthor, &bLibn.publicationYear, &bLibn.bookQuant);
            decrypt(2,"",&bLibn.bookNum);
            decrypt(1,bLibn.ISBN,0);
            decrypt(1,bLibn.bookTitle,0);
            decrypt(1,bLibn.bookAuthor,0);
            decrypt(2,"",&bLibn.publicationYear);
            decrypt(2,"",&bLibn.bookQuant);
            addBooks(bLibn);
        }
        fclose(fp); 
    }
}
void addBooks(bREC x){
    LIST *p, *q, *temp;
    q=p=B;
    temp = (LIST*) malloc(sizeof(LIST));
    temp->bLib = x;
    while(p!=NULL && x.bookNum > p->bLib.bookNum){
        q=p;
        p=p->next;
    }
    if(p==B){
        B = temp;
    }else{
        q->next = temp;
    }temp->next = p;
}
void addBookRequests(bREC x){
    LIST *p, *q, *temp;
    q=p=C;
    temp = (LIST*) malloc(sizeof(LIST));
    temp->bLib = x;
    while(p!=NULL && x.bookNum > p->bLib.bookNum){
        q=p;
        p=p->next;
    }
    if(p==B){
        C = temp;
    }else{
        q->next = temp;
    }temp->next = p;
}


void registerStudent(){
    aREC aLibn;
    HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,06);
    int count=0;
    fillAgain1:
        if(count<3){
            system("cls");
            currentSKey=aLibn.skey = 1; currentLKey=aLibn.lkey = 0;

            printToxy(22,2," \xdc\xdc    \xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc     \xdc\xdc      \xdc\xdc    \xdc\xdc  \xdc\xdc\xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc\xdc   ");
            printToxy(22,3," \xdc\xdc\xdc   \xdc\xdc  \xdc\xdc      \xdc\xdc     \xdc\xdc      \xdc\xdc    \xdc\xdc  \xdc\xdc     \xdc\xdc      \xdc\xdc    \xdc\xdc  ");
            printToxy(22,4," \xdc\xdc \xdc\xdc \xdc\xdc  \xdc\xdc\xdc\xdc\xdc   \xdc\xdc  \xdc  \xdc\xdc      \xdc\xdc    \xdc\xdc  \xdc\xdc\xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc   \xdc\xdc\xdc\xdc\xdc\xdc\xdc   ");
            printToxy(22,5," \xdc\xdc  \xdc\xdc\xdc\xdc  \xdc\xdc      \xdc\xdc\xdc   \xdc\xdc\xdc      \xdc\xdc    \xdc\xdc     \xdc\xdc  \xdc\xdc      \xdc\xdc  \xdc\xdc    ");
            printToxy(22,6," \xdc\xdc   \xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc     \xdc\xdc      \xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc   \xdc\xdc   ");
            SetConsoleTextAttribute(h,15); printToxy(22,8," A   P   P   L   I   C   A   T   I   O   N          F   O   R   M");
            printToxy(22,10,"Enter Student Name: ");
            printToxy(22,11,"Enter Student ID: ");
            gotoxy(42,10);scanf(" %[^\n]s",aLibn.studentName);
            gotoxy(42,11);scanf(" %[^\n]s",aLibn.studentID);

            strcpy(aLibn.librarianID, fill);
            strcpy(aLibn.librarianName, fill);
            strcpy(currentStudentName, aLibn.studentName);
            strcpy(currentStudentID, aLibn.studentID);

            if(checkAccount(1,aLibn.studentID)==1){
                gotoxy(22,16);printf("REGISTRATION COMPLETE");
                gotoxy(22,17);system("pause");
                addAccount(aLibn);
            }else{
                printToxy(42,16,"Invalid Entry. Duplicate Student ID. Please try again.");
                gotoxy(42,17);system("pause");
                count++; goto fillAgain1;
            }
        }else{
            printf("\n\nERROR. TOO MANY UNSUCCESSFUL ATTEMPS.");
            printf("\nPLEASE TRY AGAIN LATER.\n");
            system("pause"); exit(0);
        }
    system("cls");
}
int registerLibrarian(){
    aREC aLibn;
    HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,06);
    int count=0;
    char userStr[19];
    currentLKey=aLibn.lkey = 1; currentSKey=aLibn.skey = 0;
    strcpy(aLibn.librarianName, adminFillName);
    strcpy(currentLibrarianName, adminFillName);
    strcpy(aLibn.librarianID, adminFillID);
    strcpy(currentLibrarianID, adminFillID);
    strcpy(aLibn.studentID, fill);
    strcpy(aLibn.studentName, fill);

    fillAgain2:
        if(count<3){
            system("cls");
            printToxy(22,2," \xdc\xdc    \xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc     \xdc\xdc         \xdc\xdc      \xdc\xdc\xdc\xdc\xdc     \xdc\xdc     \xdc\xdc  \xdc\xdc  \xdc\xdc    \xdc\xdc");
            printToxy(22,3," \xdc\xdc\xdc   \xdc\xdc  \xdc\xdc      \xdc\xdc     \xdc\xdc        \xdc\xdc\xdc\xdc     \xdc\xdc   \xdc\xdc   \xdc\xdc\xdc   \xdc\xdc\xdc  \xdc\xdc  \xdc\xdc\xdc   \xdc\xdc");
            printToxy(22,4," \xdc\xdc \xdc\xdc \xdc\xdc  \xdc\xdc\xdc\xdc\xdc   \xdc\xdc  \xdc  \xdc\xdc       \xdc\xdc  \xdc\xdc    \xdc\xdc   \xdc\xdc   \xdc\xdc  \xdc  \xdc\xdc  \xdc\xdc  \xdc\xdc \xdc\xdc \xdc\xdc");
            printToxy(22,5," \xdc\xdc  \xdc\xdc\xdc\xdc  \xdc\xdc      \xdc\xdc\xdc   \xdc\xdc\xdc      \xdc\xdc    \xdc\xdc   \xdc\xdc   \xdc\xdc   \xdc\xdc     \xdc\xdc  \xdc\xdc  \xdc\xdc  \xdc\xdc\xdc\xdc");
            printToxy(22,6," \xdc\xdc   \xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc     \xdc\xdc      \xdc\xdc    \xdc\xdc   \xdc\xdc\xdc\xdc\xdc     \xdc\xdc     \xdc\xdc  \xdc\xdc  \xdc\xdc   \xdc\xdc\xdc");
            SetConsoleTextAttribute(h,15); printToxy(35,8," A   D   M   I   N   I   S   T   R   A   T   O   R"); 
            printf("\nEnter Librarian ID to Confirm: \n"); scanf(" %[^\n]",userStr);
            if(strcmp(userStr,aLibn.librarianID)==0){
                printToxy(22,10,"Librarian Name: "); printToxy(38,10,aLibn.librarianName);
                printToxy(22,11,"Librarian ID: "); printToxy(38,11,aLibn.librarianID);

                if(checkAccount(2,aLibn.librarianID)==1){
                    addAccount(aLibn); 
                }
                gotoxy(22,15);printf("REGISTRATION COMPLETE");
                gotoxy(22,16);system("pause");
                
            }else{
                printf("\nERROR.");
                printf("\nCRIDENTIALS DO NOT MATCH.\n");
                system("pause");
                count++; goto fillAgain2;
            }
        }else{
            printf("\n\nERROR. TOO MANY UNSUCCESSFUL ATTEMPS.");
            printf("\nPLEASE TRY AGAIN LATER.\n");
            system("pause"); exit(0);
        }
    system("cls");
}
void userLOGIN(){
    aREC aLibn;
    int count;
    strcpy(aLibn.studentName, currentStudentName);
    aLibn.skey = currentSKey; aLibn.lkey = currentLKey;
    strcpy(aLibn.librarianName, currentLibrarianName);

    if(currentSKey==1 && currentLKey==0){
        count=0;
        enterStudID:
            if(count<3){
                system("cls");
                printf("\nLOG IN");
                printf("\nEnter Student ID: ");
                scanf(" %[^\n]s",aLibn.studentID);
                if(strcmp(aLibn.studentID, currentStudentID)!=0){
                    printf("\nWrong Student ID. Please try again.\n");
                    system("pause"); system("cls");
                    count++; goto enterStudID;
                }else{
                    logs("IN",fill); system("cls");
                }
            }else{
                printf("\n\nERROR. TOO MANY UNSUCCESSFUL ATTEMPS.");
                printf("\nPLEASE TRY AGAIN LATER.\n");
                system("pause"); exit(0);
            }
            
    }else if(currentLKey==1 && currentSKey==0){
        count=0;
        enterLibID:
            if(count<3){
                system("cls");
                printf("\nLOG IN");
                printf("\nEnter Librarian ID: ");
                scanf(" %[^\n]s",aLibn.librarianID);

                if(strcmp(aLibn.librarianID, currentLibrarianID)!=0){
                    printf("\nWrong Librarian ID. Please try again.\n");
                    system("pause"); system("cls");
                    count++; goto enterLibID;
                }else{
                    logs("IN",fill); system("cls");
                }
            }else{
                printf("\n\nERROR. TOO MANY UNSUCCESSFUL ATTEMPS.");
                printf("\nPLEASE TRY AGAIN LATER.\n");
                system("pause"); exit(0);
            }
            
    }else{
        system("cls");
        printf("\nSYSTEM ERROR.\n");
        system("pause"); system("cls");
    }
}


void displayBooks(){
    LIST *p; p=B;
    system("cls");
    printf("| %-8s | %-15s | %-74s | %-82s | %-9s | %-8s |\n",
         "BOOK NUM", "ISBN", "BOOK TITLE", "BOOK AUTHOR", "PUB. YEAR", "QUANTITY");

    while (p != NULL) {
        printf("| %-8d | %-15s | %-74s | %-82s | %-9d | %-8d |\n",
            p->bLib.bookNum, p->bLib.ISBN, p->bLib.bookTitle, 
            p->bLib.bookAuthor, p->bLib.publicationYear, p->bLib.bookQuant);
        p = p->next;
    }
}
void displayCurrentBook(bREC *x){
    printf("\n| %-8s | %-15s | %-74s | %-82s | %-9s | %-8s |\n",
            "BOOK NUM", "ISBN", "BOOK TITLE", "BOOK AUTHOR", "PUB. YEAR", "QUANTITY");
        
    printf("| %-8d | %-15s | %-74s | %-82s | %-9d | %-8d |\n\n",
        x->bookNum, x->ISBN, x->bookTitle,
        x->bookAuthor, x->publicationYear, x->bookQuant);
}
void displayLogs(){
    lREC rLogsn;
    int count=0;
    char userFilename[50];
    char searchFile[50];
    EnterDateAgainLogs:
        if(count<3){
            system("cls");
            displayDirectoryContent();
            printf("\n\nENTER DATE (YYYY-MM-DD) !DON'T INCLUDE THE .csv! : ");
            scanf(" %[^\n]s", userFilename);
            snprintf(searchFile, sizeof(searchFile), "%s\\%s.csv", LMSLogs, userFilename);
            FILE *fp;
            fp=fopen(searchFile, "r");
            if(fp==NULL){
                printf("\nERROR 404. FILE (%s) NOT FOUND.\n",userFilename);
                system("pause");
            }else{
                printf("| %-11s | %-11s | %-50s | %-10s | %-10s |\n",
                        "DATE", "TIME", "NAME", "STATUS", "ITEM");
                while(fp!=NULL){
                    fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                            rLogsn.date, rLogsn.time, rLogsn.name,
                            rLogsn.STATUS, rLogsn.ITEM);
                    
                    printf("| %-11s | %-11s | %-50s | %-10s | %-10s |\n",
                            rLogsn.date, rLogsn.time, rLogsn.name,
                            rLogsn.STATUS, rLogsn.ITEM);
                }
                printf("\n\n"); system("pause");
            }
        }else{
            printf("\nTOO MANY FAILED ATTEMPTS.");
            printf("\nPLEASE TRY AGAIN LATER.\n");
            system("pause");
        }
    system("cls");
}
void displayDirectoryContent(){
    struct dirent *direct;
    DIR *directory = opendir(LMSLogs);
    if(directory == NULL){
        printf("\nERROR 404. DIRECTORY NOT FOUND.\n");
        system("pause");
    }else{
        printf("\nLOG DATES:\n");
        while((direct = readdir(directory)) != NULL){
            printf("\n-> %s",direct->d_name);
        }
    } closedir(directory);
}
int menu(int x){
    int i, userNum;
    HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    if(x==1){//student
        printToxy(22,2,"   \xdc\xdc\xdc\xdc\xdc    \xdc\xdc   \xdc\xdc\xdc\xdc\xdc\xdc\xdc \xdc\xdc\xdc\xdc\xdc\xdc   \xdc\xdc\xdc\xdc\xdc    \xdc\xdc\xdc\xdc\xdc   \xdc\xdc\xdc\xdc\xdc\xdc\xdc   \xdc\xdc    \xdc\xdc                                          ");
        printToxy(22,3," \xdc\xdc        \xdc\xdc\xdc\xdc    \xdc\xdc\xdc   \xdc\xdc     \xdc\xdc        \xdc\xdc   \xdc\xdc  \xdc\xdc    \xdc\xdc   \xdc\xdc  \xdc\xdc                                              ");
        printToxy(22,4," \xdc\xdc       \xdc\xdc  \xdc\xdc   \xdc\xdc\xdc   \xdc\xdc\xdc\xdc\xdc  \xdc\xdc   \xdc\xdc\xdc  \xdc\xdc   \xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc\xdc      \xdc\xdc                                  ");
        printToxy(22,5," \xdc\xdc      \xdc\xdc    \xdc\xdc  \xdc\xdc\xdc   \xdc\xdc     \xdc\xdc    \xdc\xdc  \xdc\xdc   \xdc\xdc  \xdc\xdc  \xdc\xdc       \xdc\xdc                                  ");
        printToxy(22,6,"   \xdc\xdc\xdc\xdc\xdc \xdc\xdc    \xdc\xdc  \xdc\xdc\xdc   \xdc\xdc\xdc\xdc\xdc\xdc   \xdc\xdc\xdc\xdc\xdc    \xdc\xdc\xdc\xdc\xdc   \xdc\xdc   \xdc\xdc      \xdc\xdc                                                      ");
        SetConsoleTextAttribute(h,15);
        gotoxy(12,10); for(i=0;i<19;i++) printf("%c",220); gotoxy(12,14); for(i=0;i<19;i++) printf("%c",220); printToxy(17,16,"[1]");
        for(i=0;i<4;i++){gotoxy(12,11+i);printf("%c",219);} for(i=0;i<4;i++){gotoxy(30,11+i);printf("%c",219);} printToxy(16,12,"BORROW BOOK");
        gotoxy(45,10); for(i=0;i<19;i++) printf("%c",220); gotoxy(45,14); for(i=0;i<19;i++) printf("%c",220); printToxy(53,16,"[2]");
        for(i=0;i<4;i++){gotoxy(45,11+i);printf("%c",219);} for(i=0;i<4;i++){gotoxy(63,11+i);printf("%c",219);} printToxy(49,12,"RETURN BOOK");
        gotoxy(78,10); for(i=0;i<20;i++) printf("%c",220); gotoxy(78,14); for(i=0;i<19;i++) printf("%c",220); printToxy(87,16,"[3]");
        for(i=0;i<4;i++){gotoxy(78,11+i);printf("%c",219);} for(i=0;i<4;i++){gotoxy(97,11+i);printf("%c",219);} printToxy(86,12,"EXIT");
        SetConsoleTextAttribute(h,05); gotoxy(5,18); for(int i=0;i<101;i++) printf("%c",223);
        SetConsoleTextAttribute(h,06); printToxy(33,8,"S       T       U       D       E       N       T ");
    }else{//librarian
        printToxy(22,2,"   \xdc\xdc\xdc\xdc\xdc    \xdc\xdc   \xdc\xdc\xdc\xdc\xdc\xdc\xdc \xdc\xdc\xdc\xdc\xdc\xdc   \xdc\xdc\xdc\xdc\xdc    \xdc\xdc\xdc\xdc\xdc   \xdc\xdc\xdc\xdc\xdc\xdc\xdc   \xdc\xdc    \xdc\xdc                                          ");
        printToxy(22,3," \xdc\xdc        \xdc\xdc\xdc\xdc    \xdc\xdc\xdc   \xdc\xdc     \xdc\xdc        \xdc\xdc   \xdc\xdc  \xdc\xdc    \xdc\xdc   \xdc\xdc  \xdc\xdc                                              ");
        printToxy(22,4," \xdc\xdc       \xdc\xdc  \xdc\xdc   \xdc\xdc\xdc   \xdc\xdc\xdc\xdc\xdc  \xdc\xdc   \xdc\xdc\xdc  \xdc\xdc   \xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc\xdc      \xdc\xdc                                  ");
        printToxy(22,5," \xdc\xdc      \xdc\xdc    \xdc\xdc  \xdc\xdc\xdc   \xdc\xdc     \xdc\xdc    \xdc\xdc  \xdc\xdc   \xdc\xdc  \xdc\xdc  \xdc\xdc       \xdc\xdc                                  ");
        printToxy(22,6,"   \xdc\xdc\xdc\xdc\xdc \xdc\xdc    \xdc\xdc  \xdc\xdc\xdc   \xdc\xdc\xdc\xdc\xdc\xdc   \xdc\xdc\xdc\xdc\xdc    \xdc\xdc\xdc\xdc\xdc   \xdc\xdc   \xdc\xdc      \xdc\xdc                                                      ");
        SetConsoleTextAttribute(h,15);
        gotoxy(12,10); for(i=0;i<14;i++) printf("%c",220); gotoxy(12,14); for(i=0;i<14;i++) printf("%c",220); printToxy(17,16,"[1]");
        for(i=0;i<4;i++){gotoxy(12,11+i);printf("%c",219);} for(i=0;i<4;i++){gotoxy(25,11+i);printf("%c",219);} printToxy(15,12,"ADD BOOK");
        gotoxy(35,10); for(i=0;i<15;i++) printf("%c",220); gotoxy(35,14); for(i=0;i<15;i++) printf("%c",220); printToxy(41,16,"[2]");
        for(i=0;i<4;i++){gotoxy(35,11+i);printf("%c",219);} for(i=0;i<4;i++){gotoxy(49,11+i);printf("%c",219);} printToxy(38,12,"EDIT BOOK");
        gotoxy(59,10); for(i=0;i<17;i++) printf("%c",220); gotoxy(59,14); for(i=0;i<17;i++) printf("%c",220); printToxy(66,16,"[3]");
        for(i=0;i<4;i++){gotoxy(59,11+i);printf("%c",219);} for(i=0;i<4;i++){gotoxy(75,11+i);printf("%c",219);} printToxy(62,12,"REMOVE BOOK");
        gotoxy(85,10); for(i=0;i<14;i++) printf("%c",220); gotoxy(85,14); for(i=0;i<14;i++) printf("%c",220); printToxy(91,16,"[4]");
        for(i=0;i<4;i++){gotoxy(85,11+i);printf("%c",219);} for(i=0;i<4;i++){gotoxy(98,11+i);printf("%c",219);} printToxy(90,12,"BOOK REQUESTS");
        printf("\t[5] DISPLAY BOOKS"); 
        printf("\t[6] DISPLAY LOGS"); 
        printf("\t[7] EXIT"); 
        SetConsoleTextAttribute(h,05); gotoxy(5,18); for(int i=0;i<101;i++) printf("%c",223);
        SetConsoleTextAttribute(h,06); printToxy(33,8,"L     I     B     R     A     R     I     A     N");
    }
    SetConsoleTextAttribute(h,15);printToxy(5,20,"Enter choice: ");
    scanf("%d",&userNum);
    return userNum;
}


void borrowBook(int x){
    int count, borrow;
    char temp[100];
    LIST *p, *q;
    q=p=B;
    while(p!=NULL && x!=p->bLib.bookNum){
        q=p;
        p=p->next;
    }
    if(p==NULL){
        printf("\nError 404. Book Number: %d not found.\n",x);
        system("pause"); system("cls");
    }else{
        //get current date and time
        time_t currentTime;
        struct tm *localTime;
        currentTime = time(NULL);
        localTime = localtime(&currentTime);

        displayCurrentBook(p);
        
        if(verifyAccount(1)==1){
            strcpy(temp,p->bLib.bookTitle);
            count=0;
            EnterBookCopyAgain:
                if(count<3){
                    printf("\nHow many copies to be borrowed: ");
                    scanf("%d", &borrow);
                    if(borrow<p->bLib.bookQuant && borrow>0){
                        p->bLib.bookQuant -= borrow;

                        //save the borrowed book to the file and the date borrwed
                        FILE *fp;
                        char fileName[50];
                        snprintf(fileName, sizeof(fileName), "%s\\borrowedBooks.txt", LMSFlashDrive);
                        fp=fopen(fileName,"a+");
                        if(fp!=NULL){
                            fprintf(fp,"%d,%s,%s,%s,%d,%d,%04d,%02d,%02d\n",
                                    p->bLib.bookNum,p->bLib.ISBN, p->bLib.bookTitle, 
                                    p->bLib.bookAuthor, p->bLib.publicationYear, borrow,
                                    localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday);
                        }else{
                            printf("\nSystem Error. cant save into file.\n");
                            system("pause");system("cls");
                        }fclose(fp);
                        saveBooks(); 
                        logs("Borrowed Book", temp);
                        printf("\nYou successfully borrowed (%s).\n", temp);
                        system("pause");
                    }else{
                        printf("\nINVALID INPUT.");
                        printf("\nPLEASE TRY AGAIN.\n");
                        system("pause");
                        count++; goto EnterBookCopyAgain;
                    }
                }else{
                    printf("\nTOO MANY FAILED ATTEMPTS.");
                    printf("\nPLEASE TRY AGAIN LATER.\n");
                    system("pause");
                }
        }else{
            printf("\nTransaction Cancelled. Your input does not match to your cridentials.\n");
            system("pause");system("cls");
        }
    }
}
void returnbook(){
    FILE *fp;
    bREC bLibn;
    LIST *p, *q;
    q=p=B;
    int borrowYear, borrowMonth, borrowDay, penalty;
    char fileName[50];
    snprintf(fileName, sizeof(fileName), "%s\\borrowedBooks.txt", LMSFlashDrive);
    fp=fopen(fileName,"r");
    if(fp==NULL){
        printf("\nERROR. No Books to Return.\n");
        system("pause"); system("cls");
    }else{
        //get current date and time
        time_t currentTime;
        struct tm *localTime;
        currentTime = time(NULL);
        localTime = localtime(&currentTime);
        int currYear = localTime->tm_year + 1900;
        int currMonth = localTime->tm_mon + 1;
        int currDay = localTime->tm_mday;

        while(!feof(fp)){
            fscanf(fp,"%d,%[^,],%[^,],%[^,],%d,%d,%d,%d,%d\n",
                    &bLibn.bookNum, bLibn.ISBN, bLibn.bookTitle, 
                    bLibn.bookAuthor, &bLibn.publicationYear, &bLibn.bookQuant,
                    &borrowYear, &borrowMonth, &borrowDay);

            //check penalty 
            //[kayo na dito mga fre HAHAHAHAHA lagyan nyo banko para pwede mag withdraw si student HAHAHAHAHAHA]
            if(borrowYear > currYear){
                //penalty here
                displayCurrentBook(&bLibn);
                printf("\nPENALTY:");
                printf("\nP 1,000 * 'x' NUMBER OF YEAR(S) * 'x' NUMBER OF BOOK COPIES");
                penalty = currYear - borrowYear;
                printf("\n\nNUMBER OF YEAR YOU HAVE HAD THE BOOK: %d",penalty);
                printf("\nCOPIES OF BOOKS THAT YOU BORROWED: %d",bLibn.bookQuant);
                penalty *= 1000; penalty *= bLibn.bookQuant;
                printf("\n\nPLEASE SETTLE THE AMOUNT OF (P %d) IMMEDIATELY.",penalty);

            }else if(borrowMonth > currMonth){
                //penalty here
            }else if((currDay-borrowDay) >= 3){
                //penalty here
            }else{
                //no penalty
            }

            //return the book to the Database
            while(p!=NULL && p->bLib.bookNum!=bLibn.bookNum){
                q=p;
                p=p->next;
            }
            if(p==NULL){
                addBooks(bLibn);
                logs("Retured Book",bLibn.bookTitle);
                printf("\nBook (%s) successfully retured.\n",bLibn.bookTitle);
            }else{
                p->bLib.bookQuant += bLibn.bookQuant;
                printf("\nBook (%s) successfully retured.\n",bLibn.bookTitle);
            }
        }fclose(fp);
        saveBooks();
        remove(fileName);
        system("pause"); system("cls");
    }
}

void insertExistingBook(){
    int userNum;
    system("cls");
    displayBooks();
    printf("\n\nEnter Book Number: ");
    scanf("%d", &userNum);

    LIST *p, *q;
    q=p=B;
    while(p!=NULL && userNum!=p->bLib.bookNum){
        q=p;
        p=p->next;
    }
    if(p==NULL){
        printf("\nMODIFICATION UNSUCCESSFUL.");
        printf("\nINVALID BOOK NUMBER.\n");
        system("pause");
    }else{
        printf("\nBOOK SELECTED:\n");
        displayCurrentBook(&p);
        printf("\nEnter books copies to be inserted: ");
        scanf("%d", &userNum);
        if(userNum<=0){
            printf("\nERROR.");
            printf("\nINVALID QUANTITY OF BOOKS.\n");
            system("pause");
        }else{
            p->bLib.bookQuant += userNum;
            printf("\nMODIFICATION SUCCESSFUL.\n");
            displayCurrentBook(&p);
            system("pause");
            displayBooks();
            system("pause");
            saveBooks(); 
            logs("Insert Existing Book",p->bLib.bookTitle);
        }
    }
}
void insertNewBook(){
    bREC bBooks;
    int userNum, count;
    char userISBN[14];
    long long firstNum, randomNum;
    insertNewBookAgain:
    if(count<3){
            system("cls");

            bBooks.bookNum = getBookNumber();
            printf("\nBook ID: %d",bBooks.bookNum);

            printf("\nInput book title: ");
            scanf(" %[^\n]s",bBooks.bookTitle);

            printf("\nEnter Book Quantity: ");
            scanf("%d", &bBooks.bookQuant);

            printf("\nInput book author: ");
            scanf(" %[^\n]s",bBooks.bookAuthor);
            
            printf("\nInput publication year: ");
            scanf("%d",&bBooks.publicationYear);

        printf("\nDo you know the books's ISBN?");
        printf("\n[1] YES");
        printf("\n[2] NO");
        printf("\n-> ");
        scanf("%d",&userNum);
        if(userNum==1){
            if(bBooks.publicationYear>0 && bBooks.publicationYear<=2006){
                printf("\n\nEnter VALID 10-digit ISBN: ");
                scanf(" %[^\n]s",userISBN);
                int len = strlen(userISBN);
                if(len == 10){
                    if(checkISBN(userISBN,10)==1){
                        strcpy(bBooks.ISBN,userISBN);
                    }else{
                        printf("\nMODIFICATION UNSUCCESSFUL.");
                        printf("\nINVALID ISBN.\n");
                        system("pause");
                    }
                }else{
                    printf("\nMODIFICATION UNSUCCESSFUL.");
                    printf("\nINVALID ISBN.\n");
                    system("pause");
                }
            }else if(bBooks.publicationYear>2006){
                printf("\n\nEnter VALID 13-digit ISBN: ");
                scanf(" %[^\n]s",userISBN);
                int len = strlen(userISBN);
                if(len == 13){
                    if(checkISBN(userISBN,13)==1){
                        strcpy(bBooks.ISBN,userISBN);
                    }else{
                        printf("\nMODIFICATION UNSUCCESSFUL.");
                        printf("\nINVALID ISBN.\n");
                        system("pause");
                    }
                }else{
                    printf("\nMODIFICATION UNSUCCESSFUL.");
                    printf("\nINVALID ISBN.\n");
                    system("pause");
                }
            }else{
                printf("\nMODIFICATION UNSUCCESSFUL.");
                printf("\nINVALID PUBLICATION YEAR.\n");
                system("pause");
                goto insertNewBookAgain;
            }                
        }else if(userNum==2){ 
            //will generate valid ISBN base on publication year
            if(bBooks.publicationYear>0 && bBooks.publicationYear<=2006){
                char generatedISBN[11];
                do{
                    do{
                        firstNum = rand() % 10;
                    }while(firstNum<=0);

                    do{
                        randomNum = firstNum*1000000000 + rand() % 100000000 + 999999999;
                    }while(randomNum<=0);

                    //convert int to string
                    sprintf(generatedISBN, "%lld", randomNum);
                }while(checkISBN(generatedISBN,10)==2);
                strcpy(bBooks.ISBN,generatedISBN);

            }else if(bBooks.publicationYear>2006){
                char generatedISBN[14];
                do{
                    do{
                        firstNum = rand() % 10;
                    }while(firstNum<=0);

                    do{
                        randomNum = firstNum*1000000000000 + rand() % 100000000000 + 999999999999;
                    }while(randomNum<=0);

                    //convert int to string
                    sprintf(generatedISBN, "%lld", randomNum);
                }while(checkISBN(generatedISBN,13)==2);
                strcpy(bBooks.ISBN,generatedISBN);

            }else{
                printf("\nMODIFICATION UNSUCCESSFUL.");
                printf("\nINVALID PUBLICATION YEAR.\n");
                system("pause");
                goto insertNewBookAgain;
            }  
        }else{
            printf("\nMODIFICATION UNSUCCESSFUL.");
            printf("\nINVALID INPUT.\n");
            system("pause");
            goto insertNewBookAgain;
        }

        if(checkBooks(&bBooks)==1){
            if(verifyAccount(2)==1){
                addBooks(bBooks);
                saveBooks();
                logs("Add Book",bBooks.bookTitle);
                displayBooks();
                printf("\n\nMODIFICATION SUCCESSFUL.\n");
                system("pause");
            }else{
                displayBooks();
                printf("\n\nMODIFICATION UNSUCCESSFUL.\n");
                system("pause");
            }
        }else{
            system("cls");
        }
    }
}
void editBooks(){
    int ch=0, a, x;
    char userISBN[14];
    LIST *p, *q;
    bREC bBooks;

    printf("\n\nInput book ID to be edited: ");
    scanf("%d",&x);

    if(verifyAccount(2)==1){
        q=p=B;
        while(p!=NULL && x!=p->bLib.bookNum){
            q=p;
            p=p->next;
        }
        if (p==NULL){
            printf("Book not found!\n");
            printf("Wrong book ID or book does not exist.\n");
            system("pause"); system("cls");
        }else{
            while(ch!=5){
                system("cls");
                printf("\nBook ID: %d\n",p->bLib.bookNum);
                printf("ISBN: %s\n",p->bLib.ISBN);
                printf("Book title: %s\n",p->bLib.bookTitle);
                printf("Book author: %s\n",p->bLib.bookAuthor);
                printf("Book publication year: %d\n",p->bLib.publicationYear);
                printf("Book Quantity: %d", p->bLib.bookQuant);
                printf("\nCHANGE BOOK DETAILS\n");
                printf("[1] Book title\n");
                printf("[2] Book author\n");
                printf("[3] Book publication year\n");
                printf("[4] Book quantity\n");
                printf("[5] Back\n");
                printf("\nSelect the detail to edit: ");
                scanf("%d",&ch);
                switch(ch){
                    case 1: printf("\nInput NEW book title: ");
                            scanf(" %[^\n]s",p->bLib.bookTitle);
                            break;
                    case 2: printf("\nInput NEW book author: ");
                            scanf(" %[^\n]s",p->bLib.bookAuthor);
                            break;
                    case 3: printf("\nInput NEW publication year: ");
                            scanf("%d",&p->bLib.publicationYear);
                            break;
                    case 4: printf("\nInput NEW bok quantity: ");
                            scanf("%d",&p->bLib.bookQuant);
                            break;
                    case 5: printf("\n\nBook was succesfully edited.\n");
                            system("pause"); system("cls");
                            break;
                    default: printf("\n\nSelect 1-5 only.");
                            break;
                }
            }
            saveBooks();
            logs("Edit Book",p->bLib.bookTitle);
        }
        displayBooks();
        printf("\n\nMODIFICATION SUCCESSFUL.\n");
        system("pause");
    }else{
        system("cls");
        displayBooks();
        printf("\n\nMODIFICATION UNSUCCESSFUL.\n");
        system("pause");
    }
}

void removeAcopy(){
    int x, count;
    LIST *p, *q;

    printf("\n\nInput book ID: ");
    scanf("%d",&x);

    if(verifyAccount(2)==1){
        q=p=B;
        while(p!=NULL && p->bLib.bookNum!=x){
                q=p;
                p=p->next;
        }
        if (p==NULL){
            printf("ERROR 404. BOOK NOT FOUND.\n");
            printf("WRONG BOOK ID OR BOOK DOES NOT EXIST.\n");
            system("pause"); system("cls");
        }else{
            EnterBookQuantityAgain:
                printf("\nBOOK SELECTED:\n");
                displayCurrentBook(&p);
                printf("\nEnter book copies to be removed: ");
                scanf("%d", &x);
                if(x>0 && x<p->bLib.bookQuant){
                    p->bLib.bookQuant -= x;
                    printf("\nMODIFICATION SUCCESSFUL.\n");
                    displayCurrentBook(&p);
                    system("pause"); system("cls");
                    displayBooks();
                    system("pause");
                    saveBooks();
                    logs("Remove Book Copy", p->bLib.bookTitle);
                }else{
                    printf("\nERROR.");
                    printf("\nINVALID QUANTITY OF BOOKS.\n");
                    system("pause");
                    count++; goto EnterBookQuantityAgain;
                }
        }
    }else{
        printf("\nMODIFICATION UNSUCCESSFUL.\n");
        system("pause");
    }
}
void removeBooks(){
    int x;
    char temp[100];
    LIST *p, *q;

    printf("\n\nInput book ID to be removed: ");
    scanf("%d",&x);

    printf("\n\n!WARNING! THIS WILL REMOVE ALL THE COPY OF THE BOOKS.\n");

    if(verifyAccount(2)==1){
        q=p=B;
        while(p!=NULL && p->bLib.bookNum!=x){
                q=p;
                p=p->next;
        }
        if (p==NULL){
            printf("ERROR 404. BOOK NOT FOUND.\n");
            printf("WRONG BOOK ID OR BOOK DOES NOT EXIST.\n");
            system("pause"); system("cls");
        }else{
            strcpy(temp,p->bLib.bookTitle);
            if (p==B){
                B=p->next;
            }else{
                q->next=p->next;
            }free(p);
            saveBooks();
            logs("Removed Book",temp);
            printf("The book %s was successfully removed.\n", temp);
            system("pause");
        }
    }else{
        printf("\nMODIFICATION UNSUCCESSFUL.\n");
        system("pause");
    }
}
void bookRequests(){
    int userNum,x;
    FILE *fp;
    bREC bRequest;
    LIST *p, *q; 
    char fileName[50];
    snprintf(fileName, sizeof(fileName), "%s\\BookRequest.txt", LMSFlashDrive);
    fp=fopen(fileName,"r");
    if(fp==NULL){
        printf("\nNO BOOK REQUESTS YET.");
        system("pause");
    }else{
        while(!feof(fp)){
            fscanf(fp,"%d,%[^,],%[^,],%[^,],%d,%d\n",
                    &bRequest.bookNum, bRequest.ISBN, bRequest.bookTitle, 
                    bRequest.bookAuthor, &bRequest.publicationYear, &bRequest.bookQuant);
           addBookRequests(bRequest);
        }

        while(x!=3){
            system("cls");
            displayBooks();
            /*printf("| %-8s | %-15s | %-74s | %-82s | %-9s | %-8s |\n",
                "BOOK NUM", "ISBN", "BOOK TITLE", "BOOK AUTHOR", "PUB. YEAR", "QUANTITY");

            q=p=C;
            while (p != NULL) {
                printf("| %-8d | %-15s | %-74s | %-82s | %-9d | %-8s |\n\n",
                    p->bLib.bookNum, p->bLib.ISBN, p->bLib.bookTitle, 
                    p->bLib.bookAuthor, p->bLib.publicationYear, p->bLib.bookQuant);
                p = p->next;
            }*/

            printf("\n\nSELECT CATEGORY\n");
            printf("\n[1] APPROVED BOOK\n");
            printf("\n[2] DISAPPROVED BOOK\n");
            printf("\n[3] EXIT\n");
            scanf("%d", &x);

            switch(x){
                case 1: printf("\nEnter Book ID: \n");
                        scanf("%d", &userNum);

                        q=p=C;
                        while(p!=NULL && userNum!=p->bLib.bookNum){
                            q=p;
                            p=p->next;
                        }
                        if(p==NULL){
                            printf("\nError 404. Book Number: %d not found.\n",userNum);
                            system("pause"); system("cls");
                        }else{
                            if(verifyAccount(2)==1){
                                bRequest.bookNum = p->bLib.bookNum;
                                strcpy(bRequest.ISBN,p->bLib.ISBN);
                                strcpy(bRequest.bookTitle,p->bLib.bookTitle);
                                strcpy(bRequest.bookAuthor,p->bLib.bookAuthor);
                                bRequest.publicationYear = p->bLib.publicationYear;
                                bRequest.bookQuant = p->bLib.bookQuant;
                                addBooks(bRequest);
                                saveBooks();
                                logs("Approved Book", bRequest.bookTitle);

                                printf("\nBOOK (%s) APPROVED.\n",bRequest.bookTitle);
                                system("pause");
                            }else{
                                printf("\nMODIFICATION UNSUCCESSFUL.");
                                printf("\nWRONG CRIDENTIALS.\n");
                                system("pause");
                            }
                        }
                        break;
                case 2: printf("\nEnter Book ID: \n");
                        scanf("%d", &userNum);

                        q=p=C;
                        while(p!=NULL && userNum!=p->bLib.bookNum){
                            q=p;
                            p=p->next;
                        }
                        if(p==NULL){
                            printf("\nError 404. Book Number: %d not found.\n",userNum);
                            system("pause"); system("cls");
                        }else{
                            if(verifyAccount(2)==1){
                                strcpy(bRequest.bookTitle,p->bLib.bookTitle);
                                if(p==C){
                                    C = p->next;
                                }else{
                                    q->next = p->next;
                                }free(p);
                                logs("Disapproved Book", bRequest.bookTitle);

                                printf("\nBOOK (%s) DISAPPROVED.\n",bRequest.bookTitle);
                                system("pause");
                            }else{
                                printf("\nMODIFICATION UNSUCCESSFUL.");
                                printf("\nWRONG CRIDENTIALS.\n");
                                system("pause");
                            }
                        }
                        break;
                case 3: break;
                default: printf("\nINVALID INPUT\n");
                         system("pause");
                         break;
            }
        }
    }
}


int checkAccount(int x,char str[31]){ // to avoid same IDs / multiple admin accounts
    LIST *p, *q;
    q=p=A;

    switch(x){
        case 1: while(p!=NULL && strcmp(str,p->aLib.studentID)!=0){
                    q=p; p=p->next;
                }if(p==NULL){
                    return 1;
                }else{
                    return 2;
                }break;
        case 2: while(p!=NULL && strcmp(str,p->aLib.librarianID)!=0){
                    q=p; p=p->next;
                }if(p==NULL){
                    return 1;
                }else{
                    return 2;
                }break;
    }
}
int verifyAccount(int x){
    char userInput[31];
    if(x==1){ //student
        printf("\nPlease Enter Your Student ID to confirm: ");
        scanf(" %[^\n]s",userInput);
        if(strcmp(userInput,currentStudentID)==0){
            return 1;
        }else{
            return 2;
        }
    }else{ //librarian
        printf("\nPlease Enter Librarian ID to confirm: ");
        scanf(" %[^\n]s",userInput);
        if(strcmp(userInput,adminFillID)==0){
            return 1;
        }else{
            return 2;
        }
    }
}
int checkBooks(bREC *x){
    LIST *p, *q;
    q=p=B;
    
    while(p!=NULL && strcasecmp(x->bookTitle,p->bLib.bookTitle)!=0){
        q=p;
        p=p->next;
    }
    if(p==NULL){
        return 1;
    }else if(strcasecmp(x->bookAuthor,p->bLib.bookAuthor)!=0){
        return 1;
    }else{
        printf("\n\nMODIFICATION UNSUCCESSFUL.");
        printf("\nSAME BOOK TITLE AND AUTHOR IS NOT ALLOWED.\n");
        displayCurrentBook(&p);
        printf("\n"); system("pause");
        return 2;
    }
}
int checkISBN(char *ISBN, int x){
    LIST *p, *q;
    q=p=B;
    int sum=0;
    if(x==10){ 
        //check 10 digit number
        int len = strlen(ISBN);
        if(len != 10){
            return 2;
        }
        for(int i=0; i<10; i++){
            int digit = ISBN[i] - '0';
            if(digit<0 || digit>9){
                return 2;
            } 
            sum += (digit *(10-i));
        }
        if(sum%11 == 0){
            // check if ISBN is existing or not
            while(p!=NULL && strcmp(ISBN,p->bLib.ISBN)!=0){
                q=p;
                p=p->next;
            }
            if(p==NULL){
                return 1;
            }else{
                return 2;
            }
        }else{
            return 2;
        }
    }else if(x==13){ 
        //check 13 digit number
        int len = strlen(ISBN);
            if(len != 13){
                return 2;
            }
        for(int i=0; i<13; i++){
            int digit = ISBN[i] - '0';
            if(digit<0 || digit>9){
                return 2;
            } 
            sum += (digit *(10-i));
        }
        if(sum%11 == 0){
            // check if ISBN is existing or not
            while(p!=NULL && strcmp(ISBN,p->bLib.ISBN)!=0){
                q=p;
                p=p->next;
            }
            if(p==NULL){
                return 1;
            }else{
                return 2;
            }
        }else{
            return 2;
        }
    }
}
int getBookNumber(){
    int randBookNum;
    LIST *p, *q;
    do{
        do{
            randBookNum = rand() % 10 + 99999999;
        }while(randBookNum<=0);

        q=p=B;
        while(p!=NULL && randBookNum!=p->bLib.bookNum){
            q=p;
            p=p->next;
        }
    }while(p!=NULL);
    return randBookNum;
}


void decrypt(int x, char *str, int *num){
    int i=0;
    if(x==1){ 
        while(str[i] != '\0'){
            str[i] -= KEY;
            i++;
        }
    }else if(x==2){ 
        *num ^= KEY;
    }
}
void encrypt(int x,char *str,int *num){
    int i=0;
    if(x==1){ //char
        while(str[i] != '\0'){
            str[i] += KEY;
            i++;
        }
    }else if(x==2){
        *num ^= KEY;
    }
}


void saveBooks(){
    FILE *fp;
    LIST *p; p=B;

    char fileName[50];
    snprintf(fileName, sizeof(fileName), "%s\\Books.txt", LMSFolderDB);

    fp=fopen(fileName, "w+");
    if(fp==NULL){
        printf("Error 404. File not found.\n");
        system("pause");
    }else{
        while(p!=NULL){
            encrypt(2,"",&p->bLib.bookNum);
            encrypt(1,p->bLib.ISBN,0);
            encrypt(1,p->bLib.bookTitle,0);
            encrypt(1,p->bLib.bookAuthor,0);
            encrypt(2,"",&p->bLib.publicationYear);
            encrypt(2,"",&p->bLib.bookQuant);

            fprintf(fp,"%d,%s,%s,%s,%d,%d\n",
                    p->bLib.bookNum,p->bLib.ISBN,p->bLib.bookTitle,
                    p->bLib.bookAuthor,p->bLib.publicationYear,p->bLib.bookQuant);

            decrypt(2,"",&p->bLib.bookNum);
            decrypt(1,p->bLib.ISBN,0);
            decrypt(1,p->bLib.bookTitle,0);
            decrypt(1,p->bLib.bookAuthor,0);
            decrypt(2,"",&p->bLib.publicationYear);
            decrypt(2,"",&p->bLib.bookQuant);

            p=p->next;
        }fclose(fp);
    }
}
void saveAccounts(){
    FILE *fp;
    LIST *p; p=A;

    char fileName[50];
    snprintf(fileName, sizeof(fileName), "%s\\Accounts.csv", LMSFolderDB);

    fp=fopen(fileName, "w+");
    if(fp==NULL){
        printf("Error 404. File not found.\n");
        system("pause");
    }else{
        while(p!=NULL){
            encrypt(1,p->aLib.studentID,0); 
            encrypt(1,p->aLib.studentName,0); 
            encrypt(1,p->aLib.librarianID,0); 
            encrypt(1,p->aLib.librarianName,0); 
            encrypt(2,"",&p->aLib.skey);
            encrypt(2,"",&p->aLib.lkey);

            fprintf(fp,"%s,%s,%s,%s,%d,%d\n",
                    p->aLib.studentID,p->aLib.librarianID,p->aLib.studentName,
                    p->aLib.librarianName,p->aLib.skey,p->aLib.lkey);
            
            decrypt(1,p->aLib.studentID,0); 
            decrypt(1,p->aLib.studentName,0); 
            decrypt(1,p->aLib.librarianID,0); 
            decrypt(1,p->aLib.librarianName,0); 
            decrypt(2,"",&p->aLib.skey);
            decrypt(2,"",&p->aLib.lkey);

            p=p->next;
        }fclose(fp);
    }
}
void saveAccountsFD(){
    FILE *fp;
    LIST *p, *q;
    q=p=A;
    if(currentSKey==1 && currentLKey==0){
        while(p!=NULL && strcmp(currentStudentID, p->aLib.studentID)!=0){
            q=p;
            p=p->next;
        }
    }else if(currentSKey==0 && currentLKey==1){
        while(p!=NULL && strcmp(currentLibrarianID, p->aLib.librarianID)!=0){
            q=p;
            p=p->next;
        }
    }else{
        system("cls");
        printf("\nSystem Error. cant save into file.\n");
        system("pause");system("cls");
    }

    encrypt(1,p->aLib.studentID,0); 
    encrypt(1,p->aLib.studentName,0); 
    encrypt(1,p->aLib.librarianID,0); 
    encrypt(1,p->aLib.librarianName,0); 
    encrypt(2,"",&p->aLib.skey);
    encrypt(2,"",&p->aLib.lkey);

    char fileName[50];
    snprintf(fileName, sizeof(fileName), "%s\\userDetails.csv", LMSFlashDrive);
    fp=fopen(fileName, "w+");
    if (fp==NULL){
        printf("\nError 404. File not found.\n");
        system("pause");system("cls");
    }else{
        fprintf(fp,"%s,%s,%s,%s,%d,%d\n",
                p->aLib.studentID,p->aLib.librarianID,p->aLib.studentName,
                p->aLib.librarianName,p->aLib.skey,p->aLib.lkey);
    }
    fclose(fp);

    decrypt(1,p->aLib.studentID,0); 
    decrypt(1,p->aLib.studentName,0); 
    decrypt(1,p->aLib.librarianID,0); 
    decrypt(1,p->aLib.librarianName,0); 
    decrypt(2,"",&p->aLib.skey);
    decrypt(2,"",&p->aLib.lkey);
}
void logs(char status[100], char item[100]){
    FILE* fp;
    time_t currentTime;
    struct tm *localTime;

    //get current date and time
    currentTime = time(NULL);
    localTime = localtime(&currentTime);

    //generate the file path and file format
    char logsFilename[11];
    strftime(logsFilename, sizeof(logsFilename), "%Y-%m-%d", localTime);

    char logsFilePath[50];
    snprintf(logsFilePath, sizeof(logsFilePath), "%s\\%s.csv",LMSLogs,logsFilename);

    fp=fopen(logsFilePath,"a+");

    if(currentSKey==1 && currentLKey==0){
        fprintf(fp,"%04d-%02d-%02d,%02d:%02d:%02d,%s,%s,%s\n",
            localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday,
            localTime->tm_hour, localTime->tm_min, localTime->tm_sec, 
            currentStudentName, status, item);
    }else if(currentSKey==0 && currentLKey==1){
        fprintf(fp,"%04d-%02d-%02d,%02d:%02d:%02d,%s,%s,%s\n",
            localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday,
            localTime->tm_hour, localTime->tm_min, localTime->tm_sec, 
            currentLibrarianName, status, item);
    }fclose(fp);
}


void front(){
    int i; system("cls");
    HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,06);
    printToxy(5,1,"PROGRAMMING LANGUAGE PROJECT     |     BARRIOS         CALULANG          OLOROSO        |          BSCS 2CD");
    SetConsoleTextAttribute(h,15);
    printToxy(30,3,"\xdc\xdc     \xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc\xdc   \xdc\xdc\xdc\xdc\xdc\xdc\xdc     \xdc\xdc     \xdc\xdc\xdc\xdc\xdc\xdc\xdc   \xdc\xdc    \xdc\xdc");
    printToxy(30,4,"\xdc\xdc     \xdc\xdc  \xdc\xdc    \xdc\xdc  \xdc\xdc    \xdc\xdc   \xdc\xdc\xdc\xdc    \xdc\xdc    \xdc\xdc   \xdc\xdc  \xdc\xdc");
    printToxy(30,5,"\xdc\xdc     \xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc\xdc   \xdc\xdc\xdc\xdc\xdc\xdc\xdc   \xdc\xdc  \xdc\xdc   \xdc\xdc\xdc\xdc\xdc\xdc\xdc      \xdc\xdc");
    printToxy(30,6,"\xdc\xdc     \xdc\xdc  \xdc\xdc    \xdc\xdc  \xdc\xdc  \xdc\xdc   \xdc\xdc    \xdc\xdc  \xdc\xdc  \xdc\xdc       \xdc\xdc");
    printToxy(30,7,"\xdc\xdc\xdc\xdc\xdc  \xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc\xdc   \xdc\xdc   \xdc\xdc  \xdc\xdc    \xdc\xdc  \xdc\xdc   \xdc\xdc      \xdc\xdc");
    SetConsoleTextAttribute(h,06);
    printToxy(11,9, "\xdc\xdc     \xdc\xdc     \xdc\xdc     \xdc\xdc    \xdc\xdc     \xdc\xdc       \xdc\xdc\xdc\xdc\xdc   \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc     \xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc    \xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc\xdc");
    printToxy(11,10, "\xdc\xdc\xdc   \xdc\xdc\xdc    \xdc\xdc\xdc\xdc    \xdc\xdc\xdc   \xdc\xdc    \xdc\xdc\xdc\xdc    \xdc\xdc        \xdc\xdc      \xdc\xdc\xdc   \xdc\xdc\xdc  \xdc\xdc      \xdc\xdc\xdc   \xdc\xdc    \xdc\xdc\xdc  ");
    printToxy(11,11,"\xdc\xdc  \xdc  \xdc\xdc   \xdc\xdc  \xdc\xdc   \xdc\xdc \xdc\xdc \xdc\xdc   \xdc\xdc  \xdc\xdc   \xdc\xdc   \xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc   \xdc\xdc  \xdc  \xdc\xdc  \xdc\xdc\xdc\xdc\xdc   \xdc\xdc \xdc\xdc \xdc\xdc    \xdc\xdc\xdc  ");
    printToxy(11,12,"\xdc\xdc     \xdc\xdc  \xdc\xdc    \xdc\xdc  \xdc\xdc  \xdc\xdc\xdc\xdc  \xdc\xdc    \xdc\xdc  \xdc\xdc    \xdc\xdc  \xdc\xdc      \xdc\xdc     \xdc\xdc  \xdc\xdc      \xdc\xdc  \xdc\xdc\xdc\xdc    \xdc\xdc\xdc  ");
    printToxy(11,13,"\xdc\xdc     \xdc\xdc  \xdc\xdc    \xdc\xdc  \xdc\xdc   \xdc\xdc\xdc  \xdc\xdc    \xdc\xdc    \xdc\xdc\xdc\xdc\xdc   \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc     \xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc   \xdc\xdc\xdc    \xdc\xdc\xdc  ");
    SetConsoleTextAttribute(h,05);
    printToxy(33,15,"\xdc\xdc\xdc\xdc\xdc  \xdc\xdc    \xdc\xdc  \xdc\xdc\xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc     \xdc\xdc                                      ");
    printToxy(33,16,"\xdc\xdc      \xdc\xdc  \xdc\xdc   \xdc\xdc       \xdc\xdc\xdc    \xdc\xdc      \xdc\xdc\xdc   \xdc\xdc\xdc");
    printToxy(33,17,"\xdc\xdc\xdc\xdc\xdc     \xdc\xdc     \xdc\xdc\xdc\xdc\xdc    \xdc\xdc\xdc    \xdc\xdc\xdc\xdc\xdc   \xdc\xdc  \xdc  \xdc\xdc");
    printToxy(33,18,"   \xdc\xdc     \xdc\xdc        \xdc\xdc    \xdc\xdc\xdc    \xdc\xdc      \xdc\xdc     \xdc\xdc");
    printToxy(33,19,"\xdc\xdc\xdc\xdc\xdc     \xdc\xdc     \xdc\xdc\xdc\xdc\xdc    \xdc\xdc\xdc    \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc     \xdc\xdc");
    SetConsoleTextAttribute(h,06); gotoxy(5,21); for(int i=0;i<108;i++) printf("%c",223); SetConsoleTextAttribute(h,15); gotoxy(40,22);system("pause");
}
void loading(){
char load[] = {'.','.','.','o','.','.','0','o','.','0','0','o','0','0','0','o','0','0','.','o','0','.','.','o','.','.','.','\0'};
    int x=0,y=1,z=2,loop=0;
    while(loop != 9){
        if(loop > 0){
            x += 3;
            y += 3;
            z += 3;
        }
        delay(70);
        system("cls");
        gotoxy(40,4);printf("P L E A S E   I N S E R T   Y O U R   C A R D");
        gotoxy(56,6);printf("%c   %c   %c",load[x],load[y],load[z]);
        gotoxy(58,20);
        loop++;
    }
}
int scanScreen(int a){
    system("cls");
    int i;
    if(a==1){
        gotoxy(40,4);printf("S C A N N I N G   C A R D");
        for(i=0;i<18;i++){
            delay(100);
            gotoxy(40+i,6);printf("||||||||||||||||");
        }
       gotoxy(39,10);printf("N O T   Y E T   R E G I S T E R E D");
       gotoxy(40,11);system("pause");
    }else{
        if(currentSKey==1 && currentLKey==0){
            gotoxy(40,4);printf("S C A N N I N G   C A R D");
            for(i=0;i<18;i++){
                delay(100);
                gotoxy(40+i,6);printf("||||||||||||||||");
            }
            gotoxy(45,10);printf("W E L C O M E %s !",currentStudentName);
            gotoxy(40,11);system("pause");
        }else if(currentLKey==1 && currentSKey==0){
            gotoxy(40,4);printf("S C A N N I N G   C A R D");
            for(i=0;i<18;i++){
                delay(100);
                gotoxy(40+i,6);printf("||||||||||||||||");
            }
            gotoxy(45,10);printf("W E L C O M E %s !",currentLibrarianName);
            gotoxy(40,11);system("pause");
        }
    }
}
void printToxy(int x, int y, char *label){
    gotoxy(x, y);
    printf("%s", label);
}
void gotoxy(int x, int y){
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void delay(int ms){
    clock_t timeDelay = ms + clock();
    while(timeDelay > clock());
}

/*
    Reference for the valid isbn 
        https://www.tutorialspoint.com/cplusplus-program-to-check-for-isbn
*/