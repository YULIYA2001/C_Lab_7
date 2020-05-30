#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Task.h"

#define MAX_TASK_AMOUNT 40


typedef struct project
{
    int number;                          
    char name[MAX_NAME_LEN];               
    int task_amount;                     
    Task* tasks[MAX_TASK_AMOUNT];          
    int resources_amount;
    Data* begin_data;                    
    Data* end_data;                      
    double cost;                         
} Project;

void Create_Project(Project* p, int project_amount);

void input_project_name(Project* p);
void add_task_to_project(Project* p);
void calculate_begin_data(Project* p);
void calculate_end_data(Project* p);
void calculate_cost(Project* p);
void calculate_resources_amount(Project* p);
void print_all_resourses(Project* p);
void change_project_tasks(Project* p);

void Print_Project(Project* p);
void Change_Project(Project* p);
void Delete_Project(Project* p);