#include <GL/glut.h>

// Parámetros para rotación
float angleX = 20.0f, angleY = 30.0f;

// Configuración de iluminación
void setupLighting() {
    GLfloat lightAmbient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat lightDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightPosition[] = {2.0f, 4.0f, 2.0f, 1.0f};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_COLOR_MATERIAL); // Usa colores como material
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f); // Brillo
}

// Dibujar pirámide
void drawPyramid() {
    glBegin(GL_TRIANGLES);

    // Cara frontal
    glColor3f(1.0f, 0.5f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Cara derecha
    glColor3f(0.0f, 0.5f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Cara trasera
    glColor3f(0.5f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Cara izquierda
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();

    // Base
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glEnd();
}

// Dibujar suelo cuadriculado
void drawBackground() {
    glColor3f(0.6f, 0.6f, 0.6f); // Color más claro
    for (float z = -10.0f; z <= 10.0f; z += 1.0f) {
        glBegin(GL_LINES);
        glVertex3f(-10.0f, -1.5f, z);
        glVertex3f(10.0f, -1.5f, z);
        glEnd();
    }
    for (float x = -10.0f; x <= 10.0f; x += 1.0f) {
        glBegin(GL_LINES);
        glVertex3f(x, -1.5f, -10.0f);
        glVertex3f(x, -1.5f, 10.0f);
        glEnd();
    }
}

// Configuración inicial
void initGL() {
    glEnable(GL_DEPTH_TEST);
    setupLighting();
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
}

// Renderizado
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, -0.5f, -6.0f);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    drawBackground(); // Dibuja el suelo
    drawPyramid();    // Dibuja la pirámide

    glutSwapBuffers();
}

// Animación
void update(int value) {
    angleY += 2.0f;
    if (angleY > 360) angleY -= 360;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Ajustar ventana
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

// Main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Pirámide 3D con Fondo");

    initGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
