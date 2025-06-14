#include "interpolation.h"

int input_points(Point points[]) {
    int choice, n;
    
    printf("Choose input method for points:\n");
    printf("1. Enter points manually\n");
    printf("2. Generate points automatically\n");
    printf("Your choice: ");
    scanf("%d", &choice);
    
    printf("Enter number of points (2-%d): ", MAX_POINTS);
    scanf("%d", &n);
    
    if (n < 2 || n > MAX_POINTS) {
        printf("Error: number of points must be between 2 and %d\n", MAX_POINTS);
        return -1;
    }
    
    switch (choice) {
        case 1:
            printf("Enter points in format (x,y):\n");
            for (int i = 0; i < n; i++) {
                printf("Point %d: ", i + 1);
                scanf("%lf %lf", &points[i].x, &points[i].y);
            }
            break;
            
        case 2:
            generate_points(points, n);
            printf("Generated points:\n");
            for (int i = 0; i < n; i++) {
                printf("Point #%d: (%.2f, %.2f)\n", i + 1, points[i].x, points[i].y);
            }
            break;
            
        default:
            printf("Error: invalid choice\n");
            return -1;
    }
    
    return n;
}

void generate_points(Point points[], int n) {
    for (int i = 0; i < n; i++) {
        points[i].x = -3.0 + (6.0 * i) / (n - 1); // [-3; 3]
        points[i].y = sin(points[i].x) + ((double)rand() / RAND_MAX - 0.5) * 0.3;
    }
}