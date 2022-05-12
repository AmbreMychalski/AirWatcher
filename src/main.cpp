#include <iostream>
#include <string>
using namespace std;

int main () {
    cout<<"-----------------------------------------------------------------------------------------------"<<endl;
    cout<<"                                   Air Cleaner"<<endl;
    cout<<"-----------------------------------------------------------------------------------------------"<<endl;
    // Choix Menu
    int choice=0;

    cout<<"-----------------------------------Choix du Menu-----------------------------------------------"<<endl;
    while(choice>3 || choice<1){
        cout<<"1. Citoyen       2. Entreprise       3. Gouvernement"<<endl;
        cin>>choice;
    }
    switch(choice){
        case 1:
            cout<<"Je suis un citoyen"<<endl;
            break;
        case 2:
            cout<<"Je suis une entreprise"<<endl;
            break;
        case 3:
            cout<<"Je suis un gouvernement"<<endl;
            break;
    }
}