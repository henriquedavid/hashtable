#ifndef HASH_TBL
#define HASH_TBL

template < typename KeyType,
		   typename DataType,
		   typename KeyHash = std::hash< KeyType >,
		   typename KeyEqual = std::equal_to<KeyHash> >	
class HashTbl{
public:

	using Entry = HashEntry< KeyType, DataType >;

	HashTbl ( size_t tbl_size_ = DEFAULT_SIZE );
	virtual ~HashTbl();
	bool insert( const KeyType & k_, const DataType & d_ );
	bool remove( const KeyType & k_ );
	bool retrieve( const KeyType & k_, DataType & d_ ) const;
	void clear();
	bool empty( void ) const;
	unsigned long int count( void ) const;
	void print() const;

private:
	static const short DEFAULT_SIZE = 11;
	void rehash();
	bool nextPrimo();
	unsigned int m_size;
	unsigned int m_count;
	std::unique_ptr<std::forward_list< Entry > [] > * m_data_table;	// <-- Aqui seria no caso só isso ou tem que criar um outro ponteiro.
}

struct KeyHash {

	std::size_t operator()(const Account::AcctKey & k_) const;

};

struct KeyEqual{
	bool operator()(const Account::AcctKey & lhs_, const Account::AcctKey & rhs_) const;
};

#include "hashtbl.inl"

#endif