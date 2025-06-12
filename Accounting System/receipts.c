#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "receipts.h"
#include "clients.h"
#include "utils.h"

int loadReceipt(Receipt receipts[], const char *receiptsFilePath) {
    FILE *file = fopen(receiptsFilePath, "r");
    if (!file) return 0;

    int counter = 0;
    while (counter < MAX_RECEIPTS && 
           fscanf(file, "%19[^|]|%d|%d/%d/%d|%f|%d\n",
                 receipts[counter].type,
                 &receipts[counter].number,
                 &receipts[counter].issueDate.day,
                 &receipts[counter].issueDate.month,
                 &receipts[counter].issueDate.year,
                 &receipts[counter].total,
                 &receipts[counter].cuitClient) == 7) {
        counter++;
    }
    fclose(file);
    return counter;
}

int saveReceipt(Receipt receipts[], int receiptsAmount, const char *receiptsFilePath) {
    FILE *file = fopen(receiptsFilePath, "w");
    if (!file) return 0;

    for (int i = 0; i < receiptsAmount; i++) {
        fprintf(file, "%s|%d|%02d/%02d/%04d|%.2f|%d\n",
                receipts[i].type,
                receipts[i].number,
                receipts[i].issueDate.day,
                receipts[i].issueDate.month,
                receipts[i].issueDate.year,
                receipts[i].total,
                receipts[i].cuitClient);
    }
    fclose(file);
    return 1;
}

void showReceipt(Receipt r) {
    printf("\nTipo: %s", r.type);
    printf("\nNúmero: %d", r.number);
    printf("\nFecha: %02d/%02d/%04d", 
           r.issueDate.day, r.issueDate.month, r.issueDate.year);
    printf("\nCliente (CUIT): %d", r.cuitClient);
    printf("\nTotal: $%.2f\n", r.total);
}

bool clientExists(int cuit, Client clients[], int clientsAmount) {
    for (int i = 0; i < clientsAmount; i++) {
        if (clients[i].cuit == cuit) {
            return true;
        }
    }
    return false;
}

bool validateDate(Date d) {
    if (d.year < 2000 || d.year > 2100) return false;
    if (d.month < 1 || d.month > 12) return false;
    if (d.day < 1 || d.day > 31) return false;
    
    if ((d.month == 4 || d.month == 6 || d.month == 9 || d.month == 11) && d.day > 30) {
        return false;
    }
    
    if (d.month == 2) {
        int leapYear = (d.year % 4 == 0 && d.year % 100 != 0) || (d.year % 400 == 0);
        if (d.day > (leapYear ? 29 : 28)) {
            return false;
        }
    }
    return true;
}

void listReceipt(Receipt receipts[], int receiptsAmount) {
    printf("\n--- LISTADO DE COMPROBANTES (%d) ---\n", receiptsAmount);
    for (int i = 0; i < receiptsAmount; i++) {
        showReceipt(receipts[i]);
        printf("------------------------\n");
    }
}

void addReceipt(Receipt receipts[], int *receiptsAmount, Client clients[], int clientsAmount) {
    if (*receiptsAmount >= MAX_RECEIPTS) {
        printf("\n¡Error! Límite de comprobantes alcanzado.\n");
        return;
    }

    Receipt newReceipt;
    printf("\n--- NUEVO COMPROBANTE ---\n");

    printf("Tipo (Factura, Recibo, Nota de Credito, Nota de Debito.): ");
    scanf(" %19[^\n]", newReceipt.type);

    printf("Número: ");
    while (scanf("%d", &newReceipt.number) != 1) {
        printf("¡Número inválido! Ingrese solo números: ");
        cleanBuffer();
    }

    do {
        printf("Fecha (dd mm aaaa): ");
        while (scanf("%d %d %d", &newReceipt.issueDate.day, 
                    &newReceipt.issueDate.month, 
                    &newReceipt.issueDate.year) != 3) {
            printf("¡Fecha inválida! Use formato dd mm aaaa: ");
            cleanBuffer();
        }
    } while (!validateDate(newReceipt.issueDate));

    do {
        printf("CUIT del cliente: ");
        while (scanf("%d", &newReceipt.cuitClient) != 1) {
            printf("¡CUIT inválido! Ingrese solo números: ");
            cleanBuffer();
        }
        
        if (!clientExists(newReceipt.cuitClient, clients, clientsAmount)) {
            printf("¡Cliente no existe! Ingrese un CUIT válido.\n");
        }
    } while (!clientExists(newReceipt.cuitClient, clients, clientsAmount));

    printf("Total: ");
    while (scanf("%f", &newReceipt.total) != 1 || newReceipt.total <= 0) {
        printf("¡Total inválido! Ingrese un número positivo: ");
        cleanBuffer();
    }

    receipts[*receiptsAmount] = newReceipt;
    (*receiptsAmount)++;
    saveReceipt(receipts, *receiptsAmount, "receipts.txt");
    printf("\n Comprobante agregado exitosamente.\n");
}

void modifyReceipt(Receipt receipts[], int receiptsAmount, Client clients[], int clientsAmount) {
    if (receiptsAmount == 0) {
        printf("\n¡No hay comprobantes registrados!\n");
        return;
    }

    int number;
    printf("\n--- MODIFICAR COMPROBANTE ---\n");
    printf("Ingrese número de comprobante: ");
    scanf("%d", &number);

    int index = -1;
    for (int i = 0; i < receiptsAmount; i++) {
        if (receipts[i].number == number) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\n¡Comprobante no encontrado!\n");
        return;
    }

    printf("\nEditando comprobante N°%d\n", receipts[index].number);
    showReceipt(receipts[index]);

    printf("\nNuevo tipo [Enter para mantener '%s']: ", receipts[index].type);
    cleanBuffer();
    char newType[20];
    if (fgets(newType, sizeof(newType), stdin) != NULL && newType[0] != '\n') {
        newType[strcspn(newType, "\n")] = 0;
        strcpy(receipts[index].type, newType);
    }

    Date newDate;
    printf("\nNueva fecha (dd mm aaaa) [Enter para mantener actual]: ");
    char dateStr[20];
    if (fgets(dateStr, sizeof(dateStr), stdin) != NULL && dateStr[0] != '\n') {
        while (sscanf(dateStr, "%d %d %d", &newDate.day, &newDate.month, &newDate.year) != 3 || 
               !validateDate(newDate)) {
            printf("¡Fecha inválida! Ingrese dd mm aaaa: ");
            fgets(dateStr, sizeof(dateStr), stdin);
        }
        receipts[index].issueDate = newDate;
    }

    printf("\nNuevo total [Enter para mantener $%s]: ", receipts[index].type);
    char totalStr[20];
    if (fgets(totalStr, sizeof(totalStr), stdin) != NULL && totalStr[0] != '\n') {
        while (sscanf(totalStr, "%f", &receipts[index].total) != 1 || 
               receipts[index].total <= 0) {
            printf("¡Total inválido! Ingrese un número positivo: ");
            fgets(totalStr, sizeof(totalStr), stdin);
        }
    }

    saveReceipt(receipts, receiptsAmount, "receipts.txt");
    printf("\n Comprobante modificado exitosamente.\n");
}

void deleteReceipt(Receipt receipts[], int *receiptsAmount) {
    if (*receiptsAmount == 0) {
        printf("\n¡No hay comprobantes registrados!\n");
        return;
    }

    int number;
    printf("\n--- ELIMINAR COMPROBANTE ---\n");
    printf("Ingrese número de comprobante: ");
    scanf("%d", &number);

    int index = -1;
    for (int i = 0; i < *receiptsAmount; i++) {
        if (receipts[i].number == number) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\n¡Comprobante no encontrado!\n");
        return;
    }

    printf("\nComprobante a eliminar:");
    showReceipt(receipts[index]);

    char confirmation;
    printf("\n¿Confirmar eliminación? (s/n): ");
    scanf(" %c", &confirmation);

    if (confirmation == 's' || confirmation == 'S') {
        for (int i = index; i < *receiptsAmount - 1; i++) {
            receipts[i] = receipts[i + 1];
        }
        (*receiptsAmount)--;
        saveReceipt(receipts, *receiptsAmount, "receipts.txt");
        printf("\n Comprobante eliminado exitosamente.\n");
    } else {
        printf("\n Operación cancelada.\n");
    }
}

void searchReceiptPerNumber(Receipt receipts[], int receiptsAmount) {
    if (receiptsAmount == 0) {
        printf("\n¡No hay comprobantes registrados!\n");
        return;
    }

    int number;
    printf("\n--- BUSCAR COMPROBANTE ---\n");
    printf("Ingrese número de comprobante: ");
    scanf("%d", &number);

    for (int i = 0; i < receiptsAmount; i++) {
        if (receipts[i].number == number) {
            printf("\n Comprobante encontrado:");
            showReceipt(receipts[i]);
            return;
        }
    }
    printf("\n Comprobante no encontrado.\n");
}

void searchReceiptPerClient(Receipt receipts[], int receiptsAmount, Client clients[], int clientsAmount) {
    if (receiptsAmount == 0) {
        printf("\n¡No hay comprobantes registrados!\n");
        return;
    }

    int cuit;
    printf("\n--- BUSCAR COMPROBANTES POR CLIENTE ---\n");
    printf("Ingrese CUIT del cliente: ");
    scanf("%d", &cuit);

    bool found = false;
    for (int i = 0; i < receiptsAmount; i++) {
        if (receipts[i].cuitClient == cuit) {
            if (!found) {
                printf("\nComprobantes encontrados:");
                found = true;
            }
            showReceipt(receipts[i]);
            printf("------------------------\n");
        }
    }

    if (!found) {
        printf("\n No se encontraron comprobantes para este cliente.\n");
    }
}

void receiptMenu(Receipt receipts[], int *receiptsAmount, Client clients[], int clientsAmount) {
    int option;
    int exit = 0;
    
    do {
        printf(" -------------------------------- \n");
        printf("|        MENU COMPROBANTES       |\n");
        printf("|--------------------------------|\n");
        printf("|  1. Listar comprobantes        |\n");
        printf("|  2. Agregar comprobante        |\n");
        printf("|  3. Buscar por numero          |\n");
        printf("|  4. Buscar por cliente         |\n");
        printf("|  5. Modificar comprobante      |\n");
        printf("|  6. Eliminar comprobante       |\n");
        printf("|  7. Salir                      |\n");        
        printf(" -------------------------------- \n");
        printf("Seleccione una opcion: ");
        
        if (scanf("%d", &option) != 1) {
            printf("\n¡Entrada inválida!\n");
            cleanBuffer();
            continue;
        }

        switch (option) {
            case 1: listReceipt(receipts, *receiptsAmount); break;
            case 2: addReceipt(receipts, receiptsAmount, clients, clientsAmount); break;
            case 3: searchReceiptPerNumber(receipts, *receiptsAmount); break;
            case 4: searchReceiptPerClient(receipts, *receiptsAmount, clients, clientsAmount); break;
            case 5: modifyReceipt(receipts, *receiptsAmount, clients, clientsAmount); break;
            case 6: deleteReceipt(receipts, receiptsAmount); break;
            case 7: exit = 1; break;
            default: printf("\n¡Opción inválida!\n");
        }
    } while (!exit);
}