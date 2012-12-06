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
	Point deplacement;
	Point rotation;
	Point angle;
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
	Point p1 = pt( ctxt.cube_dim,	-ctxt.cube_dim,	-ctxt.cube_dim);
	Point p2 = pt( -ctxt.cube_dim,	-ctxt.cube_dim,	-ctxt.cube_dim);
	Point p3 = pt( -ctxt.cube_dim,	-ctxt.cube_dim,	ctxt.cube_dim);
	Point p4 = pt( ctxt.cube_dim,	-ctxt.cube_dim,	ctxt.cube_dim);
	Point p5 = pt( ctxt.cube_dim,	ctxt.cube_dim,	-ctxt.cube_dim);
	Point p6 = pt( -ctxt.cube_dim,	ctxt.cube_dim,	-ctxt.cube_dim);
	Point p7 = pt( -ctxt.cube_dim,	ctxt.cube_dim,	ctxt.cube_dim);
	Point p8 = pt( ctxt.cube_dim,	ctxt.cube_dim,	ctxt.cube_dim);
	drawQuad(p1,p2,p3,p4);
	drawQuad(p5,p6,p7,p8);
	drawQuad(p1,p5,p8,p4);
	drawQuad(p1,p5,p6,p2);
	drawQuad(p3,p7,p6,p2);
	drawQuad(p3,p4,p8,p7); 
	*/
	glutSolidCube(ctxt.cube_dim * 2);
}

void ctxt_rot(int x, int y, int z)
{
	ctxt.rotation.x = x;
	ctxt.rotation.y = y;
	ctxt.rotation.z = z;
	ctxt.angle.x = x;
	ctxt.angle.y = y;
	ctxt.angle.z = z;
}
void ctxt_dep(int x, int y, int z)
{
	ctxt.deplacement.x = x;
	ctxt.deplacement.y = y;
	ctxt.deplacement.z = z;
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

	glTranslatef (-4.0, -2.0, -5.0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor3f (1.0f, 0.0f, 0.0f);			// rouge
	drawLine(0,0,0,1,0,0);					// x
	glColor3f (0.0f, 1.0f, 0.0f);			// vert 
	drawLine(0,0,0,0,1,0);					// y 
	glColor3f (0.0f, 0.0f, 1.0f);			// bleu
	drawLine(0,0,0,0,0,1);					// z
	glColor3f (1.0f, 1.0f, 1.0f);
	for(i = 0 ; i < 10 ; i++)
	{
		glColor3f(0.5f,0.0,0.5f);
		drawLine(0,i,0,10,i,0);
		drawLine(i,0,0,i,10,0);
	}

	// Repere du monde
	glColor3f(0.0,0.0,1.0);
	glTranslatef(4.5 + ctxt.deplacement.x, 
			1.5 + ctxt.deplacement.y,
			2.5 + ctxt.deplacement.z);

	glRotatef(ctxt.angle.x, 1.0, 0.0, 0.0);
   	glRotatef(ctxt.angle.y, 0.0, 1.0, 0.0); 
   	glRotatef(ctxt.angle.z, 0.0, 0.0, 1.0 ); 

	glPushMatrix();

	// Torse
	glPopMatrix();
	glPushMatrix();
	glScalef(1,1,2);
	ctxt.cube_dim = 0.5;
	drawCube();

	// dessin de la tête par rapport au torse
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0, 0.2, 0.4);
	glTranslatef (0.0, 0.0, 1.25);
	ctxt.cube_dim = 0.2;
	drawCube();

	// points sur la tête
	glColor3f(0.7,0.5,0.7);
	drawPoint(0.3,0.3,0.3);
	drawPoint(-0.3,0.3,0.3);
	drawPoint(0.3,-0.3,0.3);
	drawPoint(-0.3,-0.3,0.3);

	// Autres membres
	// bras gauche
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0,0.0,0.0);
	glTranslatef (-0.8, 0.0, 0.0);
	glRotatef(10.0f, 0.0f, 1.0f, 0.0f);
	glScalef(0.3,0.3,2.0);
	ctxt.cube_dim = 0.5;
	drawCube();

	// bras droit
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0,0.0,0.0);
	glTranslatef (0.8, 0.0, 0.0);
	glRotatef(-10.0f, 0.0f, 1.0f, 0.0f);
	glScalef(0.3,0.3,2.0);
	ctxt.cube_dim = 0.5;
	drawCube();

	// jambe gauche
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0,1.0,0.0);
	glTranslatef (-0.2, 0.0, -1.5);
	glScalef(0.3,0.3,2.0);
	ctxt.cube_dim = 0.5;
	drawCube();

	// jambe droite
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0,1.0,0.0);
	glTranslatef (0.2, 0.0, -1.5);
	glScalef(0.3,0.3,2.0);
	ctxt.cube_dim = 0.5;
	drawCube();

	glPopMatrix();
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
		ctxt.deplacement.y += 0.5;
	}
	if (keycode=='s')
	{
		ctxt.deplacement.y -= 0.5;
	}
	if (keycode=='q')
	{
		ctxt.deplacement.x -= 0.5;
	}
	if (keycode=='d')
	{
		ctxt.deplacement.x += 0.5;
	}

	if (keycode=='a')
	{
		ctxt.rotation.x = 1;
		ctxt.angle.x += 10;
	}

	if (keycode=='e')
	{
		ctxt.rotation.x = 1;
		ctxt.angle.x -= 10;
	}
	
	if( keycode == 't')
	{
		ctxt.rotation.y = ((int)(ctxt.rotation.y + 1.0)) %2;
	}

	if( keycode == 'f')
	{
		ctxt.rotation.y = ((int)(ctxt.rotation.y - 1.0)) %2;
	}

	if( keycode == 'y')
	{
		ctxt.rotation.z = ((int)(ctxt.rotation.z + 1.0)) %2;
	}

	if( keycode == 'g')
	{
		ctxt.rotation.z = ((int)(ctxt.rotation.z - 1.0)) %2;
	}

	if( keycode == 'n')
	{
		ctxt_dep(0,0,0);
		ctxt_rot(0,0,0);
	}
	glutPostRedisplay();
}

void reshape(int w, int h)
{
}

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
	if(ctxt.rotation.y < 0)
	{
		ctxt.angle.y -= 10;
	}
	else if(ctxt.rotation.y > 0)
	{
		ctxt.angle.y += 10;
	}

	if(ctxt.rotation.z < 0)
	{
		ctxt.angle.z -= 10;
	}
	else if(ctxt.rotation.z > 0)
	{
		ctxt.angle.z += 10;
	}
	// animation du personnage ici
	/*
	glPopMatrix();
	glRotatef(10.0f, 0.0f, 0.0f, 1.0f);
	glPushMatrix();
	*/
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
