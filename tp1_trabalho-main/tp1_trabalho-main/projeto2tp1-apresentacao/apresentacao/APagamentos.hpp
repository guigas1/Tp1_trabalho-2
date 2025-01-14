#ifndef APRESENTACAO_PAGAMENTOS_HPP_INCLUDED
#define APRESENTACAO_PAGAMENTOS_HPP_INCLUDED

#include "interfaces.hpp"

class CntrAPagamentos: public IAPagamentos {
private:
    ISPagamentos *cntrISPagamentos;
public:
    void criarPagamento();
    void lerPagamento();
    void atualizarPagamento();
    void deletarPagamento();
    void listarPagamentos();
    void setCntrISPagamentos(ISPagamentos*);
};

void inline CntrAPagamentos::setCntrISPagamentos(ISPagamentos *cntrISPagamentos) {
    this->cntrISPagamentos = cntrISPagamentos;
}

#endif // APRESENTACAO_PAGAMENTOS_HPP_INCLUDED
