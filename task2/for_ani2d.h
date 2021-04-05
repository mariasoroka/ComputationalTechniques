#pragma once
void refine_rule(int* nE, int* IPE, double* XYP, int* verf, int* ilevel);
extern "C" void graph_demo_(int* nv, double* vrt, int* nt, int* tri, const char* fName, const char* demo_message, int fName_LEN, int demo_message_LEN);
extern "C" void initializercb_(int* nE, int* nEmax, double* XYP, int* IPE, int* MaxWi, int* iW, int* iERR);
extern "C" void errmesrcb_(int* iERR, const char* routine, const char* message, int routine_LEN, int message_LEN);
extern "C" void localrefine_(int* nP, int* nPmax, int* nF, int* nFmax, int* nE, int* nEmax, double* XYP, int* IPE, int* IPF, int* lbF, int* lbE,
     void(*RefineRule)(int*, int*, double*, int*, int*), int* ilevel, int* maxlevel, bool* history, int* MaxWi, int* iW, int *iERR);
