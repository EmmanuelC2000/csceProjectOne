#include <iostream>
#include <string>
using namespace std;

void welcomeMessage();
void nameValidator(string &name, bool &isAlphaOrSpace);
void accountTypeValidator(int &accountType);
void displayAccountSummary(string name, int accountNumber, double persAccBal, double bussAccBal);
void personalAccountCalculator(double personalAccMinBal, double &persAccCurrBal, double &transactionAmount);
void businessAccountCalculator(double bussAccMinBal, double &bussAccCurrBal, double &transactionAmount);

int main(){

    welcomeMessage();

    const double personalAccMinBal = 1000.00, businessAccMinBal = 10000.00;
    double personalAccCurrentBal = 1000.00, businessAccCurrentBal = 10000.00;
    enum account {personalAccount = 1, businessAccount = 2};

    string name;
    int accountNumber = 0, accountType = 0;
    double transactionAmount = 0;
    char userChoice;
    bool isAlphaOrSpace;


    cout << "Please enter your name: ";
    getline(cin, name);
    nameValidator(name, isAlphaOrSpace);


    cout << "Please enter your account number: ";
    cin >> accountNumber;

    do{
        cout << "What is your account type? \"1\" for Personal, \"2\" for ";
        cout << "Business: ";
        cin >> accountType;
        accountTypeValidator(accountType);

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


void accountTypeValidator(int &accountType){

    while(accountType != 1 && accountType != 2){

        cout << "Wrong choice! Please enter again.\n";
        cout << "What is your account type? \"1\" for Personal, \"2\" for ";
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

void displayAccountSummary(string name, int accountNumber, double bussAccBal, double persAccBal){

    cout << endl;
    cout << "Name: " << name << endl;
    cout << "Account Number: (Encrypted): " << accountNumber << endl;
    cout << "Business Account Balance: $" << bussAccBal << endl;
    cout << "Personal Account Balance: $" << persAccBal << endl;


}
