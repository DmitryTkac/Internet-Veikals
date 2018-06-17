#include "../../headers/Profiles_System/profiles_base.h"
#include "../../headers/Veikals_System/Products.h"
#include "../../headers/funckijas.h"

#include <iostream>
#include <windows.h>
#include <fstream>
#include <direct.h>

using namespace std;


    Profile_Base::Profile_Base() {

        mkdir("Profiles");
        mkdir("Profiles/Profiles_Info");
        mkdir("Veikals/Pasutijumi");

        ifstream file ("Profiles/Profiles_Data.txt");
        ofstream izveidot;

        if (!file) {
            izveidot.open("Profiles/Profiles_Data.txt");
            izveidot.close();
        }

        file.close();

        file.open("Profiles/Profila_Preces.txt");

        if (!file) {
            izveidot.open("Profiles/Profila_Preces.txt");
            izveidot.close();
        }

        file.close();


    }

    void Profile_Base::registration() {

        fstream data ("Profiles/Profiles_Data.txt");
        fstream prof_preces("Profiles/Profila_Preces.txt", ios::app);


        string login, password, password_check;
        string Vards, Uzvards;
        string parbaude;
        string way;
        bool atkartot;
        cout << "'REGISTRACIJA'" << endl
        << "Izdomajiet login ar kuru jus varesiet viegli ieiet sava profila" << endl
        << "Tam jabus nemazak par 6 simboliem un var saturet tikai burtus, ciparus un '-' , '_' simbolus" << endl
        << "Login: ";
        fflush(stdin);
        getline(cin, login);

        int i;

        for (i = 0; i < login[i]; i++) {
            if (
                (login[i] >= 'a' && login[i] <= 'z') ||
                (login[i] >= 'A' && login[i] <= 'Z') ||
                (login[i] >= '0' && login[i] <= '9') ||
                (login[i] == '-') ||
                (login[i] == '_')
            ) {}
            else {
                i = 0;
                break;
            }   //Nosacijums uz simbolu prasibu parbaudi
        } //cikls uz simbolu skaitisanu

        string parbaudit = login;

        for (int x = 0; x < parbaudit[x]; x++) {
            if (parbaudit[x] >= 97) {
                parbaudit[x] -= ' ';
            }
        }

        while (!data.eof()) {
            data >> parbaude;

            for (int x =  0; x < parbaude[x]; x++) {
                if (parbaude[x] >= 97) {
                    parbaude[x] -= ' ';
                }
            }

            if (parbaudit == parbaude) {
                cout << "Tads logins jau ir aiznemts! Pameginiet citu!" << endl;
                i = 0;
                break;
            } else {
                data >> parbaude;
            }
        }

        data.close();

        if (i >= 6) {
            do {

                atkartot = 0;
                cout << "Izdomajiet paroli: ";
                cin >> password_check;
                cout << "Ievadiet savu izdomato paroli velreiz: ";
                cin >> password;

                if (password != password_check) {
                    cout << "Kluda: Jusu ievadita parole nesakrit ar izdomatu!" << endl
                    << "Pameginat velreiz? [1- JA | 0 - NE]: ";
                    cin >> atkartot;
                }

                if (!atkartot) {

                    if (password == password_check) {

                        cout << "Ievadiet savu Vardu: ";
                        cin >> Vards;
                        cout << "Ievadiet savu Uzvardu: ";
                        cin >> Uzvards;

                        data.open ("Profiles/Profiles_Data.txt", ios::app);

                        data << login << " " << password << endl;
                        prof_preces << login << endl;


                        way = "Profiles/Profiles_Info/" + login + ".txt";

                        ofstream data_info(way.c_str());

                        data_info << Vards << " " << Uzvards << endl;
                        data_info << 1 << endl;

                        cout << Vards << " " << Uzvards << " Jus esat veiksmigi pieregistreti!" << endl;

                        data.close();
                        prof_preces.close();
                        data_info.close();
                    }

                    break;
                }


            } while (true);
        } else {
            cout << "Jusu ievaditajs logins neatbilst prasibam!" << endl;
        }

        system("PAUSE");

    }

    bool Profile_Base::log(string login, string password) { //login sistema

        string parbaude;
        string way;
        string Vards, Uzvards;

        ifstream data ("Profiles/Profiles_Data.txt");

        while(!data.eof()) {
            data >> parbaude;

            if (login == parbaude) {

                data >> parbaude;

                if (password == parbaude) {

                    way = "Profiles/Profiles_Info/" + login + ".txt";

                    data.close();

                    get_File_Info(way);

                    this->login = login;


                    return true;

                }

            } else {
                data >> parbaude;
            }
        }

        data.close();

        cout << "Jusu ievaditais logins vai parole ir nepareiza!" << endl;
        system("PAUSE");
        return false;

    }



    string Profile_Base::showProfiles() {

        ifstream profile ("Profiles/Profiles_Data.txt");

        string profile_login;

        system("CLS");

        do {



            profile >> profile_login;

            if(profile.eof()) {
                break;
            }

            cout << "  | "  << profile_login << endl;
            profile >> profile_login;
        } while (true);

        cout
        << "0 | Iziet" << endl
        << "  | Ievadiet loginu kuru gribiet rediget: ";

        cin >> profile_login;
        if (profile_login == "0") {
            return "0";
        }
        return profile_login;

    }

    void Profile_Base::changeName(string login) {

        cout << "Ievadiet jaunu lietotaja vardu: ";
        cin >> this->vards;

        change_File_Info(login);

    }

    void Profile_Base::changeSurname(string login) {

        cout << "Ievadiet jaunu lietotaja uzvardu: ";
        cin >> this->uzvards;

        change_File_Info(login);

    }

    void Profile_Base::changePermission(string login) {

        int new_permission;

        if (this->Permission == 3) {

            cout << "Administratora lomu nedrikst mainit!" << endl;
            system("PAUSE");
            return;

        }
        cout << "Izvelaties lomu:" << endl
             << "[1] - Lietotajs" << endl
             << "[2] - Pardevejs" << endl
             << "Jusu izvele :";

        cin >> new_permission;

        if (new_permission > 2 || new_permission < 1) {
            cout << "Jusu ievadita izvele nevar but mazaka par 1 un lielaka par 2!" << endl;
            system("pause");
        } else {
            this->Permission = new_permission;
            change_File_Info(login);
        }



    }

    void Profile_Base::setGuest() {
        this->Permission = 0;
    }

    bool Profile_Base::get_File_Info(string login_way) {

        int ID;

        ifstream get (login_way.c_str());

        if (get == 0) {
            if (login_way != "0") {
                cout << "Profile ar tadu loginu nav pameginiet velreiz!" << endl;
                system("PAUSE");
            }
            get.close();
            return false;
        }

        get >> this->vards >> this->uzvards >> this->Permission;
/**
        if (this->Permission == 2) {

            while (true) {
                if (get.eof()) {
                    break;
                } else {
                    get >> ID;
                    this->pardeveja_preces.push_back(ID);
                }
            }

//            for (int i = 0; i < this->pardeveja_preces.size()-1; i++) {
//                cout << this->pardeveja_preces.at(i) << endl;
//            }

//            system("PAUSE");
        }

*/

        get.close();

    }

    void Profile_Base::get_Merchant_Produkts(string login) {

        this->pardeveja_preces.clear();

        ifstream profila_preces ("Profiles/Profila_Preces.txt");
        ofstream sanemt_ID ("backup.txt");

        string parbaude;
        int ID = NULL;

        while (true) {

            if (profila_preces.eof()) {
                break;
            }

            profila_preces >> parbaude;
            //cout << parbaude << this->login << endl;

            if (parbaude == this->login) {
                    getline(profila_preces, parbaude);
                    sanemt_ID << parbaude;

                    break;
            }

        }

        profila_preces.close();
        sanemt_ID.close();
        profila_preces.open("backup.txt");

        while (!profila_preces.eof()) {
            if (profila_preces.eof()) {
                break;
            }
                profila_preces >> ID;

            if (ID) {
                this->pardeveja_preces.push_back(ID);
            }
            //cout << ID << endl;

        }



        profila_preces.close();

    }



    int Profile_Base::showMerchantProducts() {

        //vector<string> preces_nosaukums;
        Products buffer;

        vector<Products> prece;

        if (this->pardeveja_preces.size() == 0) {
            cout << "Jums nav nekadu produktu" << endl;
            return 0;
        }


        for (int i = 0; i <= this->pardeveja_preces.size()-1; i++) {

            buffer.get_Product_Info(this->pardeveja_preces.at(i));
            prece.push_back(buffer);
        }

        for (int i = 0; i < prece.size(); i++) {
            cout << i+1 << " | " << prece.at(i).returnProdName() << endl;
        }



    }

    void Profile_Base::change_File_Info(string login_way) {

        ofstream change (login_way.c_str());

        change << this->vards << " " << this->uzvards << endl << this->Permission;

        change.close();

    }

    void Profile_Base::addProd_To_Stat() {

        int prod_count = 0;
        string skipper;
        ifstream saskaitit ("Veikals/produkti.txt");

        while(getline(saskaitit, skipper)) {
            prod_count++;
        }

        this->pardeveja_preces.push_back(prod_count);
        saskaitit.close();

        fstream file ("Profiles/Profila_Preces.txt");
        ofstream backup ("backup.txt");
        int Login_ID = 0;
        int parbauditajs = 0;



        while(true) {

            if (file.eof()) {
                break;
            }
            file >> skipper;
            Login_ID++;
            if (skipper == this->login) {
                parbauditajs = Login_ID;
            }

            backup << skipper;

            getline(file, skipper);

            backup << skipper << endl;
        }

        Login_ID = 0;

        backup.close();
        file.close();



        file.open("backup.txt");
        backup.open("Profiles/Profila_Preces.txt");



        while (getline(file, skipper)) {
            Login_ID++;

            if(parbauditajs == Login_ID) {
                backup << this->login;
                for (int i = 0; i < this->pardeveja_preces.size(); i++) {
                    backup << " " << this->pardeveja_preces.at(i);
                }
                backup << endl;
            } else {
                backup << skipper << endl;
            }

        }

        backup.close();


        file.close();

    }

    void Profile_Base::delete_profile(string login, string login_way) {



        ifstream profile ("Profiles/Profiles_Data.txt");
        ofstream ierakstit ("backup.txt");

        string line;

        while (getline(profile, line)) {
            ierakstit << line << endl;
        }

        profile.close();
        ierakstit.close();

        profile.open("backup.txt");
        ierakstit.open("Profiles/Profiles_Data.txt");

        while (!profile.eof()) {
            profile >> line;

            if (profile.eof()) {
                break;
            }

            if (line == login) {
                remove(login_way.c_str());
                profile >> line;
            } else {
                ierakstit << line;
                //cout << line << " ";
                profile >> line;
                ierakstit << " " << line << endl;
                //cout << line << endl;
            }

        }

        profile.close();
        ierakstit.close();

        profile.open("Profiles/Profila_Preces.txt");
        ierakstit.open("backup.txt");

        while (!profile.eof()) {
            if (profile.eof()) {
                break;
            }

            profile >> line;

            if (line == login) {
                getline(profile, line);
            } else {
                ierakstit << line;
                getline(profile, line);
                ierakstit << line << endl;
            }

        }

        profile.close();
        ierakstit.close();

        profile.open("backup.txt");
        ierakstit.open("Profiles/Profila_Preces.txt");

        while (getline(profile, line)) {
            ierakstit << line << endl;
        }

        profile.close();
        ierakstit.close();

        system("PAUSE");
    }


    ///========================================///

    string Profile_Base::return_name() {
        return this->vards;
    }

    string Profile_Base::return_surname() {
        return this->uzvards;
    }

    string Profile_Base::return_login() {
        return this->login;
    }

    int Profile_Base::returnPermission() {
        return this->Permission;
    }

    int Profile_Base::return_merchant_prece_ID(int izvele) {
        return this->pardeveja_preces.at(izvele-1);
    }

    int Profile_Base::return_prece_skaits() {
        return this->pardeveja_preces.size();
    }
