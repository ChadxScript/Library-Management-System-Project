/*Library Management System By Group 8 - Armand Angelo C. Barrios, Mary Jane P. Calulang, and Andrew R. Oloroso*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <windows.h>

typedef struct accountDetails{
    int skey, lkey;
    char studentID[31], studentName[31];
    char librarianID[31], librarianName[31];
}aREC;
typedef struct anode{
    aREC aLib;
    struct anode* next;
}aLIST;aLIST *A;

typedef struct bookDetails{
    int bookNum, publicationYear, bookQuant;
    char bookTitle[100], bookAuthor[100], ISBN[15];
}bREC;
typedef struct bnode{
    bREC bLib;
    struct bnode* next;
}bLIST;bLIST *B, *C;

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
void displayLogs();
int menu(int x);

void borrowBook(int x);
void returnbook();

void editBooks();
void removeAcopy();
void removeBooks();
void bookRequests();

int checkAccount(int x, char str[31]);
int verifyAccount(int x);
int checkBooks(bREC *x);
int checkISBN(char *ISBN, int x);

void decrypt();
void encrypt();

void saveBooks();
void saveAccounts();
void saveAccountsFD();
void logs(char inout[10], char item[100]);


//Global Vars
int currentSKey, currentLKey, currentbookNum=0;
char currentStudentID[31], currentStudentName[31];
char currentLibrarianID[31], currentLibrarianName[31];
char fill[] = "NONE"; char adminFillName[] = "LibrarianADMIN"; char adminFillID[] = "LibrarianADMIN123";

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
    makenull();
    system("cls");
    printf("\033[1;33m");
    switch(insertcard()){
        case 1: registerStudent();
                break;
        case 2: if(registerLibrarian()==1){
                    break;
                }else{
                    exit(0);
                }
                break;
        case 3: userLOGIN();
                break;
        default: system("cls");
                 printf("\INVALID INPUT.\n");
                 system("pause"); system("cls");
                 break;
    }

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
                default: saveBooks(); saveAccountsFD();
                         saveAccounts(); logs("OUT",fill); exit(0);
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
                            printf("\nCANCELLED.");
                            system("pause");
                            break;
                        }
                        break;
                case 4: bookRequests();
                        break;
                case 5: displayBooks();
                        break;
                case 6: displayLogs();
                        break;
                default: saveBooks(); saveAccountsFD();
                         saveAccounts();  logs("OUT",fill); exit(0);
                         break;
            }
        }
    }
}


void makenull(){ //initiate the list to null
    A = NULL;
    B = NULL;
    C = NULL;
}
int insertcard(){
    int num, i;
    HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,06);
    FILE *fp;
    //will check if the flashdrive is inserted to the device or not
    do{
        fp=fopen("D:\\Check.txt","w");
        loading();
    }while(fp==NULL);
    fclose(fp);
    front();

    fp=fopen("D:\\userDetails.csv","r");
    if(fp==NULL){
        retrieveBooks(); retrieveAccounts();
        decrypt(); scanScreen(1);
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
        retrieveBooks(); retrieveAccounts();
        decrypt(); scanScreen(2);
        return 3;
    }
    fclose(fp);
}
void retrieveAccounts(){
    FILE *fp;
    aREC aLibn;
    // database
    fp=fopen("E:\\Accounts.csv","r+");
    if(fp!=NULL){
        while(!feof(fp)){
            fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%d,%d\n",
                    aLibn.studentID, aLibn.librarianID, aLibn.studentName,
                    aLibn.librarianName, &aLibn.skey, &aLibn.lkey);
            addAccount(aLibn);
        }fclose(fp);
    }

    // flashdrive
    fp=fopen("D:\\userDetails.csv", "r+");
    if(fp!=NULL){
        fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%d,%d",
                currentStudentID, currentLibrarianID, currentStudentName,
                currentLibrarianName, &currentSKey, &currentLKey);
        fclose(fp);
    }
}
void addAccount(aREC x){
    aLIST *p, *q, *temp;
    q=p=A;
    temp = (aLIST*) malloc(sizeof(aLIST));
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
    do{
        fp=fopen("E:\\Books.csv","r+");
    }while(fp==NULL);
    while(!feof(fp)){
        fscanf(fp,"%d,%[^,],%[^,],%[^,],%d,%d\n",
                &bLibn.bookNum, bLibn.ISBN, bLibn.bookTitle,
                bLibn.bookAuthor, &bLibn.publicationYear, &bLibn.bookQuant);
           currentbookNum=bLibn.bookNum; 
           addBooks(bLibn);
    }fclose(fp);
}
void addBooks(bREC x){
    bLIST *p, *q, *temp;
    q=p=B;
    temp = (bLIST*) malloc(sizeof(bLIST));
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
    bLIST *p, *q, *temp;
    q=p=C;
    temp = (bLIST*) malloc(sizeof(bLIST));
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
    fillAgain1:
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
            goto fillAgain1;
        }
    system("cls");
    logs("IN",fill);
}
int registerLibrarian(){
    aREC aLibn;
    HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,06);
    char userStr[19];
    system("cls");
    currentLKey=aLibn.lkey = 1; currentSKey=aLibn.skey = 0;
    strcpy(aLibn.librarianName, adminFillName);
    strcpy(currentLibrarianName, adminFillName);
    strcpy(aLibn.librarianID, adminFillID);
    strcpy(currentLibrarianID, adminFillID);
    strcpy(aLibn.studentID, fill);
    strcpy(aLibn.studentName, fill);

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
        system("cls");
        logs("IN",fill);
        return 1;
    }else{
        printf("\nERROR.");
        printf("\nCRIDENTIALS NOT MATCH.\n");
        system("pause");
        return 2;
    }
    
}
void userLOGIN(){
    aREC aLibn;
    system("cls");
    printf("\nLOG IN");
    strcpy(aLibn.studentName, currentStudentName);
    aLibn.skey = currentSKey; aLibn.lkey = currentLKey;
    strcpy(aLibn.librarianName, currentLibrarianName);

    if(currentSKey==1 && currentLKey==0){
        enterStudID:
            printf("\nEnter Student ID: ");
            scanf(" %[^\n]s",aLibn.studentID);
            if(strcmp(aLibn.studentID, currentStudentID)!=0){
                printf("\nWrong Student ID. Please try again.\n");
                system("pause"); system("cls");
                goto enterStudID;
            }else{
                logs("IN",fill);
            }
    }else if(currentLKey==1 && currentSKey==0){
        enterLibID:
            printf("\nEnter Librarian ID: ");
            scanf(" %[^\n]s",aLibn.librarianID);

            if(strcmp(aLibn.librarianID, currentLibrarianID)!=0){
                printf("\nWrong Librarian ID. Please try again.\n");
                system("pause"); system("cls");
                goto enterLibID;
            }else{
                logs("IN",fill);
            }
    }else{
        system("cls");
        printf("\nSystem Error.\n");
        system("pause"); system("cls");
    }
}


void displayBooks(){
    bLIST *p; p=B;
    system("cls");
    printf("| %-8s | %-50s | %-90s | %-80s | %-12s | %-12s |\n",
         "BOOK NUMBER", "ISBN", "BOOK TITLE", "BOOK AUTHOR", "PUBLISH YEAR", "BOOK QUANTITY");

    while (p != NULL) {
        printf("| %-8d | %-50s | %-90s | %-80s | %-12d | %-12s |\n\n",
            p->bLib.bookNum, p->bLib.ISBN, p->bLib.bookTitle, 
            p->bLib.bookAuthor, p->bLib.publicationYear, p->bLib.bookQuant);
        p = p->next;
    }
}
void displayCurrentBook(bREC *x){
    printf("\n| %-8s | %-50s | %-90s | %-80s | %-12s | %-12s |\n",
            "BOOK NUMBER", "ISBN", "BOOK TITLE", "BOOK AUTHOR", "PUBLISH YEAR", "BOOK QUANTITY");
        
    printf("| %-8s | %-50s | %-90s | %-80s | %-12s | %-12s |\n\n",
        x->bookNum, x->ISBN, x->bookTitle,
        x->bookAuthor, x->publicationYear, x->bookQuant);
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
    int i=1;
    char temp[100];
    bLIST *p, *q;
    q=p=B;
    while(p!=NULL && x!=p->bLib.bookNum){
        q=p;
        p=p->next;
    }
    if(p==NULL){
        printf("\nError 404. Book Number: %d not found.\n",x);
        system("pause"); system("cls");
    }else{
        printf("\nBook Number\t Book Title\t Book Author\t Publication Year\n %d.) %d\t %s\t %s\t %d\n",
                i++,p->bLib.bookNum, p->bLib.bookTitle, p->bLib.bookAuthor, p->bLib.publicationYear);

        if(verifyAccount(1)==1){
            //save the borrowed book to the file
            FILE *fp;
            fp=fopen("D:\\borrowedBooks.csv","a+");
            if(fp!=NULL){
                fprintf(fp,"%d,%s,%s,%d\n",
                        p->bLib.bookNum, p->bLib.bookTitle, p->bLib.bookAuthor, p->bLib.publicationYear);
            }else{
                printf("\nSystem Error. cant save into file.\n");
                system("pause");system("cls");
            }fclose(fp);

            //remove the borrowed book to the database kasi hiniram nga so bale mawawala sa database yung libro
            q=p=B;
            while(p!=NULL && x!=p->bLib.bookNum){
                q=p;
                p=p->next;
            }
            if(fp==NULL){
                printf("\nBook not found!\nWrong book ID or book does not exist or borrowed.\n");
                system("pause"); system("cls");
            }else{
                strcpy(temp,p->bLib.bookTitle);
                if (p==B){
                    B=p->next;
                }else{
                    q->next=p->next;
                }free(p);
                logs("Borrowed Book", temp);
                printf("\nYou successfully borrowed (%s).\n", temp);
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
    fp=fopen("D:\\borrowedBooks.csv","r");
    if(fp==NULL){
        printf("\nERROR. No Books to Return.\n");
        system("pause"); system("cls");
    }else{
        while(!feof(fp)){
            fscanf(fp,"%d,%[^,],%[^,],%[^,],%d,%d\n",
                    &bLibn.bookNum, bLibn.ISBN, bLibn.bookTitle, 
                    bLibn.bookAuthor, &bLibn.publicationYear, &bLibn.bookQuant);
           addBooks(bLibn);
           logs("Retured Book",bLibn.bookTitle);
           printf("\nBook (%s) successfully retured.\n",bLibn.bookTitle);
        }fclose(fp);
        saveBooks();
        remove("D:\\borrowedBooks.csv");
        system("pause"); system("cls");
    }
}

void insertExistingBook(){
    int userNum;
    system("cls");
    displayBooks();
    printf("\n\nEnter Book Number: ");
    scanf("%d", &userNum);

    bLIST *p, *q;
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
        }
    }
}
void insertNewBook(){
    bREC bBooks;
    int userNum;
    char userISBN[14];
    long long firstNum, randomNum;
    insertNewBookAgain:
        system("cls");

        currentbookNum++; bBooks.bookNum=currentbookNum;
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
            currentbookNum--;
        }
    }else{
        currentbookNum--;
    }
}
void editBooks(){
    int ch=0, a, x;
    char userISBN[14];
    bLIST *p, *q;
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
                    default: printf("\n\nSelect 1-4 only.");
                            break;
                }
            }logs("Edit Book",p->bLib.bookTitle);
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
    int x;
    bLIST *p, *q;

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
            printf("\nBOOK SELECTED:\n");
            displayCurrentBook(&p);
            printf("\nEnter book copies to be removed: ");
            scanf("%d", &x);
            if(x>0 && x<p->bLib.bookQuant){
                p->bLib.bookQuant -= x;
                printf("\nMODIFICATION SUCCESSFUL.\n");
                displayCurrentBook(&p);
                system("pause");
                displayBooks();
                system("pause");
            }else{
                printf("\nERROR.");
                printf("\nINVALID QUANTITY OF BOOKS.\n");
                system("pause");
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
    bLIST *p, *q;

    printf("\n\nInput book ID to be removed: ");
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
            strcpy(temp,p->bLib.bookTitle);
            if (p==B){
                B=p->next;
            }else{
                q->next=p->next;
            }free(p);
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
    bLIST *p, *q; 
    fp=fopen("BookRequests.csv","r");
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
            printf("| %-8s | %-50s | %-90s | %-80s | %-12s | %-12s |\n",
                "BOOK NUMBER", "ISBN", "BOOK TITLE", "BOOK AUTHOR", "PUBLISH YEAR", "BOOK QUANTITY");

            q=p=C;
            while (p != NULL) {
                printf("| %-8d | %-50s | %-90s | %-80s | %-12d | %-12s |\n\n",
                    p->bLib.bookNum, p->bLib.ISBN, p->bLib.bookTitle, 
                    p->bLib.bookAuthor, p->bLib.publicationYear, p->bLib.bookQuant);
                p = p->next;
            }

            printf("\nSELECT CATEGORY\n");
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
    aLIST *p, *q;
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
    bLIST *p, *q;
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
    bLIST *p, *q;
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


void decrypt(){
    int i;
    aLIST *p, *q;
    p=A;

    while(p!=NULL){
        i=0;
        if(p->aLib.skey==1 && p->aLib.lkey==0){ //student
            while(p->aLib.studentID[i]!='\0'){
                p->aLib.studentID[i] = p->aLib.studentID[i] - 70;
                i++;
            }
        }else if(p->aLib.skey==0 && p->aLib.lkey==1){ //Librarian 
            while(p->aLib.librarianID[i]!='\0'){
                p->aLib.librarianID[i] = p->aLib.librarianID[i] - 70;
                i++; 
            }
        } 
        p=p->next; 
    }
    
    if(currentSKey==1 && currentLKey==0){ //student
        i=0;
        while(currentStudentID[i]!='\0'){
            currentStudentID[i] = currentStudentID[i] - 70;
            i++;
        }
    }else if(currentSKey==0 && currentLKey==1){ //librarian
        i=0;
        while(currentLibrarianID[i]!='\0'){
            currentLibrarianID[i] = currentLibrarianID[i] - 70; 
            i++;
        }
    }
}
void encrypt(){
    int i=0;
    aLIST *p, *q;
    p=A;

    while(p!=NULL){
        i=0;
        if(p->aLib.skey==1 && p->aLib.lkey==0){ //student
            while(p->aLib.studentID[i]!='\0'){
                p->aLib.studentID[i] = p->aLib.studentID[i] + 70;
                i++;
            }
        }else if(p->aLib.skey==0 && p->aLib.lkey==1){ //Librarian 
            while(p->aLib.librarianID[i]!='\0'){
                p->aLib.librarianID[i] = p->aLib.librarianID[i] + 70;
                i++; 
            }
        } 
        p=p->next; 
    }
}


void saveBooks(){
    FILE *fp;
    bLIST *p; p=B;
    fp=fopen("E:\\Books.csv", "w+");
    if(fp==NULL){
        printf("Error 404. File not found.\n");
        system("pause");
    }else{
        while(p!=NULL){
            fprintf(fp,"%d,%s,%s,%s,%d,%d\n",
                    p->bLib.bookNum,p->bLib.ISBN,p->bLib.bookTitle,
                    p->bLib.bookAuthor,p->bLib.publicationYear,p->bLib.bookQuant);
            p=p->next;
        }fclose(fp);
    }
}
void saveAccounts(){
    FILE *fp;
    aLIST *p; p=A;
    fp=fopen("E:\\Accounts.csv", "w+");
    if(fp==NULL){
        printf("Error 404. File not found.\n");
        system("pause");
    }else{
        while(p!=NULL){
            fprintf(fp,"%s,%s,%s,%s,%d,%d\n",
                    p->aLib.studentID,p->aLib.librarianID,p->aLib.studentName,
                    p->aLib.librarianName,p->aLib.skey,p->aLib.lkey);
            p=p->next;
        }fclose(fp);
    }
}
void saveAccountsFD(){
    int i=0;
    FILE *fp;
    aLIST *p, *q;
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

    encrypt(); 
    fp=fopen("D:\\userDetails.csv", "w+");
    if (fp==NULL){
        printf("\nError 404. File not found.\n");
        system("pause");system("cls");
    }else{
        fprintf(fp,"%s,%s,%s,%s,%d,%d\n",
                p->aLib.studentID,p->aLib.librarianID,p->aLib.studentName,
                p->aLib.librarianName,p->aLib.skey,p->aLib.lkey);
    }
    fclose(fp);
}
void logs(char inout[10], char item[100]){
    FILE* fp;
    time_t currentTime;
    struct tm *localTime;

    //get current date and time
    currentTime = time(NULL);
    localTime = localtime(&currentTime);
    char filename[20];
    strftime(filename, sizeof(filename), "%Y-%m-%d.csv", localTime);

    fp=fopen(filename,"a+");

    if(currentSKey==1 && currentLKey==0){
        fprintf(fp,"%04d-%02d-%02d,%02d:%02d:%02d,%s,%s,%s,%s\n",
            localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday,
            localTime->tm_hour, localTime->tm_min, localTime->tm_sec, currentStudentName, currentStudentID, inout, item);
    }else if(currentSKey==0 && currentLKey==1){
        fprintf(fp,"%04d-%02d-%02d,%02d:%02d:%02d,%s,%s,%s,%s\n",
            localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday,
            localTime->tm_hour, localTime->tm_min, localTime->tm_sec, currentLibrarianName, currentLibrarianID, inout, item);
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