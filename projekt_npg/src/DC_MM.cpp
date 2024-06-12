#include "DC.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
int data_porow(date data1, date data2){ //zwraca 1 jak data1 jest póżniej, 2 jak data2 jest później, i 0 jak to ten sam dzień
    if(data1.get_rok() > data2.get_rok()){
        return 1;
    }
    if(data1.get_rok() < data2.get_rok()){
        return 2;
    }
    if(data1.get_miesiac() > data2.get_miesiac()){
        return 1;
    }
    if(data1.get_miesiac() < data2.get_miesiac()){
        return 2;
    }
    if(data1.get_dzien() > data2.get_dzien()){
        return 1;
    }
    if(data1.get_dzien() < data2.get_dzien()){
        return 2;
    }
    return 0;
}
date string_to_date(std::string data){ //zmienia string postaci xx.xx.xxxx na klase data
    date wynik(stoi(data.substr(0,2)), stoi(data.substr(3,2)),stoi(data.substr(6,4)));
    return wynik;
}

std::vector<std::vector<int>> pomiary_z_dat(date data_start, date data_end, std::string nazwa_pliku){
    std::ifstream czytany_plik(nazwa_pliku);
    date data;
    std::vector<std::vector<int>> wynik = {};
    std::string temp;
    if (czytany_plik.is_open())
    {
        while(std::getline(czytany_plik, temp)) {
            data = string_to_date(temp);
            if(data_porow(data,data_start)!=2 && data_porow(data,data_end)!=1){

                std::vector<int> o = { (std::stoi(temp.substr(temp.find("_")+1))),(std::stoi(temp.substr(temp.find("/")+1)))};
                wynik.push_back(o);

            }
        }
        czytany_plik.close();
        return wynik;
    } else {
        std::cout << "Plik się nie odworzył" << std::endl;
        error();
    }
}

date data_plus_jeden(date data){
    date data_temp;
    data_temp.set_dzien(data.get_dzien() + 1, data.get_miesiac(), data.get_rok());
    if(data_temp.get_dzien() != 0 ){
        data_temp.set_miesiac(data.get_miesiac());
        data_temp.set_rok(data.get_rok());
        return data_temp;
    }
    if(data.get_miesiac() != 12){
        data_temp.set_dzien(1, data.get_miesiac() + 1, data.get_rok());
        data_temp.set_miesiac(data.get_miesiac() + 1);
        data_temp.set_rok(data.get_rok());
        return data_temp;
    }
    data_temp.set_dzien(1, 1, data.get_rok() + 1);
    data_temp.set_miesiac(1);
    data_temp.set_rok(data.get_rok() + 1);
    return data_temp;
}
void dodaj_zera(date data_start, date data_end, std::string plik){
    std::ifstream otwor(plik,std::ios::app);
    date data;
    std::vector<std::string> temp_plik = {};
    std::string temp;
    std::ostringstream oss;
    int poz = 0;
    bool c = 1;
    int poz2;
    if (otwor.is_open())
    {
        while(std::getline(otwor, temp)) {
            temp_plik.push_back(temp);
        }
        otwor.close();
    }
    date data_s = data_start;
    for(auto& el : temp_plik){
        data = string_to_date(el.substr(0,10));
        if(data_porow(data,data_start) == 0){
            c=0;
            break;
        }
        if(data_porow(data,data_s) == 1){
            oss<<data_start.data_str()<<"_0/0";
            temp_plik.insert(temp_plik.begin() + poz, oss.str());
            c=0;
            break;
        }
        poz+=1;
    }
    if(c==1){
        oss<<data_start.data_str()<<"_0/0";
        temp_plik.insert(temp_plik.begin() + poz, oss.str());
    }
    temp = oss.str();
    oss.str("");
    oss.clear();
    while(data_porow(data_s,data_end) != 0){
        c=true;
        poz=0;
        for(auto& el : temp_plik){
            data = string_to_date(el.substr(0,10));
            if(data_porow(data,data_s) == 0){
                c= false;
                break;
            }
            if(el.substr(0,10) == temp.substr(0,10)){
                poz2 = poz;
            }
            poz+=1;
        }
        if(c){
            temp_plik.insert(temp_plik.begin() + poz2 + 1,(data_s).data_str()+"_0/0");
        }
        temp = data_s.data_str() + "_0/0";
        data_s = data_plus_jeden(data_s);
    }
    std::ofstream wynik(plik);
    for(auto& el : temp_plik){
        wynik<<el;
        wynik<<'\n';
    }
    wynik.close();
}
std::vector<int> wyszuk_po_dacie(date data, std::string plik){ // zwraca wartość jeśli data jest w pliku, zwraca 0 jak nie ma
    std::vector<std::vector<int>> wynik = pomiary_z_dat(data, data_plus_jeden(data),plik);
    if(wynik.size() == 0){
        std::cout << "Pod tą datą nie ma, żadnej wartości" << std::endl;
        error();
    }
    return wynik[0];
}


