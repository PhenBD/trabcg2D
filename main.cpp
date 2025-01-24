#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <list>
#include <iostream>
#include "headers/tinyxml2.h"
#include "headers/player.h"
#include "headers/obstacle.h"
#include "headers/enemy.h"
#include "headers/arena.h"

#define GRAVITY 0.1
#define INC_KEY 1

//Key status
int keyStatus[256];

// Window dimensions
const GLint Width = 500;
const GLint Height = 500;

//Components of the virtual world being modeled
Arena arena;
Player player;
std::list<Obstacle> obstacles;
std::list<Enemy> enemies;

using namespace tinyxml2;

void ReadSvg(const char* filename) {
    // Load the SVG file
    XMLDocument svgDoc;
    if (svgDoc.LoadFile(filename) != XML_SUCCESS) {
        std::cerr << "Erro ao carregar o arquivo SVG: " << svgDoc.ErrorStr() << std::endl;
        return;
    }

    // Get the root element
    XMLElement* root = svgDoc.RootElement();
    if (root == nullptr) {
        std::cerr << "Erro: Elemento raiz não encontrado no SVG." << std::endl;
        return;
    }

    // std::cout << "Elemento raiz: " << root->Name() << std::endl;

    // Loop through the children elements
    for (XMLElement* child = root->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
        // std::cout << "Elemento: " << child->Name() << std::endl;

        // Check if it is a rectangle
        if (strcmp(child->Name(), "rect") == 0) {
            // Get the attributes
            const char* x = child->Attribute("x");
            const char* y = child->Attribute("y");
            const char* width = child->Attribute("width");
            const char* height = child->Attribute("height");
            const char* fill = child->Attribute("fill");

            if (x != nullptr && y != nullptr && width != nullptr && height != nullptr) {
                // std::cout << "  Retângulo: x = " << x << ", y = " << y << ", width = " << width << ", height = " << height << ", fill = " << fill << std::endl;
            }

            // Check the fill color
            // If it is blue, it is the arena
            if (strcmp(child->Attribute("fill"), "blue") == 0) {
                arena = Arena(atof(x), atof(y), atof(width), atof(height));
            } // If it is black, it is an obstacle
            else if (strcmp(child->Attribute("fill"), "black") == 0) {
                Obstacle obstacle(atof(x), atof(y), atof(width), atof(height));
                obstacles.push_back(obstacle);
            }
        
        // Check if it is a circle
        } else if (strcmp(child->Name(), "circle") == 0) {
            // Get the attributes
            const char* cx = child->Attribute("cx");
            const char* cy = child->Attribute("cy");
            const char* r = child->Attribute("r");
            const char* fill = child->Attribute("fill");

            if (cx != nullptr && cy != nullptr && r != nullptr) {
                // std::cout << "  Círculo: cx = " << cx << ", cy = " << cy << ", r = " << r << ", fill = " << fill << std::endl;
            }
            
            // Check the fill color
            // If it is green, it is the player
            if (strcmp(child->Attribute("fill"), "green") == 0) {
                player = Player(atof(cx), atof(cy), atof(r));
            } // If it is red, it is an enemy
            else if (strcmp(child->Attribute("fill"), "red") == 0) {
                Enemy enemy(atof(cx), atof(cy), atof(r));
                enemies.push_back(enemy);
            }
        }
    }
}

// Mouse callback
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            keyStatus[(int)('r')] = 1;
        } else if (state == GLUT_UP) {
            keyStatus[(int)('r')] = 0;
        }
        glutPostRedisplay();
    }
}

// Keyboard callback
void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a':
        case 'A':
             keyStatus[(int)('a')] = 1; //Using keyStatus trick
             break;
        case 'd':
        case 'D':
             keyStatus[(int)('d')] = 1; //Using keyStatus trick
             break;
        case 27 :
             exit(0);
    }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus()
{
    int i;
    //Initialize keyStatus
    for(i = 0; i < 256; i++)
       keyStatus[i] = 0; 
}

void checkCollisionPlayer() {
    // Check collision with the arena
    // X axis
    if (player.getLeft() < arena.getLeft())
    {
        player.setX(arena.getLeft() + player.getWidth()/2);
    }
    else if (player.getRight() > arena.getRight()) 
    {
        player.setX(arena.getRight() - player.getWidth()/2);
    }
    // Y axis
    if (player.getTop() < arena.getTop())
    {
        player.setY(arena.getTop() + player.getHeight());
    }
    else if (player.getBottom() > arena.getBottom()) 
    {
        player.setY(arena.getBottom());
    }

    // // Check collision with obstacles
    // for (Obstacle obs : obstacles) {
    //     // X axis
    //     if (player.getX() - (player.getWidth()/2) < obs.getX() + (obs.getWidth()/2))
    //     {
    //         player.setX(obs.getX() + obs.getWidth() + player.getWidth()/2);
    //     }
    //     else if (player.getX() + (player.getWidth()/2) > obs.getX() + (obs.getWidth()/2)) 
    //     {
    //         player.setX(obs.getX() - player.getWidth()/2);
    //     }
    // }

    // // Check collision with enemies
    // for (Enemy enemy : enemies) {

    // }
}

void updatePlayer(GLdouble timeDiff) {
    // Gravity
    player.moveY(GRAVITY * timeDiff);
    checkCollisionPlayer();

    // Treat keyPress
    if(keyStatus[(int)('a')])
    {
        player.moveX(-player.getWalkSpeed() * timeDiff);
        checkCollisionPlayer();
    }
    if(keyStatus[(int)('d')])
    {
        player.moveX(player.getWalkSpeed() * timeDiff);
        checkCollisionPlayer();
    }

    // Treat mouse click
    if (keyStatus[(int)('r')])
    {
        player.moveY(-player.getJumpSpeed() * timeDiff);
    }
}

void idle(void)
{
    static GLdouble previousTime = 0;
    GLdouble currentTime;
    GLdouble timeDiference;
    
    // Elapsed time from the initiation of the game.
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDiference = currentTime - previousTime; // Elapsed time from the previous frame.
    previousTime = currentTime; //Update previous time

    updatePlayer(timeDiference);
    
    glutPostRedisplay();
}

// Render function
void renderScene(void) {
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);

    // Configure the camera
    GLfloat eyeX = player.getX() - arena.getHeight()/2; // Camera follows the player on the X axis
    GLfloat eyeY = arena.getY(); // Camera fixed at the middle of the height of the arena
    GLfloat eyeZ = 1.0f; // Camera height
    GLfloat centerX = player.getX() - arena.getHeight()/2; // Observation point fixed at the X axis of the player
    GLfloat centerY = arena.getY(); // Observation point fixed at the middle of the height of the arena
    GLfloat centerZ = 0.0f;
    GLfloat upX = 0.0f;
    GLfloat upY = 1.0f;
    GLfloat upZ = 0.0f;

    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

    // Draw elements
    arena.draw();
    player.draw();
    for (Obstacle obs : obstacles) {
        obs.draw();
    }
    for (Enemy enemy : enemies) {
        enemy.draw();
    }

    glutSwapBuffers(); // Draw the new frame of the game.
}

// Função de inicialização
void init(const char* arenaSVGFilename) {
    ResetKeyStatus();
    ReadSvg(arenaSVGFilename);

    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black, no opacity(alpha).
 
    glMatrixMode(GL_PROJECTION); // Select the projection matrix    
    glOrtho(0,     // X coordinate of left edge             
            arena.getHeight(),     // X coordinate of right edge            
            arena.getHeight(),     // Y coordinate of bottom edge             
            0,     // Y coordinate of top edge             
            -1,     // Z coordinate of the “near” plane            
            1);    // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW); // Select the projection matrix    
    glLoadIdentity();
}

int main(int argc, char** argv) {
    // Check if the SVG file was passed as an argument.
    if (argc < 2) {
        std::cerr << "Not enough arguments" << std::endl;
        return 1;
    }

    // Get the SVG filename.
    const char* arenaSVGFilename = argv[1];

    // Initialize openGL with Double buffer and RGB color without transparency.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 
    // Create the window.
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(750,250);
    glutCreateWindow("Trabalho CG 2D");

    // Define callbacks.

    // Display callback
    glutDisplayFunc(renderScene);
    glutIdleFunc(idle);

    // Keyboard callbacks
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyup);

    // Mouse callback
    glutMouseFunc(mouseClick);
    
    init(arenaSVGFilename);
 
    glutMainLoop();
    return 0;
}
