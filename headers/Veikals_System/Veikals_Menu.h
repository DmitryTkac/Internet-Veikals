#ifndef VEIKALS_MENU_H_INCLUDED
#define VEIKALS_MENU_H_INCLUDED


#include "Products.h"
#include "../Profiles_System/profiles_base.h"
#include "Pasutijums.h"

class Menu_base {

    public:

        Products prece;
        Profile_Base profils;

        virtual void show_Menu(std::string);
        virtual bool izvele(int, Profile_Base *, std::vector <Pasutijums> *);

        void meklesana(std::string);

    private:

    protected:


};

#endif // VEIKALS_MENU_H_INCLUDED
