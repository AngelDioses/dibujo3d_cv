#include <GL/glut.h>

// Rotación de la esfera
float angleX = 0.0f, angleY = 0.0f;

// Configuración de iluminación
void setupLighting() {
    GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat lightDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightPosition[] = {2.0f, 4.0f, 2.0f, 1.0f};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);
}

// Dibujo del fondo en 3D (plano cuadriculado)
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

// Dibujar esfera 3D
void drawSphere() {
    glPushMatrix();
    glColor3f(0.2f, 0.5f, 1.0f); // Color azul claro
    glutSolidSphere(1.0f, 50, 50); // Esfera de radio 1 con alta resolución
    glPopMatrix();
}

// Configuración inicial
void initGL() {
    glEnable(GL_DEPTH_TEST);
    setupLighting();
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // Fondo azul oscuro
}

// Renderizado
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Posición de la cámara
    glTranslatef(0.0f, 0.0f, -6.0f);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    drawBackground(); // Fondo cuadriculado
    drawSphere();     // Esfera

    glutSwapBuffers();
}

// Animación
void update(int value) {
    angleX += 1.0f;
    angleY += 1.5f;
    if (angleX > 360) angleX -= 360;
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
    glutCreateWindow("Esfera Animada con Fondo 3D");

    initGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
