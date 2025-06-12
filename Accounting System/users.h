#ifndef USERS_H
#define USERS_H

#include "dataTypes.h"

int loadUser(User users[], const char *usersFilePath);
int saveUser(User users[], int usersAmount, const char *usersFilePath);
int login(User users[], int usersAmount, User *currentUser);
void adminMenu(User users[], int *usersAmount);
void listUsers(User users[], int usersAmount);
void addUser(User users[], int *usersAmount);
void deleteUser(User users[], int *usersAmount);
void modifyUser(User users[], int *usersAmount);

#endif