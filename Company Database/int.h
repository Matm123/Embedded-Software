#ifndef INT_H_INCLUDED
#define INT_H_INCLUDED
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#define MAX_FIELD_LENGTH 150
#define MAX_EMP_REC_LENGTH 750
#define MAX_EMP_NUMBER 1000

char IsDateValid(char* s);
char IsNameValid(char* s);
char IsEmailValid(char* s);
char IsNumberValid(char* s);
char IsJobTiltleExist (char*);
char IsFieldEmpty (char* s);
char* JobsOptimization(char* s);
char* NameOptimization(char* s);
char* NameCapFirst(char* s);
char datecmp (char*,char*);
void SAVE_DataBase(void);
void LOAD_DataBase(void);
void ADD_Record(void);
void SEARCH_Record(void);
void SORT_Database(void);
void DELETE_Record(void);
void MODIFY_Record(void);
void DISPLAY_DataBase(void);
void SORT_ALPHAPITICAL(void);
void SelectionMenu(void);


#endif // INT_H_INCLUDED
