#include "main.h"

#ifndef SEGMENTDISPLAY_H
#define SEGMENTDISPLAY_H

class Line
{
public:
    Line() {}
    Line(float fx, float fy, float tx, float ty);
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO* object = NULL;
};

class Digit
{
public:
    Digit() {}
    Digit(char c, float x, float y);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    Line lines[7];
};


class Segmentdisplay
{
public:
    Segmentdisplay() {}
    Segmentdisplay(float x, float y);
    int score;
    int digslen;
    glm::vec3 position;
    
    void draw(glm::mat4 VP);
    void update(int score);

private:
    Digit digs[50];
};




#endif // SCORE_H
