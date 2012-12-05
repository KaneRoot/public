#include <GL/glut.h>
#include <GL/glx.h>
#include <stdlib.h>
#include <stdio.h>

/* dimensions de la fenetre */
int width = 600;
int height = 400;

typedef struct
{
	float x, y, z;
} Point;

typedef struct
{
	float cube_dim;
} contexte_s;

Point pt(float x, float y, float z)
{
	Point p;
	p.x = x;
	p.y = y;
	p.z = z;
	return p;
}

contexte_s ctxt;
/*************************************************************************/
/* Fonctions de dessin */
/*************************************************************************/

/* rouge vert bleu entre 0 et 1 */
void chooseColor(double r, double g, double b)
{
	glColor3d(r,g,b);
}

void drawPoint(double x, double  y, double z)
{
	glBegin(GL_POINTS);
	glVertex3d(x,y,z);
	glEnd();
}

void drawLine(double x1, double  y1, double z1, double x2, double y2, double z2)
{
	glBegin(GL_LINES);
	glVertex3d(x1,y1,z1);
	glVertex3d(x2,y2,z2);
	glEnd();
}

void drawQuad(Point p1, Point p2, Point p3, Point p4)
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glVertex3f(p1.x,p1.y,p1.z);
	glVertex3f(p2.x,p2.y,p2.z);
	glVertex3f(p3.x,p3.y,p3.z);
	glVertex3f(p4.x,p4.y,p4.z);
	glEnd();
}

void drawCube()
{
	/*
	Point p1 = pt(0.5,-0.5,-0.5);
	Point p2 = pt(-0.5,-0.5,-0.5);
	Point p3 = pt(-0.5,-0.5,0.5);
	Point p4 = pt(0.5,-0.5,0.5);
	Point p5 = pt(0.5,0.5,-0.5);
	Point p6 = pt(-0.5,0.5,-0.5);
	Point p7 = pt(-0.5,0.5,0.5);
	Point p8 = pt(0.5,0.5,0.5);
	drawQuad(p4,p1,p5,p8);
	drawQuad(p5,p6,p7,p8);
	*/
	glutSolidCube(ctxt.cube_dim);
	// à ecrire
}


/*************************************************************************/
/* Fonctions callback */
/*************************************************************************/

void display()
{
	int i,j;

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 60, (float)width/height, 1, 100);

	glMatrixMode(GL_MODELVIEW);

	// Pour garantir qu'au départ M (ModelView) est l'identité
	glLoadIdentity();

	// ** Dessinez ici **

	glTranslatef (-1.0, -1.0, -3.0);
	glRotatef(-70.0f, 1.0f, 0.0f, 0.0f);
	glColor3f (1.0f, 0.0f, 0.0f);			// rouge
	drawLine(0,0,0,1,0,0);					// x
	glColor3f (0.0f, 1.0f, 0.0f);			// vert 
	drawLine(0,0,0,0,1,0);					// y 
	glColor3f (0.0f, 0.0f, 1.0f);			// bleu
	drawLine(0,0,0,0,0,1);					// z
	glColor3f (1.0f, 1.0f, 1.0f);
	//glutSolidCube ( 0.5 ); // Cube Size on screen
	for(i = 0 ; i < 10 ; i++)
	{
		glColor3f(0.5f,0.0,0.5f);
		drawLine(0,i,0,10,i,0);
		drawLine(i,0,0,i,10,0);
	}
	glColor3f(0.0,0.0,1.0);
	glTranslatef (2.0, 2.0, 1.0);
	glPushMatrix();
	glScalef(1,1,2);
	ctxt.cube_dim = 1.0;
	drawCube();

	// dessin de la tête par rapport au torse
	glPopMatrix();
	glTranslatef (0.0, 0.0, 1.25);
	ctxt.cube_dim = 0.5;
	drawCube();
	glEnd ();
	glFlush();
	// Repere du monde

	// Torse

	// Autres membres

	glutSwapBuffers();
}

void keyboard(unsigned char keycode, int x, int y)
{
	/* touche ECHAP */
	if (keycode==27) 
		exit(0);
	/* touche ECHAP */
	if (keycode=='z')
	{
		printf("Touche z enfoncée\n");
	}
	if (keycode=='s')
	{
	}
	if (keycode=='q')
	{
	}
	if (keycode=='d')
	{
	}

	if (keycode=='a')
	{
	}
	if (keycode=='e')
	{
	}

	glutPostRedisplay();
}

void reshape(int w, int h)
{}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("Clic at %d %d\n",x,y);
		glutPostRedisplay();
	}

}

void idle()
{
	// animation du personnage ici

	glutPostRedisplay();
}

/*************************************************************************/
/* Fonction principale */
/*************************************************************************/

int main(int argc, char *argv[]) 
{
	/* Initialisations globales */
	glutInit(&argc, argv);

	/* Définition des attributs de la fenetre OpenGL */
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	/* Placement de la fenetre */
	glutInitWindowSize(width, height);
	glutInitWindowPosition(50, 50);

	/* Création de la fenetre */
	glutCreateWindow("Transformations matricielles");

	/* Choix de la fonction d'affichage */
	glutDisplayFunc(display);

	/* Choix de la fonction de redimensionnement de la fenetre */
	//	glutReshapeFunc(reshape);

	/* Choix des fonctions de gestion du clavier */
	glutKeyboardFunc(keyboard);
	//glutSpecialFunc(special);

	/* Choix de la fonction de gestion de la souris */
	glutMouseFunc(mouse);

	/* Choix de la fonction "oisive" */
	glutIdleFunc(idle);

	/* Boucle principale */
	glutMainLoop();

	/* Même si glutMainLoop ne rends JAMAIS la main, il faut définir le return, sinon
	   le compilateur risque de crier */
	return 0;
}
