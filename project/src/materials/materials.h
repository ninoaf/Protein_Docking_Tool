/*
 * materials.h
 *
 *  Created on: Jun 28, 2010
 *      Author: ivan
 */

#ifndef MATERIALS_H_
#define MATERIALS_H_

#include <stdio.h>
#include <string>
#include "../structures/structures.h"



#define VMOL_MATERIAL_UNDEFINED			0
#define VMOL_MATERIAL_AMBIENT			1
#define VMOL_MATERIAL_DIFFUSE			2
#define VMOL_MATERIAL_SPECULAR			3
#define VMOL_MATERIAL_EMISSIVE			4




class Material
{
public:
	Material();
	~Material();

	void init();
	void clear();
	void loadTexture(std::string path);

	int getMaterialType();
	Color getColorAmbient();
	Color getColorDiffuse();
	Color getColorSpecular();
	Color getColorEmissive();
	float getScaleU();
	float getScaleV();
	float getOffsetU();
	float getOffsetV();

	void setMaterialType(int materialType);
	void setColorAmbient(Color &colorAmbient);
	void setColorDiffuse(Color &colorDiffuse);
	void setColorSpecular(Color &colorSpecular);
	void setColorEmissive(Color &colorEmissive);
	void setScaleU(float scaleU);
	void setScaleV(float scaleV);
	void setOffsetU(float offsetU);
	void setOffsetV(float offsetV);

private:
	std::string name_;
	int textureId_;
	int numTextureDimensions_;
	char *textureData_;
	unsigned long int textureDataSize_;
	unsigned long int width_;
	unsigned long int height_;
	unsigned long int depth_;
	unsigned long int quasiDepth_;			// for the fourth texture dimension
	int colorDepth_;

	int materialType_;			// VMOL_MATERIAL_UNDEFINED, VMOL_MATERIAL_AMBIENT, VMOL_MATERIAL_DIFFUSE, VMOL_MATERIAL_SPECULAR, VMOL_MATERIAL_EMISSIVE
	Color colorAmbient_;
	Color colorDiffuse_;
	Color colorSpecular_;
	Color colorEmissive_;

	float scaleU_;
	float scaleV_;
	float offsetU_;
	float offsetV_;
};

#endif /* MATERIALS_H_ */
