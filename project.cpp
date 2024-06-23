#include <GL/glut.h>

int windowWidth = 800;
int windowHeight = 600;

// Maze dimensions
int mazeWidth = 10;
int mazeHeight = 10;  // Updated to match the maze size
int cellSize;

int startCellX = 0;
int startCellY = 0;
int endCellX = mazeWidth - 1;
int endCellY = mazeHeight - 1;

int playerX = startCellX;
int playerY = startCellY;

bool maze[10][10] = {  // Updated maze size to 10x10
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 1, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 0, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void drawMaze() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (int y = 0; y < mazeHeight; y++) {
        for (int x = 0; x < mazeWidth; x++) {
            if (maze[y][x]) {
                glColor3f(0.0, 0.0, 0.0); // Walls
            } else {
                glColor3f(1.0, 1.0, 1.0); // Open path
            }
            glBegin(GL_QUADS);
            glVertex2i(x * cellSize, y * cellSize);
            glVertex2i((x + 1) * cellSize, y * cellSize);
            glVertex2i((x + 1) * cellSize, (y + 1) * cellSize);
            glVertex2i(x * cellSize, (y + 1) * cellSize);
            glEnd();
        }
    }

    // Player
    glColor3f(0.0, 0.0, 1.0); // Blue
    glBegin(GL_QUADS);
    glVertex2i(playerX * cellSize, playerY * cellSize);
    glVertex2i((playerX + 1) * cellSize, playerY * cellSize);
    glVertex2i((playerX + 1) * cellSize, (playerY + 1) * cellSize);
    glVertex2i(playerX * cellSize, (playerY + 1) * cellSize);
    glEnd();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // Move up
            if (playerY < mazeHeight - 1 && !maze[playerY + 1][playerX])
                playerY++;
            break;
        case 's': // Move down
            if (playerY > 0 && !maze[playerY - 1][playerX])
                playerY--;
            break;
        case 'a': // Move left
            if (playerX > 0 && !maze[playerY][playerX - 1])
                playerX--;
            break;
        case 'd': // Move right
            if (playerX < mazeWidth - 1 && !maze[playerY][playerX + 1])
                playerX++;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, windowWidth, windowHeight);
    glLoadIdentity();
    glOrtho(0, windowWidth, 0, windowHeight, -1, 1);
    cellSize = windowWidth / mazeWidth;
}

int main(int argc, char** argv) {
    cellSize = windowWidth / mazeWidth;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Maze Game");

    glutDisplayFunc(drawMaze);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
