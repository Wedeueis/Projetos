#define GLEW_STATIC

#include <GL/glew.h>
#include <windows.h>
#include <math.h>
#include "EventHandler.h"

using namespace std;

void init ();

void display (void);
void centerOnScreen ();
void drawObject ();

int window_x;
int window_y;
char *window_title = "Projeto Final";
GLuint main_window;
int full_screen = 0;

//  pointer to the GLUI window
GLUI * glui_window;

//  Declare live variables (related to GLUI)
int wireframe = 1;			//  Related to Wireframe Check Box
int draw = 1;				//  Related to Draw Check Box
int listbox_item_id = 12;	//  Id of the selected item in the list box
int radiogroup_item_id = 0; //  Id of the selcted radio button
float rotation_matrix[16]	//  Rotation Matrix Live Variable Array
							= { 1.0, 0.0, 0.0, 0.0, 
								0.0, 1.0, 0.0, 0.0,
								0.0, 0.0, 1.0, 0.0, 
								0.0, 0.0, 0.0, 1.0 };	
float translate_xy[2]		//  Translation XY Live Variable
							= {0, 0};			
float translate_z = 0;		//  Translation Z Live Variable
float scale = 1;			//  Spinner Scale Live Variable

// an array of RGB components
float color[] = { 1.0, 1.0, 1.0 };

//  Set up the GLUI window and its components
void setupGLUI ();

//  Idle callack function
void idle ();

//  Declare callbacks related to GLUI
void glui_callback (int arg);

//  Declare the IDs of controls generating callbacks
enum
{
	COLOR_LISTBOX = 0,
	OBJECTYPE_RADIOGROUP,
	TRANSLATION_XY,
	TRANSLATION_Z,
	ROTATION,
	SCALE_SPINNER,
	QUIT_BUTTON
};

//  The different GLUT shapes
enum GLUT_SHAPES
{
	GLUT_WIRE_CUBE = 0,
	GLUT_SOLID_CUBE,
	GLUT_WIRE_SPHERE,
	GLUT_SOLID_SPHERE,
	GLUT_WIRE_CONE,
	GLUT_SOLID_CONE,
	GLUT_WIRE_TORUS,
	GLUT_SOLID_TORUS,
	GLUT_WIRE_DODECAHEDRON,
	GLUT_SOLID_DODECAHEDRON,
	GLUT_WIRE_OCTAHEDRON,
	GLUT_SOLID_OCTAHEDRON,
	GLUT_WIRE_TETRAHEDRON,
	GLUT_SOLID_TETRAHEDRON,
	GLUT_WIRE_ICOSAHEDRON,
	GLUT_SOLID_ICOSAHEDRON,
	GLUT_WIRE_TEAPOT,
	GLUT_SOLID_TEAPOT
};

void printMatrixf (float *matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf ("%f%\t", matrix[i*4 + j]);
		}

		printf ("\n");
	}
}

void init ()
{
	glClearColor (0.0, 0.0, 0.0, 0.0);

}

void display (void)
{
	glClear (GL_COLOR_BUFFER_BIT);

	drawObject ();

	glutSwapBuffers ();
}


void drawObject ()
{
	printf ("Displaying object...\n");

	glutWireIcosahedron ();
}


void centerOnScreen ()
{
	window_x = (glutGet (GLUT_SCREEN_WIDTH) - window_width)/2;
	window_y = (glutGet (GLUT_SCREEN_HEIGHT) - window_height)/2;
}

int main (int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize (window_width, window_height);
	glutInitWindowPosition (window_x, window_y);
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow (window_title);

    if (glewInit()!= GLEW_OK) {
        cout << "Erro ao iniciar GLEW";
        return 0;
    }

	centerOnScreen ();

	if (full_screen)
		glutFullScreen ();

	init();

	// Seta os callbacks
	glutDisplayFunc (display);
	glutReshapeFunc  (reshape);
	glutMouseFunc (mouse);
	glutMotionFunc (motion);
	glutPassiveMotionFunc (pmotion);
	glutKeyboardFunc (keyboard);
	glutSpecialFunc (special);

	// inicia o loop da GLUT
	glutMainLoop();
}
