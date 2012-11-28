/*
 * fltkmenu.cpp
 *
 *  Created on: Mar 8, 2010
 *      Author: ivan
 */

//#include "fltkmenu.h"
#include "glwindow.h"
#include "../command/vmolcommand.h"

using namespace std;



VmolView::VmolView(int x, int y, int width, int height) : Fl_Gl_Window(x, y, width, height)
{
	mode(FL_RGB | FL_ALPHA | FL_DEPTH | FL_DOUBLE);
	angle_ = 0.0f;
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
	initializedGL_ = false;

//    loadDefaultMeshes();

    viewPosition_ = (double) 0.0f;
    viewVector_ = (double) 0.0f;	viewVector_.z = 1.0f;
    viewUpVector_ = (double) 0.0f;	viewUpVector_.y = 1.0f;

    sceneRootNode_ = NULL;

    setName("DefaultView");

    for (int i=0; i<256; i++)
    	keyDown_[i] = false;

	mouseSensitivityX_ = 1.0f;
	mouseSensitivityY_ = 1.0f;
	shortcut1_ = 97;
	shortcut2_ = 98;

//    initializeGL();
}

VmolView::~VmolView()
{

}

void Perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	GLdouble xmin, xmax, ymin, ymax;
	ymax = zNear * tan(fovy * M_PI / 360.0);
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = ymax * aspect;
	glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}

void VmolView::initializeGL()
{
	if (initializedGL_ == false)
	{
		resizeGL(width_, height_);
		setupGLOptions();
		initializedGL_ = true;
	}
}

void VmolView::setupGLOptions()
{
/*
   glClearColor(.1f, .1f, .1f, 1);
   glEnable(GL_DEPTH_TEST);
*/

    glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);
//    glClearColor(1.0f, 0.0f, 0.3f, 0.5f);
//    glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
    glClearColor(1.0f, 1.0f, 1.0f, 0.5f);



    glClearDepth(1.0f);
    glEnable(GL_DEPTH_FUNC);
    glDepthFunc(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_FUNC);
    glDepthMask(GL_TRUE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
    float LightDiffuse[]=		{ 0.15f, 0.15f, 0.15f, 1.0f };
    float LightPosition[]=	    { 0.0f, 0.0f, 10.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);



//    glDisable(GL_LIGHTING);
//    glDisable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glCullFace(GL_BACK);
//    glDisable(GL_CULL_FACE);
    glEnable(GL_CULL_FACE);

//    glFrustum(-1, 1, -1, 1, 1, 100);

//    GLfloat ratio = w() / h();
//    float ratio=width_/((float) height_);
//    Perspective(30.0, 1.0*ratio, 1.0, 30.0);

}

void VmolView::resize(int x, int y, int width, int height)
{
	if (height==0)
		height=1;

	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;

	Fl_Gl_Window::resize(x, y, width, height);
	resizeGL(width, height);

//	redraw();
}

void VmolView::resizeGL(int width, int height)
{
/*
    Fl_Gl_Window::resize(x, y, w, h);
    glLoadIdentity();
    glViewport(0, 0, w, h);
//    glOrtho(-w, w, -h, h, -1, 1);
    redraw();
*/
	if (height==0)
		height=1;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void VmolView::drawAxes()
{
	glLineWidth(2.0f);
	glBegin(GL_LINES);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(50.0f, 0.0f, 0.0f);

		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 50.0f, 0.0f);

		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 50.0f);
	glEnd();
	glLineWidth(1.0f);
}

void VmolView::draw()
{
//   static bool firstTime=true;
//   if (firstTime)

//	if (initializedGL_ == false)
//		return;
	initializeGL();

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      // clear the color and depth buffer

//   glDisable(GL_LIGHTING);
//   glDisable(GL_TEXTURE_2D);

/*
   // view transformations
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-1, 1, -1, 1, 1, 100);
   glMatrixMode(GL_MODELVIEW);
*/



//   int mouseX=0, mouseY=0;
//	Fl::get_mouse(mouseX, mouseY);
//	printf ("mouseX = %d\tmouseY = %d\n", mouseX, mouseY);



   glLoadIdentity();





//   glTranslatef(0.0f, 0.0f, -20.0f);

/*
   angle_ += 0.1f;
   if (angle_ >= 360.0f)
	   angle_ = 0.0f;

   glRotatef(angle_, 1.0f, 1.0f, 0.0f);
*/

/*
   double asd=0.0f;
   asd = *((double *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_DOUBLE, (string) "increment"));
//   printf ("asd = %lf\n", asd);
   *((double *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_DOUBLE, (string) "rotacija")) = *((double *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_DOUBLE, (string) "rotacija")) + asd;
   if (*((double *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_DOUBLE, (string) "rotacija")) > 360.0f)
	   *((double *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_DOUBLE, (string) "rotacija")) -= 360.0f;
//   printf ("rotacija = %lf\n", *((double *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_DOUBLE, (string) "rotacija")));
*/

//   printf ("rotacija = %lf\n", *((double *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_DOUBLE, (string) "rotacija")));

   if (sceneRootNode_ != NULL)
	   VmolScene::getInstance()->renderScene(sceneRootNode_);


   drawAxes();




/*
// ovo tu je ono sto se uvijek vrtilo!
   //   gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
      viewPosition_.z = -20.0f;
      gluLookAt(viewPosition_.x, viewPosition_.y, viewPosition_.z, viewVector_.x, viewVector_.y, viewVector_.z, viewUpVector_.x, viewUpVector_.y, viewUpVector_.z);


//   glRotatef(45.0f, 1.0f, 1.0f, 0.0f);

   glEnable(GL_LIGHTING);
   glDisable(GL_TEXTURE_2D);

//   scene_.renderMesh(&meshSphere_);

	glColor4f(1.0f, 0.8f, 0.0f, 1.0f);
//   unsigned int boja=0xFF000000;
//   glColor4b((char) (*((char *) boja)), (char) (*(((char *) boja) + 1)), (char) (*(((char *) boja) + 2)), (char) (*(((char *) boja) + 3)));

	VmolScene::getInstance()->renderPdb(&pdbLigand_, &meshSphere_, &meshStick_, VMOL_MODE_GEOMETRY|VMOL_MODE_NORMALS|VMOL_MODE_PDB_STICKS_BALLS|VMOL_MODE_PDB_COLOR_AMINO);
*/

//   scene_.renderPdb(&pdbLigand_, &meshSphere_, &meshStick_, VMOL_MODE_GEOMETRY|VMOL_MODE_NORMALS|VMOL_MODE_WIREFRAME|VMOL_MODE_PDB_CALLOTE);

//   scene_.renderMesh(&meshStick_);

//   scene_.renderMesh(&meshCoordinateSystem_);

/*
   glDisable(GL_TEXTURE_2D);
   glDisable(GL_BLEND);

	glPushMatrix();
		glLoadIdentity();
//		glTranslatef(60.0f, -50.0f, -150.0f);
		glTranslatef(0.9f, -0.8f, -2.2f);
//		glTranslatef(0.2f, 0.0f, -1.0f);
		glRotatef(-2.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(-18.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(-22.0f, 0.0f, 1.0f, 0.0f);

//		glColor3f(0.6f, 0.6f, 0.6f);
//		glScalef(0.004f, 0.004f, 0.004f);
		glScalef(0.01f, 0.01f, 0.01f);
	    glDisable(GL_CULL_FACE);
	    glColor3f(1.0f, 0.8431f, 0.0f);
	    glEnable(GL_CULL_FACE);
	    scene_.renderMesh(&meshCoordinateSystem_);
	glPopMatrix();
*/

   // draw something
//   glPushMatrix();
//       glColor3f(0.5, 0.5, 0.5);
//       glutSolidSphere(0.5, 30, 30);
//       drawCube();
//   glPopMatrix();

//   printf ("%f\n", angle_);

//    frame = 0;
//    Fl::add_timeout(1.0f/1.0f, Timer_CB, (void*) this);       // 24fps timer

//    end();

//   swap_buffers();
}

/*
void VmolView::Timer_CB(void *userdata)
{
	VmolWindow *pb = (VmolWindow*) userdata;
	pb->redraw();
	Fl::repeat_timeout(1.0f/1.0f, Timer_CB, userdata);
}
*/

void VmolView::drawCube()
{
   glBegin(GL_QUADS);
      // front
      glColor3f(1, 0, 0);
      glVertex3f(-1, 1, 1);
      glVertex3f(-1, -1, 1);
      glVertex3f(1, -1, 1);
      glVertex3f(1, 1, 1);

      // back
      glColor3f(0, 1, 0);
      glVertex3f(-1, 1, -1);
      glVertex3f(1, 1, -1);
      glVertex3f(1, -1, -1);
      glVertex3f(-1, -1, -1);

      // top
      glColor3f(0, 0, 1);
      glVertex3f(-1, 1, -1);
      glVertex3f(-1, 1, 1);
      glVertex3f(1, 1, 1);
      glVertex3f(1, 1, -1);

      // bottom
      glColor3f(1, 1, 0);
      glVertex3f(-1, -1, -1);
      glVertex3f(1, -1, -1);
      glVertex3f(1, -1, 1);
      glVertex3f(-1, -1, 1);

      // left
      glColor3f(0, 1, 1);
      glVertex3f(-1, 1, -1);
      glVertex3f(-1, -1, -1);
      glVertex3f(-1, -1, 1);
      glVertex3f(-1, 1, 1);

      // right
      glColor3f(1, 0, 1);
      glVertex3f(1, 1, 1);
      glVertex3f(1, -1, 1);
      glVertex3f(1, -1, -1);
      glVertex3f(1, 1, -1);
   glEnd();
}

/*
int VmolView::loadDefaultMeshes()
{
	meshSphere_.loadDat((string) "data/models/sphere.dat");
	meshSphere_.autoScale(1.0f);

	meshStick_.loadDat((string) "data/models/stick.dat", true);
	meshStick_.autoScale(1.0f);

	meshCoordinateSystem_.loadDat((string) "data/models/coordinate_system.dat", true);
	meshCoordinateSystem_.autoScale(1.0f);



//	pdbLigand_.Init("data/pdb/umjetni/receptorLvisoki.pdb");
//	pdbLigand_.Init("data/pdb/amino/ala.pdb");
	pdbLigand_.Init("data/pdb/3hfl_fv.pdb");
	if (!pdbLigand_.LoadAtmtypenumbers("data/system/atmtypenumbers"))
		exit(1);
	pdbLigand_.UseUnitedRadius();
	pdbLigand_.Import(true);



	return 1;
}
*/

void VmolView::setSceneRootNode(VmolSceneNode *rootNode)
{
	sceneRootNode_ = rootNode;
}

VmolSceneNode* VmolView::getSceneRootNode()
{
	return sceneRootNode_;
}

void VmolView::setName(string nodeName)
{
	name_ = nodeName;
}

string VmolView::getName()
{
	return name_;
}

int VmolView::handle(int e)
{
	int ret=0;

    switch ( e ) {
        case FL_PUSH:
//            if (Fl::event_button() == 2)
//            {
//            	printf ("1 x = %d\ty = %d\n", Fl::event_x(), Fl::event_y());
//            }

//            	this->focus(this);

//            	this->take_focus();
            	Fl::focus(this);

            	mouseDown_ = true;
            	mouseUp_ = false;
//            	mouseDownPosition_.x = (double) Fl::event_x();
//            	mouseDownPosition_.y = (double) Fl::event_y();
            	getMouseCurrentPosition();
            	mouseDownPosition_ = mouseCurrentPosition_;
            	mouseDownButton_ = Fl::event_button();

            break;

        case FL_DRAG:
//            if (Fl::event_button() == 3)
//            {
//            	printf ("2 x = %d\ty = %d\n", Fl::event_x(), Fl::event_y());
//            }

            break;

        case FL_RELEASE:
				mouseDown_ = false;
				mouseUp_ = true;
				mouseUpPosition_.x = (double) Fl::event_x();
				mouseUpPosition_.y = (double) Fl::event_y();
				mouseUpButton_ = Fl::event_button();

        	break;

        case FL_KEYDOWN:

        	if (Fl::event_key() < 256)
        		keyDown_[Fl::event_key()] = true;
        	else
        		keyDownSpecial_.push_back(Fl::event_key());

//        	printf ("keyDown = %c, %d\n", (char) Fl::event_key(), Fl::event_key());

        	break;

        case FL_KEYUP:

        	if (Fl::event_key() < 256)
        		keyDown_[Fl::event_key()] = false;
        	else
        	{
        		for (unsigned int i=0; i<keyDownSpecial_.size(); i++)
        		{
        			if (keyDownSpecial_[i] == Fl::event_key())
        			{
        				keyDownSpecial_.erase(keyDownSpecial_.begin() + i);
        				break;
        			}
        		}
        	}

        	break;

        default:
        	;
    }

    ret = Fl_Gl_Window::handle(e);
    return(ret);
}

bool VmolView::getMouseDown()
{
	return mouseDown_;
}

bool VmolView::getMouseUp()
{
	bool ret;

	ret = mouseUp_;
	mouseUp_ = false;

	return ret;
}

int VmolView::getMouseUpButton()
{
	return mouseUpButton_;
}

int VmolView::getMouseDownButton()
{
	return mouseDownButton_;
}

Vector3 VmolView::getMouseDownPosition()
{
	return mouseDownPosition_;
}

Vector3 VmolView::getMouseUpPosition()
{
	return mouseUpPosition_;
}

Vector3 VmolView::getMouseCurrentPosition()
{
	int mouseX=0, mouseY=0;

	Fl::get_mouse(mouseX, mouseY);

	mouseCurrentPosition_.x = mouseX;
	mouseCurrentPosition_.y = mouseY;

	return mouseCurrentPosition_;
}

MouseEventBinds& VmolView::getMouseEventBinds()
{
	return mouseEventBinds_;
}

void VmolView::setMouseEventBinds(MouseEventBinds &mouseEventBinds)
{
	mouseEventBinds_ = mouseEventBinds;
}

void VmolView::setMouseDownPosition(Vector3 position)
{
	mouseDownPosition_ = position;
}

void VmolView::setMouseUpPosition(Vector3 position)
{
	mouseUpPosition_ = position;
}

void VmolView::setMouseCurrentPosition(Vector3 position)
{
	mouseCurrentPosition_ = position;
}

bool VmolView::isKeyDown(int keyIndex)
{
	if (keyIndex < 256)
		return keyDown_[keyIndex];

	for (unsigned int i=0; i<keyDownSpecial_.size(); i++)
		if (keyDownSpecial_[i] == keyIndex)
			return true;

	return false;
}

std::vector<int> VmolView::getKeyDownSpecial()
{
	return keyDownSpecial_;
}

double VmolView::getMouseSensitivityX()
{
	return mouseSensitivityX_;
}

double VmolView::getMouseSensitivityY()
{
	return mouseSensitivityY_;
}

void VmolView::setMouseSensitivityX(double sensitivityX)
{
	mouseSensitivityX_ = sensitivityX;
}

void VmolView::setMouseSensitivityY(double sensitivityY)
{
	mouseSensitivityY_ = sensitivityY;
}

int VmolView::getShortcut1()
{
	return shortcut1_;
}

void VmolView::setShortcut1(int keyCode)
{
	shortcut1_ = keyCode;
}

int VmolView::getShortcut2()
{
	return shortcut2_;
}

void VmolView::setShortcut2(int keyCode)
{
	shortcut2_ = keyCode;
}

void VmolView::setInitializedGL(bool value)
{
	initializedGL_ = value;
}

bool VmolView::getInitializedGL()
{
	return initializedGL_;
}






/*
shape_window::shape_window(int x, int y, int w, int h, const char *l):Fl_Gl_Window(x,y,w,h,l)
{
  sides = overlay_sides = 3;
}

void shape_window::draw()
{
// the valid() property may be used to avoid reinitializing your
// GL transformation for each redraw:
  if (!valid())
  {
    valid(1);
    glLoadIdentity();
    glViewport(0,0,w(),h());
  }
// draw an amazing but slow graphic:
  glClear(GL_COLOR_BUFFER_BIT);
  //  for (int j=1; j<=1000; j++) {
  static float angle=0.0f;
  angle += 1.0f;
printf ("tu sam!\n");

  glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    for (int j=0; j<sides; j++) {
      double ang = j*2*M_PI/sides;
      glColor3f(float(j)/sides,float(j)/sides,float(j)/sides);
      glVertex3f(cos(ang),sin(ang),0);
    }
    glEnd();
  // }
}

void shape_window::draw_overlay()
{
// the valid() property may be used to avoid reinitializing your
// GL transformation for each redraw:
  if (!valid()) {
    valid(1);
    glLoadIdentity();
    glViewport(0,0,w(),h());
  }
// draw an amazing graphic:
  gl_color(FL_RED);
  glBegin(GL_LINE_LOOP);
  for (int j=0; j<overlay_sides; j++) {
    double ang = j*2*M_PI/overlay_sides;
    glVertex3f(cos(ang),sin(ang),0);
  }
  glEnd();
}

void shape_window::Menu_CB(Fl_Widget*, void *data)
{
    char name[80];
    ((Fl_Menu_Button*)data)->item_pathname(name, sizeof(name)-1);
    fprintf(stderr, "Menu Callback: %s\n", name);
}

int shape_window::handle(int e)
{
    int ret = Fl_Gl_Window::handle(e);
    switch ( e ) {
        case FL_PUSH:
            if ( Fl::event_button() == 3 ) {
                char tmp[80];
                time_t t = time(NULL);
                sprintf(tmp, "Time is %s", ctime(&t));
                // Dynamically create menu, pop it up
                Fl_Menu_Button menu(Fl::event_x_root(), Fl::event_y_root(), 80, 1);
                menu.add(tmp);      // dynamic -- changes each time popup opens..
                menu.add("Edit/Copy",  0, Menu_CB, (void*)&menu);
                menu.add("Edit/Paste", 0, Menu_CB, (void*)&menu);
                menu.add("Quit",       0, Menu_CB, (void*)&menu);
                menu.popup();
            }
    }
    return(ret);
}
*/
