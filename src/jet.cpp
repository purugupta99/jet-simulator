#include "jet.h"
#include "main.h"

Jet::Jet(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->velocity = glm::vec3(0.5f, 0.5f, 0.5f);
    this->acceleration = glm::vec3(0.02f, 0.02f, 0.02f);
    this->angular_v = glm::vec3(1.0f, 1.0f, 1.0f);
    this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    this->fuel = MAX_FUEL;
    this->score = 0;
    this->health = MAX_HEALTH;
    this->fuel_consumption_rate = 0.01f;

    this->visible = true;
    this->box.position = this->position;

    this->final_rotation = glm::mat4(1.0f);

    this->rotate_x = glm::rotate((float) (this->rotation.x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    this->rotate_y = glm::rotate((float) (this->rotation.y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    this->rotate_z = glm::rotate((float) (this->rotation.z * M_PI / 180.0f), glm::vec3(0, 0, 1));

    radius_body = 0.35f;
    radius_engine = 0.25f;

    radius_fire = 0.1f;
    length_fire = 0.2f;

    radius_fire_big = 0.3f;
    length_fire_big = 0.6f;

    length_body = 1.5f; // full length_body = 2*length_body

    length_cone = 0.5f;
    length_wing = 2.0f;

    length_tail_wing = 0.75f;
    length_dorsal_wing = 0.75f;

    this->box.length = 2*length_body + length_cone + length_fire;
    this->box.width = 2*(length_wing + radius_body);
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
		body[i+4] =radius_body * sin(angle);
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

    GLfloat wings[] = {
        radius_body, 0, length_body/2.0f,
        radius_body+length_wing, 0, length_body/2.0f,
        radius_body, 0, length_body,
        radius_body, 0, length_body/2.0f,
        radius_body+length_wing, 0, length_body/2.0f,
        radius_body+length_wing, 0, 0,
        radius_body+length_wing+0.5f, 0, 0,
        radius_body+length_wing, 0, length_body/2.0f,
        radius_body+length_wing, 0, 0,

        -radius_body, 0, length_body/2.0f,
        -radius_body-length_wing, 0, length_body/2.0f,
        -radius_body, 0, length_body,
        -radius_body, 0, length_body/2.0f,
        -radius_body-length_wing, 0, length_body/2.0f,
        -radius_body-length_wing, 0, 0,
        -radius_body-length_wing-0.5f, 0, 0,
        -radius_body-length_wing, 0, length_body/2.0f,
        -radius_body-length_wing, 0, 0,
    };

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

    };

    GLfloat engine[9*vertices];

	num = 0;

	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
		engine[i] = 0.0f;
		engine[i+1] = 0.0f;
		engine[i+2] = -length_body-0.01f;
		engine[i+3] = radius_engine * cos(angle);
		engine[i+4] = radius_engine* sin(angle);
		engine[i+5] = -length_body-0.01f;
		engine[i+6] = radius_engine * cos(angle2);
		engine[i+7] = radius_engine * sin(angle2);
		engine[i+8] = -length_body-0.01f;

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

    GLfloat fire_big[9*vertices];

    num = 0;

	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
        
            fire_big[i] = 0.0f;
            fire_big[i+1] = 0.0f;
            fire_big[i+2] = -length_body - length_fire_big;
            fire_big[i+3] = radius_fire_big * cos(angle);
            fire_big[i+4] = radius_fire_big* sin(angle);
            fire_big[i+5] = -length_body;
            fire_big[i+6] = radius_fire_big * cos(angle2);
            fire_big[i+7] = radius_fire_big * sin(angle2);
            fire_big[i+8] = -length_body;

		num ++;
	}

    GLfloat crosshair[] = {
        -1.0f,0.0f,20.0f,
        1.0f,0.0f,20.0f,

        0.0f,-1.0f,20.0f,
        0.0f,1.0f,20.0f,
    };

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    this->body = create3DObject(GL_TRIANGLES, 2*vertices*3 + vertices*3, body, COLOR_GRAY, GL_FILL);
    this->cone = create3DObject(GL_TRIANGLES, vertices*3, cone, COLOR_LIGHT_BLACK, GL_FILL);
    this->wings = create3DObject(GL_TRIANGLES, 6*3, wings, COLOR_RED, GL_FILL);
    this->tail_wings = create3DObject(GL_TRIANGLES, 2*3, tail_wings, COLOR_LIGHT_BLACK, GL_FILL);
    this->dorsal_wing = create3DObject(GL_TRIANGLES, 1*3, dorsal_wing, COLOR_LIGHT_BLACK, GL_FILL);
    this->engine = create3DObject(GL_TRIANGLES, vertices*3, engine, COLOR_LIGHT_BLACK, GL_FILL);
    this->fire = create3DObject(GL_TRIANGLES, vertices*3, fire, COLOR_FIRE, GL_FILL);
    this->fire_big = create3DObject(GL_TRIANGLES, vertices*3, fire_big, COLOR_FIRE, GL_FILL);
    this->crosshair = create3DObject(GL_LINES, 4, crosshair, COLOR_WHITE, GL_FILL);
}

void Jet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate_origin = glm::translate (glm::vec3(0,0,0));    // glTranslatef
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // this->rotate_x = glm::rotate((float) (this->rotation.x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // this->rotate_y = glm::rotate((float) (this->rotation.y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // this->rotate_z = glm::rotate((float) (this->rotation.z * M_PI / 180.0f), glm::vec3(0, 0, 1));

    Matrices.model *= (translate * final_rotation);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->body);
    draw3DObject(this->cone);
    draw3DObject(this->wings);
    draw3DObject(this->tail_wings);
    draw3DObject(this->dorsal_wing);
    draw3DObject(this->engine);
    if(camera_view == PLANE_VIEW){
        draw3DObject(this->crosshair);
    }
    // std::cout << jet_on << "\n";
    if(!jet_on){
        draw3DObject(this->fire);
    }else{
        draw3DObject(this->fire_big);
    }
}

void Jet::tick() {
    this->forward_direction = glm::vec3(this->final_rotation[2][0],this->final_rotation[2][1],this->final_rotation[2][2]);
    this->up_direction = glm::vec3(this->final_rotation[1][0],this->final_rotation[1][1],this->final_rotation[1][2]);


    if(this->position.x > GROUND_WIDTH) this->position.x = GROUND_WIDTH; 
    if(this->position.x < -GROUND_WIDTH) this->position.x = -GROUND_WIDTH; 
    // std::cout << this->velocity.z << "\n";

    if(this->position.z > GROUND_LENGTH) this->position.z = GROUND_LENGTH; 
    if(this->position.z < -GROUND_LENGTH) this->position.z = -GROUND_LENGTH; 

    this->move_forward();
    this->update_box();

}

void Jet::move_forward(){
    this->position += this->velocity.z * this->forward_direction;
}

void Jet::accelerate(){
    this->fuel -= this->fuel_consumption_rate;
    this->velocity += this->acceleration;
}

void Jet::decelerate(){
    this->fuel -= this->fuel_consumption_rate;
    this->velocity -= this->acceleration;
}

void Jet::slow_down(){
    this->velocity += glm::vec3(-0.01*this->velocity.x,-0.01*this->velocity.y,-0.01*this->velocity.z);
}

void Jet::move_backward(){
    this->position += -this->velocity.z * this->forward_direction;

}

void Jet::rotate_right(){
    glm::vec3 var = glm::vec3(this->final_rotation[1][0],this->final_rotation[1][1],this->final_rotation[1][2]);
    this->rotate_y = glm::rotate((float) (-this->angular_v.y * M_PI / 180.0f), var);
    this->final_rotation = this->rotate_y * this->final_rotation;
}

void Jet::rotate_left(){
    glm::vec3 var = glm::vec3(this->final_rotation[1][0],this->final_rotation[1][1],this->final_rotation[1][2]);
    this->rotate_y = glm::rotate((float) (this->angular_v.y * M_PI / 180.0f), var);
    this->final_rotation = this->rotate_y * this->final_rotation;
}

void Jet::nose_up(){
    glm::vec3 var = glm::vec3(this->final_rotation[0][0],this->final_rotation[0][1],this->final_rotation[0][2]);
    this->rotate_x = glm::rotate((float) (-this->angular_v.x * M_PI / 180.0f), var);
    this->final_rotation = this->rotate_x * this->final_rotation;
}

void Jet::nose_down(){
    glm::vec3 var = glm::vec3(this->final_rotation[0][0],this->final_rotation[0][1],this->final_rotation[0][2]);
    this->rotate_x = glm::rotate((float) (this->angular_v.x * M_PI / 180.0f), var);
    this->final_rotation = this->rotate_x * this->final_rotation;
}

void Jet::tilt_right(){
    glm::vec3 var = glm::vec3(this->final_rotation[2][0],this->final_rotation[2][1],this->final_rotation[2][2]);
    this->rotate_z = glm::rotate((float) (this->angular_v.z * M_PI / 180.0f), var);
    this->final_rotation = this->rotate_z * this->final_rotation;
}

void Jet::tilt_left(){
    glm::vec3 var = glm::vec3(this->final_rotation[2][0],this->final_rotation[2][1],this->final_rotation[2][2]);
    this->rotate_z = glm::rotate((float) (-this->angular_v.z * M_PI / 180.0f), var);
    this->final_rotation = this->rotate_z * this->final_rotation;
}

void Jet::altitude_gain(){
    this->position.y += 0.5f;
}

void Jet::altitude_lose(){
    this->position.y +=  -0.5f;    
}

bounding_box_t Jet::get_box(){
    return this->box;
}

glm::vec3 Jet::get_position(){
    return this->position;
}

glm::vec3 Jet::get_velocity(){
    return this->velocity;
}

glm::vec3 Jet::get_up_direction(){
    return this->up_direction;
}

glm::vec3 Jet::get_forward_direction(){
    return this->forward_direction;
}

glm::mat4 Jet::get_rotation(){
    return this->final_rotation;
}

void Jet::fuel_received(){
    this->fuel += QUANTITY_FUEL_REFILL;
    if(this->fuel > MAX_FUEL){
        this->fuel = MAX_FUEL;
    }
}

void Jet::health_received(){
    this->health += QUANTITY_HEALTH_REFILL;
    if(this->health > MAX_HEALTH){
        this->health = MAX_HEALTH;
    }
}

bool Jet::get_visibility(){
    return this->visible;
}

void Jet::update_box(){
    this->box.position = this->position;
}

void Jet::inc_score(int increment){
    this->score += increment;
}

void Jet::enemy_hit(float hit_value){
    this->health += hit_value;
}

float Jet::get_remaining_fuel(){
    return this->fuel;
}

float Jet::get_health(){
    return this->health;
}

int Jet::get_score(){
    return this->score;
}