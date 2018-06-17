#include "../../headers/Veikals_System/Products.h"
#include "../../headers/funckijas.h"

#include <fstream>
#include <windows.h>
#include <cmath>
#include <vector>

#include "../../headers/Veikals_System/Pasutijums.h"

using namespace std;



    int Products::showProductInfo(int izvele) {

        if(!izvele) {
            return 0;
        }

        system("CLS");
        this->ID = izvele;
        get_Product_Info(izvele);

        cout
        << "Prece    | " << this->nosaukums << endl
        << "Cena     | " << this->cena << " EUR" << endl
        << "Apraksts | " << this->apraksts << endl
        << "Skaits   | " << this->prod_skaits << endl;


        //system ("PAUSE");

    }

    void Products::addProduct() {

        int izvele;

        cout << "|=PRECES PIEVIENOSANA=|" << endl;
        cout << "Ievadiet produkta nosaukumu: ";
        fflush(stdin);
        getline(cin, this->nosaukums);

        do {

            cout << "Ievadiet preces cenu: ";
            fflush(stdin);
            cin >> this->cena;

            this->cena = roundf(this->cena * 100) / 100;

            if (this->cena <= 0) {
                cout << "Cena nevarbut vienada ar 0 vai mazaka par 0.01!! Ievadiet velreiz!" << endl;
            } else if (this->cena >= 0.005) {
                cout << "Jusu cena tika automatiski noapalota uz " << cena << " EUR" << endl;
            }

        } while (this->cena <= 0);

        cout << "Ievadiet preces aprakstu: ";
        fflush(stdin);
        getline(cin, this->apraksts);

        do {

            cout << "Ievadiet jusu preces tagadeju skaitu: ";
            cin >> this->prod_skaits;

            if  (this->prod_skaits <= 0) {
                cout << "Preces skaits nevar but mazaks vai vienads ar 0!" << endl;
            }

        } while (this->prod_skaits <= 0);

        cout
        << endl << "Jus velaties izdarit preci: " << this->nosaukums
        << endl << "Ar cenu: " << this->cena << " EUR"
        << endl << "Aprakstu: " << this->apraksts
        << endl << "Skaitu: " << this->prod_skaits << endl;
        cout << "[1 - JA | 0 - NE] : ";
        cin >> izvele;

        if (izvele) {

            fstream produkti("Veikals/produkti.txt", ios::app);
            produkti << this->nosaukums << endl;

            produkti.close();

            produkti.open("Veikals/produkti.txt");

            string line;
            int i = 0;

            while (getline(produkti, line)) {
                i++;
            }

            produkti.close();

            line = "Veikals/Produkti/" + IntToStr(i) + "_Produkts.txt";



            ofstream produkts_info (line.c_str());

            produkts_info << this->nosaukums << endl << this->cena << endl << this->apraksts << endl << this->prod_skaits;

            produkts_info.close();

        }
    }

    int Products::showProducts() {
        int izvele;
        string line;


        ifstream produkti("Veikals/produkti.txt");

        int i;
        int sakums = 0;
        int SFbuff = 0, EFbuff = 0;

        vector<int> startfrom (99);
        startfrom.at(0) = 0;

        int LPP = 0;
        int const PPL = 10; ///Products per List -2, lai parslegties starp lapaspusem
        while (true) {
            system("CLS");
            cout << "|= PRECES =|" << endl;

            produkti.clear();
            produkti.seekg(startfrom.at(LPP), ios::beg);


            SFbuff = startfrom.at(LPP);

            i = sakums;

            cout << "|=  " << LPP+1 << " LPP =|" <<endl;

            while (getline(produkti, line) && i != sakums+PPL-2) {
                SFbuff += line.length()+2;
                i++;
                cout << i << " | " <<  line << endl;

            }

            //cout << SFbuff << endl;

            if (i == sakums+PPL-2) {
              cout << "9 | Nakama LPP"    << endl;
            }

            if (i > 0 && LPP > 0) {
                cout << "10 | Pagajusa LPP" << endl;
            }


            if (i == 0) {
                cout << "Paslaik nekadu produktu nav atrasts" << endl;

            }

            cout
            //<< "9 | Nakala LPP" << endl
            << "0 | Iziet." << endl
            << "  | Jusu izvele: ";
            cin >> izvele;

            if (!izvele) return 0;

            if(izvele == 9 && i == sakums+PPL-2) {
                LPP++;
                sakums += PPL;
                //EFbuff = startfrom.at(LPP-1);
                startfrom.at(LPP) = SFbuff;
                continue;
            }

            if (izvele == 10 && i > 0 && LPP > 0) {
                LPP--;
                sakums -= PPL;
                //startfrom = startfrom.at(LPP);
                continue;
            };

            system("CLS");

            if (!izvele) {
                break;
            } else if (izvele >= sakums+1 && izvele <= i) {
                //cout << "IR" << endl;

                return izvele-LPP*2; ///ATGRIEZ PRECES ID KURU VAJAG REDIGET

            } else {

                cout << "Produkta ar tadu ID saja lpp nav" << endl;
                system("PAUSE");
            }


        }

        produkti.close();
    }

    void Products::veikt_Pirkumu() {

        Pasutijums order;

        if (this->prod_skaits == 0) {
            cout << "Paslaik noliktava nav produktu! Uzgaidiet kamer pardevejs to papildinas" << endl;
            system("PAUSE");
            return;
        }

        string adrese, tlr_numurs;
        int izvele;
        int const MAX_SIMB_COUNT = 12;
        int const MIN_SIMB_COUNT = 8;

        cout << "Jus tiesam gribiet nopirkt so produktu?" << endl << "ievadiet, 0 -[NE], ja negribiet: ";
        cin >> izvele;

        if (!izvele) {
            return;
        }

        cout << "Lai veikt pirkumu jums vajadzes aizpildit formu!" << endl;
        system("PAUSE");
        cout << "|==FORMAS AIZPILDISANA=|" << endl;
        cout << "Ievadiet adresi: ";

        fflush(stdin);
        getline(cin, adrese);

        cout << "Ievadiet talruna numuru: ";

        fflush(stdin);
        getline(cin, tlr_numurs);

        system("CLS");

        int i;

        for (i = 0; i <= tlr_numurs[i]; i++);

        if (i == MAX_SIMB_COUNT && tlr_numurs.at(0) == '+' && tlr_numurs.at(1) == '3' && tlr_numurs.at(2) == '7' && tlr_numurs.at(3) == '1' && tlr_numurs.at(4) == '2') {

        } else if (i == MIN_SIMB_COUNT && tlr_numurs.at(0) == '2') {
        } else {
            system("CLS");
            cout << "Jusu ievaditajs talrunis ir ievadits nepareiza formata!" << endl;
            system("PAUSE");
            return;
        }

        rediget(0, this->ID);

        order.izveidotPasutijumu(this->ID, adrese, tlr_numurs);

        cout << "Jusu forma tika atsutita gaidiet kamer ar jums sazinasies pardevejs!" << endl;
        system("PAUSE");
        return;




    }

    void Products::dzestProduktu(int ID) {

        ifstream produkti ("Veikals/produkti.txt");
        ofstream backup ("backup.txt");

        int ProdCount = 0;

        string name, newname;

        while (getline(produkti, name)) {
            ProdCount++;
            backup << name << endl;
        }


        backup.close();
        produkti.close();
        name = "Veikals/Produkti/" + IntToStr(ID) + "_Produkts.txt";
        remove(name.c_str());

        int i;

        for (i = ID+1; i <= ProdCount; i++) {
            name = "Veikals/Produkti/" + IntToStr(i) + "_Produkts.txt";
            newname = "Veikals/Produkti/" + IntToStr(i-1) + "_Produkts.txt";
            rename(name.c_str(), newname.c_str());
        }

        produkti.open("backup.txt");
        backup.open("Veikals/produkti.txt");

        i = 0;

        while (getline(produkti, name)) {

            i++;

            if (i == ID) {

            } else {
                backup << name << endl;
            }

        }

        produkti.close();
        backup.close();




        int number;
        string login, prod;
        vector<int> IDs;

        ofstream backup_prod ("Profiles/Profila_Preces_bck.txt");

        produkti.open("Profiles/Profila_Preces.txt");

        ifstream nolasit;

        while (true) {
            backup.open("backup.txt");
            number = 0;


            produkti >> login;

            if (produkti.eof()) {
                produkti.close();
                break;
            }

            getline(produkti, prod);
            backup << prod;
            //cout << skipper;
            backup.close();
            nolasit.open("backup.txt");

            IDs.clear();

            while (true) {

                if (nolasit.eof()) {
                    nolasit.close();

                    break;
                }

                nolasit >> number;

                if (number > ID) {
                    number--;
                } else if (number == ID) {
                    number = 0;
                }
                //cout << ID << endl;
                if (number) {
                    IDs.push_back(number);
                }
            }


            backup_prod << login;

            for (int i = 0; i < IDs.size(); i++) {
                backup_prod << " " << IDs.at(i);
            }

            backup_prod << endl;


        }

        backup_prod.close();
        produkti.open("Profiles/Profila_Preces_bck.txt");
        backup_prod.open("Profiles/Profila_Preces.txt");
        while (getline(produkti, prod)) {

            backup_prod << prod << endl;

        }

        system("PAUSE");

    }

     void Products::rediget(int izvele, int ID) {
        string way = "Veikals/Produkti/" + IntToStr(ID) + "_Produkts.txt";

        ifstream product (way.c_str());
        ofstream product_red;

                getline(product, this->nosaukums);
                product >> this->cena;
                getline(product, this->apraksts);
                getline(product, this->apraksts);
                product >> this->prod_skaits;

        product.close();

        switch (izvele) {

            case 1: {
                cout << "Ievadi jauni preces nosaukumu: ";
                fflush(stdin);
                getline(cin, this->nosaukums);


                string way_nos = "Veikals/produkti.txt";

                product.open(way_nos.c_str());
                product_red.open("backup.txt");

                int i = 0;
                string line;

                while (getline(product, line)) {
                    i++;

                    if(i == ID) {
                        product_red << this->nosaukums << endl;
                    } else {
                        product_red << line << endl;
                    }



                }

                product_red.close();
                product_red.open(way_nos.c_str());

                product.close();
                product.open("backup.txt");

                while (getline(product, line)) {

                    product_red << line << endl;

                }

                product.close();
                product_red.close();


                break;
            }

            case 2: {

                do {

                    cout << "Ievadiet jaunu preces cenu: ";
                    fflush(stdin);
                    cin >> this->cena;

                    this->cena = roundf(this->cena * 100) / 100;

                    if (cena <= 0) {
                        cout << "Cena nevarbut vienada ar 0 vai mazaka par 0.01!! Ievadiet velreiz!" << endl;
                    } else if (this->cena >= 0.005) {
                        cout << "Jusu cena tika automatiski noapalota uz " << this->cena << " EUR" << endl;
                    }

                } while (this->cena <= 0);
                break;
            }

            case 3: {
                cout << "Ievadiet jaunu preces aprakstu: ";
                fflush(stdin);
                getline(cin, this->apraksts);
            }


            case 5: {
                cout << "Ievadiet jaunu preces skaitu: ";
                cin >> this->prod_skaits;
            }
        }

        product_red.open(way.c_str());

        if (izvele == 0) {
            this->prod_skaits--;
        }

        product_red << this->nosaukums << endl << this->cena << endl << this->apraksts << endl << this->prod_skaits;

        product_red.close();


        //cout << nosaukums << cena << apraksts << endl;
        //system("PAUSE");

    }

    void Products::get_Product_Info(int ID) {

        string way = "Veikals/Produkti/" + IntToStr(ID) + "_Produkts.txt";
        ifstream produkts (way.c_str());
        //cout << way << endl;

        getline(produkts, this->nosaukums);
        produkts >> this->cena;
        getline(produkts, this->apraksts);
        getline(produkts, this->apraksts);
        produkts >> this->prod_skaits;

        produkts.close();

    }

    string Products::returnProdName() {
        return this->nosaukums;
    }

    double Products::returnCena() {
        return this->cena;
    }
