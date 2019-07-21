#include <stdlib.h>
#include<stdio.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>
// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx=0.01f,lz=-1.0f;
// XZ position of the camera
float x=9.0f, z=18.0f;
// the key states. These variables will be zero
//when no key is being presses
int left=0,right=0,behind=0;
float deltaAngle = 0.0f;
float deltaMove = 0;
int screen=1;
using namespace std;
float g=10,h=10;//h-change the height of camera i.e. eye y-axis and g change the look direction of camersa i.e. look y-axis
const float LIGHT_POS = 7.0f; //The length of each side of the cube
const float BOX_HEIGHT = LIGHT_POS; //The height of the box off of the ground
const float FLOOR_SIZE = 20.0f; //The length of each side of the floor
float obx=BOX_HEIGHT,oby=BOX_HEIGHT,obz=BOX_HEIGHT;
//Draws the cube
void frontscreen();
int flag=0;
void drawCube(float angle) {

glPushMatrix();
glColor4f(0,0.5,0.0,0.5);
glRotatef(-angle, 1.0f, 1.0f, 0.0f);

glutSolidTeapot(1.0f);
//glutSolidCube(3);
glEnd();
glPopMatrix();

}

//Draws the floor
void drawFloor() {


glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glVertex3f(0, 0,0);
glVertex3f(0, 0, FLOOR_SIZE);
glVertex3f(FLOOR_SIZE , 0, FLOOR_SIZE);
glVertex3f(FLOOR_SIZE, 0, 0);

glEnd();
}
void drawleft() {


glBegin(GL_QUADS);
glNormal3f(1 ,0, 0);
glVertex3f(0,0,0);
glVertex3f(0,FLOOR_SIZE ,0);
glVertex3f(0,FLOOR_SIZE , FLOOR_SIZE);
glVertex3f(0,0,FLOOR_SIZE );

glEnd();
}
void drawbehind() {


glBegin(GL_QUADS);
glNormal3f(0 ,0, 1);
glVertex3f(0,0,0);
glVertex3f(0,FLOOR_SIZE ,0);
glVertex3f(FLOOR_SIZE,FLOOR_SIZE ,0);
glVertex3f(FLOOR_SIZE,0,0 );

glEnd();
}

void drawhelp() {


glBegin(GL_QUADS);

glVertex2f(0,2);
glVertex2f(0,FLOOR_SIZE);
glVertex2f(FLOOR_SIZE,FLOOR_SIZE);
glVertex2f(FLOOR_SIZE,2);

glEnd();
}

float _angle = 0;

void changeSize(int w, int h) {

	glViewport(0, 0, w, h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void computeDir(float deltaAngle) {

	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}
static void printstring(void *font, char *string)
{
   int len, i;

   len = (int) strlen(string);
   for (i = 0; i < len; i++)
      glutBitmapCharacter(font, string[i]);
}

void test()
{
glEnable(GL_STENCIL_TEST); //Enable using the stencil buffer
glColorMask(0, 0, 0, 0); //Disable drawing colors to the screen
glDisable(GL_DEPTH_TEST); //Disable depth testing
glStencilFunc(GL_ALWAYS, 1, 1); //Make the stencil test always pass
//Make pixels in the stencil buffer be set to 1 when the stencil test passes
glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//Set all of the pixels covered by the floor to be 1 in the stencil buffer
glPushMatrix();
drawFloor();
glPopMatrix();
if(left==1){
glPushMatrix();
drawleft();
glPopMatrix();
}
if(behind==1){
glPushMatrix();
drawbehind();
glPopMatrix();
}
glColorMask(1, 1, 1, 1); //Enable drawing colors to the screen
glEnable(GL_DEPTH_TEST); //Enable depth testing
//Make the stencil test pass only when the pixel is 1 in the stencil buffer
glStencilFunc(GL_EQUAL, 1, 1);
glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Make the stencil buffer not change

//Draw the teaport, reflected vertically, at all pixels where the stencil
//buffer is 1
//so that's the reason when go outside the floor u can't see the reflection
glPushMatrix();
glScalef(1, -1, 1);
glTranslatef(obx,oby, obz);
drawCube(_angle);
glPopMatrix();

if(left==1){
glPushMatrix();
glScalef(-1, 1, 1);
glTranslatef(obx,oby, obz);
drawCube(_angle);
glPopMatrix();

glEnable(GL_BLEND);

if(left==1 && behind==1){

glPushMatrix();
glScalef(-1,-1,-1);
glTranslatef(obx,oby, obz);
drawCube(_angle);
glPopMatrix();



glPushMatrix();
glColor4f(1, 1, 1, 0.2f);
glScalef(-1,-1,1);
drawbehind();
glPopMatrix();

}

glPushMatrix();
glScalef(-1,-1,1);
glTranslatef(obx,oby, obz);
drawCube(_angle);
glPopMatrix();

glPushMatrix();
glColor4f(1, 1, 1, 0.2f);
glScalef(-1,1,1);
drawFloor();
glPopMatrix();

glPushMatrix();
glColor4f(1, 1,1, 0.2f);
glScalef(1,-1,1);
drawleft();
glPopMatrix();

glDisable(GL_BLEND);
}

if(behind==1){
glPushMatrix();
glScalef(1, 1,-1);
glTranslatef(obx,oby, obz);
drawCube(_angle);
glPopMatrix();


glEnable(GL_BLEND);

if(left==1 && behind==1){

glPushMatrix();
glScalef(-1,-1,-1);
glTranslatef(obx,oby, obz);
drawCube(_angle);
glPopMatrix();

glPushMatrix();
glColor4f(1, 1, 1, 0.2f);
glScalef(1,-1,-1);
drawleft();
glPopMatrix();

}

glPushMatrix();
glScalef(1,-1,-1);
glTranslatef(obx,oby, obz);
drawCube(_angle);
glPopMatrix();

glPushMatrix();
glColor4f(1, 1, 1, 0.2f);
glScalef(1,1,-1);
drawFloor();
glPopMatrix();

glPushMatrix();
glColor4f(1, 1, 1, 0.2f);
glScalef(1,-1,1);
drawbehind();
glPopMatrix();

glDisable(GL_BLEND);
}

if(left==1 && behind==1){
glEnable(GL_BLEND);



glPushMatrix();
glScalef(-1,1,-1);
glTranslatef(obx,oby, obz);
drawCube(_angle);
glPopMatrix();

glPushMatrix();
glColor4f(1, 1, 1, 0.2f);
glScalef(1,1,-1);
drawleft();
glPopMatrix();


glPushMatrix();
glColor4f(1, 1, 1, 0.2f);
glScalef(-1,1,1);
drawbehind();
glPopMatrix();


glDisable(GL_BLEND);

}

glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer

//Blend the floor onto the screen
glEnable(GL_BLEND);
glPushMatrix();
glColor4f(0, 0, 0, 0.2f);
drawFloor();
glPopMatrix();

if(left==1){
glPushMatrix();
glColor4f(0, 0,0, 0.2f);

drawleft();
glPopMatrix();
}

if(behind==1){
glPushMatrix();
glColor4f(0.0f, 0,0, 0.2f);

drawbehind();
glPopMatrix();
}
glDisable(GL_BLEND);

if(screen==2){
glEnable(GL_BLEND);
glPushMatrix();
glColor4f(0, 0,0,0.3);
glTranslatef(0,0,30);

drawhelp();
glPopMatrix();
glDisable(GL_BLEND);
glPushMatrix();
glTranslatef(0,0,30);
glColor4f(1.0, 1.0, 1.0,1);
   glRasterPos2i(9,18);
   printstring(GLUT_BITMAP_TIMES_ROMAN_24, "Help");
   glRasterPos2i(0,16);
   printstring(GLUT_BITMAP_HELVETICA_12, " ARROW KEYS-TO ROTATE THE CAMERA AND TO MOVE IT FRONT AND BACK");
   glRasterPos2i(0,15);
   printstring(GLUT_BITMAP_HELVETICA_12, " w , s - TO MOVE THE CAMERA EYE ALONG Y-AXIS(CHANGING CAMERA HEIGHT)");
   glRasterPos2i(0,14);
   printstring(GLUT_BITMAP_HELVETICA_12, " q , a - TO MOVE THE CAMERA LOOK ALONG Y-AXIS");
    glRasterPos2i(0,13);
   printstring(GLUT_BITMAP_HELVETICA_12, " i , k - TO MOVE THE OBJECT ALONG Z-AXIS");
    glRasterPos2i(0,12);
   printstring(GLUT_BITMAP_HELVETICA_12, " j , l - TO MOVE THE OBJECT ALONG X-AXIS");
     glRasterPos2i(0,11);
   printstring(GLUT_BITMAP_HELVETICA_12, " o , p - TO MOVE THE OBJECT ALONG Y-AXIS");
   glRasterPos2i(0,10);
   printstring(GLUT_BITMAP_HELVETICA_12, " c - TO INSERT/REMOVE MIRROR ALONG YZ-PLANE");
   glRasterPos2i(0,9);
   printstring(GLUT_BITMAP_HELVETICA_12, " b - TO INSERT/REMOVE MIRROR ALONG XY-PLANE");
    glPopMatrix();

   angle = 0.0f;
lx=0.01f,lz=-1.0f;
 x=9.0f, z=18.0f;
 g=10,h=10;
}
if(screen==1){
glEnable(GL_BLEND);
glPushMatrix();
glColor4f(0, 1.0,1.0,0.5);
glTranslatef(0,0,30);

drawhelp();
glPopMatrix();
glDisable(GL_BLEND);
glPushMatrix();
glTranslatef(0,0,30);
glColor3f(0,0, 1.0);
   glRasterPos2i(3,18);
   printstring(GLUT_BITMAP_TIMES_ROMAN_24, "COMPUTER GRAPHICS PROJECT");
   glRasterPos2i(6,15);
   printstring(GLUT_BITMAP_TIMES_ROMAN_24, "REFLECTION");
glRasterPos2i(11,8);
   printstring(GLUT_BITMAP_HELVETICA_18, "BY,");
   glRasterPos2i(13,7);
   printstring(GLUT_BITMAP_HELVETICA_18, "NITIN SRIRAM");
glRasterPos2i(13,6);
   printstring(GLUT_BITMAP_HELVETICA_18, "1PE16CS082");
glRasterPos2i(13,5);
   printstring(GLUT_BITMAP_HELVETICA_18, "PAVAN KUMAR A");
glRasterPos2i(13,4);
   printstring(GLUT_BITMAP_HELVETICA_18, "1PE16CS109");


    glPopMatrix();

   angle = 0.0f;
lx=0.01f,lz=-1.0f;
 x=9.0f, z=18.0f;
 g=10,h=10;
}
}

void renderScene(void) {
  if (deltaMove)
		computePos(deltaMove);
        if (deltaAngle)
		computeDir(deltaAngle);

	// Clear Color and Depth Buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

	// Set the camera
	gluLookAt(	x, h, z,
				x+lx, g,  z+lz,
				0.0f, 1.0f,  0.0f);

// Draw ground

glTranslatef(0.0f, 0.0f, -40.0f);
glRotatef(0, 1, 0, 0);

GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat lightPos[] = {-2 * LIGHT_POS , LIGHT_POS ,4 * LIGHT_POS , 1.0f};
glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

glPushMatrix();
glTranslatef(obx,oby, obz);
drawCube(_angle);
glPopMatrix();
	test();

	glutSwapBuffers();
}


void update(int value) {
_angle += 1.0f;
if (_angle > 360) {
_angle -= 360;
}

glutPostRedisplay();
glutTimerFunc(25, update, 0);
}


void initRendering() {
glClearColor(1.0,1.0,1.0,1.0);
glEnable(GL_DEPTH_TEST);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glEnable(GL_NORMALIZE);
glEnable(GL_COLOR_MATERIAL);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}


void pressKey(int key, int xx, int yy) {
if(screen!=2 && screen!=1){
	switch (key) {
		case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
		case GLUT_KEY_UP : deltaMove = 0.5f; break;
		case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
	}
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : deltaMove = 0;break;
	}
}


void handleKeypress(unsigned char key, int x, int y) {
switch (key) {

    case 'w':if(screen!=2 && screen!=1)
            h+=0.1f;
            break;
    case 's':if(screen!=2 && screen!=1)
            h-=0.1f;
            break;
    case 'q':if(screen!=2 && screen!=1)
            g+=0.1f;
            break;
    case 'a':if(screen!=2 && screen!=1)
            g-=0.1f;
            break;

    case 'i':obz-=0.1f;
                if(obz<=1.8 && behind==1)
                obz=1.8;
            break;
    case 'k':obz+=0.1f;
            break;
    case 'j':obx-=0.1f;
                if(obx<=1.8 && left==1)
                obx=1.8;
            break;
    case 'l':obx+=0.6f;
            break;
    case 'o':oby+=0.1f;
            break;
    case 'p':oby-=0.1f;
                if(oby<=1.8)
                oby=1.8;
            break;
    case 'c':left=(!left);
                if(obx<=1.8 && left==1)
                obx=1.8;
                break;
    case 'b':behind=(!behind);
                if(obz<=1.8 && behind==1)
                obz=1.8;
                break;
}
}

void menu(int id){
	glClear(GL_COLOR_BUFFER_BIT);

	switch(id){
		case 1: screen=1;
				break;
		case 2: screen=2;
				break;
        case 3: screen=3;
                break;
		case 4: exit(0);
				break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv) {
int current;
int i,j;
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(600,600);
	glutCreateWindow("tt");
initRendering();
	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutSpecialFunc(pressKey);
	// here are the new entries
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);
glutKeyboardFunc(handleKeypress);
	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	glutCreateMenu(menu);
	glutAddMenuEntry("Title Page", 1);
	glutAddMenuEntry("Help", 2);
	glutAddMenuEntry("Project", 3);
	glutAddMenuEntry("Exit",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
glutTimerFunc(25, update, 0);
	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
	}



