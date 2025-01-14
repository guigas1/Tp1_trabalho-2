#include <stdexcept>
#include <iostream>
#include <string>

#include "dominios.hpp"
#include "entidades.hpp"
#include "interfaces.hpp"
#include "controladoras.hpp"
#include "stubs.hpp"
#include "unidadepersistencia.hpp"

using namespace std;

int main(){

    IAConta *cntrIAConta = new CntrIAConta();
    ISConta *cntrISConta = new CntrISConta();
    IAAutenticacao *cntrIAAutenticacao = new CntrIAAutenticacao();
    ISAutenticacao *cntrISAutenticacao = new CntrISAutenticacao();

    ISInvestimentos *cntrISI = new CntrISInvestimentos();

    cntrIAConta->setCntrISConta(cntrISConta);
    cntrIAAutenticacao->setCntrISAutenticacao(cntrISAutenticacao);

    cout << "teste de interface de contas" << endl;

    int decisao;
    CPF cpfteste ("083.422.731-21");
    Data d1 ("05-02-2019"), d2 ("15-04-2023");
    CodigoTitulo codigo ("CRAA1234563");
    Setor setor ("Agricultura");
    Dinheiro valor (100.5);
    Nome nom ("Pedro");

    Titulo teste;
    teste.setCpf(cpfteste);
    teste.setCodigoTitulo(codigo);
    teste.setValor(valor);
    teste.setEmissao(d1);
    teste.setVencimento(d2);
    teste.setSetor(setor);
    teste.setEmissor(nom);

    Titulo tituloRecebido;

    cout << "opcoes abaixo " << endl;
    cout << "1 - criar conta (use o mesmo cpf anterior)" << endl;
    cout << "2 - ler conta (usa o mesmo cpf anterior)" << endl;
    cout << "3 - alterar conta (usa o mesmo cpf anterior)" << endl;
    cout << "4 - deleta conta (usa o mesmo cpf anterior)" << endl;
    cout << "5 - teste de cria titulos" << endl;
    cout << "6 - teste de ler titulos" << endl;
    cout << "7 - teste de alterar titulos" << endl;
    cout << "8 - teste de deletar titulo" << endl;
    cout << "outros numeros encerram o programa" << endl;

    cin >> decisao;

    switch (decisao)
    {
    case 1:
        cntrIAConta->criarConta();
        break;
    case 2:
        cntrIAConta->lerConta(&cpfteste);
        break;
    case 3:
        cntrIAConta->atualizarConta(&cpfteste);
        break;
    case 4:
        cntrIAConta->deletarConta(&cpfteste);
        break;
    case 5:
    try{
        cntrISI->criarTitulo(teste);
        break;
    }
    catch(ErroPersistencia exp){
        cout << exp.getMensagem() << endl;
        break;
    }
    case 6:
        tituloRecebido = cntrISI->lerTitulo(codigo);
        cout << "cpf:" + tituloRecebido.getCpf().getCPF() << endl;
        cout << "codigo:" + tituloRecebido.getCodigoTitulo().getCodigoTitulo() << endl;
        cout << "valor:" + to_string(tituloRecebido.getValor().getDinheiro()) << endl;
        cout << "emissao:" + tituloRecebido.getEmissao().getData() << endl;
        cout << "vencimento:" + tituloRecebido.getVencimento().getData() << endl;
        cout << "setor:" + tituloRecebido.getSetor().getSetor() << endl;
        cout << "nome:" + tituloRecebido.getEmissor().getNome() << endl;
        break;
    case 7:
    try{
        teste.setSetor(Setor("Energia"));
        cntrISI->atualizarTitulo(&cpfteste,teste);
        break;
    }
    catch(ErroPersistencia exp){
        cout << exp.getMensagem() << endl;
        break;
    }
    case 8:
        cntrISI->deletarTitulo(&cpfteste,codigo);
        break;
    default:
        cout << "opcao invalida" << endl;
        break;
     }
    

    delete cntrIAConta;
    delete cntrISConta;
    delete cntrIAAutenticacao;
    delete cntrISAutenticacao;
    delete cntrISI;

    return 0;

}
