#ifndef PROFILU_BAZE_H_INCLUDED
#define PROFILU_BAZE_H_INCLUDED


#include <iostream>
#include <vector>

//#include "../Veikals_System/Veikals.h"

class Profile_Base {

    public:

        Profile_Base();
        void registration();
        bool log(std::string, std::string);
        void getPermission(std::string);
        int returnPermission();

        std::string showProfiles();

        void changeName(std::string);
        void changeSurname(std::string);
        void changePermission(std::string);

        std::string return_name();
        std::string return_surname();
        std::string return_login();

        int return_merchant_prece_ID(int);
        int return_prece_skaits();

        int showMerchantProducts();

        bool get_File_Info(std::string);

        void delete_profile(std::string, std::string);

        void addProd_To_Stat();



        void get_Merchant_Produkts(std::string);

        void setGuest();


    private:

        int Permission;

        std::string vards, uzvards, login;
        std::vector<int> pardeveja_preces;

        void change_File_Info(std::string);

    protected:


};


#endif // PROFILU_BAZE_H_INCLUDED
