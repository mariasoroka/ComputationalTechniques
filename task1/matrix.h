#pragma once
#include <iostream>

#include <fstream>
#include <string>
#include "umfpack.h"
#include <math.h>
#include "for_sparskit_and_ani2d.h"

using namespace::std;
class Vector{
public:
    Vector() = default;
    ~Vector(){ delete[] _vect; }
    const void subtract(Vector& v);
    const double norm();
    int _n = 0;
    double* _vect = nullptr;
};
ostream& operator<<(ostream& stream, const Vector& v);
class Matrix{
public:
    Matrix() = default;
    void MultByVect(Vector& v, Vector& v_res);
    void ChangeMode(int add);
    ~Matrix(){
        delete[] _IA;
        delete[] _JA;
        delete[] _IJA;
    }
    int _n = 0;
    int _nz = 0;
    int* _IA = nullptr;
    int* _JA = nullptr;
    double* _IJA = nullptr;
    bool mode = 0;
};
class Equation{
public:
    Equation(string filename, bool mode);
    void SolveUsingUMFPACK();
    void SolveUsingSPARSKITaniILU(int k);
    Matrix A;
    Vector right;
    Vector solution;
};