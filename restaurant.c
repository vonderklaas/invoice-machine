#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.c"

struct items {
  char item[20];
  float price;
  int qty;
};

struct orders {
  char customer[50];
  char date[50];
  int numOfItems;
  struct items itm[50];
};

int main (void) {
  // Variables
  int options;
  int n;
  struct orders ord;
  struct orders order;
  char saveBill = 'y';
  char contFlag = 'y';
  char name[50];
  FILE *filePointer;

  // Main Loop
  while (contFlag == 'y') {

    system("clear");

    float total = 0;
    int invoiceFound = 0;

    generateWelcomeOptions();

    printf("\n\nYour choice:\t");
    scanf("%d", &options);
    fgetc(stdin);

    switch (options) {
      // Generate Invoice
      case 1:
        system("clear");
        printf("\nPlease enter the name of the customer:\t");
        fgets(ord.customer, 50, stdin);
        ord.customer[strlen(ord.customer) - 1] = 0;
        strcpy(ord.date, __DATE__);
        printf("\nPlease enter the number of items:\t");
        scanf("%d", &n);
        ord.numOfItems = n;

        for (int i = 0; i < n; i++) {
          fgetc(stdin);
          printf("\nPlease enter the item %d:\t", i + 1);
          fgets(ord.itm[i].item, 20, stdin);
          ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
          printf("\nPlease enter the quantity:\t");
          scanf("%d", &ord.itm[i].qty);
          printf("\nPlease enter the unit price:\t");
          scanf("%f", &ord.itm[i].price);
          total += ord.itm[i].qty * ord.itm[i].price;
        }

        generateBillHeader(ord.customer, ord.date);
        for (int i = 0;i < ord.numOfItems; i++) {
          generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
        }
        generateBillFooter(total);

        printf("\nDo you want to save the invoice [y/n]:\t");
        scanf("%s", &saveBill);

        if (saveBill == 'y') {
          filePointer = fopen("Bills.txt", "a+");
          fwrite(&ord, sizeof(struct orders), 1, filePointer);
          if (fwrite(&ord, sizeof(struct orders), 1, filePointer) == 1) {
            printf("\nSuccessfully saved!");
          } else {
            printf("\nError saving!");
          }
          fclose(filePointer);
        }
        break;

      // Show all invoices
      case 2:
        system("clear");
        filePointer = fopen("Bills.txt", "a+");
        printf("\n  *****Your Previous Invoices*****\n");

        while (fread(&order,sizeof(struct orders), 1, filePointer)) {
            float total = 0;
            generateBillHeader(order.customer, order.date);
            for(int i = 0; i < order.numOfItems; i++){
                generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                total += order.itm[i].qty * order.itm[i].price;
            }
            generateBillFooter(total);
        }
        fclose(filePointer);
        break;

      // Show specific invoice
      case 3:
        printf("Enter the name of the customer:\t");
        fgets(name, 50, stdin);
        name[strlen(name) - 1] = 0;
        system("clear");
        filePointer = fopen("Bills.txt", "r");
        printf("\t*****Invoice of %s*****", name);

        while(fread(&order,sizeof(struct orders), 1, filePointer)){
          float total = 0;
          if(!strcmp(order.customer, name)){
            generateBillHeader(order.customer, order.date);
            for(int i = 0; i < order.numOfItems; i++){
                generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                total += order.itm[i].qty * order.itm[i].price;
            }
            generateBillFooter(total);
            invoiceFound = 1;
          }
        }

        if (!invoiceFound) {
          printf("Sorry the invoice for %s doesnot exists", name);
        }
        fclose(filePointer);
        break;

      // Exit
      case 4:
        printf("\n\t\tThanks, see you next time.\n\n");
        exit(0);
        break;
      default:
        printf("Sorry, invalid option selected!");
        break;
      }
    printf("\nDo you want to perform another operation?[y/n]:\t");
    scanf("%s", &contFlag);
  }
  printf("\n\t\tThanks, see you next time.\n\n");
  printf("\n\n");
}