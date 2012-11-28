/*
 * commanddefinitions.h
 *
 *  Created on: Apr 19, 2010
 *      Author: ivan
 */

#ifndef COMMANDDEFINITIONS_H_
#define COMMANDDEFINITIONS_H_

#include <string>
#include "../scene/scenenode.h"



/*
#define COMMAND_ADD_MESH			"addMesh"
#define COMMAND_ADD_PDB				"addPdb"
#define COMMAND_ADD_GRID			"addGrid"
#define COMMAND_ADD_VIEW			"addView"
#define COMMAND_ADD_NODE			"addNode"
*/

#define COMMAND_CREATE				"create"
#define COMMAND_CHANGE				"change"
#define COMMAND_REMOVE				"remove"
#define COMMAND_RUN					"run"
#define COMMAND_STATUS				"status"
#define COMMAND_MATH				"math"

#define SUBCOMMAND_MESH				"mesh"
#define	SUBCOMMAND_PDB				"pdb"
#define SUBCOMMAND_NODE				"node"
#define SUBCOMMAND_VARIABLE			"variable"
#define SUBCOMMAND_VIEW				"view"
#define SUBCOMMAND_GRID				"grid"
#define SUBCOMMAND_FRAMERATE		"fps"
#define SUBCOMMAND_MS				"ms"

#define PARAMETER_NAME				"name"
#define PARAMETER_PATH				"path"
#define PARAMETER_CENTER			"center"
#define PARAMETER_CENTER_TYPE		"centerType"
#define PARAMETER_NODE_TYPE			"nodeType"
#define PARAMETER_NODE_PARAMS		"nodeParams"
#define PARAMETER_NODE_PARENT		"nodeParent"
#define PARAMETER_TRANSLATE			"translate"
#define PARAMETER_ROTATE_X			"rotateX"
#define PARAMETER_ROTATE_Y			"rotateY"
#define PARAMETER_ROTATE_Z			"rotateZ"
#define PARAMETER_ROTATE_EULER		"rotateEuler"
#define PARAMETER_RADIUS_PATH		"radiusPath"
#define PARAMETER_RADIUS_TYPE		"radiusType"
#define PARAMETER_TYPE				"type"
#define PARAMETER_VALUE				"value"
#define	PARAMETER_AUTO_SCALE		"autoScale"
#define PARAMETER_PARENT			"parent"
//#define PARAMETER_PDB_NAME			"pdbName"				// for referencing to a PDB structure, used when defining new nodes
// #define PARAMETER_PDB_NAME			"pdbName"

#define COMMAND_VAR_ALL						1<<63
#define COMMAND_VAR_CHAR					1<<1
#define COMMAND_VAR_UNSIGNED_CHAR			1<<2
#define COMMAND_VAR_LONG_INT				1<<3
#define COMMAND_VAR_UNSIGNED_LONG			1<<4
#define COMMAND_VAR_UNSIGNED_LONG_LONG		1<<5
#define COMMAND_VAR_FLOAT					1<<6
#define COMMAND_VAR_DOUBLE					1<<7
#define COMMAND_VAR_VECTOR3					1<<8
#define COMMAND_VAR_COLOR					1<<9
#define COMMAND_VAR_EULER_VECTOR3			1<<10
#define COMMAND_VAR_MESH					1<<11
#define COMMAND_VAR_PDB						1<<12
#define COMMAND_VAR_VIEW					1<<13
#define COMMAND_VAR_NODE					1<<14
#define COMMAND_VAR_STRING					1<<15



class Parameters
{
public:
	std::string name;
	std::string path;
	bool center;
	std::string centerType;
	std::string nodeType;
	std::string nodeParams;
//	std::string nodeParent;
	Vector3 translate;
	double rotateX;
	double rotateY;
	double rotateZ;
	EulerVector3 rotateEuler;
	std::string radiusPath;
	std::string radiusType;
	std::string type;
	std::string value;
	double autoScale;
	std::string parent;

	Parameters()
	{
		initDefaults();
	}

	void initDefaults()
	{
		name = path = nodeParams = centerType = radiusPath = radiusType = "";
		center = true;
//		nodeType = VMOL_NOP;
		nodeType = "";
//		nodeParent = "";
		translate.init();
		rotateX = rotateY = rotateZ = 0.0f;
		rotateEuler.init();
		type = value = "";
		autoScale = 0.0f;
		parent = "";
	}

    void operator= (const Parameters &op1)
    {
    	name = op1.name;
    	path = op1.path;
    	center = op1.center;
    	centerType = op1.centerType;
    	nodeType = op1.nodeType;
    	nodeParams = op1.nodeParams;
//    	nodeParent = op1.nodeParent;
    	translate = op1.translate;
    	rotateX = op1.rotateX;
    	rotateY = op1.rotateY;
    	rotateZ = op1.rotateZ;
    	rotateEuler = op1.rotateEuler;
    	radiusPath = op1.radiusPath;
    	radiusType = op1.radiusType;
    	type = op1.type;
    	value = op1.value;
    	autoScale = op1.autoScale;
    	parent = op1.parent;
    }

    void debugPrint()
    {
    	printf ("name: %s\n", name.c_str());
    	printf ("path: %s\n", path.c_str());
    	printf ("center: %d\n", center);
    	printf ("centerType: %s\n", centerType.c_str());
    	printf ("nodeType: %s\n", nodeType.c_str());
    	printf ("nodeParams: %s\n", nodeParams.c_str());
//    	printf ("nodeParent: %s\n", nodeParent.c_str());
    	printf ("translate: (%lf, %lf, %lf)\n", translate.x, translate.y, translate.z);
    	printf ("rotateX: %lf\n", rotateX);
    	printf ("rotateY: %lf\n", rotateY);
    	printf ("rotateZ: %lf\n", rotateZ);
    	printf ("rotateEuler: (%lf, %lf, %lf)\n", rotateEuler.alpha, rotateEuler.beta, rotateEuler.gamma);
    	printf ("radiusPath: %s\n", radiusPath.c_str());
    	printf ("radiusType: %s\n", radiusType.c_str());
    	printf ("type: %s\n", type.c_str());
    	printf ("value: %s\n", value.c_str());
    	printf ("autoScale: %lf\n", autoScale);
    	printf ("parent: %s\n", parent.c_str());
    }
};

/*
class CommandStore
{
public:
	CommandStore();
	~CommandStore();

	void init();
	void initAllCommands();

	void addCommand(string commandName);
	void addSubcommand(string subCommandName);

};
*/

#endif /* COMMANDDEFINITIONS_H_ */
