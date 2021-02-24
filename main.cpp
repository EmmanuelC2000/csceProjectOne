#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;


// Prototyping the necessary functions for main method to run.
void welcomeMessage();
void nameValidator(string &name, bool &isAlphaOrSpace);
void capitalNameConvertor(string &name);
void accountNumberValidator(int &accountNumber);
void accountNumberEncryption(int &accountNumber);
void accountTypeValidator(int &accountType);
void displayAccountSummary(const string &name, int accountNumber, double &persAccBal, double &bussAccBal);
void personalAccountCalculator(double personalAccMinBal, double &persAccCurrBal, double &transactionAmount);
void businessAccountCalculator(double bussAccMinBal, double &bussAccCurrBal, double &transactionAmount);




int main(){

    // Displaying Welcome Message to the user.
    welcomeMessage();

    // Declaration of variables in order to hold minimum balances for both personal and business accounts as well as
    // the starting balances for both accounts.
    const double personalAccMinBal = 1000.00, businessAccMinBal = 10000.00;
    double personalAccCurrentBal = 1000.00, businessAccCurrentBal = 10000.00;
    enum account {personalAccount = 1, businessAccount = 2};

    // Declaration of variables in order to save the users name, account number, account type and validators.
    string name;
    int accountNumber = 0, accountType = 0;
    double transactionAmount = 0;
    char userChoice;
    bool isAlphaOrSpace;

    // Prompting the user for their name and validating their input.
    cout << "Please enter your name: ";
    getline(cin, name);
    nameValidator(name, isAlphaOrSpace);
    capitalNameConvertor(name);

    // Prompting the user for their account number and validating their input.
    cout << "Please enter your account number: ";
    cin >> accountNumber;
    accountNumberValidator(accountNumber);
    accountNumberEncryption(accountNumber);

    // Start of the do-while loop.
    do{

        // Prompting the user for their account type and validating their input.
        cout << R"(What is your account type? "1" for Personal, "2" for )";
        cout << "Business: ";
        cin >> accountType;
        accountTypeValidator(accountType);

        // Performing a switch case block if account type is valid.
        switch(accountType){

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
                businessAccountCalculator(businessAccMinBal, businessAccCurrentBal, transactionAmount);
                cout << "Do you want to process another transaction? Y/N: ";
                cin >> userChoice;
        }

    }while(toupper(userChoice) == 'Y');

    // Displaying the users account summary after they have completed their transactions.
    displayAccountSummary(name, accountNumber, businessAccCurrentBal, personalAccCurrentBal);



    return 0;
}




void welcomeMessage(){

    cout << endl;
    cout << "=============================================" << endl;
    cout << " Computer Science and Engineering" << endl;
    cout << " CSCE 1030 - Computer Science I" << endl;
    cout << " Emmanuel Carrillo ec0663; ec0663@my.unt.edu" << endl;
    cout << "=============================================" << endl;

}


void nameValidator(string &name, bool &isAlphaOrSpace){

    for(int index = 0; index < name.length(); index++) {
        if (!(isalpha(name.at(index))) && !(isspace(name.at(index)))) {
            isAlphaOrSpace = false;
        } else {
            isAlphaOrSpace = true;
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

    while(numberOfDigits < 6 || numberOfDigits > 6){

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


void accountTypeValidator(int &accountType){

    while(accountType != 1 && accountType != 2){

        cout << "Wrong choice! Please enter again.\n";
        cout << R"(What is your account type? "1" for Personal, "2" for )";
        cout << "Business: ";
        cin >> accountType;
    }
}


void personalAccountCalculator(const double personalAccMinBal, double &persAccCurrBal, double &transactionAmount){

    persAccCurrBal += transactionAmount;
    if(persAccCurrBal < personalAccMinBal){
        cout << "Your personal balance cannot be less than minimum balance. Transaction denied.\n";
        persAccCurrBal -= transactionAmount;
    }

    cout << "Personal Account Balance: $" << persAccCurrBal << endl;

}


void businessAccountCalculator(const double bussAccMinBal, double &bussAccCurrBal, double &transactionAmount){

    bussAccCurrBal += transactionAmount;
    if(bussAccCurrBal < bussAccMinBal){

        bussAccCurrBal -= 10;
        cout << "Your balance is less than the required minimum. There will be a $10.00";
        cout << " fee for every transaction." << endl;
    }

    cout << "Business Balance: $" << bussAccCurrBal << endl;
}


void displayAccountSummary(const string &name, int accountNumber, double &bussAccBal, double &persAccBal){

    cout << setprecision(2) << fixed;
    cout << endl;
    cout << "Name: " << name << endl;
    cout << "Account Number: (Encrypted): " << accountNumber << endl;
    cout << "Business Account Balance: $" << bussAccBal << endl;
    cout << "Personal Account Balance: $" << persAccBal << endl;


}
