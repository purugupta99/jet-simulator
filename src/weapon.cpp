#include "weapon.h"
#include "main.h"

Missile::Missile(float x, float y, float z, glm::mat4 rotation, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->velocity = glm::vec3(0.5f, 0.5f, 0.5f);
    this->acceleration = glm::vec3(0.05f, 0.05f, 0.05f);
    this->angular_v = glm::vec3(1.0f, 1.0f, 1.0f);
    this->total_rotation = rotation;
    this->forward = forward_direction;

    this->visible = true;
    this->box.position = this->position;

    radius_body = 0.15f;
    radius_engine = 0.10f;

    radius_fire = 0.10f;
    length_fire = 0.20f;
    length_body = 1.0f; // full length_body = 2*length_body

    length_cone = 0.25f;

    length_tail_wing = 0.5f;
    length_dorsal_wing = 0.5f;

    this->box.length = 2*length_body + length_cone + length_fire;
    this->box.width = 2*(radius_body);
    this->box.height = 2*(radius_body);

    int vertices = BODY_EDGES;

	GLfloat body[9*2*vertices + 9*vertices];
	GLfloat cone[9*vertices];

	int num = 0;

	for(int i=0;i<9*2*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
        
            body[i] = radius_body * cos(angle);
            body[i+1] = radius_body* sin(angle);
            body[i+2] = -length_body;
            body[i+3] = radius_body * cos(angle);
            body[i+4] = radius_body* sin(angle);
            body[i+5] = length_body;
            body[i+6] = radius_body * cos(angle2);
            body[i+7] = radius_body * sin(angle2);
            body[i+8] = length_body;

            i+=9;

            body[i] = radius_body * cos(angle2);
            body[i+1] = radius_body * sin(angle2);
            body[i+2] = length_body;
            body[i+3] = radius_body * cos(angle);
            body[i+4] = radius_body* sin(angle);
            body[i+5] = -length_body;
            body[i+6] = radius_body * cos(angle2);
            body[i+7] = radius_body * sin(angle2);
            body[i+8] = -length_body;
        

		num ++;
	}

    num = 0;

	for(int i=9*2*vertices;i<9*2*vertices + 9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
		body[i] =0.0f;
		body[i+1] =0.0f;
		body[i+2] =-length_body;
		body[i+3] =radius_body * cos(angle);
		body[i+4] =radius_body* sin(angle);
		body[i+5] =-length_body;
		body[i+6] =radius_body * cos(angle2);
		body[i+7] =radius_body * sin(angle2);
		body[i+8] =-length_body;

		num ++;
	}

    num = 0;

	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
        
            cone[i] = 0.0f;
            cone[i+1] = 0.0f;
            cone[i+2] = length_body + length_cone;
            cone[i+3] = radius_body * cos(angle);
            cone[i+4] = radius_body* sin(angle);
            cone[i+5] = length_body;
            cone[i+6] = radius_body * cos(angle2);
            cone[i+7] = radius_body * sin(angle2);
            cone[i+8] = length_body;

		num ++;
	}

    GLfloat tail_wings[] = {
        radius_body, 0, -length_body,
        radius_body, 0, -2.0f*length_body/3.0f,
        radius_body+length_tail_wing, 0, -length_body,

        -radius_body, 0, -length_body,
        -radius_body, 0, -2.0f*length_body/3.0f,
        -radius_body-length_tail_wing, 0, -length_body,

    };

    GLfloat dorsal_wing[] = {
        0, radius_body, -length_body/2.0f,
        0, radius_body, -length_body,
        0, radius_body + length_dorsal_wing, -length_body,

        0, -radius_body, -length_body/2.0f,
        0, -radius_body, -length_body,
        0, -radius_body - length_dorsal_wing, -length_body,

    };

    GLfloat engine[9*vertices];

	num = 0;

	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
		engine[i] =0.0f;
		engine[i+1] =0.0f;
		engine[i+2] =-length_body-0.01f;
		engine[i+3] =radius_engine * cos(angle);
		engine[i+4] =radius_engine* sin(angle);
		engine[i+5] =-length_body-0.01f;
		engine[i+6] =radius_engine * cos(angle2);
		engine[i+7] =radius_engine * sin(angle2);
		engine[i+8] =-length_body-0.01f;

		num ++;
	}

    GLfloat fire[9*vertices];

    num = 0;

	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
        
            fire[i] = 0.0f;
            fire[i+1] = 0.0f;
            fire[i+2] = -length_body - length_fire;
            fire[i+3] = radius_fire * cos(angle);
            fire[i+4] = radius_fire* sin(angle);
            fire[i+5] = -length_body;
            fire[i+6] = radius_fire * cos(angle2);
            fire[i+7] = radius_fire * sin(angle2);
            fire[i+8] = -length_body;

		num ++;
	}
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    this->body = create3DObject(GL_TRIANGLES, 2*vertices*3 + vertices*3, body, COLOR_GRAY, GL_FILL);
    this->cone = create3DObject(GL_TRIANGLES, vertices*3, cone, COLOR_RED, GL_FILL);
    this->tail_wings = create3DObject(GL_TRIANGLES, 2*3, tail_wings, COLOR_BLACK, GL_FILL);
    this->dorsal_wing = create3DObject(GL_TRIANGLES, 2*3, dorsal_wing, COLOR_BLACK, GL_FILL);
    this->engine = create3DObject(GL_TRIANGLES, vertices*3, engine, COLOR_BLACK, GL_FILL);
    this->fire = create3DObject(GL_TRIANGLES, vertices*3, fire, COLOR_FIRE, GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate_origin = glm::translate (glm::vec3(0,0,0));    // glTranslatef
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef


    // this->rotate_x = glm::rotate((float) (this->total_rotation.x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // this->rotate_y = glm::rotate((float) (this->total_rotation.y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // this->rotate_z = glm::rotate((float) (this->total_rotation.z * M_PI / 180.0f), glm::vec3(0, 0, 1));

    Matrices.model *= (translate * total_rotation);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->body);
    draw3DObject(this->cone);
    draw3DObject(this->tail_wings);
    draw3DObject(this->dorsal_wing);
    draw3DObject(this->engine);
    draw3DObject(this->fire);
}

void Missile::tick() {
    // this->forward = forward_direction;
    this->velocity += this->acceleration;
    // std::cout << this->position.x << "/n" << this->position.y << "/n" << this->position.z << "/n" ;
    this->move_forward();
    this->update_box();

}

void Missile::move_forward(){
    this->position += this->velocity.z * this->forward;
}

bounding_box_t Missile::get_box(){
    return this->box;
}

glm::vec3 Missile::get_position(){
    return this->position;
}

bool Missile::get_visibility(){
    return this->visible;
}

void Missile::update_box(){
    this->box.position = this->position;
}

Bomb::Bomb(float x, float y, float z, float plane_velocity,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->velocity = glm::vec3(0.0f, 0.3f, plane_velocity);
    this->acceleration = glm::vec3(0.0f, 0.01f, 0.0f);
    this->angular_v = glm::vec3(1.0f, 1.0f, 1.0f);
    this->forward = forward_direction;

    this->visible = true;
    this->box.position = this->position;

    radius_body = 0.30f;
    length_cone = 0.30f;
    
    length_body = 0.4f; // full length_body = 2*length_body

    length_wing = 0.5f;

    this->box.length = 2*(radius_body);
    this->box.width = 2*(radius_body);
    this->box.height = 2*(length_body + length_cone);

    int vertices = BODY_EDGES;

	GLfloat body[9*2*vertices];
	GLfloat cone_1[9*vertices];
	GLfloat cone_2[9*vertices];

	int num = 0;

	for(int i=0;i<9*2*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
        
        body[i] = radius_body * cos(angle);
        body[i+1] = -length_body;
        body[i+2] = radius_body* sin(angle);
        body[i+3] = radius_body * cos(angle);
        body[i+4] = length_body;
        body[i+5] = radius_body* sin(angle);
        body[i+6] = radius_body * cos(angle2);
        body[i+7] = length_body;
        body[i+8] = radius_body * sin(angle2);

        i+=9;

        body[i] = radius_body * cos(angle2);
        body[i+1] = length_body;
        body[i+2] = radius_body * sin(angle2);
        body[i+3] = radius_body * cos(angle);
        body[i+4] = -length_body;
        body[i+5] = radius_body* sin(angle);
        body[i+6] = radius_body * cos(angle2);
        body[i+7] = -length_body;
        body[i+8] = radius_body * sin(angle2);
        

		num ++;
	}

    num = 0;

	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
        
            cone_1[i] = 0.0f;
            cone_1[i+1] = length_body + length_cone;
            cone_1[i+2] = 0.0f;
            cone_1[i+3] = radius_body * cos(angle);
            cone_1[i+4] = length_body;
            cone_1[i+5] = radius_body* sin(angle);
            cone_1[i+6] = radius_body * cos(angle2);
            cone_1[i+7] = length_body;
            cone_1[i+8] = radius_body * sin(angle2);

		num ++;
	}

    for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
        
            cone_2[i] = 0.0f;
            cone_2[i+1] = -length_body - length_cone;
            cone_2[i+2] = 0.0f;
            cone_2[i+3] = radius_body * cos(angle);
            cone_2[i+4] = -length_body;
            cone_2[i+5] = radius_body* sin(angle);
            cone_2[i+6] = radius_body * cos(angle2);
            cone_2[i+7] = -length_body;
            cone_2[i+8] = radius_body * sin(angle2);

		num ++;
	}

    GLfloat wings[] = {
        -radius_body, 0, 0,
        -radius_body, length_wing, 0,
        -radius_body-length_wing, length_wing, 0,

        radius_body, 0, 0,
        radius_body, length_wing, 0,
        radius_body+length_wing, length_wing, 0,

        0, 0, radius_body,
        0, length_wing, radius_body,
        0, length_wing, radius_body+length_wing,

        0, 0, -radius_body,
        0, length_wing, -radius_body,
        0, length_wing, -radius_body-length_wing,

    };
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    this->body = create3DObject(GL_TRIANGLES, 2*vertices*3 , body, COLOR_GRAY, GL_FILL);
    this->cone_1 = create3DObject(GL_TRIANGLES, vertices*3, cone_1, COLOR_RED, GL_FILL);
    this->cone_2 = create3DObject(GL_TRIANGLES, vertices*3, cone_2, COLOR_RED, GL_FILL);
    this->wings = create3DObject(GL_TRIANGLES, 4*3, wings, COLOR_BLACK, GL_FILL);
}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate_origin = glm::translate (glm::vec3(0,0,0));    // glTranslatef
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef


    // this->rotate_x = glm::rotate((float) (this->total_rotation.x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // this->rotate_y = glm::rotate((float) (this->total_rotation.y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // this->rotate_z = glm::rotate((float) (this->total_rotation.z * M_PI / 180.0f), glm::vec3(0, 0, 1));

    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->body);
    draw3DObject(this->cone_1);
    draw3DObject(this->cone_2);
    draw3DObject(this->wings);
}

void Bomb::tick() {
    // this->forward = forward_direction;
    this->velocity += this->acceleration;
    // std::cout << this->position.x << "/n" << this->position.y << "/n" << this->position.z << "/n" ;
    this->move_forward();
    this->update_box();

}

void Bomb::move_forward(){
    this->position += this->velocity.z * this->forward;
    this->position.y -= this->velocity.y;
}

bounding_box_t Bomb::get_box(){
    return this->box;
}

glm::vec3 Bomb::get_position(){
    return this->position;
}

bool Bomb::get_visibility(){
    return this->visible;
}

void Bomb::update_box(){
    this->box.position = this->position;
}