#pragma once
extern "C" void iluk_(int* n, double* a, int* ja, int* ia, int* lfil, double* alu, int* jlu, int* ju, int* levs, int* iwk, double* w, int* jw, int* ierr);
extern "C" void prevec0_(int* IPREVEC, int* ICHANGE, double* X, double* Y, int* iW, double* rW);
extern "C" void matvec_(int* IMATVEC, double* ALPHA, double* X, double* BETA, double* Y, int* ia, int* ja, double* a);
extern "C" void slpbcgs_(void(*prevec)(int*, int*, double*, double*, int*, double*), int* IPREVEC, int* iW, double* rW,
	void(*matvec)(int*, double*, double*, double*, double*, int*, int*, double*), int* IMATVEC, int* ia, int* ja, double* a,
double* WORK, int* MW, int*NW, int* N, double* RHS, double* SOL, int* ITER, double* RESID, int* INFO, int* NUNIT);

