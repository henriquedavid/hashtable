template < typename KeyType, typename DataType >
HashTabl::HashTbl( size_t tbl_size_ = DEFAULT_SIZE ) : m_size(tbl_size_){/*empty*/}

template < typename KeyType, typename DataType >
bool HashTabl::empty( void ) const{
	if( m_size == 0 )
		return true;
	return false;
}

template < typename KeyType, typename DataType >
unsigned long int HashTabl::count( void ) const{
	if(m_count == 0)
		return true;
	return false;
}

