/*
 * This program is my implementation of Langton's Ant using OpenGL.
 *
 * It is similar to the Game of Life. The rules of the game are as follows: we start with a plane of squares that
 * can either be black or white. One of these squares is known as the ant, who moves according to set of rules:
 * - if the current square is white, turn 90 degrees clockwise and flip the color of the square.
 * - if the current square is black, turn 90 degrees counter-clockwise and flip the color of the square.
 *
 * In any case the ant moves one square forward according to its current direction. The outcome of the game is
 * completely deterministic if the initial conditions (i.e. the state of the map) are known. In an empty map, at
 * around 11000 frames, the ant is stuck in an infinite loop until the program segfaults due to accessing a negative
 * index in the map array.
 *
 * I added a random background generator which as of yet does not fully work: it generates a map but will generate
 * the same map everytime.
 *
 */

#include "ant.h"
#include <GL/freeglut_std.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <stdio.h>

/* macros stop here, program starts here */

bool Map[MAP_Y][MAP_X];
Ant *pAnt;
int id;

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

/* This following function contains the logic behind Langton's Ant. */
void gameLoop(void) {
    for(int i = 0; i < FRAME_SKIP; i++) {
        if (Map[pAnt->y][pAnt->x] == 0) { /* If the current square is white: */
            Map[pAnt->y][pAnt->x] = 1;
            pAnt->direction++;
            if(pAnt->direction > 4)
                pAnt->direction -= 4;
        } else {
            Map[pAnt->y][pAnt->x] = 0;
            pAnt->direction--;
            if(pAnt->direction < 1)
                pAnt->direction += 4;
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
    for(int i = 1; i < PROGRAM_LIMIT; i++) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        drawMap();
        //drawAnt();
        gameLoop();
        printf("%d\t%d\t%d\t%d\n", pAnt->x, pAnt->y, pAnt->direction, i);
        glutSwapBuffers();
    }
    glutDestroyWindow(id);
    return;
}

int main(int argc, char *argv[]) {
    Ant a = {(MAP_X-1)/2, (MAP_Y-1)/2, 1}; /* Creates the ant. */
    pAnt = &a;
    //genMap(25); /* Uncomment this line to generate pseudorandom map for the ant. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    id = glutCreateWindow(PROGRAM_NAME);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
