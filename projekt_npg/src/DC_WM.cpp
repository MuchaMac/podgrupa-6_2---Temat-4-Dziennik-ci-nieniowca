#include "DC.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
date::date(unsigned int d, unsigned int m, unsigned int r) {
    set_data(d, m, r);
}

const std::vector<int> mies_31d {1,3,5,7,8,10,12}; //wektor miesięcy które mają 31 dni
const std::vector<int> mies_30d {4,6,9,11}; //wektor miesięcy które mają 30 dni
//zostaje 2 - luty, który ma 28 lub 29 dni

bool sprawdzacz_elem_w_kontenerze(const std::vector<int>& wektor, int miesiac) { //sprawdza czy podany miesiac jest w którymś z kontenerów
    for(auto elem : wektor) {
        if (elem == miesiac){
            return true;
        }
    }
    return false;
}


void date::set_dzien(unsigned int dzien, unsigned int miesiac, unsigned int rok){
    dzien_ = 0;  // wstępnie ustawia dzien_ na -1, co zostanie zmienione gdy data jest dobrze podana

    if (miesiac >= 1 && miesiac <= 12) { // sprawdza czy miesiąc należy do <1;12>

        if (sprawdzacz_elem_w_kontenerze(mies_31d, miesiac)) {

            if (dzien >= 1 && dzien <= 31) {
                dzien_ = dzien; // sprawdziło że miesiąć ma 31 dni, a dzień nalezy do <1;31> więc może ustawić
            }

        } else if (sprawdzacz_elem_w_kontenerze(mies_30d, miesiac)) {
            if (dzien >= 1 && dzien <= 30) {
                dzien_ = dzien; // sprawdziło że miesiąć ma 30 dni, a dzień nalezy do <1;30> więc może ustawić
            }

        } else if (((rok % 4 == 0 && rok % 100 != 0) || (rok % 400 == 0)) && dzien == 29) { //sprawdza ewentualność, że rok jest przestępny i ustawia 29 luty
            dzien_ = dzien;
        } else if (dzien >= 1 && dzien <= 28) {
            dzien_ = dzien; // tutaj po prostu ustawia dla lutego dzień w rok nieprzestępny
        }
    }
}

void date::set_miesiac(unsigned int miesiac) {
    miesiac_ = 0;
    if (miesiac >= 1 && miesiac <= 12) {
        miesiac_ = miesiac;
    }
}

void date::set_rok(unsigned int rok) {
    rok_ = 0;
    if (rok > 0){
        rok_ = rok;
    }
}

std::string date::data_str_templet() const {
    std::ostringstream oss;

    if(dzien_ >= 1 && dzien_ <= 9) {
    }
    oss.fill('0');
    oss << std::setw(2) << dzien_ << ".";
    oss << std::setw(2)  << miesiac_ << "." ;
    oss << std::setw(4)  << rok_;
    return oss.str();
}

unsigned int date::get_dzien() const {
    return dzien_;
}

unsigned int date::get_miesiac() const {
    return miesiac_;
}

unsigned int date::get_rok() const {
    return rok_;
}

void date::set_data(unsigned int d, unsigned int m, unsigned int r) {
    set_dzien(d, m, r);
    set_miesiac(m);
    set_rok(r);

    if(rok_ == 0 or miesiac_ == 0 or dzien_ == 0)
    {
        rok_ = NULL;
        miesiac_ = NULL;
        dzien_ = NULL;
        std::cout << "Ustawienie daty zakończyło sięnie powodzeniem coś poszło nie tak" << std::endl;
        std::cout << "Zostaniesz piszeniesiony do menu" << std::endl;
        menu() ;
    }

}