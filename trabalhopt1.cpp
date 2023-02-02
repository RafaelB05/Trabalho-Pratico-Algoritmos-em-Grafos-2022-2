/*
MacroEntrega 1: Leitura de Dados, Estruturas e verificação de restrição
Enzo Velo :
Lucas Gomes Colombo :
Rafael Brunini : 202120488

*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

struct Instancia{
    string nome;
    string location;
    string comment;
    string type;
    int size;
    string distribution;
    string depot;
    int routTime;
    int timeWindow;
    int capacity;
};

struct Node{
    unsigned int id;
    float lat;
    float lng;
    int dem;
    int etw;
    int ltw;
    int dur;
    unsigned int p;
    unsigned int d;
};

struct Truck{
    unsigned int id;
    int tempoGasto = 0;
    int capacity = 0;
};


void lerInstancia(string namefile,Instancia &inst){
    char delimitador = ' ';
    ifstream arquivo(namefile);
    string nome;
    for(int i = 1; i <= 10;i++){
        getline(arquivo,nome,delimitador);
        getline(arquivo,nome);
        switch (i){
        case 1:
            inst.nome = nome;
            break;
        
        case 2:
            inst.location = nome;
            break;

        case 3:
            inst.comment = nome;
            break;

        case 4:
            inst.type = nome;
            break;
        
        case 5:
            inst.size = stoi(nome);
            break;
        
        case 6:
            inst.distribution = nome;
            break;
        
        case 7:
            inst.depot = nome;
            break;
        
        case 8:
            inst.routTime = stoi(nome);
            break;
        
        case 9:
            inst.timeWindow = stoi(nome);
            break;
        
        case 10:
            inst.capacity = stoi(nome);
            break;
        default:
            break;
        }
    }
    arquivo.close();
}

void lerGrafo(string namefile,Node *vetor,int **MA,int size){

    char delimitador = ' ';
    ifstream arquivo(namefile);
    string nome;
    
    for(int i = 0; i < size;i++)
        MA[i] = new int[size];
    
    for(int i = 0; i < 10;i++) // Descarta as 10 primeiras linhas que ja foram lidas pois caracterizam a instancia
        getline(arquivo,nome);

    getline(arquivo,nome);
    for(int i = 0; i < size;i++){
        for(int j = 1; j <= 9; j++ ){
            getline(arquivo,nome,delimitador);
            switch (j){
                case 1:
                    vetor[i].id = stoi(nome);
                    break;
                
                case 2:
                    vetor[i].lat = stof(nome);
                    break;
                case 3:
                    vetor[i].lng = stof(nome);
                    break;

                case 4:
                    vetor[i].dem = stoi(nome);
                    break;
                
                case 5:
                    vetor[i].etw = stoi(nome);
                    break;
                
                case 6:
                    vetor[i].ltw =  stoi(nome);
                    break;
                
                case 7:
                    vetor[i].dur =  stoi(nome);
                    break;
                
                case 8:
                    vetor[i].p = stoi(nome);
                    delimitador = '\n';
                    break;
                
                case 9:
                    vetor[i].d = stoi(nome);
                    delimitador = ' ';
                    break;
                
                default:
                    break;
            }
        }
    }

    getline(arquivo,nome);
    for (int i = 0; i < size; i++){
        delimitador = ' ';
        for(int j = 0; j < size;j++){
            getline(arquivo,nome,delimitador);
            MA[i][j] = stoi(nome);
            if(j == size-1)
                delimitador = '\n';
        }
    }
    arquivo.close();
}

bool verificaRestricao(Node *vetor, Instancia inst){

    bool worth = true;
    Node Deposito = vetor[0];

    Truck caminhao;

    //Deposito -> 5 -> 12 -> 15 -> 22 -> Deposito #6
    //Demanda: 0 + 30 + 24 + (-30) + (-24) + 0
    //Tempo: (0)0 + [0, 5]15 + (5)3 + [5, 12]16 + (12)4 + [12, 15]20 + (15)5 + [15, 22]10 + (22)5 + [22, 0]19

    int sequenciaDeposito[6] = {0, 5, 12, 15, 22, 0};
    int sequenciaDemanda[6] = {0, 30, 24, -30, -24};
    int sequnciaTempo[(6 * 2) - 1] = {0, 15, 3, 16, 4, 20, 5, 10, 5, 19};

    for (int i = 0; i < 6; i++){
        caminhao.capacity += sequenciaDemanda[i];
        if (caminhao.capacity > inst.capacity)
        {
            worth = false;
            break;
        }
    }

    for (int i = 0; i < (6 * 2) - 1; i++){
        caminhao.tempoGasto += sequnciaTempo[i];
        if (caminhao.tempoGasto > inst.routTime)
        {
            worth = false;
            break;
        }
        
    }

    return worth;

}

int main(){

    Instancia inst;

    //time_t begin = time(NULL)

    lerInstancia("poa-n100-6.txt",inst);

    Node *vetor = new Node[inst.size];
    int **MA = new int*[inst.size];

    lerGrafo("poa-n100-6.txt",vetor,MA,inst.size);

    //time_t end = time(NULL);

    //cout << inst.nome << endl << inst.size << endl << inst.capacity << endl;
    
    // for(int i = 0; i < inst.size;i++){
    //     cout << vetor[i].id << endl;
    // }
    
    // for (int i = 0; i < inst.size; i++){
    //     for(int j = 0; j < inst.size;j++){
    //         cout << MA[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    cout << verificaRestricao(vetor,inst);

    //printf("The elapsed time is %d seconds", (end - begin));


    delete []vetor;
    return 0;

}
