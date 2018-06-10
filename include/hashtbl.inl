/*Construtor que aloca dinamicamente em *m_data_table um
vetor cujo tamanho é determinado como sendo o menor número primo maior do que o valor
especificado em tbl_size_ . Esta é a área de armazenamento dos dados, ou seja, cada
elemento deste vetor é um ponteiro para uma lista de itens de tabela, ou HashEntry .*/
template < typename KeyType, typename DataType >
HashTabl<KeyType,DataType>::HashTbl( size_t tbl_size_ = DEFAULT_SIZE ){
	if(tbl_size_ != DEFAULT_SIZE)
		tbl_size_ = nextPrimo(tbl_size_);

	m_size = tbl_size_;
	m_count = 0;
	m_data_table = new std::forward_list< Entry > [tbl_size_];
}

/* Verifica se o número x é um número primo ou não.*/
bool HashTabl<KeyType,DataType>::ehprimo(size_t x){
	size_t count = 0;
	size_t numeracao = 1;
	while(numeracao != x){
		if(x/numeracao)
			count++;
		++numeracao;
	}

	if(count == 1)
		return true;
	else
		return false;
}

/* Procura o próximo número primo após o valor inserido pelo usuário, ou o tamanho default da lista.*/
size_t HashTabl<KeyType,DataType>::nextPrimo(size_t x){
	size_t nextPri = x+1;
 
	while(!ehprimo(nextPri))
		++nextPri;

	return nextPri;
}

/*Insere na tabela a informação contida em d_ e associada a uma chave k_ .
A classe calcula o endereço end que a informação d_ deve ocupar na tabela e o armazena na
lista de colisão correspondente, ou seja, em m_data_table[end] . Se a inserção foi realizada
com sucesso a função retorna true . Se a chave já existir na tabela, o método sobrescreve
os dados da tabela com os dados contidos em d_ e retorna false , para diferençar de uma
inserção realizada pela primeira vez.*/
template < typename KeyType, typename DataType >
bool HashTabl<KeyType,DataType>::insert(const KeyType & k_, const DataType & d_)
{

	/*Verificar se possui espaço suficiente,
	procurar se na chave já possui algum elemento,
	se possuir inserir na frente da lista encadeada,
	se não basta inserir o elemento na lista.*/

	// Verifica se possui espaço suficiente.
	if( m_count >= m_size){
		auto last(m_data_table);
		m_size = nextPrimo(m_size*2);
		std::unique_ptr<std::forward_list< Entry > [] > * new_data_table = new std::forward_list<Entry>[m_size];

		for( auto & i : m_data_table )
		{
			new_data_table.push_front(i);
		}

		delete [] m_data_table;
		m_data_table = new_data_table;
	}

	bool possui_elemento = false;

	// Verifica se já possui algum elemento na chave;
	for( auto & i : m_data_table ){
		if( i.key == k_ ){
			for( auto & j : i ){
				if( j.d_ == d_)
					possui_elemento == true;
			}
			if(!possui_elemento)
			{
				i.push_front(new HashEntry(k_, d_));
				++m_count;
				return true;
			}

		}
	}

	m_data_table.push_front(new HashEntry(k_, d_));
	++m_count;
	return true;

	return false;

}

/*Remove um item de tabela identificado por sua chave k_ .
Se a chave for encontrada o método retorna true , caso contrário false .*/
template < typename KeyType, typename DataType >
bool HashTabl<KeyType, DataType>::remove(const  KeyType & k_)
{

}

/*Recupera em d_ a informação associada a chave k_ passada como ar-
gumento para o método. Se a chave for encontrada o método retorna true , caso contrário
false .*/
template < typename KeyType, typename DataType >
bool HashTabl<KeyType, DataType>::retrieve( const KeyType & k_, DataType & d_ ) const{

}

/*Retorna true se a tabela de dispersão estiver vazia, ou false caso contrário.*/
template < typename KeyType, typename DataType >
bool HashTabl<KeyType,DataType>::empty( void ) const{
	if( m_count == 0 )
		return true;
	return false;
}

/*Retorna a quantidade de elemento atualmente armazenados na tabela.*/
template < typename KeyType, typename DataType >
unsigned long int HashTabl<KeyType,DataType>::count( void ) const{
	if(m_count == 0)
		return true;
	return false;
}

/*Libera toda a memória associada às listas de colisão da tabela, removendo todos
seus elementos. Note que a memória dinâmica associada ao ponteiro m_data_table não
deve ser liberada neste momento, mas apenas no destruidor da classe.*/
template < typename KeyType, typename DataType >
void HashTabl<KeyType,DataType>::clear(){
	// Apaga o conteúdo de cada lista interna.
	for( auto & i : m_data_table ){
		i.clear();
	}
	// Apaga a tabela em si
	delete [] this->m_data_table;
	// Declara a tabela vazia.
	this->m_data_table = new std::forward_list< Entry > [m_size];
	this->count = 0;
}

/*É um método de depuração usado apenas para gerar uma representação textual da
tabela e seus elementos. É um método útil na fase de desenvolvimento da classe para verificar
se as operações sobre a tabela estão funcionando corretamente.*/
template < typename KeyType, typename DataType >
void HashTabl<KeyType,DataType>::print() const{
	std::cout << "--- HASHTABLE --- \n";

	// Percorre a tabela.
	for( auto & i : m_data_table )
		// Percorre a lista de cada chave.
		for( auto & j : i)
			std::cout << "Chave: " << i.m_key << "  |  Dado: " << u.m_data << std::endl;
}

/*É um método privado que deve ser chamado quando o fator de carga λ for maior
que 1.0. O fator de carga é a razão entre o número de elementos na tabela e seu tamanho.
Este método vai criar uma nova tabela cujo tamanho será igual ao menor número primo maior
que o dobro do tamanho da tabela antes da chamada rehash() . Após a criação da nova
tabela, todos os elementos devem ser inseridos na nova tabela, de acordo com uma nova
função de dispersão secundária, baseada no novo tamanho da tabela. Cuidado especial deve
ser tomado para evitar vazamento de memória. O cliente não deve perceber que esta operação
foi acionada.*/
template < typename KeyType, typename DataType >
void HashTabl<KeyType,DataType>::rehash(){

}