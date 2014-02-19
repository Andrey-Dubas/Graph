#include "GraphicLib.h"
#include <math.h>
#include <windows.h>
#include <stdio.h>

const int len=4;
const int size=4;



bool operator==(const point& p1, const point& p2){
	return p1.x==p2.x&&p1.y==p2.y&&p1.z==p2.z;
}
point operator*(const point& p1, const point& p2){
	return point(p1.z*p2.y - p1.y*p2.z, p1.x*p2.z - p1.z*p2.x, p1.y*p2.x - p1.x*p2.y);
}
point operator/(const point& p1, float p2){
	return point(p1.x/p2, p1.y/p2, p1.z/p2); 
}

const point operator*=(point& p, float num){
	p.x*=num; p.y*=num; p.z*=num;
	return p;
}

point operator-(const point& p1, const point& p2){
	return point(p1.x-p2.x, p1.y-p2.y, p1.z-p2.z);
}

point operator+(const point& p1, const point& p2){
	return point(p1.x+p2.x, p1.y+p2.y, p1.z+p2.z);
}

point operator*(const point& p1, float mul){
	return point(p1.x*mul, p1.y*mul, p1.z*mul);
}

void Mul(float** m1, float**m2, float** rez){
	for(int i=0; i<len; ++i)
		for(int j=0; j<len; ++j){
			rez[i][j] = 0;
			for(int k=0; k<len; k++) 
				rez[i][j] += m1[i][k]*m2[k][j];
		}
}

void Mul(float **m, float *v, float* rez){
	for(int i=0; i<len; ++i){
		rez[i] = 0;
		for(int k=0; k<len; k++) 
			rez[i] += m[i][k]*v[k];
	}
}

float** createDiagonalMatrix(size_t size){
	float** m = new float*[size];
	for(int i=0;i<len; ++i){
		m[i] = new float[size];
		memset(m[i], 0, size*sizeof(float));
		m[i][i] = 1;
	}
	return m;
}



namespace Evclid{

	

	void rotateMatrix(float **m, vector v){
		const int n=4;
		float*** m_arr;
		m_arr = new float**[4];
		for(int i=0; i<n; ++i) m_arr[i] = matrixINIWithDiag<4>();

		Evclid::rotateMatrix<1, 2>(m_arr[0], v.x);
		Evclid::rotateMatrix<0, 2>(m_arr[1], v.y);
		Evclid::rotateMatrix<0, 1>(m_arr[2], v.z);

		Mul(m_arr[0], m_arr[1], m_arr[3]);
		Mul(m_arr[3], m_arr[2], m);

		for(int i=0; i<n; ++i){
			matrixFREE<4>(m_arr[i]);
		}
		delete [] m_arr;
	}

	void moveMatrix(float**m, vector offset){
		m[0][len-1] = offset.x;
		m[1][len-1] = offset.y;
		m[2][len-1] = offset.z;
	}

	point move(point input, vector offset){
		float** m = createDiagonalMatrix(len);
		m[0][len-1] = offset.x;
		m[1][len-1] = offset.y;
		m[2][len-1] = offset.z;
		float rez[4], v[4];
		input(v);
		Mul((float**)m, (float*)v, (float*)rez);
		
		for(int i=0;i<len; i++) delete[] m[i]; delete[] m;
		return point(rez);
	}

};








void CentralProectionMatrix(float** m, vector eyePoint){
	for(int i=0; i<4; i++){
		memset(m[i], 0, 4*sizeof(float));
		m[i][i]=1;
	}
	m[3][0] = -1./eyePoint.x;
	m[3][1] = -1./eyePoint.y;
	m[3][2] = -1./eyePoint.z;
}

bool matrixCompare(float** m1, size_t s1, float** m2, size_t s2){
	if(s1!=s2) return false;
	for(size_t i=0; i<s1; ++i){
		for(size_t j=0; j<s1; ++j){
			if(m1[i][j]!=m2[i][j]) return false;
		}
	}
	return true;
}

void matrixPrint(float** m, size_t row, size_t col){
	OutputDebugStringA("\n");
	char str[10];
	for(size_t i=0; i<row; ++i){
		for(size_t j=0; j<col; ++j){
			_gcvt(m[i][j], 3, str);
			strcat(str, "  ");
			OutputDebugStringA(str);
		}
		OutputDebugStringA("\n");
	}
	
}

inline float hypotenuse(float x1, float y1, float x2, float y2){
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

float triangleSquare(float x1, float y1, float x2, float y2, float x3, float y3){
	float side1 = hypotenuse(x1, y1, x2, y2);
	float side2 = hypotenuse(x2, y2, x3, y3);
	float side3 = hypotenuse(x1, y1, x3, y3);
	float halfPerimeter = (side1+side2+side3)/2.; 
	return sqrt(halfPerimeter*(halfPerimeter-side1)*(halfPerimeter-side2)*(halfPerimeter-side3));
}

bool isInTriangle(float xa, float ya, float xb, float yb, float xc, float yc, float x, float y){

	if(x<min(xa, min(xb, xc)) || x > max(xa, max(xb, xc))) return false;
	if(y<min(ya, min(yb, yc)) || y > max(ya, max(yb, yc))) return false;

	float sFull = triangleSquare(xa, ya, xb, yb, xc, yc);
	float s1 = triangleSquare(xa, ya, xb, yb, x, y);
	float s2 = triangleSquare(xa, ya, x, y, xc, yc);
	float s3 = triangleSquare(x, y, xb, yb, xc, yc);

	if(sFull*1.01>s1+s2+s3){
		return true;
	}
	return false;
}

point outOfTriangle(point outPoint, point l1, point l2){
	point middle = (l1+l2)/2;
	point externalVector = outPoint - middle;
	return externalVector/(hypotenuse(externalVector.x, externalVector.y, 0));
}

point getTriangleCenter(const point& A, const point& B, const point& C){
	return point((A.x+B.x+C.x)/3., (A.y+B.y+C.y)/3., (A.z+B.z+C.z)/3.);
}

vector normalToSurface(const point& A, const point& B, const point& C){
	vector v1 = A-B, v2 = B-C;
	return v1*v2;
}

int factorial(int n){
	if (n==0){
		return 1;
	}
	else{
		return n*factorial(n-1);
	}
}

int pascalKoef(int n, int k){
	return factorial(n)/(factorial(n-k)*factorial(k));
}

point vectorMul(vector v1, vector v2){
	return point(v1.y*v2.z-v2.y*v1.z, -(v1.x*v2.z-v2.x*v1.z), v1.x*v2.y-v2.x*v1.y);
}

float scalarMul(vector v1, vector v2){
	return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}