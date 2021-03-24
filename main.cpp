#include "functionDeclarations.h"


/*
 * Emmanuel Carrillo
 * 02/16/2021
 * Pradhumna Shrestha
 * This program is a simple banking account simulator.
 */


int main(){

    // Displaying Welcome Message to the user.
    welcomeMessage();

    // Declaration of variables in order to hold minimum balances for both personal and business accounts as well as
    // the starting balances for both accounts. Also declaring an enum in order to utilize it in the switch statement.

    double personalAccCurrentBal = 1000.00, businessAccCurrentBal = 10000.00;
    enum MenuChoice {process = 1, display = 2, quit = 3};
    MenuChoice usersOption;
    Account userAccount;
    vector<double> personalTransactions;
    vector<double> businessTransactions;

    // Declaration of variables in order to save the users name, account number, account type and validators.
    string name;
    string userAccNum;
    int accountType = 0, menuOption = 0;
    double transactionAmount = 0;
    char userChoice;
    bool shouldExit = false;


    // Prompting the user for their name and validating their input.
    getName(name);

    // Prompting the user for their account number and validating their input. If the account number is valid the user's
    // account number is than encrypted.
    getAccountNumber(userAccNum);
    encryptAccountNumber(userAccNum);

    // Start of the do-while loop.
    do{
        cout << "1. Process Accounts\n2. Display Account Information\n3. Quit\n";
        cout << "Please enter your choice: ";
        cin >> menuOption;
        userChoice = static_cast<MenuChoice>(menuOption);

        switch(userChoice){

            case process:
                processAccount(userAccount, transactionAmount, personalAccCurrentBal,businessAccCurrentBal, personalTransactions, businessTransactions);
                break;

            case display:
                displayAccount(userAccount, name, userAccNum, personalTransactions, businessTransactions);
                break;

            case quit:
                cout << "Thank you for using our services!\nGoodbye!\n";
                shouldExit = true;
                break;

            default:
                cout << "Incorrect Choice.\nPlease Try Again!" << endl;

        }


    }while(!(shouldExit));





    return 0;
}


