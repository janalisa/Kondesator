//
// Created by sia on 19-9-18.
//
#include <vector>
#include "TVector3.h"


#ifndef KONDESATOR_KONDENSATOR_H
#define KONDESATOR_KONDENSATOR_H

using namespace std;

typedef struct {
    TVector3 ort;
    TVector3 v;
} ortimp;

class kondensator{
    const double zk = 0.001;
    int lx, ly;
    int x,y;
    int z1, z2;
    double m;
    const double g=6.;
    int r[3];
    double v[3];
    int ay;
    int t;

    vector<vector<vector<double>>> M;
    vector<vector<vector<TVector3>>> G;
    vector<ortimp> tp;


public:
    kondensator();
    void abfrage();
    void platten();
    int feld();
    void plotmasse();
    void plotfeld();
    void flug();
    void plotflug();
};



#endif //KONDESATOR_KONDENSATOR_H

