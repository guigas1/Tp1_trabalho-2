#ifndef controladores_h_included
#define controladores_h_included

#include "interfaces.hpp"
#include "dominios.hpp"

class CntrIAAutenticacao:public IAAutenticacao{
    private:
        ISAutenticacao *cntrISAutenticacao;
    public:
        bool autenticar(CPF*);
        void setCntrISAutenticacao(ISAutenticacao*);
};

class CntrISAutenticacao:public ISAutenticacao{
    public:
        bool autenticar(CPF&, Senha&);
};

class CntrIAConta:public IAConta{
    private:
        ISConta *cntrISConta;
    public:
        void lerConta(CPF*);
        void criarConta(void);
        void atualizarConta(CPF*);
        void deletarConta(CPF*);
        void setCntrISConta(ISConta*);
};

class CntrISConta:public ISConta{
    public:
        Conta lerConta(CPF);
        void criarConta(Conta);
        void atualizarConta(Conta);
        void deletarConta(CPF*);
};

class CntrISInvestimentos:public ISInvestimentos{
    private:
        bool validaData(Data,Data);
    public:
        void criarTitulo(Titulo);
        Titulo lerTitulo(CodigoTitulo);
        void atualizarTitulo(CPF*,Titulo);
        void deletarTitulo (CPF*,CodigoTitulo);
};

#endif