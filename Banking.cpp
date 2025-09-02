#include <iostream>
using namespace std;

class BankAccount
{
private:
    int accNum;
    string holder;
    double bal;

public:
    BankAccount(int accNum, string holder, double bal)
    {
        this->accNum = accNum;
        this->holder = holder;
        this->bal = bal;
    }

    virtual void deposit(double amt)
    {
        cout << "Amount " << amt << " successfully deposited" << endl;
        bal += amt;
    }

    virtual void withdraw(double amt)
    {
        if (bal >= amt)
        {
            cout << "Withdrawal successful" << endl;
            bal -= amt;
        }
        else
        {
            cout << "Insufficient Balance" << endl;
        }
    }

    double getBalance()
    {
        return bal;
    }

    virtual void displayInfo()
    {
        cout << "------------ Account Details ------------" << endl;
        cout << "Account Number: " << this->accNum << endl;
        cout << "Account Holder Name: " << this->holder << endl;
        cout << "Account Balance: " << this->bal << endl;
    }

    int getAccNum()
    {
        return accNum;
    }

    virtual float calcInterest() = 0;
};

class SavingsAccount : public BankAccount
{
private:
    float rate;

public:
    SavingsAccount(int accNum, string holder, double bal, float rate)
        : BankAccount(accNum, holder, bal)
    {
        this->rate = rate;
    }

    float calcInterest() override
    {
        return (getBalance() * rate) / 100.0;
    }

    void displayInfo()
    {
        BankAccount::displayInfo();
        cout << "Interest Rate: " << this->rate << "%" << endl;
        cout << "Interest Earned: " << calcInterest() << endl;
    }
};

class CheckingAccount : public BankAccount
{
private:
    double overdraft;

public:
    CheckingAccount(int accNum, string holder, double bal, double overdraft)
        : BankAccount(accNum, holder, bal)
    {
        this->overdraft = overdraft;
    }

    void checkOverdraft(double amt)
    {
        cout << "Amount you want to withdraw: " << amt << endl;
        if (getBalance() - amt >= -overdraft)
        {
            cout << "Withdrawal Allowed" << endl;
            BankAccount::withdraw(amt);
        }
        else
        {
            cout << "Withdrawal Not Allowed (exceeds overdraft limit)" << endl;
        }
    }

    void deposit(double amt)
    {
        BankAccount::deposit(amt);
    }

    void withdraw(double amt)
    {
        if (getBalance() + overdraft >= amt)
        {
            cout << "Withdrawal successful" << endl;
            BankAccount::withdraw(amt);
        }
        else
        {
            cout << "It exceeds the overdraft limit" << endl;
        }
    }

    float calcInterest()
    {
        return 0.0;
    }

    void displayInfo()
    {
        BankAccount::displayInfo();
        cout << "Overdraft Limit: " << this->overdraft << endl;
    }
};

class FixedDepositAccount : public BankAccount
{
private:
    int term;
    float rate;

public:
    FixedDepositAccount(int accNum, string holder, double bal, int term, double rate)
        : BankAccount(accNum, holder, bal)
    {
        this->term = term;
        this->rate = rate;
    }

    void deposit(double amt)
    {
        cout << "You cannot deposit in a Fixed Deposit account" << endl;
    }

    void withdraw(double amt)
    {
        cout << "You cannot withdraw from a Fixed Deposit account" << endl;
    }

    float calcInterest() override
    {
        return (getBalance() * rate * term) / 100;
    }

    void displayInfo()
    {
        BankAccount::displayInfo();
        cout << "Term (years): " << this->term << endl;
        cout << "Interest Rate: " << this->rate << "%" << endl;
        cout << "Interest Earned: " << calcInterest() << endl;
    }
};

class BankingRegistry
{
private:
    BankAccount *acc[100];
    int count = 0;

public:
    void addAccount(BankAccount *a)
    {
        acc[count++] = a;
        cout << "Account added successfully!" << endl << endl;
    }

    void searchAccount(int accNum)
    {
        bool found = false;
        for (int i = 0; i < count; i++)
        {
            if (acc[i]->getAccNum() == accNum)
            {
                cout << endl << "---------- Account Found ----------" << endl;
                acc[i]->displayInfo();
                cout << endl;
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "Account Not Found" << endl << endl;
        }
    }

    void displayAccounts()
    {
        cout << endl << "------------- Accounts -------------" << endl;
        for (int j = 0; j < count; j++)
        {
            cout << "Account #" << (j + 1) << endl;
            acc[j]->displayInfo();
            cout << endl;
        }
    }

    void withdrawFrom(int accNum, double amt)
    {
        bool found = false;
        for (int k = 0; k < count; k++)
        {
            if (acc[k]->getAccNum() == accNum)
            {
                cout << endl << "---------- Withdrawal ----------" << endl;
                acc[k]->withdraw(amt);
                cout << endl;
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "Account Not Found" << endl << endl;
        }
    }

    void depositTo(int accNum, double amt)
    {
        bool found = false;
        for (int k = 0; k < count; k++)
        {
            if (acc[k]->getAccNum() == accNum)
            {
                cout << endl << "---------- Deposit ----------" << endl;
                acc[k]->deposit(amt);
                cout << endl;
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "Account Not Found" << endl << endl;
        }
    }
};

void inputDetails(int &accNum, string &holder, double &bal, int i)
{
    cout << "Enter Account " << i << " Details" << endl;
    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Enter Account Holder Name: ";
    cin.ignore();
    getline(cin, holder);
    cout << "Enter Account Balance: ";
    cin >> bal;
}

int main()
{
    BankingRegistry registry;
    int option, count, i, accNum, term;
    float rate;
    string holder;
    double bal, overdraft, amt;

    do
    {
        cout << "---------- Banking System Menu ----------" << endl;
        cout << "1. Add Savings Account" << endl;
        cout << "2. Add Checking Account" << endl;
        cout << "3. Add Fixed Deposit Account" << endl;
        cout << "4. Deposit" << endl;
        cout << "5. Withdraw" << endl;
        cout << "6. Search Account by Number" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> option;
        cout << endl;

        switch (option)
        {
        case 1:
            cout << "How many Savings Accounts do you want to open (max = 100): ";
            cin >> count;
            if (count <= 100)
            {
                for (i = 0; i < count; i++)
                {
                    inputDetails(accNum, holder, bal, i + 1);
                    cout << "Enter Interest Rate: ";
                    cin >> rate;
                    registry.addAccount(new SavingsAccount(accNum, holder, bal, rate));
                }
            }
            else
            {
                cout << "Size should not exceed 100" << endl << endl;
            }
            break;

        case 2:
            cout << "How many Checking Accounts do you want to open (max = 100): ";
            cin >> count;
            if (count <= 100)
            {
                for (i = 0; i < count; i++)
                {
                    inputDetails(accNum, holder, bal, i + 1);
                    cout << "Enter Overdraft Limit: ";
                    cin >> overdraft;
                    registry.addAccount(new CheckingAccount(accNum, holder, bal, overdraft));
                }
            }
            else
            {
                cout << "Size should not exceed 100" << endl << endl;
            }
            break;

        case 3:
            cout << "How many Fixed Deposit Accounts do you want to open (max = 100): ";
            cin >> count;
            if (count <= 100)
            {
                for (i = 0; i < count; i++)
                {
                    inputDetails(accNum, holder, bal, i + 1);
                    cout << "Enter Term (years): ";
                    cin >> term;
                    cout << "Enter Interest Rate: ";
                    cin >> rate;
                    registry.addAccount(new FixedDepositAccount(accNum, holder, bal, term, rate));
                }
            }
            else
            {
                cout << "Size should not exceed 100" << endl << endl;
            }
            break;

        case 4:
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter amount you want to deposit: ";
            cin >> amt;
            registry.depositTo(accNum, amt);
            break;

        case 5:
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter amount you want to withdraw: ";
            cin >> amt;
            registry.withdrawFrom(accNum, amt);
            break;

        case 6:
            cout << "Enter Account Number to search: ";
            cin >> accNum;
            registry.searchAccount(accNum);
            break;

        case 0:
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Enter valid input" << endl << endl;
        }

    } while (option != 0);

    return 0;
}