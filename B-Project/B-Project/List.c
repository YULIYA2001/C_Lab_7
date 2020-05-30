#include <stdio.h>
#include <stdlib.h>
#include "List.h"

extern List* head = NULL, * tail = NULL;

void Add(Project* pr)
{
    List* p, * cur = head;

    p = (List*)malloc(sizeof(List));       /* �������� ������ �������� */
    if (p != NULL)
    {
        p->project = pr;
        p->next = p->prev = NULL;
        if (head == NULL)
        {
            head = tail = p;        /*head � tail ��������� �� ��������� �������*/
            return;
        }
        tail->next = p;
        p->prev = tail;
        tail = p;
    }
}

void add_project_to_list(void)
{
    Project* pr;
    project_amount++;
    pr = (Project*)malloc(sizeof(Project));
    Create_Project(pr, project_amount);
    Add(pr);
}

void delete_project_from_list(void)
{
    int i = 0, stop;
    char c;
    List* p = head;

    printf_s("����� ������ ������ �������?\n");
    while (p != NULL)
    {
        printf_s("%d - ������ �%d (��������: %s)\n", ++i, i, p->project->name);
        p = p->next;
    }
    do
    {
        stop = 1;
        scanf_s("%d", &i);
        while ((c = getchar()) != '\n')  /* ������� ������ ����� + ������������ */
            if (c != ' ')
                stop = 0;
        if (stop == 0)
            printf_s("�������� ����. ���������� �����: ");
    } while (stop == 0);
    if(i <= 0 || i > project_amount)
        printf_s("����� ������ �� ������.\n");
    else
    {
        Delete(i);
        printf("������ ������\n");
    }
}

void Delete(int value)
{
    List* p = head;
    int i = 0;

    /* ����� �������, ���������� �������� �������� */
    while (p != NULL && p->project->number != value)
        p = p->next;
    if (p == NULL)      /* ���� ������� �� ������ */
        return;     
    if (p == head)      /* ���� ����� ������� ������ ��. */
    {
        head = head->next;
        if (head == NULL)
        {
            tail = NULL;
            project_amount = 0;
        }
        else
        {
            head->prev = NULL;
            project_amount--;
        }
    }
    else if (p == tail) /* ���� ����� ������� ��������� ������� */
    {
        tail = tail->prev;
        tail->next = NULL;
        project_amount--;
    }
    else     /* ���� ����� ������� ������� � �������� ������ */
    {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        project_amount--;
    }
    Delete_Project(p->project);
    free(p);
    p = head;
    /* ������������� ������� */
    while (p != NULL)
    {
        p->project->number = ++i;
        p = p->next;
    }
}

void Delete_All(void) 
{
    List* p = head;
    List* next = NULL;

    while (p != NULL) 
    {
        next = p->next;
        free(p);
        p = next;
    }
    head = tail = NULL;
}

void Display_All(void)
{
    List* p = head;

    system("cls");
    if (p == NULL)
        puts("������ ����");
    else
    {
        while (p != NULL)
        {
            Print_Project(p->project);
            printf_s("\n\n\n\n");
            p = p->next;
        }    
    }
}

void Display_Project(void)
{
    int i = 0, stop;
    char c;
    List* p = head;

    printf_s("����� ������ ������ �����������?\n");
    while (p != NULL)
    {
        printf_s("%d - ������ �%d (��������: %s)\n", ++i, i, p->project->name);
        p = p->next;
    }
    do
    {
        stop = 1;
        scanf_s("%d", &i);
        while ((c = getchar()) != '\n')  /* ������� ������ ����� + ������������ */
            if (c != ' ')
                stop = 0;
        if (stop == 0)
            printf_s("�������� ����. ���������� �����: ");
    } while (stop == 0);
    p = head;
    /* ����� �������, ���������� �������� �������� */
    while (p != NULL && p->project->number != i)
        p = p->next;
    if (p == NULL)
        printf_s("����� ������ �� ������.\n");
    else
        Print_Project(p->project);
}

void change_project_in_list(void)
{
    int i = 0, stop;
    char c;
    List* p = head;

    printf_s("����� ������ ������ ��������?\n");
    while (p != NULL)
    {
        printf_s("%d - ������ �%d (��������: %s)\n", ++i, i, p->project->name);
        p = p->next;
    }
    do
    {
        stop = 1;
        scanf_s("%d", &i);
        while ((c = getchar()) != '\n')  /* ������� ������ ����� + ������������ */
            if (c != ' ')
                stop = 0;
        if (stop == 0)
            printf_s("�������� ����. ���������� �����: ");
    } while (stop == 0);
    p = head;
    /* ����� �������, ���������� �������� �������� */
    while (p != NULL && p->project->number != i)
        p = p->next;
    if (p == NULL)
        printf_s("����� ������ �� ������.\n");
    else
        Change_Project(p->project);
}