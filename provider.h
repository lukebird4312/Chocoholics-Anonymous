#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;



class Provider {
    public:

    string provider_number;
    string name;
    string address;
    string city;
    string state;
    string zip;
    
    
    vector<string> service_date;
    vector<string> service_time;
    vector<string> member_served;
    vector<string> member_ID;
    vector<string> service_code;
    vector<string> fee;
    vector<string> comments;


    int consultation_count;
    int total_sales;


    int get_consults() {

        int consult = 0;

        for (int i = 0; i < service_date.size(); i++) {
            consult++;
        }

        //cout << consult << " consultations, ";

        return consult;
    }

    int get_consults_specific() {

        int consult = 0;

        for (int i = 0; i < service_date.size(); i++) {
            consult++;
        }

        cout << consult << " consultations, ";

        return consult;
    }

    int get_fees() {

        int price = 0;

        for (int i = 0; i < fee.size(); i++) {
            //cout << fee.at(i);
            price = price + stoi(fee.at(i));
        }

        //cout << price << "$" << endl << endl;

        return price;
    }

    int get_fees_specific() {

        int price = 0;

        for (int i = 0; i < fee.size(); i++) {
            //cout << fee.at(i);
            price = price + stoi(fee.at(i));
        }

        cout << price << "$" << endl << endl;

        return price;
    }

    Provider(){consultation_count = 0; total_sales = 0;}

    void print_provider() {

        cout << provider_number << endl;
        cout << name << endl;
        cout << address << ", " << city << ", " << state << ", " << zip << endl;

        for (int i = 0; i < service_date.size(); i++) {

            cout << endl;
            cout << service_date.at(i) << endl;
            cout << service_time.at(i) << endl;
            cout << member_served.at(i) << endl;
            cout << member_ID.at(i) << endl;
            cout << service_code.at(i) << endl;
            cout << fee.at(i) << "$" << endl;
            cout << comments.at(i) << endl << endl;
        }


        cout << get_consults() << " consultations" << endl;
        cout << get_fees() << "$" << endl;

    }

    void set_password(string pass) {
        password = pass;
    }

    string getPassword() {
        return password;
    }

    private:

    string password;

};

vector<Provider*> read_providers_from_file() {

    vector<Provider*> providerList;

    ifstream infile;
    infile.open("./userdata/providers.dat");


    if (!infile.is_open()) {
        cout << "file error!" << endl;
    }


    string input;
    

    while (getline(infile, input)) {

        stringstream s(input);

        Provider* temp = new Provider;

        getline(s, temp->name, ',');

        getline(s, temp->provider_number, ',');

        getline(s, temp->address, ',');

        getline(s, temp->city, ',');

        getline(s, temp->state, ',');

        getline(s, temp->zip, ',');

        string buffer;

        getline(s, buffer, ',');

        //cout << "p1\n";

        temp->consultation_count = stoi(buffer);

        //cout << "p2\n";
        getline(s, buffer, ',');

        temp->total_sales = stoi(buffer);

        //cout << "p3\n";

        providerList.push_back(temp);

        getline(s, buffer, ',');

        buffer.erase(buffer.find_last_not_of(" \n\r\t") + 1);

        temp->set_password(buffer);


        while(getline(s, buffer, ',')) {

            temp->service_date.push_back(buffer);

            getline(s, buffer, ',');
            temp->service_time.push_back(buffer);

            getline(s, buffer, ',');
            temp->member_served.push_back(buffer);

            getline(s, buffer, ',');
            temp->member_ID.push_back(buffer);

            getline(s, buffer, ',');
            temp->service_code.push_back(buffer);

            getline(s, buffer, ',');
            temp->fee.push_back(buffer);

            getline(s, buffer, ',');
            temp->comments.push_back(buffer);
        }
    }

    infile.close();

    return providerList;
}


void write_providers_to_file(vector<Provider*> provider_list) {


    ofstream outfile;
    outfile.open("./userdata/providers.dat");


    if (!outfile.is_open()) {
        cout << "file error! Could not save providers!" << endl;
    }
    

    for (int i = 0; i < provider_list.size(); i++) {

        Provider* temp = provider_list.at(i);

        outfile << temp->name << ','  << temp->provider_number << ',' << temp->address << ','  << temp->city << ','  << temp->state << ','  << temp->zip << ','  << temp->consultation_count << ','  << temp->total_sales << ','  << temp->getPassword();

        for (int k = 0; k < temp->service_code.size(); k++) {
            outfile << "," << temp->service_date.at(k) << ',' << temp->service_time.at(k) << ',' << temp->member_served.at(k) << ',' << temp->member_ID.at(k) << ',' << temp->service_code.at(k) << ',' << temp->fee.at(k) << ',' << temp->comments.at(k);
        }

        outfile << endl;
    }


    outfile.close();
}

Provider* search_provider_by_id(vector<Provider*> pList, string ID) {
    Provider* answer;

    for (int i = 0; i < pList.size(); i++) {
        
        if (pList.at(i)->provider_number == ID) {
            return pList.at(i);
        }
    }

    cout << "Provider not found!" << endl;
    return nullptr;
}

void print_provider_directory() {
    string input_buffer;
    ifstream fin("./userdata/provider_directory.dat");
    if (!fin.is_open()) {
        cout << "file error! Could not open provider directory!" << endl;
    } else {
        cout << endl;
        while (getline(fin,input_buffer)) cout << input_buffer << endl;
    }
    cout << endl;
    fin.close();    
}
string search_provider_directory(string service_code) {
    string input_buffer;
    ifstream fin("./userdata/provider_directory.dat");
    if (!fin.is_open()) {
        cout << "file error! Could not open provider directory!" << endl;
    } else {
        while (getline(fin,input_buffer, '-')) {
            if (service_code == input_buffer) {
                getline(fin,input_buffer);
                fin.close();
                return input_buffer;
                break;
            }
            getline(fin,input_buffer);
        };
    }
    fin.close();  
    // if it reaches this return, no match was found
    return "service not found";
}


void provider_menu(vector<Member*> &member_list, vector<Provider*> &provider_list, int active_id) {
    string input_buffer;
    int member_number = 0;
    string member_name = "";
    cout << "\n\nProvider Menu:\n";
    bool member_found = false;
    Member* curr_member;
    while (!member_found) {
        cout <<"\tEnter member number: ";
        cin >> member_number;
        for (auto member : member_list) {
            if (stoi(member->member_id) == member_number) {
                curr_member = member;
                cout << "\tValidated.\n\n";
                member_name = member->name;
                member_found = true;
            }
        }
        if (!member_found) cout << "\tInvalid number.\n";
    }
    
    member_found = false;
    cout << "\tRe-enter member number when service is completed: ";
    cin >> member_number;
    for (auto member : member_list) {
        if (stoi(member->member_id) == member_number) {
            cout << "\tValidated.\n\n";
            member_found = true;
        }
    }
    if (!member_found) cout << "\tInvalid number.\n";
    cout << "\tEnter date that service was provided (MM-DD-YYYY): ";
    getline(cin,input_buffer);
    getline(cin,input_buffer);
    Provider* current_provider = search_provider_by_id(provider_list, to_string(active_id));

    curr_member->serviceDates.push_back(input_buffer);
    current_provider->service_date.push_back(input_buffer);

    curr_member->serviceProviders.push_back(current_provider->name);

    cout << "\tView Provider Directory? (y/n): ";
    cin >> input_buffer;
    if (input_buffer == "y") {print_provider_directory();};
    
    input_buffer = "";
    while (input_buffer != "y" && input_buffer != "quit") {
        cout << "\tEnter service code or 'quit': ";
        cin >> input_buffer;
        string serv_code = input_buffer;
        string search_result = search_provider_directory(input_buffer);

        cout << "\tService found: " << search_result << endl;
        cout << "\tIs this the correct service? (y or n): ";
        cin >> input_buffer;
        if (input_buffer == "y") {
            curr_member->serviceRecieved.push_back(search_result);

            time_t timestamp = time(NULL);
            struct tm datetime = *localtime(&timestamp);
            string sec, min, hr;
            if (datetime.tm_hour < 10) {
                hr = "0" + to_string(datetime.tm_hour);
            } else {
                hr = to_string(datetime.tm_hour);
            }
            if (datetime.tm_min < 10) {
                min = "0" + to_string(datetime.tm_min);
            } else {
                min = to_string(datetime.tm_min);
            }
            if (datetime.tm_sec < 10) {
                sec = "0" + to_string(datetime.tm_sec);
            } else {
                sec = to_string(datetime.tm_sec);
            }
            string fee;
            cout << "\tEnter fee for service: ";
            cin >> fee;
            current_provider->fee.push_back(fee);
            current_provider->service_time.push_back(hr + ":" + min + ":" + sec);
            current_provider->service_code.push_back(serv_code);
            current_provider->member_served.push_back(member_name);
            current_provider->member_ID.push_back(to_string(member_number));


            cout << "\tEnter comments or press 'Enter' to continue: ";
            getline(cin, input_buffer);
            getline(cin, input_buffer);
            if (input_buffer == "") {
                input_buffer = "N/A";
            }
            current_provider->comments.push_back(input_buffer);

            input_buffer = "quit";
        }
    }

    

};




