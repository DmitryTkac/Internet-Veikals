#ifndef PRODUCTS_H_INCLUDED
#define PRODUCTS_H_INCLUDED

#include <iostream>
#include <vector>

#include "pasutijums.h"

class Products {
    public:

        int showProducts();
        void dzestProduktu(int);
        int showProductInfo(int);
        void addProduct();
        void rediget(int, int);
        void get_Product_Info(int);
        std::string returnProdName();
        void veikt_Pirkumu();
        double returnCena();

    private:

        std::string nosaukums;
        std::string apraksts;
        double cena;
        int prod_skaits, ID;


    protected:
};

#endif // PRODUCTS_H_INCLUDED
