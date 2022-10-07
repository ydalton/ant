#ifndef ANT_H_
#define ANT_H_
/* COLORS */
#define BLACK 0, 0, 0
#define WHITE 1, 1, 1
#define RED 1, 0, 0
/* SIZES */
#define PIXEL_SIZE 2
#define STEP_SIZE 1
#define MAP_X 400
#define MAP_Y 400
#define FRAME_SKIP 10

/* PROGRAM DEFINES */
#define W_WIDTH MAP_X * PIXEL_SIZE
#define W_HEIGHT MAP_Y * PIXEL_SIZE
#define PROGRAM_NAME "Langton's Ant"
#define PROGRAM_LIMIT 15000

typedef struct {
    unsigned int x,y;
    unsigned char direction;
} Ant;

/* PROTOTYPES */
void init(void);
void genMap(int noise);
void drawMap(void);
void drawAnt(void);
void gameLoop(void);
void display(void);

#endif // ANT_H_
