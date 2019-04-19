#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 velocity;
    bool visible;
    float parachute_radius;
    float parachute_height;
    float rope_length;
    float drop_radius;
    float drop_height;

    float rotation;

    bounding_box_t box;
    bounding_box_t get_box();

    void draw(glm::mat4 VP);
    glm::vec3 get_position();
    void tick();
    bool get_visibility();
    void update_box();
private:
    VAO *parachute_top;
    VAO *parachute_design;
    VAO *parachute_rope;
    VAO *parachute_drop;
};

#endif // PARACHUTE_H
