#include "functionDeclarations.h"


/*
 * Emmanuel Carrillo
 * 02/16/2021
 * Pradhumna Shrestha
 * This program is a simple banking account simulator, that will allow a user to run this program more than once and it
 * will allow the user to pick from a variety of options.
 */


int main(){

    // Declaration of variables in order to hold the user's personal and business account current balances, as well
    // as an enum in order to hold the menu choices that will be displayed to the user, and two vectors of type double
    // in order to hold the users transactions and display them if the user wishes to look at their past transactions.
    // Vector's were used since they can grow dynamically in size therefore saving space and making the program run
    // faster.

    double personalAccCurrentBal = 1000.00, businessAccCurrentBal = 10000.00;
    enum MenuChoice {process = 1, display = 2, quit = 3};
    MenuChoice menuOption;
    Account userAccount;
    vector<double> personalTransactions;
    vector<double> businessTransactions;

    // Declaration of variables in order to save the users name, account number, current transaction amount, the users
    // choice, and a variable to see if one should exit the loop.
    string name, userAccNum;
    int userOption = 0;
    double transactionAmount = 0;
    char userChoice;
    bool shouldExit = false;

    // Displaying Welcome Message to the user.
    welcomeMessage();

    // Calling the function "getName" in order to get the users name, the users name will be validated within the
    // function.
    getName(name);

    // Prompting the user for their account number and validating their input. If the account number is valid the user's
    // account number is than encrypted.
    getAccountNumber(userAccNum);
    encryptAccountNumber(userAccNum);

    bool isValid = true;
    // Start of the do-while loop.
    do{

        // Prompting the user what they would like to do today, if the user inputs an invalid value, the loop will
        // iterate again. The function "charToIntConvertor" is called in order to change the character value
        // to an integer in order to use the value for a type casting of MenuChoice.
        cout << "1. Process Accounts\n2. Display Account Information\n3. Quit\n";
        cout << "Please enter your choice: ";
        cin >> userChoice;
        charToIntConvertor(userChoice, userOption);
        menuOption = static_cast<MenuChoice>(userOption);

        // Start of the switch case.
        switch(menuOption){

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
                cout << "Wrong Choice!\nPlease Choose From The Appropriate Options." << endl;

        }


    }while(!(shouldExit));



    return 0;
}






