#include <iostream>
#include <windows.h>
#include <fstream>
#include <math.h>


#include "../../headers/Veikals_System/Merchant_,Menu.h"
#include "../../headers/funckijas.h"

using namespace std;

    void Merchant_Menu::show_Menu(string loma) {


            cout
            << "Jus iegajat ka " << loma  << "!\n" << endl
            << " 1 | Parskatit visas preces" << endl
            << " 2 | Meklet" << endl
            << " 3 | Pievienot preci" << endl
            << " 4 | Rediget preces" << endl
            << " 5 | Pasutijumi" << endl
            << " 6 | Iziet" << endl
            << "   | Jusu izvele: ";

    }

        bool Merchant_Menu::izvele(int izvele, Profile_Base *profile, vector <Pasutijums> *pasutijumi) {



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
                system("PAUSE");

                break;
            }

            case 3: {

                this->prece.addProduct();
                profile->addProd_To_Stat();
                //system("PAUSE");
                break;
            }

            case 4: {
                int ID;
                if(!profile->showMerchantProducts()) {
                    system("PAUSE");
                    break;
                }
                cout
                << "0 | Iziet" << endl
                << "  | Jusu izvele: ";
                cin >> ID;

                if (ID > 0 && ID <= profile->return_prece_skaits()) {

                    do {
                        this->prece.showProductInfo(profile->return_merchant_prece_ID(ID));
                        this->prec_Regig_Menu();
                        cin >> izvele;


                        if (izvele) {
                            if (izvele == 4) {
                                cout << "Jus tiesam gribiet nodzest so produktu? [1 - JA | 0 - NE]: " << endl;
                                cin >> izvele;

                                if (izvele == 1) {
                                    this->prece.dzestProduktu(profile->return_merchant_prece_ID(ID));
                                }

                                izvele = 7;
                            }


                            this->prece.rediget(izvele, profile->return_merchant_prece_ID(ID));
                        }
                        //this->prece.ShowProductInfo(profile->return_merchant_prece_ID(ID));
                    } while (izvele != 6);

                } else if (ID) {
                    cout << "Ievadits/izvelets nepareizs produkta ID!" << endl;
                    system("PAUSE");
                }
                break;
            }

            case 5: {

                vector <int> orders_list;
                int k = 0;
                string buff;

                for (int i = 0; i < profile->return_prece_skaits(); i++) {
                    if (pasutijumi->size()) {
                        for (int j = 0; j < pasutijumi->size(); j++) {
                            if (profile->return_merchant_prece_ID(i+1) == pasutijumi->at(j).getID()) {
                                orders_list.push_back(j);
                                cout << ++k << " | " << pasutijumi->at(j).getNR() << endl;

                            }
                        }
                    }

                }
                cout << "  | Jusu izvele: ";
                cin >> izvele;
                system("CLS");
                if (orders_list.size() < izvele || izvele <= 0) {
                    cout << "Ievadits nepareizs ID!" << endl;
                    system("PAUSE");
                    break;
                } else {
                    pasutijumi->at(orders_list[izvele-1]).showInfo();
                    k = orders_list[izvele - 1];
                }

                cout << "1 | Apstradat pasutijumu" << endl << "0 | Iziet" << endl << "  | Jusu izvele: ";
                cin >> izvele;

                if (izvele == 1) {

                    ifstream orders ("Veikals/Pasutijumi/Pasutijumu_saraksts.txt");
                    ofstream backup ("backup.txt");
                    while (getline(orders, buff)) {
                        backup << buff << endl;
                    }
                    orders.close();
                    backup.close();

                    orders.open("backup.txt");
                    backup.open("Veikals/Pasutijumi/Pasutijumu_saraksts.txt");

                    while (getline(orders, buff)) {

                        if (StrToInt(buff) == pasutijumi->at(k).getNR()) {

                            cout << "Pasutijums " << pasutijumi->at(k).getNR() << " tika apstradats!" << endl;
                            buff = "Veikals/Pasutijumi/" + IntToStr(pasutijumi->at(k).getNR()) + ".txt";
                            remove(buff.c_str());

                        } else {
                            backup << buff << endl;
                        }

                    }

                    orders.close();
                    backup.close();

                } else if (izvele) {
                    cout << "Nepareiza darbiba!" << endl;

                }
                system("PAUSE");
                izvele = 7;
                break;

            }

            case 6: {
                return true;
            }

            default: cout << "Izveleta nepareiza datbiba!" << endl; system("PAUSE");

        }

        //system("PAUSE");
        system("CLS");
        return false;


    }

    void Merchant_Menu::prec_Regig_Menu() {

            cout << "|== DATU REDIGESANA==|" << endl
            << "1 | Izmainit preces nosaukumu" << endl
            << "2 | Izmainit preces cenu" << endl
            << "3 | Izmainit preces aprakstu" << endl
            << "4 | Dzest preci" << endl
            << "5 | Nomainit preces daudzumu" << endl
            << "6 | Iziet" << endl
            << "  | Jusu izvele: ";

    }


