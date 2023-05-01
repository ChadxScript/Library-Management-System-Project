/*Library Management System By Group 8 - Armand Angelo C. Barrios, Mary Jane P. Calulang, and Andrew R. Oloroso*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

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
    int bookID, publicationYear;
    char bookTitle[100], bookAuthor[100];
}bREC;
typedef struct bnode{
    bREC bLib;
    struct bnode* next;
}bLIST;bLIST *B;

//Function Declaration
void makenull();
void retrieveAccounts();
void retrieveBooks();

void borrowBook(int x);
void returnbook();

void addBooks(bREC x);
void editBooks(int x);
void removeBooks(int x);
int checkBooks(bREC *x);
int verifyAccount(int x);
void saveBooks();

void saveAccounts();
void saveAccountsFD();
int insertcard();
void addAccount(aREC x);

void logs(char inout[10], char item[100]);
int menu(int x);
int checkAccount(int x, char str[31]);
void displayBooks();

//Global Vars
int currentSKey, currentLKey, currentBookID=0;
char currentStudentID[31], currentStudentName[31];
char currentLibrarianID[31], currentLibrarianName[31];
char fill[] = "NONE"; char adminFillName[] = "LibrarianADMIN"; char adminFillID[] = "LibrarianADMIN123";

int main(){
    aREC aLibn;
    bREC bBooks;
    makenull();
    //Log in part
    switch(insertcard()){
        case 1: fillAgain1: system("cls"); currentSKey=aLibn.skey = 1; currentLKey=aLibn.lkey = 0;
                printf("\nNEW USER APPLICATION FORM (STUDENT)\n");
                printf("Enter Student Name: "); scanf(" %[^\n]s",aLibn.studentName);
                printf("Enter Student ID: "); scanf(" %[^\n]s",aLibn.studentID);
                strcpy(aLibn.librarianID, fill); strcpy(aLibn.librarianName, fill);
                strcpy(currentStudentName, aLibn.studentName); strcpy(currentStudentID, aLibn.studentID);
                printf("\n\n Skey: %d\n Lkey: %d\n SName: %s\n SID: %s\n LName: %s\n LID: %s",aLibn.skey,aLibn.lkey,aLibn.studentName,aLibn.studentID,aLibn.librarianName,aLibn.librarianID);
                if(checkAccount(1,aLibn.studentID)==1){
                    printf("\n\nREGISTRATION COMPLETE\n"); system("pause");
                    addAccount(aLibn);
                }else{
                    printf("\nInvalid Entry. Duplicate Student ID. Please try again.\n"); system("pause"); goto fillAgain1;
                }system("cls"); logs("IN",fill); break;
        case 2: system("cls"); currentLKey=aLibn.lkey = 1; currentSKey=aLibn.skey = 0;
                strcpy(aLibn.librarianName, adminFillName); strcpy(currentLibrarianName, adminFillName);
                strcpy(aLibn.librarianID, adminFillID); strcpy(currentLibrarianID, adminFillID);
                strcpy(aLibn.studentID, fill); strcpy(aLibn.studentName, fill);
                printf("\n\n Skey: %d\n Lkey: %d\n SName: %s\n SID: %s\n LName: %s\n LID: %s",aLibn.skey,aLibn.lkey,aLibn.studentName,aLibn.studentID,aLibn.librarianName,aLibn.librarianID);
                if(checkAccount(2,aLibn.librarianName)==1){
                    addAccount(aLibn);
                }printf("\n\nREGISTRATION COMPLETE\n");system("pause"); system("cls"); logs("IN",fill); break;
        case 3: system("cls"); printf("\nLOG IN");
                strcpy(aLibn.studentName, currentStudentName);
                aLibn.skey = currentSKey; aLibn.lkey = currentLKey;
                strcpy(aLibn.librarianName, currentLibrarianName);
                if(currentSKey==1 && currentLKey==0){
                    enterStudID:
                    printf("\nEnter Student ID: "); scanf(" %[^\n]s",aLibn.studentID);
                    if(strcmp(aLibn.studentID, currentStudentID)!=0){
                        printf("\nWrong Student ID. Please try again.\n");
                        system("pause"); system("cls"); goto enterStudID;
                    }else{
                        //strcpy(aLibn.studentID, currentStudentID);
                        printf("\nWelcome %s !\n", aLibn.studentName);
                        system("pause"); system("cls"); logs("IN",fill);
                    }
                }else if(currentLKey==1 && currentSKey==0){
                    enterLibID:
                    printf("\nEnter Librarian ID: "); scanf(" %[^\n]s",aLibn.librarianID);
                    if(strcmp(aLibn.librarianID, currentLibrarianID)!=0){
                        printf("\nWrong Librarian ID. Please try again.\n");
                        system("pause"); system("cls"); goto enterLibID;
                    }else{
                        //strcpy(aLibn.librarianID, currentLibrarianID);
                        printf("\nWelcome %s !\n", aLibn.librarianName);
                        system("pause"); system("cls"); logs("IN",fill);
                    }
                }else{
                    system("cls"); printf("\nSystem Error.\n"); system("pause"); system("cls");
                }break;
        default: system("cls"); printf("\nWrong input.\n"); system("pause");system("cls");break;
    }

    //main menu kemerut kayo na bahala dito mga fre
    system("cls");
    if(currentSKey==1 && currentLKey==0){ //student
        while(1){
            system("cls"); displayBooks();
            switch(menu(1)){
                case 1: printf("\nInput Book ID: ");scanf("%d",&bBooks.bookID);
                        borrowBook(bBooks.bookID); break;
                case 2: if(verifyAccount(1)==1){
                            returnbook();
                        }else{
                            printf("\nTransaction Cancelled. Your input does not match to your cridentials.\n"); system("pause");system("cls");
                        }
                        break;
                default: saveBooks(); saveAccounts(); saveAccountsFD(); logs("OUT",fill); exit(0);
                        break;
            }
        }
    }else if(currentSKey==0 && currentLKey==1){ //librarian
        while(1){
            system("cls");
            displayBooks();
            switch(menu(2)){
                case 1: printf("Input book title: ");scanf(" %[^\n]s",bBooks.bookTitle);
                        bBooks.bookID=currentBookID; bBooks.bookID+=1; printf("Book ID: %d\n",bBooks.bookID);
                        printf("Input book author: ");scanf(" %[^\n]s",bBooks.bookAuthor);
                        printf("Input publication year: ");scanf("%d",&bBooks.publicationYear);
                        if(checkBooks(&bBooks)==1){
                            if(verifyAccount(2)==1){
                                addBooks(bBooks); logs("Add Book",bBooks.bookTitle);  
                                printf("\nModification Successful.\n");system("pause");
                            }else{
                                printf("\nModification Unsuccessful.\n");system("pause");
                            }
                        }else{
                            printf("\nModification Unsuccessful. Details are already in the List.\n");system("pause");
                        }
                        break;
                case 2: printf("Input book ID to be edited: ");scanf("%d",&bBooks.bookID);
                        if(verifyAccount(2)==1){
                            editBooks(bBooks.bookID); 
                            printf("\nModification Successful.\n");system("pause");
                        }else{
                            printf("\nModification Unsuccessful.\n");system("pause");
                        }
                        break;
                case 3: printf("Input book ID to be deleted: ");scanf("%d",&bBooks.bookID);
                        if(verifyAccount(2)==1){
                            removeBooks(bBooks.bookID); 
                        }else{
                            printf("\nModification Unsuccessful.\n");system("pause");
                        }
                        break;
                default: saveBooks();saveAccounts(); saveAccountsFD(); logs("OUT",fill); exit(0);
                        break;
            }
        }
    }
}

void borrowBook(int x){
    int i=1;
    char temp[100];
    bLIST *p, *q;
    q=p=B;
    while(p!=NULL && x!=p->bLib.bookID){
        q=p; 
        p=p->next;
    }
    if(p==NULL){
        printf("\nError 404. BookID: %d not found.\n",x); system("pause"); system("cls");
    }else{
        printf("\nBookID\t Book Title\t Book Author\t Publication Year\n %d.) %d\t %s\t %s\t %d\n",
                i++,p->bLib.bookID, p->bLib.bookTitle, p->bLib.bookAuthor, p->bLib.publicationYear);
        if(verifyAccount(1)==1){
            //save the borrowed book to the file
            FILE *fp; 
            fp=fopen("D:\\borrowedBooks.csv","a+");
            if(fp!=NULL){
                fprintf(fp,"%d,%s,%s,%d\n",
                        p->bLib.bookID, p->bLib.bookTitle, p->bLib.bookAuthor, p->bLib.publicationYear);
            }else{
                printf("\nSystem Error. cant save into file.\n"); system("pause");system("cls");
            }fclose(fp);

            //remove the borrowed book to the database kasi hiniram nga so bale mawawala sa database yung libro
            q=p=B;
            while(p!=NULL && x!=p->bLib.bookID){
                q=p; 
                p=p->next;
            }
            if(fp==NULL){
                printf("\nBook not found!\nWrong book ID or book does not exist.\n"); system("pause"); system("cls");
            }else{
                strcpy(temp,p->bLib.bookTitle);
                if (p==B){
                    B=p->next;
                }else{
                    q->next=p->next;
                }free(p);
                logs("Borrowed Book", temp); printf("\nYou successfully borrowed %s.\n", temp); system("pause");
            }
        }else{
            printf("\nTransaction Cancelled. Your input does not match to your cridentials.\n"); system("pause");system("cls");
        }
    }
}
void returnbook(){
    FILE *fp;
    bREC bLibn;
    fp=fopen("D:\\borrowedBooks.csv","r");
    if(fp==NULL){
        printf("\nERROR. No Books to Return.\n"); system("pause"); system("cls");
    }else{ 
        while(!feof(fp)){
            fscanf(fp,"%d,%[^,],%[^,],%d\n",
                    &bLibn.bookID, bLibn.bookTitle, bLibn.bookAuthor, 
                    &bLibn.publicationYear);
           addBooks(bLibn);
        }fclose(fp); saveBooks(); remove("D:\\borrowedBooks.csv"); logs("Retured Book",bLibn.bookTitle);
        printf("\nBook (%s) successfully retured.\n",bLibn.bookTitle); system("pause"); system("cls");
    }
}

int verifyAccount(int x){
    char userInput[31];
    if(x==1){ //student
        printf("\nPlease Enter Your Student ID to confirm: "); scanf(" %[^\n]s",userInput);
        if(strcmp(userInput,currentStudentID)==0){
            return 1;
        }else{
            return 2;
        }
    }else{ //librarian
        printf("\nPlease Enter Librarian ID to confirm: "); scanf(" %[^\n]s",userInput);
        if(strcmp(userInput,adminFillID)==0){
            return 1;
        }else{
            return 2;
        }
    }
}
void addBooks(bREC x){
    bLIST *p, *q, *temp;
    q=p=B;
    temp = (bLIST*) malloc(sizeof(bLIST));
    temp->bLib = x;
    while(p!=NULL && x.bookID > p->bLib.bookID){
        q=p;
        p=p->next;
    }
    if(p==B){
        B = temp;
    }else{
        q->next = temp;
    }temp->next = p;
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
    }else{
        q=p=B;
        while(p!=NULL && strcasecmp(x->bookAuthor,p->bLib.bookAuthor)!=0){
            q=p; 
            p=p->next;
        }
        if(p==NULL){
            return 1;
        }else{
            return 2;
        }
    } 
}
void editBooks(int x){
    int ch=0, a;
    bLIST *p, *q;
    bREC bBooks;
    q=p=B;
    while(p!=NULL && x!=p->bLib.bookID){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        printf("Book not found!\n");
        printf("Wrong book ID or book does not exist.\n");
    }
    else{
        while(ch!=4){
            printf("Book ID: %d\n",p->bLib.bookID);
            printf("Book title: %s\n",p->bLib.bookTitle);
            printf("Book author: %s\n",p->bLib.bookAuthor);
            printf("Book publication year: %d\n",p->bLib.publicationYear);
            printf("\nCHANGE BOOK DETAILS\n");
            printf("[1] Book title\n");
            printf("[2] Book author\n");
            printf("[3] Book publication year\n");
            printf("[4] Back\n");
            printf("Select the detail to edit: ");scanf("%d",&ch);
            switch(ch){
                    case 1:printf("Input NEW book title: ");scanf(" %[^\n]s",p->bLib.bookTitle);
                        //strcpy(p->bLib.bookTitle,bBooks.bookTitle);
                        break;
                    case 2:printf("Input NEW book author: ");scanf(" %[^\n]s",p->bLib.bookAuthor);
                        //strcpy(p->bLib.bookAuthor,bBooks.bookAuthor);
                        break;
                    case 3:printf("Input NEW publication year: ");scanf("%d",&p->bLib.publicationYear);
                        break;
                    case 4:printf("Book was succesfully edited.");
                        break;
                    default: printf("Select 1-4 only.");
                            break;
            }
        }logs("Edit Book",p->bLib.bookTitle);  
    }
}
void removeBooks(int x){
    char temp[100];
    bLIST *p, *q;
    q=p=B;
    while(p!=NULL && p->bLib.bookID!=x){
            q=p;
            p=p->next;
    }
    if (p==NULL){
        printf("Book not found!\n");
        printf("Wrong book ID or book does not exist.\n");
        system("pause"); system("cls");
    }
    else{
        strcpy(temp,p->bLib.bookTitle);
        if (p==B)
            B=p->next;
        else
            q->next=p->next;
        free(p);
        logs("Removed Book",temp); printf("The book %s was successfully removed.\n", temp); system("pause");
    }
}


void makenull(){ //initiate the list to null
    A = NULL;
    B = NULL;
}
int insertcard(){
    int num;
    FILE *fp;
    do{ //will check if the flashdrive is inserted to the device or not
        fp=fopen("D:\\Check.txt","w"); //system("cls");
        printf("\nPa-insert ng flashdrive. Baka na stuck kayo rito pabago nalang ng letter. palagyan narin animation like loading HAHA");
    }while(fp==NULL); fclose(fp);
    fp=fopen("D:\\userDetails.csv","r");
    if(fp==NULL){
        retrieveBooks(); retrieveAccounts();
        do{
            system("cls");
            printf("\n\nNew User || Select Category");
            printf("\n[1] Student");
            printf("\n[2] Librarian");
            printf("\nAre you a: ");
            scanf("%d",&num);
        }while(num<1||num>3); return num;
    }else{
        retrieveBooks(); retrieveAccounts();
        return 3;
    }fclose(fp);
}
void addAccount(aREC x){
    aLIST *p, *q, *temp;
    q=p=A;
    temp = (aLIST*) malloc(sizeof(aLIST));
    temp->aLib = x;
    while (p!=NULL){
        q=p;
        p=p->next;
    }
    if(p==A){
        A = temp;
    }else{
        q->next = temp;
    }temp->next = p;
}
void retrieveAccounts(){
    FILE *fp;
    aREC aLibn;
    fp=fopen("E:\\Accounts.csv","r+");
    if(fp!=NULL){
        while(!feof(fp)){
            fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%d,%d\n",
                    aLibn.studentID, aLibn.librarianID, aLibn.studentName,
                    aLibn.librarianName, &aLibn.skey, &aLibn.lkey);
            addAccount(aLibn);
        }fclose(fp);
    }
    fp=fopen("D:\\userDetails.csv", "r+");
    if(fp!=NULL){
        fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%d,%d",
                currentStudentID, currentLibrarianID, currentStudentName,
                currentLibrarianName, &currentSKey, &currentLKey);
        fclose(fp);
    }
    printf("\n\n"); //pang check lang tong part na to if naretrieve
    aLIST *p; p=A;
    while(p!=NULL){
        printf("Student Id: %s\nLibrarian Id: %s\nStudent Name: %s\nLibrarian Name: %s\nSkey: %d\nLkey: %d\n",
                p->aLib.studentID,p->aLib.librarianID,p->aLib.studentName,
                p->aLib.librarianName,p->aLib.skey,p->aLib.lkey);
        p=p->next;
    }printf("\n\n");system("pause");
}
void saveBooks(){
    FILE *fp;
    bLIST *p; p=B;
    fp=fopen("E:\\books.csv", "w+");
    if(fp==NULL){
        printf("Error 404. File not found.\n"); system("pause");
    }else{
        while(p!=NULL){
            fprintf(fp,"%d,%s,%s,%d\n",
                    p->bLib.bookID,p->bLib.bookTitle,p->bLib.bookAuthor,p->bLib.publicationYear);
            p=p->next;
        }fclose(fp);
    }
}

void retrieveBooks(){
    FILE *fp;
    bREC bLibn;
    fp=fopen("E:\\books.csv","r+");
    if(fp==NULL){
        printf("\nERROR 404. books.csv Not Found.\n");system("pause"); system("cls");
    }else{ 
        while(!feof(fp)){
            fscanf(fp,"%d,%[^,],%[^,],%d\n",
                    &bLibn.bookID, bLibn.bookTitle, bLibn.bookAuthor, 
                    &bLibn.publicationYear);
           currentBookID=bLibn.bookID; addBooks(bLibn);
        }fclose(fp);
    }
}
void logs(char inout[10], char item[100]){ //to get time if the student borrow the book
    FILE* fp;
    time_t currentTime;
    struct tm *localTime;
    fp=fopen("E:\\Logs.csv","a+");
    if(fp==NULL){
        printf("Error 404. File not found.\n"); system("pause");
    }
    currentTime = time(NULL);   //get current date and time
    localTime = localtime(&currentTime);

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
                }if(p!=NULL){
                    return 1;
                }else{
                    return 2;
                }break;
    }
}
int menu(int x){
    //system("cls"); 
    int userNum;
    printf("\nCHOOSE CATEGORY\n");
    if(x==1){//student
        printf("\n[1] BORROW");
        printf("\n[2] RETURN");
        printf("\n[3] EXIT");
    }else{//librarian
        printf("\n[1] ADD BOOK");
        printf("\n[2] EDIT BOOK");
        printf("\n[3] REMOVE BOOK");
        printf("\n[4] EXIT");
    }
    printf("\n\nENTER CHOICE: "); scanf("%d",&userNum);
    return userNum;
}
void displayBooks(){
    bLIST *p; p=B;
    system("cls"); printf("Book ID\t Book Title\t Book Author\t Publication Year\n");
    while(p!=NULL){
        printf("%d\t %s\t %s\t %d\n",
                p->bLib.bookID, p->bLib.bookTitle, p->bLib.bookAuthor,
                p->bLib.publicationYear);
        p=p->next;
    }
}

void saveAccounts(){
    FILE *fp;
    aLIST *p; p=A;
    fp=fopen("E:\\Accounts.csv", "w+");
    if(fp==NULL){
        printf("Error 404. File not found.\n"); system("pause");
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
        system("cls"); printf("\nSystem Error. cant save into file.\n"); system("pause");system("cls");
    }
    fp=fopen("D:\\userDetails.csv", "w+");
    if (fp==NULL){
        printf("\nError 404. File not found.\n"); system("pause");system("cls");
    }else{
        fprintf(fp,"%s,%s,%s,%s,%d,%d\n",
                p->aLib.studentID,p->aLib.librarianID,p->aLib.studentName,
                p->aLib.librarianName,p->aLib.skey,p->aLib.lkey);
    }
    fclose(fp);
}
