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
#include "kondensator.h"


using namespace std;

kondensator::kondensator() : M(100, vector<vector<double>>(100, vector<double>(100, 0))), G(100, vector<vector<TVector3>>(100, vector<TVector3>(100, TVector3()))){
    //Default constructor
}

void kondensator::abfrage() {
    cout << "Was ist die Laenge der Platte in x - Richtung" << endl;
    scanf("%i", &lx);
    cout << "Was ist die Laenge der Platte in y - Richtung" << endl;
    scanf("%i", &ly);
    cout << "Bei welchem X Wert beginnt die Platte?" << endl;
    scanf("%i", &x);
    cout << "Bei welchem Y Wert beginnt die Platte?" << endl;
    scanf("%i", &y);
    cout << "Bei welchem Z Wert liegt die erste Platte" << endl;
    scanf("%i", &z1);
    cout << "Bei welchem Z Wert liegt die zweite Platte" << endl;
    scanf("%i", &z2);
    cout << "Was ist die Masse eines Unterteilungsstueckes?" << endl;
    scanf("%lf", &m);
    cout << "Wie lange soll das Teilchen fliegen?" << endl;
    scanf("%i", &t);
    cout << "Was ist der Startpunkt des Teilchens in x Richtung?" << endl;
    scanf("%i", &r[0]);
    cout << "Was ist der Startpunkt des Teilchens in y Richtung?" << endl;
    scanf("%i", &r[1]);
    cout << "Was ist der Startpunkt des Teilchens in z Richtung?" << endl;
    scanf("%i", &r[2]);
    cout << "Was ist die Geschwindigkeit des Teilchens in x Richtung?" << endl;
    scanf("%lf", &v[0]);
    cout << "Was ist die Geschwindigkeit des Teilchens in y Richtung?" << endl;
    scanf("%lf", &v[1]);
    cout << "Was ist die Geschwindigkeit des Teilchens in z Richtung?" << endl;
    scanf("%lf", &v[2]);
    cout << "Was ist die Beschleunigung des Teilchens in y Richtung?" << endl;
    scanf("%i", &ay);

}



void kondensator::platten() {
    if (lx <= 50 && ly <= 50 && (x + lx) <= 100 && y + ly <= 100 && x >= 0 && x <= 100 && y >= 0 && y <= 100 &&
        z1 >= 0 && z1 <= 100 && z2 >= 0 && z2 <= 100) {
        for (int i = x; i < (x + lx); i++) {
            for (int j = y; j < (ly + y); j++) {

                cout << "lx: " << lx << endl;
                cout << "ly: " << ly << endl;
                cout << i << "   " << j << endl;
                M[i][j][z1] = m;
                M[i][j][z2] = m;
            }
        }
        cout << "platten fertig" << endl;
    }
}


int kondensator::feld(){
    if(lx<= 50 && ly<=50 && (x+lx)<=100 && y+ly<=100 && x>=0&&x<=100 && y>=0&&y<=100 && z1>=0&&z1<=100 && z2>=0&&z2<=100){
        for(int i1 =x; i1 < (x+lx); i1++){
            for(int j1=y; j1<(y+ly); j1++){
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
    TH2D *h2 = new TH2D("h2", "Kondensator", 100, 0., 100., 100, 0., 100.);
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


void kondensator::plotfeld() {
    remove("feld.dat");
    remove("feldstaerke.dat");
    ofstream gpd;
    ofstream gpfd;
    gpd.open("feld.dat");
    gpfd.open("feldstaerke.dat");
    for(int i=0; i<100; i++){
        for(int j=0; j<100; j++){
            for(int k=0; k<100; k++){
                gpd  << i << " " << j << " " << k << " " << G[i][j][k].X()/1000. << " " << G[i][j][k].Y()/1000. << " " << G[i][j][k].Z() << "\n";
                gpfd << i << " " << j << " " << k << " " << G[i][j][k].Mag() << "\n";
            }
        }
        gpd.close();
        gpfd.close();

    }
    cout << "Dateien fertig, eventuell zrange [40:60] setzen" << endl;
}



void kondensator::flug(){

    tp.push_back({TVector3(r[0], r[1], r[2]), TVector3(v[0], v[1], v[2])});

    for(int q=0; q<t; q++){
        TVector3 ort=tp.back().ort;
        if((ort.X()<0 || (ort.X()>100) || (ort.Y()<0) || (ort.Y()>100) || (ort.Z()<0) || (ort.Z()>100))){
            cout << "Teilchen aus Koordinatensystem" << endl;
            break;
        }
        else {
            if(M[ort.X()][ort.Y()][ort.Z()] !=0){
                cout << "Teilchen in Platte" << endl;
                break;
            }
            else{
                TVector3 neuort = ort + (zk * tp.back().v);
                TVector3 neuv = (zk * tp.back().v) + G[ort.X()][ort.Y()][ort.Z()];
                tp.push_back({neuort, neuv});
            }
        }
    }
}



void kondensator::plotflug() {
    remove("flug.dat");
    ofstream gpd;
    for(int i=0; i<tp.capacity()-1; i++){
        gpd << setw(10) << tp[i].ort.X() << setw(10) << tp[i].ort.Y() << setw(10) << tp[i].ort.Z() << "\n";
    }
    gpd.close();
}





































