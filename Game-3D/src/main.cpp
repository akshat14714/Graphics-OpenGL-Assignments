#include "main.h"
#include "timer.h"
#include "ball.h"
#include "boat.h"
#include "rock.h"
#include "water.h"
#include "cuboid.h"
#include "cannon.h"
#include "monster.h"
#include "booster.h"
#include "coin.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

int width;
int height;

int windZinda = 0;
int windTime = 20;
int windStart = 900;

/**************************
* Customizable functions *
**************************/

int rockFlag = 0;

char scorput[100];

float eye_x, eye_y, eye_z;
float target_x, target_y, target_z;

// Ball boat;
Boat boat;
Rock rock[20];
Water sea;

Cuboid shot;

Monster monsters[20];
Monster boss;

Booster boosters[5];

Booster gifts[5];

Cuboid barrels[20];

Cannon canon;

Coin coins[20];

float screen_zoom = 0.5, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

int boostTick = 100;
int boost = 0;

int monsterShot = 0;

int view = 0;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), -1, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // glm::vec3 eye ( 40 * sin(boat.rotation * M_PI / 180), 10, 40 * cos(boat.rotation * M_PI / 180));
    glm::vec3 eye (eye_x, eye_y, eye_z);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 10, 10);
    // glm::vec3 target (boat.position.x, 10, boat.position.z);
    glm::vec3 target (target_x, target_y, target_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    sea.draw(VP);
    boat.draw(VP);
    for (int i=0;i<20;i++) {
      rock[i].draw(VP);
    }
    for (int i=0;i<20;i++) {
      barrels[i].draw(VP);
    }
    for (int i=0;i<20;i++) {
      coins[i].draw(VP);
    }
    if (monsterShot >= 5 && boss.isDead==0) {
      boss.draw(VP);
      // boss.set_position(boat.position.x + 50, 10, boat.position.z + 50);
    }
    for (int i=0;i<20;i++) {
      if (monsters[i].isDead==0) {
        monsters[i].draw(VP);
      }
    }
    for (int i=0; i<5; i++) {
      boosters[i].draw(VP);
    }
    // if (boss.isDead == 0) {
    //   boss.draw(VP);
    // }
    if (boss.isDead == 1 && monsterShot >= 5) {
      for (int i=0; i<5; i++) {
        if (gifts[i].consumed == 0) {
          gifts[i].draw(VP);
        }
      }
    }
    shot.draw(VP);
    canon.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);

    int space = glfwGetKey(window, GLFW_KEY_SPACE);

    // int viewChange = glfwGetKey(window, GLFW_KEY_C);

    int fire = glfwGetKey(window, GLFW_KEY_F);

    int canAngd = glfwGetKey(window, GLFW_KEY_W);
    int canAngu = glfwGetKey(window, GLFW_KEY_S);

    int orth = glfwGetKey(window, GLFW_KEY_O);
    int pers = glfwGetKey(window, GLFW_KEY_P);

    if (left) {
        boat.rotation += 2;
        shot.rotation += 2;
    }
    if (right) {
        boat.rotation -= 2;
        shot.rotation += 2;
    }
    if (up) {
        boat.position.z -= boat.speed * cos(boat.rotation * M_PI / 180);
        boat.position.x -= boat.speed * sin(boat.rotation * M_PI / 180);

        canon.position.z -= boat.speed * cos(boat.rotation * M_PI / 180);
        canon.position.x -= boat.speed * sin(boat.rotation * M_PI / 180);

        if (shot.position.y == boat.position.y) {
          shot.position.z -= boat.speed * cos(boat.rotation * M_PI / 180);
          shot.position.x -= boat.speed * sin(boat.rotation * M_PI / 180);
        }
      // }
    }
    if (down) {
        // rockFlag = 0;
        boat.position.z += boat.speed * cos(boat.rotation * M_PI / 180);
        boat.position.x += boat.speed * sin(boat.rotation * M_PI / 180);

        canon.position.z += boat.speed * cos(boat.rotation * M_PI / 180);
        canon.position.x += boat.speed * sin(boat.rotation * M_PI / 180);

        if (shot.position.y == boat.position.y) {
          shot.position.z += boat.speed * cos(boat.rotation * M_PI / 180);
          shot.position.x += boat.speed * sin(boat.rotation * M_PI / 180);
        }
    }

    if (space) {
        boat.speedy = 0.3;
        canon.speedy = 0.3;
        shot.speedy = 0.3;
        shot.speedx = boat.speed * sin(boat.rotation * M_PI / 180);
        shot.speedz = boat.speed * cos(boat.rotation * M_PI / 180);
    }

    if (fire && shot.fire==0) {
        shot.rotation = boat.rotation;
        shot.speedz = 2 * cos((boat.rotation + shot.rotation) * M_PI / 180);
        shot.speedx = 2 * sin((boat.rotation + shot.rotation) * M_PI / 180);
        shot.speedy = 0.2;
        shot.tick();
        shot.fire = 1;
    }

    if (canAngd) {
        // canon.rotz = 1;
        canon.rotation -= 1;
    }

    if (canAngu) {
        // canon.rotz = 1;
        canon.rotation += 1;
    }

    if (orth) {
      reset_screen();
    }
    if (pers) {
      reshapeWindow(window, width, height);
    }
}

void tick_elements() {
    boat.tick();
    canon.tick();
    sea.tick();

    for (int i=0; i<5; i++) {
      boosters[i].tick();
    }

    for (int i=0; i<20; i++) {
      if (monsters[i].isDead == 0) {
          monsters[i].tick();
      }
    }

    for (int i=0;i<20;i++) {
      coins[i].tick();
    }

    camera_rotation_angle += 0.5;

    shot.tick();

    if(shot.position.y <= 0 && shot.fire == 1) {
        shot = Cuboid(boat.position.x, boat.position.y, boat.position.z, 1.0, 1.0, 1.0, COLOR_RED);
        shot.bomb = 1;
        shot.fire = 0;
    }

    for (int i=0;i<20;i++) {
      if (detect_collision(boat.bounding_box(), rock[i].bounding_box())) {
          boat.health -= 5;
          boat.set_position(boat.position.x, boat.position.y, boat.position.z+2);
          canon.set_position(boat.position.x, boat.position.y, boat.position.z);
          shot.set_position(boat.position.x, boat.position.y, boat.position.z);
          break;
      }
      else {
          boat.speed = 1;
      }
    }

    for (int i=0; i<20; i++) {
      if (detect_collision(shot.bounding_box(), monsters[i].bounding_box()) && shot.fire==1) {
        monsters[i].isDead = 1;
        monsterShot++;
        boat.score += 10;
        shot = Cuboid(boat.position.x, boat.position.y, boat.position.z, 1.0, 1.0, 1.0, COLOR_RED);
        shot.bomb = 1;
        shot.fire = 0;
        if (monsterShot == 5) {
            boss.set_position(boat.position.x+50, 10, boat.position.z + 50);
            boss.isDead = 0;
            boss.shots = 0;
        }
        break;
      }
    }

    for (int i=0; i<20; i++) {
      if (detect_collision(boat.bounding_box(), monsters[i].bounding_box())) {
        boat.set_position(boat.position.x, boat.position.y, boat.position.z - 30);
        canon.set_position(boat.position.x, boat.position.y, boat.position.z);
        shot.set_position(boat.position.x, boat.position.y, boat.position.z);
        boat.health -= 25;
        break;
      }
    }

    for (int i=0; i<5; i++) {
      if (detect_collision(boat.bounding_box(), boosters[i].bounding_box())) {
        int x = -200 + rand() % 400;
        int z = -200 + rand() % 500;
        int length = 4 + rand() % 4;
        int height = 4 + rand() % 4;
        int width = 4 + rand() % 4;
        boosters[i] = Booster(x, 4, z, length, height, width, COLOR_BOOSTER);
        boat.speed += 2;
        boost = 1;
      }
    }

    for (int i=0; i<5; i++) {
      if (detect_collision(boat.bounding_box(), gifts[i].bounding_box())) {
          boat.health += 10;
          boat.health = min(100, boat.health);
          gifts[i].consumed = 1;
      }
    }

    for (int i=0; i<20; i++) {
      if (detect_collision(boat.bounding_box(), barrels[i].bounding_box())) {
        barrels[i].set_position(barrels[i].position.x-2, barrels[i].position.y, barrels[i].position.z+2);
      }
    }

    if (detect_collision(shot.bounding_box(), boss.bounding_box()) && monsterShot>=5 && shot.fire == 1) {
        boss.shots ++;
        shot = Cuboid(boat.position.x, boat.position.y, boat.position.z, 1.0, 1.0, 1.0, COLOR_RED);
        shot.bomb = 1;
        shot.fire = 0;
        if (boss.shots >= 3) {
            boss.isDead = 1;
            boat.score += 100;
            for (int i=0;i<5;i++) {
              int x = boat.position.x + rand() % 30;
              // int y = boat.position.y + rand() % 30;
              int z = boat.position.z + rand() % 30;
              gifts[i].set_position(x, gifts[i].position.y, z);
            }
        }
    }

    if (detect_collision(boat.bounding_box(), boss.bounding_box()) && monsterShot==5 && boss.isDead==0) {
        boat.health -= 50;
    }

    for (int i=0; i<20; i++) {
        if (detect_collision_coin(boat.bounding_box(), coins[i].bounding_box())) {
            boat.score += 1;
            int x = -200 + rand() % 400;
            int z = -200 + rand() % 500;
            coins[i] = Coin(x, 6, z, COLOR_COIN);
        }
    }

    if (windZinda) {
      windTime -= 1;
      if (windTime <= 0) {
        windTime = 20;
        windZinda = 0;
        boat.speedx = 0;
        shot.speedx = 0.0;
        canon.speedx = 0.0;
      }
      boat.speedx += 0.3;
      shot.speedx += 0.3;
      canon.speedx += 0.3;
    }
    else {
      windStart -= 1;
      boat.speedx = 0;
      shot.speedx = 0.0;
      canon.speedx = 0.0;
      if (windStart <= 0) {
        boat.speedx = 0;
        shot.speedx = 0.0;
        canon.speedx = 0.0;
        windZinda = 1;
        windStart = 900;
      }
    }

    if (boost) {
      boostTick--;
      if (boostTick <= 0) {
        boostTick = 100;
        boost = 0;
        boat.speed = 1;
      }
      boat.speed += 2;
    }

    speed_camera();

    sprintf(scorput, "Score: %d  Health: %d", boat.score, boat.health);
    glfwSetWindowTitle(window, scorput);
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    // boat       = Ball(0, 0, COLOR_RED);
    sea = Water(0, 0, COLOR_WATER);
    boat = Boat(0, 1, COLOR_BROWN);

    for (int i=0;i<20;i++) {
      int x = -200 + rand() % 400;
      int z = -200 + rand() % 500;
      rock[i] = Rock(x, 2, z, COLOR_GRAY);
    }

    for (int i=0;i<20;i++) {
      int x = -200 + rand() % 400;
      int z = -200 + rand() % 500;
      int length = 4 + rand() % 6;
      int height = 4 + rand() % 6;
      int width = 4 + rand() % 6;
      barrels[i] = Cuboid(x, 2, z, length, width, height, COLOR_BARREL);
    }

    for (int i=0;i<20;i++) {
      int x = -200 + rand() % 400;
      int z = -200 + rand() % 500;
      coins[i] = Coin(x, 6, z, COLOR_COIN);
    }

    boss = Monster(boat.position.x+50, 10, boat.position.z+50, 20, 12, 16, COLOR_BOSS);
    boss.isDead = 1;
    boss.shots = 0;
    boss.boss = 1;

    for (int i=0;i<20;i++) {
      // if (monsters[i].isDead==0)  {
        int x = -200 + rand() % 400;
        int z = -200 + rand() % 500;
        int length = 4 + rand() % 4;
        int height = 4 + rand() % 4;
        int width = 4 + rand() % 4;
        monsters[i] = Monster(x, 6, z, length, height, width, COLOR_SLATE);
      // }
    }

    for (int i=0; i<5; i++) {
      int x = -200 + rand() % 400;
      int z = -200 + rand() % 500;
      int length = 4 + rand() % 4;
      int height = 4 + rand() % 4;
      int width = 4 + rand() % 4;
      boosters[i] = Booster(x, 4, z, length, height, width, COLOR_BOOSTER);
    }

    for (int i=0; i<5; i++) {
      int x = boat.position.x + rand() % 30;
      // int y = boat.position.y + rand() % 30;
      int z = boat.position.z + rand() % 30;
      int length = 4 + rand() % 4;
      int height = 4 + rand() % 4;
      int width = 4 + rand() % 4;
      gifts[i] = Booster(x, 4, z, length, height, width, COLOR_BLACK);
    }

    shot = Cuboid(boat.position.x, boat.position.y, boat.position.z, 1.0, 1.0, 1.0, COLOR_RED);
    shot.bomb = 1;

    canon = Cannon(boat.position.x, boat.position.y, boat.position.z, COLOR_MAG);

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
    width  = 1920;
    height = 1024;

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

            if (boat.health <= 0) {
              printf("Game Over!\n");
              printf("Score: %d\n", boat.score);
              exit(0);
            }

            // printf("%d\n", boat.score);
            // printf("%d\n", boat.health);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 <= (a.length + b.length)) &&
           (abs(a.z - b.z) * 2 <= (a.width + b.width)) &&
           a.y <= b.height;
}

bool detect_collision_coin(bounding_box_t a, bounding_box_t b) {
  return (a.x+a.length/2 > b.x && a.x-a.length/2<b.x && a.z-a.width/2<=b.z);
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    // Matrices.projection = glm::perspective(45.0f,1.0f,10.0f,150.0f);
}

void viewChange() {
    view = (view+1)%5;
    printf("%d\n", view);
}

void speed_camera() {
    if(view==0){
        // follow
        eye_x = boat.position.x + 75*sin(boat.rotation*M_PI/180.0f);
        eye_y = 40;
        eye_z = boat.position.z + 75*cos(boat.rotation*M_PI/180.0f);

        target_x = boat.position.x;
        target_y = boat.position.y;
        target_z = boat.position.z;
    }
    else if(view==1) {
        eye_x = boat.position.x+3*sin(boat.rotation*M_PI/180.0f);
        eye_y = boat.position.y+10;
        eye_z = boat.position.z+3*cos(boat.rotation*M_PI/180.0f);

        target_x = boat.position.x+10*sin(boat.rotation*M_PI/180.0f);
        target_y = boat.position.y+10;
        target_z = boat.position.z+10*cos(boat.rotation*M_PI/180.0f);
    }
    else if(view==2) {
        // tower view
        eye_x = 45;
        eye_y = 50;
        eye_z = 45;

        target_x = 45;
        target_y = 5;
        target_z = 90;
    }
    else if(view==3) {
        // top view
        eye_x = boat.position.x;
        eye_y = 100;
        eye_z = boat.position.z;

        target_x = boat.position.x+1;
        target_y = boat.position.y;
        target_z = boat.position.z;
    }
    else if(view==4) {
        // helicopter
        eye_x = boat.position.x+1;
        eye_y = 100;
        eye_z = boat.position.z;

        target_x = boat.position.x;
        target_y = boat.position.y;
        target_z = boat.position.z;
    }

}
