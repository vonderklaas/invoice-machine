#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.c"

struct Item {
  char item[20];
  float price;
  int quantity;
};

struct Order {
  char customer[50];
  char date[50];
  int number_of_items;
  struct Item itm[50];
};

int main(void) {

  int options;
  int n;
  struct Order ord;
  struct Order order;
  char saveBill = 'y';
  char contFlag = 'y';
  char name[50];
  FILE* filePointer;

  // Main Loop
  while (contFlag == 'y') {

    // UNIX only
    system("clear");

    float total = 0;
    int invoiceFound = 0;

    generate_welcome_options();

    printf("\n\nYour choice:\t");
    scanf("%d", &options);

    // Consume the newline character left in the buffer
    fgetc(stdin);

    switch (options) {
    case 1:
      // UNIX only
      system("clear");
      printf("\nEnter customer's name:\t");
      fgets(ord.customer, 50, stdin);
      ord.customer[strlen(ord.customer) - 1] = 0;
      strcpy(ord.date, __DATE__);
      printf("\nEnter total number of items:\t");
      scanf("%d", &n);
      ord.number_of_items = n;

      for (int i = 0; i < n; i++) {
        // Consume the newline character left in the buffer
        fgetc(stdin);
        printf("\nEnter the %d item:\t", i + 1);
        fgets(ord.itm[i].item, 20, stdin);
        ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
        printf("\nEenter the quantity:\t");
        scanf("%d", &ord.itm[i].quantity);
        printf("\nEnter the unit price:\t");
        scanf("%f", &ord.itm[i].price);
        total += ord.itm[i].quantity * ord.itm[i].price;
      }

      generate_billing_header(ord.customer, ord.date);
      for (int i = 0;i < ord.number_of_items; i++) {
        generate_billing_body(ord.itm[i].item, ord.itm[i].quantity, ord.itm[i].price);
      }
      generate_billing_footer(total);

      printf("\nDo you want to save the invoice [y/n]:\t");
      scanf(" %c", &saveBill);

      if (saveBill == 'y') {
        filePointer = fopen("Bills.dat", "a+");
        if (filePointer == NULL) {
          perror("Error opening file");
          // Exit if you cannot proceed without opening the file
          exit(1);
        }
        if (fwrite(&ord, sizeof(struct Order), 1, filePointer) == 1) {
          printf("\nSuccessfully saved!");
        }
        else {
          printf("\nError saving!");
        }
        fclose(filePointer);
      }
      break;

      // Show all invoices
    case 2:
      // UNIX only
      system("clear");
      filePointer = fopen("Bills.dat", "r");
      if (filePointer == NULL) {
        perror("Error opening file");
        // Exit if you cannot proceed without opening the file
        exit(1);
      }
      printf("\n*****Your Previous Invoices*****\n");

      while (fread(&order, sizeof(struct Order), 1, filePointer)) {
        float total = 0;
        generate_billing_header(order.customer, order.date);
        for (int i = 0; i < order.number_of_items; i++) {
          generate_billing_body(order.itm[i].item, order.itm[i].quantity, order.itm[i].price);
          total += order.itm[i].quantity * order.itm[i].price;
        }
        generate_billing_footer(total);
      }
      fclose(filePointer);
      break;

      // Show specific invoice
    case 3:
      printf("Enter the name of the customer:\t");
      fgets(name, 50, stdin);
      name[strlen(name) - 1] = 0;
      // UNIX only
      system("clear");
      filePointer = fopen("Bills.dat", "r");
      if (filePointer == NULL) {
        perror("Error opening file");
        // Exit if you cannot proceed without opening the file
        exit(1);
      }
      printf("\t*****Invoice of %s*****", name);

      while (fread(&order, sizeof(struct Order), 1, filePointer)) {
        float total = 0;
        if (!strcmp(order.customer, name)) {
          generate_billing_header(order.customer, order.date);
          for (int i = 0; i < order.number_of_items; i++) {
            generate_billing_body(order.itm[i].item, order.itm[i].quantity, order.itm[i].price);
            total += order.itm[i].quantity * order.itm[i].price;
          }
          generate_billing_footer(total);
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
      printf("\nThanks, see you next time.\n\n");
      exit(0);
      break;
    default:
      printf("Sorry, invalid option selected!");
      break;
    }
    printf("\nDo you want to perform another operation?[y/n]:\t");
    scanf(" %c", &contFlag);
  }
  printf("\nThanks, see you next time.\n\n");
  printf("\n\n");
}