#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#define MAX 1000

struct persona {
    
    std::string name;
    bool selected;
};

struct gift{
    std::string gifter, reciever;
};

persona *obtain_memory1(int n){
    //persona *pointer = new persona[n];
    persona *pointer = (persona*)malloc(sizeof(persona)*n);
    return pointer;
}

gift *obtain_memory2(int n){
    gift *pointer = (gift*)malloc(sizeof(gift)*n);
    return pointer;
}

persona *fill_list(persona *list, int n){
    int i;
    std::string nome;
    for(i=0;i<n;i++){
        do{ 
            std::cout<< "Inserire nome della persona allo slot: " << i << std::endl;
            std::cin >> list[i].name;
        }while(nome.length() <= 0);
    }
    for(i=0;i<n;i++){
        list[i].selected = false;
    }
    return list;
}

gift *create_couples(persona *list, int n){
    gift *regali = obtain_memory2(n);
    int i, j;
    for(i=0;i<n;i++){
        do{
            j=rand()%n;
        }while(list[j].selected);

        regali[i].gifter = list[i].name;

        regali[i].reciever = list[j].name;

        list[j].selected = true;
    }
    return regali;
}

void writetofile(std::string filename, std::string contents){
    std::ofstream fp(filename + ".txt");
    fp << contents;
    fp.close();
}

void write_gifts(gift *regali, int n){
    int i;
    for(i=0;i<n;i++){
        writetofile(regali[i].gifter, regali[i].reciever);
    }
}

int main(){
    int i, n;
    persona *lista;
    gift *regali;
    //ottieni numero persone lista
    do{
        std::cout << "Inserire numero di persone della lista\n";
        std::cin >> n;
    }while( n < 1 || n > MAX);
    //ottieni spazio in memoria per la lista
    lista = obtain_memory1(n);
    
    //popola la lista
    lista = fill_list(lista, n);

    //decidi chi regala a chi
    regali = create_couples(lista, n);

    //scrivi a ogni persona la sua persona in file segreti segretissimi uoo
    write_gifts(regali, n);

    //libero memoria heap
    free(regali);
    free(lista);

    //chiudo
    return 0;
}
