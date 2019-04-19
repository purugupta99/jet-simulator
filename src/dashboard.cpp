#include "dashboard.h"
#include "main.h"

using namespace std;

Dashboard::Dashboard(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;
    this->visible = true;

    speedometer_x = -2.0f;
    speedometer_y = 3.50f;

    healthmeter_x = 1.5f; 
    healthmeter_y = 2.75f;

    altitude_x = 1.5;
    altitude_y = 3.25;

    fuelometer_x = 1.5f;
    fuelometer_y = 3.75f;

    compass_x = 0.5f;
    compass_y = 3.25f;

    map_x = -2.5f;
    map_y = -2.5f;

    map_radius = 1.0f;

    length_bar = 2.0f;
    height_bar = 0.25f;

    radius_speedometer = 1.5f;
    length_speedometer = 0.01f;
    offset_speedometer = 0.5f;

    length_speedometer_needle = 0.75f * radius_speedometer;
    length_compass_needle = 0.75f;

    int vertices = 50;
    GLfloat speedometer_body[9*2*vertices];

    GLfloat speedometer_needle[2*3*3] = {
        speedometer_x, speedometer_y, 0.0f,
        speedometer_x - 0.2f, speedometer_y - 0.15f, 0.0f,
        speedometer_x - 0.2f, speedometer_y + 0.15f, 0.0f,

        speedometer_x - 0.2f, speedometer_y - 0.15f, 0.0f,
        speedometer_x - 0.2f, speedometer_y + 0.15f, 0.0f,
        speedometer_x - length_speedometer_needle, speedometer_y, 0.0f,
    };

     GLfloat compass_needle[3*3*3] = {
        compass_x - 0.2f, compass_y, -length_compass_needle/2.0f,
        compass_x + 0.2f, compass_y, -length_compass_needle/2.0f,
        compass_x + 0.2f, compass_y, length_compass_needle/2.0f,

        compass_x - 0.2f, compass_y, -length_compass_needle/2.0f,
        compass_x - 0.2f, compass_y, length_compass_needle/2.0f,
        compass_x + 0.2f, compass_y, length_compass_needle/2.0f,

        compass_x - 0.4f, compass_y, length_compass_needle/2.0f,
        compass_x + 0.4f, compass_y, length_compass_needle/2.0f,
        compass_x       , compass_y, length_compass_needle/2.0f + sqrt(3)*0.4f,

    };

    int num = 0;
    GLfloat map [9*vertices];

	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
		map[i] = map_x + 0.0f;
		map[i+1] = map_y + 0.0f;
		map[i+2] = 0.0f;
		map[i+3] = map_x + map_radius * cos(angle);
		map[i+4] = map_y + map_radius * sin(angle);
		map[i+5] = 0.0f;
		map[i+6] = map_x + map_radius * cos(angle2);
		map[i+7] = map_y + map_radius * sin(angle2);
		map[i+8] = 0.0f;

		num ++;
	}

    num = vertices/2 ;

	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
        
            speedometer_body[i] = speedometer_x + radius_speedometer * cos(angle);
            speedometer_body[i+1] = speedometer_y + radius_speedometer* sin(angle);
            speedometer_body[i+2] = -length_speedometer;
            speedometer_body[i+3] = speedometer_x + radius_speedometer * cos(angle);
            speedometer_body[i+4] = speedometer_y + radius_speedometer* sin(angle);
            speedometer_body[i+5] = length_speedometer;
            speedometer_body[i+6] = speedometer_x + radius_speedometer * cos(angle2);
            speedometer_body[i+7] = speedometer_y + radius_speedometer * sin(angle2);
            speedometer_body[i+8] = length_speedometer;

            i+=9;

            speedometer_body[i] = speedometer_x + radius_speedometer * cos(angle2);
            speedometer_body[i+1] = speedometer_y + radius_speedometer * sin(angle2);
            speedometer_body[i+2] = length_speedometer;
            speedometer_body[i+3] = speedometer_x + radius_speedometer * cos(angle);
            speedometer_body[i+4] = speedometer_y + radius_speedometer* sin(angle);
            speedometer_body[i+5] = -length_speedometer;
            speedometer_body[i+6] = speedometer_x + radius_speedometer * cos(angle2);
            speedometer_body[i+7] = speedometer_y + radius_speedometer * sin(angle2);
            speedometer_body[i+8] = -length_speedometer;
        

		num ++;
	}

    this->speedometer_body = create3DObject(GL_LINES, vertices*3, speedometer_body, COLOR_GREEN, GL_FILL);
    this->speedometer_needle = create3DObject(GL_TRIANGLES, 6, speedometer_needle, COLOR_GREEN, GL_FILL);
    this->compass_needle = create3DObject(GL_TRIANGLES, 9, compass_needle, COLOR_GREEN, GL_FILL);
    this->map = create3DObject(GL_TRIANGLES, 3*vertices, map, COLOR_CREAM, GL_FILL);

    this->altitude_meter = create3DObject(GL_TRIANGLES, 6, speedometer_body, COLOR_YELLOW, GL_FILL);
    this->fuelo_meter = create3DObject(GL_TRIANGLES, 6, speedometer_body, COLOR_BROWN, GL_FILL);
    this->health_meter = create3DObject(GL_TRIANGLES, 6, speedometer_body, COLOR_RED, GL_FILL);

    this->map_volcano = create3DObject(GL_TRIANGLES, 0, speedometer_body, COLOR_RED, GL_FILL);
    this->map_cannon = create3DObject(GL_TRIANGLES, 0, speedometer_body, COLOR_YELLOW, GL_FILL);
    this->map_plane = create3DObject(GL_TRIANGLES, 6, speedometer_body, COLOR_GREEN, GL_FILL);

}

void Dashboard::draw(glm::mat4 VP) {

    float plane_y = plane_position.y;

    if(plane_y > MAX_ALT) plane_y = MAX_ALT;
    if(plane_y < MIN_ALT) plane_y = MIN_ALT;

    float altitude_ratio = plane_y/MAX_ALT;

    float fuel_left = remaining_fuel;

    if(fuel_left > MAX_FUEL) fuel_left = MAX_FUEL;
    if(fuel_left < MIN_FUEL) fuel_left = MIN_FUEL;

    float fuel_ratio = fuel_left/MAX_FUEL;

    float health_left = remaining_health;

    if(health_left > MAX_HEALTH) health_left = MAX_HEALTH;
    if(health_left < MIN_HEALTH) health_left = MIN_HEALTH;

    float health_ratio = health_left/MAX_HEALTH;

    GLfloat altitude_meter [] = {
        altitude_x, altitude_y , 0.0f,
        altitude_x + length_bar*altitude_ratio, altitude_y , 0.0f,
        altitude_x, altitude_y - height_bar, 0.0f,
        altitude_x + length_bar*altitude_ratio, altitude_y - height_bar, 0.0f,
        altitude_x + length_bar*altitude_ratio, altitude_y , 0.0f,
        altitude_x, altitude_y - height_bar, 0.0f,
        
    };

    GLfloat fuelo_meter [] = {
        fuelometer_x, fuelometer_y , 0.0f,
        fuelometer_x + length_bar*fuel_ratio, fuelometer_y , 0.0f,
        fuelometer_x, fuelometer_y - height_bar, 0.0f,
        fuelometer_x + length_bar*fuel_ratio, fuelometer_y - height_bar, 0.0f,
        fuelometer_x + length_bar*fuel_ratio, fuelometer_y , 0.0f,
        fuelometer_x, fuelometer_y - height_bar, 0.0f,
        
    };

    GLfloat health_meter [] = {
        healthmeter_x, healthmeter_y , 0.0f,
        healthmeter_x + length_bar*health_ratio, healthmeter_y , 0.0f,
        healthmeter_x, healthmeter_y - height_bar, 0.0f,
        healthmeter_x + length_bar*health_ratio, healthmeter_y - height_bar, 0.0f,
        healthmeter_x + length_bar*health_ratio, healthmeter_y , 0.0f,
        healthmeter_x, healthmeter_y - height_bar, 0.0f,
        
    };

    // delete this->altitude_meter;
    // delete this->fuelo_meter;
    // delete this->health_meter;

    this->altitude_meter = create3DObject(GL_TRIANGLES, 6, altitude_meter, COLOR_YELLOW, GL_FILL);
    this->fuelo_meter = create3DObject(GL_TRIANGLES, 6, fuelo_meter, COLOR_BROWN, GL_FILL);
    this->health_meter = create3DObject(GL_TRIANGLES, 6, health_meter, COLOR_RED, GL_FILL);

    glm::vec3 new_z = dashboard_direction;
    glm::vec3 temp = glm::cross(dashboard_direction, up);
    new_z = glm::normalize(new_z);
    
    // glm::vec3 x = glm::vec3(1,0,0);
    glm::vec3 new_y = glm::cross(dashboard_direction, temp);
    glm::vec3 new_x = glm::cross(new_y,new_z);

    new_x = glm::normalize(new_x);
    new_y = glm::normalize(new_y);
    new_z = glm::normalize(new_z);


    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 translate_origin = glm::translate (glm::vec3(0.0f,0.0f,0.0f));    // glTranslatef

    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));

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
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate );

    // Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    draw3DObject(this->altitude_meter);
    draw3DObject(this->fuelo_meter);
    draw3DObject(this->health_meter);
    draw3DObject(this->speedometer_body);
    // draw3DObject(this->compass_needle);
    // draw3DObject(this->speedometer_needle);
}

void Dashboard::draw_needle(glm::mat4 VP) {

    float velocity = abs(plane_velocity.z);

    if(velocity < MIN_VEL) velocity = MIN_VEL;
    if(velocity > MAX_VEL) velocity = MAX_VEL;

    glm::vec3 new_z = dashboard_direction;
    glm::vec3 temp = glm::cross(dashboard_direction, up);
    new_z = glm::normalize(new_z);
    
    // glm::vec3 x = glm::vec3(1,0,0);
    glm::vec3 new_y = glm::cross(dashboard_direction, temp);
    glm::vec3 new_x = glm::cross(new_y,new_z);

    new_x = glm::normalize(new_x);
    new_y = glm::normalize(new_y);
    new_z = glm::normalize(new_z);


    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 translate_origin = glm::translate (glm::vec3(-speedometer_x,-speedometer_y,0.0f));    // glTranslatef
    glm::mat4 translate_back = glm::translate (glm::vec3(speedometer_x,speedometer_y,0.0f));    // glTranslatef

    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));

    float rotation = velocity/MAX_VEL;
    glm::mat4 rotate = glm::rotate((float) (0.0f * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate[0][0]= new_x.x;
    rotate[0][1]= new_x.y;
    rotate[0][2]= new_x.z;

    rotate[1][0]= new_y.x;
    rotate[1][1]= new_y.y;
    rotate[1][2]= new_y.z;

    rotate[2][0]= new_z.x;
    rotate[2][1]= new_z.y;
    rotate[2][2]= new_z.z;

    // glm::mat4 rotate_needle = glm::rotate((float) (rotation * 2 * M_PI ), glm::vec3(0,0,1));
    // glm::mat4 rotate_needle = glm::rotate((float) (rotation * 2 * M_PI ), glm::vec3(rotate[2][0], rotate[2][1], rotate[2][2]));
    glm::mat4 rotate_needle = glm::rotate((float) (rotation * M_PI ), glm::vec3(0,0,1));

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate_origin );
    Matrices.model *= (translate * rotate * translate_back * rotate_needle * translate_origin);

    // Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    draw3DObject(this->speedometer_needle);
}

void Dashboard::draw_map(glm::mat4 VP) {


    GLfloat map_volcano[TOTAL_VOLCANO*6*9];
    GLfloat map_cannon[TOTAL_CANNON*6*9];
    GLfloat map_plane[6*9];

    int volcano_vertex=0;
    for(int i=0;i<this->volcano_position.size();i++){
        // if(glm::distance(plane_position,this->volcano_position[i]) < 100.0f){
            map_volcano[volcano_vertex]=map_x + this->volcano_position[i].x/2000.0f + 0.02f;
            map_volcano[volcano_vertex+1]=map_y - this->volcano_position[i].y/2000.0f + 0.02f;
            map_volcano[volcano_vertex+2]= -0.05f;
            map_volcano[volcano_vertex+3]=map_x + this->volcano_position[i].x/2000.0f - 0.02f;
            map_volcano[volcano_vertex+4]=map_y - this->volcano_position[i].y/2000.0f + 0.02f;
            map_volcano[volcano_vertex+5]= -0.05f;
            map_volcano[volcano_vertex+6]=map_x + this->volcano_position[i].x/2000.0f - 0.02f;
            map_volcano[volcano_vertex+7]=map_y - this->volcano_position[i].y/2000.0f - 0.02f;
            map_volcano[volcano_vertex+8]= -0.05f;
            map_volcano[volcano_vertex+9]=map_x + this->volcano_position[i].x/2000.0f - 0.02f;
            map_volcano[volcano_vertex+10]=map_y - this->volcano_position[i].y/2000.0f - 0.02f;
            map_volcano[volcano_vertex+11]= -0.05f;
            map_volcano[volcano_vertex+12]=map_x + this->volcano_position[i].x/2000.0f + 0.02f;
            map_volcano[volcano_vertex+13]=map_y - this->volcano_position[i].y/2000.0f + 0.02f;
            map_volcano[volcano_vertex+14]= -0.05f;
            map_volcano[volcano_vertex+15]=map_x + this->volcano_position[i].x/2000.0f + 0.02f;
            map_volcano[volcano_vertex+16]=map_y - this->volcano_position[i].y/2000.0f - 0.02f;
            map_volcano[volcano_vertex+17]= -0.05f;

            volcano_vertex+=18;
        // }
    }

    int cannon_vertex=0;
    for(int i=0;i<this->cannon_position.size();i++){
        // if(glm::distance(plane_position,this->volcano_position[i]) < 100.0f){
            map_cannon[cannon_vertex]=map_x + this->cannon_position[i].x/2000.0f + 0.02f;
            map_cannon[cannon_vertex+1]=map_y - this->cannon_position[i].y/2000.0f + 0.02f;
            map_cannon[cannon_vertex+2]= -0.05f;
            map_cannon[cannon_vertex+3]=map_x + this->cannon_position[i].x/2000.0f - 0.02f;
            map_cannon[cannon_vertex+4]=map_y - this->cannon_position[i].y/2000.0f + 0.02f;
            map_cannon[cannon_vertex+5]= -0.05f;
            map_cannon[cannon_vertex+6]=map_x + this->cannon_position[i].x/2000.0f - 0.02f;
            map_cannon[cannon_vertex+7]=map_y - this->cannon_position[i].y/2000.0f - 0.02f;
            map_cannon[cannon_vertex+8]= -0.05f;
            map_cannon[cannon_vertex+9]=map_x + this->cannon_position[i].x/2000.0f - 0.02f;
            map_cannon[cannon_vertex+10]=map_y - this->cannon_position[i].y/2000.0f - 0.02f;
            map_cannon[cannon_vertex+11]= -0.05f;
            map_cannon[cannon_vertex+12]=map_x + this->cannon_position[i].x/2000.0f + 0.02f;
            map_cannon[cannon_vertex+13]=map_y - this->cannon_position[i].y/2000.0f + 0.02f;
            map_cannon[cannon_vertex+14]= -0.05f;
            map_cannon[cannon_vertex+15]=map_x + this->cannon_position[i].x/2000.0f + 0.02f;
            map_cannon[cannon_vertex+16]=map_y - this->cannon_position[i].y/2000.0f - 0.02f;
            map_cannon[cannon_vertex+17]= -0.05f;

            cannon_vertex+=18;
        // }
    }

    
    map_plane[0] = map_x + plane_position.x/2000.0f + 0.04f;
    map_plane[1] = map_y + plane_position.z/2000.0f;
    map_plane[2] = -0.05f;
    map_plane[3] = map_x + plane_position.x/2000.0f;
    map_plane[4] = map_y + plane_position.z/2000.0f + 0.06f;
    map_plane[5] = -0.05f;
    map_plane[6] = map_x + plane_position.x/2000.0f - 0.04f;
    map_plane[7] = map_y + plane_position.z/2000.0f;
    map_plane[8] = -0.05f;
    map_plane[9] = map_x +plane_position.x/2000.0f + 0.04f;
    map_plane[10] = map_y+ plane_position.z/2000.0f;
    map_plane[11] = -0.05f;
    map_plane[12] = map_x + plane_position.x/2000.0f;
    map_plane[13] = map_y + plane_position.z/2000.0f - 0.06f;
    map_plane[14] = -0.05f;
    map_plane[15] = map_x + plane_position.x/2000.0f - 0.04;
    map_plane[16] = map_y + plane_position.z/2000.0f;
    map_plane[17] = -0.05f;

    if(plane_position.x/2000.0f > map_radius){
        map_plane[0] -= (plane_position.x/2000.0f - map_radius);
        map_plane[3] -= (plane_position.x/2000.0f - map_radius);
        map_plane[6] -= (plane_position.x/2000.0f - map_radius);
        map_plane[9] -= (plane_position.x/2000.0f - map_radius);
        map_plane[12] -= (plane_position.x/2000.0f - map_radius);
        map_plane[15] -= (plane_position.x/2000.0f - map_radius);
    }
    if(plane_position.x/2000.0f < -map_radius){
        map_plane[0] -= (plane_position.x/2000.0f + map_radius);
        map_plane[3] -= (plane_position.x/2000.0f + map_radius);
        map_plane[6] -= (plane_position.x/2000.0f + map_radius);
        map_plane[9] -= (plane_position.x/2000.0f + map_radius);
        map_plane[12] -= (plane_position.x/2000.0f + map_radius);
        map_plane[15] -= (plane_position.x/2000.0f + map_radius);
    }

    if(plane_position.z/2000.0f < map_radius){
        map_plane[1] -= (plane_position.z/2000.0f - map_radius);
        map_plane[4] -= (plane_position.z/2000.0f - map_radius);
        map_plane[7] -= (plane_position.z/2000.0f - map_radius);
        map_plane[10] -= (plane_position.z/2000.0f - map_radius);
        map_plane[13] -= (plane_position.z/2000.0f - map_radius);
        map_plane[16] -= (plane_position.z/2000.0f - map_radius);
    }
    if(plane_position.z/2000.0f > -map_radius){
        map_plane[1] -= (plane_position.z/2000.0f + map_radius);
        map_plane[4] -= (plane_position.z/2000.0f + map_radius);
        map_plane[7] -= (plane_position.z/2000.0f + map_radius);
        map_plane[10] -= (plane_position.z/2000.0f + map_radius);
        map_plane[13] -= (plane_position.z/2000.0f + map_radius);
        map_plane[16] -= (plane_position.z/2000.0f + map_radius);
    }
    // cout << k << "\n";

    // delete this->map_volcano;
    // delete this->map_cannon;
    // delete this->map_plane;
    this->map_volcano = create3DObject(GL_TRIANGLES, volcano_vertex/3, map_volcano, COLOR_RED, GL_FILL);
    this->map_cannon = create3DObject(GL_TRIANGLES, cannon_vertex/3, map_cannon, COLOR_YELLOW, GL_FILL);
    this->map_plane = create3DObject(GL_TRIANGLES, 6, map_plane, COLOR_GREEN, GL_FILL);
    

    glm::vec3 new_z = dashboard_direction;
    glm::vec3 temp = glm::cross(dashboard_direction, up);
    new_z = glm::normalize(new_z);

    glm::vec3 new_y = glm::cross(dashboard_direction, temp);
    glm::vec3 new_x = glm::cross(new_y,new_z);

    new_x = glm::normalize(new_x);
    new_y = glm::normalize(new_y);
    new_z = glm::normalize(new_z);


    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef   // glTranslatef
    glm::mat4 translate_origin = glm::translate (glm::vec3(-map_x,-map_y,0.0f));    // glTranslatef
    glm::mat4 translate_back = glm::translate (glm::vec3(map_x,map_y,0.0f)); 

    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));

    
    glm::mat4 rotate = glm::rotate((float) (0.0f * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate_map = glm::rotate((float) (0.0f * M_PI / 180.0f), glm::vec3(0, 0, 1));

    rotate[0][0]= new_x.x;
    rotate[0][1]= new_x.y;
    rotate[0][2]= new_x.z;

    rotate[1][0]= new_y.x;
    rotate[1][1]= new_y.y;
    rotate[1][2]= new_y.z;

    rotate[2][0]= new_z.x;
    rotate[2][1]= new_z.y;
    rotate[2][2]= new_z.z;

    // glm::mat4 rotate_needle = glm::rotate((float) (rotation * 2 * M_PI ), glm::vec3(0,0,1));
    // glm::mat4 rotate_needle = glm::rotate((float) (rotation * 2 * M_PI ), glm::vec3(rotate[2][0], rotate[2][1], rotate[2][2]));

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate_origin );
    Matrices.model *= (translate * rotate * translate_back * rotate_map * translate_origin);

    // Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    // draw3DObject(this->map);
    draw3DObject(this->map_volcano);
    draw3DObject(this->map_cannon);
    draw3DObject(this->map_plane);
}

void Dashboard::draw_compass_needle(glm::mat4 VP) {

    glm::vec3 new_z = dashboard_direction;
    glm::vec3 temp = glm::cross(dashboard_direction, up);
    new_z = glm::normalize(new_z);
    
    // glm::vec3 x = glm::vec3(1,0,0);
    glm::vec3 new_y = glm::cross(dashboard_direction, temp);
    glm::vec3 new_x = glm::cross(new_y,new_z);

    new_x = glm::normalize(new_x);
    new_y = glm::normalize(new_y);
    new_z = glm::normalize(new_z);


    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 translate_origin = glm::translate (glm::vec3(-compass_x,-compass_y,0.0f));    // glTranslatef
    glm::mat4 translate_back = glm::translate (glm::vec3(compass_x,compass_y,0.0f));    // glTranslatef

    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));

    glm::mat4 rotate = glm::rotate((float) (0.0f * M_PI / 180.0f), glm::vec3(0, 1, 0));
    rotate[0][0]= new_x.x;
    rotate[0][1]= new_x.y;
    rotate[0][2]= new_x.z;

    rotate[1][0]= new_y.x;
    rotate[1][1]= new_y.y;
    rotate[1][2]= new_y.z;

    rotate[2][0]= new_z.x;
    rotate[2][1]= new_z.y;
    rotate[2][2]= new_z.z;


    glm::vec3 y_axis = glm::vec3(0,1,0);
    glm::vec3 z_axis = glm::vec3(0,0,1);

    float dot = glm::dot(z_axis, forward_direction);
    float det = glm::dot(y_axis,glm::cross(z_axis, forward_direction));

    // float rotation = -acos(forward_direction.z);
    float rotation = atan2(det, dot);
    glm::mat4 rotate_needle = glm::rotate((float) (rotation), glm::vec3(0,1,0));

    // std::cout << rotation << "\n";
    // glm::mat4 rotate_needle = glm::rotate((float) (rotation * 2 * M_PI ), glm::vec3(0,0,1));
    // glm::mat4 rotate_needle = glm::rotate((float) (rotation * 2 * M_PI ), glm::vec3(rotate[2][0], rotate[2][1], rotate[2][2]));
    
    // glm::vec3 north_direction = glm::vec3(0,plane_position.y,1000) - plane_position;
    // new_z = glm::normalize(-north_direction);

    // glm::vec3 x = glm::vec3(1,0,0);
    // new_y = glm::cross(new_z,x);
    // new_x = glm::cross(new_y,new_z);

    // new_x = glm::normalize(new_x);
    // new_y = glm::normalize(new_y);
    // new_z = glm::normalize(new_z);

    // glm::mat4 rotate_needle = glm::mat4(1.0f);

    // rotate_needle[0][0]= new_x.x;
    // rotate_needle[0][1]= new_x.y;
    // rotate_needle[0][2]= new_x.z;

    // rotate_needle[1][0]= new_y.x;
    // rotate_needle[1][1]= new_y.y;
    // rotate_needle[1][2]= new_y.z;

    // rotate_needle[2][0]= new_z.x;
    // rotate_needle[2][1]= new_z.y;
    // rotate_needle[2][2]= new_z.z;


    

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * translate_back * rotate_needle * translate_origin);
    // Matrices.model *= (translate  * translate_origin);

    // Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    draw3DObject(this->compass_needle);
}


void Dashboard::tick() {
    dashboard_direction = target - eye;
    dashboard_direction = glm::normalize(dashboard_direction);
    this->position = eye + dashboard_direction*4.0f;

    // std::cout << eye.x << " " << eye.y << " " << eye.z << "\n";

    // std::cout << this->position.x << " " << this->position.y << " " << this->position.z << "\n";

    // this->rotation += 0.5f;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

glm::vec3 Dashboard::get_position(){
    return this->position;
}

bounding_box_t Dashboard::get_box(){
    return this->box;
}

bool Dashboard::get_visibility(){
    return this->visible;
}

void Dashboard::update_box(){
    this->box.position = this->position;
}

void Dashboard::update_map(vector <pair<int, pair <float,float> > >locations){
    this->locations = locations;
    this->volcano_position.clear();
    this->cannon_position.clear();

    for(int i=0;i<this->locations.size();i++)
    {
        // std::cout << locations.size() << "\n";
        if(this->locations[i].first == VOLCANO){
            this->volcano_position.push_back(glm::vec3(this->locations[i].second.first,this->locations[i].second.second,0.0f));
        }else if(this->locations[i].first == ENEMY_CANNON){
            this->cannon_position.push_back(glm::vec3(this->locations[i].second.first,this->locations[i].second.second,0.0f));
        }
    }
}

void Dashboard::free_memory(){
    // delete [] this;
    delete [] this->map_volcano;
    delete [] this->map_cannon;
    delete [] this->map_plane;

    delete [] this->altitude_meter;
    delete [] this->fuelo_meter;
    delete [] this->health_meter;

    // free(this->map_volcano);
    // free(this->map_cannon);
    // free(this->map_plane);

    // free(this->altitude_meter);
    // free(this->fuelo_meter);
    // free(this->health_meter);

    this->map_volcano = NULL;
    this->map_cannon = NULL;
    this->map_plane = NULL;

    this->altitude_meter = NULL;
    this->fuelo_meter = NULL;
    this->health_meter = NULL;
}