/*
Name: Giovanni Falconer
Date: November 14, 2021
Description:This program is the programming aspect of Giovanni Falconer's Interenal Assessment.
            This program was designed to make the operation of a corner shop more efficient. This program does all the basic
              functions that would be needed for a corner shop to operate smoothly.These include:
            1- Calculations to improve the efficiency of the service in the shop.
            2- It stores all the item names, prices and stock amounts for the shopkeeper and automatically updates each as the day
              goes by or upon the request of the shopkeeper.
            3- It stores daily monetary earnings and can output it upon request.

            It is equipped with certain non functional actions which include:
            1- The system provides 2 accounts. 1 for a normal worker who just does calculations and 1 for the owner.

            The owner account is only accessible with the correct password and offers the user all the functional abilities of the program.
            The shopkeeper account is password free and offers the user a limited amount of the functional abilites of the program( Ones that are needed for work).
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct items{
  char itemname[255];
  int price;
  int stock;
  char receipt[50];
  double receiptprice;

};

//Here starts the LOGIN function which decides the user rank.
int login()
{
  int userRank;
  int userinput;
  int password;
  int found = 0;
  int choice;
  char userinput1;


  printf("                              ______________________________________________\n");
  printf("                             |                   ~LOGIN~                   |\n");
  printf("                             |---------------------------------------------|\n");
  printf("                             |------------------USER RANKS-----------------|\n");
  printf("                             |1---------Owner                              |\n");
  printf("                             |2-------- Shopkeeper                         |\n");
  printf("                             |_____________________________________________|\n");
  printf("                             |Please select your rank from the list above: ");
  scanf("%d", &userinput);

  switch (userinput) {
    case 1:
      do{
        choice = 1;
        printf("*======================================================================================================================*\n");
        printf("Hello Owner. For access please enter your password: (THE PASSW0RD IS: 12345)");
        scanf("%d", &password);


        if (password == 12345){
          found = 1;
          printf("\nLogin Successful!!!\n");
          userRank = 1;
          printf("\nPress Any letter followed by [ENTER] to continue\n");
          scanf("%s", &userinput1);
          system("cls");
        } else {
          printf("\nIncorrect password\n");
          printf("\nDo you wish to try again? (Enter 1 for YES and 2 for No).\n");
          scanf("%d", &choice );
          printf("\n");
          system("cls");
        }
      }while(found == 0 && choice == 1 );
      system("cls");
      break;

    case 2:
      printf("*=================================================================*\n");
      printf("Welcome to work\n\n");
      userRank = 2;
      printf("Press Any letter followed by [ENTER] to continue\n");
      scanf("%s", &userinput1);
      system("cls");
      break;

    default:
      printf("Invalid option entered\n");
      printf("Press Any letter followed by [ENTER] to continue\n");
      scanf("%s", &userinput1);
      system("cls");
      printf("===============================The system will now be stopped. Please restart and try again=============================\n");
      break;
  }

  printf("Please press any letter and [ENTER] to continue\n");
  scanf("%s", &userinput1);
  system("cls");
  return userRank;
}

//Here starts the MENU function which displays the options for user rank 1.
void Menu()
{
  printf("----------------MENU------------------\n");
  printf("1- Cash a Customer\n");
  printf("2- Import the item list\n");
  printf("3- Request a print-out of stock amounts.\n");
  printf("4- Request a print-out of cash amount and SAVE cash total.\n");
  printf("5- Update stock amounts and prices OR Add items to list\n");
  printf("6- Close & Save\n");
}

//Here starts the SUBMENU function which displays the options for user rank 2.
void SUBMenu()
{
  printf("------------MENU-----------\n");
  printf("1- Cash a Customer\n");
  printf("2- Import the item list\n");
  printf("3- Request a print-out of cash amount and SAVE cash total.\n");
  printf("4- Close & Save\n");
}
/*Here starts the updates function. Upoon being called it will allow the user to either change the stock amount of the item or change its price*/
void updates(struct items item[], int num1)
{
  int userinput;
  int i, num, counter, choice, found;
  char name[255];

  do{
      choice = 1;
      system("cls");
      printf("*======================================================================================================================*\n");
      printf("                                          ~WELCOME TO THE UPDATE FUNCTION~\n");
      printf("*======================================================================================================================*\n");

      printf("Please enter the name of the item you wish to find: ");
      scanf("%s", &name);

        i = 0;
        found = 0;

      while (found == 0 && i <= (num1-1)) {
        if (!strcmp(item[i].itemname, name)){
          found = 1;
          printf("Your item was found\n");
        }else{
          i++;
        }
      }

      if (found == 1) {
        printf("*======================================================================================================================*\n");
        printf("The item you searched for is: %s \n", item[i].itemname );
        printf("Its price is: %d \n", item[i].price);
        printf("Its stock amount is: %d \n", item[i].stock );


        printf("\nDo you wish to change the price or the stock amount. Enter 1 for Price change or 2 for Stock Update:");
        scanf("%d",&userinput );

        switch (userinput) {
          case 1:
            printf("\nPlease enter the update for the price:");
            scanf("%d", &num);
            item[i].price = num;
            printf("\nYour price change has been completed.\n");
            break;
          case 2:
            printf("Please enter the amount to add to the stock:");
            scanf("%d", &num );
            item[i].stock = num + item[i].stock;
            printf("\nYour stock amount has been updated\n");
            break;
          default:
            printf("You have entered an invalid option\n");
            break;
        }
      }else if(found == 0){
        printf("Your item was not found\n");

      }
      printf("*======================================================================================================================*\n");
      printf("Do you wish to search again? Enter 1 for YES and 2 for NO:");
      scanf("%d",&choice );
      system("cls");
    }while(choice==1);

  // return counter;
}

//Here starts the closing function. Upoon being called it prints a leaving message and then backs up all the struct information to the file.
void closing(int num, struct items item[])
{
  int i;
  system("cls");

  printf("Thank you for using this program. Please enjoy the rest of your day.\n");

  FILE * fpointer = fopen("OVERSTOCK-SHOP-INFO.txt", "w");

  for (i = 0; i < num; i++) {

    fprintf(fpointer, " %s %d %d\n", item[i].itemname , item[i].price, item[i].stock);
  }
  fclose(fpointer);

}

//Here starts the import function. Upon being called it will read the information from the file and assign them to the respective variables.
int import(struct items item[])
{
  int i = 0;
  char e[10];
  char d[10],c;

  system("cls");

  printf("Your data is now being imported.\n");
  printf("*======================================================================================================================*\n");
  FILE * fpointer = fopen("OVERSTOCK-SHOP-INFO.txt", "r");
  while ((c = getc(fpointer)) != EOF) {
    fscanf(fpointer,"%s %d %d", &item[i].itemname, &item[i].price, &item[i].stock);
    i++;
    }
  fclose(fpointer);
  i--;

  return i;
}
//Here starts the receipt function. Upon being called it will display a fomatted receipt of the most recent order.
void receipt(struct items item[], int num, double total)
{
  system("cls");
  printf("*======================================================================================================================*\n");
  printf("                                              ~RECEIPT FUNCTION~\n");
  printf("*======================================================================================================================*\n");

  int i;
  printf("----------ITEMS ------------\n");
  for (i = 0; i < num; i++) {
    printf("%s    %.2f\n", item[i].receipt, item[i].receiptprice);
  }
  printf("\n\nSub-total: $%.2f\n", total);
  printf("Tax:       $0.00\n");
  printf("Total:     $%.2f\n", total);
}
//Here starts the pricelist function. This is called by the calculation function and at that point it prints a list of the current items and their prices'
void price_list(struct items item[], int num)
{
  int i;
  printf("*======================================================================================================================*\n");
  printf("                                                  ~PRICELIST FUNCTION~\n");
  printf("*======================================================================================================================*\n");
  printf("                                     |    NO. |    ITEM NAME  |    PRICE    |\n");
  printf("                                     |--------|-----------------------------|\n");

  for ( i = 0; i < num; i++) {
    printf("                                     |    %2d  |  %s\t| $%d\t  |\n", i+1, item[i].itemname, item[i].price);
  }

}
//Here starts the stocks function. Upon being called it provides the user with the option to search for an item and see the stock amount for that item.
void stocks(struct items item[], int num)
{
  char name[255];
  char userinput1;
  int i, choice, found;

  system("cls");
  printf("*======================================================================================================================*\n");
  printf("                                          ~WELCOME TO THE STOCKS FUNCTION~\n");
  printf("*======================================================================================================================*\n");

  do {
    choice = 1;
    printf("\n*======================================================================================================================*\n");
    printf("Please enter the name of the item you wish to see the stock amount of:");
    scanf("%s", &name);

    i = 0;
    found = 0;

    while (found == 0 && i <= (num-1)) {
      if (!strcmp(item[i].itemname, name)){
        found = 1;
      }else{
        i++;
      }
    }

    if(found == 1){
      printf("\n*======================================================================================================================*\n");
      printf("The item you selected is: %s\n", item[i].itemname);
      printf("The stock currently being held in store is: %d\n", item[i].stock);

      printf("\nPlease press any letter and [ENTER] to continue\n");
      scanf("%s",&userinput1);
    }else {
      printf("Your item was not found.\n");
      printf("\nPlease press any letter and [ENTER] to continue\n");
      scanf("%s",&userinput1);
    }
    system("cls");
    printf("\n*======================================================================================================================*\n");
    printf("Do you wish to view the stock amount for any other item? (Enter 1 for YES and 2 for NO):");
    scanf("%d", &choice);
    system("cls");
  }while(choice == 1);

}

/*Here starts the calculation function. This facilitates sales done by the user as it calculates the subtotal for each order and calculates the daily total and returns it to be storesd*/
double calculations(struct items item[], int num)
{
  double subtotal;
  int i, counter, choice, c, userinput, found;
  char name[255];
  double dailytotal = 0;
  char userinput1;


do{
    c = 0;
    subtotal = 0;

    system("cls");
    printf("*======================================================================================================================*\n");
    printf("                                          ~WELCOME TO THE CALCULATIONS FUNCTION~\n");
    printf("*======================================================================================================================*\n");

    price_list(item, num);
    do{
      choice = 1;
      printf("\n*======================================================================================================================*\n");
      printf("Please enter the name of the item you wish to add to the order: ");
      scanf("%s", &name);


      i = 0;
      found = 0;

      while (found == 0 && i <= (num-1)) {
        if (!strcmp(item[i].itemname, name)){
          found = 1;

        }else{
          i++;
        }
      }

      if (found == 1) {

        printf("*======================================================================================================================*\n");
        printf("\nThe item you selected is: %s\n", item[i].itemname);
        printf("Number of items ordered:");
        scanf("%d", &userinput);

        //The following nested if-statement block checks the stock for the item that is wanted.It checks if the  stock held is adequate to fullfil the order.
        //This scenario the stock is more than the order.
        if (item[i].stock >= userinput){
          item[i].stock = item[i].stock - userinput;

          //The following if statement checks the item stock to see if it has fallen to zero and lets the user know.
          if (item[i].stock == 0) {
            printf("*======================================================================================================================*\n");
            printf("                          The stock amount for this item has fallen to: [%d]\n", item[i].stock);
            printf("*======================================================================================================================*\n");
          }

          strcpy(item[c].receipt, item[i].itemname);
          item[c].receiptprice = item[i].price * userinput;
          c++;

          subtotal = subtotal + (item[i].price * userinput);
          printf("The current subtotal is: $%.2f\n", subtotal);

          //This scenario the stock is less than the ordered amount but greater than 0
          //It lets the user know and offers a choice to renenter an amount to order.
        } else if (item[i].stock < userinput && item[i].stock != 0){

          printf("\n-----The current order amount is greater than the amount of this item currently stored-----\n");
          printf("Do you wish to reorder with a different number of the selected item?(Enter 1 for YES and 2 for NO.)\n");
          scanf("%d", &choice);

          if (choice == 1) {
            printf("*======================================================================================================================*\n");
            printf("The current stock held for that item is: %d\n",item[i].stock);
            printf("\nNumber of items for reorder:");
            scanf("%d",&userinput);
            item[i].stock = item[i].stock - userinput;

            //The following if statement checks the item stock to see if it has fallen to zero and lets the user know.
            if (item[i].stock == 0) {
              printf("*======================================================================================================================*\n");
              printf("                          The stock amount for this item has fallen to: [%d]\n", item[i].stock);
              printf("*======================================================================================================================*\n");
              printf("\nPress Any letter followed by [ENTER] to continue\n");
              scanf("%s", &userinput1);
            }

            strcpy(item[c].receipt, item[i].itemname);
            item[c].receiptprice = item[i].price * userinput;
            c++;

            subtotal = subtotal + (item[i].price*userinput);
            printf("The current subtotal is: $%.2f\n", subtotal);

          }else{
            printf("This item will not be added to the order list\n");
          }
        //This scenario the stock is fully zero.
        }else if(item[i].stock == 0){
          printf("*======================================================================================================================*\n");
          printf("                          The stock amount for this item is: [%d]\n", item[i].stock);
          printf("*======================================================================================================================*\n");
          printf("\nPress Any letter followed by [ENTER] to continue\n");
          scanf("%s", &userinput1);
        }
      }

      else{
        printf("You have enetered an invalid item name.\n");
      }
      printf("\nDo you wish to add another item to the order?(Enter 1 for YES and 2 for NO):");
      scanf("%d",&choice);
    }while(choice == 1);
    //The following lines check if the user wants to print a receipt.
    printf("*======================================================================================================================*\n");
    printf("Do you want to print a receipt?(Enter 1 for YES and 2 for NO):");
    scanf("%d",&userinput );

    if (userinput == 1) {
      receipt(item, c, subtotal);
      printf("\nPress Any letter followed by [ENTER] to continue\n");
      scanf("%s", &userinput1);
    }else{
      printf("You have entered an invalid option\n");
    }

    system("cls");

    dailytotal = dailytotal + subtotal;

    printf("Do you wish to do another calculation?(Enter 1 for YES and 2 for NO)\n" );
    scanf("%d", &choice);

  }while(choice == 1);

  return dailytotal;
}
/*Here starts the days final function. This allows the user to print the final amount for the current day or for the days since the first use of the code that were saved*/
void daysfinal(double num, char date[])
{
  int userinput;
  char userinput1,c;
  char line[255];

  system("cls");
  printf("*======================================================================================================================*\n");
  printf("                                          ~WELCOME TO THE DAYS FINAL FUNCTION~\n");
  printf("*======================================================================================================================*\n");

  printf("*------------------------*\n");
  printf("|1- Today's Final        |\n" );
  printf("|2- Previous Day's Final |\n");
  printf("*------------------------*\n");

  printf("\n*======================================================================================================================*\n");

  printf("Please choose an option from above:");
  scanf("%d", &userinput );

  switch (userinput) {
    case 1:
      printf("\n*======================================================================================================================*\n");
      printf("The date is: %s\n", date );
      printf("The final amount is: %.2f\n",num );
      printf("\nPress Any letter followed by [ENTER] to continue\n");
      scanf("%s", &userinput1);

      //The following lines write the daily money amount to a file with the date
      FILE * fpointer1 = fopen("OVERSTOCK-SHOP-DAYSFINAL.txt", "a");
      fprintf(fpointer1, " %s : $%.2f\n", date, num);

      fclose(fpointer1);
      break;

    case 2:
      system("cls");
      //The following block of code reads the daily amount of cash for previous days and prints them out from the file
      printf("*======================================================================================================================*\n");
      FILE * fpointer2 = fopen("OVERSTOCK-SHOP-DAYSFINAL.txt", "r");
      while ((c = getc(fpointer2)) != EOF) {
        fgets(line, 255, fpointer2);
        printf("%s\n", line);
        }
      fclose(fpointer2);
      break;
    default:
      printf("Invalid option entered\n");
      break;

  }
}

//This is the main function.
int main()
{
  int userinput;
  char userinput1;
  int userRank;
  double dailytotal = 0;
  int i, num=0, counter = 0, choice, itemcheck = 0;
  char date[10];
  struct items item[50];


  printf("                                    __    __  ________  __       __       ______     \n");
  printf("                                   | \\  | \\  |        \\|  \\     |  \\    /       \\      \n");
  printf("                                   | $$  | $$| $$$$$$$$| $$     | $$    |  $$$$$$\\    \n");
  printf("                                   | $$__| $$| $$__    | $$     | $$    | $$  | $$    \n");
  printf("                                   | $$    $$| $$  \\   | $$     | $$    | $$  | $$    \n");
  printf("                                   | $$$$$$$$| $$$$$   | $$     | $$    | $$  | $$  \n");
  printf("                                   | $$  | $$| $$_____ | $$_____| $$____| $$__/ $$  \n");
  printf("                                   | $$  | $$| $$     \\| $$     \\ $$     \\$$    $$  \n");
  printf("                                    \\$$   \\$$ \\$$$$$$$$\\$$$$$$$$$\\$$$$$$$$\\$$$$$$   \n");

  printf(" ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______\n");
  printf("|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|\n");

  printf("\nPress Any letter followed by [ENTER] to continue\n");
  scanf("%s", &userinput1);
  system("cls");

  system("cls");
  //Line 553 Calls the login function and assign the value returned to the userRank variable
  userRank = login();

  do{
    choice =1;
    switch (userRank) {
      case 1:
        Menu();
        printf("\nPlease select your option from the list above:");
        scanf("%d", &userinput);
        if (userinput == 1){
          //Launch calculations and store returned value

          if(counter == 0){
            printf("|*====================================================================================================================*|\n");
            printf("You have not entered any items or have not imported your stored.\n");
            printf("Do you wish to enter a new list of items?(Enter 1 for YES and 2 for NO)\n");
            scanf("%d", &choice );
            if (choice == 1){
              system("cls");
              printf("\nPlease enter the number of items on the new list(Less than 50):");
              scanf("%d", &num );

              if(num >50){
                printf("The number you have entered is too large\n" );
                printf("\nPlease re-enter a number.\n");
                scanf("%d", &num);
              }

              for (i = 0; i < num; i++) {

                printf("\nPlease enter the item name (As 1 word): ");
                scanf("%s", &item[i].itemname);

                printf("Please enter the price of the item:");
                scanf("%d", &item[i].price);


                printf("Please enter the amount of stock present for this item:");
                scanf("%d", &item[i].stock);
                printf("Item number %d has been entered\n", i+1);
                printf("*------------------------------------------------------*\n");

              }
              counter = num;
            }

          }else if (counter != 0){
            dailytotal =  dailytotal + calculations(item, counter);
          }
        }else if (userinput == 2){
          //Lauch import and store returned value.
          counter = import(item);

        }else if(userinput == 3){
          //Launch stocks
          stocks(item, counter);
        }else if (userinput == 4){
          //Launch days final
          printf("*======================================================================================================================*\n");
          printf("Please enter today's date in the format dd/mm/yyyy\n");
          scanf("%s", &date);
          daysfinal(dailytotal, date);
        }else if(userinput == 5){
          do{
              system("cls");
              printf("                                     |               ~OPTIONS~             |\n");
              printf("                                     |*------------------------------------|*\n");
              printf("                                     |1- Add items to the list             |\n");
              printf("                                     |2- Update the stock amount or prices |\n");
              printf("                                     |*------------------------------------|*\n");
              printf("\n*======================================================================================================================*\n");

              printf("\nPlease choose from the options above:");
              scanf("%d", &userinput);

              switch (userinput) {
                case 1:
                    system("cls");
                    printf("\n*======================================================================================================================*\n");
                    printf("Do you wish to create a new list? Enter 1 YES and 2 NO:");
                    scanf("%d", &userinput);

                    if (userinput == 1) {
                      printf("\nPlease enter the number of items on the new list(Less than or equal to 50):");
                      scanf("%d", &num );

                      if(num > 50){
                        printf("The number you have entered is too large\n" );
                        printf("Please re-enter a number(Less than the limit).\n");
                        scanf("%d", &num);
                      }

                      for (i = 0; i < num; i++) {

                        printf("\nPlease enter the item name (As 1 word): ");
                        scanf("%s", &item[i].itemname);

                        printf("Please enter the price of the item:");
                        scanf("%d", &item[i].price);


                        printf("Please enter the amount of stock present for this item:");
                        scanf("%d", &item[i].stock);
                        printf("Item number %d has been entered\n", i+1);
                        printf("*------------------------------------------------------*\n");

                        printf("\nPress Any letter followed by [ENTER] to continue\n");
                        scanf("%s", &userinput1);

                      }
                      counter = num;

                    }  else if (userinput == 2) {
                        printf("*======================================================================================================================*\n");
                        printf("\nPlease enter the amount of items you wish to add to the list:");
                        scanf("%d", &num);

                        if ((num + counter) > 50) {
                          printf("\n*======================================================================================================================*\n");
                          printf("The number of items you want to add will exceed the limit of the system.\n Your current number of items is: %d\n", (counter + num));
                          printf("Please enter another number that will not exceed the limit.\n");
                          scanf("%d", &num);
                        }else if((num + counter)<=50){

                        for (i = counter; i < (counter + num); i++){
                          printf("\nPlease enter the name of the item (As 1 word):");
                          scanf("%s", &item[i].itemname );

                          printf("Please enter the price of the item:" );
                          scanf("%d",&item[i].price );

                          printf("Please enter the amount of this item currently in store:");
                          scanf("%d", &item[i].stock );
                          printf("Item number %d has been entered\n", i+1);
                          printf("*------------------------------------------------------*\n");
                        }
                        counter= counter + num;
                      }
                    }
                    else {
                      printf("You have entered an invalid option\n");
                    }
                  break;
                case 2:
                  updates(item , counter);
                  break;
                default :
                  printf("Invalid option entered\n");
                }
                system("cls");
                printf("Do you wish to return to the Update-stock options? (Enter 1 for YES and 2 for NO)\n");
                scanf("%d", &choice);
            }while(choice == 1);

            } else if (userinput == 6){
              //Launch closing fucntion
              closing(counter, item);

            }else {
              printf("\nYou have entered an Invalid option\n");
            }
            break;

      case 2:
        SUBMenu();
        printf("\nPlease select your option from the list above:");
        scanf("%d", &userinput);
        if (userinput == 1) {
          //Launch calculations and store returned vale
          dailytotal =  dailytotal + calculations(item, counter);
        }else if(userinput == 2){
          //Lauch import and store returned value.
          counter = import(item);
        }else if(userinput == 3){
          //Launch days final function
          printf("*======================================================================================================================*\n");
          printf("Please enter today's date in the format dd/mm/yyyy\n");
          scanf("%s", &date);
          daysfinal(dailytotal, date);
        }else if(userinput == 4){
          //Lauch closing function
          closing(counter, item);
        }else {
          printf("You have entered an Invalid option\n");
        }
        break;
      }

     printf("\nDo you wish to return to the main menu? (Enter 1 for YES and 2 for NO):");
     scanf("%d",&choice );
     system("cls");
  }while(choice == 1);

  printf("Do you wish to restart this program?(Enter 1 for YES and 2 for NO):");
  scanf("%d", &choice);

  if (choice == 1){
    system("cls");
    main();
  }
return 0;
}
