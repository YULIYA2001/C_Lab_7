#include <stdlib.h>
#include <stdio.h>
#include "Resource.h"


void Create_Resource(Resource* r)
{
    input_resourse_type(r);
    input_resourse_name(r);
    input_resourse_amount(r);
    input_resourse_cost(r);
}

void Print_Resourse(Resource* r)
{
    if(r->type == 0)
        printf_s("��� �������: ��������\n");
    else printf_s("��� �������: ������������\n");
    printf_s("�������� �������: %s\n", r->name);
    printf_s("���������� �������: %d\n", r->amount);
    printf_s("��������� ������� � ���.���.: %.2lf\n\n", r->cost);
}

void Change_Resourse(Resource* r)
{
    char ch;
    int stop = 1;

    printf_s("\n");
    Print_Resourse(r);
    do
    {
        printf_s("\n��� ������ ��������?\n1 - ��������\n2 - ����������\n3  - ���������\n0 - �����\n");
        do
        {
            ch = getch();
            printf_s("\n");
            switch (ch)
            {
                case '1':
                {
                    input_resourse_name(r);
                    break;
                }
                case '2':
                {
                    input_resourse_amount(r);
                    break;
                }
                case '3':
                {
                    input_resourse_cost(r);
                    break;
                }
                case '0':
                {
                    break;
                }
                default:
                {
                    printf_s("�������� ����. ���������� �����: ");
                    stop = 0;
                    break;
                }
            }
        } while (stop == 0);
    } while (ch != '0');
}

void Delete_Resourse(Resource* r)
{
    free(r);
}

void input_resourse_type(Resource* r)
{
    char ch, c;
    int stop;

    printf_s("\n�������� ��� �������: 1 - ��������, 2 - ������������: ");
    do
    {
        stop = 1;
        ch = getch();
        switch (ch)
        {
            case '1':
            {
                r->type = PEOPLE;
                printf_s("\n������ ��������. ");
                break;
            }
            case '2':
            {
                r->type = MATERIAL;
                printf_s("\n������ ������������. ");
                break;
            }
            default:
            {
                printf_s("\n�������� ����. ���������� �����: ");
                stop = 0;
                break;
            }
        }
    } while (stop == 0);
}


void input_resourse_name(Resource* r)
{
    int len;

    printf_s("������� �������� ������� (������������� �����): ");
    fgets(r->name, 50, stdin);
    len = strlen(r->name);
    r->name[len - 1] = '\0';
}


void input_resourse_amount(Resource* r)
{
    int stop;
    char ch;

    printf_s("������� ����������: ");
    do
    {
        stop = 1;
        scanf_s("%d", &(r->amount));
        while ((ch = getchar()) != '\n')  /* ������� ������ ����� + ������������ */
            if (ch != ' ')
                stop = 0;
        if (r->amount < 0 || r->amount > 10000)
            stop = 0;
        if (stop == 0)
            printf_s("�������� ����. 0 < ���������� < 10000. ���������� �����: ");
    } while (stop == 0);
}


void input_resourse_cost(Resource* r)
{
    /* ��� �������� ����� */
    int stop, i, length;
    char str[20], ch;

    printf_s("������� ��������� ������� � ���.���. !!!����� '.' (��. 22.51): ");
    do
    {
        stop = 1;
        scanf_s("%lf", &(r->cost));
        while ((ch = getchar()) != '\n')  /* ������� ������ ����� + ������������ */
            if (ch != ' ')
                stop = 0;
        if (r->cost <= 0)
            stop = 0;
        if (stop == 0)
            printf_s("�������� ����. 0 < ���������. ���������� �����: ");
        else
        {
            /* �������� �� 2 ����� ����� , */
            sprintf_s(str, 20, "%lf", r->cost);
            length = strlen(str);
            for (i = 0; i < length; i++)
            {
                if (str[i] == '.' || str[i] == ',')
                    break;
            }
            if (str[i + 3] != '0')
            {
                printf_s("�������� ����. ��������� �� ����� 2 ������ ����� ','. ���������� �����: ");
                stop = 0;
            }
        }
    } while (stop == 0);
}

void print_for_project(Resource* r)
{
    char type;

    if (r->type == 0)
        type = '�';
    else  type = '�';
    printf_s("%2c\t%15s\t%10d\t%10.2lf\n", type, r->name, r->amount, r->cost);
}