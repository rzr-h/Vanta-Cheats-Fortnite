#pragma once

#include "Includes.h"

class Vector {
public:
	Vector() : x(0.f), y(0.f), z(0.f)
	{

	}

	Vector(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
	{

	}

	~Vector()
	{

	}

	double x;
	double y;
	double z;

	double Dot(const Vector& vOther) const {
		const Vector& a = *this;
		return (a.x * vOther.x + a.y * vOther.y + a.z * vOther.z);
	}

	double Distance(Vector v) {
		return double(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	Vector operator-(Vector V) {
		return Vector(x - V.x, y - V.y, z - V.z);
	}

	Vector operator+(Vector V) {
		return Vector(x + V.x, y + V.y, z + V.z);
	}

	Vector operator*(double Scale) {
		return Vector(x * Scale, y * Scale, z * Scale);
	}

	Vector operator/(double Scale) {
		double RScale = 1.f / Scale;
		return Vector(x * RScale, y * RScale, z * RScale);
	}

	Vector operator+(double A) {
		return Vector(x + A, y + A, z + A);
	}

	Vector operator-(double A) {
		return Vector(x - A, y - A, z - A);
	}

	Vector operator*(Vector V) {
		return Vector(x * V.x, y * V.y, z * V.z);
	}

	Vector operator/(Vector V) {
		return Vector(x / V.x, y / V.y, z / V.z);
	}

	double operator|(Vector V) {
		return x * V.x + y * V.y + z * V.z;
	}

	double operator^(Vector V) {
		return x * V.y - y * V.x - z * V.z;
	}

	Vector operator+=(Vector v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector operator-=(Vector v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vector operator*=(Vector v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	Vector operator/=(Vector v) {
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	bool operator==(Vector src) {
		return (src.x == x) && (src.y == y) && (src.z == z);
	}

	bool operator!=(Vector src) {
		return (src.x != x) || (src.y != y) || (src.z != z);
	}

	double Size() {
		return sqrt(x * x + y * y + z * z);
	}

	double Size2D() const {
		return sqrt(x * x + y * y);
	}

	double SizeSquared() {
		return x * x + y * y + z * z;
	}

	double SizeSquared2D() {
		return x * x + y * y;
	}
};



double RadianToDegree(double radian) {
	return radian * (180 / M_PI);
}

double DegreeToRadian(double degree) {
	return degree * (M_PI / 180);
}

Vector RadianToDegree(Vector radians) {
	Vector degrees;
	degrees.x = radians.x * (180 / M_PI);
	degrees.y = radians.y * (180 / M_PI);
	degrees.z = radians.z * (180 / M_PI);
	return degrees;
}

Vector DegreeToRadian(Vector degrees) {
	Vector radians;
	radians.x = degrees.x * (M_PI / 180);
	radians.y = degrees.y * (M_PI / 180);
	radians.z = degrees.z * (M_PI / 180);
	return radians;
}

void ClampAngle(Vector& angle) {
	if (angle.x > 89.0f) angle.x = 89.f;
	if (angle.x < -89.0f) angle.x = -89.f;

	if (angle.y > 180.f) angle.y = 180.f;
	if (angle.y < -180.f) angle.y = -180.f;

	angle.z = 0.0f;
}

void Normalise(Vector& angle) {
	if (angle.x > 89.0f) angle.x -= 180.0f;
	if (angle.x < -89.0f) angle.x += 180.0f;

	while (angle.y > 180) angle.y -= 360.f;
	while (angle.y < -180) angle.y += 360.f;
}

Vector CalcAngle(Vector src, Vector dst) {
	Vector OutAngle;
	OutAngle.x = -atan2f(dst.x - src.x, dst.y - src.y) / M_PI * 180 + 180;
	OutAngle.y = asinf((dst.z - src.z) / src.Distance(dst)) * 180 / M_PI;
	OutAngle.z = 0;

	return OutAngle;
}

struct FPlane : Vector
{
	double W = 0;


	Vector ToVector3()
	{
		Vector value;
		value.x = this->x;
		value.y = this->y;
		value.z = this->y;

		return value;
	}
};

struct FMatrix
{
	FPlane XPlane;
	FPlane YPlane;
	FPlane ZPlane;
	FPlane WPlane;
};

struct FTransform
{
	FPlane  rot;
	Vector translation;
	char    pad[8];
	Vector scale;

	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		double x2 = rot.x + rot.x;
		double y2 = rot.y + rot.y;
		double z2 = rot.z + rot.z;

		double xx2 = rot.x * x2;
		double yy2 = rot.y * y2;
		double zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		double yz2 = rot.y * z2;
		double wx2 = rot.W * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		double xy2 = rot.x * y2;
		double wz2 = rot.W * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		double xz2 = rot.x * z2;
		double wy2 = rot.W * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};
static D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

	return pOut;
}
static D3DMATRIX Matrix(Vector rot, Vector origin = Vector(0, 0, 0)) {
	float radPitch = (rot.x * double(M_PI) / 180.f);
	float radYaw = (rot.y * double(M_PI) / 180.f);
	float radRoll = (rot.z * double(M_PI) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}

void AngleVectors(const Vector& angles, Vector* forward)
{
	float	sp, sy, cp, cy;

	sy = sin(DegreeToRadian(angles.y));
	cy = cos(DegreeToRadian(angles.y));

	sp = sin(DegreeToRadian(angles.x));
	cp = cos(DegreeToRadian(angles.x));

	forward->x = cp * cy;
	forward->y = cp * sy;
	forward->z = -sp;
}