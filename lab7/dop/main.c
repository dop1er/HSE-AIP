#include "interpolation.h"
#include <time.h>

int main() {
    Point points[MAX_POINTS];
    Polynomial poly;
    int n;
    
    printf("=== Lagrange Polynomial Interpolation Program ===\n\n");
    
    srand(time(NULL));
    
    n = input_points(points);
    if (n < 0) {
        return 1;
    }
    
    printf("\nCalculating interpolation polynomial...\n");
    poly = lagrange_interpolation(points, n);
    
    print_polynomial(poly);
    
    printf("Interpolation verification:\n");
    for (int i = 0; i < n; i++) {
        double calculated = evaluate_polynomial(poly, points[i].x);
        printf("P(%.2f) = %.6f, original y = %.6f, error = %.2e\n", 
               points[i].x, calculated, points[i].y, fabs(calculated - points[i].y));
    }
    printf("\n");
    
    printf("Creating plot...\n");
    create_plot(poly, points, n);
    
    char choice;
    printf("\nDo you want to evaluate the polynomial at an arbitrary point? (y/N): ");
    scanf(" %c", &choice);
    
    if (choice == 'y' || choice == 'Y') {
        double x;
        printf("Enter x value: ");
        scanf("%lf", &x);
        double result = evaluate_polynomial(poly, x);
        printf("P(%.6f) = %.6f\n", x, result);
    }
    
    return 0;
}