#include <stdio.h>

using namespace std;



template<class T>
VmolList<T>::VmolList()
{
	init(1);
}

template<class T>
VmolList<T>::VmolList (unsigned int size)
{
	init(size);
}

template<class T>
void VmolList<T>::init(unsigned int size)
{
	elements = NULL;
	numElements = 0;
	reservedSpace = 0;
	growSize = size;

	addSpace (size);
}

template<class T>
void VmolList<T>::growAllocatedSize ( unsigned int size )
{
	growSize = size;
}

template<class T>
VmolList<T>::~VmolList()
{
	if ( elements )
		delete[] elements;
	elements = NULL;
}

template<class T>
bool VmolList<T>::push ( T *newElement )
{
	/*
		if (coords == NULL)
		{
		num_coords = 0;
		coords = (CCoord *) calloc ((num_coords + 1), sizeof(CCoord));
	}

		if (coord == NULL)
		{
		Error_Report(pdt_log_file, "Not enough memory to store MSMS coordinates!", "ERROR");
	}

		coords[num_coords].

		num_coords += 1;
		coords = (CCoord *) calloc ((num_coords + 1), sizeof(CCoord));
	*/

	printf ("1\n");

	if (numElements >= (reservedSpace - 1))
	{
		if (addSpace(growSize) == false)
			return false;
	}
	
	elements[numElements] = *newElement;
	numElements += 1;


	printf ("2\n");

/*
	int i=0;
	T *temp_elements=NULL;

	temp_elements = Allocate ( ( numElements + 1 ) );
	if ( temp_elements == NULL )
		return false;

	for ( i=0; i<numElements; i++ )
		temp_elements[i] = elements[i];
	temp_elements[numElements] = *new_element;
	numElements += 1;

	if ( elements )
		delete[] elements;
	elements = temp_elements;
*/


	return true;

}

template<class T>
bool VmolList<T>::push ( T newElement )
{
/*
	int i=0;
	T *temp_elements=NULL;

	temp_elements = Allocate ( ( numElements + 1 ) );
	if ( temp_elements == NULL )
		return false;

	for ( i=0; i<numElements; i++ )
		temp_elements[i] = elements[i];
	temp_elements[numElements] = new_element;
	numElements += 1;

	if ( elements )
		delete[] elements;
	elements = temp_elements;

	return true;
*/

	if (numElements >= (reservedSpace - 1))
	{
		if (addSpace(growSize) == false)
			return false;
	}

//	printf ("TU SAM!!! new_element = %d\n", new_element);
//	printf ("numElements = %d\n", numElements);
//	printf ("reservedSpace = %d\n", reservedSpace);

//	printf ("elements[numElements] = %d\n", elements[numElements]);
	elements[numElements] = newElement;
	numElements += 1;
//	printf ("elements[numElements] = %d\n", elements[numElements-1]);
/*	
	int i=0;
	printf ("ispis elemenata u funkciji; ");
	for (i=0; i<numElements; i++)
		printf ("%d\t", elements[i]);
	printf ("\n");
*/

	return true;
}

template<class T>
T VmolList<T>::pop()
{
/*
	int i=0;
	T ret;
	T *temp_elements=NULL;

	ret = *Get ( ( numElements-1 ) );

	temp_elements = Allocate ( numElements );
	if ( temp_elements == NULL )
		return ret;


	for ( i=0; i< ( numElements-1 ); i++ )
		temp_elements[i] = elements[i];
	numElements -= 1;

	if ( elements )
		delete[] elements;
	elements = temp_elements;

	return ret;
*/
	T ret;
	
	if (numElements <= 0)
		return ret;

	ret = elements[numElements];
	numElements -= 1;
	
	if (numElements < (reservedSpace - growSize))
	{
		int i=0;
		T *tempElements=NULL;
		
		tempElements = allocate((reservedSpace - growSize + 1));
		if (tempElements == NULL)
			return ret;
		
		for (i=0; i<numElements; i++)
			tempElements[i] = elements[i];
		
		if (elements)
			delete[] elements;
		
		elements = tempElements;
		reservedSpace -= growSize;
	}

	return ret;
}

template<class T>
bool VmolList<T>::Delete ( unsigned long int index )
{
/*
	int i=0;
	T *temp_elements;

	if ( index>=0 && index<numElements )
	{
		temp_elements = Allocate ( numElements );
		if ( temp_elements == NULL )
			return false;

		for ( i=0; i< ( numElements-1 ); i++ )
		{
			if ( i < index )
				temp_elements[i] = elements[i];
			else
				temp_elements[i] = elements[i + 1];
		}

		if ( elements )
			delete[] elements;
		elements = temp_elements;
	
		numElements -= 1;

		return true;
	}

	return false;
*/
	int i=0;
	
	if (index>=0 && index<numElements)
	{
		for (i=index; i<(numElements-1); i++)
		{
			elements[i] = elements[i + 1];
		}
		
		numElements -= 1;
		
		return true;
	}
	
	return false;
}

template<class T>
T* VmolList<T>::get (unsigned long int index)
{
	if (index>=0 && index<numElements)
		return &(elements[index]);

	return NULL;
}



template<class T>
T* VmolList<T>::allocate (unsigned int newSize)
{
	T *ret=NULL;

	ret = new T [newSize];

	if (ret == NULL)
	{
//		string errorMessage;
//		errorMessage = "Not enough memory! Error in function VmolList::Allocate(unsigned int)";
//		Error_Report (pdt_log_file, error_message, "ERROR");
		printf ("%Not enough memory! Error in function VmolList::Allocate(unsigned int).\n");
	}

	return ret;
}

template<class T>
bool VmolList<T>::addSpace (unsigned int size)
{
	unsigned long int i=0;
	T *tempElements=NULL;
	
	tempElements = allocate (reservedSpace + size + 1);

	if (tempElements == NULL)
		return false;

	for (i=0; i<numElements; i++)
		tempElements[i] = elements[i];
	
//	for (i=numElements; i<(reservedSpace+size); i++)
//		tempElements[i] = 0;
	
	if (elements)
		delete[] elements;

	elements = tempElements;
	reservedSpace += size;

//	printf ("size = %d\n", size);
//	printf ("reservedSpace = %d\n", reservedSpace);

	return true;
}

template<class T>
void VmolList<T>::clear()
{
	if (elements)
		delete[] elements;
	elements = NULL;
	
	numElements = 0;
	reservedSpace = 0;
}

template<class T>
bool VmolList<T>::elementExists(T *search_element)
{
	unsigned long int i=0;
	
	for (i=0; i<numElements; i++)
	{
		if (elements[i] == *search_element)
			return true;
	}
	
	return false;
}

template<class T>
void VmolList<T>::sort()
{
	unsigned long int i=0, j=0;
	T tempElement;
	
	for (i=0; i<numElements; i++)
	{
		for (j=i; j<numElements; j++)
		{
//			if (elements[i] < elements[j])
			{
				tempElement = elements[j];
				elements[j] = elements[i];
				elements[i] = tempElement;
			}
		}
	}
}

template<class T>
bool VmolList<T>::operator== (const VmolList<T> &op1)
{
	unsigned long int i=0;
	
	if (op1.numElements == numElements)
	{
		for (i=0; i<op1.numElements; i++)
		{
			if (!(op1.elements[i] == elements[i]))
				return false;
		}
		
		return true;
	}
	
	return false;
}

template<class T>
unsigned int VmolList<T>::size()
{
	return numElements;
}

template<class T>
T& VmolList<T>::operator[](unsigned int n)
{
	return elements[n];
}
