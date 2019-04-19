#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H


class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y, float z, color_t color);
    glm::vec3 position;
    bool visible;
    float island_radius;
    float island_height;

    float volcano_radius;
    float volcano_height;

    float lava_radius;
    float lava_height;

    float rotation;

    bounding_box_t box;
    bounding_box_t get_box();

    void draw(glm::mat4 VP);
    glm::vec3 get_position();
    void tick();
    bool get_visibility();
private:
    VAO *island;
    VAO *volcano;
    VAO *lava;
};

#endif // VOLCANO_H
