//
// Created by sia on 19-9-18.
//

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
#include "TH1F.h"
#include "TH2D.h"
#include "TPolyMarker3D.h"
#include "kondensator.h"


using namespace std;

int main() {

/*
    int lx, ly;
    int x, y, z1, z2;
    double m;
    int t;
    int r[3];
    double v[3];
    int ay;




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
*/


    kondensator hpk;

    hpk.abfrage();

    hpk.platten();
    int error = hpk.feld();
    if (error != 1) {
        hpk.flug();
        hpk.plotmasse();
        hpk.plotfeld();
        hpk.plotflug();
    } else {
        cout << "Fehler" << endl;
        return 1;
    }


    cout << "Fertig" << endl;
    return 0;
}