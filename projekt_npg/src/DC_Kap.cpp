#include "DC.hpp"
#include <fstream>
#include <iostream>
#include <exception>

std::vector<int> mich = {0,31,28,31,30,31,30,31,31,30,31,30,31};
//Dziennik_cis::~Dziennik_cis() {
//    o_plik_.close();
//    i_plik_.close();
//}
std::string Dziennik_cis::get_sieżka_i_nazwa_pliku() const {
    return sciezka_ + nazwa_pliku_;
}
Dziennik_cis::Dziennik_cis(std::string nazwa_pliku,std::string scieżka)
:nazwa_pliku_(nazwa_pliku)
{
    if(scieżka == ""){
        sciezka_ ="";
    } else {
        sciezka_ = scieżka + "/";
    }
}

int Dziennik_cis::odczytanie_pliku() {
    o_plik_.open(sciezka_ + nazwa_pliku_, std::ios::app);
    if (o_plik_.fail()) {
        o_plik_.close();
        std::cout << "Nie udaoło się otworzyć pliku" << std::endl;
        return 0;
    } else{
        return 1;
    }

}

void Dziennik_cis::tworzenie_pliku() {
    std::ifstream file;
    file.open(sciezka_ + nazwa_pliku_);
    if(file.is_open()){
        std::cout << "Plik o tej nazwie już istnije" << std::endl;
        file.close();
        return;

    } else{
        o_plik_.open(sciezka_ + nazwa_pliku_);
        if (o_plik_.fail()) {
            o_plik_.close();
            std::cout << "Nie udaoło się otworzyć pliku" << std::endl;
            return;
        }
    }
}

void Dziennik_cis::wypisanie_pomiarów(pomiar dane) {
    if (o_plik_.is_open()){
        o_plik_ << dane.get_date().data_str_templet() << "_" << dane.get_wartosc_cts() << "/" << dane.get_wartosc_ctr() << std::endl;
        o_plik_.close();
    } else { std::cout << "plik nie jest otwarty" << std::endl;

    }
}
void komunikat_początek(){
    std::cout << "Applikacja dziennik ciśnieniowca" << std::endl;
    std::cout << "Wpisz do konsoli jeden z podanych numerów, żeby wybrać akcje:" << std::endl;
    std::cout << "1. Otwórz plik" << std::endl;
    std::cout << "2. Stwórz plik" << std::endl;
    std::cout << "3. Zakończ program" << std::endl;

}
void komunikat_akcji_powybraniu_pliku(const Dziennik_cis &D){
    std::cout << "Plik, w którym jesteśmy to \"" << D.get_sieżka_i_nazwa_pliku() << "\"" << std::endl;
    std::cout << "Wpisz do konsoli jeden z podanych numerów, żeby wybrać akcje:" << std::endl;
    std::cout << "1.Wpisz pomiary." << std::endl;
    std::cout << "2.Wyszukaj pomiary." << std::endl;//dzieli na dwa
    std::cout << "3.Wypisz wykres." << std::endl;//dzieli na dwa
    std::cout << "4.Przedź do początkowego menu." << std::endl;
    std::cout << "5.Zakończ program." << std::endl;
}

void menu(){
    komunikat_początek();
    int input;
    std::cin >> input;
    while (not (input == 1 or input == 2 or input == 3)){
        std::cout << "Nie akcji, która pod numer " << input << std::endl;
        std::cin >> input;
    }
    std::cout << std::endl;
    switch (input) {
        case 1: {
            std::cout << "Wpisz nazwę sieżki, w której znajduje się plik, jeżeli jej brak to wpisz 0" << std::endl;
            std::string ścieżka_o;
            std::cin >> ścieżka_o;
            std::cout << "Wpisz nazwę pliku, który chcesz otworzyć" << std::endl;
            std::string nazwa_o;
            std::cin >> nazwa_o;
            Dziennik_cis plik_główny_o = Dziennik_cis(nazwa_o);
            if (plik_główny_o.odczytanie_pliku() == 0) {
                std::cout << "coś poszło nie tak, reset menu";
                menu();
            } else {
                std::cout << "git";
                menu_akcje(plik_główny_o);
            }
            break;
        }
        case 2: {
            std::cout << "Wpisz nazwę sieżki, w której chcesz stworzyć plik, jeżeli jej brak to wpisz \"\"" << std::endl;
            std::string ścieżka_t;
            std::cin >> ścieżka_t;
            std::cout << "Wpisz nazwę pliku, który chcesz stworzyć" << std::endl;
            std::string nazwa_t;
            std::cin >> nazwa_t;
            Dziennik_cis plik_główny_t = Dziennik_cis(nazwa_t, ścieżka_t);
            if (plik_główny_t.odczytanie_pliku() == 0) {
                std::cout << "coś poszło nie tak, reset menu";
                menu();
            } else {
                std::cout << "git";
                menu_akcje(plik_główny_t);
            }
            break;
        }
        case 3:
            return;
            break;
        default:

    }
}

void menu_akcje(Dziennik_cis &D){
    komunikat_akcji_powybraniu_pliku(D);
    int input;
    std::cin >> input;
    while (not (input == 1 or input == 2 or input == 3 or input == 4 or input == 5)){
        std::cout << "Nie akcji, która pod numer " << input << std::endl;
        std::cin >> input;
    }
    std::cout << std::endl;
    switch (input) {
        case 1: {
            std::cout << "Wpisz warotść ciśnienia_tetnicze_skurczowe" << std::endl;
            unsigned int cts;
            std::cin >> cts;
            std::cout << "Wpisz warotść ciśnienia_tetnicze_rozkurczowe" << std::endl;
            unsigned int ctr;
            std::cin >> ctr;
            std::cout << "Wpisz dzień, w którym mierzeni się odbyło" << std::endl;
            unsigned int d;
            std::cin >> d;
            std::cout << "Wpisz miesiąc, w którym mierzeni się odbyło" << std::endl;
            unsigned int m;
            std::cin >> m;
            std::cout << "Wpisz rok, w którym mierzeni się odbyło" << std::endl;
            unsigned int r;
            std::cin >> r;
            date data = date(d, m, r);
            pomiar po = pomiar(cts, ctr, data);
            D.wypisanie_pomiarów(po);
            break;
        }
        case 2: {

            break;
        }
        case 3: {
            int m;
            std::cout << "miesiąc z którego ma powstać wykres" << std::endl;
            std::cin >> m;
            while (not (m == 1 or  m == 2 or m == 3 or  m == 4 or m == 5 or m == 6 or  m == 7 or m == 8 or  m == 9 or m == 10 or  m == 11 or  m == 12)){
                std::cout << "Nie ma mieśąca, o numerze " << m << ".Sprubój jeszcze raz." << std::endl;
                std::cin >> m;
            }
            int r;
            std::cout << "rok z którego ma powstać wykres" << std::endl;
            std::cin >> r;
            while (r < 0){
                std::cout << "Nie ma ujemnego roku.Sprubój jeszcze raz." << std::endl;
                std::cin >> r;
            }
            int typ;
            std::cout << "Wybierz typ wykresu, jeżeli chcesz otrzymać wykres punktowy wpisz 1, jeżli chcesz otrzymać historgram wpisz 2" << std::endl;
            std::cin >> typ;
            while (not (typ == 1 or typ == 2)){
                std::cout << "Nie ma wykesu, która pod numer " << typ << ".Sprubój jeszcze raz." << std::endl;
                std::cin >> typ;
            }

            if(typ == 1){
                unsigned int dzień_ost;
                if(m==2 and (r%400 == 0 or (r%4 ==0 and r%100 != 0))){
                    dzień_ost = 29;
                } else {
                    dzień_ost = mich[m];
                }
                date ds = date(1,m,r);
                date dos = date(21,m,r);

                std::vector<std::vector< int>> pd = pomiary_z_dat(ds, dos,D.get_sieżka_i_nazwa_pliku());
                std::cout << "Dla jakiego rodzaju ciśnienia ma powstać wykres:" << std::endl;
                std::cout << "Jeżeli dla ciśnieni_tetnicze_skurczowe wpisz 1, jeżeli dla ciśnieni_tetnicze_rozkurczowe wpisz 2" << std::endl;
                int typ_w;
                std::cin >> typ_w;
                while (not (typ_w == 1 or typ_w == 2) ){
                    std::cout << "Nie ma opcji, pod numerem " << typ << ".Sprubój jeszcze raz." << std::endl;
                    std::cin >> typ_w;
                }
                if(typ_w == 1) {
                    wykres_promiarow_main(dzień_ost, tworzenie_wykresu(pd,100,40,0));
                } else {
                    wykres_promiarow_main(dzień_ost, tworzenie_wykresu(pd,60,90,1));
                }
            } else {

            }
            break;
        }
        case 4:
            menu();
            break;
        case 5:
            return;
            break;


    }
}
