#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <ctype.h>
#include <time.h>
// #include <conio.h>
#define MAX_USERS 50

// All structures
typedef struct
{
    char name[100];
    char password[25];
    float balance;
    char DOB[11]; // dd-mm-yyyy

} user;

typedef struct
{
    char name[100];
    float deposit;
    float withdraw;
    char time[30];
} transaction;

// All Functions List

// functions for easy shortcut
int writeUsers(user users[], int userCount, char filename[]);
int readUsers(user users[], char filename[]);
int readStatements(transaction user[], char filename[]);

// function of main menu
void mainMenu();

// function for admin
void adminLogin();
void adminView();
void viewAllUsers();
void viewUserDetails();
void transactionHistory();
void searchBankStatements();
void deleteUser();

// functions for user
void userRegister();
void userLogin();
void deposit(user editedUser[], int numUsers, int userIndex);
void withdraw(user editedUser[], int numUsers, int userIndex);
void showUserBalance(user editedUser[], int numUsers, int userIndex);
void showUserDetails(user editedUser[], int numUsers, int userIndex);
void resetUserPassword(user editedUser[], int numUsers, int userIndex);


int main()
{
    mainMenu();
    return 0;
}

int readStatements(transaction user[], char filename[])
{
    FILE *fp = fopen(filename, "r");

    int userCount = 0;
    char type[20];

    while (userCount < MAX_USERS && fscanf(fp, "%99s %f %f %29[^\n]",
                                           user[userCount].name, &user[userCount].deposit, &user[userCount].withdraw, user[userCount].time) == 4)
    {

        userCount++;
    }

    fclose(fp);
    return userCount;
}

int readUsers(user users[], char filename[])
{
    FILE *fp = fopen(filename, "r");

    int userCount = 0;

    while (userCount < MAX_USERS && fscanf(fp, " Account holder name - %99[^\n]", users[userCount].name) == 1)
    {
        fscanf(fp, " Password - %24[^\n]", users[userCount].password);

        fscanf(fp, " Date of birth - %10[^\n]", users[userCount].DOB);

        fscanf(fp, " Balance - %f", &users[userCount].balance);

        userCount++;
    }

    fclose(fp);
    return userCount;
}

int writeUsers(user users[], int userCount, char filename[])
{
    FILE *fp = fopen(filename, "w");

    for (int i = 0; i < userCount; i++)
    {
        fprintf(fp, "Account holder name - %s\n", users[i].name);
        fprintf(fp, "Password - %s\n", users[i].password);
        fprintf(fp, "Date of birth - %s\n", users[i].DOB);
        fprintf(fp, "Balance - %.2f\n\n", users[i].balance);
    }

    fclose(fp);
    return userCount;
}

void mainMenu()
{

    int choice;
    while (1)
    {
        system("cls");
        printf("------------------------------------\n");
        printf("\tBANK MANAGEMENT SYSTEM\n");
        printf("------------------------------------\n");
        printf("\t1.Admin Login\n");
        printf("\t2.User Login\n");
        printf("\t3.New User Registration\n");
        printf("\t4.Exit\n");

        printf("\n\tEnter your choice:");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            adminLogin();
            break;
        case 2:
            userLogin();
            break;
        case 3:
            userRegister();
            break;
        case 4:
            system("cls");
            return;
        default:
            printf("Wrong input! Press enter to try again.");
            getchar();
            mainMenu();
        }
    }
}

void userRegister()
{
    system("cls");
    user newUser;
    user users[MAX_USERS];
    int numUsers = readUsers(users, "users.txt");  

    printf("Enter your name: ");
    gets(newUser.name);

  
    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(users[i].name, newUser.name) == 0)
        {
            printf("\nThis username is already registered! Please choose another name.\n");
            getchar();
            userRegister();  
            return;
        }
    }

    printf("Enter password: ");
    gets(newUser.password);
    newUser.balance = 0.0;
    printf("Enter date of birth (dd-mm-yyyy): ");
    gets(newUser.DOB);

   
    FILE *fp = fopen("users.txt", "a");
    fprintf(fp, "Account holder name - %s\nPassword - %s\nDate of birth - %s\nBalance - %.2f\n\n",
            newUser.name, newUser.password, newUser.DOB, newUser.balance);
    fclose(fp);

    printf("\nRegistration successful! Press enter to continue.\n");
    getchar();
    return;
}


void userLogin()
{
    system("cls");
    user editedUser[50];
    int numUsers = readUsers(editedUser, "users.txt");
    int userExists = 0;
    int userIndex;
    int choice;

    char name[100];
    char password[25];

    printf("Enter your name:");
    gets(name);
    printf("Enter your password:");
    gets(password);

    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(editedUser[i].name, name) == 0 && strcmp(editedUser[i].password, password) == 0)
        {
            userExists = 1;
            userIndex = i;
            break;
        }
    }
    if (userExists == 1)
    {
        while (1)
        {
            system("cls");
            printf("------------------------------------\n");
            printf("\tSUCCESSFULLY LOGGED IN\n");
            printf("------------------------------------\n");

            printf("\t1.Deposit\n");
            printf("\t2.Withdraw\n");
            printf("\t3.Show Balance\n");
            printf("\t4.Show Account Details\n");
            printf("\t5.Reset Password\n");
            printf("\t6.Logout\n");

            printf("\n\tEnter your choice:");
            scanf("%d", &choice);
            getchar();

            switch (choice)
            {
            case 1:
                deposit(editedUser, numUsers, userIndex);
                break;
            case 2:
                withdraw(editedUser, numUsers, userIndex);
                break;
            case 3:
                showUserBalance(editedUser, numUsers, userIndex);
                break;
            case 4:
                showUserDetails(editedUser, numUsers, userIndex);
                break;
            case 5:
                resetUserPassword(editedUser, numUsers, userIndex);
                break;
            case 6:
                mainMenu();
                break;
            default:
                printf("Wrong input! Press enter to try again.");
                getchar();
                continue;
            }
        }
    }
    else
    {
        int login_choice = 0;
        printf("\nWrong credentials.\n");
        printf("1.Try again.\n");
        printf("2.Main menu.\n");
        scanf("%d", &login_choice);
        getchar();
        switch (login_choice)
        {
        case 1:
            userLogin();
            break;
        case 2:
            mainMenu();
        }
    }
}

void deposit(user editedUser[], int numUsers, int userIndex)
{
    FILE *fp;
    time_t currentTime;
    char *currentTimeInString;

    currentTime = time(NULL);

    currentTimeInString = ctime(&currentTime);

    system("cls");
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    getchar();
    editedUser[userIndex].balance += amount;
    printf("Deposit successful! New balance: %.2f\n", editedUser[userIndex].balance);
    writeUsers(editedUser, numUsers, "users.txt");
    printf("\nPress enter to go back to previous menu.\n");

    fp = fopen("transaction_history.txt", "a");
    fprintf(fp, "%-20s\t%-10.2f\t%-10.2f\t%s\n", editedUser[userIndex].name, amount, 0.0, currentTimeInString);
    fclose(fp);
    getchar();
}

void withdraw(user editedUser[], int numUsers, int userIndex)
{
    FILE *fp;
    time_t currentTime;
    char *currentTimeInString;

    currentTime = time(NULL);

    currentTimeInString = ctime(&currentTime);

    system("cls");
    float amount;
    do
    {
        printf("Enter amount to withdraw: ");
        scanf("%f", &amount);
        getchar();
        if (editedUser[userIndex].balance < amount)
        {
            printf("Withdraw insuccessful! Current balance: %.2f\n", editedUser[userIndex].balance);
        }
    } while (editedUser[userIndex].balance < amount);

    editedUser[userIndex].balance -= amount;
    printf("Withdraw successful! New balance: %.2f\n", editedUser[userIndex].balance);
    writeUsers(editedUser, numUsers, "users.txt");
    printf("\nPress enter to go back to previous menu.\n");

    fp = fopen("transaction_history.txt", "a");
    fprintf(fp, "%-20s\t%-10.2f\t%-10.2f\t%s\n", editedUser[userIndex].name, 0.0, amount, currentTimeInString);
    fclose(fp);
    getchar();
}

void showUserBalance(user editedUser[], int numUsers, int userIndex)
{
    system("cls");
    printf("Your current balance is: %.2f\n", editedUser[userIndex].balance);
    printf("\nPress enter to go back to previous menu.\n");
    getchar();
}

void showUserDetails(user editedUser[], int numUsers, int userIndex)
{
    system("cls");
    printf("Account Holder Name: %s\n", editedUser[userIndex].name);
    printf("Date of Birth: %s\n", editedUser[userIndex].DOB);
    printf("Current Balance: %.2f\n", editedUser[userIndex].balance);
    printf("\nPress enter to go back to previous menu.\n");
    getchar();
}

void resetUserPassword(user editedUser[], int numUsers, int userIndex)
{
    system("cls");
    char newPassword[25];
    fflush(stdin);
    printf("Enter new password: ");
    gets(newPassword);
    strcpy(editedUser[userIndex].password, newPassword);
    writeUsers(editedUser, numUsers, "users.txt");
    printf("Password reset successful! Press enter to go back to previous menu.\n");
    getchar();
}

void adminLogin()
{
    system("cls");
    char name[25], pass[25];
    printf("------------------------------\n");
    printf("\tADMIN LOGIN\n");
    printf("------------------------------\n");
    printf("\n\tEnter Admin Username: ");
    gets(name);
    fflush(stdin);
    printf("\n\tEnter Password: ");
    gets(pass);
    if (strcmp(name, "admin") == 0 && strcmp(pass, "admin") == 0)
    {
        adminView();
    }
    else
    {
        printf("\nWrong credentials! Press enter to try again.\n");
        getchar();
        adminLogin();
    }
}

void adminView()

{
    int choice;

    while (1)
    {
        system("cls");
        printf("------------------------------\n");
        printf("\tWELCOME TO ADMIN PANEL\n");
        printf("------------------------------\n");
        printf("\t1.View All Users\n");
        printf("\t2.View User Details\n");
        printf("\t3.View All Transactions\n");
        printf("\t4.Search Bank Statements\n");
        printf("\t5.Delete user\n");
        printf("\t6.Logout\n");

        printf("\n\tEnter your choice:");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            viewAllUsers();
            break;
        case 2:
            viewUserDetails();
            break;
        case 3:
            transactionHistory();
            break;
        case 4:
            searchBankStatements();
            break;
        case 5:
            deleteUser();
            break;

        case 6:
            printf("\nLogging out...\n");
            return;

        default:
            printf("Wrong input! Press enter to try again.");
            getchar();
            adminView();
        }
    }
}

void viewAllUsers()
{
    system("cls");
    user users[MAX_USERS];
    int numUsers = readUsers(users, "users.txt");

    printf("List of all users:\n");
    for (int i = 0; i < numUsers; i++)
    {
        printf("User %d: %s\n", i + 1, users[i].name);
    }
    printf("\nPress enter to go back to admin menu.\n");
    getchar();
}

void viewUserDetails()
{
    system("cls");
    user users[MAX_USERS];
    int numUsers = readUsers(users, "users.txt");

    char name[100];
    printf("Enter the name of the user to view details: ");
    gets(name);

    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(users[i].name, name) == 0)
        {
            printf("Account Holder Name: %s\n", users[i].name);
            printf("Date of Birth: %s\n", users[i].DOB);
            printf("Current Balance: %.2f\n", users[i].balance);
            printf("\nPress enter to go back to admin menu.\n");
            getchar();
            return;
        }
    }
    printf("User not found! Press enter to try again.\n");
    getchar();
    viewUserDetails();
}

void transactionHistory()
{
    system("cls");
    transaction trans[MAX_USERS];
    int numTrans = readStatements(trans, "transaction_history.txt");

    float totalDeposit = 0, totalWithdraw = 0;

    printf("---------------------------------------------------------------------\n");
    printf("S.No   %-20s %-10s %-10s %-25s\n", "Name", "Deposit", "Withdraw", "Time");
    printf("---------------------------------------------------------------------\n");

    for (int i = 0; i < numTrans; i++)
    {
        printf("%-6d %-20s %-10.2f %-10.2f %-25s\n",
               i + 1, trans[i].name, trans[i].deposit, trans[i].withdraw, trans[i].time);
        totalDeposit += trans[i].deposit;
        totalWithdraw += trans[i].withdraw;
    }

    printf("---------------------------------------------------------------------\n");
    printf("TOTAL  %-20s %-10.2f %-10.2f\n", "", totalDeposit, totalWithdraw);
    printf("---------------------------------------------------------------------\n");

    printf("\nPress enter to go back to previous menu.\n");
    getchar();
}


void searchBankStatements()
{
    system("cls");
    transaction trans[MAX_USERS];
    int numTrans = readStatements(trans, "transaction_history.txt");

    char name[100];
    printf("Enter the name of the user to view statement: ");
    gets(name);

    float totalDeposit = 0, totalWithdraw = 0;
    int found = 0;

    printf("---------------------------------------------------------------------\n");
    printf("S.No   %-20s %-10s %-10s %-25s\n", "Name", "Deposit", "Withdraw", "Time");
    printf("---------------------------------------------------------------------\n");

    for (int i = 0; i < numTrans; i++)
    {
        if (strcmp(trans[i].name, name) == 0)
        {
            found = 1;
            printf("%-6d %-20s %-10.2f %-10.2f %-25s\n",
                   i + 1, trans[i].name, trans[i].deposit, trans[i].withdraw, trans[i].time);
            totalDeposit += trans[i].deposit;
            totalWithdraw += trans[i].withdraw;
        }
    }

    if (found)
    {
        printf("---------------------------------------------------------------------\n");
        printf("TOTAL  %-20s %-10.2f %-10.2f\n", "", totalDeposit, totalWithdraw);
        printf("---------------------------------------------------------------------\n");
    }
    else
    {
        printf("\nNo transactions found for user '%s'.\n", name);
    }

    printf("\nPress enter to go back to admin menu.\n");
    getchar();
}

void deleteUser()
{
    system("cls");
    user users[MAX_USERS];
    int numUsers = readUsers(users, "users.txt");

    char name[100];
    printf("Enter the name of the user to delete: ");
    gets(name);

    int found = 0;
    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(users[i].name, name) == 0)
        {
            found = 1;
            for (int j = i; j < numUsers - 1; j++)
            {
                users[j] = users[j + 1];
            }
            numUsers--;
            break;
        }
    }

    if (found)
    {
        writeUsers(users, numUsers, "users.txt");
        printf("User deleted successfully! Press enter to go back to admin menu.\n");
    }
    else
    {
        printf("User not found! Press enter to try again.\n");
    }
    getchar();
}