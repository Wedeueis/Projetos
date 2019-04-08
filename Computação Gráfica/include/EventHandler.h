#include <gl/glui.h>
#include <iostream>

int window_width = 512;
int window_height = 512;

void reshape (int w, int h);
void mouse (int button, int state, int x, int y);
void motion (int x, int y);
void pmotion (int x, int y);
void keyboard (unsigned char key, int x, int y);
void special (int key, int x, int y);
void entry (int state);

void reshape (int w, int h)
{
	//  Stay updated with the window width and height
	window_width = w;
	window_height = h;
	
	if (h<w) glViewport( (w-h)/2 , 0, h, h);
    else glViewport(0, (h-w)/2, w, w);

	//  Print current width and height on the screen
	printf ("Window Width: %d, Window Height: %d.\n", window_width, window_height);
}

void mouse (int button, int state, int x, int y)
{
	switch (button)
	{
		//  Left Button Clicked
		case GLUT_LEFT_BUTTON:

			switch (state)
			{
				//  Pressed
				case GLUT_DOWN:
					printf ("Mouse Left Button Pressed (Down)...\n");
					break;
				//  Released
				case GLUT_UP:
					printf ("Mouse Left Button Released (Up)...\n");
					break;
			}

			break;

		//  Middle Button clicked
		case GLUT_MIDDLE_BUTTON:

			switch (state)
			{
				//  Pressed
				case GLUT_DOWN:
					printf ("Mouse Middle Button Pressed (Down)...\n");
					break;
				//  Released
				case GLUT_UP:
					printf ("Mouse Middle Button Released (Up)...\n");
					break;
			}

			break;

		//  Right Button Clicked
		case GLUT_RIGHT_BUTTON:

			switch (state)
			{
				//  Pressed
				case GLUT_DOWN:
					printf ("Mouse Right Button Pressed (Down)...\n");
					break;
				//  Released
				case GLUT_UP:
					printf ("Mouse Right Button Released (Up)...\n");
					break;
			}

			break;

	}
}

void motion (int x, int y)
{
	//  Print the mouse drag position
	printf ("Mouse Drag Position: %d, %d.\n", x, y);
}

void pmotion (int x, int y)
{
	//  Print mouse move positopn
	printf ("Mouse Move Position: %d, %d.\n", x, y);
}

void keyboard (unsigned char key, int x, int y)
{
	//  Print what key the user is hitting
	printf ("User is hitting the '%c' key.\n", key);
	printf ("ASCII code is %d.\n", key);

	switch (key)
	{
		//  User hits A key
		case 'a':

			break;

		//  User hits Shift + A key
		case 'A':

			break;

		//  User hits Enter
		case '\r':
			printf ("User is hitting the Return key.\n");
			break;

		//  User hits Space
		case ' ':
			printf ("User is hitting the Space key.\n");
			break;

		//  User hits back space
		case 8:
			printf ("User is hitting the Back Space key.\n");
			break;

		//  User hits ESC key
		case 27:
			exit (1);
			break;
	}

	glutPostRedisplay ();
}

void special (int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_F1 :
			printf ("F1 function key.\n");
			break;
		case GLUT_KEY_F2 :
			printf ("F2 function key. \n");
			break;
		case GLUT_KEY_F3 :
			printf ("F3 function key. \n");
			break;
		case GLUT_KEY_F4 :
			printf ("F4 function key. \n");
			break;
		case GLUT_KEY_F5 :
			printf ("F5 function key. \n");
			break;
		case GLUT_KEY_F6 :
			printf ("F6 function key. \n");
			break;
		case GLUT_KEY_F7 :
			printf ("F7 function key. \n");
			break;
		case GLUT_KEY_F8 :
			printf ("F8 function key. \n");
			break;
		case GLUT_KEY_F9 :
			printf ("F9 function key. \n");
			break;
		case GLUT_KEY_F10 :
			printf ("F10 function key. \n");
			break;
		case GLUT_KEY_F11 :
			printf ("F11 function key. \n");
			break;
		case GLUT_KEY_F12 :
			printf ("F12 function key. \n");
			break;
		case GLUT_KEY_LEFT :
			printf ("Left directional key. \n");
			break;
		case GLUT_KEY_UP :
			printf ("Up directional key. \n");
			break;
		case GLUT_KEY_RIGHT :
			printf ("Right directional key. \n");
			break;
		case GLUT_KEY_DOWN :
			printf ("Down directional key. \n");
			break;
		case GLUT_KEY_PAGE_UP :
			printf ("Page up directional key. \n");
			break;
		case GLUT_KEY_PAGE_DOWN :
			printf ("Page down directional key. \n");
			break;
		case GLUT_KEY_HOME :
			printf ("Home directional key. \n");
			break;
		case GLUT_KEY_END :
			printf ("End directional key. \n");
			break;
		case GLUT_KEY_INSERT :
			printf ("Inset directional key. \n");
			break;
	}

	glutPostRedisplay ();
}

void entry (int state)
{
	//  Notify that this is a GLUT Callback
	printf ("GLUT: ");

	//  Notify theat we entered the window
	if (state == GLUT_ENTERED)
		printf ("Mouse entered GLUT window...\n");
	//  Notify that we left the window
	else if (state == GLUT_LEFT)
		printf ("Mouse left GLUT window...\n");
}