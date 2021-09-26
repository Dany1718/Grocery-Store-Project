// Preprocessor directives.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// Struct and global variables.
int n = 0;
int changesMade = 0;
struct Item
{
    int id;
    char name[10];
    double cost;
    char category;
};
struct Item item[10];
// Function prototypes.
void addItem(struct Item item[]);
void deleteItem(struct Item item[]);
void changeItem(struct Item item[]);
void searchItem(struct Item item[]);
void displayInventory(struct Item item[]);
void saveChanges(char *filename);
void readInFile(char *filename);
int main()
{
    // Welcome message and file-name input.
    int option = 0;
    char filename[30];

    printf("Welcome to the grocery store!\n");
    printf("Please input the file you'd like to load into stock.\n");
    scanf("%s",filename);
    // Reading in file.
    readInFile(filename);

    do // Grocery store menu.
    {
         printf("Please make one of the following selections:\n");
         printf("1. Add new item\n2. Delete item\n3. Change the cost of an item\n4. Search for item\n5. Display inventory details\n6.Quit\n");
         scanf("%i",&option);

         if(option == 1) // Option 1 leads to addItem function.
         {
            addItem(item);
            changesMade = 1;
         }
         else if(option == 2) // Option 2 leads to deleteItem function.
         {
            deleteItem(item);
            changesMade = 1;
         }
         else if(option == 3) // Option 3 leads to ChangeItem function.
         {
            changeItem(item);
            changesMade = 1;
         }
         else if(option == 4) // Option 4 leads to SearchItem function.
            searchItem(item);
         else if(option == 5) // Option 5 leads to displayInventory function.
            displayInventory(item);
         else if(option == 6) // Option 6 leads to goodbye message.
            printf("Thank you, Bye!");
         else
             printf("Invalid option, try again!\n");
    }while(option != 6);

    if(changesMade == 1) // If changes were made we must overwrite the file.
    {
        remove(filename);
        saveChanges(filename);
    }

    return 0;
}

void addItem(struct Item item[]) // This function will add an item to the inventory.
{

    bool added = false;
    bool successful;
    char nameTemp[20];
    int idTemp = 0;
    while(!added) // This loop will allow the user to enter the new item's details given that the details don't match any existing item.
    {
        successful = true;
        fflush(stdin);
        printf("What is the ID number for the item?\n");
        scanf("%i",&idTemp);
        for(int i = 0; i < n;i++)
        {
            if(idTemp == item[i].id)
            {
                printf("This ID has already been taken, please enter a different one.\n");
                successful = false;
                break;
            }
        }
        if(!successful)
            continue;
        item[n].id = idTemp;
        printf("What is the name of the item?\n");
        scanf("%s",nameTemp);
        for(int i = 0; i < n;i++)
        {
            if(strcmp(nameTemp,item[i].name) == 0)
            {
                printf("Another item has this name, if you would like to replace an item's id you must delete it first.\n\n");
                return;
            }
        }
        strcpy(item[n].name,nameTemp);
        printf("What is the cost of the item?\n");
        scanf("%lf",&item[n].cost);
        getchar();
        printf("What is the category letter of the item?\n");
        scanf("%c",&item[n].category);
        printf("%s has been added into the database.\n",item[n].name);
        n++;
        added = true;
    }
}
void deleteItem(struct Item item[]) // This function will delete an item from the inventory.
{
    int id;
    int check = 0;
    int option = 0;

    while(check == 0) // This loop will allow user to search and delete the item in question. If the item cannot be found, the user can search for a different one or exit.
    {
        printf("What is the ID number of the item in question?\n");
        scanf("%i",&id);
        for(int i = 0;i < n;i++)
        {
            if(id == item[i].id)
            {
                for(int j = i; j < n;j++)
                    item[j] = item[j+1];
                    printf("Item %i has successfully been deleted.\n",id);
                    check = 1;
            }
        }
        while(check == 0)
        {
            printf("Could not find that order, would you like to try again?\n1: Yes\n2: No\n");
            scanf("%i",&option);
            if(option == 2)
                return;
            else if(option == 1)
                break;
            else
                printf("Invalid option!\n");
        }
    }
    if(check == 1)
        n--;
}
void changeItem(struct Item item[]) // This function will change the cost of an item in the inventory.
{
    int id;
    int option = 0;
    int check = 0;
     while(check == 0) // This loop will allow the user to search for the item to be changed. If the item cannot be found, the user can search for another one or exit.
    {
        printf("What is the ID number of the item in question?\n");
        scanf("%i",&id);
        for(int i = 0;i < n;i++)
        {
            if(id == item[i].id)
            {
                printf("Okay I've found the item %s, what would you like the cost to be changed to?\n",item[i].name);
                scanf("%lf",&item[i].cost);
                printf("Item %s cost has been changed to %.2f\n",item[i].name,item[i].cost);
                check = 1;
                break;
            }
        }
        while(check == 0)
        {
            printf("Could not find that item in our system, would you like to try again?\n1: Yes\n2: No\n");
            scanf("%i",&option);
            if(option == 2)
                return;
            else if(option == 1)
                break;
            else
                printf("Invalid option!\n");
        }
    }
    
}
void searchItem(struct Item item[]) // This function will search for an item in the inventory.
{
    fflush(stdin);
    int check = 0;
    char itemForSearch[20];
    int option = 1;

    while(check == 0) // Inside this loop the user can enter the item to be searched, if it cannot be found the user can try again or quit to the main menu.
    {
        printf("What item would you like to search for?\n");
        scanf("%s",itemForSearch);

        for(int i = 0; i < n;i++)
        {
            if(strcmp(itemForSearch,item[i].name) == 0)
            {
                printf("We have found the item %s\n",item[i].name);
                check = 1;
            }
        }
            if(check == 0)
            {
                printf("We could not find the item, would you like to try again?\n1: Yes\n2: No\n");
                scanf("%i",&option);
                if(option == 1)
                    check = 0;
                else if(option == 2)
                    check = 1;
                else
                    printf("Invalid option, try again!\n");
            }
    }
}
void displayInventory(struct Item item[]) // This function will display an item in the inventory.
{
    printf("Here is a listing of all items in stock.\n");

    for(int i = 0;i < n;i++)
    {
        printf("ID: %i    Name: %s",item[i].id,item[i].name);
        printf("   Cost: %.2lf    Category: %c\n",item[i].cost,item[i].category);
    }
}
void saveChanges(char *filename) // This function will overwrite the existing grocery file.
{
        FILE * pfile = fopen(filename,"w");
        for(int i = 0;i < n;i++)
            fprintf(pfile,"%i %s %.2lf %c\n",item[i].id,item[i].name,item[i].cost,item[i].category);
        
        fclose(pfile);
}
void readInFile(char *filename) // This function will read in the inventory.
{
     FILE * pfile;
     pfile = fopen(filename,"r");

    if(pfile == NULL)
    {
        printf("Can't open file.\n");
        exit(0);
    }
    while(!feof(pfile))
    {
        fscanf(pfile,"%d %s %lf %c",&item[n].id,item[n].name,&item[n].cost,&item[n].category);
        n++;
    }
    n--;

    printf("\n%s as been properly loaded. With %i items\n\n\n",filename,n);
    fclose(pfile);
}