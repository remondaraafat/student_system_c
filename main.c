#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>
#include <conio.h>
//global variables
int size=100;
int numOfStu=0;
//go to x y function
COORD coord={0,0};                   // this is global variable set to top left 0,0
 void gotoxy(int x,int y)
 {
   coord.X=x;
   coord.Y=y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }
 //set color function
 void SetColor(int ForgC)
 {
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
//structs
struct Subject{
    char subName[50];
    int score;
};
typedef struct Subject Subject;

struct Student{
int id;
char stuName[50];
char grade;
int averageScore;
int numOfsubjects;
Subject* subjects;
};
typedef struct Student Student;
//display menu
char displayMenu(char menu[5][30], int* selected) {
    system("cls");
    char pressed_key;
    for(int i = 0; i < 5; i++) {
        if(i == *selected) {
            gotoxy(1, i);
            SetColor(5);
            printf("->");
        }
        gotoxy(3, i);
        printf("%s", menu[i]);
        SetColor(3);
    }
 pressed_key = getch();
    if(pressed_key == -32) {
        pressed_key = getch();
        switch(pressed_key) {
            case 72: // Up Arrow
                (*selected)--;
                break;
            case 80: // Down Arrow
                (*selected)++;
                break;
        }
    }

    if(*selected > 4) {
        *selected = 0;
    }
    if(*selected < 0) {
        *selected = 4;
    }
    return pressed_key;
}
//load menu
void loadMenu( Student* ptrStu){
char menu1[5][30]={"Add new student","Search for student","Update Student","Statistics","Quit"};
    SetColor(3);
    int selected=0;
    char pressed_key;
   do {
    pressed_key=displayMenu(menu1, &selected);
    if(pressed_key==-32){
        pressed_key=getch();
        switch(pressed_key){
        case 72:
            selected--;
            break;
        case 80:
            selected++;
            break;
        }
    }
    if(selected>4){
        selected=0;
    }
    if (selected<0){
        selected=4;
    }
    //actions on menu item
    if(pressed_key=='\r' && selected==0){
            AddStudent(ptrStu);
    }
    else if(pressed_key=='\r' && selected==1){
        int id;
        printf("Enenter id you searching on:");
        scanf("%d",&id);
        searchDisplayStu(ptrStu,id);
        getchar();
    }
    else if(pressed_key=='\r' && selected==2){
        int id;
        printf("Enenter id you want to update:");
        scanf("%d",&id);
        UpdateStu(ptrStu,id);
    }
    else if(pressed_key=='\r' && selected==3){
        loadSubMenu(ptrStu);
    }
    }
    while(pressed_key!='\r'||selected!=4);
}

//load SubMenu
void loadSubMenu( Student* ptrStu,int *size,int *numOfStu){
char menu2[5][30]={"View passed students","View failed students","View average score","View top performed student","Quit"};
    SetColor(3);
    int selected=0;
    char pressed_key;
    do {
        pressed_key = displayMenu(menu2, &selected);
   // pressed_key=getch();
    if(pressed_key==-32){
        pressed_key=getch();
        switch(pressed_key){
        case 72:
            selected--;
            break;
        case 80:
            selected++;
            break;
        }
    }
    if(selected>4){
        selected=0;
    }
    if (selected<0){
        selected=4;
    }
    //actions on menu item
    if(pressed_key=='\r' && selected==0){
        displayPassedStu(ptrStu);
    }
    else if(pressed_key=='\r' && selected==1){
       displayFailedStu(ptrStu);
    }
    else if(pressed_key=='\r' && selected==2){
        displayAvgScore(ptrStu);
    }
    else if(pressed_key=='\r' && selected==3){
        displayTopStu(ptrStu);
    }
    }
    while(pressed_key!='\r'||selected!=4);

}
//expand array
//void expandArray(Student* ptrStu,int newMaxSize) {
  //int newSize = newMaxSize * 2;
    //Student* temp = (Student*)realloc(ptrStu, newSize * sizeof(Student));
    //if (temp == NULL) {
      //  printf("Failed to expand array memory!\n");
        //return 1;
    //}

    //ptrStu = temp;
    //size = newSize;
//}
//determine grade
char determineGrade(int score) {
    if (score >= 90) {
        return 'A';
    } else if (score >= 80) {
        return 'B';
    } else if (score >= 70) {
        return 'C';
    } else if (score >= 60) {
        return 'D';
    } else {
        return 'F';
    }
}
//get student by id
Student* getStudentById(Student* ptrStu, int id) {
    for (int j = 0; j < numOfStu; j++) {
        if (id == ptrStu[j].id) {
            return &ptrStu[j]; // Return pointer to the found student.
        }
    }
    return NULL; // Return NULL if not found.
}
//test
void changNumOfStu(){
numOfStu+=6;
}
// Function to validate score
int validateScore() {
    int score;
    while (true) {
        scanf("%d", &score);
        if (score >= 0 && score <= 100) {
            return score;
        }
        printf("Enter score between 0 and 100: ");
    }
}
//add function
void AddStudent( Student* ptrStu){
    int newMaxSize;
    printf("\n\nEnter num of Students you want to add:");
    scanf("%d", &newMaxSize);
    newMaxSize+=numOfStu;

    for(int j=numOfStu;j<newMaxSize;j++){
        //id
        int tempId;
        printf("Enter Student %d id:",j+1);
        scanf("%d",&tempId);
        if(getStudentById(ptrStu,tempId)){
            printf("id already exist\n");
            j--;
            continue;
        }

        numOfStu++;
        (ptrStu)[j].id=tempId;
        (ptrStu)[j].averageScore=0;
        (ptrStu)[j].grade='F';
        (ptrStu)[j].numOfsubjects=0;
        strcpy((ptrStu)[j].stuName,"none");
        int sumScore=0;
        //name
        printf("Enter Student %d name:",j+1);
        scanf("%s",(ptrStu)[j].stuName);
        // int numOfsubjects;
        printf("Enter Student %d number of subjects:",j+1);
        scanf("%d",&(ptrStu)[j].numOfsubjects);
        //allocate memory for subjects
          (ptrStu)[j].subjects=(Subject*)malloc((ptrStu)[j].numOfsubjects * sizeof(Subject));

        if ((ptrStu)[j].subjects == NULL) {
            printf("Memory allocation failed for subjects!\n");
            return 1;
        }
        //add the subjects
        for(int i=0;i<(ptrStu)[j].numOfsubjects;i++){
            printf("Enter Student %d subject %d name:",j+1,i+1);
            scanf("%s",(ptrStu)[j].subjects[i].subName);
            //validate on score
            printf("Enter Student %d subject %d score:",j+1,i+1);
            (ptrStu)[j].subjects[i].score = validateScore();
            sumScore+=(ptrStu)[j].subjects[i].score;
        }
        //average score
            (ptrStu)[j].averageScore=sumScore/ (ptrStu)[j].numOfsubjects;

        //grade
        (ptrStu)[j].grade=determineGrade((ptrStu)[j].averageScore);
    }
}

//display student
void displayStudent(Student* student) {
    if (student == NULL) {
        printf("Student not found.\n");
        return;
    }

    // Display ID and Name
    printf("Student ID: %d\n", student->id);
    printf("Student Name: %s\n", student->stuName);

    // Display Subjects
    for (int i = 0; i < student->numOfsubjects; i++) {
        printf("Subject %d Name: %s\n", i + 1, student->subjects[i].subName);
        printf("Subject %d Score: %d\n", i + 1, student->subjects[i].score);
    }

    // Display Average, Grade, and Passed Status
    printf("Average Score: %d\n", student->averageScore);
    printf("Grade: %c\n", student->grade);
}
// search and display student
void searchDisplayStu(Student* ptrStu, int id){
    printf("Searching for student with ID: %d\n", id);

    // Use getStudentById to find the student
    Student* student = getStudentById(ptrStu, id);

    // Use displayStudent to show the details
    displayStudent(student);
     getchar();
}
//Update Student
void UpdateStu(Student* ptrStu, int id){
    printf("Searching for student with ID: %d\n", id);

    // Use getStudentById to find the student
    Student* student = getStudentById(ptrStu, id);

    // Use displayStudent to show the details
    displayStudent(student);
    bool updated=false;
    char tempName[50];
    int tempScore;
    printf("\nEnter the name of the subject ypu want to change it's score");
        scanf("%s",tempName);
        printf("\nEnter subject new score");
       tempScore= validateScore();
        for(int i=0;i< student->numOfsubjects;i++){
          if(strcmp(tempName, student->subjects[i].subName) == 0){
            student->subjects[i].score=tempScore;
            updated=true;
            break;
           }
        }
        if(!updated){
           printf("subject not found\n");
        }
        // Recalculate average score
    int sumScore = 0;
    for (int i = 0; i < student->numOfsubjects; i++) {
        sumScore += student->subjects[i].score;
    }
    student->averageScore = sumScore / student->numOfsubjects;

    // Determine new grade
    student->grade = determineGrade(student->averageScore);
}
//View passed students
void displayPassedStu(Student* ptrStu){
    printf("\npassed students");
    bool passed=false;


    for (int j = 0; j < numOfStu; j++) {
        // Debugging: Check if the student's name is properly initialized

        if (ptrStu[j].grade != 'F') {
            printf("\n %s",ptrStu[j].stuName);
            passed=true;
        }
    }
    if(!passed){
       printf("\n there is no passed students");
    }
    getch();
}
//view failed students
void displayFailedStu(Student* ptrStu){
    printf("\nFailed students");
    bool passed=false;
    for (int j = 0; j < numOfStu; j++) {
        if (ptrStu[j].grade == 'F') {
            printf("\n %s",ptrStu[j].stuName);
            passed=true;
        }
    }
    if(!passed){
       printf("\n there is no failed students");
    }
    getch();
}
//view average
void displayAvgScore(Student* ptrStu){
    if(numOfStu==0){
       printf("\n there is no students");
    }
    int sum=0;
    for (int j = 0; j < numOfStu; j++) {
       sum+=ptrStu[j].averageScore;
    }
    printf("\nAverage Score is: %d",sum/numOfStu);

    getch();
}
//top performance
void displayTopStu(Student* ptrStu){
    if(numOfStu>0){
    Student* topStu;
    topStu=&ptrStu[0];
    int sum=0;
    for (int j = 1; j < numOfStu; j++) {
       if(topStu->averageScore < ptrStu[j].averageScore){
        topStu=&ptrStu[j];
       }
    }
    printf("\nthe 1st top performance in the system is is: \n");
    displayStudent(topStu);
    }
    else{
         printf("\n there is no students");
    }
    getch();
}

int main()
{
    Student *ptrStu = (Student *)malloc(size * sizeof(Student));

    if (ptrStu == NULL) {
        printf("Memory allocation failed for students!\n");
        return 1;
    }
    loadMenu(&ptrStu);
    printf("\n");
    SetColor(2);
    return 0;
}
