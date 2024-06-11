#include "DC.hpp"
#include <iostream>
void obrot_macierzy(std::vector<std::vector<std::string>> &M){
    std::vector<std::vector<std::string>> temp(M[1].size(),std::vector<std::string>((M).size()));
    for (int i = 0; i != M.size(); ++i) {
        for (int j = 0; j != (M[1]).size(); ++j) {
            temp[j][(M).size()-i-1] = M[i][j];
        }
    }
    M = temp;
}

pomiar::pomiar(unsigned int wartosc_cts,unsigned int wartosc_ctr, date data)
        :data_(data)
{
    set_wartosc_cts(wartosc_cts);
    set_wartosc_ctr(wartosc_ctr);
}

void pomiar::set_wartosc_cts(unsigned int wartosc_cts) {
    if(wartosc_cts >= 0){
        ciśnieni_tetnicze_skurczowe = wartosc_cts;
    } else {
        std::cout << "Wartość, którą próbujsz dodać jest ujemna";
    }
}
void pomiar::set_wartosc_ctr(unsigned int wartosc_ctr) {
    if(wartosc_ctr >= 0){
        ciśnieni_tetnicze_rozkurczowe = wartosc_ctr;
    } else {
        std::cout << "Wartość, którą próbujsz dodać jest ujemna";
    }
}

unsigned int pomiar::get_wartosc_cts() const {
    return ciśnieni_tetnicze_skurczowe;
}
unsigned int pomiar::get_wartosc_ctr() const {
    return ciśnieni_tetnicze_rozkurczowe;
}

date pomiar::get_date() const {
    return data_;
}
std::vector<std::vector<std::string>> tworzenie_wykresu(std::vector<std::vector<unsigned int>> wektor, unsigned int niż_y, unsigned int wyż_y, int typ){
    std::vector<std::vector<std::string>> wykres(wektor.size(),std::vector<std::string>(wyż_y-niż_y));
    for (int i = 0; i != wektor.size() ; ++i) {
        for (unsigned int j = 0; j != wyż_y - wektor[i][typ] ; ++j) {
            wykres[i][j] = ".";
        }
        for (unsigned int j = wyż_y - wektor[i][typ]; j != wyż_y - niż_y ; ++j) {
            wykres[i][j] = "@";
        }
    }
    obrot_macierzy(wykres);
    return wykres;
}
void wykres_promiarow_main(unsigned int liczba_dni, std::vector<std::vector<std::string>> wykres){
    for (int i = 0; i != wykres.size(); ++i) {
        for (int j = 0; j != wykres[1].size() ; ++j) {
            std::cout << wykres[i][j];
        } std::cout << std::endl;
    }
}
