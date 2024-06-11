#include <bit/stdc++.h>
//klasa tworzy obiekt, któremu jest przypisany plik o podanej nazwie i sicezce
class Dziennik_cis{
public:
    Dziennik_cis();
// czytanie pliku lub tworzenie pliku
    void odczytanie_pliku();
    void tworzenie_pliku();
//wyszukiwanie pomiarów po dacie i pomiarze (przciąrzenie)
    // data to wektor, który składa sie z trzech wartosc <dd,mm,yyyy> np.<05,05,2024> piąty maj 2024(potrzebny będzie warunek na to czy wektor poprawieni okresia date)
    void wyszukiwanie(date data);
    void wyszukiwanie(int wartosc);

    //wyszukiwanie po dacie i wartosci
    std::vector<std::string> wyszukiwanie(date data);
    std::vector<std::int> wyszukiwanie(int wartosc);
    
    //wypisanie wartości w main
    void wypisanie_pomiarów();
    // wykres zaczyna się od 800 do 1100
    //funkcjia wypisująca wykres danego pliku na podstawie wybranego miesiąca
    void wykres_promiarow_main(int miesiac);
    //funkcjia tworzy plik txt z wykres danego pliku na podstawie wybranego miesiąca
    void wykres_promiarow_tworzenie_pliku(int miesiac);
    //funkcja tworzac miacierz, która pozniej bedzie urzyta w funkcji wykresu pomiarow
    std::vector<std::vector<std::string>> tworzenie_macierzy_wykresu();
    
    //wczytwanie i zapisywanie pomiarów.
    void wczytywanie();
    void zapisywanie();
    
private:
//sierzka i nazwa czytanego pliku
    std::string sciezka;
    std::string nazwa_pliku;
    
}

//funkcja obracajaca macierz wykresu która pozniej bedzie urzyta w funkcji wykresu pomiarow
void obrot_macierzy(std::vector<std::vector<std::string>> & M);
//komunikat na poczatku, ktory mowi co urzytkownik moze zrobic
void komunikat();


class pomiar{
public:
    pomiar(unsigned int wartosc, date data)
    : , date_(date)
    {set_wartosc(wartosc)};
    //sprawdzić czy jest nie ujemna
    void set_wartosc(unsigned int wartosc);
    
    unsigned int get_wartosc() const;
private:
    // wartosci od 800 do 1100
    int wartosc_
    date data_;
}

class date{
public:
    date(int d,int m, int r){
        set_dzien(d, m, r);
        set_miesiac(m);
        set_rok(r);

    };

    unsigned int get_dzien() const { return dzien_; }
    unsigned int get_miesiac () const { return miesiac_; }
    unsigned int get_rok() const { return rok_; }

    void set_dzien(int dzien, int miesiac, int rok); //funkcja musi dostac miesiac oraz rok, żeby sprawdzic poprawność daty
    void set_miesiac(int miesiac);
    void set_rok(int rok);

    std::string data_str() const;


private:
    unsigned int dzien_;
    unsigned int miesiac_;
    unsigned int rok_;

};
