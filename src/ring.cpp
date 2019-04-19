#include "ring.h"
#include "main.h"

Ring::Ring(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    int random = rand() % 180;
    this->rotation = random;

    ring_length = 1.0f;
    ring_radius = 5.0f;

    this->box.position = this->position;
    this->box.length = 0.1*ring_length;
    this->box.width = 1.5*ring_radius;
    this->box.height = 1.5*ring_radius;

    this->visible = true;

    int vertices = 50;

	GLfloat ring_body[9*2*vertices];

	int num = 0;

	for(int i=0;i<9*2*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
    
        ring_body[i] = ring_radius * cos(angle);
        ring_body[i+1] = ring_radius* sin(angle);
        ring_body[i+2] = -ring_length;
        ring_body[i+3] = ring_radius * cos(angle);
        ring_body[i+4] = ring_radius* sin(angle);
        ring_body[i+5] = ring_length;
        ring_body[i+6] = ring_radius * cos(angle2);
        ring_body[i+7] = ring_radius * sin(angle2);
        ring_body[i+8] = ring_length;

        i+=9;

        ring_body[i] = ring_radius * cos(angle2);
        ring_body[i+1] = ring_radius * sin(angle2);
        ring_body[i+2] = ring_length;
        ring_body[i+3] = ring_radius * cos(angle);
        ring_body[i+4] = ring_radius* sin(angle);
        ring_body[i+5] = -ring_length;
        ring_body[i+6] = ring_radius * cos(angle2);
        ring_body[i+7] = ring_radius * sin(angle2);
        ring_body[i+8] = -ring_length;
    

		num ++;
	}


    this->ring_body = create3DObject(GL_TRIANGLES, 3*2*vertices, ring_body, COLOR_GOLDEN, GL_FILL);

}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ring_body);
}

void Ring::tick() {
    // this->rotation += 0.5f;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

glm::vec3 Ring::get_position(){
    return this->position;
}

glm::vec3 Ring::get_forward(){
    return this->forward;
}

bounding_box_t Ring::get_box(){
    return this->box;
}

bool Ring::get_visibility(){
    return this->visible;
}

void Ring::make_visible(){
    this->visible = true;
}

void Ring::taken(){
    this->visible = false;
}