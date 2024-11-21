#include <GL/glut.h>

// Ángulos de rotación
float angleX = 0.0f;
float angleY = 0.0f;

// Inicialización de OpenGL
void initGL() {
    glEnable(GL_DEPTH_TEST); // Habilita la profundidad
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fondo negro
}

// Función para dibujar un cubo
void drawCube() {
    glBegin(GL_QUADS);

    // Cara frontal (roja)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);

    // Cara trasera (verde)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);

    // Cara superior (azul)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);

    // Cara inferior (amarilla)
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);

    // Cara derecha (magenta)
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);

    // Cara izquierda (cian)
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);

    glEnd();
}

// Dibuja el plano cuadriculado en 3D
void drawGrid() {
    glColor3f(0.6f, 0.6f, 0.6f); // Color claro para las líneas del plano
    for (float z = -10.0f; z <= 10.0f; z += 1.0f) {
        glBegin(GL_LINES);
        glVertex3f(-10.0f, -1.0f, z);
        glVertex3f(10.0f, -1.0f, z);
        glEnd();
    }
    for (float x = -10.0f; x <= 10.0f; x += 1.0f) {
        glBegin(GL_LINES);
        glVertex3f(x, -1.0f, -10.0f);
        glVertex3f(x, -1.0f, 10.0f);
        glEnd();
    }
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpia buffers
    glLoadIdentity();

    // Posición de la cámara
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotación en X
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotación en Y

    drawGrid(); // Dibuja el fondo cuadriculado
    drawCube(); // Dibuja el cubo

    glutSwapBuffers(); // Cambia buffers
}

// Función para animar
void update(int value) {
    angleX += 2.0f;
    angleY += 3.0f;
    if (angleX > 360) angleX -= 360;
    if (angleY > 360) angleY -= 360;

    glutPostRedisplay(); // Redibuja
    glutTimerFunc(16, update, 0); // Llama a update cada 16 ms
}

// Ajusta el viewport
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cubo con Fondo 3D");

    initGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
