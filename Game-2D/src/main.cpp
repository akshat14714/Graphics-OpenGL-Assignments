#include "main.h"
#include "timer.h"
#include "ball.h"
#include "rectangle.h"
#include "lake.h"
#include "slope.h"
#include "trampoline.h"
#include "porcupine.h"
#include "magnet.h"
#include "plank.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball[20];
Ball player;

Magnet magnet;

Rectangle ground, grass;
Lake pond;
Slope planks[2];
Trampoline trampoline;
Porcupine porc;
Plank slplank[2];

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

char scorput[100];
char lives[100];

Timer t60(1.0 / 60);

// create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data, COLOR_GR, GL_FILL);
// draw3DObject(create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data, COLOR_GR, GL_FILL));

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view * glm::scale(glm::vec3(exp(camerazoom)));

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ground.draw(VP);
    grass.draw(VP);
    pond.draw(VP);
    trampoline.draw(VP);
    if (magnet.zinda) {
      magnet.draw(VP);
    }
    porc.draw(VP);
    player.draw(VP);
    for(int i=0; i<20; i++) {
      ball[i].draw(VP);
    }
    for(int i=0; i<2; i++) {
      planks[i].draw(VP);
    }
    for(int i=0; i<2; i++) {
      slplank[i].draw(VP);
    }
}

void tick_input(GLFWwindow *window) {
    int lefta  = glfwGetKey(window, GLFW_KEY_A);
    int rightd = glfwGetKey(window, GLFW_KEY_D);
    int upspace = glfwGetKey(window, GLFW_KEY_SPACE);

    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);

    int mouse_clicked = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

    if (mouse_clicked) {
      if (drag_oldx == -1 && drag_oldy == -1) {
         glfwGetCursorPos(window, &drag_oldx, &drag_oldy);
       }
       else {
         int w, h;
         double new_x, new_y;
         glfwGetCursorPos(window, &new_x, &new_y);
         glfwGetWindowSize(window, &w, &h);
         float pos_x, pos_y;
         pos_x = .7 * (new_x - drag_oldx) / (w * screen_zoom);

         player.position.x += pos_x;
       }
    }

    if (lefta) {
      player.position.x -= 0.1;
    }
    if (rightd) {
      player.position.x += 0.1;
    }
    if (upspace) {
      player.speedy = 0.1;
      player.jmp = 1;
    }

    if (left && screen_center_x - 4/screen_zoom > -6) {
        screen_center_x -= 0.07;
        reset_screen();
    }
    if (down && screen_center_y - 4/screen_zoom > -8) {
        screen_center_y -= 0.07;
        reset_screen();
    }
    if (right && screen_center_x + 4/screen_zoom < 6) {
        screen_center_x += 0.07;
        reset_screen();
    }
    if (up && screen_center_y + 4/screen_zoom < 10) {
        screen_center_y += 0.07;
        reset_screen();
    }
}

void tick_elements() {
    player.tick();
    porc.tick();

    for(int i=0;i<20;i++) {
      ball[i].tick();
    }

    for(int i=0; i<2; i++) {
      planks[i].tick();
    }

    for(int i=0; i<2; i++) {
      slplank[i].tick();
    }

    if (magnet.zinda) {
      magnet.vis -= 1;
      if (magnet.vis <= 0) {
        magnet.vis = 300;
        magnet.zinda = 0;
        player.speed = 0;
      }
      if (player.position.y<=5 && player.position.y>=3.5) {
        if (player.position.x>=-2) {
          player.speed = 0.02;
        }
        else {
          player.speed = -0.02;
        }
      }
      else {
        player.speed = 0;
      }
    }
    else {
      magnet.start -= 1;
      player.speed = 0;
      if (magnet.start <= 0) {
        player.speed = 0;
        magnet.zinda = 1;
        magnet.start = 600;
      }
    }

    for(int i=0; i<20; i++) {
      if (detect_collision_ball(player.bounding_box(), ball[i].bounding_box()) && player.position.y > ball[i].position.y && player.speedy < 0) {
          float x = -25 + rand() % 20;
          float y = rand() % 5 - 1;
          player.speedy += 0.08;
          ball[i].set_position(x, y);
          if (ball[i].colour == 1) {
            player.score += 10;
          }
          else {
            player.score += 5;
          }
      }
    }

    if (detect_collision_tramp(player.bounding_box(), trampoline.bounding_box()) && player.position.y > trampoline.position.y && player.speedy < 0) {
      player.speedy += 0.25;
    }

    if (detect_collision_porc() && player.position.y<=-1.7) {
      float x = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 0.1;
      porc.set_position(x, -2);
      player.set_position(2, 0);
      player.life -= 1;
      player.score -= 50;
    }

    for(int i=0; i<2; i++) {
      if (detect_collision_plank(player.bounding_box(), slplank[i].bounding_box()) && player.speedy < 0) {
        player.speedy += 0.2;
        float x = -25 + rand() % 20;
        float y = rand() % 5 - 1;
        slplank[i].set_position(x,y);
      }
    }

    sprintf(scorput, "Score: %d", player.score);
    glfwSetWindowTitle(window, scorput);
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ground = Rectangle(0, 0, -5, -2.5, COLOR_BROWN);
    grass = Rectangle(0, 0, -2.5, -2, COLOR_GR);
    pond = Lake(1.35, 2, -2, COLOR_BLUE);
    trampoline = Trampoline(0.5, -3, -1.25, 0.75, 0.1, COLOR_GRAY);
    magnet = Magnet(0, -2, 1, COLOR_MAG);
    porc = Porcupine(-1, -2, COLOR_PORC);
    porc.speed = -porc.speed;
    player = Ball(0.3, 0, -1.7, COLOR_PLAY);
    player.speed = 0.0;
    player.play = 1;
    player.initialy = -1.7;
    player.inwater = 0;
    player.jmp = 0;
    player.life = 3;
    player.score = 0;

    for(int i=0; i<2; i++) {
      float x = -25 + rand() % 20;
      float y = rand() % 5 - 1;
      planks[i] = Slope(x, y, 1.5, 0.1, COLOR_PLANK);
      planks[i].speed = -1 * planks[i].speed;
    }

    for(int i=0; i<20; i++) {
      int k = rand() % 2;
      float r = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 0.4;
      float x = -25 + rand() % 20;
      float y = rand() % 5 - 1;
      if (k == 1) {
        ball[i] = Ball(r, x, y, COLOR_RED);
        ball[i].colour = 1;
      }
      else {
        ball[i] = Ball(r, x, y, COLOR_SLATE);
        ball[i].colour = 2;
      }
      ball[i].speed = -1 * abs(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 0.04 + 0.01;
      ball[i].play = 0;
    }

    for(int i=0; i<2; i++) {
      float x = -25 + rand() % 20;
      float y = rand() % 5 - 1;
      float r = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 0.2 + 0.2;
      slplank[i] = Plank(x, y, r, COLOR_PLANK);
      slplank[i].speed = -1 * slplank[i].speed;
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1024;
    int height = 1024;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);

            if (player.life == 0) {
              printf("Score: %d\n", player.score);
              exit(0);
            }
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

// bool detect_collision(bounding_box_t a, bounding_box_t b) {
//     return (sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)) == (a.radius + b.radius));
//     // return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
//     //        (abs(a.y - b.y) * 2 < (a.height + b.height));
// }

bool detect_collision_ball(bounding_box_t a, bounding_box_t b) {
  return (sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)) <= (a.radius + b.radius));
}

bool detect_collision_tramp(bounding_box_t a, bounding_box_t b) {
  return (a.x<=(b.x+b.radius) && a.x>=(b.x-b.radius) && (a.y-a.radius)<=b.y);
}

int detect_collision_porc() {
  float xb = player.position.x;
  float yb = player.position.y;
  float xp = porc.position.x;
  if (xb<=(xp+0.3) && xb>=(xp-0.3) && (yb-player.radius)<=(-1.7)) {
    return 1;
  }
  return 0;
}

// bool detect_collision_slope(bounding_box_t a, bounding_box_t b) {
//   // printf("%d\n",((a.x<=(b.x+cos(M_PI/6)*(b.length)/2.0)) && (a.x>=(b.x-cos(M_PI/6)*(b.length)/2.0))));
//   return ((a.x<=(b.x+cos(M_PI/6)*(b.length)/2.0)) && (a.x>=(b.x-cos(M_PI/6)*(b.length)/2.0))
//         && (abs(a.y - b.y) <= abs(a.radius/cos(M_PI/6) + abs(a.x - b.x)*tan(M_PI/3))));
// }

// bool detect_collision_plank(bounding_box_t a, bounding_box_t b) {
//   return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
//            (abs(a.y - b.y) * 2 < (a.height + b.height));
// }

int detect_collision_plank(bounding_box_t a, bounding_box_t b) {
  if (sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)) <= 0.5*(a.radius + b.radius)) {
    return 1;
  }
  return 0;
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
