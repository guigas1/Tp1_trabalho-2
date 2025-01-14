#ifndef unidadePersistenciaH
#define unidadePersistenciaH

#include "dominios.hpp"
#include "entidades.hpp"
#include <list>
#include <iostream>
#include <string>
#include <bits/stdc++.h>

#include "sqlite3.h"


class ErroPersistencia{
    private:
        string mensagem;
    public:
        ErroPersistencia(string);
        string getMensagem() const;
};

class ElementoResultado{
    private:
        string nomeColuna;
        string valorColuna;
    public:
        void setNomeColuna(const string&);
        string getNomeColuna() const;
        void setValorColuna(const string&);
        string getValorColuna() const;
};

class ComandoSQL{
    private:
        const char *nomeBancoDados;
        sqlite3 *bd;
        char *mensagem;
        int rc;
        void conectar();
        void desconectar();
        static int callback(void *, int, char **, char **);
    protected:
        static list<ElementoResultado> listaResultado;
        string comandoSQL;
    public:
        ComandoSQL() {nomeBancoDados = "testedb.db";} //colocar nome do banco de dados
        void executar();
};

//Comandos relacionados a conta

class ComandoCriarConta:public ComandoSQL{
    public:
        ComandoCriarConta(Conta);
};

class ComandoLerConta:public ComandoSQL{
    public:
        ComandoLerConta(CPF);
        Conta getResultado();
};

class ComandoEditarConta:public ComandoSQL{
    public:
        ComandoEditarConta(Conta);
};

class ComandoDeletarConta:public ComandoSQL{
    public:
        ComandoDeletarConta(CPF);
};

//Comando count
class ComandoCount:public ComandoSQL{
    public:
        ComandoCount(string,string);
        ComandoCount(string);
        int getResultado();
};

//Comandos relacionados a titulos
class ComandoCriarTitulo:public ComandoSQL{
    public:
        ComandoCriarTitulo(Titulo);
};

class ComandoLerTitulo:public ComandoSQL{
    public:
        ComandoLerTitulo(CodigoTitulo);
        Titulo getResultado();
};

class ComandoDeletarTitulo:public ComandoSQL{
    public:
        ComandoDeletarTitulo(string);
};

class ComandoAtualizarTitulo:public ComandoSQL{
    public:
        ComandoAtualizarTitulo(Titulo);
};


#endif