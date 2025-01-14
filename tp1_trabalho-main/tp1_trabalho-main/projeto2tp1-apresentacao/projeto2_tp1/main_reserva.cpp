#include <stdexcept>
#include <iostream>
#include <string>

#include "dominios.hpp"
#include "entidades.hpp"
#include "interfaces.hpp"
#include "controladoras.hpp"
#include "stubs.hpp"

using namespace std;

int main(){

    IAAutenticacao *cntrIAAutenticacao = new CntrIAAutenticacao();
    ISAutenticacao *stubISAutenticacao = new StubISAutenticacao();

    cntrIAAutenticacao->setCntrISAutenticacao(stubISAutenticacao);
    bool result;

    Nome nomeTeste  ;

    while(true){

        cout << "Tela inicial do sistema" << endl;

        try{
            result = cntrIAAutenticacao->autenticar(&nomeTeste);
        }
        catch(runtime_error &exp){
                cout << "Erro de sistema" << endl;
        }

        if(result){
            cout << "sucesso de auth" << endl;
            cout << "nome: " << nomeTeste.getNome() << endl;
            break;
        } else {
            cout << "erro de auth" << endl;
            break;
        }

    }

    delete cntrIAAutenticacao;
    delete stubISAutenticacao;

    return 0;

}
