#ifndef PASUTIJUMS_H_INCLUDED
#define PASUTIJUMS_H_INCLUDED

#include <iostream>
#include <vector>

class Pasutijums {

    public:
        void setAdrese(std::string);
        void setTalr(std::string);
        std::string getAdrese();
        std::string getTalr();

        void izveidotPasutijumu(int, std::string, std::string);

        void getInfoFromFile(int);
        void Update();

        int getID();
        int getNR();

        void showInfo();

    private:
        std::string adrese, talr;
        int produkta_ID;
        int pasutijuma_NR;
    protected:



};

#endif // PASUTIJUMS_H_INCLUDED
