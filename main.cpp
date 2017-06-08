/*********************************************************************/
/*                                                                   */
/*Jared Bain                                            Homework 5   */
/*CISC3110                                              Section WQ6  */
/*                                                                   */
/*********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>


using namespace std;

//Constant Definition
const int Max_Num = 100;

//Prototypes
void menu();
int readaccts(int [], double[], int);
int findacct (int [], int, int);
void withdrawal (int [], double [], int, ofstream &outfile);
void deposit (int [], double [], int, ofstream &outfile);
int new_acct (int [], double [], int, ofstream &outfile);
void bankBalance (int [], double [], int, ofstream &outfile);
void print_accts (int [], double [], int, ofstream &datafile);
int delete_acct (int [], double [], int, ofstream &outfile);



int main()
{
    int acctnum [Max_Num];
    double balance [Max_Num];
    int num_accts;
    char choice;
    bool quit = true;

    //Open output file
    ofstream outfile ("bankoutput.txt");
    outfile.setf(ios:: fixed, ios:: floatfield);

    //Decimal precision
    outfile.precision(2);

    num_accts = readaccts(acctnum, balance, Max_Num);
    print_accts(acctnum, balance, num_accts, outfile);

    do
    {
        menu();
        cin >> choice;
        switch (choice)
        {
        case 'Q':
        case 'q':
            quit = false;

            print_accts(acctnum, balance, num_accts, outfile);
            break;
        case 'B':
        case 'b':
            bankBalance(acctnum, balance, num_accts, outfile);
            break;
        case 'D':
        case 'd':
            deposit(acctnum, balance, num_accts, outfile);
            break;
        case 'W':
        case 'w':
            withdrawal(acctnum, balance, num_accts, outfile);
            break;
        case 'N':
        case 'n':
            num_accts = new_acct(acctnum, balance, num_accts, outfile);
            break;
        case 'X':
        case 'x':
            num_accts = delete_acct(acctnum, balance, num_accts, outfile);
            break;

                default:
                    outfile << "Error: '" << choice << "' is an invalid input selection - try again" << endl << endl << endl;
                    break;
        }

    }

    while (quit);
        outfile.close(); //Closes output file
        system ("pause");
        return 0;
}

//Main Menu for Transaction
void menu()
{
    cout << endl;
    cout << "Which Transaction Would You Like To Do Today?: " << endl;
    cout << "\t W -- Withdrawal" << endl;
    cout << "\t D -- Deposit" << endl;
    cout << "\t N -- New Account" << endl;
    cout << "\t B -- Balance" << endl;
    cout << "\t X -- Delete Account" << endl;
    cout << "\t Q -- Quit" << endl;
    cout << endl << "\t Choose One Selection: ";

    return;
}

int readaccts(int acctnum[], double balance [], int max_accts)
{
    ifstream datafile ("bankinfo.txt");
    int cnt = 0;

    while (datafile >> acctnum [cnt] && cnt < max_accts)
    {
        //Read in file
        datafile >> balance[cnt];
        cnt++;
    }

        datafile.close();
        return cnt;
}

int findacct(int acctnum[], int num_accts, int accountNo)
{
    for (int index = 0; index < num_accts; index++)
    if (acctnum[index] == accountNo)
            return index;
    return -1;
}

void print_accts(int acctnum[], double balance[], int num_accts, ofstream &datafile)
{
    datafile << endl << endl;
    datafile <<"\t\t Details of Bank Accounts" << endl << endl;
    datafile << "Account   Balance" << endl << endl;

        for (int index = 0; index < num_accts; index ++)
        {
            datafile << acctnum[index];
            datafile << "\t$" << balance[index];
            datafile << endl;
        }
        return;
}

void bankBalance(int acctnum[], double balance[], int num_accts, ofstream &outfile)
{
    int accountNo;
    int index;
    cout << endl << "Enter Account Number: ";
    cin>> accountNo;

    index = findacct(acctnum, num_accts, accountNo);
            if (index == -1)
            {
                outfile << endl << "Transaction Requested: Balance Inquiry" << endl;
                outfile << "Error: Account Number " << accountNo << "does not exist" << endl;
            }
            else
            {
                outfile << endl << "Transaction Requested: Balance Inquiry" << endl;
                outfile << "Account Number: " << accountNo << endl;
                outfile << "Current Balance: $" << balance[index] << endl;
            }

            return;
}

void deposit(int acctnum[], double balance[], int num_accts, ofstream &outfile)
{
    int accountNo;
    int index;
    double amount_to_deposit;

    cout << endl << "Enter the account number: ";
    cin >> accountNo;

    index = findacct(acctnum, num_accts, accountNo);
        if ( index == -1)
        {
            outfile << endl << "Transaction Requested: Deposit" << endl;
            outfile << "Error: Account Number " << accountNo << " does not exist" << endl;
        }
        else
        {
            cout << "Enter amount to deposit: ";
            cin >> amount_to_deposit;

            //if invalid amount
            if (amount_to_deposit <=0.00)
            {
                outfile << endl << "Transaction Requested: Deposit" << endl;
                outfile << "Account Number: " << accountNo << endl;
                outfile << "Error: " << amount_to_deposit << " is an invalid amount" << endl;
            }
            else
            {
                outfile << endl << "Transaction Requested: Deposit" << endl;
                outfile << "Account Number: " << accountNo << endl;
                outfile << "Previous Balance: $" << balance[index] << endl;
                outfile << "Amount to Deposit: $" << amount_to_deposit << endl;

                balance[index] += amount_to_deposit;
                outfile << "New Balance: $" << balance[index] << endl;
            }
        }
        return;
}


void withdrawal(int acctnum[], double balance[], int num_accts, ofstream &outfile)
{
    int accountNo;
    int index;
    double amount_to_withdraw;

    cout << endl << "Enter the account number: ";
    cin >> accountNo;

    index = findacct(acctnum, num_accts, accountNo);
        if ( index == -1)
        {
            outfile << endl << "Transaction Requested: Withdrawal" << endl;
            outfile << "Error: Account Number " << accountNo << " does not exist" << endl;
        }
        else
        {
            cout << "Enter amount to withdraw: ";
            cin >> amount_to_withdraw;

            //If invalid amount
            if (amount_to_withdraw <=0.00)
            {
                outfile << endl << "Transaction Withdrawal" << endl;
                outfile <<"Amount Number: " << accountNo << endl;
                outfile << "Error: " << amount_to_withdraw << "is an invalid amount" << endl;
            }
            else
            {
                outfile << endl << "Transaction Requested: Withdrawal" << endl;
                outfile << "Account Number: " << accountNo << endl;
                outfile << "Previous Balance: $" << balance[index] << endl;
                outfile << "Amount to Withdraw: $" << amount_to_withdraw << endl;

                balance[index] -= amount_to_withdraw;
                outfile << "New Balance: $" << balance[index] << endl;
            }
        }
        return;
}

int new_acct(int acctnum[], double balance[], int num_accts, ofstream &outfile)
{
    return num_accts;
}

int delete_acct(int acctnum[], double balance[], int num_accts, ofstream &outfile)
{
    return num_accts;
}
