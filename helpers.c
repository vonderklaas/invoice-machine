void generateWelcomeOptions () {
  printf("\n============ RESTAURANT BILLING ============");
  printf("\n\nPlease select an operation");
  printf("\n\n1. Generate Invoice");
  printf("\n2. Show all Invoices");
  printf("\n3. Search Invoice");
  printf("\n4. Exit");
}

void generateBillHeader (char name[50], char date[30]) {
  printf("\n\n");
  printf("\nRestaurant [NAME]");
  printf("\nDate: %s", date);
  printf("\nInvoice To: %s", name);
  printf("\n");
  printf("---------------------------------------\n");
  printf("Items\t\t");
  printf("Qty\t\t");
  printf("Total\t\t");
  printf("\n---------------------------------------");
  printf("\n\n");
}

void generateBillBody (char item[30], int qty, float price) {
  printf("%s\t\t", item); 
  printf("%d\t\t", qty); 
  printf("%.2f\t\t", qty * price); 
  printf("\n");
}

void generateBillFooter (float total) {
  printf("\n");
  float discount = 0.1 * total;
  float netTotal = total - discount;
  float cgst = 0.09 * netTotal;
  float finalTotal = netTotal + (cgst * 2); // 2 because CGST and SGST are same
  printf("---------------------------------------\n");
  printf("Sub Total\t\t\t%.2f", total);
  printf("\nDiscount @10%s\t\t\t%.2f", "%", discount);
  printf("\n\t\t\t\t-------");
  printf("\nNet Total\t\t\t%.2f", netTotal);
  printf("\nCGST @9%s\t\t\t%.2f", "%", cgst);
  printf("\nSGST @9%s\t\t\t%.2f", "%", cgst);
  printf("\n---------------------------------------");
  printf("\nTotal\t\t\t%.2f", finalTotal);
  printf("\n---------------------------------------\n");
}