#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define PLANE_VIEW 1
#define TOP_VIEW 2 
#define TOWER_VIEW 3
#define FOLLOW_VIEW 4 
#define HELICOPTER_VIEW 5

#define VOLCANO 1
#define ENEMY_CANNON 2
#define RING 3

struct color_t {
    int r;
    int g;
    int b;
};

// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
void       draw3DObject(struct VAO *vao);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);

// Types
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int    NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint    MatrixID;
};

extern GLMatrices Matrices;
extern GLMatrices Matrices_Ortho;

// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

struct bounding_box_t {
    glm::vec3 position;
    float length;
    float width;
    float height;
};

bool detect_collision(bounding_box_t a, bounding_box_t b);

extern glm::vec3 eye, target, up;
extern float screen_zoom, screen_center_x, screen_center_y;
extern float NEAR_CAMERA, FAR_CAMERA; 
void reset_screen();

// ---- Colors ----
extern const color_t COLOR_BLACK;
extern const color_t COLOR_WHITE;
extern const color_t COLOR_BROWN;
extern const color_t COLOR_GRAY;
extern const color_t COLOR_RED;
extern const color_t COLOR_PINK; 
extern const color_t COLOR_ORANGE_RED;
extern const color_t COLOR_DARK_RED;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLUE;
extern const color_t COLOR_PURPLE;
extern const color_t COLOR_LIGHT_BLACK;
extern const color_t COLOR_TEAL;
extern const color_t COLOR_YELLOW;
extern const color_t COLOR_WOOD;
extern const color_t COLOR_SKIN;
extern const color_t COLOR_GOLDEN;
extern const color_t COLOR_CREAM;
extern const color_t COLOR_FIRE;
extern const color_t COLOR_DARK_FIRE;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_BACKDROP;
extern const color_t COLOR_WATER;
extern const color_t COLOR_SKY;

extern float nowTime;
extern float pxpos,pypos; 
extern const int WIDTH, HEIGHT;
extern double cam_heli_x, cam_heli_y;
extern int ticks;

extern float CANNON_DAMAGE;
extern float CANNON_BALL_DAMAGE;
extern float VOLCANO_DAMAGE;
extern int PARACHUTE_SCORE;
extern int CANNON_SCORE;
extern int RING_SCORE;
extern int FUEL_BARREL_SCORE;
extern int HEALTH_SCORE;
extern int CHECKPOINT_SCORE;
extern int CANNON_BALL_HIT;

extern const int BODY_EDGES;
extern const float GROUND_HEIGHT, GROUND_WIDTH, GROUND_LENGTH;

extern int no_volcano;
extern const int TOTAL_VOLCANO;
extern const float DIST_VOLCANO;

extern const float DIST_RING;
extern const float HEIGHT_RING_1;
extern const float HEIGHT_RING_2;
extern const float HEIGHT_RING_3;
extern const int TOTAL_RING;
extern int no_ring;

extern const float DIST_PARACHUTE;
extern const float HEIGHT_PARACHUTE_1;
extern const float HEIGHT_PARACHUTE_2;
extern const float HEIGHT_PARACHUTE_3;
extern const int TOTAL_PARACHUTE;
extern int no_parachute;

extern int no_cannon;
extern const int TOTAL_CANNON;
extern const float DIST_CANNON;
extern const float CANNON_HEIGHT;
extern const float CANNON_WIDTH;
extern const float CANNON_LENGTH;
extern const float CANNON_RANGE;

extern const float DIST_FUEL_REFILL;
extern const float QUANTITY_FUEL_REFILL;
extern const int TOTAL_FUEL_REFILL;
extern int no_fuel_refill;

extern int no_health_refill;
extern const int TOTAL_HEALTH_REFILL;
extern const float DIST_HEALTH_REFILL;
extern const float QUANTITY_HEALTH_REFILL;

extern const float MIN_ALT;
extern const float MAX_ALT;

extern const float MIN_VEL;
extern const float MAX_VEL;

extern const float MIN_HEALTH;
extern const float MAX_HEALTH;

extern const float MIN_FUEL;
extern const float MAX_FUEL;

extern float CHECKPOINT_HEIGHT;

extern int no_missile;
extern float lastTime_missile;

extern int no_bomb;
extern float lastTime_bomb;

extern int no_cannon_ball;
extern float lastTime_cannon_ball;
extern float lastTime_cannon_touch;

extern glm::vec3 plane_position, plane_velocity;
extern glm::vec3 up_direction;
extern glm::vec3 forward_direction;
extern float remaining_fuel;
extern float remaining_health;

extern glm::vec3 dashboard_direction;
extern int camera_view;
extern bool jet_on;
extern bool checkpoint_taken;
extern int checkpoint_num;

#endif
