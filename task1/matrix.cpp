#include "matrix.h"
#include "profile.h"
const void Vector::subtract(Vector& v){
    if(v._n != _n){
        cerr << "Vectors' sizes does not match" << endl;
    }
    else{
        for(int i = 0; i < _n; i++){
            v._vect[i] -= _vect[i];
        }
    }
}
ostream& operator<<(ostream& stream, const Vector& v){
    for(int i = 0; i < v._n; i++){
        cout << "(" << i << ", " << v._vect[i] << ")" << endl;
    }
    return stream;
}
const double Vector::norm(){
    double norm = 0;
    for(int i = 0; i < _n; i++){
        norm += _vect[i] * _vect[i];
    }
    return sqrt(norm);
}
void Matrix::MultByVect(Vector& v, Vector& v_res){
    if(v._n != _n){
        cerr << "Vector size does not match matrix size" << endl;
    }
    else{
        v_res._n = _n;
        v_res._vect = new double[_n];
        if(mode == 0){
            for(int i = 0; i < _n; i++){
                double temp = 0;
                for(int j = _IA[i]; j < _IA[i + 1]; j++){
                    temp += _IJA[j] * v._vect[_JA[j]];
                }
                v_res._vect[i] = temp;
            }
        }
        else{
            for(int i = 0; i < _n; i++){
                double temp = 0;
                for(int j = _IA[i] - 1; j < _IA[i + 1] - 1; j++){
                    temp += _IJA[j] * v._vect[_JA[j] - 1];
                }
                v_res._vect[i] = temp;
            }
        }
    }
}
void Matrix::ChangeMode(int add){
    for(int i = 0; i < _nz; i++){
        _JA[i] += add;
    }
    for(int i = 0; i < _n + 1; i++){
        _IA[i] += add;
    }
    mode += add;
}
Equation::Equation(string filename, bool mode){
    ifstream file;
    file.open(filename, ios_base::in);
    file >> A._n;
    A.mode = mode;
    A._IA = new int[A._n + 1];
    for(int i = 0; i < A._n + 1; i++){
        file >> A._IA[i];
        if(mode == 0){
            A._IA[i]--;
        }
    }
    A._nz = A._IA[A._n];
    A._JA = new int[A._nz];
    A._IJA = new double[A._nz];
    
    for(int i = 0; i < A._nz; i++){
        file >> A._JA[i];
        if(mode == 0){
            A._JA[i]--;
        }
    }
    for(int i = 0; i < A._nz; i++){
        file >> A._IJA[i];
    }
    right._vect = new double[A._n];
    for(int i = 0; i < A._n; i++){
        file >> right._vect[i];
    }
    right._n = A._n;
    file.close();
}

void Equation::SolveUsingUMFPACK(){
    solution._n = A._n;
    solution._vect = new double[solution._n];
    double *null = (double *) NULL ;
    void *Symbolic ;
    void *Numeric ;
    LOG_DURATION("UMFPACK_factorize"){
        (void) umfpack_di_symbolic (A._n, A._n, A._IA, A._JA, null, &Symbolic, null, null) ;
        int err = umfpack_di_numeric (A._IA, A._JA, A._IJA, Symbolic, &Numeric, null, null) ;
        cout << "UMFPACK_factorize_report " << err << endl;
    }
    umfpack_di_free_symbolic(&Symbolic) ;
    LOG_DURATION("UMFPACK_solve"){
        int err =  umfpack_di_solve (UMFPACK_A, A._IA, A._JA, A._IJA, solution._vect, right._vect, Numeric, null, null) ;
        cout << "UMFPACK_solve_report " << err << endl;
    }
    umfpack_di_free_numeric(&Numeric) ;
}
void Equation::SolveUsingSPARSKITaniILU(int k){
    int lfil = k;
    int iwk = A._nz * 10 * (k + 1) * (k + 1);
    int* levs = new int[iwk];
    int* jw = new int[500 * 3 * A._nz];
    double* w = new double[500 * A._nz];
    int ierr = 0;
    double* rW = new double[iwk];
    int* iW = new int[iwk];
    LOG_DURATION("SPARSKIT_precond"){
        iluk_(&A._n, A._IJA, A._JA, A._IA, &lfil, rW, iW + A._n + 1, iW, levs, &iwk, w, jw, &ierr);
    }
    cout << "SPARSKIT_precond_report " << ierr << endl;
    delete[] w;
    delete[] jw;
    delete[] levs;

    int IPREVEC = A._n;
    int IMATVEC = A._n;
    double RESID = 1.0e-13;
    int ITER = 1000000;
    int MW = A._n;
    int NW = 8;
    double* WORK = new double[NW * A._n];
    solution._n = A._n;
    solution._vect = new double[A._n];
    for(int i = 0; i < A._n; i++){ solution._vect[i] = 0.0; };
    int INFO = 0;
    int NUNIT = 0;
    int n = A._n;

    void(*prev)(int*, int*, double*, double*, int*, double*) = prevec0_;
    void(*matv)(int*, double*, double*, double*, double*, int*, int*, double*) = matvec_;
    LOG_DURATION("Ani2D_solve"){
        slpbcgs_(prev, &IPREVEC, iW, rW, matv, &IMATVEC, A._IA, A._JA, A._IJA, 
        WORK, &MW, &NW, &n, right._vect, solution._vect, &ITER, &RESID, &INFO, &NUNIT);
    }
    cout << "Ani2D_solve_report " << INFO << endl;
    cout << "num_iters " << ITER << endl;
    delete[] WORK;
    delete[] rW;
    delete[] iW;
};