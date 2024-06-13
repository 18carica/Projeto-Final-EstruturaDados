// Programas.cpp

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <locale.h>
//using namespace std;

// PILHA E FILA
int Pilha[50];
int tamanhoPilha = 0;
int Fila[50];
int tamanhoFila = 0;

// JOGO DA VELHA
bool jogador2 = false;
char JogadorAtual = 'X';
int tabuleiro[3][3];
int countJogadas = 0;
char Nome1[20];
char Nome2[20];

// BATALHA NAVAL
bool BNjogador2 = false;
int BNJogadorAtual = 1;
int tabJog1Navios[6][6];
int tabJog1Jogadas[6][6];
int tabJog2Navios[6][6];
int tabJog2Jogadas[6][6];
char BNNome1[20];
char BNNome2[20];
int QuantNavJ1 = 0;
int QuantNavJ2 = 0;

#define OCUPADO -3
#define FOGO -2
#define NADA -1
#define AGUA 0
#define Navio1 1
#define Navio2 2
#define Navio3 3
#define Navio4 4

int J1Nav2 = 0; int J1Nav3 = 0; int J1Nav4 = 0;
int J2Nav2 = 0; int J2Nav3 = 0; int J2Nav4 = 0;

// PONTEIROS
int A, B, C, D, E, F, G, H, I, J;
int vetor[10];
int matriz[2][5];

// ------------------------------------- GRAFOS ---------------------------------------------
class No {
public:
    std::string nome;
    std::vector<std::string> arestas;

    // Construtor padrão
    No() : nome("") {}

    // Construtor com nome
    No(const std::string& nome) : nome(nome) {}
};

class Grafo {
private:
    std::map<std::string, No> nos;

public:
    void adicionarNo(const std::string& nomeNo) {
        if (nos.find(nomeNo) == nos.end()) {
            nos[nomeNo] = No(nomeNo);
            std::cout << "Nó '" << nomeNo << "' adicionado com sucesso.\n";
        } else {
            std::cout << "Nó '" << nomeNo << "' já existe.\n";
        }
    }

    void adicionarAresta(const std::string& deNo, const std::string& paraNo) {
        if (nos.find(deNo) != nos.end() && nos.find(paraNo) != nos.end()) {
            nos[deNo].arestas.push_back(paraNo);
            nos[paraNo].arestas.push_back(deNo);
            std::cout << "Aresta entre '" << deNo << "' e '" << paraNo << "' adicionada com sucesso.\n";
        } else {
            std::cout << "Um ou ambos os nós não existem.\n";
        }
    }

    void exibirGrafo() const {
        std::cout << "\nTabela do Grafo:\n";
        std::cout << "Nó\tArestas\t\tVértices\n";
        std::cout << "-------------------------------------\n";
        for (const auto& par : nos) {
            const No& no = par.second;
            std::cout << no.nome << "\t";
            std::cout << no.arestas.size() << "\t\t";
            for (const std::string& aresta : no.arestas) {
                std::cout << aresta << " ";
            }
            std::cout << "\n";
        }
    }
};

int OpcaoGrafos(){
    setlocale(LC_ALL, "Portuguese");

    Grafo grafo;

    int n;
    std::string nomeNo, deNo, paraNo;

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Adicionar Nó\n2. Adicionar Aresta\n";
        std::cout << "3. Exibir Grafo\n4. Sair\n";
        std::cout << "\nEscolha uma opção: ";
        std::cin >> n;

        switch (n) {
        case 1:
            std::cout << "Digite o nome do nó: ";
            std::cin >> nomeNo;
            grafo.adicionarNo(nomeNo);
            break;
        case 2:
            std::cout << "Digite o nó de origem: ";
            std::cin >> deNo;
            std::cout << "Digite o nó de destino: ";
            std::cin >> paraNo;
            grafo.adicionarAresta(deNo, paraNo);
            break;
        case 3:
            grafo.exibirGrafo();
            break;
        case 4:
            std::cout << "Saindo...\n";
            break;
        default:
            std::cout << "Opção inválida. Tente novamente.\n";
        }
    } while (n != 4);
    return 0;
}

// ------------------------------------- LISTA -----------------------------------------------
// DEFINIÇÃO DO STRUCT DO NÓ
struct NoLista{
    int valor;
    NoLista* prox;  // anterior
};

// TROCA OS DADOS ENTRE DOIS NÓS
void TrocaNos(NoLista* a, NoLista* b) {
    int temp = a->valor;
    a->valor = b->valor;
    b->valor = temp;
}

// ORDENA DE FORMA DECRESCENTE
void OrdDESC(NoLista*& temp){
    if (temp == nullptr)
        return;

    NoLista* atual = temp;
    NoLista* tp = nullptr;

    std::cout << "\nLista ordenada decrescente:\n";
    while (atual != nullptr){
        tp = atual->prox;
        while (tp != nullptr){
            if (atual->valor < tp->valor)
                TrocaNos(atual, tp);
            tp = tp->prox;
        }
        std::cout << "\nEndereco: " << atual << "\nValor: " << atual->valor;
        atual = atual->prox;
    }
    std::cout << "\n";
}

// ORDENA DE FORMA CRESCENTE
void OrdASC(NoLista*& temp){
    if (temp == nullptr)
        return;

    NoLista* atual = temp;
    NoLista* tp = nullptr;

    std::cout << "\nLista ordenada decrescente:\n";
    while (atual != nullptr){
        tp = atual->prox;
        while (tp != nullptr){
            if (atual->valor > tp->valor)
                TrocaNos(atual, tp);
            tp = tp->prox;
        }
        std::cout << "\nEndereco: " << atual << "\nValor: " << atual->valor;
        atual = atual->prox;
    }
    std::cout << "\n";
}

// REMOVE ITEM DA LISTA
void RemItem(NoLista*& temp, int num){
    if (temp == nullptr) {
        std::cout << "A lista está vazia." << std::endl;
        return;
    }

    if (temp->valor == num){
        NoLista* tp = temp;
        temp = temp->prox;
        delete tp;
        return;
    }

    NoLista* tp = temp;
    NoLista* prev = nullptr;

    while (tp != nullptr && tp->valor != num){
        prev = tp;
        tp = tp->prox;
    }

    if (tp == nullptr){
        std::cout << "Valor " << num << " não encontrado na lista." << std::endl;
        return;
    }

    prev->prox = tp->prox;
    delete tp;
}

// ADICIONA ITEM NA LISTA
void AddItem(int num, NoLista*& temp){
    NoLista* newNo = new NoLista(); // cria um novo nó
    newNo->valor = num;   // atribui o valor de "num" para "valor" do struct
    newNo->prox = nullptr;// atrubui o endereço atual para o prox

    if (temp == nullptr)
        temp = newNo;
    else{
        NoLista* tp = temp;
        while (tp->prox != nullptr)
            tp = tp->prox;
        tp->prox = newNo;
    }
}

// MOSTRA TODOS OS ITENS DA LISTA
void MostrarLista(NoLista* temp){
    if (temp == nullptr){
        std::cout << "A lista está vazia." << std::endl;
        return;
    }

    while (temp != nullptr){
        std::cout << "\nEndereco: " << temp << "\nValor: " << temp->valor;
        temp = temp->prox;
    }
    std::cout << std::endl;
}

// LIBERA O ESPAÇO CRIADO PELA LISTA DA MEMÓRIA
void DeleteLista(NoLista*& temp){
    while (temp != nullptr){
        NoLista* del = temp;
        temp = temp->prox;
        delete del;
    }
    std::cout << "\nLista deletada..." << std::endl;
}

void MenuLista(){
    std::cout << std::endl;
    std::cout << "____ MENU LISTA ____" << std::endl;
    std::cout << "(1) Adicionar item \n(2) Mostrar Lista" << std::endl;
    std::cout << "(3) Remover Item \n(4) Ordenar ASC" << std::endl;
    std::cout << "(5) Ordenar DESC \n(0) SAIR" << std::endl;
}

int OpcaoLista(){
    MenuLista();

    NoLista* temp = nullptr; // inicializando como endereço vazio

    int n, num = 0;

    while (true){
        std::cout << "\nESCOLHA UMA OPCAO: ";
        std::cin >> n;

        switch (n){
            case 1:
                std::cout << "\nDigite um numero a ser adicionado: ";
                std::cin >> num;
                AddItem(num, temp);
                MenuLista();
                break;
            case 2:
                MostrarLista(temp);
                MenuLista();
                break;
            case 3:
                std::cout << "\nDigite um numero a ser removido: ";
                std::cin >> num;
                RemItem(temp, num);
                MenuLista();
                break;
            case 4:
                OrdASC(temp);
                MenuLista();
                break;
            case 5:
                OrdDESC(temp);
                MenuLista();
                break;
            case 0:
                std::cout << "Voltando ao Menu Principal..." << std::endl;
                DeleteLista(temp);
                return 0;
            default:
                std::cout << "Opcao invalida" << std::endl;
                MenuLista();
        }
    }

    return 0;
}

// ------------------------------------ PONTEIROS ---------------------------------------------
int ExibirDados(int n){
    switch(n){
    case 1:
        std::cout << std::endl;
        std::cout << "A: Endereco " << &A << ", conteudo: " << A << std::endl;
        std::cout << "B: Endereco " << &B << ", conteudo: " << B << std::endl;
        std::cout << "C: Endereco " << &C << ", conteudo: " << C << std::endl;
        std::cout << "D: Endereco " << &D << ", conteudo: " << D << std::endl;
        std::cout << "E: Endereco " << &E << ", conteudo: " << E << std::endl;
        std::cout << "F: Endereco " << &F << ", conteudo: " << F << std::endl;
        std::cout << "G: Endereco " << &G << ", conteudo: " << G << std::endl;
        std::cout << "H: Endereco " << &H << ", conteudo: " << H << std::endl;
        std::cout << "I: Endereco " << &I << ", conteudo: " << I << std::endl;
        std::cout << "J: Endereco " << &J << ", conteudo: " << J << std::endl;
        break;
    case 2:
        std::cout << std::endl;
        for (int i = 0; i < 10; ++i){
            std::cout << "A posicao " << i+1 << ": Endereco " << &vetor[i] << ", conteudo: " << vetor[i] << std::endl;
        }
        break;
    case 3:
        std::cout << std::endl;
        for (int i = 0; i < 2; i++){
            for (int j = 0; j < 5; j++){
                std::cout << "A posicao " << i+1 << " e " << j+1 << " : Endereco " << &matriz[i][j] << ", conteudo: " << matriz[i][j] << std::endl;
            }
        }
        break;
    default:
        std::cout << "\nERRO AO EXIBIR" << std::endl;
    }

    return 0;
}

int Ponteiro1(){
    std::cout << "Endereco e conteudo das variaveis ANTES de serem inicializadas." << std::endl;
    ExibirDados(1);

    std::cout << "\nAgora, insira os valores para as dez variaveis: " << std::endl;
    std::cout << "\nInsira o valor para o A: ";
    std::cin >> A;
    std::cout << "\nInsira o valor para o B: ";
    std::cin >> B;
    std::cout << "\nInsira o valor para o C: ";
    std::cin >> C;
    std::cout << "\nInsira o valor para o D: ";
    std::cin >> D;
    std::cout << "\nInsira o valor para o E: ";
    std::cin >> E;
    std::cout << "\nInsira o valor para o F: ";
    std::cin >> F;
    std::cout << "\nInsira o valor para o G: ";
    std::cin >> G;
    std::cout << "\nInsira o valor para o H: ";
    std::cin >> H;
    std::cout << "\nInsira o valor para o I: ";
    std::cin >> I;
    std::cout << "\nInsira o valor para o J: ";
    std::cin >> J;
    std::cout << std::endl;

    std::cout << "Endereco e conteudo das variaveis DEPOIS de serem inicializadas." << std::endl;
    ExibirDados(1);

    return 0;
}

int Ponteiro2(){
    std::cout << "Endereco e conteudo das posicoes do vetor ANTES de serem inicializadas." << std::endl;
    ExibirDados(2);

    std::cout << "\nAgora, insira os valores para as dez posicoes do vetor : " << std::endl;

    for (int i = 0; i < 10; ++i){
        std::cout << "\nInsira o valor para a posicao " << i+1 <<": ";
        std::cin >> vetor[i];
    }

    std::cout << std::endl;

    std::cout << "Endereco e conteudo das posicoes do vetor DEPOIS de serem inicializadas." << std::endl;
    ExibirDados(2);

    return 0;
}

int Ponteiro3(){
    std::cout << "Endereco e conteudo das posicoes da matriz ANTES de serem inicializadas." << std::endl;
    ExibirDados(3);

    std::cout << "\nAgora, insira os valores para as dez posicoes do vetor : " << std::endl;

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 5; j++){
            std::cout << "\nInsira o valor para a posicao " << i+1 << " " << j+1 <<": ";
            std::cin >> matriz[i][j];
        }
    }

    std::cout << "Endereco e conteudo das posicoes da matriz DEPOIS de serem inicializadas." << std::endl;
    ExibirDados(3);

    return 0;
}

void MenuPonteiros(){
    std::cout << std::endl;
    std::cout << "____ MENU PONTEIROS ____" << std::endl;
    std::cout << "(1) PONTEIRO 1 \n(2) PONTEIRO 2 \n(3) PONTEIRO 3" << std::endl;
    std::cout << "(0) SAIR" << std::endl;
}

int OpcaoPonteiros(void){
    MenuPonteiros();

    int n = 0;
    while (true){
        std::cout << "\nESCOLHA UMA OPCAO: ";
        std::cin >> n;

        switch (n){
            case 1:
                Ponteiro1();
                MenuPonteiros();
                break;
            case 2:
                Ponteiro2();
                MenuPonteiros();
                break;
            case 3:
                Ponteiro3();
                MenuPonteiros();
                break;
            case 0:
                std::cout << "Voltando ao Menu Principal..." << std::endl;
                return 0;
            default:
                std::cout << "Opcao invalida" << std::endl;
                MenuPonteiros();
        }
    }

    return 0;
}

// ------------------------------------ BATALHA NAVAL -----------------------------------------
int GuardarInfoJogadas(){
  int infoPos = 0;

  for (int i = 0; i < 6; ++i){
    for (int j = 0; j < 6; ++j){

      if (BNJogadorAtual == 1){

        if (tabJog1Jogadas[i][j] == OCUPADO){
          if (tabJog2Navios[i][j] != NADA){
            infoPos = tabJog2Navios[i][j];

            switch(infoPos){
            case 1:
              tabJog1Jogadas[i][j] = FOGO;
              QuantNavJ2--;
              tabJog2Navios[i][j] = FOGO;
              std::cout << "\n\nNavio tipo 1 do jogador 2 foi destruido!\n";
              break;
            case 2:
              tabJog1Jogadas[i][j] = FOGO;
              QuantNavJ2--;
              tabJog2Navios[i][j] = FOGO;
              J2Nav2++;
              if ((J2Nav2 % 2) == 0)
                std::cout << "\n\nNavio tipo 2 do jogador 2 foi destruido!\n";
              break;
            case 3:
              tabJog1Jogadas[i][j] = FOGO;
              QuantNavJ2--;
              tabJog2Navios[i][j] = FOGO;
              J2Nav3++;
              if ((J2Nav3 % 3) == 0)
                std::cout << "\n\nNavio tipo 3 do jogador 2 foi destruido!\n";
              break;
            case 4:
              tabJog1Jogadas[i][j] = FOGO;
              QuantNavJ2--;
              tabJog2Navios[i][j] = FOGO;
              J2Nav4++;
              if ((J2Nav4 % 4) == 0)
                std::cout << "\n\nNavio tipo 4 do jogador 2 foi destruido!\n";
              break;
            default:
              tabJog1Jogadas[i][j] = AGUA;
              tabJog2Navios[i][j] = AGUA;
            }
          }
          else{
            tabJog1Jogadas[i][j] = AGUA;
            tabJog2Navios[i][j] = AGUA;
          }
        }
      }
      else{

        if (tabJog2Jogadas[i][j] == OCUPADO){
          if (tabJog1Navios[i][j] != NADA){
            infoPos = tabJog1Navios[i][j];

            switch(infoPos){
            case 1:
              tabJog2Jogadas[i][j] = FOGO;
              QuantNavJ1--;
              tabJog1Navios[i][j] = FOGO;
              std::cout << "\n\nNavio tipo 1 do jogador 1 foi destruido!\n";
              break;
            case 2:
              tabJog2Jogadas[i][j] = FOGO;
              QuantNavJ1--;
              tabJog1Navios[i][j] = FOGO;
              J1Nav2++;
              if ((J1Nav2 % 2) == 0)
                std::cout << "\n\nNavio tipo 2 do jogador 1 foi destruido!\n";
              break;
            case 3:
              tabJog2Jogadas[i][j] = FOGO;
              QuantNavJ1--;
              tabJog1Navios[i][j] = FOGO;
              J1Nav3++;
              if ((J1Nav3 % 3) == 0)
                std::cout << "\n\nNavio tipo 3 do jogador 1 foi destruido!\n";
              break;
            case 4:
              tabJog2Jogadas[i][j] = FOGO;
              QuantNavJ1--;
              tabJog1Navios[i][j] = FOGO;
              J1Nav4++;
              if ((J1Nav4 % 4) == 0)
                std::cout << "\n\nNavio tipo 4 do jogador 1 foi destruido!\n";
              break;
            default:
              tabJog2Jogadas[i][j] = AGUA;
              tabJog1Navios[i][j] = AGUA;
            }
          }
          else{
            tabJog2Jogadas[i][j] = AGUA;
            tabJog1Navios[i][j] = AGUA;
          }
        }
      }
    }
  }
  return 0;
}

int checkPosiJogadas(int l, int c){
  if (BNJogadorAtual == 1){
    if (tabJog1Jogadas[l][c] != NADA){
      std::cout << "\nPosicao OCUPADA. Tente novamente." << std::endl;
      return 0;
    }
    else{
      tabJog1Jogadas[l][c] = OCUPADO;
      return 1;
    }
  }
  else{
    if (tabJog2Jogadas[l][c] != NADA){
      std::cout << "\nPosicao OCUPADA. Tente novamente." << std::endl;
      return 0;
    }
    else{
      tabJog2Jogadas[l][c] = OCUPADO;
      return 1;
    }
  }
}

int RegistrarJogadas(){
  int l = 0; // variavel da linha
  int c = 0; // variavel da coluna
  int x = 0; // variavel temporaria

  do{
    while (x < 1 || x > 6){
      std::cout << "\nDigite a linha: ";
      std::cin >> x;
      if (x < 1 || x > 6 || std::cin.fail())
        std::cout << "\nPosicao invalida. Tente novamente." << std::endl;
      else{
        l = x - 1;
        break;
      }
    }

    x = 0;

    while(x < 1 || x > 6){
      std::cout << "\nDigite a coluna: ";
      std::cin >> x;
      if (x < 1 || x > 6 || std::cin.fail())
        std::cout << "\nPosicao invalida. Tente novamente." << std::endl;
      else{
        c = x - 1;
        break;
      }
    }

  }while (!(checkPosiJogadas(l,c)));

  return 0;
}

int LimparTabuleiros(){
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j){
      tabJog1Navios[i][j] = NADA;
      tabJog1Jogadas[i][j] = NADA;
      tabJog2Navios[i][j] = NADA;
      tabJog2Jogadas[i][j] = NADA;
    }
  }

  return 0;
}

int BNCheckVencedor(){
  if (QuantNavJ2 == 0){
    std::cout << "\nTODOS OS NAVIOS DO JOGADOR 2 FORAM DESTRUIDOS!\n";
    std::cout << "O jogador " << BNNome1 << " VENCEU!!\n\n";

    return 1;
  }
  else if(QuantNavJ1 == 0){
    std::cout << "\nTODOS OS NAVIOS DO JOGADOR 1 FORAM DESTRUIDOS!\n";
    std::cout << "O jogador " << BNNome2 << " VENCEU!!\n\n";

    return 1;
  }
  else
    return 0;
}

int MostrarTabuleiros(){
  if (BNJogadorAtual == 1){
    std::cout << "\nNavios do Jogador 1: " << BNNome1 << std::endl;
    std::cout << "\n  1 2 3 4 5 6\n";

    for (int i = 0; i < 6; ++i){
      std::cout << i + 1 << " ";
      for (int j = 0; j < 6; ++j){

        if (tabJog1Navios[i][j] == NADA)
          std::cout << "  ";
        else if (tabJog1Navios[i][j] == AGUA)
          std::cout << "O ";
        else if (tabJog1Navios[i][j] == FOGO)
          std::cout << "X ";
        else if (tabJog1Navios[i][j] == Navio1)
          std::cout << "1 ";
        else if (tabJog1Navios[i][j] == Navio2)
          std::cout << "2 ";
        else if (tabJog1Navios[i][j] == Navio3)
          std::cout << "3 ";
        else if (tabJog1Navios[i][j] == Navio4)
          std::cout << "4 ";
      }
      std::cout << "\n";
    }
    std::cout << std::endl;
    std::cout << "\nJogadas disponiveis"<< std::endl;
    std::cout << "\n  1 2 3 4 5 6\n";

    for (int i = 0; i < 6; ++i){
      std::cout << i + 1 << " ";
      for (int j = 0; j < 6; ++j){

        if (tabJog1Jogadas[i][j] == NADA)
          std::cout << "  ";
        else if (tabJog1Jogadas[i][j] == AGUA)
          std::cout << "O ";
        else if (tabJog1Jogadas[i][j] == FOGO)
          std::cout << "X ";
      }
      std::cout << "\n";
    }
    std::cout << std::endl;
  }
  else{
    std::cout << "\nNavios do Jogador 2: " << BNNome2 << std::endl;
    std::cout << "\n  1 2 3 4 5 6\n";

    for (int i = 0; i < 6; ++i){
      std::cout << i + 1 << " ";
      for (int j = 0; j < 6; ++j){

        if (tabJog2Navios[i][j] == NADA)
          std::cout << "  ";
        else if (tabJog2Navios[i][j] == AGUA)
          std::cout << "O ";
        else if (tabJog2Navios[i][j] == FOGO)
          std::cout << "X ";
        else if (tabJog2Navios[i][j] == Navio1)
          std::cout << "1 ";
        else if (tabJog2Navios[i][j] == Navio2)
          std::cout << "2 ";
        else if (tabJog2Navios[i][j] == Navio3)
          std::cout << "3 ";
        else if (tabJog2Navios[i][j] == Navio4)
          std::cout << "4 ";
      }
      std::cout << "\n";
    }
    std::cout << std::endl;
    std::cout << "\nJogadas disponiveis"<< std::endl;
    std::cout << "\n  1 2 3 4 5 6\n";

    for (int i = 0; i < 6; ++i){
      std::cout << i + 1 << " ";
      for (int j = 0; j < 6; ++j){

        if (tabJog2Jogadas[i][j] == NADA)
          std::cout << "  ";
        else if (tabJog2Jogadas[i][j] == AGUA)
          std::cout << "O ";
        else if (tabJog2Jogadas[i][j] == FOGO)
          std::cout << "X ";
      }
      std::cout << "\n";
    }
    std::cout << std::endl;
  }

  return 0;
}

int MostrarTabInicio(){
  if (BNJogadorAtual == 1){
    std::cout << "\nNavios do Jogador 1: " << BNNome1 << std::endl;
    std::cout << "\n  1 2 3 4 5 6\n";

    for (int i = 0; i < 6; ++i){
      std::cout << i + 1 << " ";
      for (int j = 0; j < 6; ++j){

        if (tabJog1Navios[i][j] == NADA)
          std::cout << "  ";
        else if (tabJog1Navios[i][j] == Navio1)
          std::cout << "1 ";
        else if (tabJog1Navios[i][j] == Navio2)
          std::cout << "2 ";
        else if (tabJog1Navios[i][j] == Navio3)
          std::cout << "3 ";
        else if (tabJog1Navios[i][j] == Navio4)
          std::cout << "4 ";
      }
      std::cout << "\n";
    }
  }
  if (BNJogadorAtual == 2 && BNjogador2 == true){
    std::cout << "\nNavios do Jogador 2: " << BNNome2 << std::endl;
    std::cout << "\n  1 2 3 4 5 6\n";

    for (int i = 0; i < 6; ++i){
      std::cout << i + 1 << " ";
      for (int j = 0; j < 6; ++j){

        if (tabJog2Navios[i][j] == NADA)
          std::cout << "  ";
        else if (tabJog2Navios[i][j] == Navio1)
          std::cout << "1 ";
        else if (tabJog2Navios[i][j] == Navio2)
          std::cout << "2 ";
        else if (tabJog2Navios[i][j] == Navio3)
          std::cout << "3 ";
        else if (tabJog2Navios[i][j] == Navio4)
          std::cout << "4 ";
      }
      std::cout << "\n";
    }
  }
  return 0;
}

int checkPosiPecas(int l, int c){
  if (BNJogadorAtual == 1){
    if (tabJog1Navios[l][c] != NADA){
      std::cout << "\nPosicao OCUPADA. Tente novamente." << std::endl;
      return 0;
    }
    else{
      return 1;
    }
  }
  else{
    if (tabJog2Navios[l][c] != NADA){
      std::cout << "\nPosicao OCUPADA. Tente novamente." << std::endl;
      return 0;
    }
    else{
      return 1;
    }
  }
}

int RegistrarPecas(int n){
  int l = 0; // variavel da linha
  int c = 0; // variavel da coluna
  int x = 0; // variavel temporaria

  std::cout << "\nEscolha a posicao inicial da peca:\n";

  do{
    while (x < 1 || x > 6){
      std::cout << "\nDigite a linha: ";
      std::cin >> x;
      if (x < 1 || x > 6 || std::cin.fail())
        std::cout << "\nPosicao invalida. Tente novamente." << std::endl;
      else{
        l = x - 1;
        break;
      }
    }

    x = 0;
    while(x < 1 || x > 6){
      std::cout << "\nDigite a coluna: ";
      std::cin >> x;
      if (x < 1 || x > 6 || std::cin.fail())
        std::cout << "\nPosicao invalida. Tente novamente." << std::endl;
      else{
        c = x - 1;
        break;
      }
    }
  }while (!(checkPosiPecas(l,c)));

  if (n != 1){
    int direcao = 0;
    std::cout << "\nDirecoes:" << std::endl;
    std::cout << "\n(1) Direita\n(2) Esquerda";
    std::cout << "\n(3) Cima\n(4) Baixo\n";

    std::cout << "\nQual direcao deseja adicionar a peca: ";
    std::cin >> direcao;

    switch(direcao){
      case 1:
        for (int i = 0; i < n; i++){
          if (c+n <= 6){
            if (checkPosiPecas[l][c+i]){
              if (BNJogadorAtual == 1)
                tabJog1Navios[l][c+i] = n;
              else
                tabJog2Navios[l][c+i] = n;
            }
            else{
              std::cout << "\nNao pode colocar uma peca em cima da outra." << std::endl;
              break;
            }
          }
          else{
            std::cout << "\nA Peca nao pode ir nessa direcao." << std::endl;
            break;
          }
        }
        break;
      case 2:
        for (int i = 0; i < n; i++){
          if (c-n >= -1){
            if (checkPosiPecas[l][c-i]){
              if (BNJogadorAtual == 1)
                tabJog1Navios[l][c-i] = n;
              else
                tabJog2Navios[l][c-i] = n;
            }
            else{
              std::cout << "\nNao pode colocar uma peca em cima da outra." << std::endl;
              break;
            }
          }
          else{
            std::cout << "\nA Peca nao pode ir nessa direcao." << std::endl;
            break;
          }
        }
        break;
      case 3:
        for (int i = 0; i < n; i++){
          if (l-n >= -1){
            if (checkPosiPecas[l-i][c]){
              if (BNJogadorAtual == 1)
                tabJog1Navios[l-i][c] = n;
              else
                tabJog2Navios[l-i][c] = n;
            }
            else{
              std::cout << "\nNao pode colocar uma peca em cima da outra." << std::endl;
              break;
            }
          }
          else{
            std::cout << "\nA Peca nao pode ir nessa direcao." << std::endl;
            break;
          }
        }
        break;
      case 4:
        for (int i = 0; i < n; i++){
          if (l+n <= 6){
            if (checkPosiPecas[l+i][c]){
              if (BNJogadorAtual == 1)
                tabJog1Navios[l+i][c] = n;
              else
                tabJog2Navios[l+i][c] = n;
            }
            else{
              std::cout << "\nNao pode colocar uma peca em cima da outra." << std::endl;
              break;
            }
          }
          else{
            std::cout << "\nA Peca nao pode ir nessa direcao." << std::endl;
            break;
          }
        }
        break;
      default:
        std::cout << "\nOpcao invalida. Tente novamente.";
    }
  }
  else{
    if (BNJogadorAtual == 1)
      tabJog1Navios[l][c] = n;
    else
      tabJog2Navios[l][c] = n;
  }

  return 0;
}

int MenuPecas(){
  std::cout << std::endl;
  std::cout << "TIPO 1 - 1" << std::endl;
  std::cout << "TIPO 2 - 22" << std::endl;
  std::cout << "TIPO 3 - 333" << std::endl;
  std::cout << "TIPO 4 - 4444" << std::endl;
  std::cout << std::endl;

  return 0;
}

int PosiPecas(){
  int pecas = 0;
  int n = 0;

  while(true){
    MenuPecas();
    std::cout << "\nESCOLHA UMA OPCAO: ";
    std::cin >> n;

    MostrarTabInicio();

    switch (n){
    case 1:
      if (BNJogadorAtual == 1)
        QuantNavJ1++;
      else
        QuantNavJ2++;
      RegistrarPecas(1);
      pecas++;
      break;
    case 2:
      if (BNJogadorAtual == 1)
        QuantNavJ1+=2;
      else
        QuantNavJ2+=2;
      RegistrarPecas(2);
      pecas++;
      break;
    case 3:
      if (BNJogadorAtual == 1)
        QuantNavJ1+=3;
      else
        QuantNavJ2+=3;
      RegistrarPecas(3);
      pecas++;
      break;
    case 4:
      if (BNJogadorAtual == 1)
        QuantNavJ1+=4;
      else
        QuantNavJ2+=4;
      RegistrarPecas(4);
      pecas++;
      break;
    default:
      std::cout << "\nOpcao invalida" << std::endl;
    }

    if (pecas == 4)
      break;
  }

  return 0;
}

int BNIniciarJogo(){
  BNJogadorAtual = 1;
  LimparTabuleiros();

  std::cout << "\nJogador 1 deve selecionar as posicoes da suas pecas.\n";
  PosiPecas();
  std::cout << "\n\n";

  if (BNjogador2 == true){
    std::cout << "\nJogador 2 deve selecionar as posicoes da suas pecas.\n";
    BNJogadorAtual = 2;
    PosiPecas();
    BNJogadorAtual = 1;
    std::cout << "\n\n";
  }

  while(true){
    MostrarTabuleiros();

    if (BNJogadorAtual == 1)
      std::cout << "\nVez do jogador 1: " << BNNome1 << std::endl;
    else
      std::cout << "\nVez do jogador 2: " << BNNome2 << std::endl;

    RegistrarJogadas();
    GuardarInfoJogadas();

    BNJogadorAtual = (BNJogadorAtual == 1) ? 2 : 1;

    if (BNCheckVencedor())
      break;


    if (BNjogador2 != true && BNJogadorAtual == 2){
      std::cout << "\nVez do jogador 2: COMPUTADOR" << std::endl;
      //JogadaRobo();
      if (BNCheckVencedor())
        break;
      else
        BNJogadorAtual = (BNJogadorAtual == 1) ? 2 : 1;
    }
  }

  return 0;
}

int BNRegistrarJogador() {
  std::cout << std::endl;
  std::cout << "Digite o nome do jogador 1: ";
  std::cin >> BNNome1;

  if (BNjogador2 == true) {
    std::cout << std::endl;
    std::cout << "Digite o nome do jogador 2: ";
    std::cin >> BNNome2;
  }

  std::cout << std::endl;
  std::cout << "Iniciando BATALHA NAVAL...\n\n";

  return 0;
}

int MenuBatalhaNaval() {
  std::cout << std::endl;
  std::cout << "===========================" << std::endl;
  std::cout << "       BATALHA NAVAL       " << std::endl;
  std::cout << "===========================" << std::endl;

  std::cout << std::endl;
  std::cout << "1 - PvC" << std::endl;
  std::cout << "2 - PvP" << std::endl;
  std::cout << "0 - Sair" << std::endl;
  std::cout << std::endl;

  return 0;
}

int OpcaoBatalhaNaval() {
  int n = 0;

  while (true) {
    MenuBatalhaNaval();
    std::cout << "\nESCOLHA UMA OPCAO: ";
    std::cin >> n;

    switch (n) {
    case 1:
      BNjogador2 = false;
      BNRegistrarJogador();
      BNIniciarJogo();
      break;
    case 2:
      BNjogador2 = true;
      BNRegistrarJogador();
      BNIniciarJogo();
      break;
    case 0:
      std::cout << "\n\nVoltando ao Menu Vetores e Matrizes..." << std::endl;
      return 0;
    default:
      std::cout << "\nOpcao invalida" << std::endl;
    }
  }
  return 0;
}

// ------------------------------------ JOGO DA VELHA --------------------------------------
int MostrarTabuleiro() {
  std::cout << "\n\n  1 2 3\n";

  for (int i = 0; i < 3; ++i) {
    std::cout << i + 1 << " ";

    for (int j = 0; j < 3; ++j) {

      if (tabuleiro[i][j] == 'X')
        std::cout << "X|";
      else if (tabuleiro[i][j] == 'O')
        std::cout << "O|";
      else
        std::cout << "_|";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  return 0;
}

int LimparTabuleiro() {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j)
      tabuleiro[i][j] = 0;
  }

  return 0;
}

int CheckVencedor() {
  for (int i = 0; i < 3; ++i) {
    // linha X
    if (tabuleiro[i][0] == tabuleiro[i][1] &&
        tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] == 'X'){
      MostrarTabuleiro();
      std::cout << "\n\nVencedor: "<< Nome1 << "\n\n";
      return 1;
    }

    // linha O
    if (tabuleiro[i][0] == tabuleiro[i][1] &&
        tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] == 'O'){
      MostrarTabuleiro();
      if (jogador2 == true)
        std::cout << "\n\nVencedor: "<< Nome2 << "\n\n";
      else
        std::cout << "\n\nVencedor: Computador\n\n";
      return 1;
    }

    // coluna X
    if (tabuleiro[0][i] == tabuleiro[1][i] &&
        tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] == 'X'){
      MostrarTabuleiro();
      std::cout << "\n\nVencedor: " << Nome1 << "\n\n";
      return 1;
    }

    // coluna O
    if (tabuleiro[0][i] == tabuleiro[1][i] &&
        tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] == 'O'){
      MostrarTabuleiro();
      if (jogador2 == true)
        std::cout << "\n\nVencedor: "<< Nome2 << "\n\n";
      else
        std::cout << "\n\nVencedor: Computador\n\n";
      return 1;
    }
  }
  // diagonal X
  if (tabuleiro[0][0] == tabuleiro[1][1] &&
          tabuleiro[1][1] == tabuleiro[2][2] &&
          tabuleiro[0][0] == 'X' ||
      tabuleiro[0][2] == tabuleiro[1][1] &&
          tabuleiro[1][1] == tabuleiro[2][0] &&
          tabuleiro[0][2] == 'X') {
    MostrarTabuleiro();
    std::cout << "\n\nVencedor: " << Nome1 << "\n\n";
    return 1;
  }

  // diagonal O
  if (tabuleiro[0][0] == tabuleiro[1][1] &&
          tabuleiro[1][1] == tabuleiro[2][2] &&
          tabuleiro[0][0] == 'O' ||
      tabuleiro[0][2] == tabuleiro[1][1] &&
          tabuleiro[1][1] == tabuleiro[2][0] &&
          tabuleiro[0][2] == 'O') {
    MostrarTabuleiro();
    if (jogador2 == true)
      std::cout << "\n\nVencedor: "<< Nome2 << "\n\n";
    else
      std::cout << "\n\nVencedor: Computador\n\n";
    return 1;
  }

  return 0;
}

int CheckEmpate() {
  if (countJogadas == 9){
    MostrarTabuleiro();
    std::cout << "\nDeu velha!\n";
    return 1;
  }
  return 0;
}

int JogadaRobo() {
  int posL = 0;
  int posC = 0;

  posL = rand()%3;
  posC = rand()%3;

  while (tabuleiro[posL][posC] != 0){
    posL = rand()%3;
    posC = rand()%3;
  }

  tabuleiro[posL][posC] = JogadorAtual;

  return 0;
}

int IniciarJogo() {
  int l = 0; // variavel da linha
  int c = 0; // variavel da coluna
  int x = 0; // variavel temporaria
  JogadorAtual = 'X';
  countJogadas = 0;

  LimparTabuleiro();

  while (true) {
    MostrarTabuleiro();

    if (JogadorAtual == 'X')
      std::cout << "\nVez do jogador " << JogadorAtual << ", " << Nome1 << std::endl;
    else
      std::cout << "\nVez do jogador " << JogadorAtual << ", " << Nome2 << std::endl;

    x = 0;
    while (x < 1 || x > 3) {
      std::cout << "\nDigite a linha: ";
      std::cin >> x;
      if (x < 1 || x > 3 || std::cin.fail())
        std::cout << "\nPosição inválida. Tente novamente." << std::endl;
      else
        l = x - 1;
    }

    x = 0;
    while (x < 1 || x > 3) {
      std::cout << "\nDigite a coluna: ";
      std::cin >> x;
      if (x < 1 || x > 3 || std::cin.fail())
        std::cout << "\nPosição inválida. Tente novamente." << std::endl;
      else
        c = x - 1;
    }

    tabuleiro[l][c] = JogadorAtual;
    countJogadas++;

    // operador ternario
    JogadorAtual = (JogadorAtual == 'X') ? 'O' : 'X';

    if (CheckVencedor() || CheckEmpate())
      break;

    if (jogador2 != true && JogadorAtual == 'O'){
      std::cout << "\n\nVez do jogador " << JogadorAtual << ", COMPUTADOR\n";
      JogadaRobo();
      if (CheckVencedor() || CheckEmpate())
        break;
      JogadorAtual = (JogadorAtual == 'X') ? 'O' : 'X';
    }
  }

  return 0;
}

int RegistrarJogador() {
  std::cout << std::endl;
  std::cout << "Digite o nome do jogador 1: ";
  std::cin >> Nome1;

  if (jogador2 == true) {
    std::cout << std::endl;
    std::cout << "Digite o nome do jogador 2: ";
    std::cin >> Nome2;
  }

  std::cout << std::endl;
  std::cout << "Iniciando JOGO DA VELHA...\n\n";

  return 0;
}

int MenuJogoVelha() {
  std::cout << std::endl;
  std::cout << "===========================" << std::endl;
  std::cout << "      JOGO  DA  VELHA      " << std::endl;
  std::cout << "===========================" << std::endl;

  std::cout << "\nEscolha uma Opcao:" << std::endl;
  std::cout << "1 - PvC" << std::endl;
  std::cout << "2 - PvP" << std::endl;
  std::cout << "0 - Sair" << std::endl;
  std::cout << std::endl;

  return 0;
}

int OpcaoJogoVelha() {
  int n = 0;

  while (true) {
    MenuJogoVelha();
    std::cout << "\nESCOLHA UMA OPCAO: ";
    std::cin >> n;

    switch (n) {
    case 1:
      jogador2 = false;
      RegistrarJogador();
      IniciarJogo();
      break;
    case 2:
      jogador2 = true;
      RegistrarJogador();
      IniciarJogo();
      break;
    case 0:
      std::cout << "\n\nVoltando ao Menu Vetores e Matrizes..." << std::endl;
      return 0;
    default:
      std::cout << "\nOpcao invalida" << std::endl;
    }
  }
  return 0;
}

// ---------------------------------- MENU VETORES E MATRIZES ----------------------------------
int MenuVetorMatriz() {
  std::cout << std::endl;
  std::cout << "__ MENU VETORES E MATRIZES __" << std::endl;
  std::cout << "(1) JOGO DA VELHA" << std::endl;
  std::cout << "(2) BATALHA NAVAL" << std::endl;
  std::cout << "(0) SAIR PARA O MENU PRINCIPAL" << std::endl;
  std::cout << std::endl;

  return 0;
}

int OpcaoVetorMatriz(){
  MenuVetorMatriz();

  int n = 0;
  while (true) {
    std::cout << "\nESCOLHA UMA OPCAO: ";
    std::cin >> n;

    switch (n) {
    case 1:
      OpcaoJogoVelha();
      MenuVetorMatriz();
      break;
    case 2:
      OpcaoBatalhaNaval();
      MenuVetorMatriz();
      break;
    case 0:
      std::cout << "\n\nVoltando ao Menu Principal..." << std::endl;
      MenuVetorMatriz();
      return 0;
    default:
      std::cout << "\nOpcao invalida" << std::endl;
      MenuVetorMatriz();
    }
  }

  return 0;
}

// ------------------------------------ FILA --------------------------------------------
int MostrarFila(){
    if (tamanhoFila > 0 && tamanhoFila <= 50){
        if (tamanhoFila == 1)
          std::cout << "\nO primeiro e unico item da fila é " << Fila[0] << "." << std::endl;
        else
          std::cout << "\nO primeiro e ultimo itens da fila são " << Fila[0] << " e " << Fila[tamanhoFila-1] << "." << std::endl;
    }
    else
        std::cout << "\nA fila esta vazia." << std::endl;
    return 0;
}

int RemFila(){
    if (tamanhoFila > 0 && tamanhoFila <= 50){
        //int posNum = 0;
        //std::cout << "\nInforme a posicao que deseja remover entre 1 e " << tamanhoFila << ": " << std::endl;
        //std::cin >> posNum;

        std::cout << "\nO valor " << Fila[0] << " foi removido da fila." << std::endl;

        for (int i = 0; i < 50; i++)
          Fila[i] = Fila[i+1];

        tamanhoFila--;

      if (tamanhoFila < 50)
          std::cout << "\nA fila tem " << 50 - (tamanhoFila) << " espacos livres." << std::endl;
      else
          std::cout << "\nA fila tem " << 50 - (tamanhoFila) << " espaco livre." << std::endl;
    }
    else
        std::cout << "\nNao tem nenhum item na fila." << std::endl;

    return 0;
}

int AddFila(){
    int numAdd = 0;
    if (tamanhoFila <= 50){
        std::cout << "\nInforme o valor que deseja adicionar: " << std::endl;
        std::cin >> numAdd;

        Fila[tamanhoFila] = numAdd;

        tamanhoFila++;

        std::cout << "\nO valor " << numAdd << " foi adicionado na posicao " << tamanhoFila << std::endl;
    }
    else
        std::cout << "\nNao ha espaco desponivel" << std::endl;
    return 0;
}

int MenuFila(){
    std::cout << std::endl;
    std::cout << "__ MENU FILA __" << std::endl;
    std::cout << "(1) ADICIONAR ITEM"<< std::endl;
    std::cout << "(2) REMOVER ITEM" << std::endl;
    std::cout << "(3) MOSTRAR PRIMEIRO E ULTIMO ITENS" << std::endl;
    std::cout << "(0) VOLTAR" << std::endl;

    return 0;
}

int OpcaoFila(){
    MenuFila();

    int n = 0;
    while (true){
        std::cout << "\nESCOLHA UMA OPCAO: ";
        std::cin >> n;

        switch (n){
            case 1:
                AddFila();
                MenuFila();
                break;
            case 2:
                RemFila();
                MenuFila();
                break;
            case 3:
                MostrarFila();
                MenuFila();
                break;
            case 0:
                std::cout << "Voltando ao Menu Principal..." << std::endl;
                return 0;
            default:
                std::cout << "Opcao invalida" << std::endl;
                MenuFila();
        }
    }
}

// ------------------------------------ PILHA -----------------------------------------
int MostrarPilha(){
    if (tamanhoPilha > 0)
        std::cout << "\nO topo da pilha e o valor " << Pilha[tamanhoPilha] << "." << std::endl;
    else
        std::cout << "\nA pilha esta vazia." << std::endl;
    return 0;
}

int RemPilha(){
    if (tamanhoPilha > 0 && tamanhoPilha <= 50){
        std::cout << "\nO valor " << Pilha[tamanhoPilha] << " foi removido da pilha." << std::endl;

        Pilha[tamanhoPilha] = 0;
        tamanhoPilha--;

        if (tamanhoPilha < 50)
            std::cout << "\nA pilha tem " << 50 - (tamanhoPilha) << " espacos livres." << std::endl;
        else
            std::cout << "\nA pilha tem " << 50 - (tamanhoPilha) << " espaco livre." << std::endl;
    }
    else
        std::cout << "\nNao tem nenhum item na pilha." << std::endl;

    return 0;
}

int AddPilha(){
    int numAdd = 0;
    if (tamanhoPilha <= 50){
        std::cout << "\nInforme o valor que deseja adicionar: " << std::endl;
        std::cin >> numAdd;

        tamanhoPilha++;

        Pilha[tamanhoPilha] = numAdd;

        std::cout << "\nO valor " << numAdd << " foi adicionado na posicao " << tamanhoPilha << std::endl;
    }
    else
        std::cout << "\nNao ha espaco desponivel" << std::endl;
    return 0;
}

int MenuPilha(){
    std::cout << std::endl;
    std::cout << "__ MENU PILHA __" << std::endl;
    std::cout << "(1) ADICIONAR ITEM"<< std::endl;
    std::cout << "(2) REMOVER ITEM" << std::endl;
    std::cout << "(3) MOSTRAR ULTIMO ITEM" << std::endl;
    std::cout << "(0) VOLTAR" << std::endl;

    return 0;
}

int OpcaoPilha(){
    MenuPilha();

    int n = 0;
    while (true){
        std::cout << "\nESCOLHA UMA OPCAO: ";
        std::cin >> n;

        switch (n){
            case 1:
                AddPilha();
                MenuPilha();
                break;
            case 2:
                RemPilha();
                MenuPilha();
                break;
            case 3:
                MostrarPilha();
                MenuPilha();
                break;
            case 0:
                std::cout << "Voltando ao Menu Principal..." << std::endl;
                return 0;
            default:
                std::cout << "Opcao invalida" << std::endl;
                MenuPilha();
        }
    }
}

int MenuPrin(){
    std::cout << std::endl;
    std::cout << "__ MENU __" << std::endl;
    std::cout << "(1) PILHA \n(2) FILA \n(3) VETORES E MATRIZES" << std::endl;
    std::cout << "(4) PONTEIROS 4 \n(5) LISTA \n(6) GRAFOS \n(0) SAIR" << std::endl;

    return 0;
}

// --------------------------------------------- MAIN -----------------------------------------
int main(void){
    MenuPrin();

    int n = 0;
    while (true){
        std::cout << "\nESCOLHA UMA OPCAO: ";
        std::cin >> n;

        switch (n){
            case 1:
                OpcaoPilha();
                MenuPrin();
                break;
            case 2:
                OpcaoFila();
                MenuPrin();
                break;
            case 3:
                OpcaoVetorMatriz();
                MenuPrin();
                break;
            case 4:
                OpcaoPonteiros();
                MenuPrin();
                break;
            case 5:
                OpcaoLista();
                MenuPrin();
                break;
            case 6:
                OpcaoGrafos();
                MenuPrin();
                break;
            case 0:
                std::cout << "\nSaindo do programa..." << std::endl;
                return 0;
            default:
                std::cout << "\nOpcao invalida" << std::endl;
                MenuPrin();
        }
    }
}
