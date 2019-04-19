#include "main.h"

#ifndef POWER_UP
#define POWER_UP


class Fuel_Refill {
public:
    Fuel_Refill() {}
    Fuel_Refill(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float body_length;
    float body_radius;
    float cone_length;
    float cone_radius;
    bounding_box_t box;

    void draw(glm::mat4 VP);
    glm::vec3 get_position();
    void tick(int tick);
    void update_box();
    bounding_box_t get_box();

private:
    VAO *barrel_body;
    VAO *barrel_design;
};

class Health_Refill {
public:
    Health_Refill() {}
    Health_Refill(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float length;
    float width;
    float height;
    float thickness;
    
    bounding_box_t box;

    void draw(glm::mat4 VP);
    glm::vec3 get_position();
    void tick(int tick);
    void update_box();
    bounding_box_t get_box();

private:
    VAO *horizontal_line;
    VAO *vertical_line;
};

#endif // POWER_UP
