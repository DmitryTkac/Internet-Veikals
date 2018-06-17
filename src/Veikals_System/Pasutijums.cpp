#include "../../headers/Veikals_System/Pasutijums.h"
#include "../../headers/funckijas.h"

#include <fstream>
#include <windows.h>

using namespace std;

void Pasutijums::izveidotPasutijumu(int ID, string adrese, string talr) {

    string way;

    ifstream pasut;

    this->produkta_ID = ID;
    setAdrese(adrese);
    setTalr(talr);

    while(true) {

        this->pasutijuma_NR = rand()%100000+1;
        way = "Veikals/Pasutijumi/" + IntToStr(this->pasutijuma_NR) + ".txt";
        pasut.open(way.c_str());

        if (pasut) {

        } else {
            pasut.close();
            ofstream izveidot (way.c_str());
            izveidot << this->produkta_ID << endl << this->adrese << endl << this->talr;
            izveidot.close();

            fstream p_saraksts ("Veikals/Pasutijumi/Pasutijumu_saraksts.txt", ios::app);
            p_saraksts << this->pasutijuma_NR << endl;
            p_saraksts.close();

            //cout << this->produkta_ID << endl << this->talr << endl << this->adrese << endl;


            break;
        }

        pasut.close();


    }

}

void Pasutijums::showInfo() {
    cout
    << "PASUTIJUMA INFO" << endl
    << "Pasutijuma NR: " << this->pasutijuma_NR << endl
    << "Preces ID: " << this->produkta_ID << endl
    << "Klienta adrese: " << this->adrese << endl
    << "Klienta talr: " << this->talr << endl;
}


void Pasutijums::getInfoFromFile(int NR) {

    this->pasutijuma_NR = NR;

    string way = "Veikals/Pasutijumi/" + IntToStr(this->pasutijuma_NR) + ".txt";

    ifstream p_saraksts (way.c_str());

    getline(p_saraksts, way);
    this->produkta_ID = StrToInt(way);
    getline(p_saraksts, way);
    this->adrese = way;
    getline(p_saraksts, way);
    this->talr = way;

}



///=====================================///

void Pasutijums::setAdrese(string adrese) {
    this->adrese = adrese;
}

void Pasutijums::setTalr(string talr) {
    this->talr = talr;
}

string Pasutijums::getAdrese() {
    return this->adrese;
}

string Pasutijums::getTalr() {
    return this->talr;
}

int Pasutijums::getID() {
    return this->produkta_ID;
}

int Pasutijums::getNR() {
    return this->pasutijuma_NR;
}
