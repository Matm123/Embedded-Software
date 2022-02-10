#define MAX_FIELD_LENGTH 150
#define MAX_EMP_REC_LENGTH 750
#define Delimiter_Constant 2
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
unsigned int TotalNumberOfEmployees = 0;
unsigned int FileNumberOfEmployees = 1;
Employee Employees[MAX_EMP_NUMBER];
char OptimizedJob[MAX_FIELD_LENGTH];
char* temp_name;
char* temp;
char IsSaved;

char datecmp (char* date1,char* date2) //Function that returns 0 if date1 is younger than date2 and returns 1 if date2 is the youngest
{
    int day1,day2,month1,month2,year1,year2;
    day1 = (date1[0] - 48) * 10;
    day1 += (date1[1] - 48);
    month1 = (date1[3] - 48) * 10;
    month1 += (date1[4] - 48);
    year1 = (date1[6] - 48) * 1000;
    year1 += (date1[7] - 48) * 100;
    year1 += (date1[8] - 48) * 10;
    year1 += (date1[9] - 48);

    day2 = (date2[0] - 48) * 10;
    day2 += (date2[1] - 48);
    month2 = (date2[3] - 48) * 10;
    month2 += (date2[4] - 48);
    year2 = (date2[6] - 48) * 1000;
    year2 += (date2[7] - 48) * 100;
    year2 += (date2[8] - 48) * 10;
    year2 += (date2[9] - 48);

    if (year1 > year2)
    {
        return 0;
    }
    else if (year1 < year2)
    {
        return 1;
    }
    else if (year1 == year2 && month1 > month2)
    {
        return 0;
    }
    else if (year1 == year2 && month1 < month2)
    {
        return 1;
    }
    else if (year1 == year2 && month1 == month2 && day1 > day2)
    {
        return 0;
    }
    else if (year1 == year2 && month1 == month2 && day1 < day2)
    {
        return 1;
    }
    else
    {
        return 2;
    }

}
void SORT_ALPHAPITICAL(void)
{
    unsigned int i , j;
    Employee temp;
    for (i=0;i<(TotalNumberOfEmployees-1);++i)
    {
        for (j=i+1;j<(TotalNumberOfEmployees);++j)
        {
            if (strcmp(Employees[j].Name , Employees[i].Name) < 0)
            {
                temp = Employees[i];
                Employees[i] = Employees[j];
                Employees[j] = temp;
            }
        }
    }
}
char* NameCapFirst(char* s)
{
	int i;
	//capitalize first character of words
	for(i=0; s[i]!='\0'; i++)
	{
		//check first character is lowercase alphabet
		if(i==0)
		{
			if((s[i]>='a' && s[i]<='z'))
				s[i]=s[i]-32; //subtract 32 to make it capital
			continue; //continue to the loop
		}
		if(s[i]==' ')//check space
		{
			//if space is found, check next character
			++i;
			//check next character is lowercase alphabet
			if(s[i]>='a' && s[i]<='z')
			{
				s[i]=s[i]-32; //subtract 32 to make it capital
				continue; //continue to the loop
			}
		}
		else
		{
			//all other uppercase characters should be in lowercase
			if(s[i]>='A' && s[i]<='Z')
				s[i]=s[i]+32; //subtract 32 to make it small/lowercase
		}
	}
    return s;
}
char IsFieldEmpty (char* s) //Function that return 1 if the field is Empty and 0 otherwise
{
    unsigned int SpaceCount = 0 , i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == ' ')
            ++SpaceCount;
        ++i;
    }
    if (SpaceCount == strlen(s))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
char* NameOptimization(char* s)
{
    unsigned int i = 0,j = 0;
    temp_name = (char*) malloc(strlen(s)*sizeof(char));
    if (s[0] == ' ')
    {
        ++i;
    }
    else
    {
        temp_name[j] = s[i];
        ++i;
        ++j;
    }
    while (s[i] != '\0')
    {
        if (( (s[i] == ' ') && s[i - 1] != ' ') || (s[i] != ' ' && s[i - 1] == ' ') || (s[i] != ' ' && s[i - 1] != ' '))
        {
            temp_name[j] = s[i];
            ++i;
            ++j;
        }
        else
        {
            ++i;
        }
    }
    temp_name[j] = '\0';
    return temp_name;
}
char* JobsOptimization(char* s) // Function that reads Name and Delete the spaces from it Leaving only one space between words
{
    temp = (char*) malloc(strlen(s) * sizeof(char));
    unsigned int i = 0,j = 0;
    if (s[0] == ' ')
    {
        ++i;
    }
    while (s[i] != '\0')
    {
        if (( (s[i] == ' ') && s[i - 1] != ' ' && (s[i+1] != '\0' && s[i+1] != ' '))  || (s[i] == ' ' && s[i + 1] != ' ' && s[i+1] != '\0') || (s[i] != ' ' && s[i - 1] == ' ') || (s[i] != ' ' && s[i - 1] != ' ' && s[i] != '\n'))
        {
            temp[j] = s[i];
            ++i;
            ++j;
        }
        else
        {
            ++i;
        }
    }
    temp[j] = '\0';
    return temp;
}
char IsDateValid(char* s)  //Function That returns one if the date is invalid and 0 if the date valid
{
    int i,year,month,day;
    if (IsFieldEmpty(s))
    {
        printf("This Field Is required!!\n");
        return 1;
    }
    if (!(strlen(s) <= 10))
    {
        printf("Invalid Date length\n");
        return 1;
    }
    else
    {

        if (s[2] != '/' || s[5] != '/')
        {
            printf("invalid separation!!\n");
            return 1;
        }
        else
        {
            for (i=0;i<10;i++)
            {
                if ( ((s[i] < '0' ) || (s[i] > '9') ) && (s[i] != '/') )
                {
                    printf("Error Containing Special Characters\n");
                    return 1;
                }
            }

            if (i == 10)  //NO INVALID FORMAT ERROR (WE CAN START CHECKING FOR ERRORS IN NUMBERS)
            {
                day = (s[0] - 48) * 10;
                day += (s[1] - 48);

                month = (s[3] - 48) * 10;
                month += (s[4] - 48);

                year = (s[6] - 48) * 1000;
                year += (s[7] - 48) * 100;
                year += (s[8] - 48) * 10;
                year += (s[9] - 48);

                if (year >= 1959 && year <= 1996)
                {
                    if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))       // Leap Year
                    {
                        if (month >= 1 && month <= 12)
                        {
                            if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
                            {
                                if (day >= 1 && day <= 31)
                                    return 0;
                                else
                                {
                                    printf("Please Enter a day between 1 and 31\n");
                                    return 1;
                                }
                            }
                            else if (month == 2)
                            {
                                if (day >= 1 && day <= 29)
                                    return 0;
                                else
                                {
                                    printf("Please Enter a day between 1 and 29\n");
                                    return 1;
                                }
                            }
                            else
                            {
                                if (day >= 1 && day <= 30)
                                    return 0;
                                else
                                {
                                    printf("Please Enter a day between 1 and 30\n");
                                    return 1;
                                }
                            }
                        }
                        else
                        {
                            printf("Please Enter a month between 1 and 12\n");
                            return 1;
                        }
                    }

                    else   // Common Year
                    {
                        if (month >= 01 && month <= 12)
                        {
                            if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
                            {
                                if (day >= 1 && day <= 31)
                                    return 0;
                                else
                                {
                                    printf("Please Enter a day between 1 and 31\n");
                                    return 1;
                                }
                            }
                            else if (month == 2)
                            {
                                if (day >= 1 && day <= 28)
                                    return 0;
                                else
                                {
                                    printf("Please Enter a day between 1 and 28\n");
                                    return 1;
                                }
                            }
                            else
                            {
                                if (day >= 1 && day <= 30)
                                    return 0;
                                else
                                {
                                    printf("Please Enter a day between 1 and 30\n");
                                    return 1;
                                }
                            }
                        }
                        else
                        {
                            printf("Please Enter a month between 1 and 12\n");
                            return 1;
                        }
                    }
                }
                else
                {
                    printf("Please Enter a year between 1959 and 1996\n");
                    return 1;
                }
            }
        }
    }
}
char IsNameValid(char* s) //Function That returns one if the name is invalid and 0 if the name valid
{
    char temp_name[strlen(s)];
    unsigned int i = 0;
    strcpy(temp_name,NameOptimization(s));
    if (IsFieldEmpty(temp_name))
    {
        printf("This Field Is required!!\n");
        return 1;
    }
    while (temp_name[i] != '\0')
    {
        if (temp_name[i] == ' ' || (temp_name[i] >= 'a' && temp_name[i] <= 'z') || (temp_name[i] >= 'A' && temp_name[i] <= 'Z'))
            ++i;
        else
        {
            printf("Invalid Name (Containing Numbers or Special Characters)\n");
            return 1;
        }
    }
    return 0;
}
char IsEmailValid(char* s) //Function That returns one if the Email is invalid and 0 if the name valid
{
    int i = 0,j=0,flag = 0;
    char* yahoo = "@yahoo.com";
    char* gmail = "@gmail.com";
    char temp[strlen(s)];
    if (IsFieldEmpty(s))
    {
        printf("This Field Is required!!\n");
        return 1;
    }
    else if (!((s[0] >= 'A' && s[0] <= 'Z') || (s[0] >= 'a' && s[0] <= 'z')))
    {
        printf("Invalid Email\n");
        return 1;
    }
    while (s[i] != '\0')       // Checks if @ exists in the user entry
    {
        if (s[i] == '@')
        {
            ++flag;
        }
        ++i;
    }
    if (!flag)
    {
        printf("Invalid Email\n");
        return 1;
    }
    else if (flag > 1)
    {
        printf("Invalid Email\n");
        return 1;
    }
    else // @ is there (We can check if the website is yahoo or gmail)
    {
        i = 0;
        while(s[i] != '@')
        {
            if ((s[i] == '.') || (s[i] == '_') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9') )
                ++i;
            else
            {
                printf("Invalid Email\n");
                return 1;
            }
        }
        while (s[i] != '\0')
        {
            temp[j] = s[i];
            ++i;
            ++j;
        }
        temp[j] = '\0';
        if (!strcasecmp(temp,yahoo)  || !strcasecmp(temp,gmail))
        {
            return 0;
        }
        else
        {
            printf("Invalid Email\n");
            return 1;
        }
    }

}
char IsNumberValid(char* s) //Function That returns one if the Number is invalid and 0 if the name valid
{
    int i;
    if (IsFieldEmpty(s))
    {
        printf("This Field Is required!!\n");
        return 1;
    }
    if (strlen(s) > 11)
    {
        printf("Invalid number length!!\n");
        return 1;
    }
    if (strlen(s) < 11)
    {
        printf("Invalid number length!!\n");
        return 1;
    }
    else     //No length error (We can check for errors in numbers)
    {
        for (i=0;i<11;++i)
        {
            if ( ((s[i] < '0' ) || (s[i] > '9') ) )
            {
                printf("Invalid Number Containing special characters!!\n");
                return 1;
            }
        }
    }
    return 0;
}
char IsJobTiltleExist(char* s) //Function That returns one if the job entered is in the job Files and 0 if not
{
    char* Jobs;
    unsigned int i = 0,NumberOfJobs = 0,flag = 0;
    const char delimiter[Delimiter_Constant] = ".";
    char str[MAX_FIELD_LENGTH];
    FILE* temp_jobs = fopen("CompanyDatabase_jobs.txt","r");
    if (IsFieldEmpty(s))
    {
        printf("This field is required!!\n");
        return 1;
    }
    while( fgets (str, MAX_FIELD_LENGTH, temp_jobs)!=NULL )
    {
        if (str[0] == '\n')
        {
            continue;
        }
        else
        {
            ++NumberOfJobs;
        }
    }
    fclose(temp_jobs);
    char* JobsString = (char*) malloc(sizeof(char) * MAX_FIELD_LENGTH * NumberOfJobs);
    char OptimizedJobs[NumberOfJobs][MAX_FIELD_LENGTH];
    temp_jobs = fopen("CompanyDatabase_jobs.txt","r");
    while( fgets (str, MAX_FIELD_LENGTH, temp_jobs)!=NULL )
    {
        if (str[0] == '\n')
        {
            continue;
        }
        else
        {
            if (!flag)
            {
                flag = 1;
                strcpy(JobsString,str);
            }
            else
            {
                strcat(JobsString,str);
            }
        }
    }
    Jobs = strtok(JobsString,delimiter);
    while (Jobs != NULL)
    {
        strcpy(OptimizedJobs[i],JobsOptimization(Jobs));
        if (strcasecmp(OptimizedJobs[i],JobsOptimization(s)) == 0)
        {
            strcpy(OptimizedJob,OptimizedJobs[i]);
            return 0;
        }
        Jobs = strtok(NULL,delimiter);
        ++i;
    }
    free(JobsString);
    printf("Invalid Job Title!!\n");
    return 1;
}
void ADD_Record(void)
{
    IsSaved = 1;
    char EmpName[MAX_FIELD_LENGTH];
    char EmpPhoneNumber[MAX_FIELD_LENGTH];
    char EmpDateOfBirth[MAX_FIELD_LENGTH];
    char EmpEmail[MAX_FIELD_LENGTH];
    char EmpJobTitle[MAX_FIELD_LENGTH];

    do
    {
        printf("Enter the employee name (Max 150 characters) : ");
        fflush(stdin);
        gets(EmpName);
    }while(IsNameValid(EmpName));
    free(temp_name);

    // The Name is valid
    strcpy((Employees[TotalNumberOfEmployees].Name),(NameCapFirst(NameOptimization(EmpName))));
    free(temp_name);

    do
    {
        printf("Enter the employee phone number (Max 11 Numbers) : ");
        fflush(stdin);
        gets(EmpPhoneNumber);
        strcpy(EmpPhoneNumber, NameOptimization(EmpPhoneNumber));
    }while(IsNumberValid(NameOptimization(EmpPhoneNumber)));
    free(temp_name);
    strcpy((Employees[TotalNumberOfEmployees].phoneNumber),NameOptimization(EmpPhoneNumber));
    free(temp_name);

    do
    {
        printf("Enter the employee Birth Date in DD/MM/YYYY : ");
        fflush(stdin);
        gets(EmpDateOfBirth);
        strcpy(EmpDateOfBirth,NameOptimization(EmpDateOfBirth));
        free(temp_name);
    }while(IsDateValid((EmpDateOfBirth)));
    strcpy(Employees[TotalNumberOfEmployees].BirthDate,(EmpDateOfBirth));

    do
    {
        printf("Enter the employee Email Yahoo or Gmail (No Numbers or special at start and only (. _) are allowed) : ");
        fflush(stdin);
        scanf("%s",&EmpEmail);
    }while(IsEmailValid((EmpEmail)));
    strcpy(Employees[TotalNumberOfEmployees].Email,(EmpEmail));

    do
    {
        printf("Enter the employee Job Title (Max 150 characters) : ");
        fflush(stdin);
        gets(EmpJobTitle);
    }while(IsJobTiltleExist(EmpJobTitle));
    free(temp);
    strcpy(Employees[TotalNumberOfEmployees].JobTitle,OptimizedJob);
    printf("The record has been added...Press any key to continue");
    fflush(stdin);
    getchar();
    ++TotalNumberOfEmployees;
}
void LOAD_DataBase(void)
{
    IsSaved = 1;
    FILE* file = fopen("CompanyDatabase.txt","r");
    char* record;
    const char Comma_Delimiter[Delimiter_Constant] = ",";
    char str[MAX_EMP_REC_LENGTH];
    unsigned int i = 1,j = 0,k = 0;
    char temp_rec[MAX_EMP_REC_LENGTH];
    char temp_rec_array[5][150];
    while( fgets (str, MAX_EMP_REC_LENGTH, file)!=NULL )
    {
        if (str[0] == '\n') //Ignoring Empty Lines
        {
            continue;
        }
        else
        {
            while (str[i] != '"')
            {
                temp_rec[j] = str[i];
                ++i;
                ++j;
            }
            temp_rec[j] = '\0';
            record = strtok(temp_rec,Comma_Delimiter);
            while(record != NULL)
            {
                strcpy(temp_rec_array[k],record);
                ++k;
                record = strtok(NULL,Comma_Delimiter);
            }
            /*if (IsNameValid(temp_rec_array[0]))
            {
                printf("The record's %d Name is invalid or empty!!\n",FileNumberOfEmployees);
                i = 1;
                j = 0;
                k = 0;
                FileNumberOfEmployees++;
                free(temp_name);
                continue;
            }
            if (IsNumberValid(NameOptimization(temp_rec_array[1])))
            {
                printf("The record's %d Phone number is invalid or empty!!\n",FileNumberOfEmployees);
                i = 1;
                j = 0;
                k = 0;
                FileNumberOfEmployees++;
                free(temp_name);
                continue;
            }
            if (IsEmailValid(NameOptimization(temp_rec_array[2])))
            {
                printf("The record's %d Email is invalid or empty!!\n",FileNumberOfEmployees);
                i = 1;
                j = 0;
                k = 0;
                FileNumberOfEmployees++;
                free(temp_name);
                continue;
            }
            if (IsDateValid(NameOptimization(temp_rec_array[3])))
            {
                printf("The record's %d Birth Date is invalid or empty!!\n",FileNumberOfEmployees);
                i = 1;
                j = 0;
                k = 0;
                FileNumberOfEmployees++;
                free(temp_name);
                continue;
            }
            if (IsJobTiltleExist(temp_rec_array[4]))
            {
                printf("The record's %d Job Title does not exist or empty!!\n",FileNumberOfEmployees);
                i = 1;
                j = 0;
                k = 0;
                FileNumberOfEmployees++;
                free(temp);
                continue;
            }*/
            strcpy(Employees[TotalNumberOfEmployees].Name,NameCapFirst(NameOptimization(temp_rec_array[0])));
            free(temp_name);
            strcpy(Employees[TotalNumberOfEmployees].phoneNumber,NameOptimization(temp_rec_array[1]));
            free(temp_name);
            strcpy(Employees[TotalNumberOfEmployees].Email,NameOptimization(temp_rec_array[2]));
            free(temp_name);
            strcpy(Employees[TotalNumberOfEmployees].BirthDate,NameOptimization(temp_rec_array[3]));
            free(temp_name);
            strcpy(Employees[TotalNumberOfEmployees].JobTitle,NameOptimization(temp_rec_array[4]));
            free(temp_name);
            i = 1;
            j = 0;
            k = 0;
            /*puts(Employees[TotalNumberOfEmployees].Name);
            puts(Employees[TotalNumberOfEmployees].phoneNumber);
            puts(Employees[TotalNumberOfEmployees].Email);
            puts(Employees[TotalNumberOfEmployees].BirthDate);
            puts(Employees[TotalNumberOfEmployees].JobTitle);*/
            TotalNumberOfEmployees++;
            FileNumberOfEmployees++;
        }
    }
    printf("The company text file has been loaded...Press any key to continue");
    fflush(stdin);
    getchar();

}
void DELETE_Record(void)
{
    IsSaved = 1;
    char scanned_emp_name[MAX_FIELD_LENGTH];
    unsigned int i;
    char IsFound = 0;
    char DSelect;
    unsigned int temp_index;
    if (TotalNumberOfEmployees == 0)
    {
        printf("Nothing To delete (Please Add or LOAD records)\n");
        fflush(stdin);
        getchar();
        return;
    }
    else
    {
        printf("Please enter the employee name to delete : ");
        fflush(stdin);
        gets(scanned_emp_name);
        strcpy(scanned_emp_name, NameOptimization(scanned_emp_name));
        free(temp_name);
        for (i=0;i<TotalNumberOfEmployees;++i)
        {
            if (!strcmp(Employees[i].Name,scanned_emp_name))
            {
                IsFound = 1;
                printf("Are You sure you want to delete this record (Y/N) : ");
                fflush(stdin);
                scanf("%c",&DSelect);
                if (DSelect == 'N' || DSelect == 'n' )
                {
                    printf("Press any key to continue...");
                    fflush(stdin);
                    getchar();
                    return;
                }
                else if (DSelect == 'Y' || DSelect == 'y')
                {
                    if (TotalNumberOfEmployees == 1)  //One Record Only
                    {
                        printf("The record has been deleted...Press any key to continue");
                        fflush(stdin);
                        getchar();
                        TotalNumberOfEmployees = 0;
                    }
                    else if (TotalNumberOfEmployees != 1) //The record at the start
                    {
                        while (i != (TotalNumberOfEmployees - 1))
                        {
                            strcpy(Employees[i].BirthDate , Employees[i+1].BirthDate);
                            strcpy(Employees[i].Email , Employees[i+1].Email);
                            strcpy(Employees[i].JobTitle , Employees[i+1].JobTitle);
                            strcpy(Employees[i].Name , Employees[i+1].Name);
                            strcpy(Employees[i].phoneNumber , Employees[i+1].phoneNumber);
                            i++;
                        }
                        TotalNumberOfEmployees--;
                        printf("The record has been deleted...Press any key to continue");
                        fflush(stdin);
                        getchar();
                        return;
                    }
                    else if (TotalNumberOfEmployees != 1 && i == (TotalNumberOfEmployees - 1))
                    {
                        TotalNumberOfEmployees--;
                        printf("The record has been deleted...Press any key to continue");
                        fflush(stdin);
                        getchar();
                        return;
                    }
                }
                else
                {
                    printf("Invalid Choice...Press any key to continue");
                    fflush(stdin);
                    getchar();
                    return;
                }
            }
        }
        if (!IsFound)
        {
            printf("Cannot find the record you specified...Press any key to continue");
            fflush(stdin);
            getchar();
            return;
        }

    }
}
void DISPLAY_DataBase(void)
{
    unsigned int i;
    if (!TotalNumberOfEmployees)
    {
        printf("No Data Found...Press any key to continue");
        fflush(stdin);
        getchar();
        return;
    }
    for (i=0;i<TotalNumberOfEmployees;++i)
    {
        puts(Employees[i].Name);
        puts(Employees[i].phoneNumber);
        puts(Employees[i].Email);
        puts(Employees[i].BirthDate);
        puts(Employees[i].JobTitle);
        puts("\n");
    }
    printf("Database has been displayed...Press any key to continue");
    fflush(stdin);
    getchar();
}
void SAVE_DataBase(void)
{
    IsSaved = 0;
    unsigned int i;
    SORT_Database();
    FILE* OutputFile = fopen("Output.txt","w");
    for (i=0;i<TotalNumberOfEmployees;++i)
    {
        fprintf(OutputFile,"\"%s, %s, %s, %s, %s\"\n",Employees[i].Name,Employees[i].phoneNumber,Employees[i].Email,Employees[i].BirthDate,Employees[i].JobTitle);
    }
    printf("Database has been saved to Output.txt...Press any key to continue");
    fflush(stdin);
    getchar();
    fclose(OutputFile);
}
void SEARCH_Record(void)
{
    unsigned int i;
    char IsFound = 0;
    char temp[MAX_FIELD_LENGTH];
    printf("Enter the employee name : ");
    fflush(stdin);
    gets(temp);
    strcpy(temp,NameOptimization(temp));
    free(temp_name);
    for (i=0;i<TotalNumberOfEmployees;++i)
    {
        if (!strcmp(temp, Employees[i].Name))
        {
            IsFound = 1;
            puts("\n");
            puts(Employees[i].Name);
            puts(Employees[i].phoneNumber);
            puts(Employees[i].Email);
            puts(Employees[i].BirthDate);
            puts(Employees[i].JobTitle);
            puts("\n");
        }
    }
    if (IsFound)
    {
        printf("Press any key to continue");
        fflush(stdin);
        getchar();
    }

    if (!IsFound)
    {
        printf("Cannot find the record you specified...Press any key to continue");
        fflush(stdin);
        getchar();
        return;
    }

}
void MODIFY_Record(void)
{
    IsSaved = 1;
    unsigned int i;
    char IsFound = 0;
    char temp[MAX_FIELD_LENGTH];
    char temp_field[150];
    unsigned char MSelect;
    if (!TotalNumberOfEmployees)
    {
        printf("Nothing to Modify...Press any key to continue");
        fflush(stdin);
        getchar();
        return;
    }
    printf("Enter the employee name : ");
    fflush(stdin);
    gets(temp);
    strcpy(temp,NameOptimization(temp));
    free(temp_name);
    for (i=0;i<TotalNumberOfEmployees;++i)
    {
        if (!strcmp(temp, Employees[i].Name))
        {
            IsFound = 1;
            do
            {
                printf("Choose the field to modify : \n1.Phone\n2.Job Title\n3.Email\n4.Quit\n");
                fflush(stdin);
                scanf("%d",&MSelect);
                switch (MSelect)
                {
                    case 1:
                    {
                        do
                        {
                            printf("Enter the new phone number : ");
                            fflush(stdin);
                            gets(temp_field);
                            strcpy(temp_field,NameOptimization(temp_field));
                            free(temp_name);
                        }while(IsNumberValid(temp_field));
                        strcpy(Employees[i].phoneNumber , temp_field);
                        break;
                    }
                    case 2:
                    {
                        do
                        {
                            printf("Enter the new Job : ");
                            fflush(stdin);
                            gets(temp_field);
                            strcpy(temp_field,NameOptimization(temp_field));
                            free(temp_name);
                        }while(IsJobTiltleExist(temp_field));
                        strcpy(Employees[i].JobTitle , temp_field);
                        break;
                    }
                    case 3:
                    {
                        do
                        {
                            printf("Enter the new Email : ");
                            fflush(stdin);
                            scanf("%s",&temp_field);
                        }while(IsEmailValid(temp_field));
                        strcpy(Employees[i].Email , temp_field);
                        break;
                    }
                    default :
                    {
                        printf("Invalid Choice...Press any key to continue");
                        fflush(stdin);
                        getchar();
                    }
                }
            }while(MSelect != 4);
        }
    }
    if (IsFound)
    {
        printf("The record you specified has been modified...Press any key to continue");
        fflush(stdin);
        getchar();
    }
    if (!IsFound)
    {
        printf("Cannot find the record you specified...Press any key to continue");
        fflush(stdin);
        getchar();
        return;
    }
}
void SORT_Database(void)
{
    unsigned char SSelect;
    printf("Choose DataBase Saving Order \n1.Sorting by Names from A to Z \n2.Sorting by Names from Z to A \n3.Sorting by ages from the oldest to the youngest \n4.Sorting by ages from the youngest to the oldest\n");
    fflush(stdin);
    scanf("%d",&SSelect);
    switch(SSelect)
    {
        case 1:
        {
            SORT_ALPHAPITICAL();
            break;
        }
        case 2:
        {
            unsigned int i , j;
            Employee temp;
            for (i=0;i<(TotalNumberOfEmployees-1);++i)
            {
                for (j=i+1;j<(TotalNumberOfEmployees);++j)
                {
                    if (strcmp(Employees[j].Name , Employees[i].Name) > 0)
                    {
                        temp = Employees[i];
                        Employees[i] = Employees[j];
                        Employees[j] = temp;
                    }
                }
            }
            break;
        }
        case 3:
        {
            unsigned int i , j;
            Employee temp;
            for (i=0;i<(TotalNumberOfEmployees-1);++i)
            {
                for (j=i+1;j<(TotalNumberOfEmployees);++j)
                {
                    if (datecmp(Employees[j].BirthDate , Employees[i].BirthDate) == 1)
                    {
                        temp = Employees[i];
                        Employees[i] = Employees[j];
                        Employees[j] = temp;
                    }
                }
            }
            break;
        }
        case 4:
        {
            unsigned int i , j;
            Employee temp;
            for (i=0;i<(TotalNumberOfEmployees-1);++i)
            {
                for (j=i+1;j<(TotalNumberOfEmployees);++j)
                {
                    if (!datecmp(Employees[j].BirthDate , Employees[i].BirthDate))
                    {
                        temp = Employees[i];
                        Employees[i] = Employees[j];
                        Employees[j] = temp;
                    }
                }
            }
            break;
        }
        default:
        {
            printf("Invalid Choice...Press any key to continue");
			fflush(stdin);
            getchar();
        }
    }
}
void SelectionMenu()
{
    unsigned char selector;
    char ESelect;
    printf("\t\t\t\tCompany Database\n");
    do
    {
        printf("1.ADD Employee\n2.LOAD Database\n3.DELETE Employee\n4.SAVE Database\n5.SEARCH Employee\n6.MODIFY Employee\n7.QUIT\n8.DISPLAY Database\n");
        printf("Enter your choice: ");
        fflush(stdin);
        scanf("%d",&selector);
        if (selector == 1)
        {
            ADD_Record();
        }
        else if (selector == 2)
        {
            LOAD_DataBase();
        }
        else if (selector == 3)
        {
            DELETE_Record();
        }
        else if (selector == 4)
        {
            SAVE_DataBase();
        }
        else if (selector == 5)
        {
            SEARCH_Record();
        }
        else if (selector == 6)
        {
            MODIFY_Record();
        }
        else if (selector == 7)
        {
            if (IsSaved)
            {
                printf("The Database Has Been Changed, Save the Changes (Y/N) : ");
                fflush(stdin);
                scanf("%c",&ESelect);
                if (ESelect == 'Y' || ESelect == 'y')
                {
                    SAVE_DataBase();
                }
                else if (ESelect == 'N' || ESelect == 'n')
                {

                }
                else
                {
                    printf("Invalid Choice The database will not be saved\n");
                }
            }
            else
            {

            }
        }
        else if (selector == 8)
        {
            DISPLAY_DataBase();
        }
        else
        {
            printf("Invalid choice...Press any key to continue");
            fflush(stdin);
            getchar();
        }
    }while (selector != 7);
}
