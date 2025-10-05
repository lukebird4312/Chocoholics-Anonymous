#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Member {
    public:
    string member_id;
    string name;
    string address;
    string city;
    string state;
    string zip;

    vector<string> serviceDates;
    vector<string> serviceProviders;
    vector<string> serviceRecieved;

    Member() {}

    void print_member() {
        cout << member_id << endl;
        cout << name << endl;
        cout << address << ", " << city << ", " << state << ", " << zip << endl;

        cout << "Services:" << endl;

        for (int i = 0; i < serviceDates.size(); i++) {

            cout << endl;
            cout << serviceDates.at(i) << endl;
            cout << "Provider: " << serviceProviders.at(i) << endl;
            cout << "Service: " << serviceRecieved.at(i) << endl;

        }

        cout << endl;
    }
};

vector<Member*> read_members_from_file() {
    vector<Member*> memberList;

    ifstream infile;
    infile.open("./userdata/members.dat");

    if (!infile.is_open()) {
        cout << "file error!" << endl;
    }

    string input;

    while (getline(infile, input)) {
        input.erase(input.find_last_not_of(" \n\r\t") + 1);

        stringstream s(input);
        
        Member* temp = new Member;

        getline(s, temp->name, ',');
        getline(s, temp->member_id, ',');
        getline(s, temp->address, ',');
        getline(s, temp->city, ',');
        getline(s, temp->state, ',');
        getline(s, temp->zip, ',');


        string buffer;

        int rotator = 1;

        while (getline(s, buffer, ',')) {

            if (rotator == 1) {
                temp->serviceDates.push_back(buffer);
                rotator++;
            } else if (rotator == 2) {
                temp->serviceProviders.push_back(buffer);
                rotator++;
            } else if (rotator == 3) {
                temp->serviceRecieved.push_back(buffer);
                rotator = 1;
            } else {
                cout << "Warning: Memebers could not be read properly, some entired may be desynced" << endl;
            }

        }

        memberList.push_back(temp);
    }

    infile.close();

    return memberList;
}


void write_members_to_file(vector<Member*> member_list) {


    ofstream outfile;
    outfile.open("./userdata/members.dat");


    if (!outfile.is_open()) {
        cout << "file error! Could not save providers!" << endl;
    }

    //cout << member_list.size();
    

    for (int i = 0; i < member_list.size(); i++) {

        Member* temp = member_list.at(i);

        outfile << temp->name << ','  << temp->member_id << ',' << temp->address << ','  << temp->city << ','  << temp->state << ','  << temp->zip;

        for (int k = 0; k < member_list.at(i)->serviceDates.size(); k++){

            outfile << ',' << member_list.at(i)->serviceDates.at(k) << ',' << member_list.at(i)->serviceProviders.at(k) << ',' << member_list.at(i)->serviceRecieved.at(k);
            
        }

        outfile << endl;

    }

    outfile.close();
}
