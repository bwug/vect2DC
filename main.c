#include <stdio.h>
#include <math.h>

typedef struct {
    float real;
    float imag;
} complex;

typedef struct {
    complex x;
    complex y;
    complex z;
    float magnitude;  // Magnitude of the vector
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
	float acompA = vectorA->x.real*vectorA->x.real + vectorA->x.imag*vectorA->x.imag;
	float acompB = vectorA->y.real*vectorA->y.real + vectorA->y.imag*vectorA->y.imag;
	float acompC = vectorA->z.real*vectorA->z.real + vectorA->z.imag*vectorA->z.imag;
	float bcompA = vectorB->x.real*vectorB->x.real + vectorB->x.imag*vectorB->x.imag;
	float bcompB = vectorB->y.real*vectorB->y.real + vectorB->y.imag*vectorB->y.imag;
	float bcompC = vectorB->z.real*vectorB->z.real + vectorB->z.imag*vectorB->z.imag;
	dot = acompA * bcompA + acompB * bcompB + acompC * bcompC;
	return dot;
}

int main(int argc, char **argv)
{
	vector vectA;
	set_values(&vectA, 5, 3, 2, -56, -9, 3);
	get_magnitude(&vectA);
	printf("%f\n", vectA.x.real);
	printf("%f\n", vectA.y.real);
	printf("%f\n", vectA.x.imag);
	printf("%f\n", vectA.magnitude);
	vector vectC;

	return 0;
}
