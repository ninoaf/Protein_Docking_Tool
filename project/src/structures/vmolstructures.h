/*
 * vmolstructures.h
 *
 *  Created on: Mar 25, 2010
 *      Author: ivan
 */

#ifndef VMOLSTRUCTURES_H_
#define VMOLSTRUCTURES_H_

#include <math.h>



class Vector3
{
public:
    double x, y, z;

    Vector3();
    ~Vector3();

/*
    Coordinates(const SphericalCoordinates& _sphCoord);
    Coordinates(double _x, double _y, double _z);
    void setCoordinates(double _x, double _y, double _z);
    void setFromSpherical(const SphericalCoordinates& sphericalCoordinates);
*/

    void init();
/*
    Coordinates operator+ (const Vector3& op1);
    Coordinates operator- (const Vector3& op1);
    Coordinates operator* (const Vector3& op1);
    Coordinates operator/ (const Vector3& op1);
    Coordinates operator+ (const double& op1);
    Coordinates operator- (const double& op1);
    Coordinates operator* (const double& op1);
    Coordinates operator/ (const double& op1);
    inline bool operator== (const Vector3& op1);
    void operator= (const Vector3 &op1);
    bool Normalize();
*/

    void operator= (const Vector3 &op1);
    void operator= (const double &op1);
    double magnitude();
    void normalize();
    double dotProduct(const Vector3 &op1);
    Vector3 crossProduct(const Vector3 &op1);
    void calculateNormal(Vector3 &vertex1, Vector3 &vertex2, Vector3 &vertex3);
};

class EulerVector3
{
public:
	double alpha, beta, gamma;

	EulerVector3()
	{
		init();
	}

    void operator= (const EulerVector3 &op1)
    {
    	alpha = op1.alpha;	beta = op1.beta;	gamma = op1.gamma;
    }

    void init()
    {
		alpha = beta = gamma = 0.0f;
    }
};



class TextureCoord2
{
public:
	float u, v;

	TextureCoord2()
	{
		u = v = 0.0f;
	}

    void operator= (const TextureCoord2 &op1)
    {
    	u = op1.u;	v = op1.v;
    }
};

class TextureCoord3
{
public:
	float u, v, w;

	TextureCoord3()
	{
		u = v = w = 0.0f;
	}

    void operator= (const TextureCoord3 &op1)
    {
    	u = op1.u;	v = op1.v;	w = op1.w;
    }
};

class Face3
{
public:
	unsigned int index[3];

	Face3()
	{
		index[0] = index[1] = index[2] = 0;
	}

    void operator= (const Face3 &op1)
    {
    	index[0] = op1.index[0];	index[1] = op1.index[1];	index[2] = op1.index[2];
    }
};

/*
class ObjectParameters
{
public:
	std::string name;
	std::string path;
	Vector3 translation;
};
*/



template <class T>
class VmolList
{
public:
	T *elements;
	unsigned long int numElements;
	unsigned long int reservedSpace;
	unsigned int growSize;

	VmolList();
	VmolList(unsigned int size);
	~VmolList();

	void init(unsigned int size=1);
	void clear();
	bool push(T *new_element);
	bool push(T new_element);
	T pop();
	bool Delete(unsigned long int index);
	T* get(unsigned long int index);
	T* allocate(unsigned int new_size);
	bool addSpace(unsigned int size);
	void growAllocatedSize(unsigned int size);
	bool elementExists(T *search_element);
	void sort();
	unsigned int size();

	bool operator== (const VmolList<T> &op1);
	T& operator[](unsigned int n);
};

#include "vmolstructures_list.h"

#endif /* VMOLSTRUCTURES_H_ */
