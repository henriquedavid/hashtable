template < typename KeyType, typename DataType >
HashTabl<KeyType,DataType>::HashTbl( size_t tbl_size_ = DEFAULT_SIZE ){
	if(tbl_size_ != DEFAULT_SIZE)
		tbl_size_ = nextPrimo(tbl_size_);

	m_size = tbl_size_;
	m_count = 0;
	m_data_table = new std::forward_list< Entry > [tbl_size_];
}

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

size_t HashTabl<KeyType,DataType>::nextPrimo(size_t x){
	size_t nextPri = x+1;
 
	while(!ehprimo(nextPri))
		++nextPri;

	return nextPri;
}

template < typename KeyType, typename DataType >
bool HashTabl<KeyType,DataType>::insert(KeyType & k_, DataType & d_)
{

	/*Verificar se possui espaço suficiente,
	procurar se na chave já possui algum elemento,
	se possuir inserir na frente da lista encadeada,
	se não basta inserir o elemento na lista.*/

	

}

template < typename KeyType, typename DataType >
bool HashTabl<KeyType,DataType>::empty( void ) const{
	if( m_count == 0 )
		return true;
	return false;
}

template < typename KeyType, typename DataType >
unsigned long int HashTabl<KeyType,DataType>::count( void ) const{
	if(m_count == 0)
		return true;
	return false;
}

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

template < typename KeyType, typename DataType >
void HashTabl<KeyType,DataType>::print() const{
	std::cout << "--- HASHTABLE --- \n";

	// Percorre a tabela.
	for( auto & i : m_data_table )
		// Percorre a lista de cada chave.
		for( auto & j : i)
			std::cout << "Chave: " << i.m_key << "  |  Dado: " << u.m_data << std::endl;
}