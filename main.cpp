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
void accountNumberValidator(int &accountNumber);
void accountNumberEncryption(int &accountNumber);
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


    // Prompting the user for their name and validating their input.
    cout << "Please enter your name: ";
    getline(cin, name);
    nameValidator(name);
    capitalNameConvertor(name);

    // Prompting the user for their account number and validating their input. If the account number is valid the user's
    // account number is than encrypted.
    cout << "Please enter your account number: ";
    cin >> accountNumber;
    accountNumberValidator(accountNumber);
    accountNumberEncryption(accountNumber);

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

    cout << endl;
    cout << "+===========================================+" << endl;
    cout << " Computer Science and Engineering" << endl;
    cout << " CSCE 1030 - Computer Science I" << endl;
    cout << " Emmanuel Carrillo ec0663; ec0663@my.unt.edu" << endl;
    cout << "+===========================================+" << endl << endl;

}


void nameValidator(string &name){

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

    for(int index = 0; index < name.size(); index++){
        if(islower(name.at(0))){
            name.at(index) = toupper(name.at(index));
        }

        if(isspace(name.at(index))){
            name.at(index + 1) = toupper(name.at(index + 1));
        }
    }
}


void accountNumberValidator(int &accountNumber){

    int tempValue = accountNumber;
    int numberOfDigits = 0;

    while(tempValue != 0){
        numberOfDigits++;
        tempValue /= 10;
    }

    while(numberOfDigits != 6){

        numberOfDigits = 0;
        cout << "Your account number is a 6-digit number. Enter again: ";
        cin >> accountNumber;

        tempValue = accountNumber;

        while(tempValue != 0) {
            numberOfDigits++;
            tempValue /= 10;
        }
    }
}


void accountNumberEncryption(int &accountNumber){

    int temp = 0;
    int numberOfDigits = 0;

    srand(time(0));

    int generatedValue = (rand() % 100000) + 200001;

    accountNumber += generatedValue;

    temp = accountNumber;

    while(temp != 0){
        numberOfDigits++;
        temp /= 10;
    }

    if(numberOfDigits > 6){

        accountNumber %= 1000000;

    }


}


void personalAccountCalculator(const double personalAccMinBal, double &persAccCurrBal, double transactionAmount){

    persAccCurrBal += transactionAmount;
    if(persAccCurrBal < personalAccMinBal){
        cout << "Your personal balance cannot be less than minimum balance. Transaction denied.\n";
        persAccCurrBal -= transactionAmount;
    }

    cout << setprecision(2) << fixed;
    cout << "Personal Account Balance: $" << persAccCurrBal << endl;

}


void isBusinessAccountOverdrawn(const double bussAccMinBal, double bussAccCurrBal, bool &isBussAccOverdrawn){

    if(bussAccCurrBal < bussAccMinBal){
        isBussAccOverdrawn = true;
    }
    if(bussAccCurrBal >= bussAccMinBal){
        isBussAccOverdrawn = false;
    }

}


void businessAccountCalculator(double &bussAccCurrBal, double transactionAmount, bool &isBussAccOverdrawn){

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

    cout << endl;
    cout << "Name: " << name << endl;
    cout << "Account Number: (Encrypted): " << accountNumber << endl;
    cout << "Business Account Balance: $" << bussAccBal << endl;
    cout << "Personal Account Balance: $" << persAccBal << endl;


}
