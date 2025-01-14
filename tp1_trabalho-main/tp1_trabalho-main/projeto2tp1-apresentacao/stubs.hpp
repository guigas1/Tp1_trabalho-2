#ifndef stubs_h_included
#define stubs_h_included

#include "interfaces.hpp"

#include <stdexcept>
#include <iostream>
#include <typeinfo>

using namespace std;

class StubISAutenticacao:public ISAutenticacao{
    private:
        const string trigger_falha = "Falha";
        const string trigger_erro_sistema = "Error";
    public:
        bool autenticar(const Nome&, const Senha&);
        string getTrigFalha();
        string getTrigErro();
};

#endif