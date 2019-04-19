#include "segmentdisplay.h"
#include "main.h"
#include <cstring>

Segmentdisplay::Segmentdisplay(float x, float y)
{
    this->score = 0;
    this->digslen = 0;
    this->position = glm::vec3(x, y, 0);
}

void Segmentdisplay::update(int score) {
    this->score = score;
    char scorestr[50];
    sprintf(scorestr, "%d", score);
    this->digslen = strlen(scorestr);

    int i=this->digslen-1;
    while(i>=0){
        digs[i] = Digit(scorestr[i], 4 - 0.3*(this->digslen - i) + this->position.x, this->position.y);
        i--;
    }
}

void Segmentdisplay::draw(glm::mat4 VP) {
    for (int i = 0; i < this->digslen; i++){
        digs[i].draw(VP);
    }
}

Digit::Digit(char c, float x, float y)
{
    this->position = glm::vec3(x, y, 0);
    bool l[8];
    for (int i = 0; i < 8; i++) l[i] = false;
    switch (c) {
    case '0':
        l[1] = l[2] = l[3] = l[4] = l[5] = l[6] = true;
        break;
    case '1':
        l[2] = l[3] = true;
        break;
    case '2':
        l[1] = l[2] = l[7] = l[5] = l[4] = true;
        break;
    case '3':
        l[1] = l[2] = l[7] = l[3] = l[4] = true;
        break;
    case '4':
        l[6] = l[7] = l[2] = l[3] = true;
        break;
    case '5':
        l[1] = l[6] = l[7] = l[3] = l[4] = true;
        break;
    case '6':
        l[1] = l[6] = l[7] = l[3] = l[4] = l[5] = true;
        break;
    case '7':
        l[1] = l[2] = l[3] = true;
        break;
    case '8':
        l[1] = l[2] = l[7] = l[5] = l[4] = l[3] = l[6] = true;
        break;
    case '9':
        l[1] = l[2] = l[7] = l[4] = l[3] = l[6] = true;
        break;
    case '-':
        l[7] = true;
    }
    const GLfloat vbl[][6] = {
        {0, 0.4, 0, 0.2, 0.4, 0},
        {0.2, 0.4, 0, 0.2, 0.2, 0},
        {0.2, 0.2, 0, 0.2, 0, 0},
        {0.2, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0.2, 0},
        {0, 0.4, 0, 0, 0.2, 0},
        {0, 0.2, 0, 0.2, 0.2, 0},
    };

    int i=0;
    while(i<7)
    {
        if (l[i+1])
        {
            lines[i] = Line(x+vbl[i][0], y+vbl[i][1], x+vbl[i][3], y+vbl[i][4]);
        }
        i++;
    }
}

void Digit::draw(glm::mat4 VP) {
    for (int i = 0; i < 7; i++) lines[i].draw(VP);
}

Line::Line(float fx, float fy, float tx, float ty)
{
    if (tx == fx) rotation = ty > fy ? M_PI/2 : -M_PI/2;
    else if (ty == fy) rotation = tx > fx ? 0 : M_PI;
    else rotation = atan((ty-fy)/(tx-fx));
    position = glm::vec3(fx, fy, 0);
    static const GLfloat vertex_buffer_data [] = {
        0, 0, 0,
        0.2, 0, 0
    };
    this->object = create3DObject(GL_LINES, 2, vertex_buffer_data, COLOR_YELLOW, GL_FILL);
}


void Line::draw(glm::mat4 VP) {
    if (!this->object) return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 rotate = glm::rotate(rotation, glm::vec3(0,0,1));
    glm::mat4 translate = glm::translate (this->position);        // glTranslatef
    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    draw3DObject(this->object);
}
