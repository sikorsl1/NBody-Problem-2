#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "physics.hpp"
#include "body.hpp"
#include "files.hpp"

using namespace std;

void skrypt(FILE *plik, int n){
    FILE *fpl = fopen("plot.pg", "w");
    fprintf(fpl, "set title 'symulacja NBody'\n splot 'wyniki.plt' every %i ps 0.25 pt 7 lc 1\n", n);

    int j;
    for(j=1;j<n;j++){
        fprintf(fpl, "replot 'wyniki.plt' every %i::%i ps 0.25 pt 7 lc %i\n",n, j, j+1);
    }
    fprintf(fpl, "pause -1");
    fclose(fpl);
}

void wpiszDoPliku(FILE *plik, struct Body *bd){
    int i;
    for(i=0;i<2;i++){
        fprintf(plik, "%lf ", bd->position[i]);
    }
    fprintf(plik, "%lf\n", bd->position[2]);
}

int main()
{
    int n,j,k,i;
    double simTime, timeStep;
    cout << "Podaj dlugosc symulacji (w latach): ";
    cin >> simTime;
    cout << "\n" << "Podaj dlugosc kroku czasowego (w dniach): ";
    cin >> timeStep;
    cout << endl;
    double time = timeStep*86400;
    double steps = floor(simTime*365/timeStep);
    //cout << "Ciala wczytane z pliku : " << endl;
    FILE *plik = openFILE("dane3.plt");
    fscanf(plik, "%i", &n);
    struct Body *bodies;
    bodies = (struct Body*) malloc(n*sizeof *bodies);
    double *data;
    data = (double*) malloc((n*6)*sizeof *data);
    for(j=0;j<6*n;j++)
        data[j] = 0;
    struct Body *bd;
    for(j=0;j<n;j++){
        bodies[j] = bodyCreate(plik);
        bd = &bodies[j];
        //wypisz(bd);
    }
    fclose(plik); //tu sie konczy wczytywanie cial z plik
    //mozna juz zaczac symulacje
    FILE *plik2 = fopen("wyniki.plt", "w");
    double *v;
    v = (double*) malloc(3*sizeof *v);
    double *p;
    p = (double*) malloc(3*sizeof *p);
    for(i=0;i<=steps;i++){
        simulateTimeStep(bodies,n,time,data);
        for(j=0;j<n;j++){
            for(k=0;k<3;k++){
                v[k]=data[j*6+k];
                p[k]=data[j*6+k+3];
                }
            bd = &bodies[j];
            bodies[j] = bodyUpload(bd,v,p);
            bd = &bodies[j];
            wpiszDoPliku(plik2, bd);
            //wypisz(bd);
        }
    }
    skrypt(plik2, n);
    fclose(plik2);
    free(v);
    free(p);
    cout << endl;
    system("pause");
    return 0;
}

