#include "main.h"

#ifndef WEAPON_H
#define WEAPON_H


class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z, glm::mat4 rotation, color_t color);
    bool visible;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::mat4 total_rotation;
    glm::vec3 angular_v;
    glm::vec3 acceleration;
    glm::vec3 forward;

    float radius_body;
    float length_body;
    float radius_fire;
    float length_fire;
    float radius_engine;
    float length_cone;
    float length_tail_wing;
    float length_dorsal_wing;
    
    bounding_box_t box;
    bounding_box_t get_box();
    
    void draw(glm::mat4 VP);
    glm::vec3 get_position();
    glm::vec3 get_forward_direction();
    bool get_visibility();
    void tick();
    void move_forward();
    void update_box();
private:
    VAO *body;
    VAO *cone;
    VAO *tail_wings;
    VAO *dorsal_wing;
    VAO *engine;
    VAO *fire;
};

class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z, float plane_velocity, color_t color);
    bool visible;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 angular_v;
    glm::vec3 acceleration;
    glm::vec3 forward;

    float radius_body;
    float length_body;
    float length_cone;
    float length_wing;
    
    bounding_box_t box;
    bounding_box_t get_box();
    
    void draw(glm::mat4 VP);
    glm::vec3 get_position();
    glm::vec3 get_forward_direction();
    bool get_visibility();
    void tick();
    void move_forward();
    void update_box();
private:
    VAO *body;
    VAO *cone_1;
    VAO *cone_2;
    VAO *wings;
};

#endif // WEAPON_H
