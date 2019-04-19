#include "main.h"

#ifndef JET_H
#define JET_H


class Jet {
public:
    Jet() {}
    Jet(float x, float y, float z, color_t color);
    bool visible;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 rotation;
    glm::vec3 angular_v;
    glm::vec3 up_direction;
    glm::vec3 forward_direction;

    glm::mat4 rotate_x,rotate_y,rotate_z;
    glm::mat4 final_rotation;

    float radius_body;
    float length_body;
    float radius_fire;
    float length_fire;
    float radius_fire_big;
    float length_fire_big;
    float radius_engine;
    float length_cone;
    float length_wing;
    float length_tail_wing;
    float length_dorsal_wing;

    float fuel;
    float fuel_consumption_rate;

    float health;

    int score;
    
    bounding_box_t box;
    bounding_box_t get_box();
    
    void draw(glm::mat4 VP);
    glm::vec3 get_position();
    glm::vec3 get_velocity();
    glm::mat4 get_rotation();
    glm::vec3 get_up_direction();
    glm::vec3 get_forward_direction();
    bool get_visibility();
    void tick();
    void move_forward();
    void move_backward();
    void accelerate();
    void decelerate();
    void slow_down();
    void rotate_right();
    void rotate_left();
    void nose_up();
    void nose_down();
    void tilt_left();
    void tilt_right();
    void altitude_gain();
    void altitude_lose();
    void update_box();
    float get_remaining_fuel();
    float get_health();
    void fuel_received();
    void health_received();
    void enemy_hit(float hit_value);
    void inc_score(int increment);
    int get_score();
private:
    VAO *body;
    VAO *cone;
    VAO *wings;
    VAO *tail_wings;
    VAO *dorsal_wing;
    VAO *engine;
    VAO *fire;
    VAO *fire_big;
    VAO *crosshair;
};

#endif // JET_H
