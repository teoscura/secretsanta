#include <cstdio>
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
    persona *pointer = (persona*) new persona[n];
    if(pointer){
        std::cout<<"Pointer Created Successfully\n";
        return pointer;
    }
    else{
        std::cout<<"ERROR IN OBTAINING POINTER IN LIST\n";
        return NULL;
    }
}

gift *obtain_memory2(int n){
    gift *pointer = (gift*) new gift[n];
    if(pointer){
        std::cout<<"Pointer Created Successfully\n";
        return pointer;
    }
    else{
        std::cout<<"ERROR IN OBTAINING POINTER IN GIFT\n";
        return NULL;
    }
}

persona *fill_list(persona *list, int n){
    int i;
    std::string nome;
    for(i=0;i<n;i++){
        do{ 
            std::cout<< "Inserire nome della persona allo slot: " << i+1 << std::endl;
            std::cin >> list[i].name;
        }while(list[i].name.length() <= 0);
    }
    for(i=0;i<n;i++){
        list[i].selected = false;
    }
    return list;
}

/*
gift *create_couples(persona *list, gift *regali, int n){
    int i, j;
    for(i=0;i<n;i++){
        do{
            j=rand()%n;
            if(i<2) std::cout << j << std::endl;
        }while(list[j].selected || i==j);
        regali[i].gifter = list[i].name;
        regali[i].reciever = list[j].name;
        list[j].selected = true;
    }
    return regali;
}
*/

gift *create_couples_lollosversion(persona *list, gift *regali, int n){
    int i, j;
    for(i=0;i<n;i++){
        if(i!=n-1) j=i+1;
        else j = 0;
        regali[i].gifter = list[i].name;
        regali[i].reciever = list[j].name;
    }
    return regali;
}

void writetofile(std::string filename, std::string contents){
    std::ofstream fp("./target/" + filename + ".txt");
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
    //ottieni spazio di memoria per gli assegnamenti
    regali = obtain_memory2(n);
    //decidi chi regala a chi
    regali = create_couples_lollosversion(lista, regali, n);
    //scrivi a ogni persona la sua persona in file segreti segretissimi uoo
    write_gifts(regali, n);
    //generalcleanup
    delete [] lista;
    delete [] regali;
    //chiudo
    return 0;
}
