#ifndef ADMIN_MENU_H_INCLUDED
#define ADMIN_MENU_H_INCLUDED

#include "Veikals_Menu.h"

class Admin_Menu : public Menu_base{

    void show_Menu(std::string);
    bool izvele(int, Profile_Base *, std::vector <Pasutijums> *);
    void redig_Menu();
    void prof_Redig_Menu(std::string);
    void prec_Redig_Menu(int);
    //std::string ShowProfiles();


};


#endif // ADMIN_MENU_H_INCLUDED
