/*Library Management System By Group 8 - Armand Angelo C. Barrios, Mary Jane P. Calulang, and Andrew R. Oloroso*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

typedef struct accountDetails{
    int skey, lkey;
    char studentID[12]; 
    char studentName[31];
    char librarianID[12], librarianName[31];
}aREC;
typedef struct anode{
    aREC aLib;
    struct anode* next;
}aLIST;aLIST *A;

//Global Vars
int currentSKey, currentLKey;
char currentStudentID[12], currentStudentName[31];
char currentLibrarianID[12], currentLibrarianName[31];
char fill[] = "NONE";

void makenull(){ //initiate the list to null
    A = NULL;
}
void retrieveAccounts(){
    FILE *fp;
    aREC aLibn; 
    fp=fopen("E:\\Accounts.csv","r+");
    if(fp!=NULL){
        while(!feof(fp)){
            fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%d,%d\n",
            aLibn.studentID, aLibn.librarianID, aLibn.studentName, aLibn.librarianName, &aLibn.skey, &aLibn.lkey);
            addAccount(aLibn);
        }fclose(fp);
    }
    fp=fopen("D:\\userDetails.csv", "r+");
    if(fp!=NULL){
        fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%d,%d",
        currentStudentID, currentLibrarianID, currentStudentName, currentLibrarianName, &currentSKey, &currentLKey);
        fclose(fp);
    }
    printf("\n\n");
    aLIST *p; p=A;
    while(p!=NULL){
        printf("Student Id: %s\nLibrarian Id: %s\nStudent Name: %s\nLibrarian Name: %s\nSkey: %d\nLkey: %d\n",
        p->aLib.studentID,p->aLib.librarianID,p->aLib.studentName,p->aLib.librarianName,p->aLib.skey,p->aLib.lkey);
        p=p->next;
    }printf("\n\n");system("pause");
}
void retrieveBooks(){

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
            p->aLib.studentID,p->aLib.librarianID,p->aLib.studentName,p->aLib.librarianName,p->aLib.skey,p->aLib.lkey);
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
        p->aLib.studentID,p->aLib.librarianID,p->aLib.studentName,p->aLib.librarianName,p->aLib.skey,p->aLib.lkey);
    }fclose(fp);
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

void getTime(){ //to get time if the student borrow the book
    time_t t;
    time(&t);
    printf("%s", ctime(&t));
}

int main(){
    aREC aLibn;
    makenull();
    //Log in part
    switch(insertcard()){
        case 1: system("cls"); currentSKey=aLibn.skey = 1; currentLKey=aLibn.lkey = 0;
                printf("\nNEW USER APPLICATION FORM (STUDENT)\n");
                printf("Enter Student Name: "); scanf(" %[^\n]s",aLibn.studentName);
                printf("Enter Student ID: "); scanf(" %[^\n]s",aLibn.studentID);
                strcpy(aLibn.librarianID, fill); strcpy(aLibn.librarianName, fill); strcpy(currentStudentID, aLibn.studentID);
                //printf("\n\n Skey: %d\n Lkey: %d\n Name: %s\n ID: %s",aLibn.skey,aLibn.lkey,aLibn.studentName,aLibn.studentID);
                printf("\n\nREGISTRATION COMPLETE\n"); system("pause");
                addAccount(aLibn); system("cls"); saveAccounts(); saveAccountsFD(); break; //if meron ng keme sa may main menu ililipat don yung save accounts tas yung savefd
        case 2: system("cls"); currentLKey=aLibn.lkey = 1; currentSKey=aLibn.skey = 0;
                printf("\nNEW USER APPLICATION FORM (LIBRARIAN)\n");
                printf("Enter Librarian Name: "); scanf(" %[^\n]s",aLibn.librarianName);
                printf("Enter Librarian ID: "); scanf(" %[^\n]s",aLibn.librarianID);
                printf("\n\nREGISTRATION COMPLETE\n");system("pause");
                strcpy(aLibn.studentID, fill); strcpy(aLibn.studentName, fill); strcpy(currentLibrarianID, aLibn.librarianID);
                addAccount(aLibn); system("cls"); saveAccounts(); saveAccountsFD(); break; //if meron ng keme sa may main menu ililipat don yung save accounts tas yung savefd
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
                        system("pause"); system("cls");
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
                        system("pause"); system("cls");
                    }
                }else{
                    system("cls"); printf("\nSystem Error.\n"); system("pause"); system("cls");
                }break;
        default: system("cls"); printf("\nWrong input.\n"); system("pause");system("cls");break;
    }

    //main menu kemerut kayo na bahala dito mga fre
    system("cls");
    /*switch(menu()){ 
        case 1: student kemerut
        case 2: librarian kemerut
    }*/
}