#include <iostream>
#include <memory>
#include <forward_list>
#include <functional>

#include "Account.h"
#include "hashtbl.h"

/// \note: Hash entry é desconhecido para o cliente
int main( void )
{


	// Versão 1
	{	
        HashTbl<int, App::Account, std::hash<int>, App::KeyEqual<int>> ht(10);
        App::Account acc1(15, "Pablo", 1224, 31732, 21323, 0.0);
        ht.insert(acc1.conta_, acc1);
        ht.remove(acc1.conta_);
        ht.print();
	}	

	// Versão 2
	{

	}

	// Versão 3
	{

	}
	
	
	return 0;
}
