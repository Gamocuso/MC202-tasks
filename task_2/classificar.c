#include <stdio.h>
#include <string.h>

typedef struct
{
    char firstName[31];
    char lastName[31];
} patient;

patient read_patient()
{

    patient a;
    char fullName[31];
    int _index = 0;

    scanf("%s ", fullName);

    for (int i = 0; fullName[i] != '\0'; i++)
    {

        if (fullName[i] == '_')
        {
            _index = i + 1;
            a.firstName[i] = '\0';
            continue;
        }
        else if (fullName[i + 1] == '\0')
        {
            a.lastName[i - _index + 1] = '\0';
        }

        if (!_index)
        {
            a.firstName[i] = fullName[i];
        }
        else
        {
            a.lastName[i - _index] = fullName[i];
        }
    }

    return a;
}

void read_patients_list(patient list[], int n)
{

    for (int i = 0; i < n; i++)
    {
        list[i] = read_patient();
    }
}

void classify(patient list[], int n)
{
    char filter[10];
    char compareName[31];
    scanf("%s %s", filter, compareName);

    for (int i = 0; i < n; i++)
    {

        if (strcmp(filter, "homonimos") == 0)
        {

            if (strcmp(list[i].firstName, compareName) == 0)
            {
                printf("%s_%s\n", list[i].firstName, list[i].lastName);
            }
        }
        else
        {
            if (strcmp(list[i].lastName, compareName) == 0)
            {

                printf("%s_%s\n", list[i].firstName, list[i].lastName);
            }
        }
    }
}

int main()
{

    int n;
    patient list[100];

    scanf("%d", &n);

    read_patients_list(list, n);

    classify(list, n);

    return 0;
}
