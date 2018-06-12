#include <iostream>
#include <memory>
#include <forward_list>
#include <functional>
#include <cstring>

#include "../include/Account.h"
#include "../include/hashtbl.h"

/// Classe de testes da HashTable em 3 versões.
int main( void )
{

    // Versão 1
    {

        std::cout << "VERSÃO 01\n" << std::endl;

    	// Cria a tabela
        HashTbl<int, App::Account, App::KeyHash<int>, App::KeyEqual<int>> ht(10);

        // Cria uma conta.

        App::Account acc1(15, "Pablo", 1224, 31732, 21323, 0.0);
        App::Account acc3(11, "Henrique", 32443, 17352, 21323, 1.0);
        App::Account acc4(11, "Selan", 0001, 12321, 1122, 10000000.0);

        // Insere a conta a tabela.
        ht.insert(acc1.conta_, acc1);
        ht.insert(acc3.conta_, acc3);
        ht.insert(acc4.conta_, acc4);
        // Remove a conta da tabela.
        ht.remove(acc1.conta_);
        // Imprime a tabela ( por consequência está vazia pois o único dado inserido foi removido ).
        ht.print();

        // Cria um conta vazia.
        App::Account acc2;
        // Realiza a busca através de uma chave e insere na acc2 se encontrada.
        bool retrieve = ht.retrieve(0, acc2);
        if(retrieve == true)
            std::cout << acc2;
        else
            std::cout << "Não foi possível encontrar!\n";
        ht.clear();

    }

    // Versão 2
    {

        std::cout << "\n\n\nVERSÃO 02\n" << std::endl;

    	// Cria uma nova tabela na qual a chave é o nome do cliente e o número da conta.
        HashTbl<std::pair<std::string, int>, App::Account, App::KeyHash<std::pair<std::string, int>>,
                App::KeyEqual<std::pair<std::string, int>>> ht(10);
        // Cria contas.
        App::Account acc1(0, "Pablo", 1224, 31732, 21323, 0.0);
        App::Account acc2(1, "Henrique", 15434, 36542, 7657, 543643.25);
        App::Account acc3(2, "Selan", 14234, 6452, 654, 999965464664.99);
        // Insere as contas na lista.
        ht.insert(std::make_pair<> (acc1.nome_, acc1.conta_), acc1);
        ht.insert(std::make_pair<> (acc2.nome_, acc2.conta_), acc2);
        ht.insert(std::make_pair<> (acc3.nome_, acc3.conta_), acc3);
        // Remove apenas a conta acc1.
        ht.remove(std::make_pair<> (acc1.nome_, acc1.conta_));
        // Imprime as contas da tabela. 
        ht.print();

        // Retorna a conta acc1, a qual foi apagada, assim não foi encontrada.
        bool retrieve = ht.retrieve(std::make_pair<> (acc1.nome_, acc1.conta_), acc2);
        if(retrieve == true)
            std::cout << acc2;
        else
            std::cout << "Não foi possível encontrar!\n";

        // Ŕecebe a conta acc2.
        retrieve = ht.retrieve(std::make_pair<> (acc2.nome_, acc2.conta_), acc2);
        if(retrieve == true)
            std::cout << acc2;
        else
            std::cout << "Não foi possível encontrar!\n";
    }

    // Versão 3
    {
        std::cout << "\n\n\nVERSÃO 03\n" << std::endl;
        using KeyType = std::tuple<std::string, int, int, int>;
    	// Cria uma nova tabela para armazenar uma hash table com chave sendo o nome do cliente, o banco, a agencia e a conta.
        HashTbl<KeyType, App::Account, App::KeyHash<KeyType>, App::KeyEqual<KeyType>> ht(3);
        // Cria 3 novas contas.
        App::Account acclist[] =
        {
            App::Account(0, "Conta 1", 321, 3732, 213623, 0.0),
            App::Account(1, "Conta 2", 1867, 3652, 7657, 543643.25),
            App::Account(2, "Conta 3", 184, 6437252, 64, 9994.6),
            App::Account(2, "Conta 3", 184, 6437252, 64, 9994.6),
            App::Account(0, "Conta 1", 321, 3732, 213623, 0.0),
            App::Account(4, "Conta 5", 24, 365442, 765877, 9999476.6),
            App::Account(6, "Conta 6", 1434, 645452, 6454, 965464664.99)
        };
        auto size = sizeof(acclist) / sizeof(App::Account);
        for(uint c(0); c < size; ++c)
        {
            ht.insert(std::make_tuple<> (acclist[c].nome_, acclist[c].conta_, acclist[c].banco_, acclist[c].agencia_), acclist[c]);
        }
        // Imprime todas as contas presentes na tabela.
        ht.print();

    }
    return 0;
}
