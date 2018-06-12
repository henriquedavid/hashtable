#include "hashtbl.h"

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline HashTbl<KeyType,DataType, KeyHash, KeyEqual>::HashTbl( size_t tbl_size_){
    // Pega o próximo primo a partir do tamanoh passado.
    tbl_size_ = nextPrimo(tbl_size_);

	// O novo tamanho será o definido.
	m_size = tbl_size_;
	// Não há nenhuma conta inserida.
	m_count = 0;
	// Cria lista dinâmica para armazenar as contas.
    using Entry = HashEntry< KeyType, DataType >;
    m_data_table = std::unique_ptr<std::forward_list< Entry > [] > (new std::forward_list< Entry > [tbl_size_]);
}


template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::ehprimo(size_t x){
    // Verifica se o numero eh divisivel por alguem entre 2 e ele
    for(uint c = 2; c < x; ++c)
        if(x % c == 0)
            return false;
    return true;

}

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline size_t HashTbl<KeyType,DataType, KeyHash, KeyEqual>::nextPrimo(size_t x){
    // Pega o proximo numero primo a partir de x
    size_t nextPri = x;
 
    while(ehprimo(nextPri) == false)
    {
        ++nextPri;
    }

	return nextPri;
}


template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline bool HashTbl<KeyType,DataType, KeyHash, KeyEqual>::insert(const KeyType & k_, const DataType & d_)
{

    /* Verificar se possui espaço suficiente,
	procurar se na chave já possui algum elemento,
	se possuir inserir na frente da lista encadeada,
    se não basta inserir o elemento na lista. */

    KeyHash hf;
    KeyEqual equal;
    size_t id = hf(k_) % m_size;

	// Verifica se já possui algum elemento na chave;
    auto& list = m_data_table[id];

    /*
     * Caso o usuário insira uma chave que já esteja na tabela o novo dado não é inserido.
     */
    /// \note: A chave é o identificador do elemento, se ela já existe, não insera. Não é necessário comparar os dados.
    for(auto & element : list)
        if(equal(k_, element.m_key))
                return false;

    // Verifica o fator de carga atual da tabela
    if(m_count / m_size >= 1.0)
        rehash();

    // adiciona o novo elemento
    list.push_front(Entry(k_, d_));
    // Incrementa o tamanho ocupado.
	++m_count;
    return true;

}

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::remove(const  KeyType & k_)
{
    KeyHash hf;
    KeyEqual equal;
    size_t id = hf(k_) % m_size;

    // Obtem a lista no local especifico.
    auto& list = m_data_table[id];

    // Obtem o valor anterior ao inicio da lista.
    auto before(list.before_begin());
    // Obtem o inicio da lista.
    auto begin(list.begin());
    // Obtem o final da lista.
    auto end(list.end());
    // Percorre a lista de forma a encontrar o valor informado.
    while(begin != end)
    {
        if(equal(begin->m_key, k_))
        {
        	// Se foi encontrado a chave então remove o dado.
            list.erase_after(before);
            return true;
        }
        ++before;
        ++begin;
    }

    // Caso não tenha sido encontrado nenhum valor então retorne falso.
    return false;
}


template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::retrieve( const KeyType & k_, DataType & d_ ) const{

    KeyHash hf;
    KeyEqual equal;
    // Obtém em qual posição se encontra o elemento na tabela.
    size_t id = hf(k_) % m_size;

    // Procura o elemento
    auto & list = m_data_table[id];
    for(auto & element : list)
    {
        if(equal(k_, element.m_key)){
        	// Atribui o valor encontrado a uma conta que o usuário especificou.
            d_ = element.m_data;
            return true;
        }
    }

    // Se não foi encontrada a conta retorna falso.
    return false;
}

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline bool HashTbl<KeyType,DataType, KeyHash, KeyEqual>::empty( void ) const{
	// Verifica se alguma conta foi inserida.
	if( m_count == 0 )
		return true;
	return false;
}

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline unsigned long int HashTbl<KeyType,DataType, KeyHash, KeyEqual>::count( void ) const{
	// Retorna quantas contas estão na tabela.
    return m_count;
}


template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline void HashTbl<KeyType,DataType, KeyHash, KeyEqual>::clear(){
	// Limpa todas as contas da tabela.
    for(uint i = 0; i < m_size; ++i)
    {
        auto& list = m_data_table[i];
        list.clear();
    }
    m_count = 0;
}

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline void HashTbl<KeyType,DataType, KeyHash, KeyEqual>::print() const{
	// Imprime todos os dados da tabela.
	std::cout << "--- HASHTABLE --- \n";
    for(uint i = 0; i < m_size; ++i)
    {
        std::cout << "--- linha " << i << " ---\n";
        std::cout << "{\n";
        auto& list = m_data_table[i];
        for(auto & element : list )
        {
            std::cout << element.m_data << "\n";
        }
        std::cout << "}\n";
    }
}


template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline void HashTbl<KeyType,DataType, KeyHash, KeyEqual>::rehash(){
    // modifica o atributo que armazena o tamanho
    m_size *= 2;
    // Alias para entrada
    using Entry = HashEntry< KeyType, DataType >;
    // Aloca o novo vetor
    std::forward_list<Entry>* new_data_table = new std::forward_list<Entry>[m_size];
    // Copia o conteudo para a tabela nova
    for(uint i = 0; i < m_size; ++i)
    {
        auto& list = m_data_table[i];
        new_data_table[i] = list;
    }
    // Susbstitui o ponteiro antigo
    m_data_table.reset(new_data_table);
    // Atualiza o tamanho
}

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
inline HashTbl<KeyType,DataType, KeyHash, KeyEqual>::~HashTbl(){
    // chama o método clear
    clear();
    m_size = 0;
}

