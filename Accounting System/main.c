#include <stdio.h>
#include <stdbool.h>
#include "users.h"
#include "clients.h"
#include "receipts.h"
#include "utils.h"

void showHeader();

int main() {
    User users[MAX_USERS];
    Client clients[MAX_CLIENTS];
    Receipt receipts[MAX_RECEIPTS];
    
    int usersAmount = loadUser(users, "users.txt");    
    int clientsAmount = loadClients(clients, "clients.txt");
    int receiptsAmount = loadReceipt(receipts, "receipts.txt");

    if (usersAmount == 0) {
        printf("\n¡Error crítico! No se pudieron cargar usuarios.\n");
        return 1;
    }

    User actualUser;

    // Intentos infinitos hasta que inicie sesión correctamente
    while (true) {
        showHeader();
        if (login(users, usersAmount, &actualUser)) {
            break; // Inicio de sesión exitoso
        } else {
            printf("\nCredenciales incorrectas. Intente nuevamente.\n");
        }
    }

    int option;
    bool exit = false;
    
    while (!exit) {
        printf("Usuario: %s (%s)\n\n", 
               actualUser.userName,
               actualUser.isAdmin ? "Administrador" : "Usuario");
        
        printf("1. Gestion de Clientes\n");
        printf("2. Gestion de Comprobantes\n");
        if (actualUser.isAdmin) {
            printf("3. Gestion de Usuarios\n");
        }
        printf("0. Salir del sistema\n");
        printf("\nSeleccione una opcion: ");
        
        if (scanf("%d", &option) != 1) {
            printf("\n¡Error! Ingrese un número válido.\n");
            cleanBuffer();
            continue;
        }

        switch (option) {
            case 1:
                clientsMenu(clients, &clientsAmount, receipts, &receiptsAmount);
                break;
            case 2:
                receiptMenu(receipts, &receiptsAmount, clients, clientsAmount);
                break;
            case 3:
                if (actualUser.isAdmin) {
                    adminMenu(users, &usersAmount);
                } else {
                    printf("\n¡Opción no válida! Intente nuevamente.\n");
                }
                break;
            case 0:
                exit = true;
                showHeader();
                printf("Guardando datos...\n");
                saveUser(users, usersAmount, "users.txt");
                saveClients(clients, clientsAmount, "clients.txt");
                saveReceipt(receipts, receiptsAmount, "receipts.txt");
                break;
            default:
                printf("\n¡Opción no válida! Intente nuevamente.\n");
        }
    }
    return 0;
}

void showHeader() {
    printf("\n====================================");
    printf("\n         SISTEMA CONTABLE ");
    printf("\n====================================\n");
}
