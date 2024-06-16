//

#ifndef PROJEKT_NPG_DC_HPP
#define PROJEKT_NPG_DC_HPP
#include <vector>
#include <fstream>

#include <iostream>


//git
class date{
public:
    date(int d,int m, int r);
    date() = default;

    void set_dzien(int dzien, int miesiac, int rok); //funkcja musi dostac miesiac oraz rok, żeby sprawdzic poprawność daty
    void set_miesiac(int miesiac);
    void set_rok(int rok);
    void set_data(int d, int m, int r);

     int get_dzien() const;
     int get_miesiac () const;
     int get_rok() const;
    std::string data_str() const;

private:
     int dzien_;
     int miesiac_;
     int rok_;

};

class pomiar{
public:
    //git
    pomiar(int wartosc_cts, int wartosc_ctr, date data);

    //sprawdzić czy jest nie ujemne
    //Git
    void set_wartosc_cts( int wartosc_cts);
    void set_wartosc_ctr( int wartosc_ctr);
    //git
     int get_wartosc_cts() const;
     int get_wartosc_ctr() const;
     date get_date() const;
private:
    // wartosci od 50 do 120
     int ciśnieni_tetnicze_skurczowe;
     int ciśnieni_tetnicze_rozkurczowe;
    date data_;
};


//klasa tworzy obiekt, któremu jest przypisany plik o podanej nazwie i sicezce
class Dziennik_cis{
public:
//git
    Dziennik_cis(std::string nazwa_pliku,std::string scieżka = "");
// czytanie pliku lub tworzenie pliku
//git
    bool sprawdzanie_czy_plik_może_się_otworzyć();

//git
    bool sprawdzenie_czy_nazwa_pliku_jest_zajęta();

    void wpisanie_pomiarów(pomiar dane);

    std::string get_sieżka_i_nazwa_pliku() const;
private:
//sierzka i nazwa czytanego pliku
    std::string sciezka_;
    std::string nazwa_pliku_;
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



//settery trzeba ustawić tak żeby daty były zawsze poprawne

std::vector<std::vector<std::string>> tworzenie_wykresu(std::vector<std::vector< int>> wektor,  int niż_y,  int wyż_y, int typ);

void wykres_promiarow_main(int liczba_dni, const std::vector<std::vector<std::string>> &wykres, int średnia, int max);

std::vector<std::vector< int>> pomiary_z_dat(date data_start, date data_end, std::string nazwa_pliku);
void menu();
void menu_akcje(Dziennik_cis &D);
void error();
date data_plus_jeden(date data);
void dodaj_zera(date data_start, date data_end, std::string plik);
std::vector<int> wyszuk_po_dacie(date data, std::string plik);
int średnia_i_typ(std::vector<std::vector<int>> wektor, int typ);
std::vector<std::vector<std::string>> dominanta(std::vector<std::vector<int>> wektor, int wartość, int typ);
std::vector<date> wyszukiwanie_po_wartości(int wartość, std::string nazwa_pliku, int typ);
#endif //PROJEKT_NPG_DC_HPP
