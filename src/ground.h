#include "main.h"

#ifndef GROUND_H
#define GROUND_H


class Ground {
public:
    Ground() {}
    Ground(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float length;
    float width;
    float height;
    void draw(glm::mat4 VP);
    glm::vec3 get_position();
    void tick();
private:
    VAO *ground;
    VAO *soil;
};

#endif // GROUND_H
