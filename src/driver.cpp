#include <iostream>
#include <memory>
#include <forward_list>
#include <functional>
#include <cstring>

#include "../include/Account.h"
#include "../include/hashtbl.h"

int main( void )
{

    // Versão 1
    {
        HashTbl<int, App::Account, App::KeyHash<int>, App::KeyEqual<int>> ht(10);
        App::Account acc1(15, "Pablo", 1224, 31732, 21323, 0.0);
        ht.insert(acc1.conta_, acc1);
        ht.remove(acc1.conta_);
        ht.print();


        App::Account acc2;
        bool retrieve = ht.retrieve(0, acc2);
        if(retrieve == true)
            std::cout << acc2;
        else
            std::cout << "Não foi possível encontrar!\n";
    }
    // Versão 2
    {
        HashTbl<std::pair<std::string, int>, App::Account, App::KeyHash<std::pair<std::string, int>>,
                App::KeyEqual<std::pair<std::string, int>>> ht(10);
        App::Account acc1(0, "Pablo", 1224, 31732, 21323, 0.0);
        App::Account acc2(1, "Henrique", 15434, 36542, 7657, 543643.25);
        App::Account acc3(2, "Selan", 14234, 6452, 654, 999965464664.99);
        ht.insert(std::make_pair<> (acc1.nome_, acc1.conta_), acc1);
        ht.insert(std::make_pair<> (acc2.nome_, acc2.conta_), acc2);
        ht.insert(std::make_pair<> (acc3.nome_, acc3.conta_), acc3);
        ht.remove(std::make_pair<> (acc1.nome_, acc1.conta_));
        ht.print();

        bool retrieve = ht.retrieve(std::make_pair<> (acc1.nome_, acc1.conta_), acc2);
        if(retrieve == true)
            std::cout << acc2;
        else
            std::cout << "Não foi possível encontrar!\n";

        retrieve = ht.retrieve(std::make_pair<> (acc2.nome_, acc2.conta_), acc2);
        if(retrieve == true)
            std::cout << acc2;
        else
            std::cout << "Não foi possível encontrar!\n";
    }
    // Versão 3
    {
        using KeyType = std::tuple<std::string, int, int, int>;
        HashTbl<KeyType, App::Account, App::KeyHash<KeyType>, App::KeyEqual<KeyType>> ht(3);
        App::Account acc1(0, "Pablo", 1224, 31732, 21323, 0.0);
        App::Account acc2(1, "Henrique", 15434, 36542, 7657, 543643.25);
        App::Account acc3(2, "Selan", 14234, 6452, 654, 999965464664.99);
        ht.insert(std::make_tuple<> (acc1.nome_, acc1.conta_, acc1.banco_, acc1.agencia_), acc1);
        ht.insert(std::make_tuple<> (acc2.nome_, acc2.conta_, acc2.banco_, acc2.agencia_), acc2);
        ht.insert(std::make_tuple<> (acc3.nome_, acc3.conta_, acc3.banco_, acc3.agencia_), acc3);

        ht.print();

    }
    return 0;
}
