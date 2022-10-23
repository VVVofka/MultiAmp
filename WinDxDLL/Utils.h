#pragma once

// for dumps console
#pragma comment ( lib, "User32.lib" )
#include <Windows.h>
#include <cstdio>
#include <iostream>

#include <amp.h>
#include <amp_math.h>
using namespace Concurrency;
using namespace Concurrency::fast_math;

#define NORMAL_TO_AREA(POS, WIDTH) (float(2 * (POS) + 1) / (WIDTH) - 1.f)

void setConsole();

struct FLT2{
	float y;
	float x;
	FLT2() : y(0), x(0){}
	FLT2(float Y, float X) restrict(amp, cpu) : x(X), y(Y){}
	FLT2(int Y, int X) restrict(amp, cpu) : x(float(X)), y(float(Y)){}
	FLT2(double Y, double X) restrict(amp, cpu) : x(float(X)), y(float(Y)){}
	void set(float Y, float X) restrict(amp, cpu){ y = Y, x = X; }
	bool not0(){ return x != 0 || y != 0; }
	const FLT2& abs() const restrict(amp, cpu){ return FLT2(fabsf(y), fabsf(x)); }
	bool operator == (const FLT2& other) const {return y== other.y && x==other.x;}
	FLT2 sign() const{
		float outy = (y < 0) ? -1.f : (y > 0) ? 1.f : 0;
		float outx = (x < 0) ? -1.f : (x > 0) ? 1.f : 0;
		return FLT2(outy, outx);
	}
}; // ********************************************************************************************
struct DBL2{
	double y;
	double x;
	DBL2() : y(0), x(0){}
	DBL2(double Y, double X) restrict(amp, cpu) : x(X), y(Y){}
	DBL2(int Y, int X) restrict(amp, cpu) : x(double(X)), y(double(Y)){}
	DBL2(float Y, float X) restrict(amp, cpu) : x(double(X)), y(double(Y)){}
	void set(double Y, double X) restrict(amp, cpu){ y = Y, x = X; }
	bool not0(){ return x != 0 || y != 0; }
}; // ********************************************************************************************

struct INT2{
	int y;
	int x;
	INT2() restrict(amp, cpu) : y(0), x(0){}
	INT2(int Y, int X) restrict(amp, cpu) : y(Y), x(X){}
	INT2(concurrency::index<2> idx) restrict(amp, cpu) : y(idx[0]), x(idx[1]){}
	void operator *=(int mult){ y *= mult; x *= mult; }

	const INT2& operator * (int mult) const restrict(amp, cpu){ return INT2(y * mult, x * mult); }
	int Max()const { return __max(y, x); }
	int Square()const { return x * y; }
}; // ********************************************************************************************

struct DrQuadro{
	FLT2 items[4];
	bool not0(){ return items[0].not0() || items[1].not0() || items[2].not0() || items[3].not0(); }
	void dump(){
		for(int i = 0; i < 4; i++)
			printf("\ti:%d y:%+.1f x:%+.1f", i, items[i].y, items[i].x);
	} // ///////////////////////////////////////////////////////////////////////////////////////
}; // ********************************************************************************************

//enum class CPUtype{ GPU = 0, MT = 1, CPU = 2 };
