/*
 * complexmesh.h
 *
 *  Created on: Jun 28, 2010
 *      Author: ivan
 */

#ifndef COMPLEXMESH_H_
#define COMPLEXMESH_H_

#include <stdio.h>
#include <string>
#include <vector>
#include "mesh.h"
#include "chunks3ds.h"
#include "../materials/materials.h"



class ComplexMesh
{
public:
	ComplexMesh();
	~ComplexMesh();

	void init();
	void clear();

	int load3ds(std::string path);

private:
	std::vector<Mesh> meshList_;
	std::vector<Material> materialList_;
};

#endif /* COMPLEXMESH_H_ */
