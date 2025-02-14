#include <stdio.h>
#include <math.h>

#define PI 3.14

/*
Written by Harry Hescott
Start Date: 11th Feb 2025
*/

typedef struct {
    float real;
    float imag;
} complex;

typedef struct {
    complex x;
    complex y;
    complex z;
    float magnitude;  // Magnitude of the vector
	float angle[3]; // Angle against the X, Y, Z axes
} vector;

void get_magnitude(vector* vector)
{
	vector->magnitude = sqrtf(vector->x.real * vector->x.real + vector->x.imag * vector->x.imag
							+ vector->y.real * vector->y.real + vector->y.imag * vector->y.imag
							+ vector->z.real * vector->z.real + vector->z.imag * vector->z.imag);
	return;
}

vector add_vector(vector vectorOUT, vector* vectorA, vector* vectorB)
{	
	vectorOUT.x.real = vectorA->x.real + vectorB->x.real;
	vectorOUT.x.imag = vectorA->x.imag + vectorB->x.imag;
	vectorOUT.y.real = vectorA->y.real + vectorB->y.real;
	vectorOUT.y.imag = vectorA->y.imag + vectorB->y.imag;
	vectorOUT.z.real = vectorA->z.real + vectorB->z.real;
	vectorOUT.z.imag = vectorA->z.imag + vectorB->z.imag;
	return vectorOUT;
}

void set_values(vector* vector, float a, float b, float c, float d, float e, float f)
{
	vector->x.real = a; vector->x.imag = b;
	vector->y.real = c; vector->y.imag = d; 
	vector->z.real = e; vector->z.imag = f;
}

float dot_product(vector* vectorA, vector* vectorB)
{
	float dot = 0;
	if((vectorA == NULL) || (vectorB == NULL)){return -1;}
	float acompA = sqrt(vectorA->x.real*vectorA->x.real + vectorA->x.imag*vectorA->x.imag);
	float acompB = sqrt(vectorA->y.real*vectorA->y.real + vectorA->y.imag*vectorA->y.imag);
	float acompC = sqrt(vectorA->z.real*vectorA->z.real + vectorA->z.imag*vectorA->z.imag);
	float bcompA = sqrt(vectorB->x.real*vectorB->x.real + vectorB->x.imag*vectorB->x.imag);
	float bcompB = sqrt(vectorB->y.real*vectorB->y.real + vectorB->y.imag*vectorB->y.imag);
	float bcompC = sqrt(vectorB->z.real*vectorB->z.real + vectorB->z.imag*vectorB->z.imag);
	dot = acompA * bcompA + acompB * bcompB + acompC * bcompC;
	return dot;
}

void angle(vector* vector)
{
	get_magnitude(vector);
	float A = sqrt(vector->x.real*vector->x.real + vector->x.imag*vector->x.imag);
	float B = sqrt(vector->y.real*vector->y.real + vector->y.imag*vector->y.imag);
	float C = sqrt(vector->z.real*vector->z.real + vector->z.imag*vector->z.imag);
	vector->angle[0] = acos(A / vector->magnitude);
	vector->angle[1] = acos(B / vector->magnitude);
	vector->angle[2] = acos(C / vector->magnitude);
	return;
}

// int angle[3] is decayed to a pointer to array[0] in compile time
void create_matrix(float (*matrix)[3], float angle[3])
{
	/*
		a = alpha
		b = beta
		y = gamma
		c = cos
		s = sin
		code below calculates the angles as per
		https://en.wikipedia.org/wiki/Rotation_matrix
	*/
	float val = PI / 180;
	float anglex = angle[0] * val; float angley = angle[1] * val; float anglez = angle[2] * val; 
	float ca = cos(anglex); float sa = sin(anglex);
	float cb = cos(angley); float sb = sin(angley);
	float cy = cos(anglez); float sy = sin(anglez);
	matrix[0][0] = cb*cy; matrix[1][0] = cb*cy; matrix[2][0] = -sb;
	matrix[0][1] = sa*sb*cy - ca*sy;
	matrix[0][2] = ca*sb*cy + sa*sy;
	matrix[1][1] = sa*sb*sy+ca*cy;
	matrix[1][2] = ca*sb*sy-sa*cy;
	matrix[2][1] = sa*cb;
	matrix[2][2] = ca*cb;
	return;
}

// Very computationally heavy, use sparingly :3
void rotate(vector* vector, float angle[3])
{
	float matrix[3][3];
	float result[3];
	float A = sqrt(vector->x.real*vector->x.real + vector->x.imag*vector->x.imag);
	float B = sqrt(vector->y.real*vector->y.real + vector->y.imag*vector->y.imag);
	float C = sqrt(vector->z.real*vector->z.real + vector->z.imag*vector->z.imag);
	float vct[3] = {A, B, C};
	create_matrix(matrix, angle);
	// Maths time
	// Using https://mathinsight.org/matrix_vector_multiplication
    for (int i = 0; i < 3; i++) {
        result[i] = 0; // Initialize the result[i] to zero before summing
        for (int j = 0; j < 3; j++) {
            result[i] += matrix[i][j] * vct[j];
        }
    }

	printf("%f", matrix[0][0]);
	return;
}

int main(int argc, char **argv)
{
	vector vectA;
	set_values(&vectA, 5, 3, 2, -56, -9, 3);
	get_magnitude(&vectA);
	angle(&vectA);
	float angles[3] = {40.2, 276.4, 2.0};
	rotate(&vectA, angles);
	printf("%f\n", vectA.x.real);
	printf("%f\n", vectA.y.real);
	printf("%f\n", vectA.x.imag);
	printf("%f\n", vectA.magnitude);
	vector vectC;

	return 0;
}