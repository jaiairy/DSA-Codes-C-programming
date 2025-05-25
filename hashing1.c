#include <stdio.h>
#include <stdlib.h>

typedef struct Student 
{
    int sapid;
    struct Student* next;
} Student;

#define FAMILY_COUNT 10

Student* hashtable[FAMILY_COUNT] = {NULL};

int lastthreedigit(int sapid) 
{
    return sapid % 1000;
}

int sdigitsum(int n) 
{
    int sum;
    do {
        sum = 0;
        while (n > 0) 
        {
            sum += n % 10;
            n /= 10;
        }
        n = sum;
    } while (sum >= 10);
    return sum;
}

int getFamily(int sapid) 
{
    int last3 = lastthreedigit(sapid);
    return sdigitsum(last3);
}

void insertStudent(int sapid) 
{
    int family = getFamily(sapid);

    Student* newstudent = (Student*)malloc(sizeof(Student));
    newstudent->sapid = sapid;
    newstudent->next = hashtable[family];
    hashtable[family] = newstudent;

    printf("Inserted SAP ID %d into family %d\n", sapid, family);
}

void displayfamilies() 
{
    printf("\n--- Family Buckets ---\n");
    for (int i = 0; i < FAMILY_COUNT; i++) 
    {
        printf("Family %d: ", i);
        Student* current = hashtable[i];
        int count = 0;

        while (current != NULL) 
        {
            printf("%d -> ", current->sapid);
            current = current->next;
            count++;
        }

        printf("NULL");

        if (count > 1) {
            printf("  [Collision detected: %d entries]", count);
        }

        printf("\n");
    }
}

int main()
 {
    int n, sapid;

    printf("Enter number of students to insert: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) 
    {
        printf("Enter SAP ID for student %d: ", i + 1);
        scanf("%d", &sapid);
        insertstudent(sapid);
    }

    displayfamilies();

    return 0;
}
