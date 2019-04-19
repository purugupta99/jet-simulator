#include "volcano.h"
#include "main.h"

Volcano::Volcano(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;

    this->visible = true;
    island_radius = 35.0f;
    island_height = 1.0f;
    volcano_radius = 25.0f;
    volcano_height = 40.0f;
    lava_radius = 10.0f;
    lava_height = 16.0f;

    // this->box.x = x;
    // this->box.y = y + volcano_height/2.0f;
    // this->box.z = z;

    this->box.position = this->position;
    this->box.position.y += volcano_height/2.0f;


    this->box.length = 2*island_radius;
    this->box.width = 2*island_radius;
    this->box.height = (island_height + volcano_height + 10.0f)*5;

    int vertices = 75;

	GLfloat island[9*2*vertices + 9*vertices];
	GLfloat volcano[9*vertices];
	GLfloat lava[9*vertices];


	int num = 0;

	for(int i=0;i<9*2*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;

        island[i] = island_radius * cos(angle);
        island[i+1] = -island_height;
        island[i+2] = island_radius* sin(angle);
        island[i+3] = island_radius * cos(angle);
        island[i+4] = island_height;
        island[i+5] = island_radius* sin(angle);
        island[i+6] = island_radius * cos(angle2);
        island[i+7] = island_height;
        island[i+8] = island_radius * sin(angle2);

        i+=9;

        island[i] = island_radius * cos(angle2);
        island[i+1] = island_height;
        island[i+2] = island_radius * sin(angle2);
        island[i+3] = island_radius * cos(angle);
        island[i+4] = -island_height;
        island[i+5] = island_radius* sin(angle);
        island[i+6] = island_radius * cos(angle2);
        island[i+7] = -island_height;
        island[i+8] = island_radius * sin(angle2);
        

		num ++;
	}

    num = 0;

	for(int i=9*2*vertices;i<9*2*vertices + 9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
		island[i] =0.0f;
		island[i+1] =island_height;
		island[i+2] =0.0f;
		island[i+3] =island_radius * cos(angle);
		island[i+4] =island_height;
		island[i+5] =island_radius* sin(angle);
		island[i+6] =island_radius * cos(angle2);
		island[i+7] =island_height;
		island[i+8] =island_radius * sin(angle2);

		num ++;
	}

    num = 0;

	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
        
            volcano[i] = 0.0f;
            volcano[i+1] = island_height + volcano_height;
            volcano[i+2] = 0.0f;
            volcano[i+3] = volcano_radius * cos(angle);
            volcano[i+4] = island_height;
            volcano[i+5] = volcano_radius* sin(angle);
            volcano[i+6] = volcano_radius * cos(angle2);
            volcano[i+7] = island_height;
            volcano[i+8] = volcano_radius * sin(angle2);

		num ++;
	}

    num = 0;

	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
        
            lava[i] = 0.0f;
            lava[i+1] = island_height + volcano_height + 0.01f;
            lava[i+2] = 0.0f;
            lava[i+3] = lava_radius * cos(angle);
            lava[i+4] = island_height + volcano_height - lava_height;
            lava[i+5] = lava_radius* sin(angle);
            lava[i+6] = lava_radius * cos(angle2);
            lava[i+7] = island_height + volcano_height - lava_height;
            lava[i+8] = lava_radius * sin(angle2);

		num ++;
	}


    this->island = create3DObject(GL_TRIANGLES, 2*vertices*3 + vertices*3, island, COLOR_GREEN, GL_FILL);
    this->volcano = create3DObject(GL_TRIANGLES, vertices*3, volcano, COLOR_BROWN, GL_FILL);
    this->lava = create3DObject(GL_TRIANGLES, vertices*3, lava, COLOR_DARK_FIRE, GL_FILL);

}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->island);
    draw3DObject(this->volcano);
    draw3DObject(this->lava);
}

void Volcano::tick() {
    // this->rotation += 0.5f;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

glm::vec3 Volcano::get_position(){
    return this->position;
}

bounding_box_t Volcano::get_box(){
    return this->box;
}

bool Volcano::get_visibility(){
    return this->visible;
}