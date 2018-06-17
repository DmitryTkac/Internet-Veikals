#include <iostream>
#include <windows.h>
#include <fstream>
#include <math.h>


#include "../../headers/Veikals_System/Admin_Menu.h"
#include "../../headers/funckijas.h"

using namespace std;

    void Admin_Menu::show_Menu(string loma) {


            cout
            << "Jus iegajat ka " << loma  << "!\n" << endl
            << " 1 | Parskatit visas preces" << endl
            << " 2 | Meklet" << endl
            << " 3 | Rediget datus" << endl
            << " 4 | Iziet" << endl
            << "   | Jusu izvele: ";

    }

    bool Admin_Menu::izvele(int izvele,Profile_Base *profile, vector <Pasutijums> *pasutijumi) {

        switch(izvele) {

            case 1: {
                if (this->prece.showProductInfo(this->prece.showProducts())) {

                    cout
                    << "1 | Veikt pirkumu" << endl
                    << "2 | Parskatit citas preces" << endl
                    << "0 | Iziet" << endl;

                    cin >> izvele;
                    if (izvele == 1) {
                        if (profile->returnPermission() > 0) {
                            int akcija = rand()%3; // random ja 0 = 5% (minimala pierigistretam lietotajam!), 1 = 10%, 2 = turpina randomu uz 20% vai lidz 50%
                            cout << "Apsveicam! Jus sanemat akcijas kuponu uz ";
                            if (akcija == 2) {
                                akcija = rand() % 2;
                                if (akcija == 1) {
                                    akcija = rand() % 2;
                                    if (akcija == 1) {
                                        akcija = rand() % 2;
                                        if (akcija == 1) {
                                            cout << "50%" << endl;
                                            cout << "Tgad produkts maksas: " << roundf(this->prece.returnCena() * 0.5 * 100) / 100 << endl; //roundf(this->cena * 100) / 100;
                                        } else {
                                            cout << "40%" <<endl;
                                            cout << "Tgad produkts maksas: " << roundf(this->prece.returnCena() * 0.6 * 100) / 100 << endl;
                                        }
                                    } else {
                                        cout << "30%!" << endl;
                                        cout << "Tgad produkts maksas: " << roundf(this->prece.returnCena() * 0.7 * 100) / 100 << endl;
                                    }
                                } else {
                                    cout << "20%" << endl;
                                    cout << "Tgad produkts maksas: " << roundf(this->prece.returnCena() * 0.8 * 100) / 100 << endl;
                                }
                            } else if (akcija == 1) {
                                cout << "10%!" << endl;
                                cout << "Tgad produkts maksas: " << roundf(this->prece.returnCena() * 0.9 * 100) / 100 << endl;
                            } else {
                                cout << "5%!" << endl;
                                cout << "Tgad produkts maksas: " << roundf(this->prece.returnCena() * 0.95 * 100) / 100 << endl;
                            }
                        } else {
                            cout << "Lai sanemt akcijas kuponu vajag pieregistreties vai ieiet sava profila!" << endl;
                        }

                        this->prece.veikt_Pirkumu();
                    } else if(izvele == 2) {
                        this->izvele(1, profile, pasutijumi);
                    } else if (izvele != 0) {
                        cout << "Izveleta nepareiza darbiba!" << endl;
                        system("PAUSE");

                    }
                }

                break;
            }

            case 2: {
                cout << "MEKLESANA" << endl;
                break;
            }

            case 3: {
                this->redig_Menu();
                break;
            }

            case 4: {
                return true;
            }

            default: cout << "Izveleta nepareiza datbiba!" << endl; system("pause");

        }

        //system("PAUSE");
        system("CLS");
        return false;


    }

    void Admin_Menu::redig_Menu() {
        int izvele;

        do {
            system("CLS");
            cout << "|== DATU REDIGESANA==|" << endl
            << "1 | Rediget profilus" << endl
            << "2 | Rediget preces" << endl
            << "3 | Iziet" << endl
            << "  | Jusu izvele: ";

            cin >> izvele;

            switch (izvele) {

                case 1: {
                    this->prof_Redig_Menu(this->profils.showProfiles());
                    break;
                }

                case 2: {
                    this->prec_Redig_Menu(this->prece.showProducts());
                    break;
                }

                case 3: {
                    break;
                }

                default: {
                    cout << "Izveleta nepareiza darbiba!" << endl;
                    system("PAUSE");
                }

            }

        } while (izvele != 3);
    }


    void Admin_Menu::prof_Redig_Menu(string login) {

        int izvele;
        string login_way = "Profiles/Profiles_Info/" + login + ".txt";

        Profile_Base edit_prof;

        if (login == "0") {
            return;
        }

        if (!edit_prof.get_File_Info(login_way)) {
            return;
        }

        do {
            system("CLS");

            cout << "Profils: " << edit_prof.return_name() << " " << edit_prof.return_surname() << endl << "Limenis: ";

            switch (edit_prof.returnPermission()) {

                case 1: {
                        cout << "Lietotajs" << endl;
                        break;
                    }

                    case 2: {
                        cout << "Pardevejs" << endl;
                        break;
                    }

                    case 3: {
                        cout << "Administrators" << endl;
                        break;
                    }

            }

            cout << "|== DATU REDIGESANA==|" << endl
            << "1 | Izmainit Vardu" << endl
            << "2 | Izmainit Uzvardu" << endl
            << "3 | Izmainit lieotaja lomu" << endl
            << "4 | Dzest Profilu" << endl
            << "5 | Iziet" << endl
            << "  | Jusu izvele: ";

            cin >> izvele;

            switch(izvele) {

                case 1: {
                    edit_prof.changeName(login_way);
                    break;
                }

                case 2: {
                    edit_prof.changeSurname(login_way);
                    break;
                }

                case 3: {
                    edit_prof.changePermission(login_way);
                    break;
                }

                case 4: {

                    if (edit_prof.returnPermission() == 3) {
                        cout << "Administratora profilu nedrikst dzest!" << endl;
                        system("PAUSE");
                        return;
                    }

                    cout << "Jus tiesam gribiet nodzest so profilu? ievadiet, 0 -[NE], ja negribiet: " << endl;
                    cin >> izvele;
                    if (izvele) {
                        edit_prof.delete_profile(login, login_way);
                        return;
                    }
                    break;
                }

                case 5: {
                    break;
                }

                default: cout << "Izveleta nepareiza darbiba" << endl; system("PAUSE");

            }

        } while (izvele != 5);

    }

    void Admin_Menu::prec_Redig_Menu(int ID) {

        if (!ID) return;

        int izvele;

        do {
            system("CLS");

            this->prece.showProductInfo(ID);

            cout << "|== DATU REDIGESANA==|" << endl
            << "1 | Izmainit preces nosaukumu" << endl
            << "2 | Izmainit preces cenu" << endl
            << "3 | Izmainit preces aprakstu" << endl
            << "4 | Dzest preci" << endl
            << "5 | Nomainit preces daudzumu" << endl
            << "6 | Iziet" << endl
            << "  | Jusu izvele: ";

            cin >> izvele;

            this->prece.rediget(izvele, ID);

            switch (izvele) {

                case 1: break;
                case 2: break;
                case 3: break;

                case 4: {

                    cout << "Jus tiesam gribiet nodzest so produktu? [1 - JA | 0 - NE]: " << endl;
                    cin >> izvele;

                    if (izvele == 1) {
                        this->prece.dzestProduktu(ID);
                    }

                    izvele = 6;

                    break;

                }

                case 5: {
                    break;
                }

                case 6: {
                    break;
                }

                default: {
                    cout << "Izveleta nepareiza darbiba!" << endl;
                    system("PAUSE");
                }

            }

        } while (izvele != 6);

    }






