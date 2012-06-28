/*
 * wigner.cpp
 *
 *  Created on: Sep 14, 2009
 *      Author: nino
 */

#include "math_pdt.h"

using namespace std;


double Fakt(unsigned int x)
{
    // fakt(12) is most that we can get with unsigned int
    double ret=1.0f;
    unsigned int i=0;

/*
    if (x > 12)
    {
        printf ("Fakt_double error! x = %d\n", x);
        class ExMemoryError {};
        throw ExMemoryError();

        return 0;
    }
*/

    if (x == 0)
    {
        ret = 1;
        return ret;
    }

    // only if x GE 1 and LE 12
    for (i=1; i<=x; i++)
    {
        ret = ret * i;
    }

    return ret;
}


/** New function for calculating binomial coefficients where none of the partial
 *  results are larger than the final number. Algorithm is from "Lilavati" - a
 *  treatise on arithmetic written about 850 years ago in India. Credit goes to
 *  Mark Dominus from http://blog.plover.com/math/choose.html
 */
unsigned int binomialCoefficient(unsigned int m, unsigned int n)
{
  unsigned int result = 1;
  unsigned int d;

  if (n > m) return 0;
  for (d=1; d <= n; d++)
  {
    result *= m--;
    result /= d;
  }
  return result;
}


/** Function for calculating the element of matrix d(l) with index (m',m). */
//double Wigner_Element_Of_Matrix_D(int l, int m_crt, int m, double beta)
double elementOfMatrixD(int l, int m_crt, int m, double beta)
{
  double temp1_ui=0, temp2_ui=0; // temp3_ui=0;
  double temp1=0.0f, temp2=0.0f, temp3=0.0f, sum=0.0f, ret=0.0f;
  double temp_cos=0.0f, temp_sin=0.0f;

  int min=0, max=0, k=0;

  // assign the value of min(l-m', l+m) to the variable min
  min = l + m;
  if ((l - m_crt) < (l + m))
  {
  	min = l - m_crt;
  }
  // assign the value of max(m-m', 0) to the variable max
  max = 0;
  if ((m - m_crt) > 0)
  {
    max = m - m_crt;
  }

  // calculate the first part of expression (Dokmanic - 5-18)
  temp1 = Fakt(l+m) * Fakt(l-m);
  temp3= Fakt(l+m_crt) * Fakt(l-m_crt);

  ret = sqrt(temp3 / temp1);

	temp_cos = cos(beta/2);
	temp_sin = sin(beta/2);
  // ... and the second part of expression (Dokmanic - 5-18)
  for (k=max; k<=min; k++)
  {
    // calculate binomial coefficients
	  temp1_ui = binomialCoefficient ((unsigned int) (l + m), (unsigned int) k);
	  temp2_ui = binomialCoefficient ((unsigned int) ( l - m), (unsigned int) (l - m_crt - k));

    temp3 = temp1_ui * temp2_ui;

    // assign the values cos(beta/2) and sin(beta/2) to the variables
    temp1 = cos(beta/2);
    temp2 = sin(beta/2);

    // ... and raise them to the power of 2l+m-m'-2k and 2k+m'-m
    temp1 = pow(temp_cos, (unsigned int) (2*l + m - m_crt - 2*k));
    temp2 = pow(temp_sin, (unsigned int) (2*k + m_crt - m));

    // ... now multiply them all
    temp3 = temp1 * temp2 * temp3;

    // if (-1)^(k+m'-m) is negative value
    if (((k + m_crt - m) % 2) != 0)
    {
        temp3 *= -1;
    }

    sum += temp3;
  }

  ret *= sum;

  return ret;
}

/** Function for calculating the values for all elements of matrix d(l).
 *  Matrix needs to be initialised outside of function and of size (2l+1)x(2l+1).
*/
// void Matrix_d(int l, double beta, mpf_t *matrix_d)
//void Wigner_Matrix_D(int l, double beta, double *matrix_d)
void matrixD(int l, double beta, double *matrix_d)
{
  int i=0, j=0, m=0, m_crt=0;
	double temp=0.0f;

  // (2l+1)x(2l+1) is the size of the matrix d
  for (i=0; i<=((2*l+1)-1); i++)
  {
    for (j=0; j<=((2*l+1)-1); j++)
    {
      // calculate only if the element doesn't have an assigned value (zero)
			// Compare op1 and op2. Return a positive value if op1 > op2, zero if
      // op1 = op2, and a negative value if op1 < op2.
			if (matrix_d[i*(2*l+1) + j] == 0)
      {
        // matrix d(l) has m columns and m' rows so values are m'=i-l and m=j-l
        // indexes of m' and m are in the range from -2*l to 2*l
        m_crt = i - l;
        m = j - l;
			  temp = elementOfMatrixD(l, m_crt, m, beta);
        // we store the result in matrix d on index (i,j)
			  matrix_d[i*(2*l+1) + j] = temp;

        // because of the multiple simmetry d(m',m) = (-1)^(m'-m)d(m,m') =
			  // = (-1)^(m'-m)d(-m',-m)

        // we take the negative value if it's needed ( because of (-1)^(m'-m) )
        if (abs((m_crt - m) % 2) == 1)
        {
					temp *= (-1);
        }
        // because of the simmetry d(m',m) = (-1)^(m'-m)d(-m',-m)
        // the values for i and j are i=-m'+l and j=-m+l
				matrix_d[(l-m_crt)*(2*l+1)+l-m] = temp;

        // if m and m' are the same there's no use of changing their places
        if (m != m_crt)
        {
          // because of the simmetry d(m',m) = (-1)^(m'-m)d(m,m')
					matrix_d[j*(2*l+1) + i] = temp;
        }
      } // end if
    } // end for(j...)
  } // end for(i...)

}

/** Function for calculating the elements of the rotational matrix R. Beta is
 *  unnecessary as an argument because it's already used in calculating matrix d(l).
*/
// void ElementOfMatrix_R(int l, int m_crt, int m, double alpha, double gamma, mpf_t *matrix_d, mpf_t res)
double elementOfMatrixR(int l, int m_crt, int m, double alpha, double gamma, double *matrix_d)
{
  double temp1_d=0.0f, temp2_d=0.0f;
	double ret=0.0f;

  // indexes for matrix d are calculated with i=m'+l and j=m+l
  // default is matrix_d[ i*(2*l+1)+j ]
  if (m_crt>0 && m>0)
  {
    temp1_d = cos(m*gamma + m_crt*alpha);
    temp2_d = cos(m*gamma - m_crt*alpha );

    if (abs(m_crt % 2) == 1)
    {
      temp2_d = -temp2_d;
    }

		temp1_d = temp1_d * matrix_d[(m_crt+l)*(2*l+1) + m + l];
		temp2_d = temp2_d * matrix_d[(-m_crt+l)*(2*l+1)+m+l];

		ret = temp1_d + temp2_d;
  }
  else if (m_crt==0 && m>0)
  {
    temp1_d = sqrt(2) * cos( m * gamma );
		ret = temp1_d * matrix_d[l*(2*l+1)+m+l];
   }
   else if (m_crt<0 && m>0)
   {
     temp1_d = sin(m*gamma + m_crt*alpha);
     temp2_d = sin(m*gamma - m_crt*alpha );
     if (abs((m_crt+1) % 2 ) == 1)
     {
       temp1_d = -temp1_d;
     }

		temp1_d = temp1_d * matrix_d[(m_crt+l)*(2*l+1)+m+l];
		temp2_d = temp2_d * matrix_d[(-m_crt+l)*(2*l+1)+m+l];

		ret = temp1_d + temp2_d;
  }
  else if (m_crt>0 && m==0)
  {
    temp1_d = sqrt(2) * cos(m_crt * alpha);
		ret = temp1_d * matrix_d[(m_crt+l)*(2*l+1)+l];
  }
  else if (m_crt==0 && m==0)
  {
		ret = matrix_d[l*(2*l+1) + l];
  }
  else if (m_crt<0 && m==0)
  {
    temp1_d = sqrt(2) * sin(m_crt * alpha);
    if (abs((m_crt+1) % 2) == 1)
    {
      temp1_d = -temp1_d;
    }
		ret = temp1_d * matrix_d[(m_crt+l)*(2*l+1) + l];
  }
  else if (m_crt>0 && m<0)
  {
    temp1_d = sin(m*gamma + m_crt*alpha);
    temp2_d = sin(m*gamma - m_crt*alpha );

    if (abs(m%2) == 1)
    {
      temp1_d = -temp1_d;
    }

    if (abs((m+m_crt) % 2 ) == 1)
    {
      temp2_d = -temp2_d;
    }

		temp1_d = temp1_d * matrix_d[(m_crt+l)*(2*l+1) + m + l];
		temp2_d = temp2_d * matrix_d[(-m_crt+l)*(2*l+1) + m + l];

		ret = temp1_d + temp2_d;
  }
  else if (m_crt==0 && m<0)
  {
    temp1_d = sqrt(2) * sin(m * gamma);
    if (abs(m % 2) == 1)
    {
      temp1_d = -temp1_d;
    }

		ret = temp1_d * matrix_d[l*(2*l+1) + m + l];
  }
  else if (m_crt<0 && m<0)
  {
     temp1_d = cos(m*gamma + m_crt*alpha);
     temp2_d = cos(m*gamma - m_crt*alpha);

     if (abs((m + m_crt) % 2 ) == 1)
     {
       temp1_d = -temp1_d;
     }
     if (abs((m + 1) % 2) == 1)
     {
       temp2_d = -temp2_d;
     }

		temp1_d = temp1_d * matrix_d[(m_crt+l)*(2*l+1) + m + l];
		temp2_d = temp2_d * matrix_d[(-m_crt+l)*(2*l+1)+m+l];

		ret = temp1_d + temp2_d;
  }
  else
  {
    printf( "\nError regarding parameters m and m_crt!\n" );
  }

  return ret;
}

/** Main function for calculating rotational matrix R for given order l and angles alpha, beta and gamma.
*/
//void Wigner_Matrix_R(int l, double alpha, double beta, double gamma, double *matrix_r)
void calculateMatrixR(int l, double alpha, double beta, double gamma, double *matrix_r)
{
  int k=0, i=0, j=0, m=0, m_crt=0;
  double temp=0.0f;
  double *matrix_d=NULL;

	matrix_d = new double[(2*l+1)*(2*l+1)];

  for (k = 0; k <= (2*l+1)*(2*l+1)-1; k++)
  {
    matrix_d[k] = 0.0f;
  }

  // calculation of matrix d
  matrixD(l, beta, matrix_d);

  // (2l+1)x(2l+1) is the size of the matrix R
  for (i=0; i<=(2*l+1)-1; i++)
  {
    for (j=0; j<=(2*l+1)-1; j++)
    {
      // matrix R(l) has m columns and m' rows so values are m'=i-l and m=j-l
      // indexes of m' and m are in the range from -2*l to 2*l
      m_crt = i - l;
      m = j - l;

		  temp = elementOfMatrixR(l, m_crt, m, alpha, gamma, matrix_d);

      // we store the result in matrix R on index (i,j)
      matrix_r[i*(2*l+1) + j] = temp;
    }
  }

	if (matrix_d)
  {
	  delete[] matrix_d;
  }

}

/** Function for loading the element of rotational matrix R on index (m',m).
*/
//double Wigner_Get_Element(int l, int m_crt, int m, double *matrix_r)
double getElement(int l, int m_crt, int m, double *matrix_r)
{
    return matrix_r[(m_crt+l)*(2*l+1) + m + l];
}

/** Function for multiplying two rotational matrices of order l.
*/
//double* Wigner_Matrix_Multiply(int l, double *matrix_r1, double *matrix_r2)
double* matrixMultiply(int l, double *matrix_r1, double *matrix_r2)
{
   int i, j, k;
   double temp=0.0f, sum=0.0f;
   double *ret;
   ret = new double[(2*l+1)*(2*l+1)];

   for(i=0; i<=(2*l+1)-1; i++)
   {
     for(j=0; j<=(2*l+1)-1; j++)
     {
        sum = 0.0f;

        for(k=0; k<=(2*l+1)-1; k++)
        {
           temp = matrix_r1[ i*(2*l+1)+k ] * matrix_r2[ k*(2*l+1)+j];
           sum += temp;
        }

        ret[i*(2*l+1)+j] = sum;
      }
   }

   return ret;
}
