#include "main.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H


class Dashboard {
public:
    Dashboard() {}
    Dashboard(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 velocity;
    bool visible;

    float map_radius;

    float length_bar;
    float height_bar;
    float radius_speedometer;
    float length_speedometer;
    float offset_speedometer;

    float length_speedometer_needle;

    float length_compass_needle;

    float altitude_x;
    float altitude_y;
    float compass_x;
    float compass_y;
    float map_x;
    float map_y;
    float healthmeter_x;
    float healthmeter_y;
    float speedometer_x;
    float speedometer_y;
    float fuelometer_x;
    float fuelometer_y;

    std::vector <glm::vec3> volcano_position;
    std::vector <glm::vec3> cannon_position;

    std::vector < std::pair<int, std::pair <float,float> > > locations;

    float rotation;

    bounding_box_t box;
    bounding_box_t get_box();

    void draw(glm::mat4 VP);
    void draw_needle(glm::mat4 VP);
    void draw_map(glm::mat4 VP);
    void draw_compass_needle(glm::mat4 VP);
    glm::vec3 get_position();
    void tick();
    bool get_visibility();
    void update_box();
    void free_memory();
    void update_map(std::vector < std::pair<int, std::pair <float,float> > >locations);
private:
    VAO *altitude_meter;
    VAO *health_meter;
    VAO *fuelo_meter;
    VAO *speedometer_body;
    VAO *speedometer_needle;
    VAO *compass_needle;
    VAO *map;
    VAO *map_volcano;
    VAO *map_cannon;
    VAO *map_plane;
};

#endif // DASHBOARD_H
