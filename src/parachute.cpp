#include "parachute.h"
#include "main.h"

Parachute::Parachute(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->velocity = glm::vec3(0.0f, -0.1f, 0.0f);
    this->rotation = 0.0f;

    this->visible = true;
    
    parachute_radius = 7.5f;
    parachute_height = 5.0f;
    rope_length = 10.0f;
    drop_radius = 2.5f;
    drop_height = 2.5f;
    

    // this->box.x = x;
    // this->box.y = y + parachute_height/2.0f;
    // this->box.z = z;

    this->box.position = this->position;
    this->box.position.y -= 3.75f;


    this->box.length = 2*parachute_radius;
    this->box.width = 2*parachute_radius;
    this->box.height = rope_length + parachute_height + drop_height;

    int vertices = 6;

	GLfloat parachute_top[9*vertices];
	GLfloat parachute_design[6*vertices];
	GLfloat parachute_rope[6*vertices];
	GLfloat parachute_drop[9*2*vertices + 9*2*vertices];

	int num = 0;

	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
        
            parachute_top[i] = 0.0f;
            parachute_top[i+1] = parachute_height;
            parachute_top[i+2] = 0.0f;
            parachute_top[i+3] = parachute_radius * cos(angle);
            parachute_top[i+4] = 0.0f;
            parachute_top[i+5] = parachute_radius* sin(angle);
            parachute_top[i+6] = parachute_radius * cos(angle2);
            parachute_top[i+7] = 0.0f;
            parachute_top[i+8] = parachute_radius * sin(angle2);

		num ++;
	}

    num = 0;

	for(int i=0;i<6*vertices;i+=6)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
        
        parachute_design[i] = 0.0f;
        parachute_design[i+1] = parachute_height;
        parachute_design[i+2] = 0.0f;
        parachute_design[i+3] = parachute_radius * cos(angle);
        parachute_design[i+4] = 0.0f;
        parachute_design[i+5] = parachute_radius* sin(angle);

		num ++;
	}

    for(int i=0;i<6*vertices;i+=6)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
        
        parachute_rope[i] = drop_radius * cos(angle);
        parachute_rope[i+1] = -rope_length;
        parachute_rope[i+2] = drop_radius * sin(angle);
        parachute_rope[i+3] = parachute_radius * cos(angle);
        parachute_rope[i+4] = 0.0f;
        parachute_rope[i+5] = parachute_radius* sin(angle);

		num ++;
	}

    num = 0;

	for(int i=0;i<9*2*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;

        parachute_drop[i] = drop_radius * cos(angle);
        parachute_drop[i+1] = -rope_length;
        parachute_drop[i+2] = drop_radius* sin(angle);
        parachute_drop[i+3] = drop_radius * cos(angle);
        parachute_drop[i+4] = -(rope_length + drop_height);
        parachute_drop[i+5] = drop_radius* sin(angle);
        parachute_drop[i+6] = drop_radius * cos(angle2);
        parachute_drop[i+7] = -(rope_length + drop_height);
        parachute_drop[i+8] = drop_radius * sin(angle2);

        i+=9;

        parachute_drop[i] = drop_radius * cos(angle2);
        parachute_drop[i+1] = -(rope_length + drop_height);
        parachute_drop[i+2] = drop_radius * sin(angle2);
        parachute_drop[i+3] = drop_radius * cos(angle);
        parachute_drop[i+4] = -(rope_length  + drop_height);
        parachute_drop[i+5] = drop_radius* sin(angle);
        parachute_drop[i+6] = drop_radius * cos(angle2);
        parachute_drop[i+7] = -rope_length;
        parachute_drop[i+8] = drop_radius * sin(angle2);
        

		num ++;
	}

     num = 0;

	for(int i=9*2*vertices; i<9*2*vertices + 9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
		parachute_drop[i] =0.0f;
		parachute_drop[i+1] = -rope_length;
		parachute_drop[i+2] =0.0f;
		parachute_drop[i+3] = drop_radius * cos(angle);
		parachute_drop[i+4] = -rope_length;
		parachute_drop[i+5] = drop_radius* sin(angle);
		parachute_drop[i+6] = drop_radius * cos(angle2);
		parachute_drop[i+7] = -rope_length;
		parachute_drop[i+8] = drop_radius * sin(angle2);

		num ++;
	}

    for(int i=9*3*vertices; i<9*4*vertices; i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
		parachute_drop[i] =0.0f;
		parachute_drop[i+1] = -(rope_length + drop_height);
		parachute_drop[i+2] =0.0f;
		parachute_drop[i+3] = drop_radius * cos(angle);
		parachute_drop[i+4] = -(rope_length + drop_height);
		parachute_drop[i+5] = drop_radius* sin(angle);
		parachute_drop[i+6] = drop_radius * cos(angle2);
		parachute_drop[i+7] = -(rope_length + drop_height);
		parachute_drop[i+8] = drop_radius * sin(angle2);

		num ++;
	}

    this->parachute_top = create3DObject(GL_TRIANGLES, vertices*3, parachute_top, COLOR_PINK, GL_FILL);
    this->parachute_design = create3DObject(GL_LINES, vertices*2, parachute_design, COLOR_BLACK, GL_FILL);
    this->parachute_rope = create3DObject(GL_LINES, vertices*2, parachute_rope, COLOR_WHITE, GL_FILL);
    this->parachute_drop = create3DObject(GL_TRIANGLES, vertices*3*4, parachute_drop, COLOR_BROWN, GL_FILL);

}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->parachute_top);
    draw3DObject(this->parachute_design);
    draw3DObject(this->parachute_rope);
    draw3DObject(this->parachute_drop);
}

void Parachute::tick() {
    // this->rotation += 0.5f;
    this->position += this->velocity;
    this->update_box();
    // this->position.x -= speed;
    // this->position.y -= speed;
}

glm::vec3 Parachute::get_position(){
    return this->position;
}

bounding_box_t Parachute::get_box(){
    return this->box;
}

bool Parachute::get_visibility(){
    return this->visible;
}

void Parachute::update_box(){
    this->box.position = this->position;
}