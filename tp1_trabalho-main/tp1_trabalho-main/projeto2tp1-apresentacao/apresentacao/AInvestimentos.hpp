#ifndef APRESENTACAO_INVESTIMENTOS_HPP_INCLUDED
#define APRESENTACAO_INVESTIMENTOS_HPP_INCLUDED

#include "interfaces.hpp"

class CntrAInvestimentos: public IAInvestimentos {
private:
    ISInvestimentos *cntrISInvestimentos;
public:
    void criarTitulo();
    void lerTitulo();
    void atualizarTitulo();
    void deletarTitulo();
    void listarTitulos();
    void setCntrISInvestimentos(ISInvestimentos*);
};

void inline CntrAInvestimentos::setCntrISInvestimentos(ISInvestimentos *cntrISInvestimentos) {
    this->cntrISInvestimentos = cntrISInvestimentos;
}

#endif // APRESENTACAO_INVESTIMENTOS_HPP_INCLUDED
