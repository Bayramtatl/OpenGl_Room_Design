#define GL_SILENCE_DEPRECATION
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

GLboolean redFlag = true, switchOne = false, switchTwo = false, switchLamp = false, amb1 = true, diff1 = true, spec1 = true, amb2 = true, diff2 = true, spec2 = true, amb3 = true, diff3 = true, spec3 = true;
double windowHeight = 800, windowWidth = 600;
double eyeX = 7.0, eyeY = 2.0, eyeZ = 15.0, refX = 0, refY = 0, refZ = 0; // bakýþ açýsý için kullanýlacak deðiþkenler.
double theta = 180.0, y = 1.36, z = 7.97888;

static GLfloat v_kup[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.0, 3.0, 0.0}, //4
    {0.0, 3.0, 3.0}, //5
    {3.0, 3.0, 3.0}, //6
    {3.0, 3.0, 0.0}  //7
};

static GLubyte quadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};



static void getNormal3p // Cisme ýþýðýn hangi açýyla çarptýðýný vs hesaplar
(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2 - x1;
    Uy = y2 - y1;
    Uz = z2 - z1;

    Vx = x3 - x1;
    Vy = y3 - y1;
    Vz = z3 - z1;

    Nx = Uy * Vz - Uz * Vy;
    Ny = Uz * Vx - Ux * Vz;
    Nz = Ux * Vy - Uy * Vx;

    glNormal3f(Nx, Ny, Nz);
}


void kupCiz(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX = 0, GLfloat ambY = 0, GLfloat ambZ = 0, GLfloat shine = 50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);

    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(v_kup[quadIndices[i][0]][0], v_kup[quadIndices[i][0]][1], v_kup[quadIndices[i][0]][2],
            v_kup[quadIndices[i][1]][0], v_kup[quadIndices[i][1]][1], v_kup[quadIndices[i][1]][2],
            v_kup[quadIndices[i][2]][0], v_kup[quadIndices[i][2]][1], v_kup[quadIndices[i][2]][2]);
        glVertex3fv(&v_kup[quadIndices[i][0]][0]);
        glVertex3fv(&v_kup[quadIndices[i][1]][0]);
        glVertex3fv(&v_kup[quadIndices[i][2]][0]);
        glVertex3fv(&v_kup[quadIndices[i][3]][0]);
    }
    glEnd();
}

static GLfloat v_yamuk[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.5, 3.0, 0.5}, //4
    {0.5, 3.0, 2.5}, //5
    {2.5, 3.0, 2.5}, //6
    {2.5, 3.0, 0.5}  //7
};

static GLubyte TquadIndices[6][4] =
{
    {0, 1, 2, 3}, //alt 
    {4, 5, 6, 7}, //üst
    {5, 1, 2, 6}, //ön
    {0, 4, 7, 3}, // arka 
    {2, 3, 7, 6}, //sað
    {1, 5, 4, 0}  //sol
};

void yamukCiz(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine = 50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_emission[] = { difX, difY, difZ, 0.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    if (switchLamp == true) {
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }
    else {
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }

    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(v_yamuk[TquadIndices[i][0]][0], v_yamuk[TquadIndices[i][0]][1], v_yamuk[TquadIndices[i][0]][2],
            v_yamuk[TquadIndices[i][1]][0], v_yamuk[TquadIndices[i][1]][1], v_yamuk[TquadIndices[i][1]][2],
            v_yamuk[TquadIndices[i][2]][0], v_yamuk[TquadIndices[i][2]][1], v_yamuk[TquadIndices[i][2]][2]);

        glVertex3fv(&v_yamuk[TquadIndices[i][0]][0]);
        glVertex3fv(&v_yamuk[TquadIndices[i][1]][0]);
        glVertex3fv(&v_yamuk[TquadIndices[i][2]][0]);
        glVertex3fv(&v_yamuk[TquadIndices[i][3]][0]);
    }
    glEnd();
}


//Drawing pyramid *************************
static GLfloat v_pyramid[5][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 0.0, 0.0},
    {1.0, 4.0, 1.0}
};

static GLubyte p_Indices[4][3] =
{
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};

static GLubyte PquadIndices[1][4] =
{
    {0, 3, 2, 1}
};

void piramitCiz(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i < 4; i++)
    {
        getNormal3p(v_pyramid[p_Indices[i][0]][0], v_pyramid[p_Indices[i][0]][1], v_pyramid[p_Indices[i][0]][2],
            v_pyramid[p_Indices[i][1]][0], v_pyramid[p_Indices[i][1]][1], v_pyramid[p_Indices[i][1]][2],
            v_pyramid[p_Indices[i][2]][0], v_pyramid[p_Indices[i][2]][1], v_pyramid[p_Indices[i][2]][2]);
        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i < 1; i++)
    {
        getNormal3p(v_pyramid[PquadIndices[i][0]][0], v_pyramid[PquadIndices[i][0]][1], v_pyramid[PquadIndices[i][0]][2],
            v_pyramid[PquadIndices[i][1]][0], v_pyramid[PquadIndices[i][1]][1], v_pyramid[PquadIndices[i][1]][2],
            v_pyramid[PquadIndices[i][2]][0], v_pyramid[PquadIndices[i][2]][1], v_pyramid[PquadIndices[i][2]][2]);
        glVertex3fv(&v_pyramid[PquadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][3]][0]);
    }
    glEnd();

}

void poligon(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(6, 0);
    glVertex2f(5.8, 1);
    glVertex2f(5.2, 2);
    glVertex2f(5, 2.2);
    glVertex2f(4, 2.8);
    glVertex2f(3, 3);
    glVertex2f(2, 2.8);
    glVertex2f(1, 2.2);
    glVertex2f(0.8, 2);
    glVertex2f(0.2, 1);
    //glVertex2f(0,0);

    glEnd();
}

void poligonCizgi(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_LINE_STRIP);
    //glVertex2f(0,0);
    glVertex2f(6, 0);
    glVertex2f(5.8, 1);
    glVertex2f(5.2, 2);
    glVertex2f(5, 2.2);
    glVertex2f(4, 2.8);
    glVertex2f(3, 3);
    glVertex2f(2, 2.8);
    glVertex2f(1, 2.2);
    glVertex2f(0.8, 2);
    glVertex2f(0.2, 1);
    glVertex2f(0, 0);

    glEnd();
}

void kureCiz(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine = 90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidSphere(3.0, 20, 16);
}

void dolap()
{

        //dolap
    glPushMatrix();
    glTranslatef(4, 0, 4.4);
    glScalef(0.5, 1, 0.5);
    kupCiz(0.741, 0.718, 0.420, 0.341, 0.318, 0.210);
    glPopMatrix();

    //dolap üst yatay çizgi
    glPushMatrix();
    glTranslatef(4, 1, 5.9);
    glScalef(0.5, 0.01, 0.0001);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //dolap üst 2. yatay çizgi
    glPushMatrix();
    glTranslatef(4, 0.5, 5.9);
    glScalef(0.5, 0.01, 0.0001);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //dolap 3. yatay çizgi
    glPushMatrix();
    glTranslatef(4, 0, 5.9);
    glScalef(0.5, 0.01, 0.0001);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //dolap dikey çizgi
    glPushMatrix();
    glTranslatef(5.5, 0, 5.9);
    glScalef(0.01, 1, 0.0001);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //dolap sað dikey çizgi
    glPushMatrix();
    glTranslatef(4.75, 1, 5.9);
    glScalef(0.01, 0.67, 0.0001);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //dolap sol dikey çizgi
    glPushMatrix();
    glTranslatef(4, 0, 5.9);
    glScalef(0.01, 1, 0.0001);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //dolap sað tutacak
    glPushMatrix();
    glTranslatef(5, 1.4, 5.9);
    glScalef(0.02, 0.18, 0.01);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //dolap sað tutacak dairesi
    glPushMatrix();
    glTranslatef(5.02, 1.9, 5.91);
    glScalef(0.02, 0.02, 0.01);
    kureCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05, 10);
    glPopMatrix();

    //dolap sol tutacak
    glPushMatrix();
    glTranslatef(4.5, 1.4, 5.9);
    glScalef(0.02, 0.18, 0.01);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //dolap sol tutacak dairesi
    glPushMatrix();
    glTranslatef(4.52, 1.9, 5.91);
    glScalef(0.02, 0.02, 0.01);
    kureCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05, 10);
    glPopMatrix();

    //dolap üst çekmece tutacaðý
    glPushMatrix();
    glTranslatef(4.5, 0.7, 5.9);
    glScalef(0.16, 0.02, 0.01);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //cdolap alt çekmece tutacaðý
    glPushMatrix();
    glTranslatef(4.5, 0.25, 5.9);
    glScalef(0.16, 0.02, 0.01);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
}

void oda()
{
    // halý
    //glColor3f(0.2, 0.8, 0.8);
    glPushMatrix();
    //glScalef(5, 0.1, 7);
    glTranslatef(3, -0.2, 7);
    glScalef(1.3, 0.01, 1.7);
    kupCiz(0.24, 0.2, 0.45, 0.482, 0.408, 0.933);
    //kupCiz(0.482, 0.408, 0.933, 0.24, 0.2, 0.45);
    glPopMatrix();

    // arka duvar
    //glColor3f(1, 0.8, 0.5);
    glPushMatrix();
    glTranslatef(-1.5, -1, .5);
    glScalef(5, 2, 0.1);
    kupCiz(1, 0.8, 0.7, 0.5, 0.4, 0.35);
    glPopMatrix();

    // sol duvar
    //glColor3f(1, 0.8, 0.7);
    glPushMatrix();
    glTranslatef(-4.5, -1, 0);
    glScalef(1, 2, 5);
    kupCiz(1, 0.8, 0.7, 0.5, 0.4, 0.35);
    glPopMatrix();

    // sað duvar
    //glColor3f(1, 0.8, 0.7);
    glPushMatrix();
    glTranslatef(8, -1, 0);
    glScalef(0.2, 2, 5);
    kupCiz(1, 0.8, 0.7, 0.863, 0.863, 0.863);
    glPopMatrix();

    //tavan
     //glColor3f(1.0, 0.9, 0.8);
    glPushMatrix();
    glTranslatef(-2, 5.1, 0);
    glScalef(5, 0.1, 7);
    kupCiz(1.0, 0.9, 0.8, 0.412, 0.412, 0.412);
    glPopMatrix();

    // zemin
    glPushMatrix();
    glScalef(5, 0.1, 7);
    glTranslatef(-1, -5, 0); //-1,-5,.5
    //glScalef(5, 0.1, 7);
    kupCiz(0.1, 0.2, 0.4, 0.502, 0.502, 0.502);
    glPopMatrix();
}

void yatak()
{
    //yatak kafalýk
    glPushMatrix();
    glScalef(0.1, 0.5, 0.9);
    glTranslatef(-2, -0.5, 6.2);
    kupCiz(0.5, 0.2, 0.2, 0.25, 0.1, 0.1);
    glPopMatrix();

    //yatak gövde
    glPushMatrix();
    glScalef(1, 0.2, 0.9); //1, 0.2, 0.9
    glTranslatef(0, -0.5, 6.2);
    kupCiz(0.824, 0.706, 0.549, 0.412, 0.353, 0.2745);
    glPopMatrix();

    //saðdaki yastýk
    //glColor3f(0.627, 0.322, 0.176);
    glPushMatrix();
    glTranslatef(0.5, 0.5, 6);
    glRotatef(40, 0, 0, 1);
    glScalef(0.1, 0.15, 0.28);
    kupCiz(0.627, 0.322, 0.176, 0.3135, 0.161, 0.088);
    glPopMatrix();

    //soldaki yastýk
    //glColor3f(0.627, 0.322, 0.176);
    glPushMatrix();
    glTranslatef(0.5, 0.5, 7.2);
    glRotatef(42, 0, 0, 1);
    glScalef(0.1, 0.15, 0.28);
    kupCiz(0.627, 0.322, 0.176, 0.3135, 0.161, 0.088);
    glPopMatrix();

    //yorgan
    //glColor3f(0.627, 0.322, 0.176);
    glPushMatrix();
    glTranslatef(1.4, 0.45, 5.5);
    //glRotatef(22, 0,0,1);
    glScalef(0.5, 0.05, 0.95);
    kupCiz(0.122, 0.206, 0.446, 0.255, 0.412, 0.882);
    glPopMatrix();

    //yorgan sol alt tarafý
    //glColor3f(0.627, 0.322, 0.176);
    glPushMatrix();
    glTranslatef(1.4, -0.3, 8.16);
    //glRotatef(22, 0,0,1);
    glScalef(0.5, 0.25, 0.05);
    kupCiz(0.122, 0.206, 0.446, 0.255, 0.412, 0.882);
    glPopMatrix();
}

void komodin()
{

      //komodin
    glPushMatrix();
    glTranslatef(0.5, -0.1, 8.7); //0.5,-0.1,9
    glScalef(0.12, 0.2, 0.23);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //komodinin çekmece kýsmý
    glPushMatrix();
    glTranslatef(0.88, 0, 8.8);
    glScalef(0.0001, 0.11, 0.18);
    kupCiz(0.3, 0.2, 0.2, 0.15, 0.1, 0.1);
    glPopMatrix();

    //çekmecenin tutacaðý
    glPushMatrix();
    glTranslatef(0.9, 0.15, 9.05);
    glScalef(0.01, 0.02, 0.02);
    kureCiz(0.3, 0.1, 0.0, 0.15, 0.05, 0.0);
    glPopMatrix();
}

void lamba()
{
    //lamba temel
    glPushMatrix();
    glTranslatef(.6, 0.5, 8.95);
    glScalef(0.07, 0.02, 0.07);
    kupCiz(0, 0, 1, 0, 0, 0.5);
    glPopMatrix();

    //lamba duruþ
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(.7, 0.35, 9.05);
    glScalef(0.01, 0.2, 0.01);
    kupCiz(1, 0, 0, 0.5, 0.0, 0.0);
    glPopMatrix();

    // Abajur
    glColor3f(0.0, 0.030, 0.545);
    glPushMatrix();
    glTranslatef(.6, 0.9, 8.9);
    glScalef(0.08, 0.09, 0.08);
    yamukCiz(0.000, 0.000, 0.545, 0, 0, 0.2725); // Abajurun tepesi
    glPopMatrix();
}




void sifonyer()
{

    
        //sifonyer sol gövde
    glPushMatrix();
    glTranslatef(5.9, 0, 4.6);
    glScalef(0.2, 0.2, 0.2);
    kupCiz(0.545, 0.271, 0.075, 0.2725, 0.1355, 0.0375);
    glPopMatrix();


       //sifonyer sað gövde
    glPushMatrix();
    glTranslatef(7, 0, 4.6);
    glScalef(0.2, 0.2, 0.2);
    kupCiz(0.545, 0.271, 0.075, 0.2725, 0.1355, 0.0375);
    glPopMatrix();


         //sifonyer üst gövde
    glPushMatrix();
    glTranslatef(5.9, 0.6, 4.6);
    glScalef(0.57, 0.1, 0.2);
    kupCiz(0.545, 0.271, 0.075, 0.2725, 0.1355, 0.0375);
    glPopMatrix();

    //sifonyer üst gövdedeki alt þerit
    glPushMatrix();
    glTranslatef(5.9, 0.6, 5.2);
    //glRotatef(22, 0,0,1);
    glScalef(0.57, 0.01, 0.0001);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //sifonyer üst gövdedeki üst þerit
    glPushMatrix();
    glTranslatef(5.9, 0.9, 5.2);
    //glRotatef(22, 0,0,1);
    glScalef(0.57, 0.01, 0.0001);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //þifonyer üst gövde kolu
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(6.5, 0.75, 5.2);
    //glRotatef(22, 0,0,1);
    glScalef(0.16, 0.02, 0.0001);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //þifonyer sol gövde kolu
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(6.4, 0.1, 5.2);
    //glRotatef(22, 0,0,1);
    glScalef(0.02, 0.13, 0.0001);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //þifonyer sað gövde kolu
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(7.1, 0.1, 5.2);
    //glRotatef(22, 0,0,1);
    glScalef(0.02, 0.13, 0.0001);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //þifonyer ana ayna
    glPushMatrix();
    glTranslatef(6.2, 0.9, 4.7);
    //glRotatef(22, 0,0,1);
    glScalef(0.36, 0.5, 0.0001);
    kupCiz(0.690, 0.878, 0.902, 0.345, 0.439, 0.451, 10);
    glPopMatrix();

    //þifonyer sol ayna
    glPushMatrix();
    glTranslatef(5.92, 0.9, 4.7);
    //glRotatef(0, 0,1,0);
    glScalef(0.1, 0.48, 0.0001);
    kupCiz(0.690, 0.878, 0.902, 0.345, 0.439, 0.451, 10);
    glPopMatrix();

    //þifonyer sol ayna sol þerit
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(5.92, 0.9, 4.71);
    //glRotatef(22, 0,0,1);
    glScalef(0.019, 0.48, 0.0001);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //þifonyer sol ayna sað þerit
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(6.17, 0.9, 4.71);
    //glRotatef(22, 0,0,1);
    glScalef(0.019, 0.48, 0.0001);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //dressing table aynadaki þerit
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(5.92, 0.9, 4.71);
    //glRotatef(22, 0,0,1);
    glScalef(0.55, 0.019, 0.0001);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //dressing table sað ayna üst þerit
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(5.92, 2.3, 4.71);
    //glRotatef(22, 0,0,1);
    glScalef(0.1, 0.019, 0.0001);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //dressing table sað ayna
    glPushMatrix();
    glTranslatef(7.25, 0.9, 4.7);
    //glRotatef(-40, 0,1,0);
    glScalef(0.1, 0.48, 0.0001);
    kupCiz(0.690, 0.878, 0.902, 0.345, 0.439, 0.451, 10);
    glPopMatrix();

    //dressing table sol ayna üst þerit
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(7.25, 2.3, 4.71);
    //glRotatef(22, 0,0,1);
    glScalef(0.1, 0.019, 0.0001);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //sifonyer sað ayna sol þerit
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(7.25, 0.9, 4.71);
    //glRotatef(22, 0,0,1);
    glScalef(0.019, 0.48, 0.0001);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //sifonyer sað ayna sað þerit
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(7.5, 0.9, 4.71);
    //glRotatef(22, 0,0,1);
    glScalef(0.019, 0.48, 0.0001);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //sifonyer ana ayna poligon parçasý
    glColor3f(0.690, 0.878, 0.902);
    glPushMatrix();
    glTranslatef(6.2, 2.4, 4.7);
    //glRotatef(22, 0,0,1);
    glScalef(0.18, 0.18, 2);
    poligon(0.690, 0.878, 0.902, 0.345, 0.439, 0.451, 10);
    glPopMatrix();

    //sifonyer üst yuvarlak þerit
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(6.2, 2.4, 4.71);
    glScalef(.18, .18, 1);
    poligonCizgi(0.2, 0.1, 0.1, 0.1, 0.05, 0.05, 50);
    glPopMatrix();
    
}

void tv()
{


    //tv çerçeve
    glPushMatrix();
    glTranslatef(0.3, 1, 1);
    glScalef(0.71, 0.5, 0.08);
    kupCiz(0.001, 0.0001, 0.00001, 0.000, 0.000, 0.000);
    glPopMatrix();

    //tv ekran
    glPushMatrix();
    glTranslatef(0.42, 1.15, 1);
    glScalef(0.65, 0.4, 0.10);
    kupCiz(0.001, 0.0001, 0.00001, 0.412, 0.412, 0.412);
    glPopMatrix();

}

void Saat()
{
    //Saat ************************************************************

        //saat gövde
    glColor3f(0.545, 0.271, 0.075);
    glPushMatrix();
    glTranslatef(-0.9, 1.8, 7.87);
    //glRotatef(22, 0,0,1);
    glScalef(0.08, 0.25, 0.1);
    kupCiz(0.400, 0.804, 0.667, 0.2, 0.4, 0.0375, 50);
    glPopMatrix();

    //clock gövde beyaz kýsým
    glPushMatrix();
    glTranslatef(-0.83, 1.9, 7.9);
    //glRotatef(22, 0,0,1);
    glScalef(0.06, 0.2, 0.08);
    kupCiz(1.000, 0.894, 0.710, 1.000, 0.894, 0.710);
    glPopMatrix();

    //saat akrep
    glPushMatrix();
    glTranslatef(-0.65, 2.18, 8.01);
    glRotatef(45, 1, 0, 0);
    glScalef(0.0001, 0.01, 0.04);
    kupCiz(0, 0, 0, 0, 0, 0);
    glPopMatrix();

    //saat yelkovan
    glPushMatrix();
    glTranslatef(-0.65, 2.18, 8.01);
    glRotatef(90, 1, 0, 0);
    glScalef(0.0001, 0.012, 0.08);
    kupCiz(0, 0, 0, 0, 0, 0);
    glPopMatrix();


       //saat çubuk
    glColor3f(0.2, 0.1, 0.1); //0.2,0.1,0.1
    glPushMatrix();
    glTranslatef(-0.7, 2, 8.1);
    glRotatef(theta, 1, 0, 0);
    glScalef(0.0001, 0.2, 0.03);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //saat çubuktaki top
    glColor3f(0.2, 0.1, 0.1); //0.2,0.1,0.1
    glPushMatrix();
    glTranslatef(-0.72, 1.42, z);
    //glRotatef(x, 1,0,0);
    glScalef(0.035, 0.035, 0.035);
    //drawCube();
    kureCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05, 10);
    glPopMatrix();

    //clock üst piramit
    glPushMatrix();
    glTranslatef(-0.9, 2.5, 7.81);
    //glRotatef(x, 1,0,0);
    glScalef(0.16, 0.1, 0.2);
    piramitCiz(0.400, 0.804, 0.667, 0.2, 0.4, 0.0375, 50);
    glPopMatrix();
}

void ayna()
{
    //ayna 
    glPushMatrix();
    glTranslatef(-0.9, 1, 8.9); //0.5,1,9.6
    glScalef(0.0001, .6, .3);
    kupCiz(1.0, 1.0, 1.0, 0.05, 0.05, 0.05);
    glPopMatrix();

    //ayna sað kenar
    glPushMatrix();
    glTranslatef(-0.9, 1, 8.9);
    glScalef(0.04, 0.6, 0.0001);
    kupCiz(0.8, 0.6, 0.4, 0.4, 0.3, 0.2);
    glPopMatrix();

    //ayna sol kenar
    glPushMatrix();
    glTranslatef(-0.9, 1, 9.8);
    glScalef(0.04, 0.6, 0.0001);
    kupCiz(0.8, 0.6, 0.4, 0.4, 0.3, 0.2);
    glPopMatrix();

    //ayna üst kenar
    glPushMatrix();
    glTranslatef(-0.7, 2.7, 8.9);
    glScalef(0.0001, 0.05, 0.4);
    kupCiz(0.7, 0.6, 0.5, 0.35, 0.3, 0.25);
    glPopMatrix();


    //ayna alt kenar
    glPushMatrix();
    glTranslatef(-0.8, 1.02, 8.9);
    glScalef(0.0001, 0.02, 0.34);
    kupCiz(0.7, 0.6, 0.5, 0.35, 0.3, 0.25);
    glPopMatrix();

 
}

void masa()
{
    //masa yüzey
    glPushMatrix();
    //glTranslatef(5, 0.2, 10);
    glTranslatef(4.4, 1.2, 9);
    //glScalef(0.1, 0.02, 0.1);
    glScalef(0.4, 0.05, 0.5);
    //kureCiz(0.5, 0.2, 0, 0.25, 0.1, 0, 20);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // ayak
    glPushMatrix();
    glTranslatef(4.98, -0.1, 10);
    glScalef(0.02, 0.45, 0.02);
    kupCiz(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    // taban
    glPushMatrix();
    glTranslatef(5, -0.1, 10);
    glScalef(0.05, 0.01, 0.05);
    kureCiz(0.5, 0.2, 0, 0.25, 0.1, 0, 20);
    glPopMatrix();
}


void lightBulb1() // saðdaki tepe lambasýný ve aydýnlanma deðerlerini ayarlar
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = { 1.000, 1,1, 0.0 };

    glPushMatrix();
    glTranslatef(5, 5, 8);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    if (switchOne == true) {
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }
    else {
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }

    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

void lightBulb2() // soldaki tepe lambasýný ve aydýnlanma deðerlerini ayarlar
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = { 1,1,1, 1.0 };

    glPushMatrix();
    glTranslatef(0, 5, 8);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    if (switchTwo == true) {
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }
    else {
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

void lightBulb3()// abajurun içindeki lambasýný ve aydýnlanma deðerlerini ayarlar
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = { 1,1,1, 1.0 };

    glPushMatrix();
    glTranslatef(0.7, 1.5, 9.0);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    if (switchLamp == true) {
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }
    else {
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}


void lightOne() // Iþýk kaynaðýnýn aydýnlatma ile ilgili deðiþkenlerini yapýlandýrýr
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 5.0, 5.0, 8.0, 1.0 }; //5 5 10

    //glEnable( GL_LIGHT0);

    if (amb1 == true) { glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); }
    else { glLightfv(GL_LIGHT0, GL_AMBIENT, no_light); }

    if (diff1 == true) { glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); }
    else { glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light); }

    if (spec1 == true) { glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); }
    else { glLightfv(GL_LIGHT0, GL_SPECULAR, no_light); }

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}

void lightTwo()// Iþýk kaynaðýnýn aydýnlatma ile ilgili deðiþkenlerini yapýlandýrýr
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 0.9, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 5.0, 8.0, 1.0 };

    //glEnable( GL_LIGHT1);

    if (amb2 == true) { glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient); }
    else { glLightfv(GL_LIGHT1, GL_AMBIENT, no_light); }

    if (diff2 == true) { glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse); }
    else { glLightfv(GL_LIGHT1, GL_DIFFUSE, no_light); }

    if (spec2 == true) { glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular); }
    else { glLightfv(GL_LIGHT1, GL_SPECULAR, no_light); }

    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glPopMatrix();
}

void lampLight() // Abajurdaki Iþýk kaynaðýnýn aydýnlatma ile ilgili deðiþkenlerini yapýlandýrýr
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.7, 1.5, 9.0, 1.0 };  //0.7, 4.5, 9.0

    //glEnable( GL_LIGHT2);

    if (amb3 == true) { glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient); }
    else { glLightfv(GL_LIGHT2, GL_AMBIENT, no_light); }

    if (diff3 == true) { glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse); }
    else { glLightfv(GL_LIGHT2, GL_DIFFUSE, no_light); }

    if (spec3 == true) { glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular); }
    else { glLightfv(GL_LIGHT2, GL_SPECULAR, no_light); }

    glLightfv(GL_LIGHT2, GL_POSITION, light_position);
    GLfloat spot_direction[] = { 0.3, -1, -0.8 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 35.0);
    glPopMatrix();
}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, refX, refY, refZ, 0, 1, 0); //7,2,15, 0,0,0, 0,1,0

    glEnable(GL_LIGHTING);
    lightOne();
    lightTwo();
    lampLight();
    oda();
    yatak();
    komodin();
    lamba();
    tv();
    dolap();
    sifonyer();
    Saat();
    ayna();
    masa();
    lightBulb1();
    lightBulb2();
    //lightBulb3();
    glDisable(GL_LIGHTING);

    glFlush();
    glutSwapBuffers();
}

void klavyeFonk(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w': // move eye point upwards along Y axis
        eyeY += 1.0;
        break;
    case 's': // move eye point downwards along Y axis
        eyeY -= 1.0;
        break;
    case 'a': // move eye point left along X axis
        eyeX -= 1.0;
        break;
    case 'd': // move eye point right along X axis
        eyeX += 1.0;
        break;
    case 'o':  //zoom out
        eyeZ += 1;
        break;
    case 'i': //zoom in
        eyeZ -= 1;
        break;
    case 'q': //back to default eye point and ref point
        eyeX = 7.0; eyeY = 2.0; eyeZ = 15.0;
        refX = 0.0; refY = 0.0; refZ = 0.0;
        break;
    case 'j': // move ref point upwards along Y axis
        refY += 1.0;
        break;
    case 'n': // move ref point downwards along Y axis
        refY -= 1.0;
        break;
    case 'b': // move ref point left along X axis
        refX -= 1.0;
        break;
    case 'm': // move eye point right along X axis
        refX += 1.0;
        break;
    case 'k':  //move ref point away from screen/ along z axis
        refZ += 1;
        break;
    case 'l': //move ref point towards screen/ along z axis
        refZ -= 1;
        break;
    case '1': //to turn on and off light one
        if (switchOne == false)
        {
            switchOne = true; amb1 = true; diff1 = true; spec1 = true;
            glEnable(GL_LIGHT0); break;
        }
        else if (switchOne == true)
        {
            switchOne = false; amb1 = false; diff1 = false; spec1 = false; glDisable(GL_LIGHT0); break;
        }
    case '2': //to turn on and off light two
        if (switchTwo == false)
        {
            switchTwo = true; amb2 = true; diff2 = true; spec2 = true;
            glEnable(GL_LIGHT1); break;
        }
        else if (switchTwo == true)
        {
            switchTwo = false; amb2 = false; diff2 = false; spec2 = false;
            glDisable(GL_LIGHT1); break;
        }
    case '3': //to turn on and off light one
        if (switchLamp == false)
        {
            switchLamp = true; amb3 = true; diff3 = true; spec3 = true;
            glEnable(GL_LIGHT2); break;
        }
        else if (switchLamp == true)
        {
            switchLamp = false; amb3 = false; diff3 = false; spec3 = false;
            glDisable(GL_LIGHT2); break;
        }
    case'4': //turn on/off ambient light 1
        if (amb1 == false) { amb1 = true; break; }
        else { amb1 = false; break; }
    case'5':
        if (diff1 == false) { diff1 = true; break; }
        else { diff1 = false; break; }
    case'6':
        if (spec1 == false) { spec1 = true; break; }
        else { spec1 = false; break; }
    case'7': //turn on/off ambient light 2
        if (amb2 == false) { amb2 = true; break; }
        else { amb2 = false; break; }
    case'8':
        if (diff2 == false) { diff2 = true; break; }
        else { diff2 = false; break; }
    case'9':
        if (spec2 == false) { spec2 = true; break; }
        else { spec2 = false; break; }
    case'e': //turn on/off ambient lamba light
        if (amb3 == false) { amb3 = true; break; }
        else { amb3 = false; break; }
    case'r':
        if (diff3 == false) { diff3 = true; break; }
        else { diff3 = false; break; }
    case't':
        if (spec3 == false) { spec3 = true; break; }
        else { spec3 = false; break; }
    case 27:    // Escape key
        exit(1);
    }

    glutPostRedisplay();
}


void animasyon()
{
    if (redFlag == true)
    {
        theta += 2;
        z -= 0.02; //0.016667;
        if (theta >= 196 && theta <= 210)
        {
            y = 1.44;
        }
        else if (theta >= 180 && theta <= 194)
        {
            y = 1.42;
        }
        else if (theta >= 180 && theta <= 194)
        {
            y = 1.4;
        }
        else if (theta >= 164 && theta <= 178)
        {
            y = 1.42;
        }

        if (theta == 210)
        {
            redFlag = false;
        }
    }
    else if (redFlag == false)
    {
        theta -= 2;
        z += 0.02;//0.016667;

        if (theta >= 196 && theta <= 210)
        {
            y = 1.44;
        }
        else if (theta >= 180 && theta <= 194)
        {
            y = 1.42;
        }
        else if (theta >= 180 && theta <= 194)
        {
            y = 1.4;
        }
        else if (theta >= 164 && theta <= 178)
        {
            y = 1.42;
        }

        if (theta == 150)
        {
            redFlag = true;
        }
    }

    glutPostRedisplay();
    
}

void fullScreen(int w, int h)
{
    //0 olursa bölüm tanýmsýz çýkacaðýndan 1 e eþitliyoruz.
    if (h == 0)
        h = 1;
    float ratio = (GLfloat)w / (GLfloat)h;         //En boy oraný hesabý

    //Perspektif koordinat sistemini ayarladýk
    glMatrixMode(GL_PROJECTION);                   
    glLoadIdentity();                              

    glViewport(0, 0, w, h);                        
    gluPerspective(60, ratio, 1, 500);             
    glMatrixMode(GL_MODELVIEW);                    //Perspektif vs ayarýndan sonra model görünümüne tekrar geçtik.
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    std::cout << "Goz pointerini hareket ettirmek icin:" << std::endl;
    std::cout << "w: yukari" << std::endl;
    std::cout << "s: asagi" << std::endl;
    std::cout << "a: sol" << std::endl;
    std::cout << "d: sag" << std::endl;
    std::cout << "i: yakinlas" << std::endl;
    std::cout << "o: uzaklas" << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "Kamera pointerini hareket ettirmek icin:" << std::endl;
    std::cout << "j: yukari" << std::endl;
    std::cout << "n: asagi" << std::endl;
    std::cout << "b: sol" << std::endl;
    std::cout << "m: sag" << std::endl;
    std::cout << "l: yakinlas" << std::endl;
    std::cout << "k: uzaklas" << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "Q ile ayarlari resetle" << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "Isiklandirma icin:      " << std::endl;
    std::cout << "1. Isik kaynagi [Ekranin sagindaki isik " << std::endl;
    std::cout << "1: Isigi ac kapat     " << std::endl;
    std::cout << "4: Ambient ayarini ac kapat     " << std::endl;
    std::cout << "5: diffusion ayarini ac kapat      " << std::endl;
    std::cout << "6: specular ayarini ac kapat      " << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "2. Isik kaynagi [Ekranin solundaki isik " << std::endl;
    std::cout << "2: Isigi ac kapat     " << std::endl;
    std::cout << "7: Ambient ayarini ac kapat     " << std::endl;
    std::cout << "8: diffusion ayarini ac kapat     " << std::endl;
    std::cout << "9: specular ayarini ac kapat      " << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "Abajurdaki isik" << std::endl;
    std::cout << "3: Isigi ac kapat     " << std::endl;
    std::cout << "e: Ambient ayarini ac kapat    " << std::endl;
    std::cout << "r: diffusion ayarini ac kapat      " << std::endl;
    std::cout << "t: specular ayarini ac kapat      " << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "____________________" << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "      " << std::endl;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("1607063 Bedroom");

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glutReshapeFunc(fullScreen);
    glutDisplayFunc(display);
    glutKeyboardFunc(klavyeFonk);
    glutIdleFunc(animasyon);
    glutMainLoop();

    return 0;
}
