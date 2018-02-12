//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int *points);
GObject detectCollision(GWindow window, GOval ball);
void collisionPossibility(GWindow window, GOval ball, GLabel scoreBoard,GRect paddle, double *velocityX, double *velocityY,int *bricks, int *points);
void borderCollision(GWindow window, GOval ball, double *velocityY, double *velocityX, int *lives);
int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel scoreBoard = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    double velocityX = 1.0, velocityY = 2.0;
    // keep playing until game over
    waitForClick();
    
    while (lives > 0 && bricks > 0)
    {  
        detectCollision(window,  ball);
        move(ball, velocityX, velocityY);
        pause(7);
        collisionPossibility( window,  ball,  scoreBoard,paddle,  &velocityX,  &velocityY, &bricks,  &points);
        borderCollision( window,  ball,  &velocityY,  &velocityX,  &lives);
        updateScoreboard(window,  scoreBoard,  &points);
        GEvent event = getNextEvent(MOUSE_EVENT);
        // if we heard one
        if (event != NULL)
        {
            
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows top cursor
                double x = getX(event) - getWidth(paddle) / 2;
                setLocation(paddle, x, 560);
                
            }
            
         }    
        // TODO
       
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    string color = "RED";
    double x= 25, y = 40;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            GRect brick = newGRect( x, y, 30, 10);
            setColor(brick, color);
            setFilled(brick, true);
            add(window, brick);
            x = x + 35;
        }
        x = 25;
        y = y + 15;
        if(i==0)
        {
            color = "ORANGE";
        }
         if(i==1)
        {
            color = "YELLOW";
        }
         if(i==2)
        {
            color = "GREEN";
        }
         if(i==3)
        {
            color = "BLUE";
        }
    }
   
    // TODO
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
   GOval ball = newGOval( 200,300,20,20);
   setColor(ball, "BLACK");
   setFilled(ball, true);
   add(window, ball);   
   return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    GRect paddle = newGRect( 180, 560, 60, 10);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel scoreBoard = newGLabel("");
    setFont(scoreBoard, "SansSerif-36");
    add(window, scoreBoard);
    char s[12];
    sprintf(s, "%i", 0);
    setLabel(scoreBoard, s);
    setColor(scoreBoard, "GRAY");
    double x = (getWidth(window) - getWidth(scoreBoard)) / 2;
    double y = (getHeight(window) - getHeight(scoreBoard)) / 2;
    setLocation(scoreBoard, x, y);
    return scoreBoard; 
}

/**    
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int *points)
{
    // update label
    char s[12];
    sprintf(s, "%i", *points);
    setLabel(label, s);
    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
void collisionPossibility(GWindow window, GOval ball, GLabel scoreBoard,GRect paddle, double *velocityX, double *velocityY,int *bricks, int *points)
{
    GObject collision = detectCollision(window, ball);
    if(collision != NULL)
    {
        if(collision == paddle)
        {
            *velocityY = -*velocityY;
        }
        else if(collision == scoreBoard)
        {
            *velocityY=*velocityY;
            *velocityX=*velocityX;
        }
        else if(strcmp(getType(collision), "GRect")==0)
        {
            *velocityY= -*velocityY;
            *points=*points+1;
            *bricks=*bricks-1;
            removeGWindow(window, collision);
        }
       
    }  
}
void borderCollision(GWindow window, GOval ball, double *velocityY, double *velocityX, int *lives)
{
        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            *velocityX = -*velocityX;
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            *velocityX = -*velocityX;
        }
        // bounce off top edge of window
        else if (getY(ball)<= 0)
        {
            *velocityY = -*velocityY;
        }
        else if (getY(ball) + getWidth(ball) >= getHeight(window))
        {
            *lives=*lives-1;
            int x = getWidth(window)/2 - (getWidth(ball)/2);
            int y = getHeight(window)/2;
            setLocation(ball, x, y);       
        }
}   

