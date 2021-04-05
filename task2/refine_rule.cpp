#include "for_ani2d.h"
#include "math.h"
#include <iostream>
#include <utility>
typedef std::pair<double, double> vect;
double t = 295;
int mult_sign(vect v_1, vect v_2){
    double res = v_1.first * v_2.second - v_1.second * v_2.first;
    if(res < 0){
        return -1;
    }
    else if(res == 0){
        return 0;
    }
    else{
        return 1;
    }
}
bool check(int a, int b, int c){
    if(a * b < 0.0 || b * c < 0.0 || c * a < 0.0){
        return 0;
    }
    else{
        return 1;
    }
}
void refine_rule(int* nE, int* IPE, double* XYP, int* verf, int* ilevel){
    std::cout << t << std::endl;
    double t_in_rad = t * M_PI / 180.0;
    double p_loc_x = 0.5 + 0.5 * cos(t_in_rad);
    double p_loc_y = 0.5 + 0.5 * sin(t_in_rad);
    // double p_loc_x = 0.75;
    // double p_loc_y = 0.75;
    for(int n = 0; n < *nE; n++){
        vect v_1(XYP[2 * (IPE[n * 3 + 0] - 1) + 0] - p_loc_x, XYP[2 * (IPE[n * 3 + 0] - 1) + 1] - p_loc_y);
        vect v_2(XYP[2 * (IPE[n * 3 + 1] - 1) + 0] - p_loc_x, XYP[2 * (IPE[n * 3 + 1] - 1) + 1] - p_loc_y);
        vect v_3(XYP[2 * (IPE[n * 3 + 2] - 1) + 0] - p_loc_x, XYP[2 * (IPE[n * 3 + 2] - 1) + 1] - p_loc_y);

        vect e_1(XYP[2 * (IPE[n * 3 + 0] - 1) + 0] - XYP[2 * (IPE[n * 3 + 2] - 1) + 0], XYP[2 * (IPE[n * 3 + 0] - 1) + 1] - XYP[2 * (IPE[n * 3 + 2] - 1) + 1]);
        vect e_2(XYP[2 * (IPE[n * 3 + 1] - 1) + 0] - XYP[2 * (IPE[n * 3 + 0] - 1) + 0], XYP[2 * (IPE[n * 3 + 1] - 1) + 1] - XYP[2 * (IPE[n * 3 + 0] - 1) + 1]);
        vect e_3(XYP[2 * (IPE[n * 3 + 2] - 1) + 0] - XYP[2 * (IPE[n * 3 + 1] - 1) + 0], XYP[2 * (IPE[n * 3 + 2] - 1) + 1] - XYP[2 * (IPE[n * 3 + 1] - 1) + 1]);

        // std::cout << *ilevel << " " << mult_sign(v_1, e_1) << " " << mult_sign(v_2, e_2) << " " << mult_sign(v_3, e_3) << std::endl;

        if(check(mult_sign(v_1, e_1), mult_sign(v_2, e_2), mult_sign(v_3, e_3)) == 0){
            verf[n] = 0;
        }
        else{
            verf[n] = 2;
        }

    }
}