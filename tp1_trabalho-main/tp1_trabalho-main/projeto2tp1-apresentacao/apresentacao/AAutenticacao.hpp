#ifndef AUTENTICACAO_H_INCLUDED
#define AUTENTICACAO_H_INCLUDED

#include "interfaces.hpp"
#include "../biblioteca/dominios.hpp"
#include "../biblioteca/entidades.hpp"

#define limpar system("clear");
#define esperar cin.ignore();

class ApresentacaoAutenticacao:public IAAutenticacao{
    private:
        ISAutenticacao *servico_autenticacao;
    public:
        bool autenticar(CPF*);
        void setServicoAutenticacao(ISAutenticacao*);
};

#endif //APRESENTACAO_AUTENTICACAO_HPP_INCLUDED