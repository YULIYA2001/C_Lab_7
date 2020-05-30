#pragma once

typedef enum type_of_resource
{
    PEOPLE,
    MATERIAL
} Type;

typedef struct resource
{
    Type type;
    char name[50];
    int amount;
    double cost;
} Resource;

void Create_Resource(Resource* r);

void input_resourse_type(Resource* r);
void input_resourse_name(Resource* r);
void input_resourse_amount(Resource* r);
void input_resourse_cost(Resource* r);
void print_for_project(Resource* r);

void Print_Resourse(Resource* r);
void Change_Resourse(Resource* r);
void Delete_Resourse(Resource* r);
