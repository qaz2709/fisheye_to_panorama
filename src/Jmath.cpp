#include "Jmath.h"
#include <math.h>


void setRotationMatrix(double r, double p, double y, double _R[3][3])
{
    double Rp[3][3], Ry[3][3], Rr[3][3], temp[3][3];

    Rp[0][0] = 1;               Rp[0][1] = 0;               Rp[0][2] = 0;
    Rp[1][0] = 0;               Rp[1][1] = cos(p);          Rp[1][2] = -sin(p);
    Rp[2][0] = 0;               Rp[2][1] = -Rp[1][2];       Rp[2][2] = Rp[1][1];

    Ry[0][0] = cos(y);          Ry[0][1] = 0;               Ry[0][2] = sin(y);
    Ry[1][0] = 0;               Ry[1][1] = 1;               Ry[1][2] = 0;
    Ry[2][0] = -Ry[0][2];       Ry[2][1] = 0;               Ry[2][2] = Ry[0][0];

    Rr[0][0] = cos(r);          Rr[0][1] = -sin(r);         Rr[0][2] = 0;
    Rr[1][0] = -Rr[0][1];       Rr[1][1] = Rr[0][0];        Rr[1][2] = 0;
    Rr[2][0] = 0;               Rr[2][1] = 0;               Rr[2][2] = 1;

    matrix_mult_matrix(Rr, Rp, temp);
    matrix_mult_matrix(temp, Ry, _R);//intrinsic
}

void matrix_mult_matrix(double m1[3][3],double m2[3][3],double result[3][3])
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result[i][j] = m1[i][0] * m2[0][j] + m1[i][1] * m2[1][j] + m1[i][2] * m2[2][j];
        }
    }

}
