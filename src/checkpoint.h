#include "main.h"

#ifndef CHECKPOINT_H
#define CHECKPOINT_H


class Checkpoint {
public:
    Checkpoint() {}
    Checkpoint(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float body_length;
    float body_radius;
    float cone_length;
    float cone_radius;
    void draw(glm::mat4 VP);
    glm::vec3 get_position();
    void tick(int tick);
private:
    VAO *arrow_body;
    VAO *arrow_head;
};

#endif // CHECKPOINT_H
