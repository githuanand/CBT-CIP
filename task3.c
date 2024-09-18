#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define ACCOUNT_NUMBER_LENGTH 20
#define NAME_LENGTH 100

// Structure to represent a bank account
typedef struct {
    char accountNumber[ACCOUNT_NUMBER_LENGTH];
    char name[NAME_LENGTH];
    float balance;
    float interestRate; // Annual interest rate as a percentage
} Account;

// Array to store accounts and count of accounts
Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

/*
 * Function to create a new bank account
 */
void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Account limit reached. Cannot create more accounts.\n");
        return;
    }

    Account newAccount;
    printf("Enter account number: ");
    scanf("%s", newAccount.accountNumber);
    printf("Enter account holder's name: ");
    scanf(" %[^\n]", newAccount.name); // Read string with spaces
    printf("Enter initial balance: ");
    scanf("%f", &newAccount.balance);
    printf("Enter annual interest rate (in percentage): ");
    scanf("%f", &newAccount.interestRate);

    accounts[accountCount++] = newAccount;
    printf("Account created successfully.\n");
}

/*
 * Function to deposit funds into an existing account
 */
void deposit() {
    char accountNumber[ACCOUNT_NUMBER_LENGTH];
    float amount;
    printf("Enter account number: ");
    scanf("%s", accountNumber);
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].accountNumber, accountNumber) == 0) {
            accounts[i].balance += amount;
            printf("Deposited %.2f to account %s. New balance: %.2f\n", amount, accountNumber, accounts[i].balance);
            return;
        }
    }
    printf("Account not found.\n");
}

/*
 * Function to withdraw funds from an existing account
 */
void withdraw() {
    char accountNumber[ACCOUNT_NUMBER_LENGTH];
    float amount;
    printf("Enter account number: ");
    scanf("%s", accountNumber);
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].accountNumber, accountNumber) == 0) {
            if (accounts[i].balance >= amount) {
                accounts[i].balance -= amount;
                printf("Withdrew %.2f from account %s. New balance: %.2f\n", amount, accountNumber, accounts[i].balance);
            } else {
                printf("Insufficient funds.\n");
            }
            return;
        }
    }
    printf("Account not found.\n");
}

/*
 * Function to check the balance of an existing account
 */
void checkBalance() {
    char accountNumber[ACCOUNT_NUMBER_LENGTH];
    printf("Enter account number: ");
    scanf("%s", accountNumber);

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].accountNumber, accountNumber) == 0) {
            printf("Account Number: %s\n", accounts[i].accountNumber);
            printf("Account Holder: %s\n", accounts[i].name);
            printf("Balance: %.2f\n", accounts[i].balance);
            printf("Annual Interest Rate: %.2f%%\n", accounts[i].interestRate);
            return;
        }
    }
    printf("Account not found.\n");
}

/*
 * Function to calculate interest on an account over a number of years
 */
void calculateInterest() {
    char accountNumber[ACCOUNT_NUMBER_LENGTH];
    int years;
    printf("Enter account number: ");
    scanf("%s", accountNumber);
    printf("Enter number of years: ");
    scanf("%d", &years);

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].accountNumber, accountNumber) == 0) {
            float interest = accounts[i].balance * (accounts[i].interestRate / 100) * years;
            printf("Interest for account %s over %d years: %.2f\n", accountNumber, years, interest);
            return;
        }
    }
    printf("Account not found.\n");
}

/*
 * Main function to display menu and handle user choices
 */
int main() {
    int choice;

    while (1) {
        printf("\nBank Account Management System\n");
        printf("1. Create Account\n");
        printf("2. Deposit Funds\n");
        printf("3. Withdraw Funds\n");
        printf("4. Check Balance\n");
        printf("5. Calculate Interest\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            // Handle invalid input
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                checkBalance();
                break;
            case 5:
                calculateInterest();
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
