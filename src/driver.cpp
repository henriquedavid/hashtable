#include <iostream>
#include <memory>
#include <forward_list>
#include <functional>

#include "Account.h"
#include "hashtbl.h"

/// \note: Hash entry é desconhecido para o cliente
int main( void )
{

    HashTbl<int, App::Account, App::KeyHash<int>, App::KeyEqual<int>> ht(10);
    App::Account acc1(0, "Pablo", 122, 33232, 21323, 0.0);
    ht.insert(0, acc1);
	// Versão 1
	{	

	}	

	// Versão 2
	{

	}

	// Versão 3
	{

	}
	
	
	return 0;
}
