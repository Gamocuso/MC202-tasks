#include <stdio.h>
#include <string.h>

typedef struct
{
    char code[4];
    char name[101];
} disease;

typedef struct
{
    char name[31];
} patient;

typedef struct
{
    char name[31];
    char crm[7];
} doctor;

typedef struct
{
    patient patient_;
    doctor doctor_;
    disease disease_;
} consult;

int read_doctor_file(doctor list[])
{
    int n, i;
    FILE *fp = fopen("./dados/medicos.txt", "r");

    if (fp == NULL)
    {
        perror("nao foi possivel abrir o arquivo medicos.txt");
        return 1;
    }
    else
    {
        fscanf(fp, "%d", &n);
        for (i = 0; i < n; i++)
        {
            fscanf(fp, "%s %s", list[i].crm, list[i].name);
        }
    }

    fclose(fp);
    return 0;
}

int read_disease_file(disease list[])
{

    int n, i;
    FILE *fp = fopen("./dados/doencas.txt", "r");

    if (fp == NULL)
    {
        perror("nao foi possivel abrir o arquivo doencas.txt");
        return 1;
    }
    else
    {
        fscanf(fp, "%d", &n);
        for (i = 0; i < n; i++)
        {
            fscanf(fp, "%s %[^\n]", list[i].code, list[i].name);
        }
    }

    fclose(fp);
    return 0;
}

patient add_patient(char name[31])
{
    patient new;
    strcpy(new.name, name);
    return new;
}

doctor find_doctor(doctor doc_list[], char crm[])
{

    int i = 0;
    for (i = 0; i < 50; i++)
    {

        if (strcmp(crm, doc_list[i].crm) == 0)
        {
            break;
        }
    }
    return doc_list[i];
}

disease find_disease(disease dis_list[], char code[])
{

    int i;
    for (i = 0; i < 150; i++)
    {

        if (strcmp(code, dis_list[i].code) == 0)
            break;
    }
    return dis_list[i];
}

consult register_consult(doctor doc_list[], disease dis_list[])
{
    consult new;
    char patient_name[31];
    char dis_code[200];
    char crm[7];
    scanf("%s %s %s", patient_name, dis_code, crm);

    new.doctor_ = find_doctor(doc_list, crm);
    new.disease_ = find_disease(dis_list, dis_code);
    new.patient_ = add_patient(patient_name);

    return new;
}

void remove_consult(consult consult_list[], int count)
{
    char patient_name[31];
    scanf("%s", patient_name);
    int find = 0;

    for (int i = 0; i < count; i++)
    {

        if (strcmp(patient_name, consult_list[i].patient_.name) == 0)
        {
            find = 1;
        }

        else if (find)
        {

            consult_list[i - 1] = consult_list[i];
        }
    }
}

void change_consult(consult consult_list[], disease dis_list[], int count)
{
    char patient_name[31];
    char code[4];

    scanf("%s %s", patient_name, code);

    for (int i = 0; i < count; i++)
    {

        if (strcmp(patient_name, consult_list[i].patient_.name) == 0)
        {

            int j;
            for (j = 0; j < 150; j++)
            {
                if (strcmp(code, dis_list[j].code) == 0)
                {
                    consult_list[i].disease_ = dis_list[j];
                    break;
                }
            }

            break;
        }
    }
}

void display_consults(consult consult_list[], int count)
{

    for (int i = 0; i < count; i++)
    {

        consult a = consult_list[i];

        printf("%s atendido por %s: %s\n", a.patient_.name, a.doctor_.name, a.disease_.name);
    }
}

int start_sys(int n, consult consult_list[], doctor doc_list[], disease dis_lsit[])
{

    int i, count = 0;
    char command[10];

    for (i = 0; i <= n;)
    {
        scanf("%s", command);

        if (strcmp(command, "registrar") == 0)
        {
            consult_list[count] = register_consult(doc_list, dis_lsit);
            count++;
            i++;
        }
        else if (strcmp(command, "remover") == 0)
        {
            remove_consult(consult_list, count);
            count--;
            i--;
        }
        else if (strcmp(command, "alterar") == 0)
        {

            change_consult(consult_list, dis_lsit, count);
        }
        else if (strcmp(command, "fechar") == 0)
            break;
    }

    return count;
}

int main()
{
    doctor doc_list[50];
    disease dis_list[150];
    consult consult_list[100];
    char command[10];
    int n, count;

    read_doctor_file(doc_list);
    read_disease_file(dis_list);

    scanf("%s %d", command, &n);

    if (strcmp(command, "abrir") == 0)
        count = start_sys(n, consult_list, doc_list, dis_list);

    display_consults(consult_list, count);

    return 0;
}
