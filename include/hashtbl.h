#ifndef HASH_TBL
#define HASH_TBL

template < typename KeyType, typename DataType >	
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
	std::unique_ptr<std::forward_list< Entry > [] > * m_data_table;
}

#include "hashtbl.cpp"

#endif