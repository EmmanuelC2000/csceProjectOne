#include "functionDeclarations.h"

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


void getName(string &name){

    cout << "Please enter your name: ";
    getline(cin, name);
    nameValidator(name);
    capitalNameConvertor(name);

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


void getAccountNumber(string &userAccNum){

    cout << "Please enter your account number: ";
    getline(cin, userAccNum);
    accountNumberValidation(userAccNum);

}


void accountNumberValidation(string &userAccNum){

    /*
    * Function: accountNumberValidator
    * Parameters: A string parameter and an account number parameter in order to save the user's account number.
    * Return type: Void.
    * Description: This function will validate the user's account number and if invalid it will ask them to keep
    * entering a valid account number, this function will also execute the encryption of the account number and save
     * the result in the account number variable in the main function.
    */



    for(int index = 0; index < userAccNum.size(); index++){

        while(!isdigit(userAccNum.at(index)) || userAccNum.size() != 6){
            cout << "Your account number can only contain digits and it must be";
            cout << " a six digit number" << endl;
            cout << "Please enter again!: ";
            cin >> userAccNum;
        }
    }



}

void encryptAccountNumber(string &userAccNum){

    srand(time(0));


    const int SIZE = userAccNum.length();
    int encryptArray[SIZE];

    for(int index = 0; index < SIZE; index++){

        encryptArray[index] = (rand() % 11) + 10;
    }

    for(int index = 0; index < userAccNum.size(); index++){

        userAccNum.at(index) += encryptArray[index];

    }

}


void processAccount(Account &userAccount, double transactionAmount, double &personalAccCurrentBal, double &businessAccCurrentBal, vector<double> &personal, vector <double> &business) {

    int accountType;
    char userChoice;
    bool isAccountTypeValid = true, isBussAccOverDrawn = false;


    do {

        isAccountTypeValid = true;
        isBusinessAccountOverdrawn(businessAccMinBal, businessAccCurrentBal, isBussAccOverDrawn);

        cout << R"(What is your account type? "1" for Personal, "2" for Business: )";
        cin >> accountType;
        userAccount = static_cast<Account>(accountType);

        switch (userAccount) {

            case personalAccount:
                cout << "Enter transaction amount: $";
                cin >> transactionAmount;
                personalAccountCalculator(personalAccCurrentBal, transactionAmount, personal);
                cout << "Do you want to process another transaction? Y/N: ";
                cin >> userChoice;
                break;

            case businessAccount:
                cout << "Enter transaction amount: $";
                cin >> transactionAmount;
                businessAccountCalculator(businessAccCurrentBal, transactionAmount, isBussAccOverDrawn, business);
                cout << "Do you want to process another transaction? Y/N: ";
                cin >> userChoice;
                break;

            default:
                cout << "Wrong choice! Please enter again.\n";
                isAccountTypeValid = false;


        }

    }while (!(isAccountTypeValid) || toupper(userChoice) == 'Y');
}


void personalAccountCalculator(double &persAccCurrBal, double transactionAmount, vector<double> &personal){

    /*
     * Function: personalAccountCalculator
     * Parameters: A constant double, a double to hold the user's personal account current balance and a double in order
     * to hold the transaction amount.
     * Return type: Void.
     * Description: This function will perform a calculation and determine if the personal account balance is less
     * than the personal account minimum balance and if so it will deny the transaction and revert back to the correct
     * value. The function will also do all of the calculations and save the appropriate value to the personalAccCurrBal
     * variable in the main function.
     */

    persAccCurrBal += transactionAmount;
    personal.push_back(transactionAmount);
    if(persAccCurrBal < personalAccMinBal){
        cout << "Your personal balance cannot be less than minimum balance. Transaction denied.\n";
        persAccCurrBal -= transactionAmount;
        personal.pop_back();
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


void businessAccountCalculator(double &bussAccCurrBal, double transactionAmount, bool &isBussAccOverdrawn, vector<double> &business){

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
    business.push_back(transactionAmount);

    if(isBussAccOverdrawn){
        bussAccCurrBal -= 10;
        cout << "Your balance is less than the required minimum. There will be a $10.00";
        cout << " fee for every transaction." << endl;
    }
    cout << setprecision(2) << fixed;
    cout << "Business Account Balance: $" << bussAccCurrBal << endl;

}


void displayAccount(Account &userAccount, const string name, const string userAccNum, vector<double> &personal, vector<double> &business){

    /*
     * Function: displayAccountSummary
     * Parameters: constant parameter to hold the name, account number, business account balance, and personal account
     * balance.
     * Return type: Void.
     * Description: This function will display to the user the final results of their transaction.
     */

    int userChoice = 0;
    bool isValid = true;
    char sortingOption;

    do{

        isValid = true;

        cout << "Name: " <<  name << endl;
        cout << "Account Number (Encrypted): " << userAccNum << endl;

        cout << "Which account do you want to display? \"1\" for Personal, \"2\" for Business: ";
        cin >> userChoice;
        userAccount = static_cast<Account>(userChoice);

        switch(userAccount){

            case personalAccount:
                cout << "Do you want to sort? Y/N: ";
                cin >> sortingOption;
                if(personal.empty()){
                    cout << "There have been no transactions made." << endl;
                    break;
                }
                sortingOption = toupper(sortingOption);
                if(sortingOption == 'Y'){
                    sortValues(personal);
                }
                for(int index = 0; index < personal.size(); index++){

                    cout << "$" << personal.at(index) << endl;
                }
                break;

            case businessAccount:
                cout << "Do you want to sort? Y/N: ";
                cin >> sortingOption;
                if(business.empty()){
                    cout << "There have been no transactions made." << endl;
                    break;
                }
                sortingOption = toupper(sortingOption);
                if(sortingOption == 'Y'){
                    sortValues(business);
                }
                for(int index = 0; index < business.size(); index++){

                    cout << "$" << business.at(index) << endl;
                }

                break;

            default:
                cout << "Invalid Option! Please Try Again\n";
                isValid = false;

        }


    }while(!(isValid));


}


void sortValues(vector<double> &transactionAmount){

    double tempValue = 0;

    for(int outerIndex = 0; outerIndex < (transactionAmount.size() - 1); outerIndex++){

        for(int innerIndex = 0; innerIndex < (transactionAmount.size() - 1 - outerIndex); innerIndex++){

            if(transactionAmount.at(innerIndex) > transactionAmount.at(innerIndex + 1)) {
                tempValue = transactionAmount.at(innerIndex);
                transactionAmount.at(innerIndex) = transactionAmount.at(innerIndex + 1);
                transactionAmount.at(innerIndex + 1) = tempValue;
            }
        }
    }

}

