#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define MAX_POINTS 2000

int read_file (float* points, char* filename) {

    int n = 0;
    float next[2];
    FILE* file_ptr;
    file_ptr = fopen(filename,"r");
    if (file_ptr == NULL) {
	printf ("error : could not open file %s for reading\n",filename);
	    exit(1);
    }
    while (fscanf (file_ptr,"%f %f",next,next+1) == 2) {
	    if (n < MAX_POINTS) {
	        points[2*n] = next[0];
	        points[2*n+1] = next[1];
	        n += 1;
	    } else {
	        printf ("Too many points in file %s\n",filename);
	        fclose (file_ptr);
	        exit(1);
        }
    }
    fclose (file_ptr);
    return n;
}

float calc_dist (float* u, float* v) {
    float diff_x = u[0] - v[0];
    float diff_y = u[1] - v[1];
    return sqrt(diff_x*diff_x + diff_y*diff_y);
}

float center_cost (int n, float* dist, int c1, int c2, int c3, int c4) {
    float cost = 0;
    for (int i=0;i<n;i++) {
	    float dist_1 = dist[i*n+c1];
	    float dist_2 = dist[i*n+c2];
	    float dist_3 = dist[i*n+c3];
        float dist_4 = dist[i*n+c4];
	    float min_dist = dist_1;
	    if (dist_2 < min_dist) {
	        min_dist = dist_2;
	    }
	    if (dist_3 < min_dist) {
	        min_dist = dist_3;
	    }
        if (dist_4 < min_dist) {
	        min_dist = dist_4;
	    }
	    if (min_dist > cost) {
	        cost = min_dist;
	    }
    }
    return cost;
}

int main (int argc, char** argv) {

    /* the dataset array */
    float points[2*MAX_POINTS];

    /* read filename from command line */
    if (argc < 2) {
	    printf ("Command usage : %s %s\n",argv[0],"filename");
	    return 1;
    }

    /* read dataset */
    int n = read_file (points,argv[1]);

    float dist[n*n];
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            dist[i*n+j] = calc_dist (points+2*i,points+2*j);
        }
    }
    
    double optimal_cost = DBL_MAX;
    int optimal_centers[4];
    int tuples_checked = 0;

    /* solve the 4-center problem exactly */
    for (int i=0;i<n-3;i++) {
        for (int j=i+1;j<n-2;j++) {
            for (int k=j+1;k<n-1;k++) {
                for (int l=k+1;l<n;l++) {
		            tuples_checked += 1;
		            double cost = center_cost (n, dist, i, j, k, l);
		            if (cost < optimal_cost) {
			            optimal_cost = cost;
			            optimal_centers[0] = i;
			            optimal_centers[1] = j;
			            optimal_centers[2] = k;
                        optimal_centers[3] = l;
                    }
		        }
		    }
	    }
    }

    /* print out the number of 4-tuples checked */
    printf ("number of 4-tuples checked = %d\n",tuples_checked);

    /* print the minimal cost for the 4-center problem */
    printf ("minimal cost = %g\n",optimal_cost);

    /* print an optimal solution to the 4 center problem */
    printf ("optimal centers : %d %d %d %d\n",
            optimal_centers[0],optimal_centers[1],
            optimal_centers[2],optimal_centers[3]);

    return 0;
}
