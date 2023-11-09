typedef struct
{
    char name[20];
    int age;
    char phone[11];
} person_t;

typedef struct
{
    char name[20];
    int age;
    char grade;
    char phone[11];
	//id
    person_t father;
    person_t mother;
    int NofBrothers;
    person_t *brothers;
} student_t;

typedef struct
{
    student_t* school;
    int NofStudent;
} school;