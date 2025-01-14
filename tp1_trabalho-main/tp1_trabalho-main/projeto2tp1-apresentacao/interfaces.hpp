#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include "dominios.hpp"
#include "entidades.hpp"
#include <stdexcept>

using namespace std;

class ISAutenticacao{
public:
    virtual bool autenticar(CPF&, Senha&) = 0 ;
    virtual ~ISAutenticacao(){};
};

class IAAutenticacao{
public:
    virtual bool autenticar(CPF*) = 0;
    virtual void setCntrISAutenticacao(ISAutenticacao*) = 0;
    virtual ~IAAutenticacao(){};
};

class ISConta{
public:
    virtual Conta lerConta(CPF) = 0;
    virtual void criarConta(Conta) = 0;
    virtual void atualizarConta(Conta) = 0;
    virtual void deletarConta(CPF*) = 0;
    virtual ~ISConta(){};
};

class IAConta{
public:
    virtual void lerConta(CPF*) = 0;
    virtual void criarConta(void) = 0;
    virtual void atualizarConta(CPF*) = 0;
    virtual void deletarConta(CPF*) = 0;
    virtual void setCntrISConta(ISConta*) = 0;
    virtual ~IAConta(){};
};

class ISInvestimentos{
public:
    virtual void criarTitulo(Titulo) = 0;
    virtual Titulo lerTitulo(CodigoTitulo) = 0;
    virtual void atualizarTitulo(CPF*,Titulo) = 0;
    virtual void deletarTitulo (CPF*,CodigoTitulo) = 0;
    virtual void listarTitulos(CPF*) = 0;
    virtual ~ISInvestimentos(){};
};

class IAInvestimentos{
public:
    virtual void criarTitulo() = 0;
    virtual void lerTitulo() = 0;
    virtual void atualizarTitulo() = 0;
    virtual void deletarTitulo() = 0;
    virtual void listarTitulos() = 0;
    virtual void setCntrISInvestimentos(ISInvestimentos*) = 0;
    virtual ~IAInvestimentos(){};
};

class ISPagamentos{
public:
    virtual void criarPagamento(Pagamento) = 0;
    virtual Pagamento lerPagamento(CodigoPagamento) = 0;
    virtual void atualizarPagamento(Pagamento) = 0;
    virtual void deletarPagamento(CodigoPagamento*) = 0;
    virtual void listarPagamentos(CodigoTitulo*) = 0;
    virtual ~ISPagamentos(){};
};

class IAPagamentos{
public:
    virtual void criarPagamento() = 0;
    virtual void lerPagamento() = 0;
    virtual void atualizarPagamento() = 0;
    virtual void deletarPagamento() = 0;
    virtual void listarPagamentos() = 0;
    virtual void setCntrISPagamentos(ISPagamentos*) = 0;
    virtual ~IAPagamentos(){};
};

#endif // INTERFACES_HPP_INCLUDED
