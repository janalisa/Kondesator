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