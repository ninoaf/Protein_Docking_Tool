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

void Coordinates::operator= (const Coordinates &op1)
{
	x = op1.x;
	y = op1.y;
	z = op1.z;
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

double Coordinates::dotProduct(Coordinates &op1)
{
	return (x*op1.x + y*op1.y + z*op1.z);
}

Coordinates Coordinates::crossProduct(Coordinates &op1)
{
	Coordinates ret;

	ret.x = y*op1.z - z*op1.y;
	ret.y = z*op1.x - x*op1.z;
	ret.z = x*op1.y - y*op1.x;

	return ret;
}

double Coordinates::magnitude()
{
	return sqrt(x*x + y*y + z*z);
}

void Coordinates::multiplyMatrix(double *transformMatrix)
{
	double newX=0.0f, newY=0.0f, newZ=0.0f, newH=0.0f;

	newX = x* transformMatrix[0] + y* transformMatrix[4] + z* transformMatrix[8] + 1.0f* transformMatrix[12];
	newY = x* transformMatrix[1] + y* transformMatrix[5] + z* transformMatrix[9] + 1.0f* transformMatrix[13];
	newZ = x* transformMatrix[2] + y* transformMatrix[6] + z* transformMatrix[10] + 1.0f* transformMatrix[14];
	newH = x* transformMatrix[3] + y* transformMatrix[7] + z* transformMatrix[11] + 1.0f* transformMatrix[15];

	newX /= newH;
	newY /= newH;
	newZ /= newH;
	newH /= newH;

	x = newX;
	y = newY;
	z = newZ;
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
AtomPdb::AtomPdb()
{
}

AtomPdb AtomPdb::transformCoordinates(double *transformMatrix, char newChainDesignation)
{
	AtomPdb ret;
	double newX=0.0f, newY=0.0f, newZ=0.0f, newH=0.0f;
	std::string newLine;

	ret = *this;



	newX = x* transformMatrix[0] + y* transformMatrix[4] + z* transformMatrix[8] + 1.0f* transformMatrix[12];
	newY = x* transformMatrix[1] + y* transformMatrix[5] + z* transformMatrix[9] + 1.0f* transformMatrix[13];
	newZ = x* transformMatrix[2] + y* transformMatrix[6] + z* transformMatrix[10] + 1.0f* transformMatrix[14];
	newH = x* transformMatrix[3] + y* transformMatrix[7] + z* transformMatrix[11] + 1.0f* transformMatrix[15];

/*
	newX = x* transformMatrix[0] + y* transformMatrix[1] + z* transformMatrix[2] + 1.0f* transformMatrix[3];
	newY = x* transformMatrix[4] + y* transformMatrix[5] + z* transformMatrix[6] + 1.0f* transformMatrix[7];
	newZ = x* transformMatrix[8] + y* transformMatrix[9] + z* transformMatrix[10] + 1.0f* transformMatrix[11];
	newH = x* transformMatrix[12] + y* transformMatrix[13] + z* transformMatrix[14] + 1.0f* transformMatrix[15];
*/

//	printf ("H = %lf\tx = %lf\ty = %lf\tz = %lf\n", newH, x, y, z);

	newX /= newH;
	newY /= newH;
	newZ /= newH;
	newH /= newH;

	ret.x = newX;
	ret.y = newY;
	ret.z = newZ;

/*
	printf ("%d\t%d\t%d\n", strlen(charX), strlen(charY), strlen(charZ));
	printf ("|%s|\t|%s|\t|%s|\n", charX, charY, charZ);
	printf ("%lf\n", z);
	for (int i=0; i<16; i++)
	{
		printf ("%lf\t", transformMatrix[i]);
		if ((i+1)%4 == 0)
			printf ("\n");
	}

	char asd;
	scanf("%c", &asd);
*/

	newLine = ret.updateLineCoordinates();

	if (newChainDesignation != ' ')
		newLine[21] = newChainDesignation;

	ret.originalLine = newLine;

	return ret;
}

std::string AtomPdb::updateLineCoordinates()
{
	char charX[20], charY[20], charZ[20];
	std::string ret="";

	if (originalLine != "")
	{
		sprintf (charX, "%8.3f", x);
		sprintf (charY, "%8.3f", y);
		sprintf (charZ, "%8.3f", z);

		ret = originalLine.substr(0, 30);
		ret += charX;
		ret += charY;
		ret += charZ;
		ret += originalLine.substr(54, 26);
	}

	return ret;
}

AtomPdb& AtomPdb::operator= (const AtomPdb &op1)
{
	x = op1.x;	y = op1.y;	z = op1.z;	r = op1.r;	covalent_r = op1.covalent_r;
	atomSerial = op1.atomSerial;	atomName = op1.atomName;	altLoc = op1.altLoc; resName = op1.resName;	chainId = op1.chainId;
	resSeq = op1.resSeq;	insertionCode = op1.insertionCode;	xString = op1.xString;	yString = op1.yString;	zString = op1.zString;
	occupancy = op1.occupancy;	tempFactor = op1.tempFactor;	segmentId = op1.segmentId;	elementSymbol = op1.elementSymbol;
	charge = op1.charge;
	originalLine = op1.originalLine;
	mass = op1.mass;
	atomColorPointer = op1.atomColorPointer;
	aminoColorPointer = op1.aminoColorPointer;
	chainColorPointer = op1.chainColorPointer;

	return *this;
}

void AtomPdb::trim()
{
	atomSerial = trimString(atomSerial);
	atomName = trimString(atomName);
	altLoc = trimString(altLoc);
	resName = trimString(resName);
	chainId = trimString(chainId);
	occupancy = trimString(occupancy);
	tempFactor = trimString(tempFactor);
	segmentId = trimString(elementSymbol);
	elementSymbol = trimString(atomSerial);
	charge = trimString(charge);
	originalLine = trimString(originalLine);
	resSeq = trimString(resSeq);
	insertionCode = trimString(insertionCode);
	xString = trimString(xString);
	yString = trimString(yString);
	zString = trimString(zString);
}

std::string AtomPdb::trimString(std::string line)
{
	int i=0;
	int firstChar=0, lastChar=0;
	std::string ret="";

	for (i=0; i<line.size(); i++)
	{
		if (line[i]!=' ' && line[i]!='\t')
		{
			firstChar = i;
			break;
		}
	}

	for (i = (line.size()-1); i >= 0; --i)
	{
		if (line[i]!=' ' && line[i]!='\t')
		{
			lastChar = i;
			break;
		}
	}

	ret = line.substr(firstChar, (lastChar-firstChar+1));

	return ret;
}

int AtomPdb::parseLine(std::string line)
{
	if (line.size() < 80)
		return 1;

	atomSerial = line.substr(6, 5);
	atomName = line.substr(12, 4);
	altLoc = line.substr(16, 1);
	resName = line.substr(17, 3);
	chainId = line.substr(21, 1);
	resSeq = line.substr(22, 4);
	insertionCode = line.substr(26, 1);
	xString = line.substr(30, 8);
	yString = line.substr(38, 8);
	zString = line.substr(46, 8);
	occupancy = line.substr(54, 6);
	tempFactor = line.substr(60, 6);
	segmentId = line.substr(72, 4);
	elementSymbol = line.substr(76, 2);
	charge = line.substr(78, 2);


	sscanf(xString.c_str(), "%lf", &(x));
	sscanf(yString.c_str(), "%lf", &(y));
	sscanf(zString.c_str(), "%lf", &(z));

	originalLine = line;

	return 0;
}
