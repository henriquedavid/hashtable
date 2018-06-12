# Hash Table
O projeto é uma tabela de dispersão para armazenar contas correntes. A utilização da chave é dividida em 3 versões.
- A primeira versão é uma chave composta por um inteiro correspondente ao número da conta corrente.
- A segunda versão é uma chave composta pelo nome do cliente e o número da conta.
- A terceira versão é uma chave composta pelo nome do cliente, o código do banco, o número da agência e o número da conta.

Todas as versões estão separadas no arquivo presente na pasta src, driver.cpp, devidamente identificada cada versão.

## Compilar
Se estiver em um ambiente GNU/Linux com o cmake instalado, você poderá usar os comandos:

- cmake: para compilar o arquivo normalmente.
```
cmake -H. -Bbuild
cmake --build build -- -j3
```

- caso não esteja com o comando cmake disponivel, você poderá usar o g++ com o comando dentro da pasta src:  
```g++ -Wall -std=c++11 src/driver.cpp -o driver```  

## Executar
Após a compilação, você poderá executar o código com o comando ```./bin/hashtable```, ou ```./driver``` (se não usou make).

### Authorship
- Henrique David de Medeiros	(henriquemed101@gmail.com)
- Pablo Emanuell L. Targino	(pabloemanuell@academico.ufrn.br)