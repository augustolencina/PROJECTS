#ifndef CLIENTS_H
#define CLIENTS_H

#include "dataTypes.h"

int loadClients(Client clients[], const char *clientsFilePath);
int saveClients(Client clients[], int clientsAmount, const char *clientsFilePath);
void clientsMenu(Client clients[], int *clientsAmount, Receipt receipts[], int *receiptsAmount);
void listClients(Client clients[], int clientsAmount);
void addClient(Client clients[], int *clientsAmount);
void modifyClient(Client clients[], int clientsAmount);
void deleteClient(Client clients[], int *clientsAmount, Receipt receipts[], int receiptsAmount);
void searchClientPerCuit(Client clients[], int clientsAmount);
bool hasAssociatedReceipts(int cuit, Receipt receipts[], int receiptsAmount);

#endif