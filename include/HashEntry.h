/// Classe que armazena uma chave e um dado, o cliente não possui conhecimento sobre a existência da HashEntry.
template < typename KeyType,
           typename DataType,
           typename KeyHash = std::hash< KeyType >,
           typename KeyEqual = std::equal_to< KeyHash > >
class HashEntry
{
	public:
		HashEntry( KeyType k_, DataType d_ ) : m_key(k_), m_data(d_)
		{/* empty */}
        ~HashEntry();
		KeyType m_key;
		DataType m_data;
};
template <typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
inline HashEntry<KeyType, DataType, KeyHash, KeyEqual>::~HashEntry()
{
    m_key.~KeyType();
    m_data.~DataType();
}
