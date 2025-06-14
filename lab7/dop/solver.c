#include "interpolation.h"

Polynomial lagrange_interpolation(Point points[], int n) {
    Polynomial result;
    result.degree = n - 1;
    
    for (int i = 0; i < MAX_POINTS; i++) {
        result.coefficients[i] = 0.0;
    }
    
    for (int i = 0; i < n; i++) {
        double basis_poly[MAX_POINTS] = {0};
        basis_poly[0] = 1.0;
        int current_degree = 0;
        
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double factor = 1.0 / (points[i].x - points[j].x);
                
                double temp_poly[MAX_POINTS] = {0};
                
                for (int k = current_degree; k >= 0; k--) {
                    temp_poly[k + 1] += basis_poly[k]; // x * coef
                    temp_poly[k] -= basis_poly[k] * points[j].x; // -x_j * coef
                }
                
                current_degree++;
                
                for (int k = 0; k <= current_degree; k++) {
                    basis_poly[k] = temp_poly[k] * factor;
                }
            }
        }
        
        for (int k = 0; k <= current_degree; k++) {
            result.coefficients[k] += points[i].y * basis_poly[k];
        }
    }
    
    return result;
}

double evaluate_polynomial(Polynomial poly, double x) {
    double result = 0.0;
    double x_power = 1.0;
    
    for (int i = 0; i <= poly.degree; i++) {
        result += poly.coefficients[i] * x_power;
        x_power *= x;
    }
    
    return result;
}

void print_polynomial(Polynomial poly) {
    printf("\nInterpolation polynomial:\n");
    printf("P(x) = ");
    
    int first_term = 1;
    for (int i = 0; i <= poly.degree; i++) {
        if (fabs(poly.coefficients[i]) > 1e-10) {
            if (!first_term) {
                if (poly.coefficients[i] > 0) {
                    printf(" + ");
                } else {
                    printf(" - ");
                    poly.coefficients[i] = -poly.coefficients[i];
                }
            } else if (poly.coefficients[i] < 0) {
                printf("-");
                poly.coefficients[i] = -poly.coefficients[i];
            }
            
            if (i == 0) {
                printf("%.6f", poly.coefficients[i]);
            } else if (i == 1) {
                if (fabs(poly.coefficients[i] - 1.0) < 1e-10) {
                    printf("x");
                } else {
                    printf("%.6f*x", poly.coefficients[i]);
                }
            } else {
                if (fabs(poly.coefficients[i] - 1.0) < 1e-10) {
                    printf("x^%d", i);
                } else {
                    printf("%.6f*x^%d", poly.coefficients[i], i);
                }
            }
            first_term = 0;
        }
    }
    
    if (first_term) {
        printf("0");
    }
    
    printf("\n\n");
}