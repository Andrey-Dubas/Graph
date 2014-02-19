

#ifndef GRAPHIC_LIB_H
#define GRAPHIC_LIB_H

#include <math.h>
//#include <tchar.h>
#include <Windows.h>

class Exception{
protected:
	wchar_t* message;
public:
	Exception(const wchar_t* mess, const char* func, const unsigned int row){
		static const wchar_t* inRow = L" in row: ";
		static const wchar_t* inFunc = L" in function ";
		message = new wchar_t[wcslen(mess)+1+wcslen(inFunc)+wcslen(inRow)+50];
		wcscpy(message, mess);

		wchar_t* endOfString=message;

		wcscat(endOfString, inRow);
		while(*(++endOfString)!=0);
		_itow(row, endOfString, 10);

		while(*(++endOfString)!=0);
		wcscpy(endOfString, inFunc);
		wchar_t fName[25];
		MultiByteToWideChar(CP_ACP, 0, func, 25, fName, 25);
		while(*(++endOfString)!=0);
		wcscat(endOfString, fName);

		dbg_printA();
	}

	~Exception(){
		delete [] message;
	}

	void dbg_printA(){
		char* out = new char[wcslen(message)+1];
		WideCharToMultiByte(CP_ACP, NULL, message, wcslen(message)+1, out, wcslen(message)+1, 0, 0);
		OutputDebugStringA(out);
	}
};

typedef Exception MathException;
typedef Exception PropertyExchangeException;

#define MATH_EXCEPTION(MESSAGE) new MathException(MESSAGE, __FUNCTION__, __LINE__)
#define PROPERTY_EXCEPTION(MESSAGE) new PropertyExchangeException(MESSAGE, __FUNCTION__, __LINE__)

#define MATRIXDIAGONAL(MATRIX, DIAGONAL)\
	for(int i=0;i<DIAGONAL; ++i) MATRIX[i][i]=1

template<int mSize>
void matrixFREE(float** m){
	for(int i=0;i<mSize; ++i) delete[] m[i];
	delete[] m;
}


template<int mSize>
float** matrixINI(){
	float **m = (float**)malloc(mSize*sizeof(float*));
	for(int i=0; i<mSize; ++i){
		m[i] = (float*)malloc(mSize*sizeof(float));
		memset(m[i], 0, mSize*sizeof(float));
	}
	return m;
}

template<int mSize>
float** matrixINIWithDiag(){
	float **m = (float**)malloc(mSize*sizeof(float*));
	for(int i=0; i<mSize; ++i){
		m[i] = (float*)malloc(mSize*sizeof(float));
		memset(m[i], 0, mSize*sizeof(float));
	}
	for(int i=0; i<mSize; ++i) m[i][i] = 1;
	return m;
}




struct point{
	friend const point operator*=(point& p, float num);
	friend point operator*(const point& p1, const point& p2);
	friend point operator/(const point& p, float num);
	friend point operator+(const point& , const point& );
	friend point operator-(const point& , const point& );
	friend point operator*(const point& , float );
	friend bool operator==(const point& , const point& );
	//friend operator float*()(point& p);
public:
	float x, y, z;
public:
	void operator()(float v[4]){
		v[0] = x; v[1] = y; v[2] = z; v[3] = 1; 
	}
	point operator-(){return point(-x, -y, -z);}
	point operator-(point obj){
		point p(this->x-obj.x, this->y-obj.y, this->z-obj.z);
		return p;
	}
	point operator=(point p){
		x = p.x; y = p.y; z = p.z;
		return (*this);
	}
	point(float _x, float _y, float _z):x(_x), y(_y), z(_z){}
	point(float v[4]):x(v[0]), y(v[1]), z(v[2]){}
	point(){};
};

typedef point vector;







float** createDiagonalMatrix(size_t size);

void Mul(float **m, float *v, float* rez);
void Mul(float** m1, float**m2, float** rez);


namespace Evclid{

	void rotateMatrix(float **m, vector v);
	void moveMatrix(float**m, vector offset);

	template <int num1, int num2>
	point rotate(point input, float dAngle){
		const int len=4;
		float vInput[len];
		input(vInput);
		float **m = createDiagonalMatrix(len);
		m[num1][num1] = cos(dAngle);    m[num1][num2] = -sin(dAngle);
		m[num2][num1] = -m[num1][num2]; m[num2][num2] = m[num1][num1];
		float out[4];
		Mul(m, vInput, out);
		return point(out);
	}

	template <int num1, int num2>
	void rotateMatrix(float **m, float angle){
		const int len=4;
		m[num1][num1] = cos(angle);    m[num1][num2] = -sin(angle);
		m[num2][num1] = -m[num1][num2]; m[num2][num2] = m[num1][num1];
	}

	point move(point input, vector offset);
}

template<int mSize>
float determinant(float** matrix){

	if(mSize==2) return matrix[0][0]* matrix[1][1] - matrix[1][0]* matrix[0][1];

	const int S = mSize;
	float **m = new float*[mSize];
	for(int i=0; i<mSize; ++i) m[i] = new float[2*mSize-1]; //longer array for preventing if
	for(int i=0; i<mSize; ++i){
 		for(int j=0; j<S; ++j)
			m[i][j]=matrix[i][j];
		for(int j=0; j<S-1; ++j)
			m[i][j+mSize] = matrix[i][j];
	}

	float sum=0;
	for(int i=0; i<S; ++i){
		float mul1 = 1, mul2=1;
		for(int j=0; j<S; j++){
			mul1 *= m[j][i+j];
			mul2 *= m[j][2*S-2 - (i+j)];
		}
		sum+=mul1-mul2;
	}

	for(int i=0; i<mSize; ++i) delete[] m[i];
	delete [] m;

	return sum;
}

template <int mSize>
void reverseMatrix(float** matrix, float** reverse){
	//matrixPrint(matrix, mSize, mSize);
	float det = determinant<mSize>(matrix);
	if(det==0){
		throw MATH_EXCEPTION(L"determinant = 0");
	}
	for(int i=0; i<mSize; ++i)
		for(int j=0; j<mSize; ++j) 
			reverse[i][j] = minor<mSize>(matrix, j, i)/det;
}

template<int mSize>
float minor(float** matrix, unsigned int row, unsigned int col){
	float** m = matrixINI<mSize-1>();
	for(int i=0, j=0; i<mSize; ++i){
		if(i!=row){ 
			for(int k=0, g=0; k<mSize; ++k){
				if(k!=col){
					m[j][g] = matrix[i][k];
					++g;
				}
			}
			++j;
		}
	}
	float rez = (row+col)%2==0?determinant<mSize-1>(m):-determinant<mSize-1>(m);
 	matrixFREE<mSize-1>(m);
	return rez;
}

template<int mSize>
void transponate(float** matrix, float** mTrans){
	for(int i=0; i<mSize; ++i){
		for(int j=0;j<mSize; ++j) mTrans[i][j] = matrix[j][i];
	}
}

bool matrixCompare(float** m1, size_t s1, float** m2, size_t s2);

void matrixPrint(float** m, size_t row, size_t col);

inline float hypotenuse(float x, float y, float z) {return sqrt(x*x+y*y+z*z);}
inline float hypotenuse(point p) {return sqrt(p.x*p.x+p.y*p.y+p.z*p.z);}
inline float hypotenuse(point p1, point p2) {
	return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) + (p1.z-p2.z)*(p1.z-p2.z));
}

inline float hypotenuse(float x1, float y1, float x2, float y2);

float triangleSquare(float x1, float y1, float x2, float y2, float x3, float y3);

bool isInTriangle(float xa, float ya, float xb, float yb, float xc, float yc, float x, float y);

point outOfTriangle(point outPoint, point l1, point l2);
					// returns vector for get an external relationally triangle point
/*inline */point getTriangleCenter(const point& A, const point& B, const point& C);

vector normalToSurface(const point& A, const point& B, const point& C);
int factorial(int n);
int pascalKoef(int n, int k);

point vectorMul(vector v1, vector v2);

float scalarMul(vector v1, vector v2);
#endif//GRAPHIC_LIB_H