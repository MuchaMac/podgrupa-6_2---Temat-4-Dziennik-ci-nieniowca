#include <string>
#include <vector>
#include <map>
//klasa tworzy obiekt, któremu jest przypisany plik o podanej nazwie i sicezce
class Dziennik_cis{
public:
    Dziennik_cis();
// czytanie pliku lub tworzenie pliku
    void odczytanie_pliku();
    void tworzenie_pliku();
//wypisanie wartości w main
    void wypisanie_pomiarów();
//wyszukiwanie pomiarów po dacie i pomiarze (przciąrzenie)
    // data to wektor, który składa sie z trzech wartosc <dd,mm,yyyy> np.<05,05,2024> piąty maj 2024(potrzebny będzie warunek na to czy wektor poprawieni okresia date)
    void wyszukiwanie(date data);
    void wyszukiwanie(int wartosc);
    //wers
    std::vector<std::string> wyszukiwanie(date data);
    std::vector<std::int> wyszukiwanie(int wartosc);

//funkcjia wypisująca wykres danego pliku na podstawie wybranego miesiąca
    void wykres_promiarow_main(int miesiac);
    //funkcjia tworzy plik txt z wykres danego pliku na podstawie wybranego miesiąca
    void wykres_promiarow_tworzenie_pliku(int miesiac);
    
private:
//sierzka i nazwa czytanego pliku
    std::string sciezka;
    std::string nazwa_pliku;
    
}
//funkcja tworzac miacierz, która pozniej bedzie urzyta w funkcji wykresu pomiarow
std::vector<std::vector<std::string>> tworzenie_macierzy_wykresu();
//funkcja obracajaca macierz wykresu która pozniej bedzie urzyta w funkcji wykresu pomiarow
void obrot_macierzy(std::vector<std::vector<std::string>> & M);
//komunikat na poczatku, ktory mowi co urzytkownik moze zrobic
void komunikat();


class pomiar{
public:
    pomiar(int wartosc, date data)
    : wartosc_(set_wartosc(wartosc)), date_(date)
    {};
    //sprawdzić czy jest nie ujemna
    int set_wartosc(int wartosc);
private:
    int wartosc_
    date data_;
}

class date{
public:
    date(int d,int m, int r){
    };
    
    int set_dzien(int dzien);
    int set_miesiac(int dzien);
    int set_rok(int rok);
    
private:
    int dzien_;
    int miesiac_;
    int rok_;
    
}
