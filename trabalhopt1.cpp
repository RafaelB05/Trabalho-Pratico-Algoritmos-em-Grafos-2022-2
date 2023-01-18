#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h>
#include <unistd.h>

using namespace std;

struct Instacia{
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

void lerInstancia(string namefile,Instacia &inst){
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
            if(j == 99)
                delimitador = '\n';
        }
    }
    arquivo.close();
}

string verificaRestricao(){
    string resposta = "Nao respeita";

    return resposta;
}



int main(){
    Instacia inst;

    time_t begin = time(NULL);

    lerInstancia("poa-n100-6.txt",inst);

    Node *vetor = new Node[inst.size];
    int **MA = new int*[inst.size];

    lerGrafo("poa-n100-6.txt",vetor,MA,inst.size);

    time_t end = time(NULL);

    cout << inst.nome << endl << inst.size << endl << inst.capacity << endl;
    
    for(int i = 0; i < inst.size;i++){
        cout << vetor[i].id << endl;
    }
    
    for (int i = 0; i < inst.size; i++){
        for(int j = 0; j < inst.size;j++){
            cout << MA[i][j] << " ";
        }
        cout << endl;
    }

    printf("The elapsed time is %d seconds", (end - begin));


    delete []vetor;
    return 0;

}
