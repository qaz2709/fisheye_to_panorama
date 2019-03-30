#pragma once


static constexpr double PI = 3.14159265358979323846264338327950288;

void setRotationMatrix(double r, double p, double y, double R[3][3]);

void matrix_mult_matrix(double m1[3][3],double m2[3][3],double result[3][3]);

inline constexpr double DEGREE_TO_RAD(double degree) { return degree * 2.0 * PI / 360; }
