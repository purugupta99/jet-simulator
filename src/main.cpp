#include <unistd.h>
#include <iostream>
#include "main.h"
#include "timer.h"
#include "jet.h"
#include "ground.h"
#include "volcano.h"
#include "weapon.h"
#include "ring.h"
#include "checkpoint.h"
#include "parachute.h"
#include "dashboard.h"
#include "powerup.h"
#include "enemy_cannon.h"
#include "segmentdisplay.h"

using namespace std;

GLMatrices Matrices;
GLMatrices Matrices_Ortho;
GLuint     programID;
GLFWwindow *window;

float CANNON_DAMAGE = -10.0f;
float CANNON_BALL_DAMAGE = -5.0f;
float VOLACANO_DAMAGE = -MAX_HEALTH;
int PARACHUTE_SCORE = 30;
int CANNON_SCORE = 50;
int RING_SCORE = 10;
int CHECKPOINT_SCORE = 20;
int FUEL_BARREL_SCORE = 10;
int HEALTH_SCORE = 10;
int CANNON_BALL_HIT = -10;

const int BODY_EDGES = 50;
const float GROUND_HEIGHT = 10.0f, GROUND_WIDTH = 2000.0f, GROUND_LENGTH = 2000.0f;

const float DIST_VOLCANO = 800.0f;
const int TOTAL_VOLCANO = 25;
int no_volcano = 0;

const float QUANTITY_FUEL_REFILL = 25.0f;
const float DIST_FUEL_REFILL = 1000.0f;
const int TOTAL_FUEL_REFILL = 16;
int no_fuel_refill = 0;

int no_health_refill = 0;
const int TOTAL_HEALTH_REFILL = 16;
const float DIST_HEALTH_REFILL = 1000.0f;
const float QUANTITY_HEALTH_REFILL = 25.0f;

const float DIST_RING = 400.0f;
const float HEIGHT_RING_1 = 75.0f;
const float HEIGHT_RING_2 = 100.0f;
const float HEIGHT_RING_3 = 125.0f;
const int TOTAL_RING = 100;
int no_ring = 0;

const float DIST_PARACHUTE = 400.0f;
const float HEIGHT_PARACHUTE_1 = 75.0f;
const float HEIGHT_PARACHUTE_2 = 100.0f;
const float HEIGHT_PARACHUTE_3 = 125.0f;
const int TOTAL_PARACHUTE = 10;
int no_parachute = 0;

float CHECKPOINT_HEIGHT = 100.0f;

const float CANNON_HEIGHT = 20.0f;
const float CANNON_WIDTH = 15.0f;
const float CANNON_LENGTH = 15.0f;
const float DIST_CANNON = 400.0f;
const int TOTAL_CANNON = 81;
const float CANNON_RANGE = 1000.0f;
int no_cannon = 0;

const float MIN_ALT = GROUND_HEIGHT + 10.0f;
const float MAX_ALT = FAR_CAMERA;

const float MIN_VEL = 0.0f;
const float MAX_VEL = 20.0f;

const float MAX_FUEL = 100.0f;
const float MIN_FUEL = 0.0f;

const float MAX_HEALTH = 100.0f;
const float MIN_HEALTH = 0.0f;

int no_missile = 0;
float lastTime_missile = -1.0f;

int no_bomb = 0;
float lastTime_bomb = -1.0f;

int no_cannon_ball = 0;
float lastTime_cannon_ball = -1.0f;

float lastTime_cannon_touch = -1.0f;

float pxpos,pypos;
double cam_heli_x = 0, cam_heli_y = 0;
int ticks = 0;

const int WIDTH  = 600;
const int HEIGHT = 600;
/**************************
* Customizable functions *
**************************/
glm::vec3 eye, target, up;
float NEAR_CAMERA = 0.1f;
float FAR_CAMERA = 5000.0f;
float nowTime = 0.0f;

Jet fighter_jet;
Ground ground;
Checkpoint arrow;
Dashboard dashboard;
Segmentdisplay score;

vector<Volcano> volcano_vector;
vector<Cannon> cannon_vector;
vector<Cannon_Ball> cannon_ball_vector;
vector<Missile> missile_vector;
vector<Bomb> bomb_vector;
vector<Ring> ring_vector;
vector<Parachute> parachute_vector;
vector<Fuel_Refill> fuel_refill_vector;
vector<Health_Refill> health_refill_vector;
glm::vec3 plane_position, plane_velocity, forward_direction, up_direction, dashboard_direction;
float remaining_fuel, remaining_health;
bool jet_on = false;
bool checkpoint_taken = true;
int checkpoint_num;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int camera_view = PLANE_VIEW;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    glm::mat4 rotation = fighter_jet.get_rotation();
    if(camera_view == PLANE_VIEW){
        eye = glm::vec3( plane_position.x + 4*forward_direction.x, plane_position.y + 4*forward_direction.y, plane_position.z  + 4*forward_direction.z);
        target = glm::vec3(plane_position.x + 50*forward_direction.x, plane_position.y+50*forward_direction.y, plane_position.z  + 50*forward_direction.z);
        up = glm::vec3(up_direction.x, up_direction.y, up_direction.z);
        // target = glm::vec3(0, 23, 100);
        // eye = glm::vec3(0, 27, -10);
        // up = glm::vec3(0,1,0);
    }
    if(camera_view == TOP_VIEW){
        eye = glm::vec3( plane_position.x , plane_position.y + 10, plane_position.z );
        target = glm::vec3( plane_position.x , plane_position.y - 5, plane_position.z );
        up = glm::vec3(forward_direction.x, forward_direction.y, forward_direction.z);
    }
    if(camera_view == TOWER_VIEW){
        eye = glm::vec3( plane_position.x, plane_position.y + 20, plane_position.z - 10);
        target = glm::vec3(plane_position.x, plane_position.y, plane_position.z);
        up = glm::vec3(0, 1, 0);
    }
    if(camera_view == FOLLOW_VIEW){

        eye = glm::vec3( plane_position.x - 8*forward_direction.x, plane_position.y + 8, plane_position.z - 8*forward_direction.z);
        target = glm::vec3(plane_position.x, plane_position.y, plane_position.z);
        up = glm::vec3(0,1,0);
    }
    if(camera_view == HELICOPTER_VIEW){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
    
        // if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) 

        cam_heli_x += + (xpos - pxpos) * 90 / WIDTH;
        cam_heli_y -= + (ypos - pypos) * 90 / HEIGHT;
        pxpos = xpos;
        pypos = ypos;
        target = glm::vec3(plane_position.x, plane_position.y, plane_position.z);

        // 10 + (20-camera_zoom/5)*cos(camera_look_x*M_PI/180.0f)*sin(camera_look_y*M_PI/180.0f)
        // (20-camera_zoom/5)*cos(camera_look_y*M_PI/180.0f)
        // 10 + (20-camera_zoom/5)*sin(camera_look_x*M_PI/180.0f)*sin(camera_look_y*M_PI/180.0f)
        float eye_x = plane_position.x + (20-10*screen_zoom)*cos(cam_heli_x*M_PI/180.0f)*sin(cam_heli_y*M_PI/180.0f);
        float eye_y = plane_position.y + (20-10*screen_zoom)*cos(cam_heli_y*M_PI/180.0f);
        float eye_z = plane_position.z + (20-10*screen_zoom)*sin(cam_heli_x*M_PI/180.0f)*sin(cam_heli_y*M_PI/180.0f);

        eye = glm::vec3(eye_x,eye_y,eye_z);
        up = glm::vec3(0,1,0);        
    }

    
    dashboard.tick();
    // cout << fighter_jet.get_score() << "\n";
    // score.update(fighter_jet.get_score());


    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    Matrices_Ortho.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP_Ortho = Matrices_Ortho.projection * Matrices_Ortho.view;


    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    glm::mat4 MVP_Ortho;

    // Scene render
    fighter_jet.draw(VP);
    ground.draw(VP);
    arrow.draw(VP);
    dashboard.draw(VP);
    dashboard.draw_map(VP);
    score.draw(VP_Ortho);
    dashboard.draw_needle(VP);
    dashboard.draw_compass_needle(VP);
    dashboard.free_memory();

    for(int i=0;i<no_volcano;i++)
    {
        volcano_vector[i].draw(VP);
    }

    for(int i=0;i<no_cannon;i++)
    {
        if(cannon_vector[i].get_visibility()){
            cannon_vector[i].draw(VP); 
            cannon_vector[i].draw_gun(VP); 
        }
    }

    for(int i=0;i<no_cannon_ball;i++)
    {
        if(cannon_ball_vector[i].get_visibility()){
            cannon_ball_vector[i].draw(VP); 
        }
    }

    for(int i=0;i<no_missile;i++)
    {
        missile_vector[i].draw(VP);
    }

    for(int i=0;i<no_bomb;i++)
    {
        bomb_vector[i].draw(VP);
    }

    for(int i=0;i<no_ring;i++)
    {
        ring_vector[i].draw(VP);
    }

    for(int i=0;i<no_parachute;i++)
    {
        parachute_vector[i].draw(VP);
    }

    for(int i=0;i<no_fuel_refill;i++)
    {
        fuel_refill_vector[i].draw(VP);
    }

    for(int i=0;i<no_health_refill;i++)
    {
        health_refill_vector[i].draw(VP);
    }
}

void tick_input(GLFWwindow *window) {
    glm::mat4 rotation = fighter_jet.get_rotation();
    bool time_missile = (nowTime - lastTime_missile > 1.0f);    
    bool time_bomb = (nowTime - lastTime_bomb > 1.0f);    

    int forward = glfwGetKey(window, GLFW_KEY_W);
    int backward = glfwGetKey(window, GLFW_KEY_S);
    int missile = glfwGetKey(window, GLFW_KEY_M);
    int bomb = glfwGetKey(window, GLFW_KEY_B);
    int altitude_inc = glfwGetKey(window, GLFW_KEY_G);
    int altitude_dec = glfwGetKey(window, GLFW_KEY_H);
    int rotate_right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int rotate_left = glfwGetKey(window, GLFW_KEY_LEFT);
    int tilt_right = glfwGetKey(window, GLFW_KEY_D);
    int tilt_left = glfwGetKey(window, GLFW_KEY_A);
    int nose_up = glfwGetKey(window, GLFW_KEY_UP);
    int nose_down = glfwGetKey(window, GLFW_KEY_DOWN);
    int plane_view = glfwGetKey(window, GLFW_KEY_1);
    int top_view = glfwGetKey(window, GLFW_KEY_2);
    int tower_view = glfwGetKey(window, GLFW_KEY_3);
    int follow_view = glfwGetKey(window, GLFW_KEY_4);
    int helicopter_view = glfwGetKey(window, GLFW_KEY_5);

    // PLANE_VIEW = TOP_VIEW = TOWER_VIEW = FOLLOW_VIEW = HELICOPTER_VIEW = false;
    if(plane_view){
        camera_view = PLANE_VIEW;
    }
    if(top_view){
        camera_view = TOP_VIEW;
    }
    if (tower_view) {
        camera_view = TOWER_VIEW;
    }
    if(follow_view){
        camera_view = FOLLOW_VIEW;
    }
    if(helicopter_view){
        camera_view = HELICOPTER_VIEW;
    }

    if(forward){
        jet_on = true;
        fighter_jet.accelerate();
    }else if(backward){
        jet_on = false;
        fighter_jet.decelerate();
    }else{
        jet_on = false;
        fighter_jet.slow_down();
    }

    if(altitude_inc){
        fighter_jet.altitude_gain();
    }

    if(altitude_dec){
        fighter_jet.altitude_lose();
    }

    // if(backward){
    //     fighter_jet.decelerate();
    // }else{
    //     fighter_jet.slow_down();
    // }

    if(rotate_right){
        fighter_jet.rotate_right();
    }
    if(rotate_left){
        fighter_jet.rotate_left();
    }
    if(tilt_right){
        fighter_jet.tilt_right();
    }
    if(tilt_left){
        fighter_jet.tilt_left();
    }
    if(nose_up){
        fighter_jet.nose_up();
    }
    if(nose_down){
        fighter_jet.nose_down();
    }
    if((missile || glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) && time_missile){
        system("aplay ../sounds/missile.wav &");
        missile_vector.push_back(Missile(plane_position.x,plane_position.y,plane_position.z,rotation,COLOR_GRAY));
        no_missile++;
        lastTime_missile = nowTime;
    }

    if((bomb || glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) && time_bomb){
        bomb_vector.push_back(Bomb(plane_position.x,plane_position.y,plane_position.z,plane_velocity.z,COLOR_BLACK));
        no_bomb++;
        lastTime_bomb = nowTime;
    }
}

void tick_elements() {
    nowTime = glfwGetTime();    
    fighter_jet.tick();
    ground.tick();
    arrow.tick(ticks);
    score.update(fighter_jet.get_score());


    for(int i=0;i<no_missile;i++)
    {
        missile_vector[i].tick();

        if(glm::distance(plane_position,missile_vector[i].get_position()) > FAR_CAMERA){
            missile_vector.erase(missile_vector.begin()+i);
            no_missile--;
        }
    }

    for(int i=0;i<no_bomb;i++)
    {
        bomb_vector[i].tick();

        if(glm::distance(plane_position,bomb_vector[i].get_position()) > FAR_CAMERA){
            bomb_vector.erase(bomb_vector.begin()+i);
            no_bomb--;
        }
    }

    for(int i=0;i<no_fuel_refill;i++)
    {
        fuel_refill_vector[i].tick(ticks);
    }

    for(int i=0;i<no_health_refill;i++)
    {
        health_refill_vector[i].tick(ticks);
    }

    for(int i=0;i<no_ring;i++)
    {
        ring_vector[i].tick();
    }

    for(int i=0;i<no_parachute;i++)
    {
        if(parachute_vector[i].get_position().y < GROUND_HEIGHT){
            parachute_vector.erase(parachute_vector.begin()+i);
            no_parachute--;
        }
        parachute_vector[i].tick();
    }


    for(int i=0;i<no_cannon_ball;i++)
    {
        cannon_ball_vector[i].tick();

        if(glm::distance(plane_position,cannon_ball_vector[i].get_position()) > FAR_CAMERA){
            cannon_ball_vector.erase(cannon_ball_vector.begin()+i);
            no_cannon_ball--;
        }
    }

    for(int i=0;i<no_volcano;i++)
    {
        // cout << barry.get_box().x << " " << coin_vector[i].get_box().x << "\n";
        bool collision = detect_collision(fighter_jet.get_box(),volcano_vector[i].get_box());
        if(volcano_vector[i].get_visibility() && collision)
        {
            fighter_jet.enemy_hit(VOLACANO_DAMAGE);
            // cout << collision << " " << i << "\n";
        }
        else
        {
            // cout << "no collision" << "\n";
        }
        
    }

    for(int i=0;i<no_ring;i++)
    {
        // cout << barry.get_box().x << " " << coin_vector[i].get_box().x << "\n";
        bool collision = detect_collision(fighter_jet.get_box(),ring_vector[i].get_box());
        if(ring_vector[i].get_visibility() && collision)
        {
            // cout << collision << " " << i << "\n";
            fighter_jet.inc_score(RING_SCORE);
            system("aplay ../sounds/ring.wav &");
            ring_vector.erase(ring_vector.begin() + i);
        }
        else
        {
            // cout << "no collision" << "\n";
        }
        
    }

    for(int i=0;i<no_cannon;i++)
    {
        bool time_cannon = (nowTime - lastTime_cannon_touch > 2.0f);
        // cout << barry.get_box().x << " " << coin_vector[i].get_box().x << "\n";
        bool collision = detect_collision(fighter_jet.get_box(),cannon_vector[i].get_box());
        if(cannon_vector[i].get_visibility() && collision & time_cannon)
        {
            fighter_jet.enemy_hit(CANNON_DAMAGE);
            lastTime_cannon_touch = nowTime;
            // cout << collision << " " << i << "\n";
        }
        else
        {
            // cout << "no collision" << "\n";
        }
        
    }

    for(int i=0;i<no_fuel_refill;i++)
    {
        // cout << barry.get_box().x << " " << coin_vector[i].get_box().x << "\n";
        bool collision = detect_collision(fighter_jet.get_box(),fuel_refill_vector[i].get_box());
        if( collision)
        {
            // cout << collision << " " << i << "\n";
            fighter_jet.inc_score(FUEL_BARREL_SCORE);
            fighter_jet.fuel_received();
            system("aplay ../sounds/fuel.wav &");
            fuel_refill_vector.erase(fuel_refill_vector.begin() + i);
            no_fuel_refill--;
        }
        else
        {
            // cout << "no collision" << "\n";
        }
        
    }

    for(int i=0;i<no_health_refill;i++)
    {
        // cout << barry.get_box().x << " " << coin_vector[i].get_box().x << "\n";
        bool collision = detect_collision(fighter_jet.get_box(),health_refill_vector[i].get_box());
        if(collision)
        {
            // cout << collision << " " << i << "\n";
            fighter_jet.inc_score(HEALTH_SCORE);
            fighter_jet.health_received();
            system("aplay ../sounds/health.wav &");
            health_refill_vector.erase(health_refill_vector.begin() + i);
            no_health_refill--;
        }
        else
        {
            // cout << "no collision" << "\n";
        }
        
    }

    for(int i=0;i<no_cannon_ball;i++)
    {
        // cout << barry.get_box().x << " " << coin_vector[i].get_box().x << "\n";
        bool collision = detect_collision(fighter_jet.get_box(),cannon_ball_vector[i].get_box());
        if(cannon_ball_vector[i].get_visibility() && collision)
        {
            fighter_jet.inc_score(CANNON_BALL_HIT);
            fighter_jet.enemy_hit(CANNON_BALL_DAMAGE);
            system("aplay ../sounds/cannon_hit.wav &");
            cannon_ball_vector[i].destroyed();
            // cout << collision << " " << i << "\n";
        }
        else
        {
            // cout << "no collision" << "\n";
        }
        
    }

    // for(int i=0;i<no_bomb;i++){
    //     for(int j=0;j<no_cannon;j++){
    //         bool collision = detect_collision(bomb_vector[i].get_box(),cannon_vector[j].get_box());
    //         if(cannon_vector[j].get_visibility() && collision){
    //             cannon_vector.erase(cannon_vector.begin() + j);
    //             no_cannon--;
    //         }
    //     }
    // }

    // for(int i=0;i<no_missile;i++){
    //     for(int j=0;j<no_cannon;j++){
    //         bool collision = detect_collision(missile_vector[i].get_box(),cannon_vector[j].get_box());
    //         if(cannon_vector[j].get_visibility() && collision){
    //             cannon_vector.erase(cannon_vector.begin() + j);
    //             no_cannon--;
    //         }
    //     }
    // }

        
        // cout << "checkpoint = " << checkpoint_num << " no_cannon = " << no_cannon <<  "\n";

    if(checkpoint_taken == true && no_cannon>0){
        // fighter_jet.inc_score(CHECKPOINT_SCORE);
        vector<pair<int, pair <float,float> > >locations;

        for(int i=0;i<no_volcano;i++){
            glm::vec3 position = volcano_vector[i].get_position();
            locations.push_back(make_pair(VOLCANO,make_pair(position.x,position.z)));
        }

        for(int i=0;i<no_cannon;i++){
            glm::vec3 position = cannon_vector[i].get_position();
            locations.push_back(make_pair(ENEMY_CANNON,make_pair(position.x,position.z)));
        }

        // cout << locations.size() << "\n";
        dashboard.update_map(locations);

        checkpoint_taken = false;
        checkpoint_num = rand() % no_cannon;
        glm::vec3 cannon_position = cannon_vector[checkpoint_num].get_position();
        cannon_vector[checkpoint_num].make_visible();
        arrow = Checkpoint(cannon_position.x,CHECKPOINT_HEIGHT,cannon_position.z,COLOR_DARK_RED);
    }

    int time_cannon_ball = (nowTime - lastTime_cannon_ball > 2.0f);    
    
    if(checkpoint_taken == false){
        bool in_range = (glm::distance(plane_position, cannon_vector[checkpoint_num].get_position()) < CANNON_RANGE);
        if(time_cannon_ball && in_range){
            glm::vec3 cannon_position = cannon_vector[checkpoint_num].get_position();
            cannon_ball_vector.push_back(Cannon_Ball(cannon_position.x,cannon_position.y,cannon_position.z,cannon_vector[checkpoint_num].get_forward(),COLOR_BLACK));
            // system("aplay ../sounds/cannon.wav &");            
            no_cannon_ball++;
            lastTime_cannon_ball = nowTime;
        }

        for(int i=0;i<no_missile;i++){
            bool collision = detect_collision(missile_vector[i].get_box(),cannon_vector[checkpoint_num].get_box());
            if(cannon_vector[checkpoint_num].get_visibility() && collision){
                cannon_vector.erase(cannon_vector.begin() + checkpoint_num);
                checkpoint_taken = true;
                system("aplay ../sounds/explosion.wav &");
                no_cannon--;
                fighter_jet.inc_score(CANNON_SCORE);
            }
        }

        for(int i=0;i<no_bomb;i++){
            bool collision = detect_collision(bomb_vector[i].get_box(),cannon_vector[checkpoint_num].get_box());
            if(cannon_vector[checkpoint_num].get_visibility() && collision){
                cannon_vector.erase(cannon_vector.begin() + checkpoint_num);
                checkpoint_taken = true;
                system("aplay ../sounds/explosion.wav &");
                no_cannon--;
                fighter_jet.inc_score(CANNON_SCORE);
            }
        }
    }

    for(int i=0;i<no_missile;i++){
        for(int j=0;j<no_parachute;j++){
            bool collision = detect_collision(missile_vector[i].get_box(),parachute_vector[j].get_box());
            if(collision){
                fighter_jet.inc_score(PARACHUTE_SCORE);
                system("aplay ../sounds/parachute.wav &");
                parachute_vector.erase(parachute_vector.begin() + j);
                no_parachute--;
            }
        }
    }
}

void init_volcano(){
    float z_coord = -1900.0f; 
    for(int i=0;i<sqrt(TOTAL_VOLCANO);i++){
        float x_coord = -1900.0f;
        for(int j=0;j<sqrt(TOTAL_VOLCANO);j++){
            int random = rand() % 2;
            if(random == 0){
                volcano_vector.push_back(Volcano(x_coord,GROUND_HEIGHT,z_coord,COLOR_GREEN));
                no_volcano++;
            }
            x_coord += DIST_VOLCANO;
        }
        z_coord += DIST_VOLCANO;
    }
}

void init_cannon(){
    float z_coord = -1800.0f; 
    for(int i=0;i<sqrt(TOTAL_CANNON);i++){
        float x_coord = -1800.0f;
        for(int j=0;j<sqrt(TOTAL_CANNON);j++){
            int random = rand() % 3;
            if(random){
                cannon_vector.push_back(Cannon(x_coord,GROUND_HEIGHT + CANNON_HEIGHT/4.0f,z_coord,COLOR_RED));
                no_cannon++;
            }
            x_coord += DIST_CANNON;
        }
        z_coord += DIST_CANNON;
    }
}



void init_ring(){
    float z_coord = -1800.0f; 
    for(int i=0;i<sqrt(TOTAL_RING);i++){
        float x_coord = -1800.0f;
        for(int j=0;j<sqrt(TOTAL_RING);j++){
            int random = rand() % 2;
            int random_height = rand() % 3;

            float height;
            if(random_height == 0){
                height = HEIGHT_RING_1;
            } else if (random_height == 1){
                height = HEIGHT_RING_2;
            } else if (random_height == 2){
                height = HEIGHT_RING_3;
            }

            if(random){
                ring_vector.push_back(Ring(x_coord,height,z_coord,COLOR_GOLDEN));
                no_ring++;
            }
            x_coord += DIST_RING;
        }
        z_coord += DIST_RING;
    }
}

void init_parachute(){

    int sign[] = {-1,1};
    for(int i=0; i<TOTAL_PARACHUTE; i++){
        float z_coord = rand() % (int)(GROUND_LENGTH - 100); 
        float x_coord = rand() % (int)(GROUND_WIDTH - 100);

        int random_sign_1 = rand()%2;
        int random_sign_2 = rand()%2;

        z_coord *= sign[random_sign_1];
        x_coord *= sign[random_sign_2];

        int random_height = rand() % 3;

        float height;
        if(random_height == 0){
            height = HEIGHT_PARACHUTE_1;
        } else if (random_height == 1){
            height = HEIGHT_PARACHUTE_2;
        } else if (random_height == 2){
            height = HEIGHT_PARACHUTE_3;
        }

        parachute_vector.push_back(Parachute(x_coord,height,z_coord,COLOR_GOLDEN));
        no_parachute++;

    }
}

void init_fuel_refill(){

    int sign[] = {-1,1};
    for(int i=0; i<TOTAL_FUEL_REFILL; i++){
        float z_coord = rand() % (int)(GROUND_LENGTH - 100); 
        float x_coord = rand() % (int)(GROUND_WIDTH - 100);

        int random_sign_1 = rand()%2;
        int random_sign_2 = rand()%2;

        z_coord *= sign[random_sign_1];
        x_coord *= sign[random_sign_2];

        int random_height = rand() % 3;

        float height;
        if(random_height == 0){
            height = HEIGHT_RING_1;
        } else if (random_height == 1){
            height = HEIGHT_RING_2;
        } else if (random_height == 2){
            height = HEIGHT_RING_3;
        }

        fuel_refill_vector.push_back(Fuel_Refill(x_coord,height,z_coord,COLOR_GOLDEN));
        no_fuel_refill++;

    }
}

void init_health_refill(){

    int sign[] = {-1,1};
    for(int i=0; i<TOTAL_HEALTH_REFILL; i++){
        float z_coord = rand() % (int)(GROUND_LENGTH - 100); 
        float x_coord = rand() % (int)(GROUND_WIDTH - 100);

        int random_sign_1 = rand()%2;
        int random_sign_2 = rand()%2;

        z_coord *= sign[random_sign_1];
        x_coord *= sign[random_sign_2];

        int random_height = rand() % 3;

        float height;
        if(random_height == 0){
            height = HEIGHT_RING_1;
        } else if (random_height == 1){
            height = HEIGHT_RING_2;
        } else if (random_height == 2){
            height = HEIGHT_RING_3;
        }

        health_refill_vector.push_back(Health_Refill(x_coord,height,z_coord,COLOR_DARK_RED));
        no_health_refill++;

    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    fighter_jet = Jet(0, 50, 0, COLOR_RED);
    ground = Ground(0, 0, 0, COLOR_RED);
    arrow = Checkpoint(0,100,50,COLOR_DARK_RED);
    dashboard = Dashboard (0.0f,0.0f,0.0f, COLOR_WHITE);

    score = Segmentdisplay(-0.25,3.25);
    score.update(0);

    init_volcano ();
    init_cannon();
    init_ring();
    init_parachute();
    init_fuel_refill();
    init_health_refill();

    vector<pair<int, pair <float,float> > >locations;

    for(int i=0;i<no_volcano;i++){
        glm::vec3 position = volcano_vector[i].get_position();
        locations.push_back(make_pair(VOLCANO,make_pair(position.x,position.z)));
    }

    for(int i=0;i<no_cannon;i++){
        glm::vec3 position = cannon_vector[i].get_position();
        locations.push_back(make_pair(ENEMY_CANNON,make_pair(position.x,position.z)));
    }

    // for(int i=0<i<no_ring;i++){
    //     glm::vec3 position = ring_vector[i].get_position();
    //     locations.push_back(make_pair(RING,make_pair(position.x,position.z)));
    // }

    dashboard.update_map(locations);



    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Matrices_Ortho.MatrixID = glGetUniformLocation(programID, "MVP_Ortho");


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

    window = initGLFW(WIDTH, HEIGHT);

    initGL (window, WIDTH, HEIGHT);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {

            plane_position = fighter_jet.get_position();
            plane_velocity = fighter_jet.get_velocity();
            up_direction = fighter_jet.get_up_direction();
            forward_direction = fighter_jet.get_forward_direction();
            remaining_fuel = fighter_jet.get_remaining_fuel();
            remaining_health = fighter_jet.get_health();

            if(plane_position.y < GROUND_HEIGHT || remaining_health < MIN_HEALTH || remaining_fuel < MIN_FUEL){
                cout << "YOU LOSE\nYOUR FINAL SCORE: " << fighter_jet.get_score() << "\n";
                exit(0);
            }

            if(no_cannon <= 0){
                cout << "YOU WIN\nYOUR FINAL SCORE: " << fighter_jet.get_score() << "\n";  
                exit(0);              
            }
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
            usleep(10000);

            ticks++;

            if(ticks % 900 == 0){
                // quit(window);
                // exit(0);
                init_parachute();
            }
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.position.x - b.position.x) * 2 < (a.width + b.width)) &&
           (abs(a.position.y - b.position.y) * 2 < (a.height + b.height)) &&
           (abs(a.position.z - b.position.z) * 2 < (a.length + b.length));
}

void reset_screen() {
    float view_volume = 90.0f / screen_zoom;
    Matrices.projection = glm::perspective(glm::radians(view_volume),1.0f,NEAR_CAMERA,FAR_CAMERA);

    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices_Ortho.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
