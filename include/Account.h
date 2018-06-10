struct Account{

	using AcctKey = size_t;

	AcctKey id;
	std::string nome_;
	int banco_;
	int agencia_;
	int conta_; 
	float saldo_;

	Account( size_t id, std::string nome, int banco, int agencia, int conta, float saldo){
		nome_ = nome;
		banco_ = banco;
		agencia_ = agencia;
		conta_ = conta;
		saldo_ = saldo;
	}

	AcctKey get_key(){
		return id;
	}

};