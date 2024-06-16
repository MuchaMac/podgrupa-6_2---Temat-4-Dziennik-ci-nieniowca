#include "DC.hpp"
#include <fstream>
#include <iostream>

std::vector<int> mich = {0,31,28,31,30,31,30,31,31,30,31,30,31};

std::string Dziennik_cis::get_sieżka_i_nazwa_pliku() const {
    return sciezka_ + nazwa_pliku_;
}
Dziennik_cis::Dziennik_cis(std::string nazwa_pliku,std::string scieżka)
:nazwa_pliku_(nazwa_pliku)
{
    if(scieżka == "\"\""){
        sciezka_ = "";
    } else {
        sciezka_ = scieżka + "/";
    }
}

bool Dziennik_cis::sprawdzanie_czy_plik_może_się_otworzyć() {
    std::ofstream plik(sciezka_ + nazwa_pliku_,std::ios::app);
    if (plik.fail()) {
        std::cout << "Nie udało się otworzyć pliku" << std::endl;
        return false;
    }
    plik.close();
    return true;
}

bool Dziennik_cis::sprawdzenie_czy_nazwa_pliku_jest_zajęta() {
    std::ifstream file;
    file.open(sciezka_ + nazwa_pliku_, std::ifstream::in);
    if(file.is_open()){
        std::cout << "Plik o tej nazwie już istnije" << std::endl;
        file.close();
        return false;
    }
    return true;
}

void Dziennik_cis::wpisanie_pomiarów(pomiar dane) {
    std::ofstream plik(sciezka_ + nazwa_pliku_, std::ios::app);
    if (plik.is_open()){
        plik << dane.get_date().data_str() << "_" << dane.get_wartosc_cts() << "/" << dane.get_wartosc_ctr() << std::endl;
        plik.close();
        std::cout << "Wpisanie pomiaru powiodło się powrót do menu.";
        menu();
    } else {
        std::cout << "Plik nie jest otwarty" << std::endl;
        menu();
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
            std::cout << "Wpisz nazwę sieżki, w której znajduje się plik, jeżeli jej brak to wpisz \"\"" << std::endl;
            std::string ścieżka_o;
            std::cin >> ścieżka_o;
            std::cout << "Wpisz nazwę pliku, który chcesz otworzyć" << std::endl;
            std::string nazwa_o;
            std::cin >> nazwa_o;
            Dziennik_cis plik_główny_o = Dziennik_cis(nazwa_o,ścieżka_o);
            if(plik_główny_o.sprawdzanie_czy_plik_może_się_otworzyć()){
                menu_akcje(plik_główny_o);
            } else {
                std::cout << "Pliku nie da się otworzyć" << std::endl << std::endl;
                std::cout << "Przekierowywuje do menu" << std::endl;
                menu();
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
            if(plik_główny_t.sprawdzenie_czy_nazwa_pliku_jest_zajęta()){
                std::ofstream tworzenie_pliku(plik_główny_t.get_sieżka_i_nazwa_pliku());
                tworzenie_pliku.close();
                menu_akcje(plik_główny_t);
            } else {
                std::cout << "Przekierowywuje do menu" << std::endl;
                menu();
            }
            break;
        }
        case 3:
            return;
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
            int cts;
            std::cin >> cts;
            while ( not(cts > 100 and cts <= 140)) {
                std::cout << "ciśnienia_tetnicze_skurczowe nie może mieć wartość " << cts << " spróbuj jeszcze raz."<< std::endl;
                std::cin >> cts;
            }
            std::cout << "Wpisz warotść ciśnienia_tetnicze_rozkurczowe" << std::endl;
            int ctr;
            std::cin >> ctr;
            while ( not( ctr > 60 and ctr <= 90)) {
                std::cout << "ciśnienia_tetnicze_rozkurczowe nie może mieć wartość " << ctr << " spróbuj jeszcze raz."<< std::endl;
                std::cin >> ctr;
            }
            std::cout << "Wpisz dzień, w którym mierzeni się odbyło" << std::endl;
            int d;
            std::cin >> d;
            std::cout << "Wpisz miesiąc, w którym mierzeni się odbyło" << std::endl;
            int m;
            std::cin >> m;
            std::cout << "Wpisz rok, w którym mierzeni się odbyło" << std::endl;
            int r;
            std::cin >> r;
            date stworzona_data = date(d, m, r);
            pomiar stworzony_pomiar = pomiar(cts, ctr, stworzona_data);
            D.wpisanie_pomiarów(stworzony_pomiar);
            break;
        }
        case 2: {
            std::cout << "Wpisz 1 jeżeli chcesz wyszukiwać po dacie, wpisz 2 jeżeli chcesz wyszukiwać po wartości" << std::endl;
            int input;
            std::cin >> input;
            while (not (input == 1 or input == 2)){
                std::cout << "Nie akcji, która pod numer " << input << std::endl;
                std::cin >> input;
            }
            if(input == 1){
                std::cout << "Wpisz dzień, w którym mierzeni się odbyło" << std::endl;
                int d;
                std::cin >> d;
                std::cout << "Wpisz miesiąc, w którym mierzeni się odbyło" << std::endl;
                int m;
                std::cin >> m;
                std::cout << "Wpisz rok, w którym mierzeni się odbyło" << std::endl;
                int r;
                std::cin >> r;
                std::vector<int> wektro = wyszuk_po_dacie(date(d,m,r), D.get_sieżka_i_nazwa_pliku());
                if(wektro.empty()){

                } else {
                    std::cout << "Wartość ciśnienia tetnicze skurczowe to: " << wektro[0]
                              << ", a wartość ciśnienia tetnicze rozkurczowe to:" << wektro[1] << std::endl;
                }
                std::cout << "Przekierowywuje do menu" << std::endl;
                menu();
            } else{
                std::cout << "Wpisz wartość, która ma odpowiadać coś po dacie" << std::endl;
                int szukana_wartość;
                std::cin >> szukana_wartość;
                std::cout << "Wpisz 1 jeżeli chcesz szukać po wartościach ciśnienia tetnicze skurczowe, wpisz 2 jeżeli chcesz szukać po wartościach ciśnienia tetnicze rozkurczowe" << std::endl;
                int typ;
                std::cin >> typ;
                while (not (typ == 1 or typ == 2)){
                    std::cout << "Nie ma wykesu, która pod numer " << typ << ".Sprubój jeszcze raz." << std::endl;
                    std::cin >> typ;
                }
                std::vector<date> vec_data = wyszukiwanie_po_wartości(szukana_wartość, D.get_sieżka_i_nazwa_pliku(), typ - 1);
                if(vec_data.empty()){
                    std::cout << "Nie ma takich wartości w tym pliku" << std::endl;
                    std::cout << "Przekierowywuje do menu" << std::endl;
                    menu();
                } else {
                    std::cout << "Daty z wybraną wartością to:" << std::endl;
                    for (auto ele: vec_data) {
                        std::cout << ele.data_str() << std::endl;
                    }
                    std::cout << "Przekierowywuje do menu" << std::endl;
                    menu();
                }
            }
            break;
        }
        case 3: {
            int m;
            std::cout << "Miesiąc z którego ma powstać wykres" << std::endl;
            std::cin >> m;
            while (not (m == 1 or  m == 2 or m == 3 or  m == 4 or m == 5 or m == 6 or  m == 7 or m == 8 or  m == 9 or m == 10 or  m == 11 or  m == 12)){
                std::cout << "Nie ma mieśąca, o numerze " << m << ".Sprubój jeszcze raz." << std::endl;
                std::cin >> m;
            }
            int r;
            std::cout << "Rok z którego ma powstać wykres" << std::endl;
            std::cin >> r;
            while (r < 0){
                std::cout << "Nie ma ujemnego roku.Sprubój jeszcze raz." << std::endl;
                std::cin >> r;
            }
            int typ;
            std::cout << "Wybierz typ wykresu, jeżeli chcesz otrzymać wykres punktowy wpisz 1, jeżli chcesz otrzymać dominante wpisz 2" << std::endl;
            std::cin >> typ;
            while (not (typ == 1 or typ == 2)){
                std::cout << "Nie ma wykesu, która pod numer " << typ << ".Sprubój jeszcze raz." << std::endl;
                std::cin >> typ;
            }
            if(typ == 1){
                int dzień_ost;
                if(m==2 and (r%400 == 0 or (r%4 ==0 and r%100 != 0))){
                    dzień_ost = 29;
                } else {
                    dzień_ost = mich[m];
                }
                date date_start = date(1, m, r);
                date date_last = date(dzień_ost, m, r);
                std::vector<std::vector<int>> wektor_z_liczbami_pomiarów= pomiary_z_dat(date_start, date_last, D.get_sieżka_i_nazwa_pliku());
                std::cout << "Dla jakiego rodzaju ciśnienia ma powstać wykres:" << std::endl;
                std::cout << "Jeżeli dla ciśnieni_tetnicze_skurczowe wpisz 1, jeżeli dla ciśnieni_tetnicze_rozkurczowe wpisz 2" << std::endl;
                int typ_w;
                std::cin >> typ_w;
                while (not (typ_w == 1 or typ_w == 2) ){
                    std::cout << "Nie ma opcji, pod numerem " << typ << ".Sprubój jeszcze raz." << std::endl;
                    std::cin >> typ_w;
                }
                if(typ_w == 1) {
                    std::vector<std::vector<std::string>> wykres = tworzenie_wykresu(wektor_z_liczbami_pomiarów, 100, 140, 0);
                    wykres_promiarow_main(dzień_ost, wykres, średnia_i_typ(wektor_z_liczbami_pomiarów,0), 140);
                } else {
                    std::vector<std::vector<std::string>> wykres = tworzenie_wykresu(wektor_z_liczbami_pomiarów, 60, 90,1);
                    wykres_promiarow_main(dzień_ost, wykres, średnia_i_typ(wektor_z_liczbami_pomiarów, 1),90);
                }
            } else if(typ == 2) {
                int dzień_ost;
                if(m==2 and (r%400 == 0 or (r%4 ==0 and r%100 != 0))){
                    dzień_ost = 29;
                } else {
                    dzień_ost = mich[m];
                }
                date date_start = date(1, m, r);
                date date_last = date(dzień_ost, m, r);
                std::vector<std::vector<int>> wektor_z_liczbami_pomiarów= pomiary_z_dat(date_start, date_last, D.get_sieżka_i_nazwa_pliku());
                std::cout << "Dla jakiego rodzaju ciśnienia ma powstać wykres:" << std::endl;
                std::cout << "Jeżeli dla ciśnieni_tetnicze_skurczowe wpisz 1, jeżeli dla ciśnieni_tetnicze_rozkurczowe wpisz 2" << std::endl;
                int typ_w;
                std::cin >> typ_w;
                while (not (typ_w == 1 or typ_w == 2) ){
                    std::cout << "Nie ma opcji, pod numerem " << typ << ".Sprubój jeszcze raz." << std::endl;
                    std::cin >> typ_w;
                }
                if(typ_w == 1) {
                    std::cout << "Dominanta dla ciśnieni_tetnicze_skurczowe" << std::endl;
                    std::vector<std::vector<std::string>> wykres = dominanta(wektor_z_liczbami_pomiarów, 40, 0);
                    wykres_promiarow_main(dzień_ost, wykres, średnia_i_typ(wektor_z_liczbami_pomiarów,0), 40);
                } else {
                    std::cout << "Domianta dla ciśnieni_tetnicze_rozkurczowe" << std::endl;
                    std::vector<std::vector<std::string>> wykres = dominanta(wektor_z_liczbami_pomiarów, 30,1);
                    wykres_promiarow_main(dzień_ost, wykres, średnia_i_typ(wektor_z_liczbami_pomiarów, 1),31);
                }
            }
            break;
        }
        case 4:
            menu();
            break;
        case 5:
            return;


    }
}

int średnia_i_typ(std::vector<std::vector<int>> wektor, int typ){
    int warotść = 0;
    for (auto ele: wektor) {
        warotść += ele[typ];
    }
    return warotść/wektor.size();
}

std::vector<std::vector<std::string>> dominanta(std::vector<std::vector<int>> wektor, int wartość, int typ){
    std::vector<int> wektor_ile_razy(wartość);
    for (int i = 0; i != wektor.size() ; ++i) {
        if (typ == 0) {
            wektor_ile_razy[wektor[i][typ] - 100] = wektor_ile_razy[wektor[i][typ] - 100] + 1;
        } else {
            wektor_ile_razy[wektor[i][typ] - 60] = wektor_ile_razy[wektor[i][typ] - 60] + 1;

        }
    }
    std::vector<std::vector<std::string>> wykres(wartość,std::vector<std::string>(wartość));
    for (int i = 0; i != wartość ; ++i) {
        for (int j = 0; j != wartość - wektor_ile_razy[wartość - 1] + 1; ++j) {
            wykres[i][j] = ".";
        }
        for (int j = wartość - wektor_ile_razy[wartość - i]; j != wartość ; ++j) {
            wykres[i][j] = "@";
        }
    }
    obrot_macierzy(wykres);
    return wykres;
}

void error() {
    try{
        throw(std::invalid_argument("Zrobiłeś błąd T_T"));
    }
    catch (std::invalid_argument ans){
        std::cout << ans.what() << std::endl;
    }
}

std::vector<date> wyszukiwanie_po_wartości(int wartość, std::string nazwa_pliku, int typ){
    std::ifstream czytany_plik(nazwa_pliku);
    std::vector<date> zwracany_wektor = {};
    std::string temp;
    date data;
    std::vector<int> temp_vec_int = {};
    if (czytany_plik.is_open())
    {
        while(std::getline(czytany_plik, temp)) {
            data = string_to_date(temp);
            temp_vec_int = { (std::stoi(temp.substr(temp.find("_")+1))),(std::stoi(temp.substr(temp.find("/")+1)))};
            if(temp_vec_int[typ] == wartość){
                zwracany_wektor.push_back(data);
            }
        }
        czytany_plik.close();
        return zwracany_wektor;
    } else {
        std::cout << "Plik się nie odworzył" << std::endl;
        error();
    }
}


