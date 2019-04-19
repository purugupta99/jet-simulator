#include "enemy_cannon.h"
#include "main.h"

Cannon::Cannon(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    length = CANNON_LENGTH/2.0f;
    width = CANNON_WIDTH/2.0f;
    height = CANNON_HEIGHT/4.0f;

    gun_length = length*2.0f;
    gun_radius = 3.0f;

    this->box.position = this->position;
    this->box.length = CANNON_LENGTH;
    this->box.width = CANNON_WIDTH;
    this->box.height = CANNON_HEIGHT;

    this->visible = false;

    GLfloat cannon_body[3*3*12*4] = {
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
        cannon_body[i] = -cannon_body[i-3*3*12];
        cannon_body[i+1] = cannon_body[i+1-3*3*12];
        cannon_body[i+2] = cannon_body[i+2-3*3*12];

    }

    for(int i=3*3*12*2;i<3*3*12*3;i+=3){
        cannon_body[i] = -cannon_body[i-3*3*12*2];
        cannon_body[i+1] = cannon_body[i+1-3*3*12*2];
        cannon_body[i+2] = -cannon_body[i+2-3*3*12*2];
    }

    for(int i=3*3*12*3;i<3*3*12*4;i+=3){
        cannon_body[i] = cannon_body[i-3*3*12*3];
        cannon_body[i+1] = cannon_body[i+1-3*3*12*3];
        cannon_body[i+2] = -cannon_body[i+2-3*3*12*3];

    }

    GLfloat cannon_base[3*3*12*4] = {
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
        cannon_base[i] = -cannon_base[i-3*3*12];
        cannon_base[i+1] = cannon_base[i+1-3*3*12];
        cannon_base[i+2] = cannon_base[i+2-3*3*12];

    }

    for(int i=3*3*12*2;i<3*3*12*3;i+=3){
        cannon_base[i] = -cannon_base[i-3*3*12*2];
        cannon_base[i+1] = cannon_base[i+1-3*3*12*2];
        cannon_base[i+2] = -cannon_base[i+2-3*3*12*2];
    }

    for(int i=3*3*12*3;i<3*3*12*4;i+=3){
        cannon_base[i] = cannon_base[i-3*3*12*3];
        cannon_base[i+1] = cannon_base[i+1-3*3*12*3];
        cannon_base[i+2] = -cannon_base[i+2-3*3*12*3];

    }

    int vertices = 50;

	GLfloat cannon_gun[9*3*vertices];

	int num = 0;

	for(int i=0;i<9*2*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
        
            cannon_gun[i] = gun_radius * cos(angle);
            cannon_gun[i+1] = gun_radius* sin(angle) + height/2.0f;
            cannon_gun[i+2] = -gun_length + length;
            cannon_gun[i+3] = gun_radius * cos(angle);
            cannon_gun[i+4] = gun_radius* sin(angle) + height/2.0f;
            cannon_gun[i+5] = gun_length + length;
            cannon_gun[i+6] = gun_radius * cos(angle2);
            cannon_gun[i+7] = gun_radius * sin(angle2) + height/2.0f;
            cannon_gun[i+8] = gun_length + length;

            i+=9;

            cannon_gun[i] = gun_radius * cos(angle2);
            cannon_gun[i+1] = gun_radius * sin(angle2) + height/2.0f;
            cannon_gun[i+2] = gun_length + length;
            cannon_gun[i+3] = gun_radius * cos(angle);
            cannon_gun[i+4] = gun_radius* sin(angle) + height/2.0f;
            cannon_gun[i+5] = -gun_length + length;
            cannon_gun[i+6] = gun_radius * cos(angle2);
            cannon_gun[i+7] = gun_radius * sin(angle2) + height/2.0f;
            cannon_gun[i+8] = -gun_length + length;
        

		num ++;
	}

    num = 0;

	for(int i=9*2*vertices;i<9*2*vertices + 9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
		cannon_gun[i] =0.0f;
		cannon_gun[i+1] =0.0f + height/2.0f;
		cannon_gun[i+2] = gun_length + length;
		cannon_gun[i+3] =gun_radius * cos(angle);
		cannon_gun[i+4] =gun_radius* sin(angle) + height/2.0f;
		cannon_gun[i+5] = gun_length + length;
		cannon_gun[i+6] =gun_radius * cos(angle2);
		cannon_gun[i+7] =gun_radius * sin(angle2) + height/2.0f;
		cannon_gun[i+8] = gun_length + length;

		num ++;
	}

    this->cannon_body = create3DObject(GL_TRIANGLES, 12*3*4, cannon_body, COLOR_BLUE, GL_FILL);
    this->cannon_base = create3DObject(GL_TRIANGLES, 12*3*4, cannon_base, COLOR_GREEN, GL_FILL);
    this->cannon_gun = create3DObject(GL_TRIANGLES, 3*3*vertices, cannon_gun, COLOR_BLACK, GL_FILL);

}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->cannon_body);
    draw3DObject(this->cannon_base);
    // draw3DObject(this->cannon_gun);
}

void Cannon::draw_gun(glm::mat4 VP){
    glm::vec3 new_z = plane_position - this->position;
    new_z = glm::normalize(new_z);
    this->forward = new_z;
    glm::vec3 x = glm::vec3(1,0,0);
    glm::vec3 new_x = glm::cross(new_z,x);
    glm::vec3 new_y = glm::cross(new_z,new_x);
    
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 translate_origin = glm::translate (glm::vec3(0.0f,0.0f,0.0f));    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));

    glm::mat4 rotate = glm::rotate((float) (0.0f * M_PI / 180.0f), glm::vec3(1, 0, 0));
    rotate[0][0]= new_x.x;
    rotate[0][1]= new_x.y;
    rotate[0][2]= new_x.z;

    rotate[1][0]= new_y.x;
    rotate[1][1]= new_y.y;
    rotate[1][2]= new_y.z;

    rotate[2][0]= new_z.x;
    rotate[2][1]= new_z.y;
    rotate[2][2]= new_z.z;

    Matrices.model *= (translate * rotate * translate_origin);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    draw3DObject(this->cannon_gun);

}

void Cannon::tick() {
    // this->rotation += 0.5f;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

glm::vec3 Cannon::get_position(){
    return this->position;
}

glm::vec3 Cannon::get_forward(){
    return this->forward;
}

bounding_box_t Cannon::get_box(){
    return this->box;
}

bool Cannon::get_visibility(){
    return this->visible;
}

void Cannon::make_visible(){
    this->visible = true;
}

Cannon_Ball::Cannon_Ball(float x, float y, float z, glm::vec3 forward,  color_t color) {
    this->position = glm::vec3(x, y, z);
    this->velocity = glm::vec3(4.0f, 4.0f, 4.0f);
    this->acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    this->angular_v = glm::vec3(1.0f, 1.0f, 1.0f);
    // this->total_rotation = rotation;
    this->forward = forward;

    this->visible = true;
    this->box.position = this->position;

    radius_cone = 1.0f;
    height_cone = sqrt(2) * radius_cone;

    this->box.length = 2*radius_cone;
    this->box.width = 2*(radius_cone);
    this->box.height = 2*(height_cone);

    int vertices = 4;

	GLfloat cannon_ball[2*9*vertices];

    int num = 0;

	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
        
            cannon_ball[i] = 0.0f;
            cannon_ball[i+1] = height_cone;
            cannon_ball[i+2] = 0.0f;
            cannon_ball[i+3] = radius_cone * cos(angle);
            cannon_ball[i+4] = 0.0f;
            cannon_ball[i+5] = radius_cone* sin(angle);
            cannon_ball[i+6] = radius_cone * cos(angle2);
            cannon_ball[i+7] = 0.0f;
            cannon_ball[i+8] = radius_cone * sin(angle2);

		num ++;
	}

    num = 0;

	for(int i=9*vertices;i<2*9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
        
            cannon_ball[i] = 0.0f;
            cannon_ball[i+1] = -height_cone;
            cannon_ball[i+2] = 0.0f;
            cannon_ball[i+3] = radius_cone * cos(angle);
            cannon_ball[i+4] = 0.0f;
            cannon_ball[i+5] = radius_cone* sin(angle);
            cannon_ball[i+6] = radius_cone * cos(angle2);
            cannon_ball[i+7] = 0.0f;
            cannon_ball[i+8] = radius_cone * sin(angle2);

		num ++;
	}

    this->cannon_ball = create3DObject(GL_TRIANGLES, 2*vertices*3 , cannon_ball, COLOR_BLACK, GL_FILL);
}

void Cannon_Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate_origin = glm::translate (glm::vec3(0,0,0));    // glTranslatef
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef

    Matrices.model *= (translate * total_rotation);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->cannon_ball);
}

void Cannon_Ball::tick() {
    // this->forward = forward_direction;
    this->velocity += this->acceleration;
    // std::cout << this->position.x << "/n" << this->position.y << "/n" << this->position.z << "/n" ;
    this->move_forward();
    this->update_box();

}

void Cannon_Ball::move_forward(){
    this->position += this->velocity.z * this->forward;
}

bounding_box_t Cannon_Ball::get_box(){
    return this->box;
}

glm::vec3 Cannon_Ball::get_position(){
    return this->position;
}

bool Cannon_Ball::get_visibility(){
    return this->visible;
}

void Cannon_Ball::destroyed(){
    this->visible = false;
}

void Cannon_Ball::update_box(){
    this->box.position = this->position;
}