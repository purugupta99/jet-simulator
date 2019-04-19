#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 forward;
    float rotation;
    
    float ring_radius;
    float ring_length;
    bool visible;
    bounding_box_t box;

    void draw(glm::mat4 VP);
    glm::vec3 get_position();
    glm::vec3 get_forward();

    void tick();
    bool get_visibility();
    void make_visible();
    void taken();
    bounding_box_t get_box();
private:
    VAO *ring_body;
};

#endif // RING_H
