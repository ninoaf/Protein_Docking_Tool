/*
 * fltkmenu.h
 *
 *  Created on: Mar 8, 2010
 *      Author: ivan
 */

#ifndef FLTKMENU_H_
#define FLTKMENU_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>
#include <Fl/Fl_Gl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Preferences.H>
#include <FL/Fl_XPM_Image.H>
#include <FL/Fl_XBM_Image.H>
#include <FL/Fl_Tiled_Image.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/fl_draw.H>
#include <FL/gl.h>
#include <FL/x.H>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <math.h>
#include <FL/math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "../objects/mesh.h"
#include "../scene/scenenode.h"
#include "../scene/scene.h"
#include "../command/commanddefinitions.h"
//#include "../command/vmolcommand.h"



// Audio headers...
// #include <config.h>

#ifndef WIN32
#  include <unistd.h>
#  include <sys/time.h>
#endif // !WIN32

#ifdef HAVE_ALSA_ASOUNDLIB_H
#  define ALSA_PCM_NEW_HW_PARAMS_API
#  include <alsa/asoundlib.h>
#endif // HAVE_ALSA_ASOUNDLIB_H
#ifdef __APPLE__
#  include <CoreAudio/AudioHardware.h>
#endif // __APPLE__
#ifdef WIN32
#  include <mmsystem.h>
#endif // WIN32



class MouseEventBinds
{
public:
/*
	void *mouseLeftHorizontalVariable;
	void *mouseLeftVerticalVariable;
	void *mouseMiddleHorizontalVariable;
	void *mouseMiddleVerticalVariable;
	void *mouseRightHorizontalVariable;
	void *mouseRightVerticalVariable;
	void *mouseShortcutAHorizontalVariable;
	void *mouseShortcutAVerticalVariable;
	void *mouseShortcutBHorizontalVariable;
	void *mouseShortcutBVerticalVariable;

	unsigned long long int mouseLeftHorizontalVariableType;
	unsigned long long int mouseLeftVerticalVariableType;
	unsigned long long int mouseMiddleHorizontalVariableType;
	unsigned long long int mouseMiddleVerticalVariableType;
	unsigned long long int mouseRightHorizontalVariableType;
	unsigned long long int mouseRightVerticalVariableType;
	unsigned long long int mouseShortcutAHorizontalVariableType;
	unsigned long long int mouseShortcutAVerticalVariableType;
	unsigned long long int mouseShortcutBHorizontalVariableType;
	unsigned long long int mouseShortcutBVerticalVariableType;

	MouseEventBinds()
	{
		mouseLeftHorizontalVariable = mouseLeftVerticalVariable = NULL;
		mouseMiddleHorizontalVariable = mouseMiddleVerticalVariable = NULL;
		mouseRightHorizontalVariable = mouseRightVerticalVariable = NULL;
		mouseShortcutAHorizontalVariable = mouseShortcutAVerticalVariable = NULL;
		mouseShortcutBHorizontalVariable = mouseShortcutBVerticalVariable = NULL;

		mouseLeftHorizontalVariableType = mouseLeftVerticalVariableType = 0;
		mouseMiddleHorizontalVariableType = mouseMiddleVerticalVariableType = 0;
		mouseRightHorizontalVariableType = mouseRightVerticalVariableType = 0;
		mouseShortcutAHorizontalVariableType = mouseShortcutAVerticalVariableType = 0;
		mouseShortcutBHorizontalVariableType = mouseShortcutBVerticalVariableType = 0;
	}
*/
	std::vector<void *> variable;
	std::vector<unsigned long long int> variableType;

	MouseEventBinds()
	{
		variable.clear();
		variableType.clear();

		for (int i=0; i<18; i++)
		{
//			variable[i] = NULL;
//			variableType[i] = 0;
			variable.push_back((void *) 1);
			variableType.push_back(0);
		}
	}
};




class VmolView:public Fl_Gl_Window
{
public:
	VmolView(int x, int y, int width, int height);
	~VmolView();
	void initializeGL();
	void setupGLOptions();
	void draw();
	void drawCube();
	void drawAxes();
	void resize(int x, int y, int w,int h);
	void resizeGL(int width, int height);

//	int loadDefaultMeshes();

	void setSceneRootNode(VmolSceneNode *rootNode);

	VmolSceneNode* getSceneRootNode();

    // Constructor
//    void Playback(int X,int Y,int W,int H,const char*L=0) : Fl_Gl_Window(X,Y,W,H,L);
//	static void Timer_CB(void *userdata);

	void setName(std::string nodeName);
	std::string getName();

	int handle(int e);

	void setInitializedGL(bool value);
	bool getInitializedGL();

	bool getMouseDown();
	bool getMouseUp();
	int getMouseUpButton();
	int getMouseDownButton();
	Vector3 getMouseDownPosition();
	Vector3 getMouseUpPosition();
	Vector3 getMouseCurrentPosition();

	void setMouseDownPosition(Vector3 position);
	void setMouseUpPosition(Vector3 position);
	void setMouseCurrentPosition(Vector3 position);

	MouseEventBinds& getMouseEventBinds();
	void setMouseEventBinds(MouseEventBinds &mouseEventBinds);

	bool isKeyDown(int keyIndex);
	std::vector<int> getKeyDownSpecial();

	double getMouseSensitivityX();
	double getMouseSensitivityY();
	void setMouseSensitivityX(double sensitivityX);
	void setMouseSensitivityY(double sensitivityY);

	int getShortcut1();
	void setShortcut1(int keyCode);
	int getShortcut2();
	void setShortcut2(int keyCode);

private:
	double angle_;
	Mesh meshSphere_;
	Mesh meshStick_;
	Mesh meshCoordinateSystem_;
	Mesh meshEulerSphere_;
	PdbFile pdbLigand_;
	bool initializedGL_;

	Vector3 viewPosition_;
	Vector3 viewVector_;
	Vector3 viewUpVector_;

	VmolSceneNode *sceneRootNode_;

	int x_, y_, width_, height_;

	std::string name_;

	bool mouseDown_;
	bool mouseUp_;
	int mouseDownButton_;
	int mouseUpButton_;
	Vector3 mouseDownPosition_;
	Vector3 mouseUpPosition_;
	Vector3 mouseCurrentPosition_;
	double mouseSensitivityX_;
	double mouseSensitivityY_;
	int shortcut1_;
	int shortcut2_;

	MouseEventBinds mouseEventBinds_;
	bool keyDown_[256];
	std::vector<int> keyDownSpecial_;
};



/*
class shape_window : public Fl_Gl_Window
{
  void draw();
  void draw_overlay();

public:
  int sides;
  int overlay_sides;

  shape_window(int x, int y, int w, int h, const char *l=0);

  static void Menu_CB(Fl_Widget*, void *data);
  int handle(int e);
};
*/

#endif /* FLTKMENU_H_ */
