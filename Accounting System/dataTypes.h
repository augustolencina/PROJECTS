#ifndef DATATYPES_H
#define DATATYPES_H

#define MAX_USERS 100
#define MAX_CLIENTS 100
#define MAX_RECEIPTS 100

typedef struct {
    char userName[50];
    char userPassword[50];
    int isAdmin;
} User;

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char name[50];
    int cuit;
    char adress[100];
    char email[50];
} Client;

typedef struct {
    char type[50];
    int number;          
    Date issueDate;         
    float total;       
    int cuitClient;
} Receipt;

#endif