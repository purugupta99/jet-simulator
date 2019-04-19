#include "ground.h"
#include "main.h"

Ground::Ground(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    length = GROUND_LENGTH;
    width = GROUND_WIDTH;
    height = GROUND_HEIGHT;

    GLfloat ground[3*3*12*4] = {
        0.0f,height,0.0f,
        0.0f,0.0f,0.0f,
        0.0f,0.0f,width,
        0.0f,height,0.0f,
        0.0f,height,width,
        0.0f,0.0f,width,
        0.0f,height,0.0f,
        0.0f,height,width,
        length,height,0.0f,
        length,height,width,
        0.0f,height,width,
        length,height,0.0f,
        length,height,width,
        length,0.0f,0.0f,
        length,height,0.0f,
        length,height,width,
        length,0.0f,0.0f,
        length,0.0f,width,
        0.0f,0.0f,0.0f,
        length,0.0f,0.0f,
        length,0.0f,width,
        0.0f,0.0f,0.0f,
        0.0f,0.0f,width,
        length,0.0f,width,
        0.0f,height,width,
        0.0f,0.0f,width,
        length,0.0f,width,
        0.0f,height,width,
        length,height,width,
        length,0.0f,width,
        0.0f,0.0f,0.0f,
        0.0f,height,0.0f,
        length,0.0f,0.0f,
        length,height,0.0f,
        0.0f,height,0.0f,
        length,0.0f,0.0f,
    };

    for(int i=3*3*12;i<3*3*12*2;i+=3){
        ground[i] = -ground[i-3*3*12];
        ground[i+1] = ground[i+1-3*3*12];
        ground[i+2] = ground[i+2-3*3*12];

    }

    for(int i=3*3*12*2;i<3*3*12*3;i+=3){
        ground[i] = -ground[i-3*3*12*2];
        ground[i+1] = ground[i+1-3*3*12*2];
        ground[i+2] = -ground[i+2-3*3*12*2];
    }

    for(int i=3*3*12*3;i<3*3*12*4;i+=3){
        ground[i] = ground[i-3*3*12*3];
        ground[i+1] = ground[i+1-3*3*12*3];
        ground[i+2] = -ground[i+2-3*3*12*3];

    }

    GLfloat soil[3*3*12*4] = {
        0.0f,-height,0.0f,
        0.0f,0.0f,0.0f,
        0.0f,0.0f,width,
        0.0f,-height,0.0f,
        0.0f,-height,width,
        0.0f,0.0f,width,
        0.0f,-height,0.0f,
        0.0f,-height,width,
        length,-height,0.0f,
        length,-height,width,
        0.0f,-height,width,
        length,-height,0.0f,
        length,-height,width,
        length,0.0f,0.0f,
        length,-height,0.0f,
        length,-height,width,
        length,0.0f,0.0f,
        length,0.0f,width,
        0.0f,0.0f,0.0f,
        length,0.0f,0.0f,
        length,0.0f,width,
        0.0f,0.0f,0.0f,
        0.0f,0.0f,width,
        length,0.0f,width,
        0.0f,-height,width,
        0.0f,0.0f,width,
        length,0.0f,width,
        0.0f,-height,width,
        length,-height,width,
        length,0.0f,width,
        0.0f,0.0f,0.0f,
        0.0f,-height,0.0f,
        length,0.0f,0.0f,
        length,-height,0.0f,
        0.0f,-height,0.0f,
        length,0.0f,0.0f,
    };

    for(int i=3*3*12;i<3*3*12*2;i+=3){
        soil[i] = -soil[i-3*3*12];
        soil[i+1] = soil[i+1-3*3*12];
        soil[i+2] = soil[i+2-3*3*12];

    }

    for(int i=3*3*12*2;i<3*3*12*3;i+=3){
        soil[i] = -soil[i-3*3*12*2];
        soil[i+1] = soil[i+1-3*3*12*2];
        soil[i+2] = -soil[i+2-3*3*12*2];
    }

    for(int i=3*3*12*3;i<3*3*12*4;i+=3){
        soil[i] = soil[i-3*3*12*3];
        soil[i+1] = soil[i+1-3*3*12*3];
        soil[i+2] = -soil[i+2-3*3*12*3];

    }

    this->ground = create3DObject(GL_TRIANGLES, 12*3*4, ground, COLOR_WATER, GL_FILL);
    this->soil = create3DObject(GL_TRIANGLES, 12*3*4, soil, COLOR_LIGHT_BLACK, GL_FILL);

}

void Ground::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ground);
    draw3DObject(this->soil);
}

void Ground::tick() {
    // this->rotation += 0.5f;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

glm::vec3 Ground::get_position(){
    return this->position;
}
