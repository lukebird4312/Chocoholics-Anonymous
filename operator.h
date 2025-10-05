#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void operator_menu(vector<Member*> &member_list, vector<Provider*> &provider_list) {
    int input_option;
    string input_buffer;
    cout << "\n\nOperator Menu:\n";
    cout << "\tMember Management:\n";
    cout << "\tAdd Member (1)\n";
    cout << "\tEdit Member (2)\n";
    cout << "\tDelete Member (3)\n";
    cout << "\n\tProvider Management\n";
    cout << "\tAdd Provider (4)\n";
    cout << "\tEdit Provider (5)\n";
    cout << "\tDelete Provider (6)\n";
    cout << "\t> ";
    cin >> input_option;

    
    switch (input_option) {
        case 1: {     // add member
            Member* new_member = new Member;
            int new_member_id = 0;
            cout << "\n\tEnter new member name: ";
            getline(cin, input_buffer);
            getline(cin, input_buffer);
            new_member->name = input_buffer;

            new_member_id = stoi(member_list.back()->member_id) + 1;
            new_member->member_id = "0" + to_string(new_member_id);

            cout << "\tEnter member address: ";
            getline(cin, input_buffer);
            new_member->address = input_buffer;

            cout << "\tEnter member city: ";
            getline(cin, input_buffer);
            new_member->city = input_buffer;

            cout << "\tEnter member state: ";
            getline(cin, input_buffer);
            new_member->state = input_buffer;

            cout << "\tEnter member zip code: ";
            getline(cin, input_buffer);
            new_member->zip = input_buffer;

            member_list.push_back(new_member);

            break;
        } case 2: { // edit member  
            Member* current_member;
            
            cout << "\n\tEnter member name that you would like to edit: ";
            getline(cin, input_buffer);
            getline(cin, input_buffer);
            bool found_member = false;
            for (auto member : member_list) {
                if (member->name == input_buffer) {
                    current_member = member;
                    found_member = true;
                }
            }
            if (!found_member) cout << "Couldn't find member '" << input_buffer << "'\n";

            cout << "\n\tOld member info:\n\n";
            current_member->print_member();

            cout << "Please enter the updated information" << "\n\n";

            cout << "\nEnter new member name: ";
            getline(cin, input_buffer);
            current_member->name = input_buffer;

            cout << "\tEnter member address: ";
            getline(cin, input_buffer);
            current_member->address = input_buffer;

            cout << "\tEnter member city: ";
            getline(cin, input_buffer);
            current_member->city = input_buffer;

            cout << "\tEnter member state: ";
            getline(cin, input_buffer);
            current_member->state = input_buffer;

            cout << "\tEnter member zip code: ";
            getline(cin, input_buffer);
            current_member->zip = input_buffer;

            
            break;
        } case 3: {    // delete member
            cout << "\n\tEnter member name for removal: ";
            getline(cin, input_buffer);
            getline(cin, input_buffer);
            bool found_member = false;
            for (int i = 0; i < member_list.size(); i++) {
                if (member_list.at(i)->name == input_buffer) {
                    member_list.erase(member_list.begin() + i);
                    found_member = true;
                } 
            }
            if (!found_member) {
                cout << "Couldn't find member '" << input_buffer << "'\n";
            }

            break;
        } case 4: {    // add provider
            Provider* new_provider = new Provider;
            int new_provider_id = 0;
            cout << "\n\tEnter new provider name: ";
            getline(cin, input_buffer);
            getline(cin, input_buffer);
            new_provider->name = input_buffer;

            new_provider_id = stoi(provider_list.back()->provider_number) + 1;
            new_provider->provider_number = to_string(new_provider_id);

            cout << "\tEnter provider address: ";
            getline(cin, input_buffer);
            new_provider->address = input_buffer;

            cout << "\tEnter provider city: ";
            getline(cin, input_buffer);
            new_provider->city = input_buffer;

            cout << "\tEnter provider state: ";
            getline(cin, input_buffer);
            new_provider->state = input_buffer;

            cout << "\tEnter provider zip code: ";
            getline(cin, input_buffer);
            new_provider->zip = input_buffer;

            new_provider->consultation_count = 0;
            new_provider->total_sales = 0;

            cout << "\tChoose a password: ";
            getline(cin, input_buffer);
            new_provider->set_password(input_buffer);

            provider_list.push_back(new_provider);

            break;
        } case 5: { // edit provider  
            Provider* current_provider = nullptr;;
            
            cout << "\n\tEnter provider name that you would like to edit: ";
            getline(cin, input_buffer);
            getline(cin, input_buffer);

            cout << input_buffer;
            for (auto provider : provider_list) {
                if (provider->name == input_buffer) {
                    current_provider = provider;
                    break;
                } 
            }

            if(current_provider == nullptr) {
                cout << "Couldn't find provider '" << input_buffer << "'\n";
                return;
            }

            cout << "Old provider info:" << endl;
            current_provider->print_provider();

            cout << "Please enter the updated informaton" << "\n\n";

            cout << "\nEnter new provider name: ";
            getline(cin, input_buffer);
            current_provider->name = input_buffer;

            cout << "\tEnter provider address: ";
            getline(cin, input_buffer);
            current_provider->address = input_buffer;

            cout << "\tEnter provider city: ";
            getline(cin, input_buffer);
            current_provider->city = input_buffer;

            cout << "\tEnter provider state: ";
            getline(cin, input_buffer);
            current_provider->state = input_buffer;

            cout << "\tEnter provider zip code: ";
            getline(cin, input_buffer);
            current_provider->zip = input_buffer;

            cout << "\tEnter provider consultation count: ";
            getline(cin, input_buffer);
            current_provider->zip = stoi(input_buffer);

            cout << "\tEnter provider net sales: ";
            getline(cin, input_buffer);
            current_provider->zip = stoi(input_buffer);

            
            break;
        } case 6: {    // delete provider
            cout << "\n\tEnter provider name for removal: ";
            getline(cin, input_buffer);
            getline(cin, input_buffer);
            bool found_provider = false;
            for (int i = 0; i < provider_list.size(); i++) {
                if (provider_list.at(i)->name == input_buffer) {
                    provider_list.erase(provider_list.begin() + i);
                    found_provider = true;
                }
            }
            if (!found_provider) cout << "Couldn't find provider '" << input_buffer << "'\n";
            break;
        } default:
            cout << "Invalid input. Enter a number 1-3.\n";
            break;
    }
};


class Operator {
    
    
    public:
    string operator_number;
    string operator_name;

    void set_password(string pass) {
        password = pass;
    }

    string getPassword() {
        return password;
    }

    private:

    string password;

};




vector<Operator*> read_operators_from_file() {

    vector<Operator*> operatorList;

    ifstream infile;
    infile.open("./userdata/operators.dat");


    if (!infile.is_open()) {
        cout << "file error!" << endl;
    }


    string input;
    

    while (getline(infile, input)) {

        stringstream s(input);

        Operator* temp = new Operator;

        getline(s, temp->operator_name, ',');

        getline(s, temp->operator_number, ',');

        string buffer;

        getline(s, buffer);

        buffer.erase(buffer.find_last_not_of(" \n\r\t") + 1);

        temp->set_password(buffer);

        operatorList.push_back(temp);

    }

    infile.close();

    return operatorList;
}

void write_operators_to_file(vector<Operator*> operator_list) {


    ofstream outfile;
    outfile.open("./userdata/operators.dat");


    if (!outfile.is_open()) {
        cout << "file error! Could not save operators!" << endl;
    }


    for (int i = 0; i < operator_list.size(); i++) {

        Operator* temp = operator_list.at(i);

        outfile << temp->operator_name << ','  << temp->operator_number << ',' << temp->getPassword() << endl;

    }

    outfile.close();

}