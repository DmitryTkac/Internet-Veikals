#ifndef MERCHANT_,MENU_H_INCLUDED
#define MERCHANT_,MENU_H_INCLUDED

#include "Veikals_Menu.h"

class Merchant_Menu : public Menu_base{

    void show_Menu(std::string);
    bool izvele(int, Profile_Base *, std::vector <Pasutijums> *);
    void prec_Regig_Menu();

};

#endif // MERCHANT_,MENU_H_INCLUDED
