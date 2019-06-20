/* second.cpp
 * Programmer: Bintao Wamg
 * Purpose: To draw a good fractal with openGL. It allows you to draw fractals 
 * 			from a default parameters, or from a user defined parameter. Also
 * 			the length of the each step. 
 * 
 * Input:	Basicly you just use left click to make the dragon curve grow. When you 
 * 			right click. it jumps out a menu that allows you to clear, and replay the 
 * 			curve, drawing the curve from the original parameter, and user designed 
 * 			paremeter with default length or user designer length. User can input parameter 
 * 			by left-clicking the window, and input length by entering an integer. And user
 *			can change back to default length by entering a float at this part.
 * Output:	A growing dragon curve, could disappear or reappear, could start with different 
 *			origin and different length. If you are not inputting an int, it will bring an 
 *			error message. 
 */
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <GL/glut.h>
#include <cstring>
#include <string>
using namespace std;
int windowHeight = 1000;				// The X-size of the window
int windowWidth = 1000;					// The Y-size of the window
int blank = 0;							// A boolian number deciding whether showing the curve or not
int x_origin = 500;						// The default x-axis for the curve, could be changed
int y_origin = 500;						// The default y-axis for the curve, could be changed
int click_time = 0;						// Counting the number your mouse clicks. Could be reset
string Glbpattern = "1";				// The Original pattern, it will grow when there's more mouse click
int step = 1;							// The default length of curve segments, could be user designed
float newstep;							// user designed length or the curve
float x_designed;						// user designed x parameter
float y_designed;						// user designed y parameter
float color = 0.0;						// To manage the color while drawing curve
float Red = 0, Green = 0, Blue = 0;		// Changing color
void mymenu (int);
class frac
{
	int x1, x2, y1, y2;					// x1&y1 are the old coordinate, and x2&y2 are new ones
										// They make a line.
	int numpoints;						// number of points
	int numvertex;                 		// number of vertices
public:
	void drawCurve ();
	void setPoint (int, int);
    void setVertex (int, int);
	void strsignal (string, int, int);
	frac(){numpoints = 0; numvertex = 0;};  // constructor
};
frac mydrawing;
void display ()
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
  	glClear (GL_COLOR_BUFFER_BIT);
  	mydrawing.drawCurve();
  	glFlush ();
}
void myMouse (int button, int state, int x, int y)
{
	string pattern = Glbpattern;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		blank = 1;
		click_time++;
		int click_match2 = 1;
		if(click_time < 17){			
		cout << "Going Forward" << endl;
		mydrawing.strsignal(pattern, click_time, click_match2);
		display ();
		}
		else{
			cout << "window is full" << endl;
		}
	}
}
void frac::strsignal(string pattern, int click, int click_match){
	string pattern2 = pattern;			// making the second half of the new pattern
	int i =  pattern2.length()/2;
	if(pattern2[i] == '0')				// flipping the mid number of that half
		pattern2[i] = '1';
	else{
		pattern2[i] = '0';
	}
	pattern = pattern + '1' + pattern2;	// add them up and make the new pattern
	
	Glbpattern = pattern;
	// if(click_match < click){
	// 	click_match++;
	// 	mydrawing.strsignal(pattern, click, click_match);
	// }

}
void frac::drawCurve(void)
{
	// glClear(GL_COLOR_BUFFER_BIT);
  	x1 = x_origin;							// Doing the original x1,x2,y1,y2.
  	y1 = y_origin;
  	x2 = x1 + step;
  	y2 = y1;
  	if(blank == 1){
	  	glBegin(GL_LINES);
	  		glColor3f(Red, Green, Blue);
	  		glVertex3f(x1, y1, 0);
	  		glVertex3f(x2, y2, 0);
	  	glEnd();
	  	for(int line_count = 0; line_count < Glbpattern.length(); line_count++){
	  		if(Glbpattern[line_count] == '0'){		// all cases for turning left
				if(y1 == y2){					// when the previous one is horizontal
					if(x2 > x1){				// case for left to right
						x1 = x2;				// and change x1,x2,y1,y2 to a new one and draw a new line with it
						y2 = y2 + step;
					}
					else{						// case for right to left
						x1= x2;
						y2 = y2 - step;
					}
				}
				else{							// when hte previous one is vertical
					if(y2 > y1){				// case for down to up
						x2 = x2 - step;
						y1 = y2;
					}
					else{						// case for up to down
						x2 = x2 + step;
						y1 = y2;
					}
				}
			}
			else{								// all cases for turning right
				if(y1 == y2){					// when teh previous one is horizontal
					if(x2 > x1){				// case for left to right
						x1 = x2;
						y2 = y2 - step;
					}
					else{						// case for right to left
						x1 = x2;
						y2 = y2 + step;
					}
				}
				else{							// when the previous one is vertical
					if(y2 > y1){				// case for down to up
						x2 = x2 + step;
						y1 = y2;
					}
					else{						// case for up to down
						x2 = x2 - step;
						y1 = y2;
					}
				}
			}
			  int choice = line_count%300;		// giving different color to the fractal
			  if(choice >= 0 && choice <= 140){
			  	Red = 0.85;
			  	Green = 0.85;
			  	Blue = 0.1;
			  }
			  else if(choice > 140 && choice <= 160){
			  	Red = 1;
			  	Green = 0.1;
			  	Blue = 0.1;
			  }
			  else if(choice > 160 && choice <= 300){
			  	Red = 0.1;
			  	Green = 0.85;
			  	Blue = 0.25;
			  }
			  glBegin(GL_LINES);				// Drawing a new line
	          glColor3f(Red, Green, Blue);		
	          glVertex3f(x1, y1, 0);
	          glVertex3f(x2, y2, 0);
	        glEnd();
        }
        // point_x[i] = x1;
        // point_y[i] = y1;
  	}
}
void init ()
{
   glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D (0.0, windowWidth, 0.0, windowHeight);
}
void initmenu ()						// set up menu
{
   glutCreateMenu (mymenu);     		// register callback function
   glutAddMenuEntry ("Menu", 0);
   glutAddMenuEntry ("", 0);
   glutAddMenuEntry ("Clear", 1);
   glutAddMenuEntry ("Redisplay", 2);
   glutAddMenuEntry ("New one", 3);
   glutAddMenuEntry ("New location", 4);
   glutAddMenuEntry ("New length", 5);
   // glutAddMenuEntry ("Backward", 6);
   glutAddMenuEntry ("", 0);
   glutAddMenuEntry ("Quit", 7);
   glutAttachMenu (GLUT_RIGHT_BUTTON);
}
void mymenu (int value)					// Define actions for the menu based on values given in initmenu()
{
   switch (value) {
	  case 1: 	cout << "Clearing Window" << endl;
	  			blank = 0;
	  			display ();
			  	break;
	  case 2: 	cout << "Redisplay Window" << endl;
	  			blank = 1;
	  			display ();
			  	break;
	  case 3: 
	  			cout << "Display from default parameter" << endl;
	  			click_time = 0;
	  			Glbpattern = "1";
	  			x_origin = 500;
	  			y_origin = 500;
	  			display ();
			  	break;
	  case 4: 	cout << "Setting new parameter, please input new x value around 0 and 1000" << endl;
	  			cin >> x_designed;
	  			if(x_designed >= 0 && x_designed <= 1000){
	  				cout << "Approved, now please input new y value around 0 and 1000" << endl;
	  				x_origin = x_designed;
	  				cin >> y_designed;
	  				if(y_designed >= 0 && y_designed <= 1000){
	  					cout << "Approved" << endl;
	  					y_origin = y_designed;
	  				}
	  				else{
	  					cout << "Out of range, setting x and y value to default" << endl;
	  					x_origin = 500;
	  					y_origin = 500;
	  					click_time = 0;
	  					Glbpattern = "1";
	  				}
	  			}
	  			else{
	  				cout << "Out of range, setting x value to default" << endl;
	  				x_origin = 500;
	  				click_time = 0;
	  				Glbpattern = "1";
	  			}
	  			click_time = 0;
	  			Glbpattern = "1";
	  			display ();
			  	break;
	  case 5: 
	  			cout << "Displaying with user designed length" << endl;
	  			cout << "Enter the length: ";
	  			cin >> newstep;
	  			if(newstep == (int)newstep){
	  				cout << "change successfuly" << endl;
	  				step = (int)newstep;
	  			}
	  			else{
	  				cout << "change unsuccessfuly, changing back to default length" << endl;
	  				step = 1;
	  			}
	  			display ();
			  	break;
	  // case 6: 
			//   	cout << "Going Backward" << endl;
			//  //  	string first =  Glbpattern.length()/2;
			// 	// string second =  Glbpattern.length();
			// 	// Glbpattern.erase (first,second);
			//   	step--;
			//   	display ();
	  // 		 	break;
	  case 7: cout << "Goodbye" << endl;
			  exit (1);
   }
}
int main (int argc, char** argv)
{
   // instruction();
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   /* set up the window size, in pixels */
   glutInitWindowSize (1000, 1000); 
   /* put the window at 100, 100 on user's screen */
   glutInitWindowPosition (100, 100);
   /* make a title for window */
   glutCreateWindow ("Dragon Curve");
   /* set up some GL stuff; use class method */
   init ();
   initmenu ();
   /* call display function, which in turn will call class method */
   glutDisplayFunc(display); 
   //GlutPostRedisplay();
   /* can do the same trick with the keyboard function as above */
   //glutKeyboardFunc (keyboard);
   glutMouseFunc (myMouse);
   //glClearColor(0.0;0.0;0.0;0.0);
   /* repeat these things indefinitely */
   glutMainLoop();
   /* we're done! */
   return 0; 
}