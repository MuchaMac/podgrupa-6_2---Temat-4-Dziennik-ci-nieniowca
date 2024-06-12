#include "DC.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
date::date( int d,  int m,  int r) {
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


void date::set_dzien( int dzien,  int miesiac,  int rok){
    dzien_ = 0;  // wstępnie ustawia dzien_ na -1, co zostanie zmienione gdy data jest dobrze podana

    if (miesiac >= 1 and miesiac <= 12) { // sprawdza czy miesiąc należy do <1;12>

        if (sprawdzacz_elem_w_kontenerze(mies_31d, miesiac)) {

            if (dzien >= 1 and dzien <= 31) {
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

void date::set_miesiac( int miesiac) {
    miesiac_ = 0;
    if (miesiac >= 1 && miesiac <= 12) {
        miesiac_ = miesiac;
    }
}

void date::set_rok( int rok) {
    rok_ = 0;
    if (rok >= 0){
        rok_ = rok;
    }
}

std::string date::data_str() const {
    std::ostringstream oss;
    oss.fill('0');
    oss << std::setw(2) << dzien_ << ".";
    oss << std::setw(2)  << miesiac_ << "." ;
    oss << std::setw(4)  << rok_;
    return oss.str();
}

 int date::get_dzien() const {
    return dzien_;
}

 int date::get_miesiac() const {
    return miesiac_;
}

 int date::get_rok() const {
    return rok_;
}

void date::set_data( int d,  int m,  int r) {
    set_dzien(d, m, r);
    set_miesiac(m);
    set_rok(r);

    if(rok_ == 0 or miesiac_ == 0 or dzien_ == 0)
    {
        error();
    }

}

void wykres_promiarow_main(int liczba_dni, const std::vector<std::vector<std::string>> &wykres, int średnia, int max) {

    std::cout << "\n    ";
    for(int k = 0; k < liczba_dni / 2; k++){ //wypisywanie słowa wykres oraz średnia dojezdza spacjami do
        std::cout << " ";                          //polowy wykresu i wypisuje, zastosowane to jest dalej kilka razy
    }
    std::cout << "WYKRES\n";

    for(int k = 0; k < liczba_dni / 2; k++){ //wypisywanie słowa srednia
        std::cout << " ";
    }
    std::cout << "SREDNIA = " << średnia; //wrzucić wartość funkcji średnia

    std::cout << "\n~~~~";
    for(int k = 0; k < liczba_dni; k++){ //wypisywanie kreski "~" pod napisem "wykres"
        std::cout << "~";
    }
    std::cout << "~~~~";

    int osy = max; // licznik osi y

    std::cout << "\n   ^\n" << "   |\n"; // wypisywanie "^" oraz piewrszej pionowej "|"


    for (int i = 0; i < wykres.size(); ++i) {
        for (int j = 0; j <= liczba_dni; ++j) {
            if (j == 0) {
                if(osy >= 100) {
                    std::cout << osy << "|"; // wypisywanie osi i pionowej kreski dla wartości trzycyfrowych
                } else if(osy >= 10){
                    std::cout << osy << " |"; // wypisywanie osi i pionowej kreski dla wartosci dwucyfrowych
                } else {
                    std::cout << osy << "  |"; // wypisywanie osi i pionowej kreski dla wartosci jednocyfrowych
                }
            }
            if(max == 90 or max ==140) {
                std::cout << wykres[i][liczba_dni - j];
            } else {
                std::cout << wykres[i][j];
            }
        }
        std::cout << std::endl;
        osy -= 1;
    }

    switch (max) {    //case sprawdza jaki jest wymagany rozmiar wykresu, nie jest ustawiony default, czyli
        case 140:               //jak bedzie cos poza 140 i 90 to da "0  "
            std::cout << "100";
            break;
        case 90:
            std::cout << "60 ";
            break;
        default:
            std::cout << "0  ";
            break;
    }

    for(int k = 0; k <liczba_dni + 4; k++){ //wypisywanie kreski "~" pod napisem "wykres"
        std::cout << "-";
    }
    std::cout << " >\n";
}