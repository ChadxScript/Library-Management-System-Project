#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

COORD coord = {0, 0}; //UI
void printToxy(int x, int y, char *label);
void gotoxy(int x, int y);

int main()
{
    //front()
    //librarian() 
      student();
    //student_new_user()
    //select_user()
}

void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printToxy(int x, int y, char *label)
{
    gotoxy(x, y);
    printf("%s", label);
}                                                            

void front()
{
      int i;
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

void librarian() //add,edit,remove exit
{
    int i;
    HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
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
     for(i=0;i<4;i++){gotoxy(85,11+i);printf("%c",219);} for(i=0;i<4;i++){gotoxy(98,11+i);printf("%c",219);} printToxy(90,12,"EXIT");
    SetConsoleTextAttribute(h,05); gotoxy(5,18); for(int i=0;i<101;i++) printf("%c",223); 
    SetConsoleTextAttribute(h,06); printToxy(33,8,"L     I     B     R     A     R     I     A     N");
    SetConsoleTextAttribute(h,15);printToxy(5,20,"Enter choice: "); 
    //AND SO ON AND SO FORT
}

void student() //borrow, return
{
    int i;
    HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
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
    SetConsoleTextAttribute(h,15);printToxy(5,20,"Enter choice: "); //gotoxy (?,?); scanf(kineso)
    //AND SO ON AND SO FORT
}                                                                            

void student_new_user() //new user application form, student name, student id
{ 
    HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,06);
    printToxy(22,2," \xdc\xdc    \xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc     \xdc\xdc      \xdc\xdc    \xdc\xdc  \xdc\xdc\xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc\xdc   ");
    printToxy(22,3," \xdc\xdc\xdc   \xdc\xdc  \xdc\xdc      \xdc\xdc     \xdc\xdc      \xdc\xdc    \xdc\xdc  \xdc\xdc     \xdc\xdc      \xdc\xdc    \xdc\xdc  ");
    printToxy(22,4," \xdc\xdc \xdc\xdc \xdc\xdc  \xdc\xdc\xdc\xdc\xdc   \xdc\xdc  \xdc  \xdc\xdc      \xdc\xdc    \xdc\xdc  \xdc\xdc\xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc   \xdc\xdc\xdc\xdc\xdc\xdc\xdc   ");
    printToxy(22,5," \xdc\xdc  \xdc\xdc\xdc\xdc  \xdc\xdc      \xdc\xdc\xdc   \xdc\xdc\xdc      \xdc\xdc    \xdc\xdc     \xdc\xdc  \xdc\xdc      \xdc\xdc  \xdc\xdc    ");
    printToxy(22,6," \xdc\xdc   \xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc     \xdc\xdc      \xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc  \xdc\xdc\xdc\xdc\xdc\xdc  \xdc\xdc   \xdc\xdc   ");
    SetConsoleTextAttribute(h,15); printToxy(22,8," A   P   P   L   I   C   A   T   I   O   N          F   O   R   M"); 
    printToxy(22,10,"Enter Student Name: "); //gotoxy (?,?); scanf(kineso)
    printToxy(22,11,"Enter Student ID: "); //gotoxy (?,?); scanf(kineso)
}

void select_user()
{   
    int i;
    HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,06);
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
    SetConsoleTextAttribute(h,15); printToxy(50,18,"Are you a: ");  //gotoxy (?,?); scanf(kineso)
}