
template < class KeyType,
		   class DataType,
		   class KeyHash = std::hash< KeyType >,
		   class KeyEqual = std::equal_to< KeyHash > >
HashTbl<KeyType,DataType, KeyHash, KeyEqual>::HashTbl( size_t tbl_size_ = DEFAULT_SIZE ){
	if(tbl_size_ != DEFAULT_SIZE)
		tbl_size_ = nextPrimo(tbl_size_);

	m_size = tbl_size_;
	m_count = 0;
	m_data_table = new std::forward_list< Entry > [tbl_size_];
}


template < class KeyType, class DataType, class KeyHash, class KeyEqual >
bool HashTabl<KeyType,DataType, KeyHash, KeyEqual>::ehprimo(size_t x){
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

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
size_t HashTabl<KeyType,DataType, KeyHash, KeyEqual>::nextPrimo(size_t x){
	size_t nextPri = x+1;
 
	while(!ehprimo(nextPri))
		++nextPri;

	return nextPri;
}


template < class KeyType, class DataType, class KeyHash, class KeyEqual >
bool HashTabl<KeyType,DataType, KeyHash, KeyEqual>::insert(const KeyType & k_, const DataType & d_)
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

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
bool HashTabl<KeyType, DataType, KeyHash, KeyEqual>::remove(const  KeyType & k_)
{

}


template < class KeyType, class DataType, class KeyHash, class KeyEqual >
bool HashTabl<KeyType, DataType, KeyHash, KeyEqual>::retrieve( const KeyType & k_, DataType & d_ ) const{

}

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
bool HashTabl<KeyType,DataType, KeyHash, KeyEqual>::empty( void ) const{
	if( m_count == 0 )
		return true;
	return false;
}

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
unsigned long int HashTabl<KeyType,DataType, KeyHash, KeyEqual>::count( void ) const{
	if(m_count == 0)
		return true;
	return false;
}


template < class KeyType, class DataType, class KeyHash, class KeyEqual >
void HashTabl<KeyType,DataType, KeyHash, KeyEqual>::clear(){
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

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
void HashTabl<KeyType,DataType, KeyHash, KeyEqual>::print() const{
	std::cout << "--- HASHTABLE --- \n";

	// Percorre a tabela.
	for( auto & i : m_data_table )
		// Percorre a lista de cada chave.
		for( auto & j : i)
			std::cout << "Chave: " << i.m_key << "  |  Dado: " << u.m_data << std::endl;
}


template < class KeyType, class DataType, class KeyHash, class KeyEqual >
void HashTabl<KeyType,DataType, KeyHash, KeyEqual>::rehash(){

}

std::size_t KeyHash::operator()(const Account::AcctKey & k_) const{
	return std::hash<int>(k_);
	// return std::hash<std::string>()(k_.first)) xor
	//		  std::hash<int>()(k_.second); <- Versão 2
}

bool KeyEqual::operator()(const Account::AcctKey & lhs_, const Account::AcctKey & rhs_) const{
	return lhs_ == rhs_;
	// lhs_.first == rhs_.first and lhs_.second == rhs_.second;
}

