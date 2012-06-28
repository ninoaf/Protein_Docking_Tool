/*
 * structures.h
 *
 *      Author: ?
 */

#include "../math/math_pdt.h"
#include <string>
//#include "../coefficients/coefficients.h"

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

class SphericalCoordinates;

class Coordinates
{
public:
    double x, y, z;

    Coordinates();
    ~Coordinates();
    Coordinates(const SphericalCoordinates& _sphCoord);
    Coordinates(double _x, double _y, double _z);
    void setCoordinates(double _x, double _y, double _z);
    void setFromSpherical(const SphericalCoordinates& sphericalCoordinates);
    void init();
    Coordinates operator+ (const Coordinates& op1);
    Coordinates operator- (const Coordinates& op1);
    Coordinates operator* (const Coordinates& op1);
    Coordinates operator/ (const Coordinates& op1);
    Coordinates operator+ (const double& op1);
    Coordinates operator- (const double& op1);
    Coordinates operator* (const double& op1);
    Coordinates operator/ (const double& op1);
    inline bool operator== (const Coordinates& op1);
    bool Normalize();
};

class SphericalCoordinates
{
public:
	double radius, elevation, azimuth;

	SphericalCoordinates();
	~SphericalCoordinates();
	SphericalCoordinates(const Coordinates& _coord);
	SphericalCoordinates(double _radius, double _elevation, double _azimuth);
	void init();
	void setFromCartesian(const Coordinates& coordinates);
};


class GridValue
{
public:
    Coordinates coord;
    double value;

    GridValue();
    ~GridValue();
    GridValue(double _x, double _y, double _z, double _value);
    void init();
};


class CoeffCoordinates
{
public:
    int n, l, m;

    CoeffCoordinates();
    CoeffCoordinates(int _n, int _l, int _m);
    ~CoeffCoordinates();
    void init();

    bool operator == (const CoeffCoordinates &a) const;
    bool operator != (const CoeffCoordinates &a) const;
};

class CoeffValue
{
public:
	CoeffCoordinates coeffCoord;
    double value;

    CoeffValue();
    ~CoeffValue();
    void init();
};

// KOEFICIJENTI TRANSLACIJSKIH MATRICA CUVAT CE SE U OBICNOM vector<double>
// KOORDINATE NISU POTREBNE (NADAMO SE)

/*
class TransCoordinates
{
public:
    int n, l, m;

    TransCoordinates();
    ~TransCoordinates();
    void init();

    TransCoordinates& operator= (const TransCoordinates& op1);
};

class TransValue
{
public:
    TransCoordinates transCoord;
    double value;

    TransValue();
    ~TransValue();
    void init();
    TransValue& operator= (const TransValue &op1);
};
*/

class Face
{
public:
	unsigned int index[3];

	Face();
	~Face();
	Face(const Face& source);
	void init();
	bool operator== (const Face &op1);
};

class Triangle
{
public:
	Coordinates coord[3];

	Triangle();
	~Triangle();
	Triangle(const Triangle& source);
	void init();
	void setTriangle(Coordinates _c1, Coordinates _c2, Coordinates _c3);
	;
};

class RotationAngle
{
public:
	double beta;
	double gamma;

	RotationAngle(double _beta, double _gamma);
	RotationAngle();
	~RotationAngle();
	void init();
};

class Sphere
{
public:
	double x, y, z;
	double r;

	Sphere();
	~Sphere();
	void init();
	void operator= (const Sphere& op1);
};

class Atom
{
public:
    double x, y, z;
    double r;
    double covalent_r;

    std::string atomSerial, atomName, altLoc, resName, chainId, resSeq, insertionCode;
    std::string xString, yString, zString, occupancy, tempFactor, segmentId, elementSymbol, charge;
    std::string originalLine;

    Atom TransformCoordinates(double *transformMatrix, char newChainDesignation);
    Atom& operator= (const Atom &op1);
};

class MSMSCoord
{
public:
	Coordinates coord;
	Coordinates vector;
	long int d;
	long int atomNumber;
	long int f;

	MSMSCoord();
	~MSMSCoord();
	void init();
	MSMSCoord& operator= (const MSMSCoord &op1);
	MSMSCoord& operator= (const double &op1);
	bool operator== (const MSMSCoord &op1);
};

class MSMSFace
{
public:
	Face face;
	unsigned int attrib1;
	unsigned int attrib2;

	MSMSFace();
	~MSMSFace();
	void init();
	MSMSFace& operator= (const MSMSFace &op1);
	MSMSFace& operator= (const unsigned long int &op1);
	bool operator== (const MSMSFace &op1);
};

/** Structure used for navigation through map, which is B-tree. */
class CoordCompare
{
public:
    bool operator() (Coordinates c1, Coordinates c2) const /** operator used for navigation in map */
    {
        if (c1.x < c2.x) return 1;
        if (c1.x > c2.x) return 0;
        if (c1.y < c2.y) return 1;
        if (c1.y > c2.y) return 0;
        if (c1.z < c2.z) return 1;
        if (c1.z > c2.z) return 0;

        return 0;
    }
};

#endif /* STRUCTURES_H_ */
