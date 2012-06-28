/*
 * structures.cpp
 *
 */

#include "structures.h"

/////////////////////////////////////////////////////
// OPERATOR OVERLOAD FOR GRID COORDINATES AND VALUES
/////////////////////////////////////////////////////

Coordinates::Coordinates()
{
    init();
}

Coordinates::~Coordinates()
{
	;
}

Coordinates::Coordinates(double _x, double _y, double _z)
{
	x = _x; y = _y; z = _z;
}

Coordinates::Coordinates(const SphericalCoordinates& _sphCoord){
	setFromSpherical(_sphCoord);
}

void Coordinates::setCoordinates(double _x, double _y, double _z)
{
	x = _x; y = _y; z = _z;
}

void Coordinates::setFromSpherical(const SphericalCoordinates& sphericalCoordinates){
	x = sphericalCoordinates.radius * cos(sphericalCoordinates.azimuth) * sin(sphericalCoordinates.elevation);
	y = sphericalCoordinates.radius * sin(sphericalCoordinates.azimuth) * sin(sphericalCoordinates.elevation);
	z = sphericalCoordinates.radius * cos(sphericalCoordinates.elevation);
}

void Coordinates::init()
{
    x = y = z = 0.0;
}

Coordinates Coordinates::operator+ (const Coordinates& op1)
{
    Coordinates ret;
    ret.x = x + op1.x;  ret.y = y + op1.y;  ret.z = z + op1.z;
    return ret;
}

Coordinates Coordinates::operator- (const Coordinates& op1)
{
    Coordinates ret;
    ret.x = x - op1.x;  ret.y = y - op1.y;  ret.z = z - op1.z;
    return ret;
}

Coordinates Coordinates::operator* (const Coordinates& op1)
{
    Coordinates ret;
    ret.x = x * op1.x;  ret.y = y * op1.y;  ret.z = z * op1.z;
    return ret;
}

Coordinates Coordinates::operator/ (const Coordinates& op1)
{
    Coordinates ret;
    ret.x = x / op1.x;  ret.y = y / op1.y;  ret.z = z / op1.z;
    return ret;
}

Coordinates Coordinates::operator+ (const double& op1)
{
    Coordinates ret;
    ret.x = x + op1;    ret.y = y + op1;    ret.z = z + op1;
    return ret;
}

Coordinates Coordinates::operator- (const double& op1)
{
    Coordinates ret;
    ret.x = x - op1;    ret.y = y - op1;    ret.z = z - op1;
    return ret;
}

Coordinates Coordinates::operator* (const double& op1)
{
    Coordinates ret;
    ret.x = x * op1;    ret.y = y * op1;    ret.z = z * op1;
    return ret;
}

Coordinates Coordinates::operator/ (const double& op1)
{
    Coordinates ret;
    ret.x = x / op1;    ret.y = y / op1;    ret.z = z / op1;
    return ret;
}

bool Coordinates::Normalize()
{
	double magnitude=0.0f;

	magnitude = sqrt(x*x + y*y + z*z);

	if (magnitude == 0.0f)
		return false;

	x /= magnitude;
	y /= magnitude;
	z /= magnitude;

	return true;
}

///////////////////////////////////////////////////////////////////////////////


SphericalCoordinates::SphericalCoordinates()
{
	init();
}

SphericalCoordinates::~SphericalCoordinates()
{
	;
}

SphericalCoordinates::SphericalCoordinates(double _radius, double _elevation, double _azimuth)
{
	radius = _radius; elevation = _elevation; azimuth = _azimuth;
}

SphericalCoordinates::SphericalCoordinates(const Coordinates& _coord){
	setFromCartesian(_coord);
}

void SphericalCoordinates::init()
{
	radius = elevation = azimuth = 0.0;
}

void SphericalCoordinates::setFromCartesian(const Coordinates& coordinates)
{
	radius = sqrt(coordinates.x*coordinates.x + coordinates.y*coordinates.y + coordinates.z*coordinates.z);
	elevation = (radius > 0) ? acos(coordinates.z/radius) : 0.0;
	azimuth = atan2(coordinates.y, coordinates.x);
}

///////////////////////////////////////////////////////////////////////////////


GridValue::GridValue()
{
    init();
}

GridValue::~GridValue()
{

}

GridValue::GridValue(double _x, double _y, double _z, double _value)
{
	coord.x = _x; coord.y = _y; coord.z = _z;
	value = _value;
}

void GridValue::init()
{
    coord.init();
    value = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////
// OPERATOR OVERLOAD FOR GRID COORDINATES AND VALUES
////////////////////////////////////////////////////

CoeffCoordinates::CoeffCoordinates()
{
    init();
}

CoeffCoordinates::~CoeffCoordinates()
{

}

CoeffCoordinates::CoeffCoordinates(int _n, int _l, int _m)
{
	n = _n; l = _l, m = _m;
}

void CoeffCoordinates::init()
{
    n = l = m = 0;
}

bool CoeffCoordinates::operator == (const CoeffCoordinates &a) const
{
	return (a.l == this->l && a.n == this->n && a.m == this->m);
}

bool CoeffCoordinates::operator != (const CoeffCoordinates &a) const
{
	return !(*this == a);
}

///////////////////////////////////////////////////////////////////////////////

CoeffValue::CoeffValue()
{
    init();
}

CoeffValue::~CoeffValue()
{

}

void CoeffValue::init()
{
    coeffCoord.init();;
    value = 0.0;
}

///////////////////////////////////////////////////////////////////////////////
/*
TransValue::TransValue()
{
    init();
}

TransValue::~TransValue()
{

}

void TransValue::init()
{
    transCoord.init();;
    value = 0.0;
}

TransValue& TransValue::operator= (const TransValue& op1)
{
    transCoord = op1.transCoord;
    value = op1.value;

    return *this;
}
*/
///////////////////////////////////////////////////////////////////////////////


Face::Face()
{
	init();
}

Face::~Face()
{

}

Face::Face(const Face& source)
{
	index[0] = source.index[0];
	index[1] = source.index[1];
	index[2] = source.index[2];
}

void Face::init()
{
	index[0] = index[1] = index[2] = 0;
}

bool Face::operator== (const Face &op1)
{
	if (index[0]==op1.index[0] && index[1]==op1.index[1] && index[2]==op1.index[2])
		return true;
	return false;
}

///////////////////////////////////////////////////////////////////////////////


Triangle::Triangle()
{
	init();
}

Triangle::~Triangle()
{
}

void Triangle::init()
{
	coord[0].init();
	coord[1].init();
	coord[2].init();
}

Triangle::Triangle(const Triangle& source)
{
	coord[0] = source.coord[0];
	coord[1] = source.coord[1];
	coord[2] = source.coord[2];
}

void Triangle::setTriangle(Coordinates _c1, Coordinates _c2, Coordinates _c3){
	coord[0] = _c1;
	coord[1] = _c2;
	coord[2] = _c3;
}

///////////////////////////////////////////////////////////////////////////////

RotationAngle::RotationAngle()
{
	init();
}

RotationAngle::RotationAngle(double _beta, double _gamma)
{
	beta = _beta; gamma = _gamma;
}

RotationAngle::~RotationAngle()
{

}

void RotationAngle::init()
{
	beta = gamma = 0.0;
}

///////////////////////////////////////////////////////////////////////////////

Sphere::Sphere()
{
	init();
}

Sphere::~Sphere()
{

}

void Sphere::init()
{
	x = y = z = r = 0.0f;
}

void Sphere::operator= (const Sphere& op1)
{
	x = op1.x;
	y = op1.y;
	z = op1.z;
	r = op1.r;
}

///////////////////////////////////////////////////////////////////////////////

MSMSCoord::MSMSCoord()
{
	init();
}

MSMSCoord::~MSMSCoord()
{

}

void MSMSCoord::init()
{
	coord.init();
	vector.init();
	d = 0;		atomNumber = 0;	f = 0;
}

MSMSCoord& MSMSCoord::operator= (const MSMSCoord &op1)
{
	coord = op1.coord;
	vector = op1.vector;
	d = op1.d;	atomNumber = op1.atomNumber;	f = op1.f;
	return *this;
}

MSMSCoord& MSMSCoord::operator= (const double &op1)
{
	coord.x = op1;	coord.y = op1;	coord.z = op1;
	vector.x = op1;	vector.y = op1;	vector.z = op1;
	d = atomNumber = f = 0;
	return *this;
}

bool MSMSCoord::operator== (const MSMSCoord &op1)
{
	if (coord.x==op1.coord.x && coord.y==op1.coord.y && coord.z==op1.coord.z && vector.x==op1.vector.x && vector.y==op1.vector.y && vector.z==op1.vector.z && d==op1.d && atomNumber==op1.atomNumber && f==op1.f)
		return true;
	return false;
}

///////////////////////////////////////////////////////////////////////////////

MSMSFace::MSMSFace()
{
	init();
}

MSMSFace::~MSMSFace()
{

}

void MSMSFace::init()
{
	face.init();
	attrib1 = 0;	attrib2 = 0;
}

MSMSFace& MSMSFace::operator= (const MSMSFace &op1)
{
	face = op1.face;
	attrib1 = op1.attrib1;	attrib2 = op1.attrib2;
	return *this;
}

MSMSFace& MSMSFace::operator= (const unsigned long int &op1)
{
	face.index[0] = op1;	face.index[1] = op1;	face.index[2] = op1;
	attrib1 = op1;	attrib2 = op1;
	return *this;
}

bool MSMSFace::operator== (const MSMSFace &op1)
{
	if (face==op1.face && attrib1==op1.attrib1 && attrib2==op1.attrib2)
		return true;
	return false;
}

///////////////////////////////////////////////////////////////////////////////

Atom Atom::TransformCoordinates(double *transformMatrix, char newChainDesignation)
{
	Atom ret;
	char charX[9], charY[9], charZ[9];
	double newX=0.0f, newY=0.0f, newZ=0.0f, newH=0.0f;
	std::string newLine;

	ret = *this;

	newX = x* transformMatrix[0] + y* transformMatrix[4] + z* transformMatrix[8] + 1.0f* transformMatrix[12];
	newY = x* transformMatrix[1] + y* transformMatrix[5] + z* transformMatrix[9] + 1.0f* transformMatrix[13];
	newZ = x* transformMatrix[2] + y* transformMatrix[6] + z* transformMatrix[10] + 1.0f* transformMatrix[14];
	newH = x* transformMatrix[3] + y* transformMatrix[7] + z* transformMatrix[11] + 1.0f* transformMatrix[15];

	newX /= newH;
	newY /= newH;
	newZ /= newH;
	newH /= newH;

	ret.x = newX;
	ret.y = newY;
	ret.z = newZ;

	sprintf (charX, "%8.3f", ret.x);
	sprintf (charY, "%8.3f", ret.y);
	sprintf (charZ, "%8.3f", ret.z);

	newLine = ret.originalLine.substr(0, 30);
	newLine += charX;
	newLine += charY;
	newLine += charZ;
	newLine += ret.originalLine.substr(54, 26);

	newLine[21] = newChainDesignation;

	ret.originalLine = newLine;

	return ret;
}

Atom& Atom::operator= (const Atom &op1)
{
	x = op1.x;	y = op1.y;	z = op1.z;	r = op1.r;	covalent_r = op1.covalent_r;
	atomSerial = op1.atomSerial;	atomName = op1.atomName;	altLoc = op1.altLoc; resName = op1.resName;	chainId = op1.chainId;
	resSeq = op1.resSeq;	insertionCode = op1.insertionCode;	xString = op1.xString;	yString = op1.yString;	zString = op1.zString;
	occupancy = op1.occupancy;	tempFactor = op1.tempFactor;	segmentId = op1.segmentId;	elementSymbol = op1.elementSymbol;
	charge = op1.charge;
	originalLine = op1.originalLine;

	return *this;
}
