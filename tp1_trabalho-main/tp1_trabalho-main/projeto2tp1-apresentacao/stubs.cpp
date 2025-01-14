#include "stubs.hpp"
#include <iostream>

string StubISAutenticacao::getTrigErro(){
    return this->trigger_erro_sistema;
}

string StubISAutenticacao::getTrigFalha(){
    return this->trigger_falha;
}

bool StubISAutenticacao::autenticar(const Nome &nome, const Senha &senha){
    cout << "Stub de servico de autenticacao" << endl;
    cout << "Nome: " << nome.getNome() << endl;
    cout << "Senha: " << senha.getSenha() << endl;

    if(nome.getNome() == getTrigErro()){
        throw runtime_error("erro de sistema");
    }

    if(nome.getNome() == getTrigFalha()){
        return false;
    }

    return true;

}






