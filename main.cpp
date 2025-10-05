#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>

#include "member.h"
#include "provider.h"
#include "manager.h"
#include "operator.h"
// #include "service.h"

using namespace std;


int validate_user(string ID_number, vector<Member*> &L0, vector<Provider*> &L1, vector<Manager*> L2, vector<Operator*> &L3) {
    int ID = 0;    
    try {
        ID = stoi(ID_number);
    } catch (const exception& e) {
        if (ID_number != "quit") cout << "Invalid ID number: " << ID_number << endl;
        return 0;
    }

    int access_level = ID;

    string input_password;
    switch (access_level / 100000000) {
    case 1:
        for (auto provider : L1) {
            if (provider->provider_number == ID_number) {
                cout << "\tEnter User Password: ";
                cin >> input_password;
                if (input_password == provider->getPassword()) {
                    provider_menu(L0, L1, access_level);
                } else {
                    cout << "Invalid password.\n";
                    return 0;
                }
            }
        }
        return 0;
        break;
    case 2:
        for (auto manager : L2) {
            if (manager->manager_number == ID_number) {
                cout << "\tEnter User Password: ";
                
                getline(cin, input_password);

                //cout << endl << "input: " << input_password << endl;

                string mPass = manager->getPassword();
         
                if (input_password.compare(mPass) == 0) {

                    manager_menu(L0, L1);

                } else {


                    cout << "Invalid password.\n";
                    return 0;
                }
            }
        }
        break;
    case 3:
        for (auto op : L3) {
            if (op->operator_number == ID_number) {
                cout << "\tEnter User Password: ";
                cin >> input_password;
                if (input_password == op->getPassword()) {
                    operator_menu(L0, L1);
                } else {
                    cout << "Invalid password.\n";
                    return 0;
                }
            }
        }
        break;
    default:
        cout << "Invalid ID number: " << ID_number << endl;
    
        return 0;
        break;
    }
    return 0;
}





int main(int argc, char **argv) {
    vector<Member*> member_list = read_members_from_file();
    
    vector<Provider*> provider_list = read_providers_from_file();

    vector<Manager*> manager_list = read_managers_from_file();

    vector<Operator*> operator_list = read_operators_from_file();


    Provider provider;
    string input_buffer = "";
    int access_level = 0;

    while (input_buffer != "quit") {
        
        cout << "\nMain Menu:\n";
        cout << "\tEnter User Number, \"Main Accounting Procedure\", or 'quit': ";
        getline(cin, input_buffer);

        //cout << input_buffer;

        if (input_buffer == "Main Accounting Procedure") {

            cout << endl << endl;

            print_summary_report(provider_list);

            cout << endl << endl;

            print_member_report(member_list);

            cout << endl << endl;

            print_provider_report(provider_list);

            continue;
        }

        access_level = validate_user(input_buffer, member_list, provider_list, manager_list, operator_list);

    }     
    
    write_providers_to_file(provider_list);
    write_members_to_file(member_list);
    write_operators_to_file(operator_list);
    write_manager_to_file(manager_list);

    return 0;
}