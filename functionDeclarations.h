/*
 * This file will contain all of the necessary files and function declarations needed in order for the main function
 * to run.
 */


#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <vector>
using namespace std;


enum Account {personalAccount = 1, businessAccount = 2};
const double personalAccMinBal = 1000.00, businessAccMinBal = 10000.00;

void welcomeMessage();
void getName(string &name);
void nameValidator(string &name);
void capitalNameConvertor(string &name);
void getAccountNumber(string &userAccNum);
void accountNumberValidation(string &userAccNum);
void encryptAccountNumber(string &userAccNumber);
void charToIntConvertor(char userChoice, int &userOption);
void displayAccount(Account &userAccount, string name, string userAccNum, vector<double> &personal, vector<double> &business);
void personalAccountCalculator(double &persAccCurrBal, double transactionAmount, vector<double> &personal);
void businessAccountCalculator(double &bussAccCurrBal, double transactionAmount, bool &isBussAccOverDrawn, vector<double> &business);
void isBusinessAccountOverDrawn(const double bussAccMinBal, double bussAccCurrBal, bool &isBussAccOverdrawn);
void sortValues(vector<double> &transactionAmount);
void displayValues(vector<double> &accountType, char sortingOption);
void processAccount(Account &userAccount, double transactionAmount, double &personalAccCurrentBal, double &businessAccCurrentBal, vector<double> &personal, vector <double> &business);
