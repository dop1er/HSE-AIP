#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POINTS 20
#define MAX_DEGREE 19

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    double coefficients[MAX_POINTS];
    int degree;
} Polynomial;

int input_points(Point points[]);
void generate_points(Point points[], int n);

Polynomial lagrange_interpolation(Point points[], int n);
double evaluate_polynomial(Polynomial poly, double x);
void print_polynomial(Polynomial poly);

void create_plot(Polynomial poly, Point points[], int n);

#endif