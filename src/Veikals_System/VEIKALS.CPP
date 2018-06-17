#include <iostream>
#include <windows.h>
#include <direct.h>
#include <fstream>

#include "../../headers/Veikals_System/Veikals.h"

#include "../../headers/Veikals_System/Veikals_Menu.h"
#include "../../headers/Veikals_System/Admin_Menu.h"
#include "../../headers/Veikals_System/Merchant_,Menu.h"
#include "../../headers/Veikals_System/User_Menu.h"
#include "../../headers/Veikals_System/Guest_Menu.h"


using namespace std;


    void Veikals::enter_Veikals(int Level, Profile_Base *profile) {

        mkdir("Veikals");
        mkdir("Veikals/Produkti");

        ifstream p_saraksts;

        string NR_str;


        //ifstream produkti ("Veikals/Produkti")

        int izvele;
        string loma;
        Menu_base *menu;


        vector <Pasutijums> orders;
        Pasutijums buffer;
        //vector <Pasutijums> *ptr_pasutijums = &orders;

        orders.clear();

        //cout << Level << endl;
        switch (Level) {

            case 0: {
                menu = new Guest_Menu;
                profile->setGuest();
                loma = "Viesis";
                break;
            }

            case 1: {
                menu = new User_Menu;
                loma = "Lietotajs";
                break;
            }

            case 2: {
                menu = new Merchant_Menu;
                loma = "Pardevejs";
                break;
            }

            case 3: {
                menu = new Admin_Menu;
                loma = "Administrators";
                break;
            }
        }

        system("CLS");

        do{

            orders.clear();
            p_saraksts.open("Veikals/Pasutijumi/Pasutijumu_saraksts.txt");

            while(getline(p_saraksts, NR_str)) {            ///Atjaunina pasutijumu info, tada veida parbaudot uz izmainam
                buffer.getInfoFromFile(StrToInt(NR_str));   ///
                orders.push_back(buffer);
            }

            if (Level) {
                cout << "Sveiks, " << profile->return_name() << " " << profile->return_surname() << endl;
            }
            if (Level == 2) {
                profile->get_Merchant_Produkts(profile->return_login());
            }
            menu->show_Menu(loma);
            cin >> izvele;

            system("CLS");

            if (menu->izvele(izvele, profile, &orders)) {
                delete menu;
                break;
            }

            orders.resize(getCount("Veikals/produkti.txt"));

            p_saraksts.close();


        } while (true);

    }

