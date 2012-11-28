/*
 * vmolstructures.cpp
 *
 *  Created on: Mar 25, 2010
 *      Author: ivan
 */

#include "vmolstructures.h"



Vector3::Vector3()
{
	init();
}

Vector3::~Vector3()
{

}

void Vector3::init()
{
	x = y = z = 0.0f;
}

void Vector3::operator= (const Vector3 &op1)
{
	x = op1.x;	y = op1.y;	z = op1.z;
}

void Vector3::operator= (const double &op1)
{
	x = op1;	y = op1;	z = op1;
}

double Vector3::magnitude()
{
	return sqrt(x*x + y*y + z*z);
}

void Vector3::normalize()
{
	double vectorMagnitude=0.0f;
	vectorMagnitude = magnitude();
	x /= vectorMagnitude;
	y /= vectorMagnitude;
	z /= vectorMagnitude;
}

double Vector3::dotProduct(const Vector3 &op1)
{
	return (x*op1.x + y*op1.y + z*op1.z);
}

Vector3 Vector3::crossProduct(const Vector3 &op1)
{
	Vector3 ret;

	ret.x = y*op1.z - z*op1.y;
	ret.y = z*op1.x - x*op1.z;
	ret.z = x*op1.y - y*op1.x;

	return ret;
}

void Vector3::calculateNormal(Vector3 &vertex1, Vector3 &vertex2, Vector3 &vertex3)
{
	Vector3 edge1, edge2, crossProduct;
	double magnitude;

	edge1.x = vertex2.x - vertex1.x;
	edge1.y = vertex2.y - vertex1.y;
	edge1.z = vertex2.z - vertex1.z;

	edge2.x = vertex3.x - vertex1.x;
	edge2.y = vertex3.y - vertex1.y;
	edge2.z = vertex3.z - vertex1.z;

	crossProduct.x = edge1.y * edge2.z - edge1.z * edge2.y;
	crossProduct.y = edge1.z * edge2.x - edge1.x * edge2.z;
	crossProduct.z = edge1.x * edge2.y - edge1.y * edge2.x;

	if (crossProduct.x!=0 || crossProduct.y!=0 || crossProduct.z!=0)
	{
		magnitude = sqrtf((float) (crossProduct.x*crossProduct.x + crossProduct.y*crossProduct.y + crossProduct.z*crossProduct.z));
		crossProduct.x /= magnitude;
		crossProduct.y /= magnitude;
		crossProduct.z /= magnitude;
	}

	x = crossProduct.x;
	y = crossProduct.y;
	z = crossProduct.z;
}
