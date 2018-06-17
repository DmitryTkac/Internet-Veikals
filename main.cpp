#include <iostream>
#include <windows.h>
#include <time.h>

#include "headers/Profiles_System/profiles_base.h"
#include "headers/Veikals_System/Veikals.h"

using namespace std;



void menu();
void izvele(bool*);

int main() {

    srand(time(NULL));

    bool cikls = true;
    bool *ptr_cikls = &cikls;

    while (cikls) {
        system("CLS");
        cout << "'INTERNET VEIKALS'" << endl;

        menu();
        izvele(ptr_cikls);
    }
}

void menu () {

    cout
    << "\n 1 | Ieiet Profila" << endl
    << " 2 | Registreties" << endl
    << " 3 | Ieiet veikala" << endl
    << " 4 | Iziet no programmas" << endl;
}

void izvele(bool* cikls) {

    Profile_Base profile;
    Profile_Base *ptr_profile = &profile;
    Veikals Shop;

    int izvele;

    string login, parole;

    cout << "   | Jusu darbiba: ";
    cin >> izvele;

    system("CLS");

    switch (izvele) {

        case 1: {
            cout << "Ieiet profila" << endl;
            cout << "Ievadiet savu login: ";
            cin >> login;
            cout << "Ievadiet savu paroli: ";
            cin >> parole;

            if(profile.log(login, parole)) {
                Shop.enter_Veikals(profile.returnPermission(), ptr_profile);
                //system("PAUSE");
            }

            break;
        }

        case 2: {
            profile.registration();
            break;
        }

        case 3: {

            Shop.enter_Veikals(0, ptr_profile);
            break;
        }
        case 4: {
            *cikls = false;

            break;
        }

        default: {
            cout << "Kluda: Izveleta nepareiza darbiba!" << endl;
            system("Pause");
            system("CLS");
        }

    }

}
