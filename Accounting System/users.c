#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "users.h"

int loadUser(User users[], const char* usersFilePath) {
    FILE *file = fopen(usersFilePath, "r");
    if (!file) {
        printf("Archivo de usuarios no encontrado, creando uno nuevo...\n");
        file = fopen(usersFilePath, "w");
        if (!file) {
            printf("Error al crear archivo de usuarios.\n");
            return 0;
        }
        fprintf(file, "admin admin123 1\n");
        fclose(file);
        
        strcpy(users[0].userName, "admin");
        strcpy(users[0].userPassword, "admin123");
        users[0].isAdmin = 1;
        return 1;
    }

    int counter = 0;
    while (counter < MAX_USERS && 
           fscanf(file, "%49s %49s %d", 
                  users[counter].userName, 
                  users[counter].userPassword, 
                  &users[counter].isAdmin) == 3) {
        counter++;
    }
    fclose(file);

    if (counter == 0) {
        printf("Archivo de usuarios vacío, creando usuario admin...\n");
        strcpy(users[0].userName, "admin");
        strcpy(users[0].userPassword, "admin123");
        users[0].isAdmin = 1;
        return 1;
    }

    printf("Se cargaron %d usuarios correctamente\n", counter);
    return counter;
}

int saveUser(User users[], int usersAmount, const char *usersFilePath) {
    FILE *file = fopen(usersFilePath, "w");
    if (!file) return 0;

    for (int i = 0; i < usersAmount; i++) {
        fprintf(file, "%s %s %d\n", 
                users[i].userName, 
                users[i].userPassword, 
                users[i].isAdmin);
    }
    fclose(file);
    return 1;
}

int login(User users[], int usersAmount, User *currentUser) {
    char name[50];
    char password[50];

    printf("      === INICIO DE SESION ===\n");
    printf("Usuario: ");
    scanf("%49s", name);
    printf("Contrasena: ");
    scanf("%49s", password);

    for (int i = 0; i < usersAmount; i++) {
        if (strcmp(name, users[i].userName) == 0 &&
            strcmp(password, users[i].userPassword) == 0) {
            *currentUser = users[i];
            printf("Bienvenido %s!\n", name);
            return 1;
        }
    }

    printf("Usuario o contrasena incorrectos.\n");
    return 0;
}

void listUsers(User users[], int usersAmount) {
    if (usersAmount <= 0) {
        printf("No hay usuarios para mostrar.\n");
        return;
    }
    
    printf("\n--- LISTADO DE USUARIOS ---\n");
    for (int i = 0; i < usersAmount; i++) {
        printf("%d. Nombre: %s - Tipo: %s\n", 
               i+1, 
               users[i].userName, 
               users[i].isAdmin ? "Admin" : "Usuario");
    }
    printf("---------------------------\n");
}

void addUser(User users[], int *usersAmount) {
    if (*usersAmount >= MAX_USERS) {
        printf("Limite de usuarios alcanzado.\n");
        return;
    }

    printf("\n--- NUEVO USUARIO ---\n");
    printf("Nombre de usuario: ");
    scanf("%49s", users[*usersAmount].userName);
    printf("Contrasena: ");
    scanf("%49s", users[*usersAmount].userPassword);
    printf("¿Es administrador? (1=Si, 0=No): ");
    scanf("%d", &users[*usersAmount].isAdmin);

    (*usersAmount)++;
    saveUser(users, *usersAmount, "users.txt");
    printf("Usuario agregado correctamente.\n");
}

void deleteUser(User users[], int *usersAmount) {
    if (*usersAmount == 0) {
        printf("No hay usuarios registrados.\n");
        return;
    }

    char name[50];
    printf("\n--- ELIMINAR USUARIO ---\n");
    printf("Ingrese el nombre de usuario a eliminar: ");
    scanf("%49s", name);

    int index = -1;
    for (int i = 0; i < *usersAmount; i++) {
        if (strcmp(users[i].userName, name) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Usuario no encontrado.\n");
        return;
    }

    char confirmation;
    printf("¿Está seguro de eliminar al usuario %s? (s/n): ", name);
    scanf(" %c", &confirmation);

    if (confirmation == 's' || confirmation == 'S') {
        for (int i = index; i < *usersAmount - 1; i++) {
            users[i] = users[i + 1];
        }
        (*usersAmount)--;
        saveUser(users, *usersAmount, "users.txt");
        printf("Usuario eliminado correctamente.\n");
    } else {
        printf("Operación cancelada.\n");
    }
}

void modifyUser(User users[], int *usersAmount) {
    char name[50];
    printf("\n--- MODIFICAR USUARIO ---\n");
    printf("Ingrese el nombre de usuario a modificar: ");
    scanf("%49s", name);

    int index = -1;
    for (int i = 0; i < *usersAmount; i++) {
        if (strcmp(users[i].userName, name) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Usuario no encontrado.\n");
        return;
    }

    printf("\nModificando usuario: %s\n", users[index].userName);
    printf("Nuevo nombre (actual: %s): ", users[index].userName);
    scanf("%49s", users[index].userName);
    
    printf("Nueva contraseña: ");
    scanf("%49s", users[index].userPassword);
    
    printf("Nuevo rol (1=Admin, 0=Usuario) (actual: %d): ", users[index].isAdmin);
    scanf("%d", &users[index].isAdmin);

    saveUser(users, *usersAmount, "users.txt");
    printf("Usuario modificado exitosamente!\n");
}

void adminMenu(User users[], int *usersAmount) {
    int option;
    int exit = 0;

    do {
        printf(" -------------------------------- \n");
        printf("|       MENU ADMINISTRADOR       |\n");
        printf("|--------------------------------|\n");
        printf("|  1. Listar usuarios            |\n");
        printf("|  2. Agregar usuario            |\n");
        printf("|  3. Eliminar usuario           |\n");
        printf("|  4. Modificar usuario          |\n");
        printf("|  5. Salir                      |\n");
        printf(" -------------------------------- \n");
        printf("Seleccione una opcion: ");
        scanf("%d", &option);

        switch (option) {
            case 1: listUsers(users, *usersAmount); break;
            case 2: addUser(users, usersAmount); break;
            case 3: deleteUser(users, usersAmount); break;
            case 4: modifyUser(users, usersAmount); break;
            case 5: exit = 1; break;
            default: printf("Opcion invalida.\n");
        }
    } while (!exit);
}