#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "clients.h"
#include "receipts.h"
#include "utils.h"

int loadClients(Client clients[], const char *clientsFilePath) {
    FILE *file = fopen(clientsFilePath, "r");
    if (!file) return 0;

    int counter = 0;
    while (counter < MAX_CLIENTS && 
           fscanf(file, "%49[^|]|%d|%99[^|]|%49[^\n]\n", 
                 clients[counter].name, 
                 &clients[counter].cuit, 
                 clients[counter].adress,
                 clients[counter].email) == 4) {
        counter++;
    }
    fclose(file);
    return counter;
}

int saveClients(Client clients[], int clientsAmount, const char *clientsFilePath) {
    FILE *file = fopen(clientsFilePath, "w");
    if (!file) return 0;

    for (int i = 0; i < clientsAmount; i++) {
        fprintf(file, "%s|%d|%s|%s\n", 
                clients[i].name, 
                clients[i].cuit, 
                clients[i].adress,
                clients[i].email);
    }
    fclose(file);
    return 1;
}

void listClients(Client clients[], int clientsAmount) {
    printf("\n--- LISTADO DE CLIENTES ---\n");
    for (int i = 0; i < clientsAmount; i++) {
        printf("%s - CUIT: %d\nDirección: %s\nEmail: %s\n\n", 
               clients[i].name, 
               clients[i].cuit, 
               clients[i].adress,
               clients[i].email);
    }
}

void addClient(Client clients[], int *clientsAmount) {
    if (*clientsAmount >= MAX_CLIENTS) {
        printf("No se pueden agregar más clientes.\n");
        return;
    }

    printf("\n--- NUEVO CLIENTE ---\n");
    printf("Nombre: ");
    scanf(" %49[^\n]", clients[*clientsAmount].name);
    printf("CUIT (sin guiones): ");
    scanf("%d", &clients[*clientsAmount].cuit);
    printf("Dirección: ");
    scanf(" %99[^\n]", clients[*clientsAmount].adress);
    printf("Email: ");
    scanf(" %49[^\n]", clients[*clientsAmount].email);

    (*clientsAmount)++;
    saveClients(clients, *clientsAmount, "clients.txt");
    printf("Cliente agregado correctamente.\n");
}

void modifyClient(Client clients[], int clientsAmount) {
    if (clientsAmount == 0) {
        printf("\n¡No hay clientes registrados!\n");
        return;
    }

    int cuitToModify;
    printf("\n--- MODIFICAR CLIENTE ---\n");
    printf("Ingrese CUIT del cliente: ");
    scanf("%d", &cuitToModify);

    int index = -1;
    for (int i = 0; i < clientsAmount; i++) {
        if (clients[i].cuit == cuitToModify) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\n¡Cliente no encontrado!\n");
        return;
    }

    printf("\nEditando cliente: %s (CUIT: %d)\n", clients[index].name, clients[index].cuit);
    
    printf("\nNuevo nombre [Enter para mantener '%s']: ", clients[index].name);
    cleanBuffer();
    char newName[50];
    if (fgets(newName, sizeof(newName), stdin) != NULL && newName[0] != '\n') {
        newName[strcspn(newName, "\n")] = 0;
        strcpy(clients[index].name, newName);
    }
    
    printf("Nueva dirección [Enter para mantener '%s']: ", clients[index].adress);
    char newAdress[100];
    if (fgets(newAdress, sizeof(newAdress), stdin) != NULL && newAdress[0] != '\n') {
        newAdress[strcspn(newAdress, "\n")] = 0;
        strcpy(clients[index].adress, newAdress);
    }
    
    printf("Nuevo email [Enter para mantener '%s']: ", clients[index].email);
    char newEmail[50];
    if (fgets(newEmail, sizeof(newEmail), stdin) != NULL && newEmail[0] != '\n') {
        newEmail[strcspn(newEmail, "\n")] = 0;
        strcpy(clients[index].email, newEmail);
    }

    saveClients(clients, clientsAmount, "clients.txt");
    printf("\n Cliente modificado exitosamente.\n");
}

bool hasAssociatedReceipts(int cuit, Receipt receipts[], int receiptsAmount) {
    for (int i = 0; i < receiptsAmount; i++) {
        if (receipts[i].cuitClient == cuit) {
            return true;
        }
    }
    return false;
}

void deleteClient(Client clients[], int *clientsAmount, Receipt receipts[], int receiptsAmount) {
    if (*clientsAmount == 0) {
        printf("No hay clientes registrados.\n");
        return;
    }

    int cuitToDelete;
    printf("\n--- ELIMINAR CLIENTE ---\n");
    printf("Ingrese CUIT del cliente a eliminar: ");
    scanf("%d", &cuitToDelete);

    int index = -1;
    for (int i = 0; i < *clientsAmount; i++) {
        if (clients[i].cuit == cuitToDelete) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Cliente no encontrado.\n");
        return;
    }

    if (hasAssociatedReceipts(cuitToDelete, receipts, receiptsAmount)) {
        printf("\n¡Error! El cliente tiene comprobantes asociados.\n");
        printf("Elimine primero los comprobantes antes de borrar al cliente.\n");
        return;
    }

    printf("\nCliente a eliminar:\n");
    printf("Nombre: %s\n", clients[index].name);
    printf("CUIT: %d\n", clients[index].cuit);
    printf("Dirección: %s\n", clients[index].adress);

    char confirmation;
    printf("\n¿Esta seguro de eliminar este cliente? (s/n): ");
    scanf(" %c", &confirmation);

    if (confirmation == 's' || confirmation == 'S') {
        for (int i = index; i < *clientsAmount - 1; i++) {
            clients[i] = clients[i + 1];
        }
        (*clientsAmount)--;
        saveClients(clients, *clientsAmount, "clients.txt");
        printf("Cliente eliminado correctamente.\n");
    } else {
        printf("Operación cancelada.\n");
    }
}

void searchClientPerCuit(Client clients[], int clientsAmount) {
    int cuitToSearch;
    printf("\n--- BUSCAR CLIENTE POR CUIT ---\n");
    printf("Ingrese CUIT (sin guiones): ");
    
    if (scanf("%d", &cuitToSearch) != 1) {
        printf("Error: CUIT debe ser numérico.\n");
        cleanBuffer();
        return;
    }

    for (int i = 0; i < clientsAmount; i++) {
        if (clients[i].cuit == cuitToSearch) {
            printf("\nCliente encontrado:\n");
            printf("Nombre: %s\n", clients[i].name);
            printf("CUIT: %d\n", clients[i].cuit);
            printf("Dirección: %s\n", clients[i].adress);
            printf("Email: %s\n", clients[i].email);
            return;
        }
    }
    printf("No se encontró cliente con CUIT %d.\n", cuitToSearch);
}

void clientsMenu(Client clients[], int *clientsAmount, Receipt receipts[], int *receiptsAmount) {
    int option;
    int exit = 0;
    
    do {
        printf(" -------------------------------- \n");
        printf("|          MENU CLIENTES         |\n");
        printf("|--------------------------------|\n");
        printf("|  1. Listar clientes            |\n");
        printf("|  2. Agregar cliente            |\n");
        printf("|  3. Eliminar cliente           |\n");
        printf("|  4. Modificar cliente          |\n");
        printf("|  5. Buscar cliente por cuit    |\n");
        printf("|  6. Salir                      |\n");        
        printf(" -------------------------------- \n");
        printf("Seleccione una opcion: ");
        
        if (scanf("%d", &option) != 1) {
            printf("Entrada inválida.\n");
            cleanBuffer();
            continue;
        }

       switch (option) {
            case 1: listClients(clients, *clientsAmount); break;
            case 2: addClient(clients, clientsAmount); break;
            case 3: deleteClient(clients, clientsAmount, receipts, *receiptsAmount); break;
            case 4: modifyClient(clients, *clientsAmount); break;
            case 5: searchClientPerCuit(clients, *clientsAmount); break;
            case 6: exit = 1; break;
            default: printf("Opción inválida.\n");
        }
    } while (!exit);
}