/**
 * File             : Main.cpp
 * Deskripsi        : Tugas Besar Submarine Game 
 * Anggota Kelompok : Rania                           24060122120013
		              Miriam Stefani Abigail Hutapea  24060122130051
                      Nadiva Aulia Inaya			  24060122130093
                      Demina Ayunda Chesara			  24060122140149
**/
#include<windows.h>
#include <GL/glut.h>
#include<bits/stdc++.h>
#include <stdlib.h>
#define rad (3.1416/180)
#define EN_SIZE 20

#include "RGBpixmap.cpp"
using namespace std;
RGBpixmap pix[6];

float zoom = 4;
int tola[5000][5000];
float tX = 0, tY = 0, tZ = -8, rX = 0, rY = 0, rZ = 4;
float tZ1 = -20, tZ2 = -40, tZ3 = -60, tZ4 = -80, tZ5 = -100, tZ6 = -120;
float rotX = 0, rotY = 0, rotZ = 0;
float cosX = 0, cosY = 1, cosZ = 0;
float angle = 0;
float xEye = 0.0f, yEye = 5.0f, zEye = 30.0f;
float cenX = 0, cenY = 0, cenZ = 0, roll = 0;
float radius = 0;
float theta = 0, slope = 0;
float speed = 0.3;
float angleBackFrac = 0.2;
float r[] = { 0.1,0.4,0.0,0.9,0.2,0.5,0.0,0.7,0.5,0.0 };
float g[] = { 0.2,0.0,0.4,0.5,0.2,0.0,0.3,0.9,0.0,0.2 };
float b[] = { 0.4,0.5,0.0,0.7,0.9,0.0,0.1,0.2,0.5,0.0 };
int TIME = 0;
bool START = false;
float torusPosX[7] = { 1,-2,3,-4,-2,0,2 };
float torusPosY[7] = { 2,3,10,6,7,4,1 };
int skor = 0;
bool rot = false;
bool lightEnabled = true; // Toggle for lighting
bool shadowEnabled = true; // Toggle for shadows
float cameraAngle = 0.0f;
float cameraHeight = 5.0f;

static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, ar, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void batuKarang(int R, int G, int B) {
    glColor3d(r[R + 4] * 2, g[G % 10] * 2.5, b[B + 2] / 2);
    glPushMatrix();
    glTranslated(0, 0, 0);
    glutSolidCube(1);
    glPopMatrix();
}

void submarine() {
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double a = t * 90.0;
    glColor3d(0.2, 0.2, 0.5);
    glPushMatrix();
    glTranslated(0, 0, 0);
    glScaled(3, 0.6, 0.6);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3d(0.2, 0.2, 0.3);
    glPushMatrix();
    glTranslated(1, 0.5, 0);
    glScaled(0.5, 1, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glColor3d(0.2, 0.2, 0.3);
    glPushMatrix();
    glTranslated(-2.5, -0.2, 0);
    glRotated(90, 0, 1, 0);
    glScaled(0.1, 0.1, 1.5);
    glutSolidCube(1);
    glPopMatrix();

    glColor3d(0.2, 0.2, 0.3);
    glPushMatrix();
    glTranslated(-2.5, 0.3, 0);
    glRotated(90, 1, 0, 0);
    glScaled(0.1, 0.1, 1.5);
    glutSolidCube(1);
    glPopMatrix();

    glColor3d(0.8, 0.8, 0.8);
    glPushMatrix();
    glTranslated(-3.1, 0, 0);
    glRotated(90, 0, 1, 0);
    glRotated(a, 0, 0, 1);
    glScaled(0.6, 0.6, 0.6);

    for (int i = 0; i < 4; ++i) {
        glPushMatrix();
        glRotated(90 * i, 0, 0, 1);
        glTranslated(0.5, 0, 0);
        glRotated(45, 0, 1, 0);
        glRotated(-45, 1, 0, 0);
        glScaled(1.0, 1.0, 0.01);
        glutSolidCone(0.5, 1.0, 20, 20);
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix();
    glTranslated(0, -5.0, 0);
    glColor3d(0.1, 0.1, 0.1);
    glPushMatrix();
    glTranslated(0, 0, 0);
    glScaled(3, 0.05, 0.6);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1, 0.05, 0);
    glScaled(0.5, 0.1, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-2.5, -0.2, 0);
    glRotated(90, 0, 1, 0);
    glScaled(0.05, 0.05, 1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-2.5, 0.15, 0);
    glRotated(90, 1, 0, 0);
    glScaled(0.05, 0.05, 1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();
}

void drawCube(double width, double height, double depth) {
    glPushMatrix();
    glScaled(width, height, depth);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawSquidHouse() {
    glColor3f(0.2, 0.2, 0.5);
    glPushMatrix();
    glTranslated(0, 1.5, 0);
    drawCube(1, 3, 1);
    glPopMatrix();

    glColor3f(0.1, 0.1, 0.4);
    glPushMatrix();
    glTranslated(0, 3.5, 0);
    drawCube(1, 0.5, 1);
    glPopMatrix();

    glColor3f(0.1, 0.1, 0.3);
    glPushMatrix();
    glTranslated(0, 1.5, 0.6);
    drawCube(0.2, 1, 0.2);
    glPopMatrix();

    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glTranslated(0.3, 2.2, 0.55);
    drawCube(0.2, 0.5, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-0.3, 2.2, 0.55);
    drawCube(0.2, 0.5, 0.05);
    glPopMatrix();

    glColor3f(0.6, 0.3, 0.1);
    glPushMatrix();
    glTranslated(0, 0.5, 0.55);
    drawCube(0.3, 0.8, 0.05);
    glPopMatrix();
}

void kumpulanBatuKarang(int n, int R, int G) {
    for (int i = 0;i < n;i++) {
        glPushMatrix();
        glTranslated(0, 0.09 + i, 0);
        batuKarang(G, R, i);
        glPopMatrix();
    }
}

void kumpulanSquidHouse() {
    glColor3d(0, 0.5, 0.1);
    glPushMatrix();
    glTranslated(0, 0, 0);
    glScaled(EN_SIZE * 2, 0.3, EN_SIZE * 2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-4, 0, -6);
    drawSquidHouse();
    glTranslatef(0, -0.3, 0);
    glColor3d(0.2, 0.2, 0.2);
    drawSquidHouse();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-4, 0, -6);
    drawSquidHouse();
    glRotatef(90, 0, 1, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(4, 0, 6);
    drawSquidHouse();
    glTranslatef(0, -0.3, 0);
    glColor3d(0.2, 0.2, 0.2);
    drawSquidHouse();
    glPopMatrix();

    glPushMatrix();
    glTranslated(4, 0, 6);
    drawSquidHouse();
    glRotatef(90, 0, 1, 0);
    glPopMatrix();
}

void elemenHiasan(int n, float* z) {
    glColor3d(1, 0.95, 0.81);
    glPushMatrix();
    glTranslated(0, 0, 0);
    glScaled(EN_SIZE * 2, 0.3, EN_SIZE * 2);
    glutSolidCube(2);
    glPopMatrix();

    for (int i = -(EN_SIZE / 2) + 1; i < (EN_SIZE / 2); i += 2) {
        for (int j = -(EN_SIZE / 2) + 1; j < (EN_SIZE / 2); j += 2) {
            if (tola[i + (EN_SIZE / 2) + 1][j + (EN_SIZE / 2) + 1] != 0) {
                glPushMatrix();
                glTranslated(i, 0, j);
                kumpulanBatuKarang(tola[i + (EN_SIZE / 2) + 1][j + (EN_SIZE / 2) + 1], i, j);
                glPopMatrix();
                kumpulanSquidHouse();
            }
            else if (i >= -5 && i <= 5) {
            }
            else {
                tola[i + (EN_SIZE / 2) + 1][j + (EN_SIZE / 2) + 1] = (rand() % 5) + 1;
                glPushMatrix();
                glTranslated(i, 0, j);
                kumpulanBatuKarang(tola[i + (EN_SIZE / 2) + 1][j + (EN_SIZE / 2) + 1], i, j);
                glPopMatrix();
            }
        }
    }
    glColor3d(0.95, 0.49, 0.74);
    glPushMatrix();
    glTranslated(torusPosX[n], torusPosY[n], 0);
    glScaled(0.3, 0.3, 0.3);
    glutSolidSphere(1.0, 50, 50);
    glPopMatrix();
    if (torusPosX[n] + tX >= -0.5 && torusPosX[n] + tX <= 0.5) {
        if (*z > 0 && *z < 1) {
            skor += 10;
        }
    }
}

void draw() {
    double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double a = t * 90.0;
    TIME = t;
    if (rotX > 11) rotX = 11;
    if (rotX < -11) rotX = -11;
    if (rotZ > 10) rotZ = 10;
    if (rotZ < -15) rotZ = -15;
    glPushMatrix();
    glTranslated(0, 1, 0);
    glRotated(90, 0, 1, 0);
    glRotated(5, 0, 0, 1);
    glRotated(rotX, 1, 0, 0);
    glRotated(rotY, 0, 1, 0);
    glRotated(rotZ, 0, 0, 1);
    glScaled(0.4, 0.4, 0.4);
    submarine();
    glPopMatrix();
    if (tX >= 4.1) tX = 4.1;
    if (tX <= -4.1) tX = -4.1;
    if (tY > 0.1) tY = 0.1;
    if (tY < -15) tY = -15;
    static float z = 0, z1 = -20, z2 = -40, z3 = -60, z4 = -80, z5 = -100, z6 = -120;
    glPushMatrix();
    glTranslated(tX, tY, z);
    elemenHiasan(2, &z);
    glPopMatrix();
    glPushMatrix();
    glTranslated(tX, tY, z1);
    elemenHiasan(3, &z1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(tX, tY, z2);
    elemenHiasan(1, &z2);
    glPopMatrix();
    glPushMatrix();
    glTranslated(tX, tY, z3);
    elemenHiasan(5, &z3);
    glPopMatrix();
    glPushMatrix();
    glTranslated(tX, tY, z4);
    elemenHiasan(4, &z4);
    glPopMatrix();
    glPushMatrix();
    glTranslated(tX, tY, z5);
    elemenHiasan(2, &z5);
    glPopMatrix();
    glPushMatrix();
    glTranslated(tX, tY, z6);
    elemenHiasan(3, &z6);
    glPopMatrix();
    z += speed;
    z1 += speed;
    z2 += speed;
    z3 += speed;
    z4 += speed;
    z5 += speed;
    z6 += speed;
    if (z >= 20) z = -120;
    if (z1 >= 20) z1 = -120;
    if (z2 >= 20) z2 = -120;
    if (z3 >= 20) z3 = -120;
    if (z4 >= 20) z4 = -120;
    if (z5 >= 20) z5 = -120;
    if (z6 >= 20) z6 = -120;
    if (rotX > 0) rotX -= angleBackFrac;
    if (rotX < 0) rotX += angleBackFrac;
    if (rotY > 0) rotY -= angleBackFrac;
    if (rotY < 0) rotY += angleBackFrac;
    if (rotZ > 0) rotZ -= angleBackFrac;
    if (rotZ < 0) rotZ += angleBackFrac;
    speed += 0.5;
    if (speed >= 0.5) speed = 0.5;
}

void drawBitmapText(char* str, float x, float y, float z)
{
    char* c;
    glRasterPos3f(x, y + 8, z);
    for (c = str; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
    }
}

void drawStrokeText(char* str, int x, int y, int z)
{
    char* c;
    glPushMatrix();
    glTranslatef(x, y + 8, z);
    glScalef(0.002f, 0.002f, z);
    for (c = str; *c != '\0'; c++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
}

void drawStrokeText2(char* str, int x, int y, int z)
{
    char* c;
    glPushMatrix();
    glTranslatef(x, y + 8, z);
    glScalef(0.005f, 0.005f, z);
    for (c = str; *c != '\0'; c++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
}

void drawStrokeChar(char c, float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(x, y + 8, z);
    glScalef(0.002f, 0.002f, z);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
    glPopMatrix();
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double a = t * 90.0;
    double aa = a;
    if (!rot) {
        a = 0;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // Menghitung posisi kamera berdasarkan sudut dan ketinggian
    float xEye = 10.0f * sin(cameraAngle);
    float zEye = 10.0f * cos(cameraAngle);
    float yEye = cameraHeight;
    gluLookAt(xEye, yEye, zEye,  // Posisi kamera
        0, 4, 0,           // Titik yang dilihat
        0, 1.0f, 0.0f);    // Arah atas
    if (START) {
        glPushMatrix();
        glTranslated(0, 0, 0);
        glScaled(zoom, zoom, zoom);
        glRotated(a, 0, 1, 0);
        draw();
        glPopMatrix();
        glColor3f(0.0, 0.0, 0.0);
        drawStrokeText("UP: w, DOWN: s, LEFT: a, RIGHT: d, MAIN MENU: m", -9, 1, 0);
        glColor3f(0.0, 0.0, 0.0);
        drawStrokeText("TIME : ", 3, 1, 0);
        int mod, number = 0;
        while (TIME) {
            mod = TIME % 10;
            number = number * 10 + mod;
            TIME /= 10;
        }
        float tmp = 0;
        while (number) {
            mod = number % 10;
            drawStrokeChar(mod + 48, 4 + tmp, 1, 0);
            number /= 10;
            tmp += 0.2;
        }
        //menampilkan skor 
        char skor2[100];
        int skor3 = sprintf(skor2, "SKOR: %d", skor);
        drawStrokeText(skor2, 5, 1, 0);
    }
    else {
        glPushMatrix();
        glTranslated(0, 3, 0);
        glRotated(aa, 0, 1, 0);
        glScaled(1.5, 1.5, 1.5);
        submarine();
        glPopMatrix();
        glColor3f(0.0, 0.0, 0.0);
        drawStrokeText("PRESS g TO START", -1.5, -1, 0);
        glColor3f(0.0, 0.0, 0.0);
        drawStrokeText2("SUBMARINE GAME", -3, 0, 0);
    }
    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y) {
    float frac = 0.3;
    float rotFrac = 1;
    switch (key) {
    case 27:
    case 'q':
        exit(0);
        break;
    case 'r':
        rot = true;
        break;
    case 't':
        rot = false;
        break;
    case 'z':
        zoom += 0.05;
        break;
    case 'Z':
        zoom -= 0.05;
        break;
    case 'w':
        tY -= frac;
        rotZ += rotFrac;
        break;
    case 's':
        tY += frac;
        rotZ -= rotFrac;
        break;
    case 'a':
        tX += frac;
        rotX -= rotFrac * 3;
        rotY += rotFrac / 2;
        break;
    case 'd':
        tX -= frac;
        rotX += rotFrac * 3;
        rotY -= rotFrac / 2;
        break;
    case 'y':
        rotX -= rotFrac;
        break;
    case 'h':
        rotX += rotFrac;
        break;
    case 'p':
        rotY += rotFrac;
        break;
    case 'j':
        rotY -= rotFrac;
        break;
    case 'g':
        START = true;
        break;
    case 'm':
        START = false;
        break;
    case 'o':
        lightEnabled = !lightEnabled;
        if (lightEnabled) {
            glEnable(GL_LIGHTING);
        }
        else {
            glDisable(GL_LIGHTING);
        }
        break;
    case 'k':
        cameraAngle += 0.05;
        break;
    case 'c':
        cameraAngle -= 0.05;
        break;
    case 'i':
        cameraHeight += 0.5;
        break;
    case 'e':
        cameraHeight -= 0.5;
        break;
    }
    glutPostRedisplay();
}

void idle(void) {
    glutPostRedisplay();
}

const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


void init(void)
{
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1366, 720);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutCreateWindow("SUBMARINE GAME");
    glMatrixMode(GL_PROJECTION);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    glLoadIdentity();
    glClearColor(0.0, 0.5, 0.7, 1.0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glutMainLoop();
    return EXIT_SUCCESS;
}
