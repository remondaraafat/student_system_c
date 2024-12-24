#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>
#include <conio.h>

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
void loadMenu( Student* ptrStu,int *size,int *numOfStu){
char menu1[5][30]={"Add new student","Search for student","Update Student","Statestics","Quit"};
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
            AddStudent(ptrStu,size,&numOfStu);
    }
    else if(pressed_key=='\r' && selected==1){
        int id;
        printf("Enenter id you searching on:");
        scanf("%d",&id);
        searchDisplayStu(ptrStu,id,numOfStu);
        getchar();
    }
    else if(pressed_key=='\r' && selected==2){
        int id;
        printf("Enenter id you want to update:");
        scanf("%d",&id);
        UpdateStu(ptrStu,id,numOfStu);
    }
    else if(pressed_key=='\r' && selected==3){
        loadSubMenu(ptrStu,size,numOfStu);
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
        displayPassedStu(ptrStu,*numOfStu);
    }
    else if(pressed_key=='\r' && selected==1){
       // changNumOfStu(numOfStu);
        //printf("%d",*numOfStu);
        //getchar();
    }
    }
    while(pressed_key!='\r'||selected!=4);

}

//expand array
void expandArray(Student** ptrStu, int* size, int incrementValue) {
    int newSize = (*size + incrementValue) * 2;
    Student* temp = (Student*)realloc(*ptrStu, newSize * sizeof(Student));
    if (temp == NULL) {
        printf("Failed to expand array memory!\n");
        exit(1);
    }

    *ptrStu = temp; // Update the original pointer
    *size = newSize;
}
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
Student* getStudentById(Student* ptrStu, int id, int numOfStu) {
    for (int j = 0; j < numOfStu; j++) {
        if (id == ptrStu[j].id) {
            return &ptrStu[j]; // Return pointer to the found student.
        }
    }
    return NULL; // Return NULL if not found.
}
//test
void changNumOfStu(int* numOfStu){
*numOfStu+=6;
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
void AddStudent( Student* ptrStu,int* size,int numOfStu){
    int incrementValue;
    printf("\n\nEnter num of Students you want to add:");
    scanf("%d", &incrementValue);
    incrementValue+=numOfStu;
    if(numOfStu>*size){
        expandArray(ptrStu,size,incrementValue);
    }
    for(int j=numOfStu;j<incrementValue;j++){
        //id
        int tempId;
        printf("Enter Student %d id:",j+1);
        scanf("%d",&tempId);
        printf("\n%d",tempId);
        if(getStudentById(ptrStu,tempId,numOfStu)){
            printf("id already exist\n");
            j--;
            continue;
        }
        printf("old num=%d\n",numOfStu);
        numOfStu+=1;
        (numOfStu)++;
        printf("new num=%d\n",numOfStu);
        numOfStu+=1;
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
void searchDisplayStu(Student* ptrStu, int id, int numOfStu){
    printf("Searching for student with ID: %d\n", id);

    // Use getStudentById to find the student
    Student* student = getStudentById(ptrStu, id, numOfStu);

    // Use displayStudent to show the details
    displayStudent(student);
     getchar();
}
//Update Student
void UpdateStu(Student* ptrStu, int id, int numOfStu){
    printf("Searching for student with ID: %d\n", id);

    // Use getStudentById to find the student
    Student* student = getStudentById(ptrStu, id, numOfStu);

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
void displayPassedStu(Student* ptrStu,int numOfStu){
    printf("\npassed students");
    bool passed=false;


    for (int j = 0; j < 1; j++) {
        // Debugging: Check if the student's name is properly initialized
        printf("Debug: Student Name: %s, Grade: %c numner:%d\n", ptrStu[j].stuName, ptrStu[j].grade,numOfStu);

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
int main()
{
    int size=20;
    int numOfStu=0;
    Student *ptrStu = (Student *)malloc(size * sizeof(Student));

    if (ptrStu == NULL) {
        printf("Memory allocation failed for students!\n");
        return 1;
    }
    loadMenu(&ptrStu,&size,&numOfStu);
    printf("\n");
    SetColor(2);



   // AddStudent(ptrStu,&size,&numOfStu);
    //printf("%d",numOfStu);
    //int id=2;
    //searchDisplayStu(ptrStu,id,&numOfStu);
    //UpdateStu(ptrStu,id,&numOfStu);

    //passed
      //  ptrStu[j].passed = (ptrStu[j].grade != 'F');
     // printf("Passed: %s\n", student->passed ? "Yes" : "No");
        //printf("isPassed: %s\n", ptrStu[j].passed ? "yes" : "no");

    return 0;
}
