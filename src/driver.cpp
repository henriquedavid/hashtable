#include <iostream>
#include <memory>
#include <forward_list>
#include <functional>

#include "../include/Account.h"
#include "../include/hashtbl.h"

int main( void )
{

    // Versão 1
    {
        HashTbl<int, App::Account, std::hash<int>, App::KeyEqual<int>> ht(10);
        App::Account acc1(15, "Pablo", 1224, 31732, 21323, 0.0);
        ht.insert(acc1.conta_, acc1);
        ht.remove(acc1.conta_);
        ht.print();


        App::Account acc2;
        bool retrieve = ht.retrieve(0, acc2);
        if(retrieve == true)
            acc2.print();
        else
            std::cout << "Não foi possível encontrar!\n";
    }

    return 0;
}
