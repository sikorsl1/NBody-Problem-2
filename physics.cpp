#include <cstdlib>
#include <cmath>
#include <iostream>
#include "body.hpp"
#include "physics.hpp"

using namespace std;

void simulateTimeStep(struct Body *bodies, int n, double timeStep, double data[]){
    int i,j,k,l;
    double G = 6.67408*pow(10,-11);
    double R = 0;
    double **F;
    F = (double**) malloc(n*sizeof **F);
    double **a;
    a = (double**) malloc(n*sizeof **a);
    for(i=0;i<n;i++){
        F[i] = (double*) malloc(3*sizeof *F[i]);
        a[i] = (double*) malloc(3*sizeof *a[i]);
    }
    for(i=0;i<n;i++){
        for(j=0;j<3;j++){
            F[i][j]=0;
            a[i][j]=0;
        }
    }
    for(i=0;i<n;i++){ //iteracja po cialach
        for(l=0;l<3;l++){ //iteracja po wspolrzednych wektora sily i-tego ciala
            for(j=0;j<n;j++){ //iteracja po cialach, wzgledem ktorych liczy sie l-ta wspolrzedna wektora sily
                R = 0;
                if(j!=i){
                    for(k=0;k<3;k++){ //liczenie odleglosci euklidesowej dwoch cial
                        R = R + pow(bodies[i].position[k] - bodies[j].position[k],2);
                    }
                    R = sqrt(R);
                    //cout << "r = " << R << endl;
                    if(R!=0)
                        F[i][l]+=G*(bodies[i].position[l]-bodies[j].position[l])*bodies[i].mass*bodies[j].mass/pow(R,3);
                    //else //na wypadek, jakby ciala mialy to samo polozenie
                        //F[i][l]+=G*(bodies[i].position[l]-bodies[j].position[l])*bodies[i].mass*bodies[j].mass/pow(1000,3);
                }
            }
            F[i][l] = -1 * F[i][l];
        }
        for(k=0;k<3;k++){
            //cout << F[i][k] << endl;
            a[i][k] = F[i][k]/bodies[i].mass;
        }
        for(k=0;k<3;k++){
            data[6*i+k]=bodies[i].velocity[k]+a[i][k]*timeStep;
        }
        for(k=0;k<3;k++){
            data[6*i+k+3]=bodies[i].position[k]+data[6*i+k]*timeStep;
        }
    }
    free(F);
    free(a);
}

