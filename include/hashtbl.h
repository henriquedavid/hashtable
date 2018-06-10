#ifndef HASH_TBL
#define HASH_TBL

template < typename KeyType,
		   typename DataType,
		   typename KeyHash = std::hash< KeyType >,
		   typename KeyEqual = std::equal_to< KeyHash > >	
class HashTbl{
public:

	using Entry = HashEntry< KeyType, DataType >;

	/**
	 * Construtor que aloca dinamicamente em *m_data_table um
     * vetor cujo tamanho é determinado como sendo o menor número primo maior do que o valor
	 * especificado em tbl_size_ . Esta é a área de armazenamento dos dados, ou seja, cada
	 * elemento deste vetor é um ponteiro para uma lista de itens de tabela, ou HashEntry.
	 */
	HashTbl ( size_t tbl_size_ = DEFAULT_SIZE );
	virtual ~HashTbl();
	/**
	 * Insere na tabela a informação contida em d_ e associada a uma chave k_ .
	 * A classe calcula o endereço end que a informação d_ deve ocupar na tabela e o armazena na
	 * lista de colisão correspondente, ou seja, em m_data_table[end] . Se a inserção foi realizada
	 * com sucesso a função retorna true . Se a chave já existir na tabela, o método sobrescreve
	 * os dados da tabela com os dados contidos em d_ e retorna false , para diferençar de uma
	 * inserção realizada pela primeira vez.
	 */
	bool insert( const KeyType & k_, const DataType & d_ );
	/**
	 * Remove um item de tabela identificado por sua chave k_ .
	 * Se a chave for encontrada o método retorna true , caso contrário false.
	 */
	bool remove( const KeyType & k_ );
	/**
	 * Recupera em d_ a informação associada a chave k_ passada como argumento para o método.
	 * Se a chave for encontrada o método retorna true , caso contrário
	 * false.
	 */
	bool retrieve( const KeyType & k_, DataType & d_ ) const;

	/**
	 * Libera toda a memória associada às listas de colisão da tabela, removendo todos
	 * seus elementos. Note que a memória dinâmica associada ao ponteiro m_data_table não
	 * deve ser liberada neste momento, mas apenas no destruidor da classe.
	 */
	void clear();

	/// Retorna true se a tabela de dispersão estiver vazia, ou false caso contrário.
	bool empty( void ) const;
	/// Retorna a quantidade de elemento atualmente armazenados na tabela.
	unsigned long int count( void ) const;

	/**
	 * É um método de depuração usado apenas para gerar uma representação textual da
	 * tabela e seus elementos. É um método útil na fase de desenvolvimento da classe para verificar
	 * se as operações sobre a tabela estão funcionando corretamente.
	 */
	void print() const;

private:
	static const short DEFAULT_SIZE = 11;
	/**
	 * É um método privado que deve ser chamado quando o fator de carga λ for maior
	 * que 1.0. O fator de carga é a razão entre o número de elementos na tabela e seu tamanho.
	 * Este método vai criar uma nova tabela cujo tamanho será igual ao menor número primo maior
	 * que o dobro do tamanho da tabela antes da chamada rehash() . Após a criação da nova
	 * tabela, todos os elementos devem ser inseridos na nova tabela, de acordo com uma nova
	 * função de dispersão secundária, baseada no novo tamanho da tabela. Cuidado especial deve
	 * ser tomado para evitar vazamento de memória. O cliente não deve perceber que esta operação
	 * foi acionada.
	 */
	void rehash();
	/// Verifica se o número x é um número primo ou não.
	bool ehprimo();
	/// Procura o próximo número primo após o valor inserido pelo usuário, ou o tamanho default da lista.
	bool nextPrimo();
	unsigned int m_size;
	unsigned int m_count;
	std::unique_ptr<std::forward_list< Entry > [] > * m_data_table;	// <-- Aqui seria no caso só isso ou tem que criar um outro ponteiro.
};

struct KeyHash {

	std::size_t operator()(const Account::AcctKey & k_) const;

};

struct KeyEqual{
	bool operator()(const Account::AcctKey & lhs_, const Account::AcctKey & rhs_) const;
};

#include "hashtbl.inl"

#endif