#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

class Bank_account {
    int acno;
    char name[50];
    int deposit;
    char type;
public:
    void create_account();
    void show_account() const;
    void modify();
    void dep(int);
    void draw(int);
    void report() const;
    int retacno() const;
    int retdeposit() const;
    char rettype() const;
};

void Bank_account::create_account() {
    system("CLS");
    cout << "\n\t\t\tEnter the account No. : ";
    cin >> acno;
    cout << "\n\t\t\tEnter the Name of the Account holder : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\n\t\t\tEnter Type of the account (C/S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\n\n\t\t\tAccount Created..";
}

void Bank_account::show_account() const {
    cout << "\n\t\t\tAccount No. : " << acno;
    cout << "\n\t\t\tAccount Holder Name : " << name;
    cout << "\n\t\t\tType of Account : " << type;
    cout << "\n\t\t\tBalance amount : " << deposit;
}

void Bank_account::modify() {
    cout << "\n\t\t\tModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\n\t\t\tModify Type of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\n\t\t\tModify Balance amount : ";
    cin >> deposit;
}

void Bank_account::dep(int x) {
    deposit += x;
}

void Bank_account::draw(int x) {
    deposit -= x;
}

void Bank_account::report() const {
    cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int Bank_account::retacno() const {
    return acno;
}

int Bank_account::retdeposit() const {
    return deposit;
}

char Bank_account::rettype() const {
    return type;
}

void write_account() {
    Bank_account ac;
    ofstream outfile("account.dat", ios::binary | ios::app);
    ac.create_account();
    outfile.write(reinterpret_cast<char *>(&ac), sizeof(Bank_account));
    outfile.close();
}

void display_sp(int n) {
    Bank_account ac;
    bool flag = false;
    ifstream infile("account.dat", ios::binary);
    if (!infile) {
        cout << "File could not be opened!";
        return;
    }
    while (infile.read(reinterpret_cast<char *>(&ac), sizeof(Bank_account))) {
        if (ac.retacno() == n) {
            ac.show_account();
            flag = true;
        }
    }
    infile.close();
    if (!flag)
        cout << "\n\n\t\t\tAccount number does not exist";
}

void deposit_withdraw(int n, int option) {
    int amt;
    bool found = false;
    Bank_account ac;
    fstream File("account.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "File could not be opened!";
        return;
    }
    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char *>(&ac), sizeof(Bank_account));
        if (ac.retacno() == n) {
            ac.show_account();
            if (option == 1) {
                cout << "\n\t\t\tEnter Amount to Deposit: ";
                cin >> amt;
                ac.dep(amt);
            } else {
                cout << "\n\t\t\tEnter Amount to Withdraw: ";
                cin >> amt;
                if (ac.retdeposit() < amt)
                    cout << "Insufficient balance";
                else
                    ac.draw(amt);
            }
            File.seekp(-static_cast<int>(sizeof(Bank_account)), ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(Bank_account));
            found = true;
        }
    }
    File.close();
    if (!found)
        cout << "\n\n\t\t\tRecord Not Found ";
}

int main() {
    char ch;
    int num;
    do {
        system("CLS");
        cout << "\n\n\t\t\tBANK MANAGEMENT SYSTEM";
        cout << "\n\n\t\t\t1. NEW ACCOUNT";
        cout << "\n\t\t\t2. DEPOSIT AMOUNT";
        cout << "\n\t\t\t3. WITHDRAW AMOUNT";
        cout << "\n\t\t\t4. BALANCE ENQUIRY";
        cout << "\n\t\t\t5. EXIT";
        cout << "\n\t\t\tSelect option (1-5): ";
        cin >> ch;
        switch (ch) {
            case '1': write_account(); break;
            case '2': cout << "Enter Account No.: "; cin >> num; deposit_withdraw(num, 1); break;
            case '3': cout << "Enter Account No.: "; cin >> num; deposit_withdraw(num, 2); break;
            case '4': cout << "Enter Account No.: "; cin >> num; display_sp(num); break;
            case '5': exit(0);
            default: cout << "Invalid Option!";
        }
        cin.ignore();
        cin.get();
    } while (ch != '5');
    return 0;
}

