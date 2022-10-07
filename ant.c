#include "ant.h"
#include <GL/glut.h>
#include <stdbool.h>
#include <stdio.h>

/* macros stop here, program starts here */

bool Map[MAP_Y][MAP_X];
Ant *pAnt;


void init(void) {
    glClearColor(WHITE, 0);
    gluOrtho2D(0, W_WIDTH, W_HEIGHT, 0);
}

void genMap(int noise) {
    int num;
    for(int i = 0; i < MAP_Y; i++) {
        for(int j = 0; j < MAP_X; j++) {
            num = rand();
            if(num % noise == 1) {
                Map[i][j] = 1;
            } else {
                Map[i][j] = 0;
            }
        }
    }
}

void drawMap() {
    for(int i = 0; i < MAP_Y; i++) {
        for(int j = 0; j < MAP_X; j++) {
            if(Map[i][j] == 0) {
                glColor3f(WHITE);
            } else {
                glColor3f(BLACK);
            }
            glPointSize(PIXEL_SIZE);
            glBegin(GL_POINTS);
            glVertex2i(j * PIXEL_SIZE,  i * PIXEL_SIZE);
            glEnd();
        }
    }
}

void drawAnt() {
    glColor3f(RED);
    glPointSize(PIXEL_SIZE);
    glBegin(GL_POINTS);
    glVertex2i(pAnt->x * PIXEL_SIZE, pAnt->y * PIXEL_SIZE);
    glEnd();
}

void gameLoop(void) {
    for(int i = 0; i < FRAME_SKIP; i++) {
        if (Map[pAnt->y][pAnt->x] == 0) {
            Map[pAnt->y][pAnt->x] = 1;
            pAnt->direction++;
            if(pAnt->direction > 4)
                pAnt->direction = 1;
        } else {
            Map[pAnt->y][pAnt->x] = 0;
            pAnt->direction--;
            if(pAnt->direction < 1)
                pAnt->direction = 4;
        }
        switch(pAnt->direction) {
            case 1:
                pAnt->y -= STEP_SIZE;
                break;
            case 2:
                pAnt->x += STEP_SIZE;
                break;
            case 3:
                pAnt->y += STEP_SIZE;
                break;
            case 4:
                pAnt->x -= STEP_SIZE;
                break;
            default:
                break;
        }
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMap();
    printf("%d\t%d\t%d\t%d\n", pAnt->x, pAnt->y, pAnt->direction, 0);
    glutSwapBuffers();
    for(int i = 1; i < PROGRAM_LIMIT; i++) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        drawMap();
        //drawAnt();
        gameLoop();
        printf("%d\t%d\t%d\t%d\n", pAnt->x, pAnt->y, pAnt->direction, i);
        glutSwapBuffers();
    }
}

int main(int argc, char *argv[]) {
    Ant a = {(MAP_X-1)/2, (MAP_Y-1)/2, 1}; /* Creates the ant. */
    pAnt = &a;
    //genMap(50);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    glutCreateWindow(PROGRAM_NAME);
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
