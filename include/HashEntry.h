template < class KeyType, class DataType >
class HashEntry
{
public:
	HashEntry( KeyType k_, DataType d_ ) : m_key(k_), m_data(d_)
	{/* empty */}
	KeyType m_key;
	DataType m_data;
};