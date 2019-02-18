#include "body.hpp"
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

struct Body bodyCreate(FILE *plik){
    int k;
    double m;
    double *vel;
    vel = (double*)malloc(3*sizeof *vel);
    double *pos;
    pos = (double*)malloc(3*sizeof *pos);
    struct Body nowy;
    fscanf(plik, "%lf", &m);
    for(k=0;k<3;k++){
        fscanf(plik, "%lf", &vel[k]);
    }
    for(k=0;k<3;k++){
        fscanf(plik, "%lf", &pos[k]);
    }
    nowy.mass = m;
    int i;
    for(i=0;i<3;i++){
        nowy.velocity[i] = vel[i];
        nowy.position[i] = pos[i];
    }
    free(vel);
    free(pos);
    return nowy;
}

struct Body bodyUpload(struct Body *body, double *v, double *p){
    struct Body nowy;
    nowy.mass = body->mass;
    int i;
    for(i=0;i<3;i++){
        nowy.velocity[i] = v[i];
        nowy.position[i] = p[i];
    }
    return nowy;
}

void wypisz(struct Body *bd){
    cout << "mass = " << bd->mass << endl;
    cout << "velocity = [" << bd->velocity[0] << " " << bd->velocity[1] << " " << bd->velocity[2] << "]" << endl;
    cout << "position = [" << bd->position[0] << " " << bd->position[1] << " " << bd->position[2] << "]" << endl;
}


