/*   
 * Title: Assignment 02 Employement Database Management System
 * Course: CST8234 C Language
 * @Author1: Krushang Patel 041021848
 * @Author2: Naijo Palayoer Jose 041003360
 * Lab Section: 012
 * Professor: Surbhi Bahri 
 * Due date: 09th December,2021
 * Submission date: 09th December,2021
 */

/* 
 * Demo malloc(), memset(), calloc() and free() in C, Ansi-style
 * 
 * Status:
 * Requirement #1: Complete 
 * When submitting the files, you MUST follow the name specification as 
 * described in the end of each part of the assignment. Failing to follow 
 * the name specification will result in a penalty of 10 percent reduction 
 * from your final mark.
 * 
 * Requirement #2: Complete
 * If either the name or job description is longer than the specified 
 * maximum length, it should be truncated. That said, allow a maximum of 20 
 * chars.
 * 
 * Requirement #3: Complete
 * Make sure memory used to declare the array size doesn’t get WASTED, 
 * specifically, in case when the database has insufficient memory to hold 
 * the data of the employees
 * 
 * Requirement #4: Complete
 * Your database must not be inefficient in implementing important operations, 
 * especially as the elements of the array are maintained in a specific order 
 * (say names are stored in alphabetical order). If 2 employee names are the same, 
 * then sort them based on their age/gender/profession.
 * 
 * Requirement #5: Complete
 * You must distribute your functions in a meaningful manner across .c and .h files. 
 * The .c files should contain functions that represent sensible groupings of 
 * functionality. You must define .h files as appropriate 
 * 
 * Requirement #6: Complete
 * Each function must have a header comments that explain what it does, and describe 
 * and/or explain its inputs (if any) and return value (if any)
 * 
 * Requirement #7: Complete
 * You must submit makefile, .c and .h files of your properly commented code.
 * 
 * Requirement #8: Complete
 * Your program should present information to the user in clear way. 
 * 
 * Requirement #9 : Complete
 *  Your program should compile with the flags -Wall -ansi –pedantic
 *  
 */

/* Header files required for the program */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/* Macros required for program */
#define MAX 20

/* Structure required for the program with attributes */
struct employee
{
    char empName[MAX];
    char empGender;
    int empAge;
    char jobDescription[MAX];
    struct employee *next;
};

/* Functions required for the program */
char *getName(char name[MAX], char *message);
char getGender(char gender);
int getAge(int age);
char *getJobDescription(char job[MAX]);
int listLength(struct employee *head);
struct employee *insertNode(struct employee *front, char name[MAX], char gender, int age, char job[MAX]);
struct employee *sortList(struct employee *front);
void printNode(struct employee *p);
struct employee *deleteNode(struct employee *head, int indexDelete);
struct employee *swapInfo(struct employee *head);
void searchList(struct employee *head, char name[]);
struct employee *deleteOrModify(struct employee *head);
void displayList(struct employee *head);
void menuDisplay();
char chooseOption();

/* 
 * The method is used to insert the node in the Linked List 
 * Returns the value of front node.
 */
struct employee *insertNode(struct employee *front, char name[MAX], char gender, int age, char job[MAX])
{
    struct employee *p;

    p = (struct employee *)malloc(sizeof(struct employee));

    if (p == NULL)
    {

        printf("\nInsertion failed!\n");

        exit(1);
    }
    p->empAge = age;
    p->empGender = gender;
    strcpy(p->empName, name);
    strcpy(p->jobDescription, job);
    p->next = front;
    front = p;
    return front;
    free(p);
}

/*
 * The method is used to sort Linked List present in the
 * table
 * 
 * Return the front node of the Linked List
 */
struct employee *sortList(struct employee *front)
{
    struct employee *temp = front;
    while (temp != NULL && temp->next != NULL)
    {
        if (strcmp(temp->empName, temp->next->empName) > 0)
        {
            temp = swapInfo(temp);
        }
        else if (strcmp(temp->empName, temp->next->empName) == 0)
        {
            if (temp->empAge > temp->next->empAge)
            {
                temp = swapInfo(temp);
            }
        }
        temp = temp->next;
    }
    return front;
}

/* 
 * The method is used to Swap Information of the Linked List 
 * Returns the value of head node.
 */
struct employee *swapInfo(struct employee *head)
{
    char tempName[MAX], tempGender, tempJob[MAX];
    int tempAge;
    struct employee *temp = head;
    strcpy(tempName, temp->empName);
    strcpy(temp->empName, temp->next->empName);
    strcpy(temp->next->empName, tempName);

    tempAge = temp->empAge;
    temp->empAge = temp->next->empAge;
    temp->next->empAge = tempAge;

    tempGender = temp->empGender;
    temp->empGender = temp->next->empGender;
    temp->next->empGender = tempGender;

    strcpy(tempJob, temp->jobDescription);
    strcpy(temp->jobDescription, temp->next->jobDescription);
    strcpy(temp->next->jobDescription, tempJob);

    return head;
}

/*
 * This method is used to print the information of the Employees 
 * in the Linked List
 */

void printNode(struct employee *p)
{
    printf("Employee Name: %s", p->empName);
    printf("Employee Gender: %c\n", p->empGender);
    printf("Employee Age: %d\n", p->empAge);
    printf("Job Description: %s\n", p->jobDescription);
}

/*
 * This method is used to delete the node from the Linked List
 * according to the valid information.
 * 
 * Returns head node (first node) of the Linked List
 */
struct employee *deleteNode(struct employee *head, int indexDelete)
{
    struct employee *tempPointer = head;
    struct employee *headPointer = head;
    int counter = listLength(head);
    if (indexDelete == 1)
    {
        printf("\n==============\n");
        printNode(head);
        printf("\n==============\n");
        printf("<<<< Deletion Successful >>>>\n");
        head = head->next;
        free(tempPointer);
        return head;
    }
    else if (indexDelete > 1 && indexDelete < counter)
    {
        int i;
        for (i = 2; i < counter; i++)
        {
            headPointer = tempPointer;
            tempPointer = tempPointer->next;
            if (tempPointer == NULL)
            {
                break;
            }
        }

        if (tempPointer != NULL)
        {
            if (tempPointer == head)
            {
                head = head->next;
            }
            headPointer->next = tempPointer->next;
            tempPointer->next = NULL;
            free(tempPointer);
        }
        return head;
    }
    else
    {
        while (tempPointer->next->next != NULL)
        {
            tempPointer = tempPointer->next;
        }
        tempPointer->next = NULL;
        return head;
    }

    return head;
    free(tempPointer);
}

/*
 * This method is used to search the list and retrive the
 * information of the employee
 */
void searchList(struct employee *head, char name[])
{
    struct employee *ptr = head;

    while (ptr != NULL)
    {
        if (strcmp(ptr->empName, name) == 0)
        {
            printf("\n==============\n");
            printNode(ptr);
            printf("\n==============\n");
            printf("<<<< Retrieval Successful >>>>\n");
            return;
        }
        ptr = ptr->next;
    }
    if (ptr == NULL)
    {
        printf("\n%s is not in the database!\n", name);
    }
}

/*
 * The method is used to find the length of the given
 * Linked List
 * 
 * Returns the counter value as the length of the list
 */
int listLength(struct employee *head)
{
    struct employee *temp = head;
    int counter = 0;
    while (temp != NULL)
    {
        counter++;
        printf("[%d]", counter);
        printNode(temp);
        temp = temp->next;
    }
    return counter;
}

/*
 * The method is used to delete or modify the employee
 * entry in the given Linked List
 */
struct employee *deleteOrModify(struct employee *head)
{
    struct employee *pointer = head;
    int index = listLength(head);
    int counter = 0;
    int chooseEmployee = 0;
    if (index > 0)
    {
        do
        {
            printf("------- Modification -------\nTotal Employees: %d\n Choose an employee ID: ", index);
            while (scanf("%d", &chooseEmployee) != 1)
            {
                while ((getchar()) != '\n')
                    ; /*clear buffer*/
                printf("Invalid input! Please retry: ");
            }
            if (chooseEmployee < -1 || chooseEmployee > index)
            {
                while ((getchar()) != '\n')
                    ; /*clear buffer*/
                printf("The ID must be greater than 0 and less than or equal to %d\n", index);
            }
        } while (chooseEmployee < -1 || chooseEmployee > index);
    }

    while (pointer)
    {
        printf("Choose an employee: \n");
        counter++;
        if (counter == chooseEmployee)
        {
            printNode(pointer);
            break;
        }
        pointer = pointer->next;
        printf("\n");
    }

    if (counter > 0)
    {
        int deleteOrModify;
        int check;
        do
        {
            printf("------- Deletion (or) Modification -------\n(1) Delete\n(2) Modify\nChoose an option: ");
            check = scanf("%d", &deleteOrModify);
            if (check != 1)
            {
                while ((getchar()) != '\n')
                    ; /*clear buffer*/
                printf("Invalid input! Please retry: ");
            }
            else if (deleteOrModify > 2 || deleteOrModify < 1)
            {
                printf("Invalid choice! Please retry: ");
            }
        } while (check != 1 || deleteOrModify > 2 || deleteOrModify < 1);

        if (deleteOrModify == 1)
        {
            head = deleteNode(head, chooseEmployee);
            while ((getchar()) != '\n')
                ; /*clear buffer*/
        }
        else
        {
            int option;
            char gender;
            char *name;
            int age;
            char *position;
            name = malloc(MAX * sizeof(char));
            position = malloc(MAX * sizeof(char));

            do
            {
                printf("Which aspect would you like to modify?\n");
                printf("(1) Name\n(2) Gender\n(3) Age\n(4) Job Description\n(5) Exit\nChoose an option: ");
                while (scanf("%d", &option) == 0)
                {
                    printf("Invalid input! Please retry: ");
                    while ((getchar()) != '\n')
                        ; /*clear buffer*/
                }
                while ((getchar()) != '\n')
                    ; /*clear buffer*/

                switch (option)
                {
                case 1:
                    name = getName(name, "Enter the new name of the employee: ");
                    strcpy(pointer->empName, name);
                    break;
                case 2:
                    gender = getGender(gender);
                    pointer->empGender = gender;
                    break;
                case 3:
                    age = getAge(age);
                    pointer->empAge = age;
                    break;
                case 4:
                    position = getJobDescription(position);
                    strcpy(pointer->jobDescription, position);
                    break;
                case 5:
                    printf("===== Returning to main menu =====\n");
                    break;
                default:
                    printf("Invalid input! please retry!\n");
                }
            } while (option != 5);
        }
    }
    else
    {
        printf("The database is empty!\n\n");
    }
    return head;
    free(pointer);
}

/* 
 * This method is used to print the entire Linked List of the given table 
 */
void displayList(struct employee *head)
{
    struct employee *temp = head;
    while (temp != NULL)
    {
        printf("================\nEmployee Database\n================\n");
        printNode(temp);
        temp = temp->next;
    }
}

/* 
 * The method is used to display the Menu 
 */
void menuDisplay()
{
    printf("--- Menu ---\n");
    printf("(1) Insertion\n");
    printf("(2) Search\n");
    printf("(3) Display\n");
    printf("(4) Deletion or Modification\n");
    printf("(5) Terminate\n");
}

/*
 * The method is used to ask for the option for the menu
 * Returns the value of choice enetered by user.
 */
char chooseOption()
{
    char choice;
    printf("\nChoose an option: ");
    switch (choice = getchar())
    {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
        return (choice);
    }
    return choice;
}

/*
 * The method is used to get the name of the employee
 * Returns the name of the employee 
 */
char *getName(char name[MAX], char *message)
{
    printf("%s", message);
    return fgets(name, MAX + 1, stdin);
}

/*
 * The method is used to get the gender of the employee
 * Returns the gender of the employee
 */
char getGender(char gender)
{
    do
    {
        printf("\n---- Gender Choice ----\n(M)ale\n(F)emale\nChoose an option: ");
        scanf("%c", &gender);
        if (tolower(gender) != 'm' && tolower(gender) != 'f')
        {
            printf("Invalid input!\n");
            while ((getchar()) != '\n')
                ; /*clear buffer*/
        }

    } while (tolower(gender) != 'm' && tolower(gender) != 'f');
    return gender;
}

/*
 * The Method is used to get the age of the employee
 * Returns the age of employee entered
 */
int getAge(int age)
{
    int isTrue = -1;
    do
    {
        printf("\nEnter employee age: ");
        isTrue = scanf("%d", &age);
        if (isTrue != 1)
        {
            printf("Invalid input! Please retry!\n");
            age = -1;
        }
        else if (age < 0)
        {
            printf("Invalid entry! Please enter a positive number!\n");
            age = -1;
        }
        while ((getchar()) != '\n')
            ; /*clear buffer*/

    } while (isTrue != 1 || age < 0);

    return age;
}

/*
 * The Method is used to get the job description of the employee
 * Returns the job description enetered
 */
char *getJobDescription(char job[MAX])
{
    printf("Enter employee job description: ");
    return fgets(job, MAX + 1, stdin);
}