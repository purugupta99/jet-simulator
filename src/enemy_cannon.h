#include "main.h"

#ifndef ENEMY_CANNON_H
#define ENEMY_CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 forward;
    float rotation;
    float length;
    float width;
    float height;
    float gun_radius;
    float gun_length;
    bool visible;
    bounding_box_t box;

    void draw(glm::mat4 VP);
    void draw_gun(glm::mat4 VP);
    glm::vec3 get_position();
    glm::vec3 get_forward();

    void tick();
    bool get_visibility();
    void make_visible();
    bounding_box_t get_box();
private:
    VAO *cannon_body;
    VAO *cannon_base;
    VAO *cannon_gun;
};

class   Cannon_Ball {
public:
    Cannon_Ball() {}
    Cannon_Ball(float x, float y, float z, glm::vec3 forward, color_t color);
    bool visible;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::mat4 total_rotation;
    glm::vec3 angular_v;
    glm::vec3 acceleration;
    glm::vec3 forward;

    float radius_cone;
    float height_cone;
    float rotation;
    
    bounding_box_t box;
    bounding_box_t get_box();
    
    void draw(glm::mat4 VP);
    glm::vec3 get_position();
    glm::vec3 get_forward();
    bool get_visibility();
    void tick();
    void move_forward();
    void update_box();
    void destroyed();

private:
    VAO *cannon_ball;
};
#endif // ENEMY_CANNON_H
