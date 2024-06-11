#include "DC.hpp"
#include <fstream>
#include <iostream>
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

std::vector<std::vector<unsigned int>> pomiary_z_dat(date data_start, date data_end, std::string plik){
    std::ifstream otwor(plik);
    date data;
    std::vector<std::vector<unsigned int>> wynik = {};
    std::string temp;
    if (otwor.is_open())
    {
        while(std::getline(otwor, temp)) {
            data = string_to_date(temp);
            if(data_porow(data,data_start)!=2 && data_porow(data,data_end)!=1){
                std::vector<unsigned int> o = { unsigned(std::stoi(temp.substr(temp.find("_")+1))),unsigned(std::stoi(temp.substr(temp.find("/")+1)))};
                wynik.push_back(o);
            }
        }
        otwor.close();
    }
    return wynik;
}

