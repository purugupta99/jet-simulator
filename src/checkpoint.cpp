#include "checkpoint.h"
#include "main.h"

Checkpoint::Checkpoint(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    body_length = 40.0f;
    body_radius = 10.0f;

    cone_length = 20.0f;
    cone_radius = 20.0f;

    int vertices = 50;

    GLfloat arrow_body[9*2*vertices];
    GLfloat arrow_head[9*vertices];

	int num = 0;

	for(int i=0;i<9*2*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;

        arrow_body[i] = body_radius * cos(angle);
        arrow_body[i+1] = -body_length;
        arrow_body[i+2] = body_radius* sin(angle);
        arrow_body[i+3] = body_radius * cos(angle);
        arrow_body[i+4] = body_length;
        arrow_body[i+5] = body_radius* sin(angle);
        arrow_body[i+6] = body_radius * cos(angle2);
        arrow_body[i+7] = body_length;
        arrow_body[i+8] = body_radius * sin(angle2);

        i+=9;

        arrow_body[i] = body_radius * cos(angle2);
        arrow_body[i+1] = body_length;
        arrow_body[i+2] = body_radius * sin(angle2);
        arrow_body[i+3] = body_radius * cos(angle);
        arrow_body[i+4] = -body_length;
        arrow_body[i+5] = body_radius* sin(angle);
        arrow_body[i+6] = body_radius * cos(angle2);
        arrow_body[i+7] = -body_length;
        arrow_body[i+8] = body_radius * sin(angle2);
        

		num ++;
	}

    num = 0;

	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
        
            arrow_head[i] = 0.0f;
            arrow_head[i+1] = -body_length - cone_length;
            arrow_head[i+2] = 0.0f;
            arrow_head[i+3] = cone_radius * cos(angle);
            arrow_head[i+4] = -body_length;
            arrow_head[i+5] = cone_radius* sin(angle);
            arrow_head[i+6] = cone_radius * cos(angle2);
            arrow_head[i+7] = -body_length;
            arrow_head[i+8] = cone_radius * sin(angle2);

		num ++;
	}

    

    this->arrow_body = create3DObject(GL_TRIANGLES, 3*2*vertices, arrow_body, COLOR_DARK_RED, GL_FILL);
    this->arrow_head = create3DObject(GL_TRIANGLES, 3*vertices, arrow_head, COLOR_DARK_RED, GL_FILL);

}

void Checkpoint::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->arrow_body);
    draw3DObject(this->arrow_head);
}

void Checkpoint::tick(int ticks) {
    // this->rotation += 0.5f;
    // this->position.x -= speed;
    this->position.y = CHECKPOINT_HEIGHT + 5.0f * sin((float)ticks/75);
}

glm::vec3 Checkpoint::get_position(){
    return this->position;
}
