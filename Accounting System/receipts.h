#ifndef RECEIPTS_H
#define RECEIPTS_H

#include "dataTypes.h"

int loadReceipt(Receipt receipts[], const char *receiptsFilePath);
int saveReceipt(Receipt receipts[], int receiptsAmount, const char *receiptsFilePath);
void receiptMenu(Receipt receipts[], int *receiptsAmount, Client clients[], int clientsAmount);
void listReceipt(Receipt receipts[], int receiptsAmount);
void addReceipt(Receipt receipts[], int *receiptsAmount, Client clients[], int clientsAmount);
void modifyReceipt(Receipt receipts[], int receiptsAmount, Client clients[], int clientsAmount);
void deleteReceipt(Receipt receipts[], int *receiptsAmount);
void searchReceiptPerNumber(Receipt receipts[], int receiptsAmount);
void searchReceiptPerClient(Receipt receipts[], int receiptsAmount, Client clients[], int clientsAmount);
void showReceipt(Receipt r);
bool clientExists(int cuit, Client clients[], int clientsAmount);
bool validateDate(Date d);

#endif