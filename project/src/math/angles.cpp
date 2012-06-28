/*
 * angles.cpp
 *
 *  Created on: Sep 14, 2009
 *      Author: nino
 */

/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
*/

// #include "angles.h"
#include "math_pdt.h"
#include "../structures/structures.h"

using namespace std;

/** Function for calculating the coordinates of 20 icosahedron vertices.
*/
void Icosahedron_Coordinates(Coordinates* vertices)
{
    int i;
    double psi, dpsi, sintheta, costheta;

    // half of the inner angle of the pentagon
    psi = 2*PI/10;
    // inner angle of the pentagon
    dpsi = 2*PI/5;
    // sin(theta) is smaller of the two roots of quadratic equation
    sintheta = (1 - sqrt( 1 - 8*pow(sin(psi),2)*(1-2*pow(sin(psi),2)) ))/(4*pow(sin(psi),2));
    costheta = sqrt(1-pow(sintheta,2));
    psi = 0;

    // calculating coordinates of upper five vertices of icosahedron (1,2,3,4,5)
    for (i=1; i<=5; i++)
    {
        // setting the coordinates for vertice i with values for x, y and z respectively
    	vertices[i].setCoordinates(costheta*cos(psi), costheta*sin(psi), sintheta);
        psi += dpsi;
    }
    sintheta = -sintheta;
    psi = 0.5*dpsi;

    // calculating of lower five vertices of icosahedron (6,7,8,9,10)
    for (i=6; i<=10; i++)
    {
        vertices[i].setCoordinates(costheta*cos(psi), costheta*sin(psi), sintheta);
        psi += dpsi;
    }

    // setting the coordinates of remaining two vertices 1 and 12 (at the top and the bottom of icosahedron)
    vertices[0].setCoordinates(0.0, 0.0, 1.0);
    vertices[11].setCoordinates(0.0, 0.0, -1.0);
}

/** Function for calculating the middle point of an edge defined by vertices v1 and v2.
*/
void Edge_Subdivision(const Coordinates& v1, const Coordinates& v2, Coordinates& v3)
{
    double r;

    // setting the initial coordinates for the vertice as a sum of coresponding components
    v3.setCoordinates(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
    // ...and normalizing it to the sphere
    r = 1 / (sqrt(pow(v3.x, 2) + pow(v3.y, 2) + pow(v3.z, 2)));
    v3.x *= r;
    v3.y *= r;
    v3.z *= r;
}

/** Function for calculating the center of a triangle defined by vertices v1, v2 and v3.
*/
void Triangle_Center(Coordinates& v, const Coordinates& v1, const Coordinates& v2, const Coordinates& v3)
{
    double r;

    // setting the initial coordinates for the vertice as a sum of coresponding components
    v.setCoordinates(v1.x+v2.x+v3.x, v1.y+v2.y+v3.y, v1.z+v2.z+v3.z);
    // ...and normalizing it to the sphere
    r = 1 / (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
    v.x *= r;
    v.y *= r;
    v.z *= r;
}

/** Function for calculating the vertices of a tessellated icosahedron with the given order k (number of subdivisions).
*/
void Icosahedron_Subdivision(int k, Coordinates *vertices)
{
    int i, j, index=0;
    int max_number_triangles, max_number_vertices, number_triangles = 20, number_vertices = 12, division = 1;
    Coordinates x1, x2, x3, x4, x5, x6;

    // calculating number of divisions of each edge - 2^k
    for(i=0; i<k; i++)
    {
        division *= 2;
    }

    // calculating maximum number of triangles and vertices
    max_number_triangles = 20*division*division;
    max_number_vertices = 10*division*division+2;

    // initializing the arrays for storing triangles of tessellated sphere
    Triangle *triangles1, *triangles2;
    triangles1 = new Triangle [max_number_triangles];
    triangles2 = new Triangle [max_number_triangles];

    // ...and coordinates of the initial icosahedron
    Coordinates *coordinate_array;
    coordinate_array = new Coordinates [number_vertices];

    Icosahedron_Coordinates(coordinate_array);

    // initializing the 20 triangles of the initial icosahedron with calculated vertices
    int indexes[20][3] = { {0, 1, 2}, {0, 2, 3}, {0, 3, 4}, {0, 4, 5}, {0, 1, 5}, {1, 2, 6}, {2, 6, 7},
    	{2, 3, 7}, {3, 7, 8}, {3, 4, 8}, {4, 8, 9}, {4, 5, 9}, {5, 9, 10}, {1, 5, 10}, {1, 6, 10}, {6, 7, 11}, {7, 8, 11},
    		{8, 9, 11}, {9, 10, 11}, {6, 10, 11} };

    for (int i = 0; i < 20; ++i)
    {
    	triangles1[i].setTriangle(coordinate_array[indexes[i][0]],
    			coordinate_array[indexes[i][1]], coordinate_array[indexes[i][2]]);
    }

    // repeat for each order of tessellation k
    for (j=0; j<k; j++)
    {
        // first make a copy of all triangles from triangles1
        for (i=0; i<number_triangles; i++)
        {
            triangles2[i] = triangles1[i];
        }

        // reset index because it is used as a counter (and we start all over again)
        index = 0;
        // divide each triangle in four equal (more or less) triangles
        for (i=0; i<number_triangles; i++)
        {
            // three vertices that define the initial triangle
            x1 = triangles2[i].coord[0];
            x2 = triangles2[i].coord[1];
            x3 = triangles2[i].coord[2];

            // x4, x5 and x6 are middle points of each edge
            Edge_Subdivision(x1, x2, x4);
            Edge_Subdivision(x2, x3, x5);
            Edge_Subdivision(x1, x3, x6);

            // ...now use them all to define four other triangles
            triangles1[index].setTriangle(x1, x4, x6);
            index++;
            triangles1[index].setTriangle(x4, x5, x6);
            index++;
            triangles1[index].setTriangle(x4, x2, x5);
            index++;
            triangles1[index].setTriangle(x6, x5, x3);
            index++;
        }
        // the final index is the number of triangles that are calculated
        number_triangles = index;
    }

    // calculate center of each triangle and return their coordinates
    for (i=0; i<max_number_triangles; i++)
    {
        Triangle_Center( vertices[i], triangles1[i].coord[0], triangles1[i].coord[1], triangles1[i].coord[2] );
    }

    if (coordinate_array)
	    delete[] coordinate_array;
    if (triangles1)
	    delete[] triangles1;
    if (triangles2)
	    delete[] triangles2;
}

/** Function for calculating euler's beta and gamma angle from given vertex coordinates.
*/
void Euler_Angles(Coordinates &v, double &beta, double &gamma)
{
    // main formulas for calculating gamma and beta (beta doesn't depend on x coordinate)
    gamma = acos(v.x / (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2))));
    beta = acos(v.y / (sqrt( pow(v.y, 2) + pow(v.z, 2))));

    // if vertex lies in xy plane
    if (v.z == 0)
    {
        beta = 0;
        if (v.y < 0)
        {
            gamma = 2*PI - gamma;
        }
    }
    // if vertice lies in xz plane
    if (v.y == 0)
    {
        beta = 0.5*PI;
        if (v.z < 0)
        {
            gamma = 2*PI - gamma;
        }
    }
    // if vertice lies in lower part of the sphere but it's not zero
    if ( (v.z < 0) && !(v.y == 0) )
    {
        gamma = 2*PI - gamma;
        beta = PI - beta;
    }
}



/** Function for calculating rotational angles - we only need an array of vertice coordinates and their number.
*/
void Rotational_Angles(int k, RotationAngle *rotational_angles)
{
    int i=0;
    long int division=1, max_number_triangles=0;

    for(i=0; i<k; i++)
    {
        division *= 2;
    }

    max_number_triangles = 20*division*division;

    Coordinates *coordinate_array;
    coordinate_array = new Coordinates [max_number_triangles+1];

    Icosahedron_Subdivision(k, coordinate_array);

    for (i=0; i<max_number_triangles; i++)
    {
        Euler_Angles(coordinate_array[i], rotational_angles[i].beta, rotational_angles[i].gamma);
    }

    //dodao nulti kut
    rotational_angles[max_number_triangles].beta = 0.0;
    rotational_angles[max_number_triangles].gamma = 0.0; 
	
    if (coordinate_array)
	    delete [] coordinate_array;
}
