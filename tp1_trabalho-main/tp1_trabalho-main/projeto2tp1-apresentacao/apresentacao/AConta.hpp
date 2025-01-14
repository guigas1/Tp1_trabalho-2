#ifndef APRESENTACAO_CONTA_HPP_INCLUDED
#define APRESENTACAO_CONTA_HPP_INCLUDED

#include "interfaces.hpp"

class CntrAConta: public IAConta {
private:
    ISConta *cntrISConta;
public:
    void criarConta();
    void lerConta(CPF*);
    void atualizarConta(CPF*);
    void deletarConta(CPF*);
    void setCntrISConta(ISConta*);
};

void inline CntrAConta::setCntrISConta(ISConta *cntrISConta) {
    this->cntrISConta = cntrISConta;
}

#endif // APRESENTACAO_CONTA_HPP_INCLUDED
