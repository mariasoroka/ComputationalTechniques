#include <string>
#include <iostream>
#include <stdio.h>
#include "for_ani2d.h"

using namespace std;

void create_grid(int nlevel){
    int nvmax = 100000;
    int ntmax = 2 * nvmax;
    int nbmax = 50000;
    int nv = 4;
    int nt = 2;
    int nb = 4;
    double* vrt = new double[nvmax * 2];
    int* tri = new int[ntmax * 3];
    int* labelT = new int[ntmax];
    int* bnd = new int[nbmax * 2];
    int* labelB = new int[nbmax];

    vrt[0] = 0.0;
    vrt[1] = 0.0;
    vrt[2] = 0.0;
    vrt[3] = 1.0;
    vrt[4] = 1.0;
    vrt[5] = 1.0;
    vrt[6] = 1.0;
    vrt[7] = 0.0;

    tri[0] = 1;
    tri[1] = 2;
    tri[2] = 3;
    tri[3] = 3;
    tri[4] = 4;
    tri[5] = 1;

    labelT[0] = 1;
    labelT[1] = 1;

    bnd[0] = 1;
    bnd[1] = 2;
    bnd[2] = 2;
    bnd[3] = 3;
    bnd[4] = 3;
    bnd[5] = 4;
    bnd[6] = 4;
    bnd[7] = 1;

    labelB[0] = 1; 
    labelB[1] = 1; 
    labelB[2] = 1;      
    labelB[3] = 1;

    string fname = "init_mesh.ps";
    string message = "init_mesh";

    graph_demo_(&nv, vrt, &nt, tri, fname.data(), message.data(), fname.size(), message.size());

    int iERR = 0;
    int MaxWi = 5500000;
    int* iW = new int[MaxWi];

    initializercb_(&nt, &ntmax, vrt, tri, &MaxWi, iW, &iERR);
    if(iERR > 0){
        string routine = "main";
        string message = "error in InitializeRCB";
        errmesrcb_(&iERR, routine.data(), message.data(), routine.size(), message.size());
    } 
    
    int maxlevel = 150;
    bool* history = new bool[maxlevel * ntmax];
    int ilevel = 0;

    for(ilevel = 1; ilevel <= nlevel; ilevel++){
        localrefine_(&nv, &nvmax, &nb, &nbmax, &nt, &ntmax, vrt, tri, bnd, labelB, labelT,
            refine_rule, &ilevel, &maxlevel, history, &MaxWi, iW, &iERR);
        if(iERR > 0){
            string routine = "main";
            string message = "Error in LocalRefine";
            errmesrcb_(&iERR, routine.data(), message.data(), routine.size(), message.size());
        }
    } 

    fname = "refined_mesh.ps";
    message = "refined_mesh";

    graph_demo_(&nv, vrt, &nt, tri, fname.data(), message.data(), fname.size(), message.size());

    delete[] vrt;
    delete[] tri;
    delete[] labelT;
    delete[] bnd;
    delete[] labelB;
    delete[] iW;
    delete[] history;
}
int main(){
    create_grid(10);
}