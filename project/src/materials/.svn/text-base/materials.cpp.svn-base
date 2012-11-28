/*
 * materials.cpp
 *
 *  Created on: Jun 28, 2010
 *      Author: ivan
 */

#include "materials.h"



Material::Material()
{
	init();
}

Material::~Material()
{
	clear();
}

void Material::init()
{
	name_ = "";
	textureId_ = 0;
	numTextureDimensions_ = 0;
	textureData_ = NULL;
	textureDataSize_ = 0;
	width_ = 0;
	height_ = 0;
	depth_ = 0;
	quasiDepth_ = 0;
	colorDepth_ = 0;

	materialType_ = VMOL_MATERIAL_UNDEFINED;
	colorAmbient_.init();
	colorDiffuse_.init();
	colorSpecular_.init();
	colorEmissive_.init();
	scaleU_ = 0.0f;
	scaleV_ = 0.0f;
	offsetU_ = 0.0f;
	offsetV_ = 0.0f;
}

void Material::clear()
{
	if (textureData_ != NULL)
		free(textureData_);

	init();
}

void Material::loadTexture(std::string path)
{
}

int Material::getMaterialType()
{
	return materialType_;
}

Color Material::getColorAmbient()
{
	return colorAmbient_;
}

Color Material::getColorDiffuse()
{
	return colorDiffuse_;
}

Color Material::getColorSpecular()
{
	return colorSpecular_;
}

Color Material::getColorEmissive()
{
	return colorEmissive_;
}

float Material::getScaleU()
{
	return scaleU_;
}

float Material::getScaleV()
{
	return scaleV_;
}

float Material::getOffsetU()
{
	return offsetU_;
}

float Material::getOffsetV()
{
	return offsetV_;
}



void Material::setMaterialType(int materialType)
{
	materialType_ = materialType;
}

void Material::setColorAmbient(Color &colorAmbient)
{
	colorAmbient_ = colorAmbient;

}

void Material::setColorDiffuse(Color &colorDiffuse)
{
	colorDiffuse_ = colorDiffuse;
}

void Material::setColorSpecular(Color &colorSpecular)
{
	colorSpecular_ = colorSpecular;
}

void Material::setColorEmissive(Color &colorEmissive)
{
	colorEmissive_ = colorEmissive;
}

void Material::setScaleU(float scaleU)
{
	scaleU_ = scaleU;
}

void Material::setScaleV(float scaleV)
{
	scaleV_ = scaleV;
}

void Material::setOffsetU(float offsetU)
{
	offsetU_ = offsetU;
}

void Material::setOffsetV(float offsetV)
{
	offsetV_ = offsetV;
}
