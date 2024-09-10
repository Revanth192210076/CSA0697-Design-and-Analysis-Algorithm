#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to hold account details
typedef struct {
    int accountNumber;
    char accountHolderName[100];
    float balance;
} Account;

// Function prototypes
void addAccount(Account accounts[], int *size);
void displayAccounts(const Account accounts[], int size);
int binarySearch(const Account accounts[], int size, int accountNumber);

int main() {
    Account accounts[100];
    int size = 0;
    int choice, accountNumber, index;

    while (1) {
        printf("\nBank Account Management System\n");
        printf("1. Add Account\n");
        printf("2. Display All Accounts\n");
        printf("3. Search Account\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addAccount(accounts, &size);
                break;
            case 2:
                displayAccounts(accounts, size);
                break;
            case 3:
                printf("Enter account number to search: ");
                scanf("%d", &accountNumber);
                index = binarySearch(accounts, size, accountNumber);
                if (index != -1) {
                    printf("Account found:\n");
                    printf("Account Number: %d\n", accounts[index].accountNumber);
                    printf("Account Holder Name: %s\n", accounts[index].accountHolderName);
                    printf("Balance: %.2f\n", accounts[index].balance);
                } else {
                    printf("Account not found.\n");
                }
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to add an account
void addAccount(Account accounts[], int *size) {
    if (*size >= 100) {
        printf("Account list is full.\n");
        return;
    }

    Account newAccount;
    printf("Enter account number: ");
    scanf("%d", &newAccount.accountNumber);
    printf("Enter account holder name: ");
    scanf(" %[^\n]s", newAccount.accountHolderName);
    printf("Enter balance: ");
    scanf("%f", &newAccount.balance);

    // Insert the new account and sort the array
    accounts[*size] = newAccount;
    (*size)++;

    // Sort accounts by account number for binary search
    for (int i = 0; i < *size - 1; i++) {
        for (int j = i + 1; j < *size; j++) {
            if (accounts[i].accountNumber > accounts[j].accountNumber) {
                Account temp = accounts[i];
                accounts[i] = accounts[j];
                accounts[j] = temp;
            }
        }
    }

    printf("Account added successfully.\n");
}

// Function to display all accounts
void displayAccounts(const Account accounts[], int size) {
    if (size == 0) {
        printf("No accounts to display.\n");
        return;
    }

    printf("\nAccount Details:\n");
    for (int i = 0; i < size; i++) {
        printf("Account Number: %d\n", accounts[i].accountNumber);
        printf("Account Holder Name: %s\n", accounts[i].accountHolderName);
        printf("Balance: %.2f\n", accounts[i].balance);
        printf("---------------------------\n");
    }
}

// Binary search function
int binarySearch(const Account accounts[], int size, int accountNumber) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (accounts[mid].accountNumber == accountNumber) {
            return mid;
        } else if (accounts[mid].accountNumber < accountNumber) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1; // Account not found
}

