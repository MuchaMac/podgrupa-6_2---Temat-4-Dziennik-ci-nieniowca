#include "DC"
#include <string>
#include <ostream>
#include <sstream>
#include <vector>



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


void date::set_dzien(int dzien, int miesiac, int rok){
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

void date::set_miesiac(int miesiac) {
    miesiac_ = 0;
    if (miesiac >= 1 && miesiac <= 12) {
        miesiac_ = miesiac;
    }
}

void date::set_rok(int rok) {
    rok_ = 0;
    if (rok >= 1800 && rok <= 2025) {
        rok_ = rok;
    }
}

std::string date::data_str() const {
    std::ostringstream oss;

    oss << dzien_ << ".";
    if(miesiac_ >= 1 && miesiac_ <= 9) {
        oss << "0";
    }
    oss << miesiac_ << "." << rok_;

    return oss.str();
}
