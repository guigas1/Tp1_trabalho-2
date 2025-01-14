#include "controladoras.hpp"
#include "dominios.hpp"
#include "unidadepersistencia.hpp"
#include <iostream>
#include <limits>

using namespace std;


bool CntrIAAutenticacao::autenticar(CPF *cpfTeste){
    Senha senhaTeste;
    string entrada;
    bool decisaoLogin;

    cout << "Deseja realizar login?" << endl;
    cout << "1 - sim | 0 - nao" << endl;
    cin >> decisaoLogin;

    if(decisaoLogin == false){
        return false;
    }

    while(true){
        cout << "Autenticacao de usuario" << endl;

        try{
            cout << "Digite o cpf: " << endl;
            cin >> entrada;
            cpfTeste->setCPF(entrada);
            cout << "Digite a senha: " << endl;
            cin >> entrada;
            senhaTeste.setSenha(entrada);
            break;
        }
        catch(invalid_argument exp){
            cout << exp.what() << endl;
            cout << "Deseja tentar novamente?" << endl;
            cout << "1 - sim | 0 - nao" << endl;
            cin >> decisaoLogin;
            if(decisaoLogin == false){
                return false;
            }
        }
    }

    try{
        bool resultado = cntrISAutenticacao->autenticar(*cpfTeste,senhaTeste);
        return resultado;
    }
    catch(ErroPersistencia exp){
        cout << exp.getMensagem() << endl;
        cin;
    }

    return false;

}

void CntrIAAutenticacao::setCntrISAutenticacao(ISAutenticacao *interface){
    this->cntrISAutenticacao = interface;
}

bool CntrISAutenticacao::autenticar(CPF &cpfTeste, Senha &senhaTeste){

    ComandoLerConta comando (cpfTeste);

    Conta conta;

    comando.executar();

    conta = comando.getResultado();

    if(senhaTeste.getSenha() != conta.getSenha().getSenha() || cpfTeste.getCPF() != conta.getCpf().getCPF()){
        return false;
    }

    return true;

}

//Metodos relacionados a contas

void CntrIAConta::setCntrISConta(ISConta *interface){
    this->cntrISConta = interface;
}

void CntrIAConta::criarConta(){
    string inputNome;
    string inputCPF;
    string inputSenha;
    bool decisao;

    CPF cpfTeste;
    Nome nomeTeste;
    Senha senhaTeste;

    cin.ignore(1);

    while(true){

        cout << "Tela de criacao de contas" << endl;
        cout << "Digite o nome: ";
        getline(cin,inputNome,'\n');
        cout << "Digite o CPF: ";
        cin >> inputCPF;
        cin.clear();
        cout << "Digite uma senha: ";
        cin >> inputSenha;
        cin.clear();

        cout << "Deseja criar conta com os dados anteriores?" << endl;
        cout << "1 - Sim | 0 - Nao" << endl;
        cin >> decisao;

        if(decisao == 0) {
            return;
        }

        try{
            nomeTeste.setNome(inputNome);
            cpfTeste.setCPF(inputCPF);
            senhaTeste.setSenha(inputSenha);
        }
        catch(invalid_argument exp){
            cout << exp.what() << endl;
            cout << "Deseja tentar novamente?" << endl;
            cout << "1 - Sim | 0 - Nao" << endl;
            cin >> decisao;
            if(decisao == 0){
                return;
            }
        }

        Conta contaTeste;
        contaTeste.setNome(nomeTeste);
        contaTeste.setCpf(cpfTeste);
        contaTeste.setSenha(senhaTeste);

        try{
        cntrISConta->criarConta(contaTeste);
        }
        catch(ErroPersistencia exp){
            cout << exp.getMensagem() << endl;
            return;
        }

        break;

    }

    cout << "Conta criada com sucesso" << endl;
    cin;
    return;

}

void CntrIAConta::lerConta(CPF *cpfteste){

    Conta conta;

    cout << "Tela com apresentacao de dados de login" << endl;

    try{
    conta = cntrISConta->lerConta(*cpfteste);
    }
    catch(ErroPersistencia exp){
        cout << exp.getMensagem() << endl;
        cin;
        return;
    }

    cout << "Nome:" << conta.getNome().getNome() << endl;
    cout << "CPF: " << conta.getCpf().getCPF() << endl;
    cout << "Senha: " << conta.getSenha().getSenha() << endl;

    cout << "aperter ENTER para continuar" << endl;
    cin;

    return;

}

void CntrIAConta::atualizarConta(CPF *cpfTeste){

    string inputNome,inputSenha;
    bool decisao;
    Nome nomeTeste;
    Senha senhaTeste;
    Conta contaTeste;

    cout << "Tela de atualizacao de dados de login" << endl;
    cout << "Insira o nome: ";
    cin >> inputNome;
    cout << "Insira a senha: ";
    cin >> inputSenha;

    cout << "Deseja mesmo alterar sua conta?" << endl;
    cout << "1 - Sim | 0 - Nao" << endl;
    cin >> decisao;

    if(decisao == 0){
        return;
    }

    try{
        cntrISConta->lerConta(*cpfTeste);
    }
    catch(ErroPersistencia exp){
        cout << exp.getMensagem() << endl;
        cin;
        return;
    }

    try{
        nomeTeste.setNome(inputNome);
        senhaTeste.setSenha(inputSenha);
    }
    catch(invalid_argument exp){
        cout << exp.what() << endl;
        cin;
        return;
    }

    contaTeste.setCpf(*cpfTeste);
    contaTeste.setNome(nomeTeste);
    contaTeste.setSenha(senhaTeste);

    try{
        cntrISConta->atualizarConta(contaTeste);
    }
    catch(ErroPersistencia exp){
        cout << exp.getMensagem() << endl;
        return;
    }

    cout << "Alteracoes feitas" << endl;
    cin;
    return;

}

void CntrIAConta::deletarConta(CPF *cpfTeste){

    bool decisao;

    cout << "Deseja deletar a conta com cpf: ";
    cout << cpfTeste->getCPF() << endl;

    cout << "Deseja deletar conta com os dados anteriores?" << endl;
    cout << "1 - Sim | 0 - Nao" << endl;
    cin >> decisao;

    if(decisao == 0){
        return;
    }

    try{
        cntrISConta->lerConta(*cpfTeste);
    }
    catch(ErroPersistencia exp){
        cout << exp.getMensagem() << endl;
        cin;
        return;
    }

    try{
        cntrISConta->deletarConta(cpfTeste);
    }
    catch(ErroPersistencia exp){
        cout << exp.getMensagem() << endl;
    }

    cout << "Conta deletada" << endl;
    cin;
    return;

}

void CntrISConta::criarConta(Conta contaTeste){

    ComandoCriarConta comando (contaTeste);

    comando.executar();

    return;

}

Conta CntrISConta::lerConta(CPF cpfTeste){

    ComandoLerConta comando (cpfTeste);
    Conta conta;

    comando.executar();

    conta = comando.getResultado();

    return conta;

}

void CntrISConta::atualizarConta(Conta contaTeste){

    ComandoEditarConta comando (contaTeste);

    comando.executar();

    return;

}

void CntrISConta::deletarConta(CPF *cpfTeste){

    ComandoDeletarConta comando(*cpfTeste);

    comando.executar();

    return;

}

//Metodos relacionados a titulos

bool CntrISInvestimentos::validaData(Data emissao,Data vencimento){
    
    if( stoi(emissao.getAno()) > stoi(vencimento.getAno()) ){
        return false;
    } else if( stoi(emissao.getMes()) > stoi(vencimento.getMes()) ){
        return false;
    } else if( stoi(emissao.getDia()) > stoi(vencimento.getDia()) ){
        return false;
    } else {
        return true;
    }

}

void CntrISInvestimentos::criarTitulo(Titulo tituloTeste){

    int numTitulos;
    bool validacaoData;

 ComandoCount counter ("titulos","WHERE cpf = '" + tituloTeste.getCpf().getCPF() + "'" );

    counter.executar();

    numTitulos = counter.getResultado();

    if(numTitulos > 4){
        throw(ErroPersistencia("Este cpf ja chegou ao limite de titulos"));
    }

    validacaoData = validaData(tituloTeste.getEmissao(),tituloTeste.getVencimento());

    if(validacaoData == false){
        throw(ErroPersistencia("Data de vencimento é interior à data de emissao"));
    }

   try{

    ComandoCriarTitulo comando (tituloTeste);
    comando.executar();
   }
   catch(ErroPersistencia exp){
        cout << exp.getMensagem() << endl;
   }

    return;

}

Titulo CntrISInvestimentos::lerTitulo(CodigoTitulo codigo){

    ComandoLerTitulo comando (codigo);
    Titulo titulo;

    comando.executar();

    titulo = comando.getResultado();

    return titulo;

}

void CntrISInvestimentos::deletarTitulo(CPF *cpf,CodigoTitulo codigo){

    Titulo tituloArmazenado;
    ComandoLerTitulo adquireTitulo (codigo);
    adquireTitulo.executar();
    tituloArmazenado = adquireTitulo.getResultado();

    if(tituloArmazenado.getCpf().getCPF() != cpf->getCPF()){
        throw(ErroPersistencia("Esse titulo nao esta vinculado a esta conta"));
    }

    ComandoDeletarTitulo comando ("WHERE codigo = '" + codigo.getCodigoTitulo() +"'");

    comando.executar();

    return;

}

void CntrISInvestimentos::atualizarTitulo(CPF *cpf, Titulo titulo){

    ComandoLerTitulo adquireTitulo (titulo.getCodigoTitulo());
    Titulo tituloArmazenado;
    adquireTitulo.executar();
    tituloArmazenado = adquireTitulo.getResultado();

    if(tituloArmazenado.getCpf().getCPF() != cpf->getCPF()){
        throw(ErroPersistencia("Esse titulo nao esta vinculado a esta conta"));
    }

    ComandoAtualizarTitulo comando (titulo);

    comando.executar();

    return;

}




