#include "matrix.h"
#include <vector>
void PrintResultsUMFPACK(string filename){
    cout << "filename " << filename << endl;
    Equation task(filename, 0);
    cout << "order " << task.A._n << endl;
    cout << "number_of_nonzero_elements " << task.A._nz << endl;
    task.SolveUsingUMFPACK();
    Vector residual;
    task.A.MultByVect(task.solution, residual);
    task.right.subtract(residual);
    cout << "residual_norm = " << residual.norm() << endl;
}
void PrintResultsSPARSKITaniILU(string filename, int k){
    cout << "filename " << filename << endl;
    cout << "preconditiner ILU" << k << endl;
    Equation task(filename, 1);
    cout << "order " << task.A._n << endl;
    cout << "number_of_nonzero_elements " << task.A._nz << endl;
    task.SolveUsingSPARSKITaniILU(k);
    Vector residual;
    task.A.MultByVect(task.solution, residual);
    task.right.subtract(residual);
    cout << "residual_norm = " << residual.norm() << endl;
}
int main(){
    // vector<string> equations = {"data/1.dat", "data/2.dat", "data/3.dat", "data/4.dat"};
    vector<string> equations = {"data/3.dat"};
    for(string file : equations){
        for(int i = 0 ; i < 3; i++){
            PrintResultsSPARSKITaniILU(file, i);
            cout << endl;
        }
    }
    return 0;
}