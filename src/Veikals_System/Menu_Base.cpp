#include <iostream>
#include <windows.h>
#include <fstream>
#include <cmath>

#include "../../headers/Veikals_System/Veikals_Menu.h"
#include "../../headers/funckijas.h"
#include "../../headers/Veikals_System/Veikals.h"
#include "../../headers/Veikals_System/Pasutijums.h"

using namespace std;

    void Menu_base::show_Menu(string loma) {


            cout
            << "Jus iegajat ka " << loma  << "!\n" << endl
            << " 1 | Parskatit visas preces" << endl
            << " 2 | Meklet" << endl
            << " 3 | Iziet" << endl
            << "   | Jusu izvele: ";


    }

    bool Menu_base::izvele(int izvele,Profile_Base *profile, vector <Pasutijums> *pasutijumi) {

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
                string word;
                cout << "MEKLESANA" << endl;
                fflush(stdin);
                getline(cin, word);
                this->meklesana(word);
                system("PAUSE");
                break;
            }

            case 3: {
                return true;
            }

            default: cout << "Izveleta nepareiza datbiba!" << endl; system("PAUSE");

        }

        //system("PAUSE");
        system("CLS");
        return false;


    }


    void Menu_base::meklesana(string ko_meklet) {
        string buff, buff_small;
        ifstream preces_saraksts ("Veikals/produkti.txt");
        int i = 0;

        for (int i = 0; i < ko_meklet[i]; i++) {
                if (ko_meklet[i] >= 65 && ko_meklet[i] <= 90) {
                    ko_meklet[i] += 32;
                }
            }

        while (getline(preces_saraksts, buff)) {

            buff_small = buff;

            for (int i = 0; i < buff_small[i]; i++) {
                if (buff_small[i] >= 65 && buff_small[i] <= 90) {
                    buff_small[i] += 32;
                }
            }

            if (buff_small.find(ko_meklet) >= 0 && buff_small.find(ko_meklet) < 10000) {
                cout << ++i << " " << buff << endl;
            }
            //cout << buff.find(ko_meklet) << endl
        }

        preces_saraksts.clear();

    }

