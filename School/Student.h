#ifndef STUDENT_H_
#define STUDENT_H_

#define NAME_MAX 21
#define PHONE_MAX 12
#define current_student school.NofStudent-1

//Define color codes
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"
//to print in color on console

typedef struct
{
    char name[NAME_MAX];
    unsigned int age;
    char phone[PHONE_MAX];
    char grade;
    int id;
} student_t;

typedef struct
{
    student_t* student;
    int NofStudent;
} school_t;

typedef enum
{
    Add=1,
    Edit,
    Print,
    PrintAll,
    Remove,
    Sort,
    Call,
    Export,
    Import
} Option_t;
typedef enum
{
    Name,
    Phone,
    Age,
    Grade
} valid_t;

void student_application(void);
void student_addNew(void);
student_t* student_search(void);
void student_edit(student_t* pstudent);
void student_print(student_t* pstudent);
void student_printAll(void);
void student_remove(student_t* pstudent);
void student_call(student_t* pstudent);
void student_sort(void);
void selectionSort(int sort_order);
void student_swap(student_t* s1,student_t* s2);
int student_checkParameters(student_t* pstudent, valid_t check);
void export_toFile(void);
void import_fromFile(void);

#endif
