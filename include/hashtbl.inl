#include "hashtbl.h"

/// \note: valor padrão de argumentos e templates só são declarados no header
template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline HashTbl<KeyType,DataType, KeyHash, KeyEqual>::HashTbl( size_t tbl_size_){
	if(tbl_size_ != DEFAULT_SIZE)
		tbl_size_ = nextPrimo(tbl_size_);

	m_size = tbl_size_;
	m_count = 0;
    using Entry = HashEntry< KeyType, DataType >;
    m_data_table = std::unique_ptr<std::forward_list< Entry > [] > (new std::forward_list< Entry > [tbl_size_]);
}


template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::ehprimo(size_t x){
    /// \note: para checar se eh primo, se verificar se o resto da divisao de x com algum c dentro do intervalo [2, x-1] eh 0.
    for(uint c = 2; c < x; ++c)
        if(x % c == 0)
            return false;
    return true;

}

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline size_t HashTbl<KeyType,DataType, KeyHash, KeyEqual>::nextPrimo(size_t x){
    size_t nextPri = x;
    ///\note: o tamanho passado pode já ser primo, ou seja o cliente já irá ficar satisfeito com o tamanho
 
    while(ehprimo(nextPri) == false)
    {
        ++nextPri;
    }


	return nextPri;
}


template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline bool HashTbl<KeyType,DataType, KeyHash, KeyEqual>::insert(const KeyType & k_, const DataType & d_)
{

	/*Verificar se possui espaço suficiente,
	procurar se na chave já possui algum elemento,
	se possuir inserir na frente da lista encadeada,
	se não basta inserir o elemento na lista.*/
    if(m_count / m_size >= 1.0)
        rehash();

    KeyHash hf;
    KeyEqual equal;
    size_t id = hf(k_) % m_size;
	// Verifica se já possui algum elemento na chave;
    auto& list = m_data_table[id];
    for(auto & element : list)
    {
        if(equal(k_, element.m_key))
            return false;
    }
    list.push_front(Entry(k_, d_));
	++m_count;
    return true;

}

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::remove(const  KeyType & k_)
{
    return false;
}


template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::retrieve( const KeyType & k_, DataType & d_ ) const{
    return false;
}

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline bool HashTbl<KeyType,DataType, KeyHash, KeyEqual>::empty( void ) const{
	if( m_count == 0 )
		return true;
	return false;
}

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline unsigned long int HashTbl<KeyType,DataType, KeyHash, KeyEqual>::count( void ) const{
    return m_count;
}


template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline void HashTbl<KeyType,DataType, KeyHash, KeyEqual>::clear(){
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
inline void HashTbl<KeyType,DataType, KeyHash, KeyEqual>::print() const{
	std::cout << "--- HASHTABLE --- \n";
    for(uint i = 0; i < m_size; ++i)
    {
        std::cout << "--- linha " << i << " ---\n";
        std::cout << "[ ";
        auto list = m_data_table[i];
        for(auto & element : list )
        {
            std::cout << element.m_key << " ";
        }
        std::cout << "]\n";
    }
}


template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline void HashTbl<KeyType,DataType, KeyHash, KeyEqual>::rehash(){

}

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline HashTbl<KeyType,DataType, KeyHash, KeyEqual>::~HashTbl(){

}

