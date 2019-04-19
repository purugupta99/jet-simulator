#include "powerup.h"
#include "main.h"

Fuel_Refill::Fuel_Refill(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    body_length = 4.8f;
    body_radius = 3.0f;

    cone_length = 20.0f;
    cone_radius = 20.0f;

    this->box.position = this->position;
    this->box.length = 2*body_radius;
    this->box.width = 2*body_radius;
    this->box.height = 2*body_length;

    int vertices = 50;

    GLfloat barrel_body[9*4*vertices];
    GLfloat barrel_design[9*2*vertices];

	int num = 0;

	for(int i=0;i<9*2*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;

        barrel_body[i] = body_radius * cos(angle);
        barrel_body[i+1] = -body_length;
        barrel_body[i+2] = body_radius* sin(angle);
        barrel_body[i+3] = body_radius * cos(angle);
        barrel_body[i+4] = body_length;
        barrel_body[i+5] = body_radius* sin(angle);
        barrel_body[i+6] = body_radius * cos(angle2);
        barrel_body[i+7] = body_length;
        barrel_body[i+8] = body_radius * sin(angle2);

        i+=9;

        barrel_body[i] = body_radius * cos(angle2);
        barrel_body[i+1] = body_length;
        barrel_body[i+2] = body_radius * sin(angle2);
        barrel_body[i+3] = body_radius * cos(angle);
        barrel_body[i+4] = -body_length;
        barrel_body[i+5] = body_radius* sin(angle);
        barrel_body[i+6] = body_radius * cos(angle2);
        barrel_body[i+7] = -body_length;
        barrel_body[i+8] = body_radius * sin(angle2);
        

		num ++;
	}

    num = 0;

	for(int i=9*vertices*2;i<9*3*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
        
            barrel_body[i] = 0.0f;
            barrel_body[i+1] = -body_length;
            barrel_body[i+2] = 0.0f;
            barrel_body[i+3] = body_radius * cos(angle);
            barrel_body[i+4] = -body_length;
            barrel_body[i+5] = body_radius* sin(angle);
            barrel_body[i+6] = body_radius * cos(angle2);
            barrel_body[i+7] = -body_length;
            barrel_body[i+8] = body_radius * sin(angle2);

		num ++;
	}

    for(int i=9*vertices*3;i<9*4*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
        
            barrel_body[i] = 0.0f;
            barrel_body[i+1] = body_length;
            barrel_body[i+2] = 0.0f;
            barrel_body[i+3] = body_radius * cos(angle);
            barrel_body[i+4] = body_length;
            barrel_body[i+5] = body_radius* sin(angle);
            barrel_body[i+6] = body_radius * cos(angle2);
            barrel_body[i+7] = body_length;
            barrel_body[i+8] = body_radius * sin(angle2);

		num ++;
	}

    num = 0;

	for(int i=0;i<9*2*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;

        barrel_design[i] = (body_radius + 0.01f) * cos(angle);
        barrel_design[i+1] = -body_length/3.0f;
        barrel_design[i+2] = (body_radius + 0.01f)* sin(angle);
        barrel_design[i+3] = (body_radius + 0.01f) * cos(angle);
        barrel_design[i+4] = body_length/3.0f;
        barrel_design[i+5] = (body_radius + 0.01f)* sin(angle);
        barrel_design[i+6] = (body_radius + 0.01f) * cos(angle2);
        barrel_design[i+7] = body_length/3.0f;
        barrel_design[i+8] = (body_radius + 0.01f) * sin(angle2);

        i+=9;

        barrel_design[i] = (body_radius + 0.01f) * cos(angle2);
        barrel_design[i+1] = body_length/3.0f;
        barrel_design[i+2] = (body_radius + 0.01f) * sin(angle2);
        barrel_design[i+3] = (body_radius + 0.01f) * cos(angle);
        barrel_design[i+4] = -body_length/3.0f;
        barrel_design[i+5] = (body_radius + 0.01f)* sin(angle);
        barrel_design[i+6] = (body_radius + 0.01f) * cos(angle2);
        barrel_design[i+7] = -body_length/3.0f;
        barrel_design[i+8] = (body_radius + 0.01f) * sin(angle2);
        

		num ++;
	}

    

    this->barrel_body = create3DObject(GL_TRIANGLES, 3*4*vertices, barrel_body, COLOR_GRAY, GL_FILL);
    this->barrel_design = create3DObject(GL_TRIANGLES, 3*2*vertices, barrel_design, COLOR_ORANGE_RED, GL_FILL);

}

void Fuel_Refill::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    draw3DObject(this->barrel_body);
    draw3DObject(this->barrel_design);
}

void Fuel_Refill::tick(int ticks) {
    // this->rotation += 0.5f;
    // this->position.x -= speed;
    this->position.y = CHECKPOINT_HEIGHT + 5.0f * sin((float)ticks/10);
    this->update_box();
}

glm::vec3 Fuel_Refill::get_position(){
    return this->position;
}

bounding_box_t Fuel_Refill::get_box(){
    return this->box;
}

void Fuel_Refill::update_box(){
    this->box.position = this->position;
}

Health_Refill::Health_Refill(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    length = 0.5f;
    width = 2.4f;
    height = 2.4f;

    thickness = 0.5f;

    this->box.position = this->position;
    this->box.length = 2*length;
    this->box.width = 2*width;
    this->box.height = 2*height;

    GLfloat horizontal_line[3*3*12*4] = {
        0.0f,thickness,0.0f,
        0.0f,0.0f,0.0f,
        0.0f,0.0f,length,
        0.0f,thickness,0.0f,
        0.0f,thickness,length,
        0.0f,0.0f,length,
        0.0f,thickness,0.0f,
        0.0f,thickness,length,
        width,thickness,0.0f,
        width,thickness,length,
        0.0f,thickness,length,
        width,thickness,0.0f,
        width,thickness,length,
        width,0.0f,0.0f,
        width,thickness,0.0f,
        width,thickness,length,
        width,0.0f,0.0f,
        width,0.0f,length,
        0.0f,0.0f,0.0f,
        width,0.0f,0.0f,
        width,0.0f,length,
        0.0f,0.0f,0.0f,
        0.0f,0.0f,length,
        width,0.0f,length,
        0.0f,thickness,length,
        0.0f,0.0f,length,
        width,0.0f,length,
        0.0f,thickness,length,
        width,thickness,length,
        width,0.0f,length,
        0.0f,0.0f,0.0f,
        0.0f,thickness,0.0f,
        width,0.0f,0.0f,
        width,thickness,0.0f,
        0.0f,thickness,0.0f,
        width,0.0f,0.0f,
    };

    for(int i=3*3*12;i<3*3*12*2;i+=3){
        horizontal_line[i] = -horizontal_line[i-3*3*12];
        horizontal_line[i+1] = horizontal_line[i+1-3*3*12];
        horizontal_line[i+2] = horizontal_line[i+2-3*3*12];

    }

    for(int i=3*3*12*2;i<3*3*12*3;i+=3){
        horizontal_line[i] = -horizontal_line[i-3*3*12*2];
        horizontal_line[i+1] = horizontal_line[i+1-3*3*12*2];
        horizontal_line[i+2] = -horizontal_line[i+2-3*3*12*2];
    }

    for(int i=3*3*12*3;i<3*3*12*4;i+=3){
        horizontal_line[i] = horizontal_line[i-3*3*12*3];
        horizontal_line[i+1] = horizontal_line[i+1-3*3*12*3];
        horizontal_line[i+2] = -horizontal_line[i+2-3*3*12*3];

    }

    GLfloat vertical_line[3*3*12*4] = {
        0.0f,height,0.0f-length/2.0f,
        0.0f,0.0f,0.0f-length/2.0f,
        0.0f,0.0f,length-length/2.0f,
        0.0f,height,0.0f-length/2.0f,
        0.0f,height,length-length/2.0f,
        0.0f,0.0f,length-length/2.0f,
        0.0f,height,0.0f-length/2.0f,
        0.0f,height,length-length/2.0f,
        thickness,height,0.0f-length/2.0f,
        thickness,height,length-length/2.0f,
        0.0f,height,length-length/2.0f,
        thickness,height,0.0f-length/2.0f,
        thickness,height,length-length/2.0f,
        thickness,0.0f,0.0f-length/2.0f,
        thickness,height,0.0f-length/2.0f,
        thickness,height,length-length/2.0f,
        thickness,0.0f,0.0f-length/2.0f,
        thickness,0.0f,length-length/2.0f,
        0.0f,0.0f,0.0f-length/2.0f,
        thickness,0.0f,0.0f-length/2.0f,
        thickness,0.0f,length-length/2.0f,
        0.0f,0.0f,0.0f-length/2.0f,
        0.0f,0.0f,length-length/2.0f,
        thickness,0.0f,length-length/2.0f,
        0.0f,height,length-length/2.0f,
        0.0f,0.0f,length-length/2.0f,
        thickness,0.0f,length-length/2.0f,
        0.0f,height,length-length/2.0f,
        thickness,height,length-length/2.0f,
        thickness,0.0f,length-length/2.0f,
        0.0f,0.0f,0.0f-length/2.0f,
        0.0f,height,0.0f-length/2.0f,
        thickness,0.0f,0.0f-length/2.0f,
        thickness,height,0.0f-length/2.0f,
        0.0f,height,0.0f-length/2.0f,
        thickness,0.0f,0.0f-length/2.0f,
    };

    for(int i=3*3*12;i<3*3*12*2;i+=3){
        vertical_line[i] = -vertical_line[i-3*3*12];
        vertical_line[i+1] = -vertical_line[i+1-3*3*12];
        vertical_line[i+2] = vertical_line[i+2-3*3*12];

    }

    for(int i=3*3*12*2;i<3*3*12*3;i+=3){
        vertical_line[i] = -vertical_line[i-3*3*12*2];
        vertical_line[i+1] = vertical_line[i+1-3*3*12*2];
        vertical_line[i+2] = vertical_line[i+2-3*3*12*2];
    }

    for(int i=3*3*12*3;i<3*3*12*4;i+=3){
        vertical_line[i] = vertical_line[i-3*3*12*3];
        vertical_line[i+1] = -vertical_line[i+1-3*3*12*3];
        vertical_line[i+2] = vertical_line[i+2-3*3*12*3];

    }

    this->horizontal_line = create3DObject(GL_TRIANGLES, 12*3*4, horizontal_line, COLOR_DARK_RED, GL_FILL);
    this->vertical_line = create3DObject(GL_TRIANGLES, 12*3*4, vertical_line, COLOR_DARK_RED, GL_FILL);

}

void Health_Refill::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    draw3DObject(this->horizontal_line);
    draw3DObject(this->vertical_line);
}

void Health_Refill::tick(int ticks) {
    this->rotation += 1.0f;
    // this->position.x -= speed;
    // this->position.y = CHECKPOINT_HEIGHT + 5.0f * sin((float)ticks/10);
    this->update_box();
}

glm::vec3 Health_Refill::get_position(){
    return this->position;
}

bounding_box_t Health_Refill::get_box(){
    return this->box;
}

void Health_Refill::update_box(){
    this->box.position = this->position;
}