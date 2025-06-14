#include "interpolation.h"

void create_plot(Polynomial poly, Point points[], int n) {
    FILE *gnuplot_pipe;
    FILE *data_file;
    FILE *poly_file;
    
    data_file = fopen("points.dat", "w");
    if (data_file == NULL) {
        printf("Error creating data file\n");
        return;
    }
    
    for (int i = 0; i < n; i++) {
        fprintf(data_file, "%.6f %.6f\n", points[i].x, points[i].y);
    }
    fclose(data_file);
    
    poly_file = fopen("polynomial.dat", "w");
    if (poly_file == NULL) {
        printf("Error creating polynomial file\n");
        return;
    }
    
    double x_min = points[0].x, x_max = points[0].x;
    for (int i = 1; i < n; i++) {
        if (points[i].x < x_min) x_min = points[i].x;
        if (points[i].x > x_max) x_max = points[i].x;
    }
    
    double range = x_max - x_min;
    x_min -= range * 0.2;
    x_max += range * 0.2;
    
    int num_plot_points = 1000;
    for (int i = 0; i <= num_plot_points; i++) {
        double x = x_min + (x_max - x_min) * i / num_plot_points;
        double y = evaluate_polynomial(poly, x);
        fprintf(poly_file, "%.6f %.6f\n", x, y);
    }
    fclose(poly_file);
    
    gnuplot_pipe = popen("gnuplot -persistent", "w");
    if (gnuplot_pipe == NULL) {
        printf("Error running gnuplot. Make sure gnuplot is installed.\n");
        printf("Data saved to files points.dat and polynomial.dat\n");
        return;
    }
    
    fprintf(gnuplot_pipe, "set title 'Lagrange Interpolation Polynomial'\n");
    fprintf(gnuplot_pipe, "set xlabel 'x'\n");
    fprintf(gnuplot_pipe, "set ylabel 'y'\n");
    fprintf(gnuplot_pipe, "set grid\n");
    fprintf(gnuplot_pipe, "plot 'polynomial.dat' with lines title 'Polynomial', ");
    fprintf(gnuplot_pipe, "'points.dat' with points pointtype 7 pointsize 1.5 title 'Original Points'\n");
    
    pclose(gnuplot_pipe);
    
    printf("Plot created using gnuplot\n");
    printf("Data saved to files:\n");
    printf("- points.dat (original points)\n");
    printf("- polynomial.dat (polynomial points)\n");
}