#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_FIELD_LENGTH 150
#define MAX_EMP_NUMBER 1000
typedef struct          //Structure To hold The employee information
{
    char Name[MAX_FIELD_LENGTH];
    char JobTitle[MAX_FIELD_LENGTH];
    char Email[MAX_FIELD_LENGTH];
    char phoneNumber[MAX_FIELD_LENGTH];
    char BirthDate[MAX_FIELD_LENGTH];
}Employee;


#endif // TYPES_H_INCLUDED
