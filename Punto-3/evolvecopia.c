#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define FLOAT float
#define PI 3.141592653589793
#define G_GRAV 39.486 //units of ua+3 msun-1 yr-1

FLOAT * get_memory(int n_points);
int * get_memory_int(int n_points);
void print_status(FLOAT *x, FLOAT *y, FLOAT *z, FLOAT *vx, FLOAT *vy, FLOAT *vz, FLOAT *ax, FLOAT *ay, FLOAT *az, int n_points);
void get_acceleration(FLOAT *ax, FLOAT *ay, FLOAT *az, FLOAT *x, FLOAT *y, FLOAT *z, FLOAT *mass, int n_points, int *ID);
FLOAT get_kinetic(FLOAT *v_x, FLOAT *v_y, FLOAT *v_z, FLOAT *mass, int n_points);
FLOAT get_potential(FLOAT *x, FLOAT *y, FLOAT *z, FLOAT *mass, int n_points);
int count_lines(char *filename);
void rungekutta(int n_points, int n_steps, FLOAT *x, FLOAT *y, FLOAT *z, FLOAT *v_x, FLOAT *v_y, FLOAT *v_z ,FLOAT *a_x, FLOAT *a_y, FLOAT *a_z, FLOAT *mass, int *ID,  int h);

int main(int argc, char **argv){
    
    FLOAT T = atof(argv[1]);
    int M = atoi(argv[2]);
    char *filename = argv[3];
    
    int n_points;
    n_points = count_lines(filename);
    
    /*Declaración de variables:*/
    
    int *ID;
    FLOAT *x;
    FLOAT *y;
    FLOAT *z;
    FLOAT *v_x;
    FLOAT *v_y;
    FLOAT *v_z;
    FLOAT *a_x;
    FLOAT *a_y;
    FLOAT *a_z;
    FLOAT *mass;
    
    /*Alocación en memoria*/
    
    x = get_memory(n_points);
    y = get_memory(n_points);
    z = get_memory(n_points);
    v_x = get_memory(n_points);
    v_y = get_memory(n_points);
    v_z = get_memory(n_points);
    a_x = get_memory(n_points);
    a_y = get_memory(n_points);
    a_z = get_memory(n_points);
    mass = get_memory(n_points);
    ID = get_memory_int(n_points);
    
    /*timestep variables*/
    FLOAT h= 0.01;
    int n_steps = (int)(T/h);
    int i,j,k;
    
    /*Lectura*/
    FILE *in1;
    in1 = fopen("IC.dat","r");
    
    for (i=0; i<n_points; i++) {
        fscanf(in1,"%d %f %f %f %f %f %f \n", &(ID[i]),&(x[i]),&(y[i]),&(z[i]),&(v_x[i]),&(v_y[i]),&(v_z[i]));
        mass[i] = 1.0;
        a_x[i] = 0.0;
        a_y[i] = 0.0;
        a_z[i] = 0.0;
    }
    
    fclose(in1);
    
    FILE *in2;
    
    in2 = fopen("evolvedmom1.dat","w");
    
    rungekutta(n_points, n_steps, x, y, z, v_x, v_y, v_z ,a_x, a_y, a_z, mass, ID, h);
    
    /*Términos para Runge-Kutta con su respectiva alocación en memoria*/
    
    FLOAT  *k_1_x;
    FLOAT  *k_1_y;
    FLOAT  *k_1_z;
    
    FLOAT  *k_1_v_x;
    FLOAT  *k_1_v_y;
    FLOAT  *k_1_v_z;
    
    FLOAT  *k_2_x;
    FLOAT  *k_2_y;
    FLOAT  *k_2_z;
    
    FLOAT  *k_2_v_x;
    FLOAT  *k_2_v_y;
    FLOAT  *k_2_v_z;
    
    FLOAT  *k_3_x;
    FLOAT  *k_3_y;
    FLOAT  *k_3_z;
    
    FLOAT  *k_3_v_x;
    FLOAT  *k_3_v_y;
    FLOAT  *k_3_v_z;
    
    FLOAT  *k_4_x;
    FLOAT  *k_4_y;
    FLOAT  *k_4_z;
    
    FLOAT  *k_4_v_x;
    FLOAT  *k_4_v_y;
    FLOAT  *k_4_v_z;
    
    FLOAT *xtemp;
    FLOAT *ytemp;
    FLOAT *ztemp;
    
    FLOAT *v_xtemp;
    FLOAT *v_ytemp;
    FLOAT *v_ztemp;
    
    FLOAT *a_xtemp;
    FLOAT *a_ytemp;
    FLOAT *a_ztemp;
    
    k_1_x = get_memory(n_points);
    k_1_y = get_memory(n_points);
    k_1_z = get_memory(n_points);
    
    k_1_v_x = get_memory(n_points);
    k_1_v_y = get_memory(n_points);
    k_1_v_z = get_memory(n_points);
    
    k_2_x = get_memory(n_points);
    k_2_y = get_memory(n_points);
    k_2_z = get_memory(n_points);
    
    k_2_v_x = get_memory(n_points);
    k_2_v_y = get_memory(n_points);
    k_2_v_z = get_memory(n_points);
    
    k_3_x = get_memory(n_points);
    k_3_y = get_memory(n_points);
    k_3_z = get_memory(n_points);
    
    k_3_v_x = get_memory(n_points);
    k_3_v_y = get_memory(n_points);
    k_3_v_z = get_memory(n_points);
    
    k_4_x = get_memory(n_points);
    k_4_y = get_memory(n_points);
    k_4_z = get_memory(n_points);
    
    k_4_v_x = get_memory(n_points);
    k_4_v_y = get_memory(n_points);
    k_4_v_z = get_memory(n_points);
    
    xtemp = get_memory(n_points);
    ytemp = get_memory(n_points);
    ztemp = get_memory(n_points);
    
    v_xtemp = get_memory(n_points);
    v_ytemp = get_memory(n_points);
    v_ztemp = get_memory(n_points);
    
    a_xtemp = get_memory(n_points);
    a_ytemp = get_memory(n_points);
    a_ztemp = get_memory(n_points);
    
    for(i=0;i<n_steps;i++){
        
        get_acceleration(a_x, a_y, a_z, x, y, z, mass, n_points,ID);
        for(j=0;j<n_points;j++){
            
            k_1_x[j] = v_x[j];
            k_1_y[j] = v_y[j];
            k_1_z[j] = v_z[j];
            
            k_1_v_x[j] = a_x[j];
            k_1_v_y[j] = a_y[j];
            k_1_v_z[j] = a_z[j];
            
            
            //FIRST STEP
            
            xtemp[j] = x[j] + (h/2.0)*k_1_x[j];
            ytemp[j] = y[j] + (h/2.0)*k_1_y[j];
            ztemp[j] = z[j] + (h/2.0)*k_1_z[j];
            
            v_xtemp[j] = v_x[j] + (h/2.0)*k_1_v_x[j];
            v_ytemp[j] = v_y[j] + (h/2.0)*k_1_v_y[j];
            v_ztemp[j] = v_z[j] + (h/2.0)*k_1_v_z[j];
            
            k_2_x[j] = v_xtemp[j];
            k_2_y[j] = v_ytemp[j];
            k_2_z[j] = v_ztemp[j];
            
        }
        
        get_acceleration(a_xtemp,a_ytemp,a_ztemp,xtemp,ytemp,ztemp, mass, n_points, ID);
        
        for(j=0;j<n_points;j++){
            
            k_2_v_x[j] = a_xtemp[j];
            k_2_v_y[j] = a_ytemp[j];
            k_2_v_z[j] = a_ztemp[j];
            
            
            //SECOND STEP
            
            xtemp[j] = x[j] + (h/2.0)*k_2_x[j];
            ytemp[j] = y[j] + (h/2.0)*k_2_y[j];
            ztemp[j] = z[j] + (h/2.0)*k_2_z[j];
            
            v_xtemp[j] = v_x[j] + (h/2.0)*k_2_v_x[j];
            v_ytemp[j] = v_y[j] + (h/2.0)*k_2_v_y[j];
            v_ztemp[j] = v_z[j] + (h/2.0)*k_2_v_z[j];
            
            k_3_x[j] = v_xtemp[j];
            k_3_y[j] = v_ytemp[j];
            k_3_z[j] = v_ztemp[j];
            
        }
        
        get_acceleration(a_xtemp,a_ytemp,a_ztemp,xtemp,ytemp,ztemp, mass, n_points,ID);
        
        for(j=0;j<n_points;j++){
            
            k_3_v_x[j] = a_xtemp[j];
            k_3_v_y[j] = a_ytemp[j];
            k_3_v_z[j] = a_ztemp[j];
            
            
            //THIRD STEP
            
            xtemp[j] = x[j] + h*k_3_x[j];
            ytemp[j] = y[j] + h*k_3_y[j];
            ztemp[j] = z[j] + h*k_3_z[j];
            
            v_xtemp[j] = v_x[j] + h*k_3_v_x[j];
            v_ytemp[j] = v_y[j] + h*k_3_v_y[j];
            v_ztemp[j] = v_z[j] + h*k_3_v_z[j];
            
            k_4_x[j] = v_xtemp[j];
            k_4_y[j] = v_ytemp[j];
            k_4_z[j] = v_ztemp[j];
            
        }
        
        get_acceleration(a_xtemp,a_ytemp,a_ztemp,xtemp,ytemp,ztemp, mass, n_points,ID);
        
        for(j=0;j<n_points;j++){
            
            k_4_v_x[j] = a_xtemp[j];
            k_4_v_y[j] = a_ytemp[j];
            k_4_v_z[j] = a_ztemp[j];
            
            
            //FOURTH STEP
            
            x[j] = x[j] + h*(1.0/6.0)*(k_1_x[j]+2*k_2_x[j]+2*k_3_x[j]+k_4_x[j]);
            y[j] = y[j] + h*(1.0/6.0)*(k_1_y[j]+2*k_2_y[j]+2*k_3_y[j]+k_4_y[j]);
            z[j] = z[j] + h*(1.0/6.0)*(k_1_z[j]+2*k_2_z[j]+2*k_3_z[j]+k_4_z[j]);
            
            v_x[j] = v_x[j] + h*(1.0/6.0)*(k_1_v_x[j]+2*k_2_v_x[j]+2*k_3_v_x[j]+k_4_v_x[j]);
            v_y[j] = v_y[j] + h*(1.0/6.0)*(k_1_v_y[j]+2*k_2_v_y[j]+2*k_3_v_y[j]+k_4_v_y[j]);
            v_z[j] = v_z[j] + h*(1.0/6.0)*(k_1_v_z[j]+2*k_2_v_z[j]+2*k_3_v_z[j]+k_4_v_z[j]);
        }
    }
    
    for (i=0; i<n_points; i++) {
        fprintf(in2,"%d %f %f %f %f %f %f \n",ID[i],x[i],y[i],z[i],v_x[i],v_y[i],v_z[i]);
    }
    
    fclose(in2);
    
    return 0;

}


void get_acceleration(FLOAT *ax, FLOAT *ay, FLOAT *az, FLOAT *x, FLOAT *y, FLOAT *z, FLOAT *mass, int n_points, int *ID){
    int i,j;
    FLOAT r_ij;
    for(i=0;i<n_points;i++){
        ax[i]=0.0;
        ay[i]=0.0;
        az[i]=0.0;
        
        
        /*Las partículas sólo sienten la masa de aquellas que tienen ID negativo*/
        
        for(j=0;j<n_points;j++){
            if(j!=i && ID[j]<0){
                r_ij = (pow((x[i] - x[j]),2.0) + pow((y[i] - y[j]),2.0) + pow((z[i] - z[j]),2.0));
                r_ij = sqrt(r_ij);
                ax[i] += -G_GRAV *mass[j]/ pow(r_ij,1.5) * (x[i] - x[j]);
                ay[i] += -G_GRAV *mass[j]/ pow(r_ij,1.5) * (y[i] - y[j]);
                az[i] += -G_GRAV *mass[j] / pow(r_ij,1.5) * (z[i] - z[j]);
                }
            }
    }
}

FLOAT get_kinetic(FLOAT *v_x, FLOAT *v_y, FLOAT *v_z, FLOAT *mass, int n_points){
    int i;
    FLOAT kinetic;
    kinetic = 0.0;
    
    
    for (i=0; i<n_points; i++) {
        kinetic += 0.5*mass[i]*(pow(v_x[i],2)+pow(v_y[i],2)+pow(v_z[i],2));
    }
    return kinetic;
}

FLOAT get_potential(FLOAT *x, FLOAT *y, FLOAT *z, FLOAT *mass, int n_points){
    int i,j;
    FLOAT r_ij;
    FLOAT potential;
    potential = 0.0;
    for (i=0; i<n_points; i++) {
        for (j=0; j<n_points; j++) {
            if (i!=j) {
                r_ij = (pow((x[i] - x[j]),2.0) + pow((y[i] - y[j]),2.0) + pow((z[i] - z[j]),2.0));
                r_ij = sqrt(r_ij);
                potential += -G_GRAV * (mass[i] * mass[j]) / r_ij;
            }
        }
    }
    return potential/2;
}

FLOAT * get_memory(int n_points){
    FLOAT * x; 
    if(!(x = malloc(sizeof(FLOAT) * n_points))){
        printf("problem with memory allocation");
        exit(1);
    }
    return x;
}

int * get_memory_int(int n_points){
    int * x;
    if(!(x = malloc(sizeof(int) * n_points))){
        printf("problem with memory allocation");
        exit(1);
    }
    return x;
}

int count_lines(char *filename){
    FILE *in;
    int n_lines;
    int c;
    if(!(in=fopen(filename, "r"))){
        printf("problem opening file %s\n", filename);
        exit(1);
    }
    
    n_lines = 0;
    do{
        c = fgetc(in);
        if(c=='\n'){
            n_lines++;
        }
    }while(c!=EOF);
    
    rewind(in);
    fclose(in);
    return n_lines;
}

void rungekutta(int n_points, int n_steps, FLOAT *x, FLOAT *y, FLOAT *z, FLOAT *v_x, FLOAT *v_y, FLOAT *v_z ,FLOAT *a_x, FLOAT *a_y, FLOAT *a_z, FLOAT *mass, int *ID, int h){}
