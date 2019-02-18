#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

FILE *openFILE(string path){
    const char *c = path.c_str();
    FILE *plik = fopen(c, "r");
    if(plik == NULL){
        cout << "Nie udalo sie otworzyc pliku z danymi!!!" << endl;
        system("pause");
    }
    return plik;
}


