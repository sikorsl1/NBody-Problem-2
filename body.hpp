#ifndef body_hpp
#define body_hpp
#include <cstdio>

struct Body{
double mass;
double velocity[3];
double position[3];
};

struct Body bodyCreate(FILE *plik);
struct Body bodyUpload(struct Body *body, double *v, double *p);
void wypisz(struct Body *bd);

#endif
