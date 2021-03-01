/*
 * Emmanuel Carrillo
 * 02/16/2021
 * Pradhumna Shrestha
 * This program is a simple banking account simulator.
 */

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;


// Prototyping the necessary functions for main method to run.
void welcomeMessage();
void nameValidator(string &name);
void capitalNameConvertor(string &name);
void accountNumberValidationAndEncryption(string &userString, int &accountNumber);
void displayAccountSummary(string name, int accountNumber, double persAccBal, double bussAccBal);
void personalAccountCalculator(double personalAccMinBal, double &persAccCurrBal, double transactionAmount);
void businessAccountCalculator(double &bussAccCurrBal, double transactionAmount, bool &isBussAccOverDrawn);
void isBusinessAccountOverdrawn(const double bussAccMinBal, double bussAccCurrBal, bool &isBussAccOverdrawn);




int main(){

    // Displaying Welcome Message to the user.
    welcomeMessage();

    // Declaration of variables in order to hold minimum balances for both personal and business accounts as well as
    // the starting balances for both accounts. Also declaring an enum in order to utilize it in the switch statement.
    const double personalAccMinBal = 1000.00, businessAccMinBal = 10000.00;
    double personalAccCurrentBal = 1000.00, businessAccCurrentBal = 10000.00;
    enum Account {personalAccount = 1, businessAccount = 2};
    Account userAccount;

    // Declaration of variables in order to save the users name, account number, account type and validators.
    string name;
    int accountNumber = 0, accountType = 0;
    double transactionAmount = 0;
    char userChoice;
    bool isAccountTypeValid, isBusinessAccountOverDrawn = false;
    string userString;


    // Prompting the user for their name and validating their input.
    cout << "Please enter your name: ";
    getline(cin, name);
    nameValidator(name);
    capitalNameConvertor(name);

    // Prompting the user for their account number and validating their input. If the account number is valid the user's
    // account number is than encrypted.
    cout << "Please enter your account number: ";
    getline(cin, userString);
    accountNumberValidationAndEncryption(userString, accountNumber);


    // Start of the do-while loop.
    do{

        isAccountTypeValid = true;
        isBusinessAccountOverdrawn(businessAccMinBal, businessAccCurrentBal, isBusinessAccountOverDrawn);

        // Prompting the user for their account type and validating their input.
        cout << R"(What is your account type? "1" for Personal, "2" for Business: )";
        cin >> accountType;
        userAccount = static_cast<Account>(accountType);

        // Performing a switch case based on the user's account type if the user types in an invalid account type
        // the default statement is executed and the do-while loop is performed as many times as needed until the user
        // provides an adequate choice.
        switch(userAccount){

            case personalAccount:
                cout << "Enter transaction amount: $";
                cin >> transactionAmount;
                personalAccountCalculator(personalAccMinBal, personalAccCurrentBal, transactionAmount);
                cout << "Do you want to process another transaction? Y/N: ";
                cin >> userChoice;
                break;

            case businessAccount:
                cout << "Enter transaction amount: $";
                cin >> transactionAmount;
                businessAccountCalculator(businessAccCurrentBal, transactionAmount,isBusinessAccountOverDrawn);
                cout << "Do you want to process another transaction? Y/N: ";
                cin >> userChoice;
                break;

            default:
                cout << "Wrong choice! Please enter again.\n";
                isAccountTypeValid = false;
        }

    }while(toupper(userChoice) == 'Y' || !(isAccountTypeValid));

    // Displaying the users account summary after they have completed their transactions.
    displayAccountSummary(name, accountNumber, businessAccCurrentBal, personalAccCurrentBal);

    return 0;
}


// Start of function definitions.

void welcomeMessage(){

    /*
     * Function: welcomeMessage.
     * Parameters: N/A.
     * Return type: Void.
     * Description: This function displays a welcome message to the user.
     */

    cout << endl;
    cout << "+===========================================+" << endl;
    cout << " Computer Science and Engineering" << endl;
    cout << " CSCE 1030 - Computer Science I" << endl;
    cout << " Emmanuel Carrillo ec0663; ec0663@my.unt.edu" << endl;
    cout << "+===========================================+" << endl << endl;

}


void nameValidator(string &name){

    /*
     * Function: nameValidator
     * Parameters: A string data type referencing an actual value in the main program.
     * Return type: Void.
     * Description: This function will validate the user's name in the main function and it will keep asking them for a
     * name if the input is invalid.
     */

    bool isAlphaOrSpace = true;

    for(int index = 0; index < name.length(); index++) {
        if (!(isalpha(name.at(index))) && !(isspace(name.at(index)))) {
            isAlphaOrSpace = false;
            break;
        }
    }
    while(!isAlphaOrSpace){

        cout << "Your name can only have characters or spaces!\n";
        cout << "Please try Again!\n";
        cout << "Please enter a valid name: ";
        getline(cin, name);

        for(int index = 0; index < name.length(); index++) {
            if (!(isalpha(name.at(index))) && !(isspace(name.at(index)))) {
                isAlphaOrSpace = false;
                break;
            } else {
                isAlphaOrSpace = true;
            }
        }
    }
}


void capitalNameConvertor(string &name){

    /*
     * Function: capitalNameConvertor
     * Parameters: A string data type that will reference the name variable in the main program.
     * Return type: Void.
     * Description: This function will take the user's name and capitalize at least all of the initials and it will
     * actually change the value in the main function since this is also utilizing a reference before the name variable.
     */

    for(int index = 0; index < name.size(); index++){
        if(islower(name.at(0))){
            name.at(index) = toupper(name.at(index));
        }

        if(isspace(name.at(index))){
            name.at(index + 1) = toupper(name.at(index + 1));
        }
    }
}


void accountNumberValidationAndEncryption(string &userString, int &accountNumber){

    /*
    * Function: accountNumberValidator
    * Parameters: A string parameter and an account number parameter in order to save the user's account number.
    * Return type: Void.
    * Description: This function will validate the user's account number and if invalid it will ask them to keep
    * entering a valid account number, this function will also execute the encryption of the account number and save
     * the result in the account number variable in the main function.
    */

    srand(time(0));
    int generatedValue = (rand() % 100000) + 200001;

    for(int index = 0; index < userString.size(); index++){

        while(!isdigit(userString.at(index)) || userString.size() != 6){
            cout << "Your account number can only contain digits and it must be";
            cout << " a six digit number" << endl;
            cout << "Please enter again!: ";
            cin >> userString;
        }
    }

    accountNumber = stoi(userString);
    accountNumber += generatedValue;
    userString = to_string(accountNumber);

    if(userString.size() == 7){
        userString.erase(0,1);
        accountNumber = stoi(userString);
    }
}


void personalAccountCalculator(const double personalAccMinBal, double &persAccCurrBal, double transactionAmount){

    /*
     * Function: personalAccountCalculator
     * Parameters: A constant double, a double to hold the user's personal account current balance and a double in order
     * to hold the transaction amount.
     * Return type: Void.
     * Description: This function will perform a calculation and determine if the personal account balance is less
     * than the personal account minimum balance and if so it will deny the transaction and revert back to the correct
     * value. The function will also do all of the calculations and save the appropriate value to the personalAccCurrBal
     * varoiable in the main function.
     */

    persAccCurrBal += transactionAmount;
    if(persAccCurrBal < personalAccMinBal){
        cout << "Your personal balance cannot be less than minimum balance. Transaction denied.\n";
        persAccCurrBal -= transactionAmount;
    }

    cout << setprecision(2) << fixed;
    cout << "Personal Account Balance: $" << persAccCurrBal << endl;

}


void isBusinessAccountOverdrawn(const double bussAccMinBal, double bussAccCurrBal, bool &isBussAccOverdrawn){

    /*
     * Function: welcomeMessage.
     * Parameters: const double to hold the business account minimum balance, a double to hold the business account
     * current balance and a boolean variable to flag if the business account is over drawn.
     * Return type: Void.
     * Description: This function will determine if the business account is overdrawn by switching the boolean variable
     * between true or false based on the data provided.
     */

    if(bussAccCurrBal < bussAccMinBal){
        isBussAccOverdrawn = true;
    }
    if(bussAccCurrBal >= bussAccMinBal){
        isBussAccOverdrawn = false;
    }

}


void businessAccountCalculator(double &bussAccCurrBal, double transactionAmount, bool &isBussAccOverdrawn){

    /*
     * Function: welcomeMessage.
     * Parameters: double to hold the business account current balance, a double to hold the transaction amount, and
     * a boolean variable to perform a while statement if the condition is true.
     * Return type: Void.
     * Description: This function will calculate the new business account current balance and it will save the result
     * in the appropriate variable in the main function. If the current balance is less than the minimum balance after the
     * second business transaction an appropriate message will be displayed to the user.
     */

    bussAccCurrBal += transactionAmount;

    if(isBussAccOverdrawn){
        bussAccCurrBal -= 10;
        cout << "Your balance is less than the required minimum. There will be a $10.00";
        cout << " fee for every transaction." << endl;
    }
    cout << setprecision(2) << fixed;
    cout << "Business Account Balance: $" << bussAccCurrBal << endl;

}


void displayAccountSummary(const string name, const int accountNumber, const double bussAccBal, const double persAccBal){

    /*
     * Function: displayAccountSummary
     * Parameters: constant parameter to hold the name, account number, business account balance, and personal account
     * balance.
     * Return type: Void.
     * Description: This function will display to the user the final results of their transaction.
     */

    cout << endl;
    cout << "Name: " << name << endl;
    cout << "Account Number: (Encrypted): " << accountNumber << endl;
    cout << "Business Account Balance: $" << bussAccBal << endl;
    cout << "Personal Account Balance: $" << persAccBal << endl;


}
