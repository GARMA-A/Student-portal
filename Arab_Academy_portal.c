#include <stdio.h>
// #include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32

#else
#include <termios.h>
#include <unistd.h>
#endif
#define NUM_SUBJECTS 7
#define NUM2_SUBJECTS 7
#define MAX_PASSWORD_LENGTH 20
#define MAX_NAME_LEN 30
#define DB_FILE "students.dat"
#define MAX_NAME_LENGTH 100

int getch();
void student();
void doctor();
void lecturer(); // new
void start();
void attendancescince1();
void CourseTablescince1();
void CourseTablescince2();
void timetablescince2();
void timetablescince1();

void displayCourseTable1();
void displayCourseTable3();
void displayCourseTable2();
void displayCourseTable4();
void attendance();
void attendance2();
void timetable();
void timetable2();
void add_student();
void edit_student();
void search_student();
void addDegrees();  // new
void editDegrees(); // new
float GPA();

struct student
{
    int REG;
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
};
typedef struct // new
{
    char registerNumber[MAX_NAME_LENGTH];
    int week7;
    int week12;
    int coursework;
    char subject[50];
    int final;
} Student;
void saveDegrees(Student *student)
{
    FILE *file = fopen("degrees.txt", "a");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }

    fprintf(file, "Register Number: %s\n", student->registerNumber);
    fprintf(file, "Subject Name: %s\n", student->subject);
    fprintf(file, "7: %d\n", student->week7);
    fprintf(file, "12: %d\n", student->week12);
    fprintf(file, "Coursework: %d\n", student->coursework);
    fprintf(file, "Final: %d\n", student->final);
    fprintf(file, "\n");

    fclose(file);
}
int main()
{
    system("color f");
    start();
}

void start()
{
    int choice = 0, choice1 = 0;

    printf("\n\n\t\t\t\t\t===== WELCOME IN OUR PROJECT =====\t\t\t");

    printf("\n\n\n\t\t\t1)Student\t\t2)Doctor\t\t3)Lecturer\t\t4)Exit\n\n");
    scanf("%d", &choice1);
    if (choice1 == 1)
    {
        system("cls");
        student();
    }
    else if (choice1 == 2)
    {
        system("cls");
        doctor();
    }
    else if (choice1 == 3)
    {
        system("cls");
        lecturer();
    }
    else if (choice1 == 4)
    {
        system("cls");
        system("color 4");
        printf("\n\t\t\t\tTHANKS FOR USING OUR SOFTWARE\n");
        system("color f");
        exit(0);
    }
}
void student()
{
    printf("\n\n\t\t\t\t\t======STUDENT PORTAL======\t\t\t");
    int sim = 1000, pass;
    struct student s;
    FILE *fp;
    int reg, found = 0, sm = 0, t12 = 0;
    fp = fopen(DB_FILE, "rb");
    if (fp == NULL)
    {
        system("color 4");
        printf("Error: Unable to open database file.\n");
        system("color f");
        return;
    }
s:
{

    system("cls");
    printf("\t\t\t\n\n\nAre you majoring in 1)science  2)mathematics  :");
    scanf("%d", &sm);
    printf("\t\t\t\n\n\nAre you 1)[TERM 1] OR 2)[TERM 2] : ");
    scanf("%d", &t12);
    printf("\t\t\t\n\n\nEnter your registration number==> ");
    scanf("%d", &reg);
    printf("\t\t\t\n\n\nEnter your PASSWORD==> ");
    scanf("%d", &pass);
    system("cls");
    while (fread(&s, sizeof(struct student), 1, fp) == 1)
    {
        if (s.REG == reg && pass == sim)
        {
            found = 1;
            break;
        }
    }

    fclose(fp);
    system("cls");
}
a:
    if (found == 1)
    {

        

        int op, op2;
        printf("\n\n\n\t\t\t\t1- Show Result\n");
        printf("\t\t\t\t2- Show  Attendance\n");
        printf("\t\t\t\t3- Show my Weekly Table of Courses\n");
        printf("\t\t\t\t4- show my information\n");
        printf("\t\t\t\t5- Calculate GPA \n");
        printf("\t\t\t\t6- EXIT \n");
        printf("\t\t\t\t__________________________________________\n");
        scanf("%d", &op);
        system("cls");

        if (op == 1)
        {

            // 1 - Show my Result =>
            if (t12 == 2)
            {
                printf("\n1 - Show my Current Result\n");
                printf("2 - Show my Semester September 2022 Result\n");
            }
            else if (t12 == 1)
            {
                printf("\n1 - Show my Current Result\n");
            }

            scanf("%d", &op2);
            if (sm == 2)
            {
                if (op2 == 1)
                {
                    system("cls");
                    displayCourseTable1();
                    printf("\t\t\t\tPress any key to Exit\n");
                    system("pause");
                    system("cls");
                    goto a;
                }
                else if (op2 == 2)
                {
                    system("cls");
                    displayCourseTable2();
                    printf("\t\t\t\tPress any key to Exit\n");
                    system("pause");
                    system("cls");
                    goto a;
                }
                else
                {
                    system("cls");
                    system("color 4");
                    printf("Invalid option.\n");
                    system("color f");
                    system("cls");
                    goto a;
                }
            }
            else if (sm == 1)
            {
                if (op2 == 1)
                {
                    system("cls");
                    CourseTablescince1();
                    printf("\t\t\t\tPress any key to Exit\n");
                    system("pause");
                    system("cls");
                    goto a;
                }
                else if (op2 == 2)
                {
                    system("cls");
                    CourseTablescince2();
                    printf("\t\t\t\tPress any key to Exit\n");
                    system("pause");
                    system("cls");
                    goto a;
                }
                else
                {
                    system("cls");
                    system("color 4");
                    printf("Invalid option.\n");
                    system("color f");
                    system("cls");
                    goto a;
                }
            }
        }
        else if (op == 2)
        {
            if (sm == 2)
            {

                system("cls");
                attendance();
                printf("\t\t\t\tPress any key to Exit\n");
                system("pause");
                system("cls");
                goto a;
            }
            if (sm == 1)
            {
                system("cls");
                void attendancescince1();
                printf("\t\t\t\tPress any key to Exit\n");
                system("pause");
                system("cls");
                goto a;
            }
        }

        else if (op == 3)
        {
            if (sm == 2)
            {
                // 3 - Show my Weekly Table of Courses =>
                system("cls");
                timetable();
                printf("\t\t\t\tPress any key to Exit\n");
                system("pause");
                system("cls");
                goto a;
            }
            else if (sm == 1)
            {
                if (t12 == 1)
                {
                    system("cls");
                    timetablescince1();
                    printf("\t\t\t\tPress any key to Exit\n");
                    system("pause");
                    system("cls");
                    goto a;
                }
                else if (t12 == 2)
                {
                    system("cls");
                    timetablescince2();
                    printf("\t\t\t\tPress any key to Exit\n");
                    system("pause");
                    system("cls");
                    goto a;
                }
            }
        }

        else if (op == 4)
        {

            printf("+----------------------+------------------+\n");
            printf("|     Information      |     Details      |\n");
            printf("+----------------------+------------------+\n");
            printf("| Name                 |  %s           |\n", s.name);
            printf("| REG number           |  %d       |\n", s.REG);
            printf("| GPA                  |  %.2f            |\n", s.gpa);
            printf("| Age                  |  %d              |\n", s.age);
            printf("+----------------------+------------------+\n");
            printf("\t\t\t\tPress any key to Exit\n");
            system("pause");
            system("cls");
            goto a;
        }

        else if (op == 5)
        {
            system("cls");
            GPA();
            printf("\t\t\t\tPress any key to Exit\n");
            system("pause");
            system("cls");
            goto a;
        }
        else if (op == 6)
        {
            system("color 4");
            system("pause");
            system("cls");
            system("color f");
            start();
        }
    }
    else if (found == 0)
    {

        system("color 4");
        system("pause");
        system("cls");
        system("color f");
        start();
    }
}
void lecturer()
{
    int choice;
    int REGLEC = 3000;
    int PASSLEC = 3000;
    int rego, passo;
    while (1)
    {
        system("cls");
        printf("\n\n\t\t\t\t\t===== lecturer portal =====\t\t\t");
        printf("\n\nEnter USER==> ");
        scanf("%d", &rego);
        printf("\n\nEnter password==> ");
        scanf("%d", &passo);
        system("cls");
        if (PASSLEC == passo && rego == REGLEC)
        {
            break; // Break the loop and continue with the rest of the program
        }
        else
        {
            printf("Wrong pass or Reg. Please try again.\n");
        }
    }
c:
    system("cls");
    printf("\n\n\n\t\t\t\t1- Add student\n");
    printf("\t\t\t\t2- Edit student\n");
    printf("\t\t\t\t3- Search for student\n");
    printf("\t\t\t\t4- Exit\n");
    printf("\t\t\t\t__________________________________________\n");
    scanf("%d", &choice);
    system("cls");
    if (choice == 1)
    {
        system("cls");
        add_student();
        printf("\t\t\t\tPress any key to Exit\n");
        system("pause");
        system("cls");
        goto c;
    }
    else if (choice == 2)
    {
        system("cls");
        edit_student();
        printf("\t\t\t\tPress any key to Exit\n");
        system("pause");
        system("cls");
        goto c;
    }
    else if (choice == 3)
    {
        system("cls");
        search_student();
        printf("\t\t\t\tPress any key to Exit\n");
        system("pause");
        system("cls");
        goto c;
    }
    else if (choice == 4)
    {
        system("cls");
        start();
        system("cls");
    }
}
void doctor()
{
    int choice;
    int REG = 2000;
    int PASS = 2000;
    int regck, passck;
    while (1)
    {
        system("cls");
        printf("\n\n\t\t\t\t\t======DOCTOR PORTAL======\t\t\t");
        printf("\n\n\nEnter USER : \n");
        scanf("%d", &regck);
        printf("\n\n\nEnter password : \n");
        scanf("%d", &passck);
        system("cls");
        if (PASS == passck && REG == regck)
        {
            break; // Break the loop and continue with the rest of the program
        }
        else
        {
            system("color 4");
            printf("\t\t\t\t\t\n\n\nWrong pass or Reg. Please try again.\n\t\t\t");
            system("pause");
            system("color f");
        }
    }
    do
    {
        system("cls");
        printf("\n\n\t\t\t\t\t======University Doctor - Degrees Management======\t\t\t");
        printf("\n\n\n\t\t\t\t1-Add Degrees \n");
        printf("\t\t\t\t2- Edit Degrees\n");
        printf("\t\t\t\t3- Quit\n");
        printf("\t\t\t\t__________________________________________\n");
        scanf("%d", &choice);
        getchar(); // Consume newline character after scanf
        system("cls");
        switch (choice)
        {
        case 1:
            system("cls");
            addDegrees();
            system("cls");
            break;
        case 2:
            system("cls");
            editDegrees();
            system("cls");
            break;
        case 3:
            system("cls");
            system("color 4");
            system("puse");
            system("color f");
            start();

            break;
        default:
            system("color 4");
            printf("Invalid choice. Please try again.\n");
            system("puse");
            system("color f");
        }
    } while (choice != 3);
}
void add_student()

{

    struct student s;
    FILE *fp;

    // Get student details
    printf("Enter student Reg: ");
    scanf("%d", &s.REG);
    printf("Enter student name: ");
    scanf("%s", s.name);
    printf("Enter student age: ");
    scanf("%d", &s.age);
    printf("Enter student GPA: ");
    scanf("%f", &s.gpa);

    // Open file for appending
    fp = fopen(DB_FILE, "ab");
    if (fp == NULL)
    {
        printf("Error: Unable to open database file.\n");
        return;
    }

    // Write student details to file
    fwrite(&s, sizeof(struct student), 1, fp);

    // Close file
    fclose(fp);

    printf("Student added successfully.\n");
}
void edit_student()
{
    int reg, found = 0;
    struct student s;
    FILE *fp;

    // Get student ID to edit
    printf("Enter student ID to edit:");
    scanf("%d", &reg);

    // Open file for reading and writing
    fp = fopen(DB_FILE, "rb+");
    if (fp == NULL)
    {
        printf("Error: Unable to open database file.\n");
        return;
    }

    // Search for student record
    while (fread(&s, sizeof(struct student), 1, fp) == 1)
    {
        if (s.REG == reg)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        // Get new student details
        printf("Enter new student name: ");
        scanf("%s", s.name);
        printf("Enter new student age: ");
        scanf("%d", &s.age);
        printf("Enter new student GPA: ");
        scanf("%f", &s.gpa);

        // Move file pointer to the beginning of the record
        fseek(fp, (long)(-sizeof(struct student)), SEEK_CUR);
        // Update student record
        fwrite(&s, sizeof(struct student), 1, fp);

        printf("Student record updated successfully.\n");
    }
    else
    {
        printf("Error: Student with REG %d not found.\n", reg);
    }

    // Close file
    fclose(fp);
}
void search_student()
{
    int reg, found = 0;
    struct student s;
    FILE *fp;

    // Get student ID to search for
    printf("Enter student ID to searchfor:");
    scanf("%d", &reg);

    // Open file for reading
    fp = fopen(DB_FILE, "rb");
    if (fp == NULL)
    {
        printf("Error: Unable to open database file.\n");
        return;
    }

    // Search for student record
    while (fread(&s, sizeof(struct student), 1, fp) == 1)
    {
        if (s.REG == reg)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        printf("+----------------------+------------------+\n");
        printf("|     Information      |     Details      |\n");
        printf("+----------------------+------------------+\n");
        printf("| Name                 | %s                \n", s.name);
        printf("| REG number           | %d                \n", s.REG);
        printf("| GPA                  | %.2f              \n", s.gpa);
        printf("| Age                  | %d                \n", s.age);
        printf("+----------------------+------------------+\n");
    }

    else
    {
        printf("Error: Student with REG %d not found.\n", reg);
    }

    // Close file
    fclose(fp);
}
float GPA()
{
    char add;
    int marks[10];
    float total_m = 0, all_s;
    float avg, grade;
    int num_courses;
    printf("\t\t\t\t\t\t\t======Student GPA======\n\n\n\t\t\t");
    printf("\tA+ =====> ( 96 )\tA  =====> ( 94 )\tA- =====> ( 90 )\n\n\n\t\t\t");
    printf("\tB+ =====> ( 86 )\tB  =====> ( 82 )\tB- =====> ( 78 )\n\n\n\t\t\t");
    printf("\tC+ =====> ( 74 )\tC  =====> ( 70 )\tC- =====> ( 66 )\n\n\n\t\t\t");
    printf("\tD+ =====> ( 62 )\tD  =====> ( 57 )\tD- =====> ( 52 ) \n\n\n\t\t\t");
    printf("Enter the number of courses: ");
    scanf("%d", &num_courses);
    for (int i = 1; i <= num_courses; i++)
    {

        printf("\n\n\t\t\t\tEnter marks of the course %d ==>", i);
        scanf("%d", &marks[i - 1]);

        total_m += marks[i - 1];
        all_s = i;
    }
    avg = (total_m / all_s);
    printf("\n\n\t\t\t\tyour average = %5.2f", avg);
    grade = avg;
    printf("\n\n\t\t\t______________________________________________________________________________\n");
    if (grade > 96.00)
    {
        printf("\n\n\t\t\t\t you  got a GPA= 4.0 !!\n");
        printf("\t\t\t\t\t\t\t\t\t\t Your grade is : A+\n\n");
    }
    else if (grade > 92.00 && grade < 96.00)
    {
        printf("\n\n\t\t\t\t you  got a GPA= 3.7 \n");
        printf("\t\t\t\t\t\t\t\t\t\t Your grade is : A\n\n");
    }
    else if (grade > 88.00 && grade < 92.00)
    {
        printf("\n\n\t\t\t\t you  got a GPA= 3.4 \n");
        printf("\t\t\t\t\t\t\t\t\t\t Your grade is : A-\n\n");
    }
    else if (grade > 84.00 && grade < 88.00)
    {
        printf("\n\n\t\t\t\t you got a GPA= 3.2 \n");
        printf("\t\t\t\t\t\t\t\t\t\t Your grade is : B+\n\n");
    }
    else if (grade > 80.00 && grade < 84.00)
    {
        printf("\n\n\t\t\t\t you  a GPA= 3.0 \n");
        printf("\t\t\t\t\t\t\t\t\t\t Your grade is : B\n\n");
    }
    else if (grade > 76.00 && grade < 80.00)
    {
        printf("\n\n\t\t\t\t you  got a GPA= 2.8 \n");
        printf("\t\t\t\t\t\t\t\t\t\t Your grade is : B-\n\n");
    }
    else if (grade > 72.00 && grade < 76.00)
    {
        printf("\n\n\t\t\t\t you  got a GPA= 2.6 \n");
        printf("\t\t\t\t\t\t\t\t\t\t Your grade is : C+\n\n");
    }
    else if (grade > 68.00 && grade < 72.00)
    {
        printf("\n\n\t\t\t\t you a got a GPA= 2.4 \n");
        printf("\t\t\t\t\t\t\t\t\t\t Your grade is : C\n\n");
    }
    else if (grade > 64.00 && grade < 68.00)
    {
        printf("\n\n\t\t\t\t you  got a GPA= 2.2 \n");
        printf("\t\t\t\t\t\t\t\t\t\t Your grade is : C-\n\n");
    }
    else if (grade > 60.00 && grade < 64.00)
    {
        printf("\n\n\t\t\t\t you got a GPA= 2.0 \n");
        printf("\t\t\t\t\t\t\t\t\t\t Your grade is : D+\n\n");
    }
    else if (grade > 55.00 && grade < 60.00)
    {
        printf("\n\n\t\t\t\t you got a GPA= 1.5 \n");
        printf("\t\t\t\t\t\t\t\t\t\t Your grade is : D\n\n");
    }
    else if (grade > 50.00 && grade < 55.00)
    {
        printf("\n\n\t\t\t\t you got a GPA= 1.0 \n");
        printf("\t\t\t\t\t\t\t\t\t\t Your grade is : D-\n\n");
    }
    else if (grade < 50.00)
    {
        printf("\n\n\t\t\t\t you got a GPA= 0 \n");
        printf("\t\t\t\t\t\t\t\t\t\t Your grade is : F\n\n");
    }
    system("pause");
}
int getch()
{
#ifdef _WIN32
    return _getch();
#else
    struct termios old, new;
    int ch;
    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return ch;
#endif
}
// table term 2
void displayCourseTable1()
{
    char *subjects[NUM_SUBJECTS] = {
        "Calculus II",
        "ESP II",
        "Communication",
        "Advanced Physics",
        "Problem Solving",
        "Entrepreneurship",
        "Discrete Structure"};
    int maxMarks[NUM_SUBJECTS] = {30, 20, 10, 30, 10, 20, 10};
    srand(time(NULL));
    int weak7Marks[NUM_SUBJECTS];
    int weak12Marks[NUM_SUBJECTS];
    int courseworkMarks[NUM_SUBJECTS];
    for (int i = 0; i < NUM_SUBJECTS; i++)
    {
        weak7Marks[i] = rand() % (maxMarks[i] + 1);
        weak12Marks[i] = rand() % (maxMarks[i] + 1);
        courseworkMarks[i] = rand() % (maxMarks[i] + 1);
    }
    printf("+---------------------------------------------------------------------------------------------+\n");
    printf("|      Subject      |       weak 7       |       weak 12       |   course work     |     U    |\n");
    printf("+---------------------------------------------------------------------------------------------+\n");
    for (int i = 0; i < NUM_SUBJECTS; i++)
    {
        printf("| %-18s| %-18d| %-18d| %-18d|     -       |\n", subjects[i], weak7Marks[i], weak12Marks[i], courseworkMarks[i]);
    }
    printf("+---------------------------------------------------------------------------------------------+\n");
}
void CourseTablescince2()
{
    char *subjects[NUM_SUBJECTS] = {
        "Calculus I",
        "ESP II",
        "Communication",
        "Advanced Physics",
        "Problem Solving",
        "Entrepreneurship",
        "Discrete Structure"};
    int maxMarks[NUM_SUBJECTS] = {30, 20, 10, 30, 10, 20, 10};
    srand(time(NULL));
    int weak7Marks[NUM_SUBJECTS];
    int weak12Marks[NUM_SUBJECTS];
    int courseworkMarks[NUM_SUBJECTS];
    for (int i = 0; i < NUM_SUBJECTS; i++)
    {
        weak7Marks[i] = rand() % (maxMarks[i] + 1);
        weak12Marks[i] = rand() % (maxMarks[i] + 1);
        courseworkMarks[i] = rand() % (maxMarks[i] + 1);
    }
    printf("+---------------------------------------------------------------------------------------------+\n");
    printf("|      Subject      |       weak 7       |       weak 12       |   course work     |     U    |\n");
    printf("+---------------------------------------------------------------------------------------------+\n");
    for (int i = 0; i < NUM_SUBJECTS; i++)
    {
        printf("| %-18s| %-18d| %-18d| %-18d|     -       |\n", subjects[i], weak7Marks[i], weak12Marks[i], courseworkMarks[i]);
    }
    printf("+---------------------------------------------------------------------------------------------+\n");
}
void CourseTablescince1()
{
    char *subjects[NUM_SUBJECTS] = {
        "Pre Calculus ",
        "ESP I",
        "Computing",
        "Physics",
        "Business",
        "Creativity",
        "INF System"};
    int maxMarks[NUM_SUBJECTS] = {30, 20, 10, 30, 10, 20, 10};
    srand(time(NULL));
    int weak7Marks[NUM_SUBJECTS];
    int weak12Marks[NUM_SUBJECTS];
    int courseworkMarks[NUM_SUBJECTS];
    for (int i = 0; i < NUM_SUBJECTS; i++)
    {
        weak7Marks[i] = rand() % (maxMarks[i] + 1);
        weak12Marks[i] = rand() % (maxMarks[i] + 1);
        courseworkMarks[i] = rand() % (maxMarks[i] + 1);
    }
    printf("+---------------------------------------------------------------------------------------------+\n");
    printf("|      Subject      |       weak 7       |       weak 12       |   course work     |     U    |\n");
    printf("+---------------------------------------------------------------------------------------------+\n");
    for (int i = 0; i < NUM_SUBJECTS; i++)
    {
        printf("| %-18s| %-18d| %-18d| %-18d|     -       |\n", subjects[i], weak7Marks[i], weak12Marks[i], courseworkMarks[i]);
    }
    printf("+---------------------------------------------------------------------------------------------+\n");
}
// gpa less 2
void displayCourseTable3()
{
    char *subjects[5] = {
        "Calculus I",
        "ESP I",
        "Advanced Physics",
        "Problem Solving",
        "Entrepreneurship"};
    int maxMarks[5] = {30, 20, 10, 30, 10};
    srand(time(NULL));
    int weak7Marks[5];
    int weak12Marks[5];
    int courseworkMarks[5];
    for (int i = 0; i < 5; i++)
    {
        weak7Marks[i] = rand() % (maxMarks[i] + 1);
        weak12Marks[i] = rand() % (maxMarks[i] + 1);
        courseworkMarks[i] = rand() % (maxMarks[i] + 1);
    }
    printf("+---------------------------------------------------------------------------------------------+\n");
    printf("|      Subject      |      weak 7       |     weak 12       |   course work     |     U       |\n");
    printf("+---------------------------------------------------------------------------------------------+\n");
    for (int i = 0; i < 5; i++)
    {
        printf("| %-18s| %-18d| %-18d| %-18d|     -       |\n", subjects[i], weak7Marks[i], weak12Marks[i], courseworkMarks[i]);
    }
    printf("+---------------------------------------------------------------------------------------------+\n");
}
// table term 1
void displayCourseTable2()
{
    char *subjects[NUM_SUBJECTS] = {
        "Calculus I",
        "ESP I",
        "Computing",
        "Physics",
        "Business",
        "Creativity",
        "INF System"};
    int maxMarks[NUM_SUBJECTS] = {30, 20, 10, 30, 10, 20, 0};
    srand(time(NULL));
    int weak7Marks[NUM_SUBJECTS];
    int weak12Marks[NUM_SUBJECTS];
    int courseworkMarks[NUM_SUBJECTS];
    // Array to store the final result for each subject
    char finalResult[NUM_SUBJECTS][3];
    for (int i = 0; i < NUM_SUBJECTS; i++)
    {
        weak7Marks[i] = rand() % (maxMarks[i] + 1);
        weak12Marks[i] = rand() % (maxMarks[i] + 1);
        courseworkMarks[i] = rand() % (maxMarks[i] + 1);
        // Generate a random degree for U
        char degrees[] = "AA-C+BADC+A";
        int index = rand() % strlen(degrees);
        strncpy(finalResult[i], degrees + index, 1);
        finalResult[i][1] = '\0';
    }
    printf("+---------------------------------------------------------------------------------------------+\n");
    printf("|      Subject      |       weak 7       |       weak 12       |   course work     |     U    |\n");
    printf("+---------------------------------------------------------------------------------------------+\n");
    for (int i = 0; i < NUM_SUBJECTS; i++)
    {
        printf("| %-18s| %-18d| %-18d| %-18d|  %-7s  |\n", subjects[i], weak7Marks[i], weak12Marks[i], courseworkMarks[i], finalResult[i]);
    }
    printf("+---------------------------------------------------------------------------------------------+\n");
}
void displayCourseTable4()
{
    char *subjects[7] = {
        "Calculus I",
        "ESP I",
        "Computing",
        "Physics",
        "Business",
        "Creativity",
        "INF System"};
    int maxMarks[7] = {30, 20, 10, 30, 10, 20, 0};
    srand(time(NULL));
    int weak7Marks[7];
    int weak12Marks[7];
    int courseworkMarks[7];
    // Array to store the final result for each subject
    char finalResult[7][3];
    for (int i = 0; i < 7; i++)
    {
        weak7Marks[i] = rand() % (maxMarks[i] + 1);
        weak12Marks[i] = rand() % (maxMarks[i] + 1);
        courseworkMarks[i] = rand() % (maxMarks[i] + 1);
        // Set final result as "F" for "Calculus I" and "ESP I"
        if (strcmp(subjects[i], "Calculus I") == 0 || strcmp(subjects[i], "ESP I") == 0)
        {
            strncpy(finalResult[i], "F", 1);
        }
        else
        {
            // Generate a random degree for other subjects
            char degrees[] = "FFCD-CDD";
            int index = rand() % strlen(degrees);
            strncpy(finalResult[i], degrees + index, 1);
        }
        finalResult[i][1] = '\0';
    }
    printf("+---------------------------------------------------------------------------------------------+\n");
    printf("|      Subject      |       weak 7       |       weak 12       |   course work     |     U    |\n");
    printf("+---------------------------------------------------------------------------------------------+\n");
    for (int i = 0; i < 7; i++)
    {
        printf("| %-18s| %-18d| %-18d| %-18d|  %-7s  |\n", subjects[i], weak7Marks[i], weak12Marks[i], courseworkMarks[i], finalResult[i]);
    }
    printf("+---------------------------------------------------------------------------------------------+\n");
}
// attendance table
void attendance()
{
    char *subjects[NUM_SUBJECTS] = {
        "Calculus II",
        "ESP II",
        "Communication",
        "Advanced Physics",
        "Problem Solving",
        "Entrepreneurship",
        "Discrete Structure"};

    float attendance[NUM_SUBJECTS] = {0.0, 3.3, 6.0, 12.0, 0.0, 15.0, 9.0}; // Attendance numbers for each subject
    printf("+---------------------------------+\n");
    printf("|      Subject      |  Attendance |\n");
    printf("+---------------------------------+\n");
    for (int i = 0; i < NUM_SUBJECTS; i++)
    {
        printf("| %-18s|   %-6.1f    |\n", subjects[i], attendance[i]);
    }
    printf("+---------------------------------+\n");
}
void attendancescince1()
{
    char *subjects[NUM_SUBJECTS] = {
        " Pre Calculus ",
        "ESP I",
        "Information System ",
        "Physics",
        "Computing",
    };
    float attendance[NUM_SUBJECTS] = {3.3, 3.3, 15.0, 15.0, 0.0}; // Attendance numbers for each subject
    printf("+---------------------------------+\n");
    printf("|      Subject      |  Attendance |\n");
    printf("+---------------------------------+\n");
    for (int i = 0; i < NUM_SUBJECTS; i++)
    {
        if (subjects[i] != NULL)
        {
            printf("| %-18s|   %-6.1f    |\n", subjects[i], attendance[i]);
        }
    }
    printf("+---------------------------------+\n");
}
void attendance2()
{
    char *subjects[NUM_SUBJECTS] = {
        "Calculus II ",
        "ESP I",
        "Problem solving ",
        " Advance Physics",
        "Enrepernership",
    };
    float attendance[NUM_SUBJECTS] = {3.3, 3.3, 15.0, 15.0, 0.0}; // Attendance numbers for each subject
    printf("+---------------------------------+\n");
    printf("|      Subject      |  Attendance |\n");
    printf("+---------------------------------+\n");
    for (int i = 0; i < NUM_SUBJECTS; i++)
    {
        if (subjects[i] != NULL)
        {
            printf("| %-18s|   %-6.1f    |\n", subjects[i], attendance[i]);
        }
    }
    printf("+---------------------------------+\n");
}
void timetable()
{
    char *daysOfWeek[] = {
        "Saturday",
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday"};

    char *subjectCodes[NUM_SUBJECTS] = {
        "EBA1106",
        "CCS1001",
        "CNC1401",
        "EBA1204",
        "UNR1407",
        "UNR1407",
        "UNR2101"};
    char *subjects[NUM_SUBJECTS] = {
        "Advanced Physics",
        "Discrete Structures",
        "Entrepreneurship Skills",
        "Calculus II",
        "Academic Writing",
        "Academic Writing",
        "Communication  Skills"};
    char *roomNumbers[NUM_SUBJECTS] = {
        "Room # A-106",
        "Room # A-106",
        "Room # Online",
        "Room # H",
        "Room # H",
        "Room # E",
        "Room # A-204"};
    char *timings[NUM_SUBJECTS][2] = {
        {"8:30 AM", "10:30 AM"},
        {"10:30 AM", "12:30 PM"},
        {"6:30 PM", "8:30 PM"},
        {"10:30 AM", "12:30 PM"},
        {"12:30 PM", "2:30 PM"},
        {"2:30 PM", "4:30 PM"},
        {"8:30 AM", "10:30 AM"}};
    char *sections[NUM_SUBJECTS] = {
        "Lect.",
        "Lect.",
        "Lect.",
        "Lect.",
        "Sec.",
        "Sec.",
        "Lect."};
    int dayCounter = 0;
    printf("+-----------------+------------------+------------------+-------------------+----------------------------+\n");
    printf("|       Day       |    Course Start  |    Course End    |     code          |    Subject                 |\n");
    printf("+-----------------+------------------+------------------+-------------------+----------------------------+\n");
    for (int i = 0; i < NUM_SUBJECTS; i++)
    {
        // printf("| %-16s| %-16s | %-16s | %-16s  | %-26s |\n",
        //        daysOfWeek[dayCounter],
        //        timings[i][0],
        //        timings[i][1],
        //        subjectCodes[i],
        //        subjects[i],
        //        roomNumbers[i]);
        dayCounter++;
        if (dayCounter == 7)
        {
            dayCounter = 0;
        }
    }
    printf("+-----------------+------------------+------------------+-------------------+----------------------------+\n");
}
void timetablescince2()
{
    char *daysOfWeek[] = {
        "Saturday",
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday"};

    char *subjectCodes[NUM_SUBJECTS] = {
        "EBA1106",
        "CCS1001",
        "CNC1401",
        "EBA1204",
        "UNR1407",
        "UNR1407",
        "UNR2101"};
    char *subjects[NUM_SUBJECTS] = {
        "Advanced Physics",
        "Discrete Structures",
        "Entrepreneurship Skills",
        "Calculus I",
        "Academic Writing",
        "Academic Writing",
        "Communication  Skills"};
    char *roomNumbers[NUM_SUBJECTS] = {
        "Room # A-106",
        "Room # A-106",
        "Room # Online",
        "Room # H",
        "Room # H",
        "Room # E",
        "Room # A-204"};
    char *timings[NUM_SUBJECTS][2] = {
        {"8:30 AM", "10:30 AM"},
        {"10:30 AM", "12:30 PM"},
        {"6:30 PM", "8:30 PM"},
        {"10:30 AM", "12:30 PM"},
        {"12:30 PM", "2:30 PM"},
        {"2:30 PM", "4:30 PM"},
        {"8:30 AM", "10:30 AM"}};
    char *sections[NUM_SUBJECTS] = {
        "Lect.",
        "Lect.",
        "Lect.",
        "Lect.",
        "Sec.",
        "Sec.",
        "Lect."};
    int dayCounter = 0;
    printf("+-----------------+------------------+------------------+-------------------+----------------------------+\n");
    printf("|       Day       |    Course Start  |    Course End    |     code          |    Subject                 |\n");
    printf("+-----------------+------------------+------------------+-------------------+----------------------------+\n");
    for (int i = 0; i < NUM_SUBJECTS; i++)
    {
        printf("| %-16s| %-16s | %-16s | %-16s  | %-26s |\n",
               daysOfWeek[dayCounter],
               timings[i][0],
               timings[i][1],
               subjectCodes[i],
               subjects[i],
               roomNumbers[i]);
        dayCounter++;
        if (dayCounter == 7)
        {
            dayCounter = 0;
        }
    }
    printf("+-----------------+------------------+------------------+-------------------+----------------------------+\n");
}
void timetablescince1()
{
    char *daysOfWeek[6] = {
        "Saturday",
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday"};

    char *subjectCodes[6] = {
        "EBA1106",
        "CCS1001",
        "CNC1401",
        "UNR1407",
        "EBA1204",
        "UNR2101"};
    char *subjects[6] = {
        "Pre Calculus ",
        "ESP I",
        "Communication",
        "Problem Solving",
        "Advanced Physics",
        "Problem Solving"};
    char *roomNumbers[6] = {
        "Room # A-206",
        "Room # A-106",
        "Room # N",
        "Room # B",
        "Room # A-204",
        "Room # Online"};
    char *timings[6][2] = {
        {"8:30 AM", "10:30 AM"},
        {"6:30 PM", "8:30 PM"},
        {"12:30 PM", "2:30 PM"},
        {"2:30 PM", "4:30 PM"},
        {"8:30 AM", "10:30 AM"},
        {"4:30 PM", "6:30 PM"}};
    char *sections[6] = {
        "Lect.",
        "Lect.",
        "Sec.",
        "Sec.",
        "Lab.",
        "Lect."};
    int dayCounter = 0;
    printf("+-----------------+------------------+------------------+-------------------+----------------------------+\n");
    printf("|       Day       |    Course Start  |    Course End    |     code          |    Subject                 |\n");
    printf("+-----------------+------------------+------------------+-------------------+----------------------------+\n");
    for (int i = 0; i < 6; i++)
    {
        printf("| %-16s| %-16s | %-16s | %-16s  | %-26s |\n",
               daysOfWeek[dayCounter],
               timings[i][0],
               timings[i][1],
               subjectCodes[i],
               subjects[i],
               roomNumbers[i]);
        dayCounter++;
        if (dayCounter == 7)
        {
            dayCounter = 0;
        }
    }
    printf("+-----------------+------------------+------------------+-------------------+----------------------------+\n");
}
void timetable2()
{
    char *daysOfWeek[6] = {
        "Saturday",
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday"};

    char *subjectCodes[6] = {
        "EBA1106",
        "CCS1001",
        "CNC1401",
        "UNR1407",
        "EBA1204",
        "UNR2101"};
    char *subjects[6] = {
        "Calculus I",
        "ESP I",
        "Communication",
        "Problem Solving",
        "Advanced Physics",
        "Problem Solving"};
    char *roomNumbers[6] = {
        "Room # A-206",
        "Room # A-106",
        "Room # N",
        "Room # B",
        "Room # A-204",
        "Room # Online"};
    char *timings[6][2] = {
        {"8:30 AM", "10:30 AM"},
        {"6:30 PM", "8:30 PM"},
        {"12:30 PM", "2:30 PM"},
        {"2:30 PM", "4:30 PM"},
        {"8:30 AM", "10:30 AM"},
        {"4:30 PM", "6:30 PM"}};
    char *sections[6] = {
        "Lect.",
        "Lect.",
        "Sec.",
        "Sec.",
        "Lab.",
        "Lect."};
    int dayCounter = 0;
    printf("+-----------------+------------------+------------------+-------------------+----------------------------+\n");
    printf("|       Day       |    Course Start  |    Course End    |     code          |    Subject                 |\n");
    printf("+-----------------+------------------+------------------+-------------------+----------------------------+\n");
    for (int i = 0; i < 6; i++)
    {
        printf("| %-16s| %-16s | %-16s | %-16s  | %-26s |\n",
               daysOfWeek[dayCounter],
               timings[i][0],
               timings[i][1],
               subjectCodes[i],
               subjects[i],
               roomNumbers[i]);
        dayCounter++;
        if (dayCounter == 7)
        {
            dayCounter = 0;
        }
    }
    printf("+-----------------+------------------+------------------+-------------------+----------------------------+\n");
}
int isValidDegree(int degree, int maxDegree)
{
    return degree >= 0 && degree <= maxDegree;
}
void addDegrees()
{
    system("cls");
    Student student;

    printf("\n\n\t\t\t\t\t======ADD DEGREES======\t\t\t");
    printf("\n\n\nEnter the student's register number: ");
    fgets(student.registerNumber, MAX_NAME_LENGTH, stdin);
    strtok(student.registerNumber, "\n"); // Remove newline character from fgets

    printf("\n\n\nEnter the subject name: ");
    scanf("%s", student.subject);

    int componentChoice;
    printf("\n\n\n\t\t\t\t1- Week 7 (Max Degree: 30\n");
    printf("\t\t\t\t2-Week 12 (Max Degree: 20) \n");
    printf("\t\t\t\t3- Coursework (Max Degree: 10)\n");
    printf("\t\t\t\t4- Final (Max Degree: 40)\n");
    printf("\t\t\t\t__________________________________________\n");
    scanf("%d", &componentChoice);

    switch (componentChoice)
    {
    case 1:
        do
        {
            printf("\t\t\nWeek 7: ");
            scanf("%d", &student.week7);
            if (!isValidDegree(student.week7, 30))
            {
                system("color 4");
                printf("Invalid degree. Please enter a value between 0 and 30.\n");
                system("color f");
            }
        } while (!isValidDegree(student.week7, 30));
        break;
    case 2:
        do
        {
            printf("Week 12: ");
            scanf("%d", &student.week12);
            if (!isValidDegree(student.week12, 20))
            {
                system("color 4");
                printf("Invalid degree. Please enter a value between 0 and 20.\n");
                system("color f");
            }
        } while (!isValidDegree(student.week12, 20));
        break;
    case 3:
        do
        {
            printf("Coursework: ");
            scanf("%d", &student.coursework);
            if (!isValidDegree(student.coursework, 10))
            {
                system("color 4");
                printf("Invalid degree. Please enter a value between 0 and 10.\n");
                system("color f");
            }
        } while (!isValidDegree(student.coursework, 10));
        break;
    case 4:
        do
        {
            printf("Final: ");
            scanf("%d", &student.final);
            if (!isValidDegree(student.final, 40))
            {
                system("color 4");
                printf("Invalid degree. Please enter a value between 0 and 40.\n");
                system("color f");
            }
        } while (!isValidDegree(student.final, 40));
        break;
    default:
        system("color 4");
        printf("Invalid component choice.\n");
        system("color f");
        return;
    }
    saveDegrees(&student);

    printf("Degrees added successfully.\n");
}
void editDegrees()
{
    char subject[50];
    int week7, week12, coursework, final;

    printf("\t\t\t\n\n\nEnter the subject name: ");
    scanf("%s", &subject);

    FILE *file = fopen("degrees.txt", "r");
    if (file == NULL)
    {
        system("color 4");
        printf("Error opening the file.\n");
        system("color f");
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        system("color 4");
        printf("Error creating temporary file.\n");
        system("color f");
        fclose(file);
        return;
    }

    int found = 0;
    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strstr(line, "Subject:") != NULL && strstr(line, subject) != NULL)
        {
            found = 1;
            fputs(line, tempFile);

            fgets(line, sizeof(line), file);
            sscanf(line, "Week 7: %d", &week7);
            printf("Current Week 7: %d\n", week7);
            do
            {
                printf("Enter new Week 7: ");
                scanf("%d", &week7);
                if (!isValidDegree(week7, 30))
                {
                    printf("Invalid degree. Please enter a value between 0 and 30.\n");
                }
            } while (!isValidDegree(week7, 30));
            fprintf(tempFile, "Week 7: %d\n", week7);

            // Similarly, modify prompts and input for Week 12, Coursework, and Final components
        }
        else
        {
            fputs(line, tempFile);
        }
    }
    fclose(file);
    fclose(tempFile);

    if (!found)
    {
        printf("Student not found.\n");
        remove("temp.txt");
        return;
    }

    remove("degrees.txt");
    rename("temp.txt", "degrees.txt");

    printf("Degrees edited successfully.\n");
}
