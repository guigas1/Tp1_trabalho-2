#include "unidadepersistencia.hpp"
#include "sqlite3.h"

list<ElementoResultado> ComandoSQL::listaResultado;


//Metodos de ErroPersistencia

ErroPersistencia::ErroPersistencia(string mensagem){
    this->mensagem = mensagem;
}

string ErroPersistencia::getMensagem() const{
    return this->mensagem;
}

//Metodos de ElementoResultado

void ElementoResultado::setNomeColuna(const string& nomeColuna) {
        this->nomeColuna = nomeColuna;
}

void ElementoResultado::setValorColuna(const string& valorColuna){
        this->valorColuna = valorColuna;
}

string ElementoResultado::getNomeColuna() const{
        return this->nomeColuna;
}

string ElementoResultado::getValorColuna() const{
        return this->valorColuna;
}

//Metodos de ComandoSQL

void ComandoSQL::conectar() {
      rc = sqlite3_open(nomeBancoDados, &bd);
      if( rc != SQLITE_OK )
        throw ErroPersistencia("Erro na conexao ao banco de dados");
}

void ComandoSQL::desconectar() {
      rc =  sqlite3_close(bd);
      if( rc != SQLITE_OK )
        throw ErroPersistencia("Erro na desconexao ao banco de dados");
}

void ComandoSQL::executar() {

        if(listaResultado.empty() == 0){
                listaResultado.clear();
        }

        conectar();
        rc = sqlite3_exec(bd, comandoSQL.c_str(), callback, 0, &mensagem);
        if(rc != SQLITE_OK){
                sqlite3_free(mensagem);
                desconectar();
                throw ErroPersistencia("Erro na execucao do comando SQL");
        }
        desconectar();
}

int ComandoSQL::callback(void *NotUsed, int argc, char **valorColuna, char **nomeColuna){
      NotUsed=0;
      ElementoResultado elemento;
      int i;
      for(i=0; i<argc; i++){
        elemento.setNomeColuna(nomeColuna[i]);
        elemento.setValorColuna(valorColuna[i] ? valorColuna[i]: "NULL");
        listaResultado.push_front(elemento);
      }
      return 0;
}

//ComandoCriarConta

ComandoCriarConta::ComandoCriarConta(Conta contaTeste){
    comandoSQL = "INSERT INTO contas(nome, cpf, senha) VALUES (";
    comandoSQL += "'" + contaTeste.getNome().getNome() + "', ";
    comandoSQL += "'" + contaTeste.getCpf().getCPF() + "', ";
    comandoSQL += "'" + contaTeste.getSenha().getSenha() + "')";
}

//ComandoLerConta

ComandoLerConta::ComandoLerConta(CPF cpfTeste){
        comandoSQL = "SELECT * FROM contas WHERE cpf = '";
        comandoSQL += cpfTeste.getCPF();
        comandoSQL += "';";
}

Conta ComandoLerConta::getResultado() {
        ElementoResultado resultado;
        Conta conta;

        //aquisicao de cpf
        if(listaResultado.empty()){
                throw ErroPersistencia("Lista de resultados vazia");
        }
        resultado = listaResultado.back();
        listaResultado.pop_back();
        conta.setCpf(CPF(resultado.getValorColuna()));

        //aquisicao de nome
        if(listaResultado.empty()){
                throw ErroPersistencia("Lista de resultados vazia");
        }
        resultado = listaResultado.back();
        listaResultado.pop_back();
        conta.setNome(Nome(resultado.getValorColuna()));

        //aquisicao de senha
        if(listaResultado.empty()){
                throw ErroPersistencia("Lista de resultados vazia");
        }
        resultado = listaResultado.back();
        listaResultado.pop_back();
        conta.setSenha(Senha(resultado.getValorColuna()));

        return conta;

}

//ComandoEditarConta

ComandoEditarConta::ComandoEditarConta(Conta contaTeste){
        comandoSQL = "UPDATE contas ";
        comandoSQL += "SET nome = '" + contaTeste.getNome().getNome();
        comandoSQL += "', senha = '" + contaTeste.getSenha().getSenha();
        comandoSQL += "' WHERE cpf = '" + contaTeste.getCpf().getCPF();
        comandoSQL += "';";
}

//ComandoDeletarConta

ComandoDeletarConta::ComandoDeletarConta(CPF cpfTeste){
        comandoSQL = "DELETE FROM contas WHERE cpf = '" + cpfTeste.getCPF();
        comandoSQL += "';";
}

//Comando count
ComandoCount::ComandoCount(string argumento){
        comandoSQL = "SELECT count(*) from ";
        comandoSQL += argumento;
        comandoSQL += ";";
}

ComandoCount::ComandoCount(string arg1, string arg2){
        comandoSQL = "SELECT COUNT(*) from ";
        comandoSQL += arg1 + " ";
        comandoSQL += arg2;
        comandoSQL += ";";
}

int ComandoCount::getResultado(){
        int number;
        ElementoResultado resultado;

        resultado = listaResultado.back();

        number = stoi(resultado.getValorColuna());

        return number;

}

//Comandos relacionados a titulos

ComandoCriarTitulo::ComandoCriarTitulo(Titulo tituloTeste){

        Conta conta;
        string cpf;

        ComandoLerConta comando (tituloTeste.getCpf());

        comando.executar();

        conta = comando.getResultado();

        comandoSQL = "INSERT INTO titulos(codigo,cpf,setor,emissao,vencimento,valor,emissor) VALUES ('";
        comandoSQL += tituloTeste.getCodigoTitulo().getCodigoTitulo() + "','";
        comandoSQL += tituloTeste.getCpf().getCPF() + "','";
        comandoSQL += tituloTeste.getSetor().getSetor() + "','";
        comandoSQL += tituloTeste.getEmissao().getData() + "','";
        comandoSQL += tituloTeste.getVencimento().getData() + "','";
        comandoSQL += to_string(tituloTeste.getValor().getDinheiro()) + "','";
        comandoSQL += conta.getNome().getNome() + "');";

}

ComandoLerTitulo::ComandoLerTitulo(CodigoTitulo codigo){
        comandoSQL = "SELECT * from titulos WHERE codigo = '";
        comandoSQL += codigo.getCodigoTitulo();
        comandoSQL += "';";
}

Titulo ComandoLerTitulo::getResultado(){
        ElementoResultado resultado;
        Titulo titulo;

        //aquisicao do codigo
        if(listaResultado.empty()){
                throw ErroPersistencia("Lista de resultados vazia");
        }
        resultado = listaResultado.back();
        listaResultado.pop_back();
        titulo.setCodigoTitulo(CodigoTitulo(resultado.getValorColuna()));

        //aquisicao de cpf
                if(listaResultado.empty()){
                throw ErroPersistencia("Lista de resultados vazia");
        }
        resultado = listaResultado.back();
        listaResultado.pop_back();
        titulo.setCpf(CPF(resultado.getValorColuna()));

        //aquisicao de setor
        if(listaResultado.empty()){
                throw ErroPersistencia("Lista de resultados vazia");
        }
        resultado = listaResultado.back();
        listaResultado.pop_back();
        titulo.setSetor(Setor(resultado.getValorColuna()));

        //aquisicao de emissao
        if(listaResultado.empty()){
                throw ErroPersistencia("Lista de resultados vazia");
        }
        resultado = listaResultado.back();
        listaResultado.pop_back();
        titulo.setEmissao(Data(resultado.getValorColuna()));

        //aquisicao de vencimento
        if(listaResultado.empty()){
                throw ErroPersistencia("Lista de resultados vazia");
        }
        resultado = listaResultado.back();
        listaResultado.pop_back();
        titulo.setVencimento(Data(resultado.getValorColuna()));

        //aquisicao de valor
        if(listaResultado.empty()){
                throw ErroPersistencia("Lista de resultados vazia");
        }
        resultado = listaResultado.back();
        listaResultado.pop_back();
        titulo.setValor(Dinheiro(stof(resultado.getValorColuna())));

        //aquisicao de emissor
        if(listaResultado.empty()){
                throw ErroPersistencia("Lista de resultados vazia");
        }
        resultado = listaResultado.back();
        listaResultado.pop_back();
        titulo.setEmissor(Nome(resultado.getValorColuna()));

        return titulo;

}

ComandoDeletarTitulo::ComandoDeletarTitulo(string arg){
        comandoSQL = "DELETE from titulos ";
        comandoSQL += arg;
        comandoSQL += ";";
}

ComandoAtualizarTitulo::ComandoAtualizarTitulo(Titulo titulo){
        comandoSQL = "UPDATE titulos ";
        comandoSQL += "SET setor = '" + titulo.getSetor().getSetor();
        comandoSQL += "', emissao = '" + titulo.getEmissao().getData();
        comandoSQL += "', vencimento = '" + titulo.getVencimento().getData();
        comandoSQL += "', valor = '" + to_string(titulo.getValor().getDinheiro());
        comandoSQL += "' WHERE codigo = '" + titulo.getCodigoTitulo().getCodigoTitulo();
        comandoSQL += "';";

}

