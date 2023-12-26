#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

struct tabela {
  string nome, pais;
  float tempoShow, custoShow;
  int numMembros;
};

void save(tabela *dados, int tamanho) {
  // passa os dados da tabela para o arquivo
  int i;
  ofstream arquivo("dados.csv");

  for (i = 0; i < tamanho; i++) {
    arquivo << dados[i].nome << ',';
    arquivo << dados[i].pais << ',';
    arquivo << dados[i].tempoShow << ',';
    arquivo << dados[i].custoShow << ',';
    arquivo << dados[i].numMembros << endl;
  }
}

tabela *expandir(tabela *dados, int &tamanho) {
  // expande o tamanho da tabela em 1 linha
  int i;
  tabela *novo = new tabela[tamanho + 1];
  for (i = 0; i < tamanho; i++) {
    novo[i].nome = dados[i].nome;
    novo[i].pais = dados[i].pais;
    novo[i].tempoShow = dados[i].tempoShow;
    novo[i].custoShow = dados[i].custoShow;
    novo[i].numMembros = dados[i].numMembros;
  }
  tamanho += 1;
  delete dados;

  return novo;
}

void inserir(tabela *&dados, int &tamanho) {
  int cont = 0, j = 0;
  // se houver alguma linha vaga, os dados serao inseridos nela
  // caso contrario, cria-se uma nova linha
  while (cont < 1 && j < tamanho) {
    if (dados[j].nome == "-1") {
      cont++;
      cout << "Informe o novo nome: ";
      getline(cin, dados[j].nome);
      cout << "Informe o novo pais: ";
      getline(cin, dados[j].pais);
      cout << "Informe o novo Tempo de Show: ";
      cin >> dados[j].tempoShow;
      cout << "Informe o novo Custo de Show: ";
      cin >> dados[j].custoShow;
      cout << "Informe o novo Numero de Integrantes: ";
      cin >> dados[j].numMembros;
      cout << endl << "Dados inseridos com Sucesso!";
    }
    j++;
  }
  if (cont == 0) {
    dados = expandir(dados, tamanho);

    cout << endl << "Informe o novo nome: ";
    getline(cin, dados[tamanho - 1].nome);
    cout << "Informe o novo pais: ";
    getline(cin, dados[tamanho - 1].pais);
    cout << "Informe o novo Tempo de Show: ";
    cin >> dados[tamanho - 1].tempoShow;
    cout << "Informe o novo Custo de Show: ";
    cin >> dados[tamanho - 1].custoShow;
    cout << "Informe o novo Numero de Integrantes: ";
    cin >> dados[tamanho - 1].numMembros;
    cout << endl << "Dados inseridos com sucesso!";
  }

  save(dados, tamanho);
}

void imprimirLinha(tabela *dados, int tamanho) {
  // Recebe um index do vetor e imprime os dados armazenados neste.

  int linha;
  cout << endl << "Informe a linha que deseja imprimir: ";
  cin >> linha;
  if (linha >= 0 and linha < tamanho) {
    cout << "Seguem os dados:" << endl;
    cout << "Banda: " << dados[linha].nome << endl;
    cout << "Pais: " << dados[linha].pais << endl;
    cout << "Tempo de Show: " << dados[linha].tempoShow << endl;
    cout << "Custo de Show: " << dados[linha].custoShow << endl;
    cout << "Numero de Integrantes: " << dados[linha].numMembros << endl;
  } else {
    cout << "LINHA INVALIDA!";
  }
}

void imprimirLparaL2(tabela *dados, int tamanho) {
  // Recebe um index do vetor e imprime os dados armazenados deste até um
  // segundo index recebido.

  int linha, linha2;
  cout << endl << "Informe de que linha deseja começar a imprimir: ";
  cin >> linha;
  cout << "Informe em qual linha deseja parar de imprimir: ";
  cin >> linha2;
  if ((linha >= 0 and linha < tamanho) and (linha2 >= 0 and linha2 < tamanho)) {

    int tanto = linha2 - linha;

    for (int i = 0; i <= tanto; i++) {
      cout << endl << "Seguem os dados:" << endl << endl;
      cout << "Banda: " << dados[linha].nome << endl;
      cout << "Pais: " << dados[linha].pais << endl;
      cout << "Tempo de Show: " << dados[linha].tempoShow << endl;
      cout << "Custo de Show: " << dados[linha].custoShow << endl;
      cout << "Numero de Integrantes: " << dados[linha].numMembros << endl;
      linha++;
    }
  } else {
    cout << endl << "LINHA(s) INVÁLIDA!";
  }
}

void remover(tabela *dados, int tamanho) {
  // marca a linha como removida alterando os dados para -1
  // exceto no campo custoShow, onde o valor e mais alto
  // para impedir que este interfira na ordenacao por preco
  string banda;
  int i, cont = 0;

  cout << endl << "Digite o nome da banda a ser removida: " << endl;
  getline(cin, banda);

  for (i = 0; i < tamanho; i++) {
    if (dados[i].nome == banda) {
      dados[i].nome = "-1";
      dados[i].pais = "-1";
      dados[i].tempoShow = -1.00;
      dados[i].custoShow = 10000;
      dados[i].numMembros = -1;
      cont++;
    }
  }

  if (cont > 0) {
    cout << endl << "REMOCAO CONCLUIDA" << endl;
  } else {
    cout << endl << "BANDA NAO ENCONTRADA" << endl;
  }
  save(dados, tamanho);
}

void buscaBanda(tabela *dados, int tamanho) {
  // Recebe um nome de banda e procura por ele no vetor para imprimir os dados
  // do memso.

  string nome;
  bool achado = false;
  getline(cin, nome);
  for (int i = 0; i < tamanho; i++) {
    if (nome == dados[i].nome) {
      cout << "BANDA ENCONTRADA!" << endl;
      cout << "Seguem os dados:" << endl;
      cout << dados[i].nome << endl;
      cout << dados[i].pais << endl;
      cout << dados[i].tempoShow << endl;
      cout << dados[i].custoShow << endl;
      cout << dados[i].numMembros << endl;
      achado = true;
    }
  }

  if (achado == false) {
    cout << endl << "BANDA NAO ENCONTRADA";
  }
}
void buscaPais(tabela *dados, int tamanho) {
  // busca por todas as bandas que são marcadas em um mesmo país e as imprime.
  string pais;
  getline(cin, pais);
  int cont = 0;
  for (int i = 0; i < tamanho; i++) {
    if (pais == dados[i].pais) {
      cont++;
    }
  }

  if (cont != 0) {
    cout << "O Pais possui banda(s)! " << endl << endl;
  } else {
    cout << "O Pais não possui bandas!" << endl;
  }
  tabela *bandasdoPais = new tabela[cont];
  int j = 0;

  for (int i = 0; i < tamanho; i++) {
    if (pais == dados[i].pais) {
      bandasdoPais[j].nome = dados[i].nome;
      bandasdoPais[j].pais = dados[i].pais;
      bandasdoPais[j].tempoShow = dados[i].tempoShow;
      bandasdoPais[j].custoShow = dados[i].custoShow;
      bandasdoPais[j].numMembros = dados[i].numMembros;
      j++;
    }
  }

  for (int i = 0; i < cont; i++) {
    cout << endl
         << "Seguem as informacoes das bandas referentes ao pais informado: "
         << endl;
    cout << "Nome: " << bandasdoPais[i].nome << endl;
    cout << "Pais: " << bandasdoPais[i].pais << endl;
    cout << "Tempo de Show: " << bandasdoPais[i].tempoShow << endl;
    cout << "Custo do Show: " << bandasdoPais[i].custoShow << endl;
    cout << "Numero de Membros: " << bandasdoPais[i].numMembros << endl;
    cout << endl;
  }

  delete[] bandasdoPais;
}

void ordenaPreco(tabela *dados, int tam) {
  tabela *ordenado = new tabela[tam];
  int i, j, ind;

  // Copiar os dados para a tabela ordenada
  for (i = 0; i < tam; i++) {
    ordenado[i].nome = dados[i].nome;
    ordenado[i].pais = dados[i].pais;
    ordenado[i].tempoShow = dados[i].tempoShow;
    ordenado[i].custoShow = dados[i].custoShow;
    ordenado[i].numMembros = dados[i].numMembros;
  }

  for (i = 0; i < tam; i++) {
    // Localizar o menor custoShow a partir do índice atual
    float menor = ordenado[i].custoShow;
    ind = i;

    for (j = i + 1; j < tam; j++) {
      if (ordenado[j].custoShow < menor) {
        menor = ordenado[j].custoShow;
        ind = j;
      }
    }

    // Armazenar os dados do menor custoShow na tabela ordenada
    tabela temp = ordenado[i];
    ordenado[i] = ordenado[ind];
    ordenado[ind] = temp;
  }

  // Copiar os dados ordenados de volta para a tabela original
  for (i = 0; i < tam; i++) {
    dados[i] = ordenado[i];
  }

  delete[] ordenado;
  cout << "ORDENACAO CONCLUIDA" << endl;
  save(dados, tam);
}

void ordenaAlfab(tabela *dados, int tam) {
  tabela *ordenado = new tabela[tam];
  int i, j, ind;

  // Copiar os dados para a tabela ordenada
  for (i = 0; i < tam; i++) {
    ordenado[i].nome = dados[i].nome;
    ordenado[i].pais = dados[i].pais;
    ordenado[i].tempoShow = dados[i].tempoShow;
    ordenado[i].custoShow = dados[i].custoShow;
    ordenado[i].numMembros = dados[i].numMembros;
  }

  for (i = 0; i < tam; i++) {
    // Localizar a primeira letra do alfabeto
    string primeiroTermo = ordenado[i].nome;
    ind = i;

    for (j = i + 1; j < tam; j++) {
      if (ordenado[j].nome < ordenado[ind].nome) {
        primeiroTermo = ordenado[j].nome;
        ind = j;
      }
    }

    // Armazenar os dados do menor custoShow na tabela ordenada
    tabela temp = ordenado[i];
    ordenado[i] = ordenado[ind];
    ordenado[ind] = temp;
  }

  // Copiar os dados ordenados de volta para a tabela original
  for (i = 0; i < tam; i++) {
    dados[i] = ordenado[i];
  }

  delete[] ordenado;
  cout << "ORDENACAO CONCLUIDA" << endl;
  save(dados, tam);
}

void imprimir(tabela *dados, int tamanho) {
  // exibe a tabela inteira
  int i;
  for (i = 0; i < tamanho; i++) {
    cout << "Nome: " << dados[i].nome << endl;
    cout << "Pais: " << dados[i].pais << endl;
    cout << "Tempo de Show: " << dados[i].tempoShow << endl;
    cout << "Custo do Show: " << dados[i].custoShow << endl;
    cout << "Numero de Membros: " << dados[i].numMembros << endl;
    cout << endl;
  }
}

void alterar(tabela *dados, int tamanho) {
  // Recebe uma banda e procura por ela no vetor, caso seja encontrada o usuário
  // recebe opções para alterar os dados da banda escolhida
  string modnome, modpais;
  int modint;
  float modtempo, modcusto;
  bool achado = false;
  string mod, banda;

  cout << "Informe a banda que deseja modificar: ";
  getline(cin, banda);

  for (int i = 0; i < tamanho; i++) {
    if (banda == dados[i].nome) {
      achado = true;

      cout << endl
           << "Informe o dado da banda que voce deseja alterar: " << endl;
      cout << "- Nome" << endl;
      cout << "- Pais" << endl;
      cout << "- Tempo" << endl;
      cout << "- Custo" << endl;
      cout << "- Integrantes" << endl;
      cout << "- Tudo " << endl;

      cin >> mod;
      cin.ignore();
      if (mod == "Nome") {
        cout << "Informe o novo nome: ";
        getline(cin, modnome);
        dados[i].nome = modnome;
        cout << endl << "Nome modificado com Sucesso!" << endl;
      } else if (mod == "Pais") {
        cout << "Informe o novo pais: ";
        getline(cin, modpais);
        dados[i].pais = modpais;
        cout << endl << "Pais modificado com Sucesso!" << endl;
      } else if (mod == "Tempo") {
        cout << "Informe o novo Tempo de Show: ";
        cin >> modtempo;
        cin.ignore();
        dados[i].tempoShow = modtempo;
        cout << endl << "Tempo de Show modificado com Sucesso!" << endl;
      } else if (mod == "Custo") {
        cout << "Informe o novo Custo de Show: ";
        cin >> modcusto;
        cin.ignore();
        dados[i].custoShow = modcusto;
        cout << endl << "Custo de Show modificado com Sucesso!" << endl;
      } else if (mod == "Integrantes") {
        cout << "Informe o novo Numero de Integrantes: ";
        cin >> modint;
        cin.ignore();
        dados[i].numMembros = modint;
        cout << endl << "Numero de Integrantes modificado com Sucesso!" << endl;
      } else if (mod == "Tudo") {
        cout << "Informe o novo nome: ";
        getline(cin, modnome);
        dados[i].nome = modnome;

        cout << "Informe o novo pais: ";
        getline(cin, modpais);
        dados[i].pais = modpais;

        cout << "Informe o novo Tempo de Show: ";
        cin >> modtempo;
        cin.ignore();
        dados[i].tempoShow = modtempo;

        cout << "Informe o novo Custo de Show: ";
        cin >> modcusto;
        cin.ignore();
        dados[i].custoShow = modcusto;

        cout << "Informe o novo Numero de Integrantes: ";
        cin >> modint;
        cin.ignore();
        dados[i].numMembros = modint;

        cout << endl << "Dados modificados com Sucesso!" << endl;
      } else {
        cout << endl << "COMANDO NAO IDENTIFICADO!" << endl;
      }
    }
  }

  if (!achado) {
    cout << endl << "BANDA NAO ENCONTRADA" << endl;
  } else {
    save(dados, tamanho);
  }
}

void ajuda() {
  // exibe os comandos
  cout << "Olá, segue a lista de comandos operacionais disponíveis em nosso código: "<< endl << endl;
  cout << "- 'ajuda', para exibir os comandos." << endl;
  cout << "- 'inserir', para inserir novos dados na tabela." << endl;
  cout << "- 'remover', para remover dados da tabela." << endl;
  cout << "- 'buscar banda', para buscar as informações de uma banda." << endl;
  cout << "- 'buscar pais', para buscar os dados das bandas de um país." << endl;
  cout << "- 'imprimir', para imprimir toda a tabela." << endl;
  cout << "- 'imprimir trecho', para imprimir um intervalo de linhas." << endl;
  cout << "- 'imprimir linha', para imprimir uma linha específica." << endl;
  cout << "- 'alterar', para alterar os dados de uma linha específica." << endl;
  cout << "- 'ordenar por preco', para alterar a apresentação da tabela, indo da com menor custo para a com maior custo." << endl;
  cout << "- 'ordenar por alfabeto', para alterar a apresentação da tabela, colocando ela em ordem alfabetica."<< endl;
  cout << "- 'finalizar', para finalizar o programa." << endl;
}

int main() {
  string comando;
  int tam = 100;

  tabela *dados = new tabela[tam];

  int i;
  char lixo;

  ifstream arquivo("dados.csv");

  for (i = 0; i < tam; i++) {
    getline(arquivo, dados[i].nome, ',');
    getline(arquivo, dados[i].pais, ',');
    arquivo >> dados[i].tempoShow;
    arquivo >> lixo;
    arquivo >> dados[i].custoShow;
    arquivo >> lixo;
    arquivo >> dados[i].numMembros;
    arquivo.ignore();
  }

  arquivo.close();

  ajuda();

  do {
    cout << endl << "INSIRA O COMANDO DESEJADO: " << endl;
    getline(cin, comando);

    if (comando == "ajuda") {
      ajuda();
    }

    else if (comando == "inserir") {
      inserir(dados, tam);
    }

    if (comando == "remover") {
      remover(dados, tam);
    }

    else if (comando == "imprimir linha") {
      imprimirLinha(dados, tam);
    }

    else if (comando == "imprimir") {
      imprimir(dados, tam);
    } else if (comando == "buscar banda") {
      string nome;
      cout << endl << "Informe o nome da banda procurada: ";

      buscaBanda(dados, tam);
    }

    else if (comando == "buscar pais") {
      string pais;
      cout << endl << "Informe o pais procurado: ";

      buscaPais(dados, tam);

    }

    else if (comando == "imprimir trecho") {
      imprimirLparaL2(dados, tam);
    }

    else if (comando == "alterar") {

      alterar(dados, tam);
    }

    else if (comando == "ordenar por preco") {
      ordenaPreco(dados, tam);
    } else if (comando == "ordenar por alfabeto") {
      ordenaAlfab(dados, tam);
    } else if (comando != "finalizar") {
      cout << endl << "COMANDO INVALIDO" << endl;
    }

  } while (comando != "finalizar");

  return 0;
}
