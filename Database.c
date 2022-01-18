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

/*Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "Database.h"

/* Macros */
#define MAX 20

/*
 * The main method of the program where execution starts.
 * It returns 0 - True for EXIT_SUCCESS and complete run
 * It includes function calls and switch menu for operational
 * accomplishments.
 */
int main()
{
    struct employee *linkList;
    char *name;
    char *jobType;
    char gender;
    char choice;
    int age;
    name = malloc(MAX * sizeof(char));
    jobType = malloc(MAX * sizeof(char));
    linkList = NULL;
    printf("\nWelcome to Algonquin Employee Database!\n");

    do
    {
        menuDisplay();
        choice = chooseOption();
        switch (choice)
        {
        case '1':
            while ((getchar()) != '\n')
                ; /*clear buffer*/
            name = getName(name, "Enter employee name: ");
            int length;
            length = strlen((const char *)name);
            if (length < 20)
            {
            }
            else
            {
                while ((getchar()) != '\n')
                    ;
            }
            gender = getGender(gender);
            age = getAge(age);
            jobType = getJobDescription(jobType);
            linkList = insertNode(linkList, name, gender, age, jobType);
            linkList = sortList(linkList);
            while ((getchar()) != '\n')
                ;
            break;
        case '2':
            if (linkList == NULL)
            {
                printf("The database is empty!\n\n");
                while ((getchar()) != '\n')
                    ;
                break;
            }
            while ((getchar()) != '\n')
                ;
            name = getName(name, "\nEnter the name of: ");
            searchList(linkList, name);
            break;
        case '3':
            if (linkList == NULL)
            {
                printf("The database is empty!\n\n");
                while ((getchar()) != '\n')
                    ;
                break;
            }
            displayList(linkList);
            while ((getchar()) != '\n')
                ;
            break;
        case '4':
            while ((getchar()) != '\n')
                ;
            linkList = deleteOrModify(linkList);
            break;
        case '5':
            printf("Thank you for using the database!\n");
            break;
        default:
            printf("Incorrect input! Please retry!\n\n");
        }
    } while (choice != '5');

    return EXIT_SUCCESS;
}
