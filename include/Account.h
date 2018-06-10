#include <cstring>
#include <utility>
#include <tuple>

namespace App {
    /// Definição de uma conta corrente.
    struct Account{
        /// ID do cliente.
        int id;
        /// Nome do cliente.
        std::string nome_;
        /// Código do banco.
        int banco_;
        /// Código da agência.
        int agencia_;
        /// Código da conta.
        int conta_;
        /// Saldo da conta.
        float saldo_;

        /// Construtor default.
        Account(){/*empty*/}

        /// Construtor que já inicializa a conta com todos os dados.
        Account( int id_, std::string nome, int banco, int agencia, int conta, float saldo){
            id = id_;
            nome_ = nome;
            banco_ = banco;
            agencia_ = agencia;
            conta_ = conta;
            saldo_ = saldo;
        }

        /// Retorna o valor do ID.
        int get_key(){
            return id;
        }

        /// Sobrecarga de atribuição.
        void operator=( Account & ac ){
            this->id = ac.id;
            this->nome_ = ac.nome_;
            this->banco_ = ac.banco_;
            this->agencia_ = ac.agencia_;
            this->conta_ = ac.conta_;
            this->saldo_ = ac.saldo_;
        }

        /// Sobrecarga do operador de comparação.
        bool operator==( const Account & ac ){
            if( this->id == ac.id &&
                this->nome_ == ac.nome_ &&
                this->banco_ == ac.banco_ &&
                this->agencia_ == ac.agencia_ &&
                this->conta_ == ac.conta_ &&
                this->saldo_ == ac.saldo_ )
                return true;
            return false;
        }
    };

    /// Sobrecarga do operador de impressão.
    std::ostream& operator<<(std::ostream & os, const Account& rhs){
        os << " - CONTA - | ID = " << rhs.id ;
        os << " | NOME = " << rhs.nome_ << " | BANCO = " << rhs.banco_ << " | AGÊNCIA = " << rhs.agencia_ <<
              " | CONTA = " << rhs.conta_ << " | SALDO = " << rhs.saldo_ << " | ";
        return os;
    }

    /// Declaração da'geração da chave.
    template <class AcctKey>
    struct KeyHash;

    /// Declaração do método de comparação de chaves.
    template <class AcctKey>
    struct KeyEqual;

    /// Estrutura de geração da chave para a Versão 1.
    template <>
    struct KeyHash<int>
    {
        using AcctKey = int;
        size_t operator()(const AcctKey& k_)
        {
            // Gera uma chave a partir do número da conta correte utilizando a função hash do STL
            return std::hash<int>()( k_ ) ;

            return 0;
        }
    };

    /// Estrutura de geração da chave para a Versão 1.
    template <>
    struct KeyHash< std::pair<std::string, int> >
    {
        using AcctKey = std::pair<std::string, int>;
        size_t operator()(const AcctKey& k_)
        {
            // Gera uma chave a partir do nome do cliente e o número da conta.
            return std::hash<std::string>()(k_.first) xor
                   std::hash<int>()(k_.second);

            return 0;
        }
    };

    /// Estrutura de geração da chave para a Versão 2.
    template <>
    struct KeyHash< std::tuple<std::string, int, int, int> >
    {
        using AcctKey = std::tuple<std::string, int, int, int>;
        size_t operator()(const AcctKey& k_)
        {
            // Gera uma chave a partir do nome do cliente, código do banco, o número da agência e o número da conta.
            return  std::hash<std::string>()(std::get<0>(k_)) xor
                    std::hash<int>()(std::get<1>(k_)) xor
                    std::hash<int>()(std::get<2>(k_)) xor
                    std::hash<int>()(std::get<3>(k_));
        }

    };

    /// Estrutura de comparação para a Versão 1.
    template <>
    struct KeyEqual<int>
    {
        using AcctKey = int;
        bool operator()(const AcctKey& lhs_, const AcctKey& rhs_)
        {
            return lhs_ == rhs_ ;
        }
    };

    /// Estrutura de comparação para a Versão 2.
    template <>
    struct KeyEqual<std::pair<std::string, int>>
    {
        using AcctKey = std::pair<std::string, int>;
        bool operator()(const AcctKey& lhs_, const AcctKey& rhs_)
        {
            return lhs_ == rhs_ ;
        }
    };

    /// Estrutura de comparação para a Versão 3.
    template <>
    struct KeyEqual<std::tuple<std::string, int, int, int>>
    {
        using AcctKey = std::tuple<std::string, int, int, int>;
        bool operator()(const AcctKey& lhs_, const AcctKey& rhs_)
        {
            return lhs_ == rhs_ ;
        }
    };

}



