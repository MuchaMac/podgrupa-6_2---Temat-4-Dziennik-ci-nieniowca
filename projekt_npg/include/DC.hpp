//

#ifndef PROJEKT_NPG_DC_HPP
#define PROJEKT_NPG_DC_HPP
#include <vector>
#include <fstream>


//git
class date{
public:
    date(unsigned int d,unsigned int m, unsigned int r);
    date() = default;

    void set_dzien(unsigned int dzien, unsigned int miesiac, unsigned int rok); //funkcja musi dostac miesiac oraz rok, żeby sprawdzic poprawność daty
    void set_miesiac(unsigned int miesiac);
    void set_rok(unsigned int rok);
    void set_data(unsigned int d, unsigned int m, unsigned int r);

    unsigned int get_dzien() const;
    unsigned int get_miesiac () const;
    unsigned int get_rok() const;
    std::string data_str_templet() const;


private:
    unsigned int dzien_;
    unsigned int miesiac_;
    unsigned int rok_;

};

class pomiar{
public:
    //git
    pomiar(unsigned int wartosc_cts,unsigned int wartosc_ctr, date data);

    //sprawdzić czy jest nie ujemne
    //Git
    void set_wartosc_cts(unsigned int wartosc_cts);
    void set_wartosc_ctr(unsigned int wartosc_ctr);
    //git
    unsigned int get_wartosc_cts() const;
    unsigned int get_wartosc_ctr() const;
    date get_date() const;
private:
    // wartosci od 50 do 120
    unsigned int ciśnieni_tetnicze_skurczowe;
    unsigned int ciśnieni_tetnicze_rozkurczowe;
    date data_;
};


//klasa tworzy obiekt, któremu jest przypisany plik o podanej nazwie i sicezce
class Dziennik_cis{
public:
//git
    Dziennik_cis(std::string nazwa_pliku,std::string scieżka = "");
// czytanie pliku lub tworzenie pliku
//    ~Dziennik_cis();

//git
    int odczytanie_pliku();

//git
    void tworzenie_pliku();


    //wyszukiwanie po dacie i wartosci
    std::vector<std::string> wyszukiwanie_date(date data);
    std::vector<unsigned int> wyszukiwanie_wartość(unsigned int wartosc);

    //wypisanie wartości w main

    void wypisanie_pomiarów(pomiar dane) ;

    // wykres zaczyna się od 800 do 1100
    //funkcjia wypisująca wykres danego pliku na podstawie wybranego miesiąca

    //funkcjia tworzy plik txt z wykres danego pliku na podstawie wybranego miesiąca
    void wykres_promiarow_tworzenie_pliku(unsigned int miesiac);

    //funkcja tworzac miacierz, która pozniej bedzie urzyta w funkcji wykresu pomiarow
    std::vector<std::vector<std::string>> tworzenie_macierzy_wykresu();

    //wczytwanie i zapisywanie pomiarów.
    void wczytywanie();
    void zapisywanie();
    std::string get_sieżka_i_nazwa_pliku() const;

private:
//sierzka i nazwa czytanego pliku
    std::string sciezka_;
    std::string nazwa_pliku_;
    std::ofstream o_plik_;
    std::ifstream i_plik_;

};
date string_to_date(std::string data);
//Git
//pierwszy wymiar określia liczba wierszy
//funkcja obracajaca macierz wykresu która pozniej bedzie urzyta w funkcji wykresu pomiarow
void obrot_macierzy(std::vector<std::vector<std::string>> & M);

//komunikat na poczatku, ktory mowi co urzytkownik moze zrobic
void komunikat_początek();

void komunikat_akcji_powybraniu_pliku(const Dziennik_cis &D);

int data_porow(date data1, date data2);

std::vector<std::vector<unsigned int>> pomiary_z_dat(date data_start, date data_end, std::string plik);

//settery trzeba ustawić tak żeby daty były zawsze poprawne

std::vector<std::vector<std::string>> tworzenie_wykresu(std::vector<std::vector<unsigned int>> wektor, unsigned int niż_y, unsigned int wyż_y, int typ);

void wykres_promiarow_main(unsigned int liczba_dni, std::vector<std::vector<std::string>> wy);

void menu();
void menu_akcje(Dziennik_cis &D);

#endif //PROJEKT_NPG_DC_HPP
