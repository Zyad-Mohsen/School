#include <stdio.h>
#include <stdlib.h>
#include "String.h"
#include "Student.h"
#include <unistd.h>

school_t school = { (void*)0, 0 };

void student_application(void)
{
    int option;
    printf("1- Add New Student.\n\n");
    printf("2- Edit Existing Student.\n\n");
    printf("3- Print Student.\n\n");
    printf("4- Print All Students.\n\n");
    printf("5- Remove Student.\n\n");
    printf("6- Sort Students.\n\n");
    printf("7- Call Student.\n\n");
    printf("8- Export Data to External File.\n\n");
    printf("9- Import Data form External File.\n\n");
    printf("Select Option: ");
    scanf("%d",&option);
    system("cls");

    if(school.NofStudent == 0 && (option > 1 && option < 9))
    {
        printf(COLOR_RED"\nDATABASE EMPTY, ADD STUDENTS FIRST!"COLOR_RESET);
    }
    else
    {
        switch(option)
        {
        case Add:
            student_addNew();
            break;
        case Edit:
            student_edit(student_search());
            break;
        case Print:
            student_print(student_search());
            break;
        case PrintAll:
            student_printAll();
            break;
        case Remove:
            student_remove(student_search());
            break;
        case Sort:
            student_sort();
            break;
        case Call:
            student_call(student_search());
            break;
        case Export:
            export_toFile();
            break;
        case Import:
            import_fromFile();
            break;
        default:
            printf(COLOR_RED"Invalid Option. Choose From 1 to 9.\n"COLOR_RESET);
            break;
        }
    }
    printf("\nPRESS ENTER KEY TO GET BACK TO MAIN MENU.\n");
    fflush(stdin);
    getchar();     //WAIT FOR ENTER KEY TO BE PUSHED
    system("cls");
}
void student_addNew(void)
{
    student_t* new_student;

    school.NofStudent++;
    new_student = (student_t*)realloc(school.student,sizeof(student_t)*school.NofStudent);

    if(new_student != (void*)0)
    {
        school.student = new_student;

        do
        {
            printf("Student Name: ");
            string_scan(school.student[current_student].name, NAME_MAX);
        }
        while(!student_checkParameters(school.student+current_student, Name));

        do
        {
            printf("Student Grade: ");
            fflush(stdin);
            scanf("%c",&(school.student[current_student].grade));
            //fflush(stdin);
        }
        while(!student_checkParameters(school.student+current_student, Grade));

        do
        {
            printf("Student Age: ");
            scanf("%d",&(school.student[current_student].age));
        }
        while(!student_checkParameters(school.student+current_student, Age));

        do
        {
            printf("Student Phone: ");
            string_scan(school.student[current_student].phone, PHONE_MAX);
        }
        while(!student_checkParameters(school.student+current_student, Phone));

        school.student[current_student].id = current_student;

        printf(COLOR_GREEN"Student Added Successfully.\n"COLOR_RESET);
    }
    else
    {
        printf(COLOR_RED"Storage Full, Can't Add New Student!\n"COLOR_RESET);
    }
}
student_t* student_search(void)
{
    int search_option=0;
    int search_id=0;
    char str[NAME_MAX];

    printf("Search of Student by: \n\n1- Name\n\n2- ID\n\n");

    do
    {
        scanf("%d",&search_option);

        if(search_option == 1)
        {
            printf("Name of Student? ");
            string_scan(str,NAME_MAX);
            printf("\n");
            int i;
            for(i=0; i<school.NofStudent; i++)
            {
                if(string_compareNotSensetive(str,school.student[i].name))
                {
                    return (school.student+i);
                }
            }
        }
        else if(search_option == 2)
        {
            do
            {
                printf("Enter ID of Student: ");
                scanf("%d",&search_id);
                printf("\n");
                if (search_id > school.NofStudent-1 || search_id < 0)
                {
                    printf(COLOR_RED"This ID Does Not Exist, Try Again!\n"COLOR_RESET);
                }
            }
            while (search_id > school.NofStudent-1 || search_id < 0);

            return (school.student+search_id);
        }
        else
            printf(COLOR_RED"Invalid Option, Try Again.\n"COLOR_RESET);
    }
    while(search_option!=1 && search_option!=2);

    printf(COLOR_RED"This Name Does Not Exist.\n"COLOR_RESET);
    return 0;
}
void student_edit(student_t* pstudent)
{
    int edit_data;
    if(pstudent != (void*)0)
    {
        do
        {
            printf("\nSelect Data to Be Edited: \n\n");
            printf("1- Age\n\n2- Phone\n\n3- Grade\n\n");
            scanf("%d",&edit_data);

            switch(edit_data)
            {
            case 1:
                do
                {
                    printf("Enter New Age: ");
                    scanf("%d",&(pstudent->age));
                }
                while(!student_checkParameters(school.student+current_student, Age));
                break;
            case 2:
                do
                {
                    printf("Enter New Phone: ");
                    string_scan(pstudent->phone,PHONE_MAX);
                }
                while(!student_checkParameters(school.student+current_student, Phone));
                break;
            case 3:
                do
                {
                    printf("Enter New Grade: ");
                    fflush(stdin);
                    scanf("%c",&(pstudent->grade));
                }
                while(!student_checkParameters(school.student+current_student, Grade));
                break;
            default:
                printf(COLOR_RED"Invalid Option, Choose from 1 to 3.\n"COLOR_RESET);
                break;
            }
        }
        while(edit_data != 1 && edit_data != 2 && edit_data != 3 );
        printf(COLOR_GREEN"Student Edited Successfully\n"COLOR_RESET);
    }
}
void student_print(student_t* pstudent)
{
    if (pstudent != (void*)0)
    {
        printf(COLOR_BLUE"+-------------------------------------------------------------------------------+\n"COLOR_RESET);
        printf(COLOR_CYAN"| Name: %-20s | Grade: %c | Age: %2d | ID: %2d | Phone: %-11s |\n"COLOR_RESET, pstudent->name, pstudent->grade, pstudent->age, pstudent->id, pstudent->phone);
        printf(COLOR_BLUE"+-------------------------------------------------------------------------------+\n"COLOR_RESET);
    }
}

void student_printAll(void)
{
    int i;
    for(i=0; i<school.NofStudent; i++)
    {
        student_print(school.student+i);
    }
}
void student_remove(student_t* pstudent)
{
    int i;
    if(pstudent != (void*)0)
    {
        for(i=0; i<school.NofStudent-1; i++)
        {
            *(pstudent+i) = *(pstudent + i +1);
            (pstudent+i)->id--;
        }
        school.NofStudent--;
        school.student = (student_t*)realloc(school.student, school.NofStudent*sizeof(student_t));
    }
    printf(COLOR_GREEN"\nStudent Deleted from Database Successfully."COLOR_RESET);
}
void student_call(student_t* pstudent)
{
    if(pstudent != (void*)0)
    {
        printf(COLOR_GREEN"Calling %s\n"COLOR_RESET,pstudent->phone);
        printf("Ringing");
        int i,j;
        for(i=0; i<3; i++)
        {
            sleep(1);
            for(j=0; j<3; j++)
            {
                printf(".");
                sleep(1);
            }
            for(j=0; j<3; j++)
            {
                printf("\b \b");
            }
        }
        printf(COLOR_RED"\n\nNO ANSWER.\n"COLOR_RESET);
    }
}
void student_sort(void)
{
    int sort_order=0;
    printf("Sort By: \n\n");
    printf("1- Ascending Alphabetical Order\n\n");
    printf("2- Descending Alphabetical Order\n\n");
    printf("3- Highest Grade Order\n\n");
    printf("4- Lowest Grade Order\n\n");
    printf("5- Ascending ID Order\n\n");
    printf("6- Descending ID Order\n\n");
    do
    {
        printf("Sort Option: ");
        scanf("%d",&sort_order);
        if(sort_order >= 1 && sort_order <= 6)
        {
            selectionSort(sort_order);
            printf(COLOR_GREEN"Sorting Done Successfully.\n\n"COLOR_RESET);
            student_printAll();
        }
        else
            printf(COLOR_RED"Invalid Input, Try Again!\n\n"COLOR_RESET);
    }
    while(!(sort_order >= 1 && sort_order <= 6));
}
void selectionSort(int sort_order)
{
    int i, j, min_idx;
    for (i = 0; i < school.NofStudent-1; i++)
    {
        min_idx = i;
        for (j = i+1; j < school.NofStudent; j++)
        {
            switch(sort_order)
            {
            case 1:
                if (*school.student[j].name < *school.student[min_idx].name)
                {
                    min_idx = j;
                }
                break;
            case 2:
                if (*school.student[j].name > *school.student[min_idx].name)
                {
                    min_idx = j;
                }
                break;
            case 3:
                if (school.student[j].grade < school.student[min_idx].grade)
                {
                    min_idx = j;
                }
                break;
            case 4:
                if (school.student[j].grade > school.student[min_idx].grade)
                {
                    min_idx = j;
                }
                break;
            case 5:
                if (school.student[j].id < school.student[min_idx].id)
                {
                    min_idx = j;
                }
                break;
            case 6:
                if (school.student[j].id > school.student[min_idx].id)
                {
                    min_idx = j;
                }
                break;
            }
        }
        if(min_idx != i)
        {
            student_swap(&school.student[min_idx], &school.student[i]);
        }
    }
}
void student_swap(student_t* s1,student_t* s2)
{
    student_t temp;
    temp=*s1;
    *s1=*s2;
    *s2=temp;
}
int student_checkParameters(student_t* pstudent, valid_t check)
{
    int i;
    switch(check)
    {
    case Name:

        for(i=0; pstudent->name[i]; i++)
        {
            if(!((pstudent->name[i] >= 'a' && pstudent->name[i] <= 'z') || (pstudent->name[i] >= 'A' && pstudent->name[i] <= 'Z')))
            {
                printf(COLOR_RED"Invalid Name Input, Only Characters Allowed!\n"COLOR_RESET);
                return 0;
            }
        }
        break;

    case Age:
        if(!(pstudent->age >= 6 && pstudent->age <= 18))
        {
            printf(COLOR_RED"Student Age Should Range from 6 to 18!\n"COLOR_RESET);
            return 0;
        }
        break;

    case Phone:
        for(i=0; pstudent->phone[i]; i++)
        {
            if(!(pstudent->phone[i] >= '0' && pstudent->phone[i] <= '9'))
            {
                printf(COLOR_RED"Invalid Phone Input, Only Numbers Allowed!\n"COLOR_RESET);
                return 0;
            }
        }
        if(i != PHONE_MAX-1)
        {
            printf(COLOR_RED"Phone Number is Less Than 11 Numbers!\n"COLOR_RESET);
            return 0;
        }
        break;

    case Grade:

        if(pstudent->grade == 'E' && pstudent->grade == 'e')
        {
            printf(COLOR_RED"Invalid Grade Input, 'E' is not a Grade!\n"COLOR_RESET);
            return 0;
        }
        if(pstudent->grade >= 'a' && pstudent->grade <= 'f')
        {
            pstudent->grade += 'A'-'a';
        }
        else if(pstudent->grade >= 'A' && pstudent->grade <= 'F')
        {

        }
        else
        {
            printf(COLOR_RED"Invalid Grade Input!\n"COLOR_RESET);
            return 0;
        }
        break;
    }
    return 1;
}
void export_toFile(void)
{
    FILE *file;
    //char data[] = "This is some data that we want to export to a file.";

    // Open the file for writing ("w" mode) - creates the file if it doesn't exist.
    file = fopen("SCHOOL.txt", "w");

    if (file == NULL)
    {
        printf("Failed to open the file for writing.\n");
    }
    fprintf(file, "%d\n",school.NofStudent);
    for(int i=0; i < school.NofStudent; i++)
    {
        // Write the data to the file
        fprintf(file, "%s\n%c\n%d\n%s\n", school.student[i].name,school.student[i].grade,school.student[i].age,school.student[i].phone);
        // Close the file when done
    }
    fclose(file);
    printf(COLOR_GREEN"Exported Successfully!\n"COLOR_RESET);
}
void import_fromFile(void)
{
    FILE *file = fopen("SCHOOL.txt", "r");

    if (file == NULL)
    {
        printf("Failed to open the file for reading.\n");
        return;
    }
    int numStudents;
    if (fscanf(file, "%d", &numStudents) != 1)
    {
        printf("Failed to read the number of students from the file.\n");
        fclose(file);
        return;
    }

    // Expand the school student array to accommodate the new students
    int newTotalStudents = school.NofStudent + numStudents;
    student_t *newStudents = (student_t *)realloc(school.student, sizeof(student_t) * newTotalStudents);

    if (newStudents == NULL)
    {
        printf("Failed to allocate memory for new students.\n");
        fclose(file);
        return;
    }

    school.student = newStudents;

    for (int i = school.NofStudent; i < newTotalStudents; i++)
    {
        student_t *currentStudent = &(school.student[i]);

        if (fscanf(file, "%29s", (school.student+i)->name) != 1)
        {
            printf("Failed to read student name from the file.\n");
            fclose(file);
            return;
        }

        if (fscanf(file, " %c", &((school.student+i)->grade)) != 1)
        {
            printf("Failed to read student grade from the file.\n");
            fclose(file);
            return;
        }

        if (fscanf(file, " %u", &((school.student+i)->age)) != 1)
        {
            printf("Failed to read student age from the file.\n");
            fclose(file);
            return;
        }

        if (fscanf(file, " %11s", (school.student+i)->phone) != 1)
        {
            printf("Failed to read student phone from the file.\n");
            fclose(file);
            return;
        }
        currentStudent->id = i;
    }
    school.NofStudent = newTotalStudents;
    fclose(file);
    printf(COLOR_GREEN"Imported Student Data Successfully!\n"COLOR_RESET);
}

