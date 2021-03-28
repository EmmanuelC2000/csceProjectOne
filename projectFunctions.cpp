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

    /*
     * Function: getName
     * Parameters: A string parameter passed by reference in order to hold and change the actual value held in the main
     * function.
     * Return type: Void.
     * Description: This function will ask the user for their name and it will call "nameValidator" function in order
     * to validate the user's input, once their input has been validated "capitalNameConvertor" function in order
     * to capitalize at least each initial.
     */

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

    /*
     * Function: getAccountNumber
     * Parameters: A string parameter that has been passed by reference in order to hold and change the actual value
     * in the main function.
     * Return type: Void.
     * Description: This function will ask the user to input an account number utilizing a string and
     * the function "accountNumberValidation" will be called in order to validate their input.
     */

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
    * entering a valid account number, and save the result in the account number variable in the main function.
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

    /*
    * Function: encryptAccountNumber
    * Parameters: A string parameter passed by reference in order to hold and change the corresponding value in the
    * main function.
    * Return type: Void.
    * Description: This function will be responsible for encrypting the user's account number by utilizing an array
    * of random integers and adding each random integer to each string index in order to populate random values.
    */

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


void charToIntConvertor(char userChoice, int &userOption){

    /*
    * Function: charToIntConvertor
    * Parameters: A character parameter in order to hold a value from the function that will call this one, as well as
    * an integer value that has been passed by reference in order to actually hold the value and change it when the
    * function is called.
    * Return type: Void.
    * Description: The sole purpose of this function is to convert a character value to its corresponding integer value.
    */

    userOption = (userChoice - 48);
}


void processAccount(Account &userAccount, double transactionAmount, double &personalAccCurrentBal, double &businessAccCurrentBal, vector<double> &personal, vector <double> &business) {

    /*
    * Function: processAccount.
    * Parameters: This function will contain an enumeration, double, and a vector of type double, out of the six
    * parameters four of them have been passed by reference in order for their values to change in the main
    * function.
    * Return type: Void.
    * Description: The job of this function is to display to the user a set of options in order for them to process
    * either a personal or a business transaction.
    */

    // Declaration of local variables in order to hold account type, two character variables in order to hold the
    // answers of certain options and two boolean variables in order to check if the account type is valid or if the
    // business account has been over drawn.
    int accountType;
    char userChoice, userOption;
    bool isAccountTypeValid = true, isBussAccOverDrawn = false;


    // Start of the do-while loop.
    do {

        // Setting "isAccountTypeValid" to true in order to prevent an infinite loop from starting. The function
        // "isBusinessAccountOverDrawn will be called in order to check if the user's business account has been
        // over drawn.
        isAccountTypeValid = true;
        isBusinessAccountOverDrawn(businessAccMinBal, businessAccCurrentBal, isBussAccOverDrawn);

        // Prompting the user for their account type and calling the function "charToIntConvertor" in order to convert
        // their input to its corresponding integer value, and then it will be casted into its correct "Account" value.
        cout << "What is your account type? \"1\" for Personal, \"2\" for Business: ";
        cin >> userChoice;
        charToIntConvertor(userChoice, accountType);
        userAccount = static_cast<Account>(accountType);

        // Start of the switch case.
        switch (userAccount) {

            case personalAccount:
                cout << "Enter transaction amount: $";
                cin >> transactionAmount;
                personalAccountCalculator(personalAccCurrentBal, transactionAmount, personal);
                cout << "Do you want to process another transaction? Y/N: ";
                cin >> userOption;
                break;

            case businessAccount:
                cout << "Enter transaction amount: $";
                cin >> transactionAmount;
                businessAccountCalculator(businessAccCurrentBal, transactionAmount, isBussAccOverDrawn, business);
                cout << "Do you want to process another transaction? Y/N: ";
                cin >> userOption;
                break;

            default:
                cout << "Wrong Choice!\nPlease Choose From The Appropriate Options." << endl;
                isAccountTypeValid = false;


        }

    }while (!(isAccountTypeValid) || toupper(userOption) == 'Y');
}


void personalAccountCalculator(double &persAccCurrBal, double transactionAmount, vector<double> &personal){

    /*
     * Function: personalAccountCalculator
     * Parameters: A constant double, a double to hold the user's personal account current balance and a double in order
     * to hold the transaction amount, and a vector of type double in order to add values when the transaction amount
     * is valid.
     * Return type: Void.
     * Description: This function will perform a calculation and determine if the personal account balance is less
     * than the personal account minimum balance and if so it will deny the transaction and revert back to the correct
     * value. The function will also do all of the calculations and save the appropriate value to the personalAccCurrBal
     * variable in the main function, this function will also be responsible for adding values to a vector if the
     * transaction amount is valid.
     */

    // Start of the necessary logic in order to add or subtract the transaction amount from the personal account
    // current balance. The transaction amount will also be added to the vector.
    persAccCurrBal += transactionAmount;
    personal.push_back(transactionAmount);

    // If the transaction amount brings the personal account minimum balance under the transaction amount will be denied
    // and the value will be removed from the vector.
    if(persAccCurrBal < personalAccMinBal){
        cout << "Your personal balance cannot be less than minimum balance. Transaction denied.\n";
        persAccCurrBal -= transactionAmount;
        personal.pop_back();
    }

    // Displaying the results to the user using fix decimal point notation.
    cout << setprecision(2) << fixed;
    cout << "Personal Account Balance: $" << persAccCurrBal << endl;

}


void isBusinessAccountOverDrawn(const double bussAccMinBal, double bussAccCurrBal, bool &isBussAccOverDrawn){

    /*
     * Function: isBusinessAccountOverDrawn
     * Parameters: const double to hold the business account minimum balance, a double to hold the business account
     * current balance and a boolean variable to flag if the business account is over drawn.
     * Return type: Void.
     * Description: This function will determine if the business account is overdrawn by switching the boolean variable
     * between true or false based on the data provided.
     */

    if(bussAccCurrBal < bussAccMinBal){
        isBussAccOverDrawn = true;
    }
    if(bussAccCurrBal >= bussAccMinBal){
        isBussAccOverDrawn = false;
    }

}


void businessAccountCalculator(double &bussAccCurrBal, double transactionAmount, bool &isBussAccOverDrawn, vector<double> &business){

    /*
     * Function: businessAccountCalculator
     * Parameters: double to hold the business account current balance, a double to hold the transaction amount, a
     * boolean variable to perform a while statement if the condition is true, and a vector of type double in order
     * to add the valid transaction amounts to the vector.
     * Return type: Void.
     * Description: This function will calculate the new business account current balance and it will save the result
     * in the appropriate variable in the main function. If the current balance is less than the minimum balance after the
     * second business transaction an appropriate message will be displayed to the user. This function will also add
     * the appropriate transaction amount values to the vector.
     */

    // Adding or subtracting the appropriate values from the business account current balance and adding the values to
    // the vector.
    bussAccCurrBal += transactionAmount;
    business.push_back(transactionAmount);

    // If statement in order to check if the business account is over drawn and if it is a message will be displayed
    // to the user.
    if(isBussAccOverDrawn){
        bussAccCurrBal -= 10;
        cout << "Your balance is less than the required minimum. There will be a $10.00";
        cout << " fee for every transaction." << endl;
    }

    // Displaying the business account balance to the user using fixed point decimal notation.
    cout << setprecision(2) << fixed;
    cout << "Business Account Balance: $" << bussAccCurrBal << endl;

}


void displayAccount(Account &userAccount, const string name, const string userAccNum, vector<double> &personal, vector<double> &business){

    /*
     * Function: displayAccountSummary
     * Parameters: constant parameter to hold the name, account number, business account balance, personal account
     * balance, and two vector's of type double in order to the display the values stored in the vector.
     * Return type: Void.
     * Description: This function will display the user's information and the user will be prompted for which account
     * they wish to display the information for.
     */

    // Local variables in order to hold the boolean variable in order to check if the value provided is valid, as well
    // as an integer variable in order to hold the userOption for their account and two character variables in order to
    // determine if the vector should be sorted, and to hold the user choice for what account they wish to
    // display.
    int userOption = 0;
    bool isValid = true;
    char sortingOption, userChoice;

    do{

        // Setting isValid to true in case the user provides an incorrect value and the loop is executed again.
        isValid = true;

        // Displaying to the user their name, and their encrypted account number.
        cout << "Name: " <<  name << endl;
        cout << "Account Number (Encrypted): " << userAccNum << endl;

        // Prompting the user for which account they wish to display.
        cout << "Which account do you want to display? \"1\" for Personal, \"2\" for Business: ";
        cin >> userChoice;
        charToIntConvertor(userChoice, userOption);
        userAccount = static_cast<Account>(userOption);

        switch(userAccount){

            case personalAccount:
                cout << "Do you want to sort? Y/N: ";
                cin >> sortingOption;
                displayValues(personal, sortingOption);
                break;

            case businessAccount:
                cout << "Do you want to sort? Y/N: ";
                cin >> sortingOption;
                displayValues(business, sortingOption);
                break;

            default:
                cout << "Invalid Option! Please Try Again\n";
                isValid = false;

        }


    }while(!(isValid));


}


void sortValues(vector<double> &transactionAmount){

    /*
    * Function: sortValues
    * Parameters: A vector of type double passed by reference in order to hold and manipulate the actual values stored
    * in the vector.
    * Description: This function will be responsible for sorting the values in the vector in ascending order.
    */

    // Local variable in order to hold a temporary value when making the switch.
    double tempValue = 0;

    // Start of the for loop in order to sort the values in the vector.
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


void displayValues(vector<double> &accountType, char sortingOption){

    /*
    * Function: displayValues
    * Parameters: A vector of type double that has been passed by reference in order to sort the values if the user
    * wishes to.
    * Description: The job of this function is to display the values stored in the vector and sort the array if the
    * correct sorting option has been provided. If the vector is empty meaning that no transactions have been made the
    * user will be notified using an appropriate message.
    */


    if(accountType.empty()){
        cout << "There have been no transactions made." << endl;
    }

    if(toupper(sortingOption) == 'Y'){
        sortValues(accountType);
    }


    for(int index = 0; index < accountType.size(); index++){

        cout << "$" << accountType.at(index) << endl;
    }

}

