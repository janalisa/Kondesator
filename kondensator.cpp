//
// Created by sia on 19-9-18.
//

#include "kondensator.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <fstream>
#include <TVector3.h>
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TMath.h"
//#include "TH1F.h"
//#include "TH2D.h"
#include "TPolyMarker3D.h"
#include "plattenkondensator.h"


using namespace std;

kondensator::kondensator() : M(100, vector<vector<double>>(100, vector<double>(100, ))), G(100, vector<vector<TVector3>>(100, vector<TVector3>(100, TVector3()))){
    //Default constructor
}

void kondensator::platten(){
    for(int i=x; i<x+lx; i++){
        for(int j=y; j<ly+y; j++){
            M[i][j][z1]=m;
            M[i][j][z2]=m;
        }
    }
    cout << "platten fertig" << endl;
}


int kondensator::feld(){
    if(lx<= 50 && ly<=50 && x+lx<=100 && y+ly<=100 && x>=0&&x<=100 && y>=0&&y<=100 && z1>=0&&z1<=100 && z2>=0&&z2<=100){
        for(int i1 =x; i1 < x+lx; i1++){
            for(int j1=y; j1<y+ly; j1++){
                for(int k1=0; k1<100; k1++){
                    if(M[i1][j1][k1]>0.){
                        for(int i2=0; i2<100; i2++){
                            for(int j2=0; j2<100; j2++){
                                for(int k2=0; k2<100; k2++){
                                    if((i1 != i2) && (j1 != j2) && (k1 != k2)){
                                        TVector3 vec1(i1, j1, k1);
                                        TVector3 vec2(i2, j2, k2);
                                        double mag = 1. / ((vec1-vec2).Mag() * (vec1-vec2).Mag() *(vec1-vec2).Mag());
                                        G[i2][j2][k2] += (g* lx*ly*m * (vec2-vec1) * mag);
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }
    }
    else {
        cout << "falsche Eingabe" << endl;
    }
}


void kondensator::plotmasse() {
    TCanvas *c = new TCanvas("c", "c", 800, 600);
    c-> Update();
    TH2D *h2 = new TH2D("h2", "Kondensato", 100, 0., 100., 100, 0., 100.);
    for(int i=0; i<100;i++){
        for(int j=0;j<100; j++){
            double sum=0;
            for(int k=0; k<100; k++){
                sum += M[i][j][k];
            }
            h2->Fill(i,j,sum);
        }
    }
    h2->SetMarkerStyle(6);
    h2->Draw();
    c->Update();
    c->SaveAs("plattenxy.png");
    c->Close();
}







































