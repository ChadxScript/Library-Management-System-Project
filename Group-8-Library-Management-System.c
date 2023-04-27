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

//Function Declaration
void makenull();
void retrieveAccounts();
void retrieveBooks();
void saveAccounts();
void saveAccountsFD();
int insertcard();
void addAccount(aREC x);
void logs();
int menu(int x);
int checkAccount(int x, char str[31]);

//Global Vars
int currentSKey, currentLKey;
char currentStudentID[31], currentStudentName[31];
char currentLibrarianID[31], currentLibrarianName[31];
char fill[] = "NONE"; char adminFillName[] = "LibrarianADMIN"; char adminFillID[] = "LibrarianADMIN123";

int main(){
    aREC aLibn;
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
                }system("cls"); logs(); break; 
        case 2: system("cls"); currentLKey=aLibn.lkey = 1; currentSKey=aLibn.skey = 0;
                strcpy(aLibn.librarianName, adminFillName); strcpy(currentLibrarianName, adminFillName); 
                strcpy(aLibn.librarianID, adminFillID); strcpy(currentLibrarianID, adminFillID);
                strcpy(aLibn.studentID, fill); strcpy(aLibn.studentName, fill); 
                printf("\n\n Skey: %d\n Lkey: %d\n SName: %s\n SID: %s\n LName: %s\n LID: %s",aLibn.skey,aLibn.lkey,aLibn.studentName,aLibn.studentID,aLibn.librarianName,aLibn.librarianID);
                if(checkAccount(2,aLibn.librarianName)==1){
                    addAccount(aLibn); 
                }printf("\n\nREGISTRATION COMPLETE\n");system("pause"); system("cls"); logs(); break; 
        case 3: system("cls"); printf("\nLOG IN");
                strcpy(aLibn.studentName, currentStudentName);
                aLibn.skey = currentSKey; aLibn.lkey = currentLKey;
                strcpy(aLibn.librarianName, currentLibrarianName);
                aLibn.skey = currentSKey; aLibn.lkey = currentLKey;
                if(currentSKey==1 && currentLKey==0){
                    enterStudID:
                    printf("\nEnter Student ID: "); scanf(" %[^\n]s",aLibn.studentID);
                    if(strcmp(aLibn.studentID, currentStudentID)!=0){
                        printf("\nWrong Student ID. Please try again.\n"); 
                        system("pause"); system("cls"); goto enterStudID;
                    }else{
                        strcpy(aLibn.studentID, currentStudentID);
                        printf("\nWelcome %s !\n", aLibn.studentName);
                        system("pause"); system("cls"); logs();
                    }
                }else if(currentLKey==1 && currentSKey==0){
                    enterLibID:
                    printf("\nEnter Librarian ID: "); scanf(" %[^\n]s",aLibn.librarianID);
                    if(strcmp(aLibn.librarianID, currentLibrarianID)!=0){
                        printf("\nWrong Librarian ID. Please try again.\n"); 
                        system("pause"); system("cls"); goto enterLibID;
                    }else{
                        strcpy(aLibn.librarianID, currentLibrarianID);
                        printf("\nWelcome %s !\n", aLibn.librarianName);
                        system("pause"); system("cls"); logs();
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
            system("cls");
            switch(menu(1)){
                case 1: //borrow
                        break;
                case 2: //return
                        break;
                default: saveAccounts(); saveAccountsFD(); exit(0); 
                        break;
            }
        }
    }else if(currentSKey==0 && currentLKey==1){ //librarian
        while(1){
            system("cls");
            switch(menu(2)){
                case 1: //add book
                        break;
                case 2: //edit book
                        break;
                case 3: //remove book
                        break;
                default: saveAccounts(); saveAccountsFD(); exit(0);
                        break;
            }
        }
    }
}

void makenull(){ //initiate the list to null
    A = NULL;
}
int insertcard(){
    int num;
    FILE *fp;
    do{ //will check if the flashdrive is inserted to the device or not
        fp=fopen("D:\\Check.txt","w"); system("cls");
        printf("\nPa-insert ng flashdrive. Baka na stuck kayo rito pabago nalang ng letter. palagyan narin animation like loading HAHA");
    }while(fp==NULL); fclose(fp);
    fp=fopen("D:\\userDetails.csv","r");
    if(fp==NULL){ //if the user is new
        retrieveBooks(); retrieveAccounts();
        do{
            system("cls");
            printf("\n\nNew User || Select Category");
            printf("\n[1] Student");
            printf("\n[2] Librarian");
            printf("\nAre you a: ");
            scanf("%d",&num);
        }while(num<1||num>3); return num;
    }else{  //if the user is existing
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
void retrieveBooks(){
    system("cls");
}
void logs(){ //to get time if the student borrow the book
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
        fprintf(fp,"%04d-%02d-%02d,%02d:%02d:%02d,%s,%s\n",
            localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday,
            localTime->tm_hour, localTime->tm_min, localTime->tm_sec, currentStudentName, currentStudentID);
    }else if(currentSKey==0 && currentLKey==1){
        fprintf(fp,"%04d-%02d-%02d,%02d:%02d:%02d,%s,%s\n",
            localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday,
            localTime->tm_hour, localTime->tm_min, localTime->tm_sec, currentLibrarianName, currentLibrarianID);
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
    system("cls"); int userNum;
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
    }fclose(fp);
}
