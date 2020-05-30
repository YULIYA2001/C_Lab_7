#pragma once

#include <conio.h>
#include <ctype.h>
#include "project.h"

typedef struct list
{
    Project* project;
    struct list* next;
    struct list* prev;
} List;

List* head, * tail;
int project_amount;

void Add(Project* pr);
void Delete(int value);
void Display_All(void);
void Display_Project(void);
void Delete_All(void);

void add_project_to_list(void);
void delete_project_from_list(void);
void change_project_in_list(void);

