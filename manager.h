#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// #include "provider.h"


using namespace std;

void print_summary_report(vector<Provider*> provider_list) {
    cout << "Summary Report:\n";

    int consults = 0;

    int price = 0;

    for (auto provider : provider_list) {

        cout << provider->name << ": " << endl;

        consults = consults + provider->get_consults_specific();

        price = price + provider->get_fees_specific();
    }

    cout << endl << endl << "Total consult number: " << consults << endl;
    cout << "Total to be paid: " << price << "$" << endl;
    
}

void print_member_report(vector<Member*> member_list) {
    cout << "Member Report:\n";

    for (auto member : member_list) {
        member->print_member();
        cout << endl << endl;
    }

}

void print_specific_provider_report(vector<Provider*> provider_list) {
    
    cout << "For which provider? ";
    string pName;
    cin >> pName;
    Provider* providerIT = nullptr;

    for (auto provider : provider_list) {
        if (provider->name == pName) {
            providerIT = provider;
        }
    }

    if (providerIT == nullptr) {
        cout << "Invalid Provider!" << endl;
    }
    else {
        providerIT->print_provider();
    }
    
}

void print_provider_report(vector<Provider*> provider_list) {

    for (auto provider : provider_list) {
        provider->print_provider();
    }
    
}

void manager_menu(vector<Member*> member_list, vector<Provider*> provider_list) {
    int input_option;
    cout << "\n\nManager Menu:\n";
    cout << "\tGet Summary Report (1)\n";
    cout << "\tGet Member Report (2)\n";
    cout << "\tGet Provider Report (3)\n";
    cout << "\t> ";
    cin >> input_option;
    string extra;
    getline(cin, extra);
    switch (input_option) {
        case 1:
            print_summary_report(provider_list);
            break;
        case 2:
            print_member_report(member_list);
            break;
        case 3:
            print_provider_report(provider_list);
            break;
        default:
            cout << "Invalid input. Enter a number 1-3.\n";
            break;
    }
};


class Manager {
    
    
    public:

    string manager_number;

    string manager_name;
    
    void set_password(string pass) {
        password = pass;
    }

    string getPassword() {
        return password;
    }

    private:

    string password;

};



vector<Manager*> read_managers_from_file() {

    vector<Manager*> managerList;

    ifstream infile;
    infile.open("./userdata/managers.dat");


    if (!infile.is_open()) {
        cout << "file error!" << endl;
    }


    string input;
    

    while (getline(infile, input)) {

        stringstream s(input);

        Manager* temp = new Manager;

        getline(s, temp->manager_name, ',');

        //cout << temp->manager_name;

        getline(s, temp->manager_number, ',');

        //cout << temp->manager_number;

        string buffer;

        getline(s, buffer);

        buffer.erase(buffer.find_last_not_of(" \n\r\t") + 1);

        temp->set_password(buffer);

        //cout << temp->getPassword() << "b";

        managerList.push_back(temp);

    }

    infile.close();

    return managerList;
}


void write_manager_to_file(vector<Manager*> manager_list) {


    ofstream outfile;
    outfile.open("./userdata/managers.dat");


    if (!outfile.is_open()) {
        cout << "file error! Could not save managers!" << endl;
    }


    for (int i = 0; i < manager_list.size(); i++) {

        Manager* temp = manager_list.at(i);

        outfile << temp->manager_name << ','  << temp->manager_number << ',' << temp->getPassword() << endl;

    }

    outfile.close();

}