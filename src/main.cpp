#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

#define MAX 1000

struct person {
    std::string name;
    bool selected;
};

struct gift{
    std::string gifter, reciever;
};

struct t_node {
    t_node *next;
    std::string name;
};

typedef t_node* ptr_node;

person *obtain_memory1(int n){
    //person *pointer = new person[n];
    person *pointer = (person*) new person[n];
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

ptr_node obtain_memory3(){
    ptr_node pointer= new t_node;
    if(pointer){
        std::cout<<"Pointer Created Successfully\n";
        return pointer;
    }
    else{
        std::cout<<"ERROR IN OBTAINING POINTER FOR NEW NODE\n";
        return NULL;
    }
}

person *fill_list(person *list, int n){
    int i;
    for(i=0;i<n;i++){
        do{ 
            std::cout<< "Input name of person in slot #" << i+1 << std::endl;
            std::cin >> list[i].name;
        }while(list[i].name.length() <= 0);
    }
    for(i=0;i<n;i++){
        list[i].selected = false;
    }
    return list;
}

/*
gift *create_couples(persona *list, gift *regali, int n){ wrong impl.
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
//this one is boring as fuck and lazy
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
*/

ptr_node build_tree(ptr_node start, person *list, int n){
    int i, j;
    ptr_node tmp;
    tmp = start;
    for(i=0;i<n;i++){
        if(i==0){
            j = rand()%n;
            tmp->name = list[j].name;
            list[j].selected = true;
            tmp->next = obtain_memory3();
            if(tmp->next != NULL){
                tmp = tmp->next;
            }
            else{
                std::cout<<"NULLPTR EXCEPTION, BREAKING OUT\n";
                return NULL;
            }
        }
        else if(i==n-1){
            do{
                j=rand()%n;
            }while(list[j].selected);
            tmp->name = list[j].name;
            list[j].selected = true;
            tmp->next = start;
        }
        else{
            do{
               j=rand()%n; 
            }while(list[j].selected);
            tmp->name = list[j].name;
            list[j].selected = true;
            tmp->next = obtain_memory3();
            if(tmp->next != NULL){
                tmp = tmp->next;
            }
            else{
                std::cout<<"NULLPTR EXCEPTION, BREAKING OUT\n";
                return NULL;
            }
        }
    }
    return start;
}

gift *create_couples_from_tree(ptr_node start, gift *gifts, int n){
    int i;
    ptr_node tmp = start;
    for(i=0;i<n;i++){
        gifts[i].gifter = tmp->name;
        gifts[i].reciever = tmp->next->name;
        tmp = tmp->next;
    }
    return gifts;
}

void writetofile(std::string filename, std::string contents){
    std::ofstream fp("./target/" + filename + ".txt");
    fp << contents;
    fp.close();
}

void write_gifts(gift *gifts, int n){
    int i;
    for(i=0;i<n;i++){
        writetofile(gifts[i].gifter, gifts[i].reciever);
    }
}

int main(){
    int i, n;
    person *list;
    gift *gifts;
    ptr_node tree;
    tree = obtain_memory3();
    //ottieni numero persone lista
    do{
        std::cout << "Please insert how many people are taking part in your secret santa:\n";
        std::cin >> n;
    }while( n < 1 || n > MAX);
    //ottieni spazio in memoria per la lista
    list = obtain_memory1(n);
    //popola la lista
    list = fill_list(list, n);
    //costruisci albero regali
    tree = build_tree(tree, list, n);
    //ottieni spazio di memoria per gli assegnamenti
    gifts = obtain_memory2(n);
    //decidi chi regala a chi
    gifts = create_couples_from_tree(tree, gifts, n);
    //scrivi a ogni persona la sua persona in file segreti segretissimi uoo
    write_gifts(gifts, n);
    //generalcleanup
    delete [] list;
    delete [] gifts;
    //chiudo
    return 0;
}
