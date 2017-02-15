#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <irrKlang.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace irrklang;

struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int NumVertices;
};
typedef struct VAO VAO;

struct COLOR {
    float r;
    float g;
    float b;
};
typedef struct COLOR COLOR;

COLOR grey = {168.0/255.0,168.0/255.0,168.0/255.0};
COLOR gold = {218.0/255.0,165.0/255.0,32.0/255.0};
COLOR red = {255.0/255.0,51.0/255.0,51.0/255.0};
COLOR coingold = {255.0/255.0,223.0/255.0,0.0/255.0};
COLOR lightgreen = {57/255.0,230/255.0,0/255.0};
COLOR darkgreen = {51/255.0,102/255.0,0/255.0};
COLOR black = {30/255.0,30/255.0,21/255.0};
COLOR blue = {0,0,1};
COLOR ball = {255/255.0,228/225.0,181/255.0};
COLOR darkbrown = {46/255.0,46/255.0,31/255.0};
COLOR lightbrown = {95/255.0,63/255.0,32/255.0};
COLOR brown1 = {117/255.0,78/255.0,40/255.0};
COLOR brown2 = {134/255.0,89/255.0,40/255.0};
COLOR brown3 = {46/255.0,46/255.0,31/255.0};
COLOR cratebrown = {153/255.0,102/255.0,0/255.0};
COLOR cratebrown1 = {121/255.0,85/255.0,0/255.0};
COLOR cratebrown2 = {102/255.0,68/255.0,0/255.0};
COLOR skyblue7 = {95/255.0,158/255.0,160/255.0};
COLOR skyblue6 = {175/255.0,238/255.0,238/255.0};
COLOR skyblue5 = {70/255.0,130/255.0,180/255.0};
COLOR skyblue4 = {30/255.0,144/255.0,255/255};
COLOR skyblue3 = {135/255.0,206/255.0,250/255};
COLOR skyblue2 = {0/255.0,0/255.0,125/255.0};
COLOR skyblue1 = {123/255.0,201/255.0,227/255.0};
COLOR skyblue = {132/255.0,217/255.0,245/255.0};
COLOR cloudwhite = {229/255.0,255/255.0,255/255.0};
COLOR cloudwhite1 = {204/255.0,255/255.0,255/255.0};
COLOR lightpink = {255/255.0,122/255.0,173/255.0};
COLOR darkpink = {255/255.0,51/255.0,119/255.0};
COLOR white = {255/255.0,255/255.0,255/255.0};
COLOR score = {117/255.0,78/255.0,40/255.0};
COLOR lightred = {117/255.0,78/255.0,71/255.0};
COLOR otherred = {178/255.0,34/255.0,34/255.0};

struct Game {
    string name;
    COLOR color;
    float x,y,z;
    VAO* object;
    float height,width,radius,depth;
    float anglex;
    float angley;
    float anglez;
    int status;
    float numx;
    float numy;
};
map <string, Game> tiles;
map <string, Game> tiles1;
map <string, Game> tiles2;
map <string, Game> background;
map <string, Game> cube;
map <string, Game> Score;
map <string, Game> heart;
map <string, Game> Bridges;
map <string, Game> prestart;
map <string, Game> background1;
int gamemap1[12][17]={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,6,0,0,0,1,1,1,1,1,1,1,0,1,1,1,0},
    {0,1,5,5,5,5,1,0,0,0,1,1,0,1,7,1,0},
    {0,1,5,5,5,5,1,1,1,1,1,4,0,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,0,2,2,3,0},
    {0,1,0,0,0,0,1,0,0,0,2,2,2,2,3,3,0},
    {0,1,0,0,0,0,1,0,0,0,2,2,2,2,3,3,0},
    {0,1,0,0,0,0,1,2,2,2,2,2,2,2,3,3,0},
    {0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0},
    {0,1,1,1,8,0,0,0,0,0,2,0,2,0,2,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
int gamemap3[12][17]={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,4,1,1,1,1,1,1,1,3,3,1,1,1,1,0,0},
    {0,0,0,0,0,0,1,1,1,3,3,0,0,2,1,0,0},
    {0,0,1,1,1,1,1,1,1,3,3,1,1,2,1,1,0},
    {0,0,1,1,1,0,0,1,2,0,0,0,0,1,1,1,0},
    {0,0,1,1,1,0,0,1,2,0,0,0,0,3,0,1,0},
    {0,0,1,1,2,0,0,1,2,0,0,0,0,3,0,1,0},
    {0,2,2,2,2,1,1,1,1,0,0,0,5,5,5,5,0},
    {0,2,2,2,1,2,1,2,2,2,0,0,5,2,2,2,0},
    {0,1,2,2,2,2,2,2,2,2,0,0,5,2,7,2,0},
    {0,0,0,1,2,2,1,0,0,6,0,0,5,2,2,2,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
int gamemap2[12][17]={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,4,0},
    {0,1,1,1,1,0,0,0,1,1,3,3,3,3,3,3,0},
    {0,1,1,1,1,0,0,0,1,2,3,2,2,2,2,2,0},
    {0,1,5,2,1,0,0,0,1,2,3,1,5,5,5,5,0},
    {0,2,5,2,2,1,1,1,1,2,3,1,5,1,1,1,0},
    {0,5,5,5,5,0,0,0,0,2,3,1,5,1,7,2,0},
    {0,5,5,5,5,0,0,0,0,2,3,1,5,1,2,2,0},
    {0,1,1,2,2,1,1,1,0,2,3,1,5,5,5,5,0},
    {0,1,1,2,2,0,0,2,0,2,3,1,1,1,1,1,0},
    {0,1,1,2,2,0,0,6,0,1,3,3,3,3,3,3,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
int gamemap[12][17]={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint MatrixID;
} Matrices;

int do_rot, floor_rel;;
GLuint programID;
double last_update_time, current_time;
glm::vec3 rect_pos, floor_pos;
float rectangle_rotation = 0;

/* Function to load Shaders - Use it as it is */
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path) {

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open())
	{
	    std::string Line = "";
	    while(getline(VertexShaderStream, Line))
		VertexShaderCode += "\n" + Line;
	    VertexShaderStream.close();
	}

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
	std::string Line = "";
	while(getline(FragmentShaderStream, Line))
	    FragmentShaderCode += "\n" + Line;
	FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    //    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    //    fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

    // Compile Fragment Shader
    //    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    //    fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

    // Link the program
    //    fprintf(stdout, "Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    //    fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void quit(GLFWwindow *window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void initGLEW(void){
    glewExperimental = GL_TRUE;
    if(glewInit()!=GLEW_OK){
	fprintf(stderr,"Glew failed to initialize : %s\n", glewGetErrorString(glewInit()));
    }
    if(!GLEW_VERSION_3_3)
	fprintf(stderr, "3.3 version not available\n");
}



/* Generate VAO, VBOs and return VAO handle */
struct VAO* create3DObject (GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat* color_buffer_data, GLenum fill_mode=GL_FILL)
{
    struct VAO* vao = new struct VAO;
    vao->PrimitiveMode = primitive_mode;
    vao->NumVertices = numVertices;
    vao->FillMode = fill_mode;

    // Create Vertex Array Object
    // Should be done after CreateWindow and before any other GL calls
    glGenVertexArrays(1, &(vao->VertexArrayID)); // VAO
    glGenBuffers (1, &(vao->VertexBuffer)); // VBO - vertices
    glGenBuffers (1, &(vao->ColorBuffer));  // VBO - colors

    glBindVertexArray (vao->VertexArrayID); // Bind the VAO 
    glBindBuffer (GL_ARRAY_BUFFER, vao->VertexBuffer); // Bind the VBO vertices 
    glBufferData (GL_ARRAY_BUFFER, 3*numVertices*sizeof(GLfloat), vertex_buffer_data, GL_STATIC_DRAW); // Copy the vertices into VBO
    glVertexAttribPointer(
                          0,                  // attribute 0. Vertices
                          3,                  // size (x,y,z)
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );

    glBindBuffer (GL_ARRAY_BUFFER, vao->ColorBuffer); // Bind the VBO colors 
    glBufferData (GL_ARRAY_BUFFER, 3*numVertices*sizeof(GLfloat), color_buffer_data, GL_STATIC_DRAW);  // Copy the vertex colors
    glVertexAttribPointer(
                          1,                  // attribute 1. Color
                          3,                  // size (r,g,b)
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );

    return vao;
}

/* Generate VAO, VBOs and return VAO handle - Common Color for all vertices */
struct VAO* create3DObject (GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode=GL_FILL)
{
    GLfloat* color_buffer_data = new GLfloat [3*numVertices];
    for (int i=0; i<numVertices; i++) {
        color_buffer_data [3*i] = red;
        color_buffer_data [3*i + 1] = green;
        color_buffer_data [3*i + 2] = blue;
    }

    return create3DObject(primitive_mode, numVertices, vertex_buffer_data, color_buffer_data, fill_mode);
}

/* Render the VBOs handled by VAO */
void draw3DObject (struct VAO* vao)
{
    // Change the Fill Mode for this object
    glPolygonMode (GL_FRONT_AND_BACK, vao->FillMode);

    // Bind the VAO to use
    glBindVertexArray (vao->VertexArrayID);

    // Enable Vertex Attribute 0 - 3d Vertices
    glEnableVertexAttribArray(0);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, vao->VertexBuffer);

    // Enable Vertex Attribute 1 - Color
    glEnableVertexAttribArray(1);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, vao->ColorBuffer);

    // Draw the geometry !
    glDrawArrays(vao->PrimitiveMode, 0, vao->NumVertices); // Starting from vertex 0; 3 vertices total -> 1 triangle
}

/**************************
 * Customizable functions *
 **************************/

float rectangle_rot_dir = 1;
bool rectangle_rot_status = true;
int up1=0,down1=0,right1=0,left1=0;
float eye_x,eye_y,eye_z;
float target_x,target_y,target_z;
int camera_follow=0;
int camera_follow_adjust=0;
int camera_top=0;
int camera_fps=0;
float camera_radius;
float camera_fov=1.3;
float fps_head_offset=0;
float fps_head_offset_x=0;
int camera_tower=1;
int camera_helicopter=0;
int camera_self=0;
int orient_right=0;
int orient_left=0;
int orient_forward=0;
int orient_backward=0;
int mouse_click=0,right_mouse_click=0;
int keyboard_press=0;
double mouse_pos_x, mouse_pos_y;
double prev_mouse_pos_x,prev_mouse_pos_y;
int bridge=0,bridge1=0;
int roundi=0;
int partition=0;
int moves=100;
int clock1=300;
int life=5;
int gamewin=0;
int gamelose=0;
float camera_rotation_angle = 90;
int toggle=0;
int toggle1=0;
int stage=1;
int hello=1;
float camera_zoom=0;
/* Render the scene with openGL */
/* Edit this function according to your assignment */
float angle;
int rep=0,fl=0;
/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */

/* Executed when window is resized to 'width' and 'height' */
/* Modify the bounds of the screen here in glm::ortho or Field of View in glm::Perspective */
void reshapeWindow (GLFWwindow* window, int width, int height)
{
    int fbwidth=width, fbheight=height;
    glfwGetFramebufferSize(window, &fbwidth, &fbheight);

    GLfloat fov = M_PI/2;

    // sets the viewport of openGL renderer
    glViewport (0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);

    // Store the projection matrix in a variable for future use
    // Perspective projection for 3D views
    Matrices.projection = glm::perspective(fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1f, 500.0f);

    // Ortho projection for 2D views
    //Matrices.projection = glm::ortho(-4.0f, 4.0f, -4.0f, 4.0f, 0.1f, 500.0f);
}
void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Function is called first on GLFW_PRESS.
    ISoundEngine* engine = createIrrKlangDevice();
    if (!engine)
    {
        printf("Could not startup engine\n");
    }

    // To play a sound, we only to call play2D(). The second parameter
    // tells the engine to play it looped.

    // play some sound stream, looped
    engine->play2D("irrKlang-64bit-1.5.0/media/jump.wav", false);
    if (action == GLFW_RELEASE) {
        switch (key) {
    case GLFW_KEY_UP:
        if(left1==0 && right1==0 && up1==0 && down1==0)
        {
            up1=1;
            down1=0;
            right1=0;
            left1=0;
            moves--;
        }
        break;
    case GLFW_KEY_DOWN:
        if(left1==0 && right1==0  && up1==0  && down1==0)
        {
            down1=1;
            up1=0;
            right1=0;
            left1=0;
            moves--;
        }
        break;
    case GLFW_KEY_LEFT:
        if(left1==0 && right1==0 && up1==0 && down1==0)
        {
            right1=0;
            left1=1;
            up1=0;
            down1=0;
            moves--;
        }
        break;
    case GLFW_KEY_RIGHT:
        if(left1==0 && right1==0 && up1==0 && down1==0)
        {
            right1=1;
            left1=0;
            up1=0;
            down1=0;
            moves--;
        }
        break;
    case GLFW_KEY_T:
        camera_top=1;
        camera_follow=0;
        camera_fps=0;
        camera_tower=0;
        camera_self=0;
        camera_helicopter=0;
        break;
    case GLFW_KEY_R:
        camera_top=0;
        camera_follow=0;
        camera_fps=0;
        camera_tower=1;
        camera_self=0;
        camera_helicopter=0;
        break;
    case GLFW_KEY_F:
        camera_top=0;
        camera_follow=1;
        camera_fps=0;
        camera_tower=0;
        camera_self=0;
        camera_helicopter=0;
        break;
    case GLFW_KEY_P:
        camera_top=0;
        camera_follow=0;
        camera_fps=0;
        camera_tower=0;
        camera_self=0;
        camera_helicopter=1;
        break;
 case GLFW_KEY_I:
    camera_top=0;
    camera_follow=0;
    camera_fps=0;
    camera_tower=0;
    camera_self=1;
    camera_helicopter=0;
    break;
	default:
	    break;
        }
    }
    else if (action == GLFW_PRESS) {
        switch (key) {
	case GLFW_KEY_ESCAPE:
	    quit(window);
	    break;
	default:
	    break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar (GLFWwindow* window, unsigned int key)
{
    ISoundEngine* engine = createIrrKlangDevice();
    if (!engine)
    {
        printf("Could not startup engine\n");
    }

    // To play a sound, we only to call play2D(). The second parameter
    // tells the engine to play it looped.

    // play some sound stream, looped
    engine->play2D("irrKlang-64bit-1.5.0/media/jump.wav", false);
    switch (key) {
    case 'Q':
    case 'q':
	quit(window);
	break;
    case 'a':
	   if(camera_follow==1 || camera_self==1)
       {
            orient_left=1;
            orient_right=0;
            orient_backward=0;
            orient_forward=0;
       }
	break;
    case 'd':
    	if(camera_follow==1 ||  camera_self==1)
           {
                orient_left=0;
                orient_right=1;
                orient_backward=0;
                orient_forward=0;
           }
	break;
    case 'w':
	   if(camera_follow==1 ||camera_self==1)
       {
            orient_left=0;
            orient_right=0;
            orient_backward=0;
            orient_forward=1;
       }
	break;
    case 's':
        if(camera_follow==1 || camera_self==1)
       {
            orient_left=0;
            orient_right=0;
            orient_backward=1;
            orient_forward=0;
       }
	break;
    case 'c':
        if(gamelose==1 || gamewin==1 || hello==1)
        {
           hello=0;
    	   gamelose=0;
           gamewin=0;
           stage=1;
           life=5;
           clock1=300;
           moves=100;
        }
	break;
    case 'j':
        if(cube["cube1"].x!=-12 || cube["cube2"].x!=-12)
        {
            roundi=1;
            cube["cube1"].x-=4;
            cube["cube2"].x-=4;
        }
        break;
    case 'm':
        if(cube["cube1"].z!=-16 || cube["cube2"].z!=-16)
        {
            roundi=1;
            cube["cube1"].z-=4;
            cube["cube2"].z-=4;
        }
        break;

    case 'n':
        if(cube["cube1"].x!=10 || cube["cube2"].x!=10)
        {
            roundi=1;
            cube["cube1"].x+=4;
            cube["cube2"].x+=4;
        }
        break;
    case 'b':
        if(cube["cube1"].z!=16 || cube["cube2"].z!=16)
        {
            roundi=1;
            cube["cube1"].z+=4;
            cube["cube2"].z+=4;
        }
        break;
    default:
	break;
    }
}

/* Executed when a mouse button is pressed/released */
void mouseButton (GLFWwindow* window, int button, int action, int mods)
{
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        if(action == GLFW_PRESS)
        {
            mouse_click=1;
            keyboard_press=0;
            right_mouse_click=0;
        }
        if(action == GLFW_RELEASE)
        {
            mouse_click=0;
        }
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        if(action == GLFW_PRESS)
        {
            right_mouse_click=1;
            keyboard_press=0;
            mouse_click=0;
        }
	    if(action == GLFW_RELEASE) 
        {
	       right_mouse_click=0;
	    }
	   break;
    default:
	break;
    }
}

VAO *rectangle, *cam, *floor_vao;

// Creates the rectangle object used in this sample code
void createRectangle (string name, float angle, COLOR color,COLOR color2,COLOR color3,COLOR color4,float x, float y,float z, float height, float width,float depth, string component,int status,float numx,float numy)
{
    // GL3 accepts only Triangles. Quads are not supported
    float w=width/2,h=height/2,d=depth/2;
    static const GLfloat vertex_buffer_data [] = {
	-w, h, d, 
	-w, -h, d, 
	w, -h, d,
	-w, h, d, 
	w, -h, d,
	w, h, d,
	w, h, d,
	w, -h, d,
	w, -h, -d,
	w, h, d,
	w, -h, -d,
	w, h, -d,
	w, h, -d,
	w, -h, -d,
	-w, -h, -d,
	w, h, -d,
	-w, -h, -d,
	-w, h, -d,
	-w, h, -d,
	-w, -h, -d,
	-w, -h, d, 
	-w, h, -d,
	-w, -h, d, 
	-w, h, d, 
	-w, h, -d,
	-w, h, d, 
	w, h, d,
	-w, h, -d,
	w, h, d,
	w, h, -d,
	-w, -h, d, 
	-w, -h, -d,
	w, -h, -d,
	-w, -h, d, 
	w, -h, -d,
	w, -h, d,
	-w, h, d,
	w, h, -d,
	w, h, -d,
    };

    static const GLfloat color_buffer_data [] = {
        color.r,color.g,color.b, // color 1
        color.r,color.g,color.b, // color 2
        color2.r,color2.g,color2.b, // color 3

        color2.r,color2.g,color2.b, // color 4
        color2.r,color2.g,color2.b, // color 5
        color.r,color.g,color.b, // color 6


        color.r,color.g,color.b, // color 1
        color.r,color.g,color.b, // color 2
        color2.r,color2.g,color2.b, // color 3

        color2.r,color2.g,color2.b, // color 4
        color2.r,color2.g,color2.b, // color 5
        color.r,color.g,color.b, // color 6

        color.r,color.g,color.b, // color 1
        color.r,color.g,color.b, // color 2
        color2.r,color2.g,color2.b, // color 3

        color2.r,color2.g,color2.b, // color 4
        color2.r,color2.g,color2.b, // color 5
        color.r,color.g,color.b, // color 6
        

        color.r,color.g,color.b, // color 1
        color.r,color.g,color.b, // color 2
        color2.r,color2.g,color2.b, // color 3

        color2.r,color2.g,color2.b, // color 4
        color2.r,color2.g,color2.b, // color 5
        color.r,color.g,color.b, // color 6
        
        color.r,color.g,color.b, // color 1
        color.r,color.g,color.b, // color 2
        color2.r,color2.g,color2.b, // color 3

        color2.r,color2.g,color2.b, // color 4
        color2.r,color2.g,color2.b, // color 5
        color.r,color.g,color.b, // color 6
        
        color.r,color.g,color.b, // color 1
        color.r,color.g,color.b, // color 2
        color2.r,color2.g,color2.b, // color 3

        color2.r,color2.g,color2.b, // color 4
        color2.r,color2.g,color2.b, // color 5
        color.r,color.g,color.b, // color 6=
    };

    // create3DObject creates and returns a handle to a VAO that can be used later
    rectangle = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color_buffer_data, GL_FILL);
    Game InstanceGame = {};
    InstanceGame.color = color;
    InstanceGame.name = name;
    InstanceGame.object = rectangle;
    InstanceGame.x=x;
    InstanceGame.y=y;
    InstanceGame.z=z;
    InstanceGame.height=height;
    InstanceGame.width=width;
    InstanceGame.depth=depth;
    InstanceGame.radius=(sqrt(height*height+width*width+depth*depth))/2;
    InstanceGame.anglex=angle;
    InstanceGame.angley=angle;
    InstanceGame.anglez=angle;
    InstanceGame.status=status;
    InstanceGame.numx=numx;
    InstanceGame.numy=numy;
    if(component=="tile")
        tiles[name]=InstanceGame;
    else if(component=="background1")
        background1[name]=InstanceGame;
    else if(component=="cube")
        cube[name]=InstanceGame;
}
void createCam ()
{
    // GL3 accepts only Triangles. Quads are not supported
    static const GLfloat vertex_buffer_data [] = {
	-0.1, 0, 0,
	0.1, 0, 0, 
	0, 0.1, 0,
    };

    static const GLfloat color_buffer_data [] = {
	1, 1, 1,
	1, 1, 1,
	1, 1, 1,
    };

    // create3DObject creates and returns a handle to a VAO that can be used later
    cam = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data, color_buffer_data, GL_LINE);
}
/*void createFloor ()
{
    // GL3 accepts only Triangles. Quads are not supported
    static const GLfloat vertex_buffer_data [] = {
	-2, -1, 2,
	2, -1, 2, 
	-2, -1, -2,
	-2, -1, -2,
	2, -1, 2, 
	2, -1, -2,
    };

    static const GLfloat color_buffer_data [] = {
	0.65, 0.165, 0.165,
	0.65, 0.165, 0.165,
	0.65, 0.165, 0.165,
	0.65, 0.165, 0.165,
	0.65, 0.165, 0.165,
	0.65, 0.165, 0.165,
    };

    // create3DObject creates and returns a handle to a VAO that can be used later
    floor_vao = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color_buffer_data, GL_FILL);
}*/

void createRectangle1 (string name, float angle, COLOR color,COLOR color2, float x, float y, float height, float width, string component,int status)
{
    // GL3 accepts only Triangles. Quads are not supported
    float w=width/2,h=height/2;
    GLfloat vertex_buffer_data [] = {
        -w,-h,0, // vertex 1
        -w,h,0, // vertex 2
        w,h,0, // vertex 3

        w,h,0, // vertex 3
        w,-h,0, // vertex 4
        -w,-h,0  // vertex 1
    };

    GLfloat color_buffer_data [] = {
        color.r,color.g,color.b, // color 1
        color.r,color.g,color.b, // color 2
        color2.r,color2.g,color2.b, // color 3

        color2.r,color2.g,color2.b, // color 4
        color2.r,color2.g,color2.b, // color 5
        color.r,color.g,color.b // color 6
    };

    // create3DObject creates and returns a handle to a VAO that can be used later
    VAO *rectangle = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);
    Game InstanceGame = {};
    InstanceGame.color = color;
    InstanceGame.name = name;
    InstanceGame.object = rectangle;
    InstanceGame.x=x;
    InstanceGame.y=y;
    InstanceGame.height=height;
    InstanceGame.width=width;
    InstanceGame.anglex=angle;
    InstanceGame.status=status;
    if(component=="background")
        background[name]=InstanceGame;
    else if(component=="score")
        Score[name]=InstanceGame;
}

void createtile (string name, float angle, COLOR color,COLOR color2,COLOR color3,COLOR color4,float x, float y,float z, float height, float width,float depth, string component,int status,float numx,float numy)
{
    // GL3 accepts only Triangles. Quads are not supported
    float w=width/2,h=height/2,d=depth/2;
    GLfloat vertex_buffer_data [] = {
        /*-w,-h,d, // vertex 1
        w,-h,d, // vertex 2
        -w,-h,-d, // vertex 3
        -w,-h,-d, // vertex 3
        w,-h,d, // vertex 4
        w,-h,-d  // vertex 1*/
        -w, h, d,
        -w, -h, d, 
        w, -h, d,
        -w, h, d, 
        w, -h, d,
        w, h, d,
        w, h, d,
        w, -h, d,
        w, -h, -d,
        w, h, d,
        w, -h, -d,
        w, h, -d,
        w, h, -d,
        w, -h, -d,
        -w, -h, -d,
        w, h, -d,
        -w, -h, -d,
        -w, h, -d,
        -w, h, -d,
        -w, -h, -d,
        -w, -h, d, 
        -w, h, -d,
        -w, -h, d, 
        -w, h, d, 
        -w, h, -d,
        -w, h, d, 
        w, h, d,
        -w, h, -d,
        w, h, d,
        w, h, -d,
        -w, -h, d, 
        -w, -h, -d,
        w, -h, -d,
        -w, -h, d, 
        w, -h, -d,
        w, -h, d,
        -w, h, d,
        w, h, -d,
        w, h, -d,
    };

    GLfloat color_buffer_data [] = {
        color4.r,color4.g,color4.b, // color 1
        color4.r,color4.g,color4.b, // color 2
        color4.r,color4.g,color4.b, // color 3

        color4.r,color4.g,color4.b, // color 4
        color4.r,color4.g,color4.b, // color 5
        color4.r,color4.g,color4.b, // color 6

        color4.r,color4.g,color4.b, // color 1
        color4.r,color4.g,color4.b, // color 2
        color4.r,color4.g,color4.b, // color 3

        color4.r,color4.g,color4.b, // color 4
        color4.r,color4.g,color4.b, // color 5
        color4.r,color4.g,color4.b, // color 6

        color4.r,color4.g,color4.b, // color 1
        color4.r,color4.g,color4.b, // color 2
        color4.r,color4.g,color4.b, // color 3

        color4.r,color4.g,color4.b, // color 4
        color4.r,color4.g,color4.b, // color 5
        color4.r,color4.g,color4.b, // color 6

        color4.r,color4.g,color4.b, // color 1
        color4.r,color4.g,color4.b, // color 2
        color4.r,color4.g,color4.b, // color 3

        color4.r,color4.g,color4.b, // color 4
        color4.r,color4.g,color4.b, // color 5
        color4.r,color4.g,color4.b, // color 6

        color.r,color.g,color.b, // color 1
        color2.r,color2.g,color2.b, // color 2
        color3.r,color3.g,color3.b, // color 3

        color3.r,color3.g,color3.b, // color 4
        color4.r,color4.g,color4.b, // color 5
        color.r,color.g,color.b, // color 6

        color.r,color.g,color.b, // color 1
        color2.r,color2.g,color2.b, // color 2
        color3.r,color3.g,color3.b, // color 3

        color3.r,color3.g,color3.b, // color 4
        color4.r,color4.g,color4.b, // color 5
        color.r,color.g,color.b, // color 6
    };

    // create3DObject creates and returns a handle to a VAO that can be used later
    VAO *tile = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color_buffer_data, GL_FILL);
    Game InstanceGame = {};
    InstanceGame.color = color;
    InstanceGame.name = name;
    InstanceGame.object = tile;
    InstanceGame.x=x;
    InstanceGame.y=y;
    InstanceGame.z=z;
    InstanceGame.height=height;
    InstanceGame.width=width;
    InstanceGame.depth=depth;
    InstanceGame.radius=(sqrt(height*height+width*width+depth*depth))/2;
    InstanceGame.anglex=angle;
    InstanceGame.status=status;
    InstanceGame.numx=numx;
    InstanceGame.numy=numy;
    if(component=="tile")
        tiles[name]=InstanceGame;
    else if(component=="tile1")
        tiles1[name]=InstanceGame;
    else if(component=="tile2")
        tiles2[name]=InstanceGame;
    else if(component=="background1")
        background1[name]=InstanceGame;
}
void createTriangle (string name, float angle, COLOR color, float x[], float y[], string component, int fill)
{
    /* ONLY vertices between the bounds specified in glm::ortho will be visible on screen */

    /* Define vertex array acreateRectangle("backgroundobjtree1",0,brown1,brown1,315,-100,100,20,"background",0);s used in glBegin (GL_TRIANGLES) */
    float xc=(x[0]+x[1]+x[2])/3;
    float yc=(y[0]+y[1]+y[2])/3;
    GLfloat vertex_buffer_data [] = {
        x[0]-xc,y[0]-yc,0, // vertex 0
        x[1]-xc,y[1]-yc,0, // vertex 1
        x[2]-xc,y[2]-yc,0 // vertex 2
    };

    GLfloat color_buffer_data [] = {
        color.r,color.g,color.b, // color 1
        color.r,color.g,color.b, // color 2
        color.r,color.g,color.b // color 3
    };

    // create3DObject creates and returns a handle to a VAO that can be used later
    VAO *triangle;
    if(fill==1)
        triangle=create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color_buffer_data, GL_FILL);
    else
        triangle=create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color_buffer_data, GL_LINE);
    Game InstanceGame = {};
    InstanceGame.color = color;
    InstanceGame.name = name;
    InstanceGame.object = triangle;
    InstanceGame.x=(x[0]+x[1]+x[2])/3;
    InstanceGame.y=(y[0]+y[1]+y[2])/3;
    InstanceGame.height=-1;
    InstanceGame.width=-1;
    InstanceGame.radius=-1;
    InstanceGame.anglex=angle;
    if(component=="heart")
        heart[name]=InstanceGame;
}
void createCircle (string name, float angles, COLOR color, float x, float y, float z,float r,float r1, int NoOfParts, string component, int fill)
{
    int parts = NoOfParts;
    float radius = r;
    GLfloat vertex_buffer_data[parts*9];
    GLfloat color_buffer_data[parts*9];
    int i,j;
    float angle=(2*M_PI/parts);
    float current_angle = 0;
    for(i=0;i<parts;i++){
        for(j=0;j<3;j++){
            color_buffer_data[i*9+j*3]=color.r;
            color_buffer_data[i*9+j*3+1]=color.g;
            color_buffer_data[i*9+j*3+2]=color.b;
        }
        vertex_buffer_data[i*9]=0;
        vertex_buffer_data[i*9+1]=0;
        vertex_buffer_data[i*9+2]=0;
        vertex_buffer_data[i*9+3]=radius*cos(current_angle);
        vertex_buffer_data[i*9+6]=radius*cos(current_angle+angle);
        if(name=="bridge")
        {
            vertex_buffer_data[i*9+5]=r1*sin(current_angle);
            vertex_buffer_data[i*9+4]=0;
            vertex_buffer_data[i*9+8]=r1*sin(current_angle+angle);
            vertex_buffer_data[i*9+7]=0;
        }
        else
        {
            vertex_buffer_data[i*9+4]=r1*sin(current_angle);
            vertex_buffer_data[i*9+5]=0;
            vertex_buffer_data[i*9+7]=r1*sin(current_angle+angle);
            vertex_buffer_data[i*9+8]=0;
        }
        current_angle+=angle;
    }
    VAO* circle;
    if(fill==1)
        circle = create3DObject(GL_TRIANGLES, (parts*9)/3, vertex_buffer_data, color_buffer_data, GL_FILL);
    else
        circle = create3DObject(GL_TRIANGLES, (parts*9)/3, vertex_buffer_data, color_buffer_data, GL_LINE);
    Game InstanceGame = {};
    InstanceGame.color = color;
    InstanceGame.name = name;
    InstanceGame.object = circle;
    InstanceGame.x=x;
    InstanceGame.y=y;
    InstanceGame.z=z;
    InstanceGame.height=2*r; //Height of the Game is 2*r
    InstanceGame.width=2*r; //Width of the Game is 2*r
    InstanceGame.radius=r;
    InstanceGame.anglex=angles;
    if(component=="heart")
        heart[name]=InstanceGame;
    else if(component=="bridge")
        Bridges[name]=InstanceGame;
    else if(component=="prestart")
        prestart[name]=InstanceGame;
}
glm::mat4 rotateTriangle2;
glm::mat4 rotateTriangle1;
void statusforscore(char val){
    Score["top"].status=0;
    Score["bottom"].status=0;
    Score["middle"].status=0;
    Score["left1"].status=0;
    Score["left2"].status=0;
    Score["right1"].status=0;
    Score["right2"].status=0;
    Score["middle1"].status=0;
    Score["middle2"].status=0;
    Score["diagonal1"].status=0;
    Score["diagonal2"].status=0;
    Score["diagonal3"].status=0;
    Score["diagonal4"].status=0;
    if(val=='A'|| val=='G' || val=='E' || val=='F' || val=='T' || val=='P' || val=='O' || val=='C' || val=='S' || val=='0' || val=='2' || val=='3' || val=='5' || val=='6'|| val=='7' || val=='8' || val=='9'){
        Score["top"].status=1;
    }
    if(val=='H' || val=='A' || val=='E' || val=='F' || val=='P' || val=='S' || val=='2' || val=='3' || val=='4' || val=='5' || val=='6' || val=='8' || val=='9'){
        Score["middle"].status=1;
    }
    if(val=='G' || val=='W' || val=='U' || val=='E' || val=='L' || val=='O' || val=='C' || val=='S' || val=='0' || val=='2' || val=='3' || val=='5' || val=='6' || val=='8' || val=='9'){
        Score["bottom"].status=1;
    }
    if(val=='H' || val=='A' || val=='G' || val=='M' || val=='W' || val=='U' || val=='E' || val=='F' || val=='L' || val=='N' || val=='P' || val=='O' || val=='C' || val=='S' || val=='0' || val=='4' || val=='5' || val=='6' || val=='8' || val=='9' ){
        Score["left1"].status=1;
    }
    if(val=='H' || val=='A' || val=='G' || val=='M' || val=='W' || val=='U' || val=='E' || val=='F' || val=='L' || val=='N' || val=='P' || val=='O' || val=='C' || val=='0' || val=='2' || val=='6' || val=='8'){
        Score["left2"].status=1;
    }
    if(val=='H' || val=='A' || val=='M' || val=='W' || val=='U' || val=='N' || val=='P'  || val=='O' || val=='0' || val=='1' || val=='2' || val=='3' || val=='4' || val=='7' || val=='8' || val=='9'){
        Score["right1"].status=1;
    }
    if(val=='H' || val=='A' || val=='G' || val=='M' || val=='W' || val=='U' || val=='N' || val=='O' || val=='S' || val=='0' || val=='1' || val=='3' || val=='4' || val=='5' || val=='6' || val=='7' || val=='8' || val=='9'){
        Score["right2"].status=1;
    }
    if(val=='T' || val=='I')
    {
        Score["middle1"].status=1;
    }
    if(val=='W' || val=='T' || val=='I' || val=='Y')
    {
        Score["middle2"].status=1;
    }
    if(val=='M' || val=='N' || val=='Y')
    {
        Score["diagonal1"].status=1;
    }
    if(val=='M' || val=='Y')
    {
        Score["diagonal2"].status=1;
    }
    if(val=='N')
    {
        Score["diagonal4"].status=1;
    }
}
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera_zoom += yoffset / 10;
}
void draw (GLFWwindow* window,float x,float y,float w,float h,int doM, int doV, int doP)
{
    int fbwidth, fbheight;
    glfwGetFramebufferSize(window, &fbwidth, &fbheight);
    glViewport((int)(x*fbwidth), (int)(y*fbheight), (int)(w*fbwidth), (int)(h*fbheight));


    // use the loaded shader program
    // Don't change unless you know what you are doing
    
    if(partition==0)
    {
        glUseProgram(programID);
        glm::vec3 eye(0+cos(45*M_PI/180),0,20);
        //glm::vec3 eye ( 8*sin(camera_rotation_angle*M_PI/180.0f), 3, 8*sin(camera_rotation_angle*M_PI/180.0f) );
        // Target - Where is the camera looking at.  Don't change unless you are sure!!
        glm::vec3 target (0,0,0);
        // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
        glm::vec3 up (0, 1, 0);

        // Compute Camera matrix (view)
        if(doV)
        Matrices.view = glm::lookAt(eye, target, up); // Fixed camera for 2D (ortho) in XY plane
        else
        Matrices.view = glm::mat4(1.0f);

        // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
        glm::mat4 VP;
        if (doP)
        VP = Matrices.projection * Matrices.view;
        else
        VP = Matrices.view;

        // Send our transformation to the currently bound shader, in the "MVP" uniform
        // For each model you render, since the MVP will be different (at least the M part)
        glm::mat4 MVP;  // MVP = Projection * View * Model

        // Load identity to model matrix
        Matrices.model = glm::mat4(1.0f);
        for(map<string,Game>::iterator it=background.begin();it!=background.end();it++){
            string current = it->first; //The name of the current object
            glm::mat4 MVP;  // MVP = Projection * View * Model

            Matrices.model = glm::mat4(1.0f);
            glm::mat4 ObjectTransform;
            glm::mat4 translateObject = glm::translate (glm::vec3(background[current].x,background[current].y,0.0f)); 
            glm::mat4 rotateTriangle = glm::rotate((float)((background[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));// glTranslatef
            ObjectTransform=translateObject*rotateTriangle;
            Matrices.model *= ObjectTransform;
            MVP = VP * Matrices.model; // MVP = p * V * M
            /*if(doM)
                MVP = VP * Matrices.model;
            else
                MVP = VP;*/
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

            draw3DObject(background[current].object);
            //glPopMatrix (); 
        }
        int k;
        for(k=1;k<=4;k++)
        {
            float translation;
            float translation1=0.85;
            if(k==1)
            {
                statusforscore('L');
                translation=-0.6;
            }
            else if(k==2)
            {
                statusforscore('I');
                translation=-0.4;
            }
            else if(k==3)
            {
                statusforscore('F');
                translation=-0.2;
            }
            else if(k==4)
            {
                statusforscore('E');
                translation=0;
            }
            for(map<string,Game>::iterator it=Score.begin();it!=Score.end();it++){
                string current = it->first; 
                if(Score[current].status==1)
                {
                    glm::mat4 MVP;  // MVP = Projection * View * Model

                    Matrices.model = glm::mat4(1.0f);

                    /* Render your scene */
                    glm::mat4 ObjectTransform;
                    glm::mat4 translateObject = glm::translate (glm::vec3(Score[current].x+translation,Score[current].y+translation1,0.0f)); // glTranslatef
                    glm::mat4 rotateTriangle = glm::rotate((float)((Score[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
                    ObjectTransform=translateObject*rotateTriangle;
                    Matrices.model *= ObjectTransform;
                    MVP = VP * Matrices.model; // MVP = p * V * M

                    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
                    draw3DObject(Score[current].object);
                }
            }
        }
        int num=0;
        for(num=1;num<=life;num++)
        {
            float translation,translation1=0.6;
            if(num==1)
                translation=-0.6;
            if(num==2)
                translation=-0.4;
            if(num==3)
                translation=-0.2;
            if(num==4)
                translation=0;
            if(num==5)
                translation=0.2;
            for(map<string,Game>::iterator it=heart.begin();it!=heart.end();it++){
                string current = it->first;
                glm::mat4 MVP;  // MVP = Projection * View * Model

                Matrices.model = glm::mat4(1.0f);

                /* Render your scene */
                glm::mat4 ObjectTransform;
                glm::mat4 translateObject = glm::translate (glm::vec3(heart[current].x+translation,heart[current].y+translation1,0.0f)); // glTranslatef
                glm::mat4 rotateTriangle = glm::rotate((float)((heart[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
                ObjectTransform=translateObject*rotateTriangle;
                Matrices.model *= ObjectTransform;
                MVP = VP * Matrices.model; // MVP = p * V * M

                glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
                draw3DObject(heart[current].object);
            }
        }
        int total=clock1;
        int ones,tens,hundreds;
        char val1,val2,val3;
        ones=total%10;
        total=total/10;
        tens=total%10;
        total=total/10;
        hundreds=total%10;
        val1=ones+'0';
        val2=tens+'0';
        val3=hundreds+'0';
        for(k=1;k<=4;k++)
        {
            float translation;
            float translation1=0.35;
            if(k==1)
            {
                statusforscore('T');
                translation=-0.6;
            }
            else if(k==2)
            {
                statusforscore('I');
                translation=-0.4;
            }
            else if(k==3)
            {
                statusforscore('M');
                translation=-0.2;
            }
            else if(k==4)
            {
                statusforscore('E');
                translation=0;
            }
            for(map<string,Game>::iterator it=Score.begin();it!=Score.end();it++){
                string current = it->first; 
                if(Score[current].status==1)
                {
                    glm::mat4 MVP;  // MVP = Projection * View * Model

                    Matrices.model = glm::mat4(1.0f);

                    /* Render your scene */
                    glm::mat4 ObjectTransform;
                    glm::mat4 translateObject = glm::translate (glm::vec3(Score[current].x+translation,Score[current].y+translation1,0.0f)); // glTranslatef
                    glm::mat4 rotateTriangle = glm::rotate((float)((Score[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
                    ObjectTransform=translateObject*rotateTriangle;
                    Matrices.model *= ObjectTransform;
                    MVP = VP * Matrices.model; // MVP = p * V * M

                    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
                    draw3DObject(Score[current].object);
                }
            }
        }
        for(k=1;k<=3;k++)
        {
            float translation;
            if(k==1)
            {
                statusforscore(val1);
                translation=-0.2;
            }
            else if(k==2)
            {
                statusforscore(val2);
                translation=-0.4;
            }
            else if(k==3)
            {
                statusforscore(val3);
                translation=-0.6;
            }
            for(map<string,Game>::iterator it=Score.begin();it!=Score.end();it++){
                string current = it->first; 
                if(Score[current].status==1)
                {
                    glm::mat4 MVP;  // MVP = Projection * View * Model

                    Matrices.model = glm::mat4(1.0f);

                    /* Render your scene */
                    glm::mat4 ObjectTransform;
                    glm::mat4 translateObject = glm::translate (glm::vec3(Score[current].x+translation,Score[current].y+0.1,0.0f)); // glTranslatef
                    glm::mat4 rotateTriangle = glm::rotate((float)((Score[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
                    ObjectTransform=translateObject*rotateTriangle;
                    Matrices.model *= ObjectTransform;
                    MVP = VP * Matrices.model; // MVP = p * V * M

                    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
                    draw3DObject(Score[current].object);
                }
            }
        }
        for(k=1;k<=5;k++)
        {
            float translation;
            float translation1=-0.25;
            if(k==1)
            {
                statusforscore('S');
                translation=-0.6;
            }
            else if(k==2)
            {
                statusforscore('T');
                translation=-0.4;
            }
            else if(k==3)
            {
                statusforscore('E');
                translation=-0.2;
            }
            else if(k==4)
            {
                statusforscore('P');
                translation=0;
            }
            else if(k==5)
            {
                statusforscore('S');
                translation=0.2;
            }
            for(map<string,Game>::iterator it=Score.begin();it!=Score.end();it++)
            {
                string current = it->first; 
                if(Score[current].status==1)
                {
                    glm::mat4 MVP;  // MVP = Projection * View * Model

                    Matrices.model = glm::mat4(1.0f);

                    /* Render your scene */
                    glm::mat4 ObjectTransform;
                    glm::mat4 translateObject = glm::translate (glm::vec3(Score[current].x+translation,Score[current].y+translation1,0.0f)); // glTranslatef
                    glm::mat4 rotateTriangle = glm::rotate((float)((Score[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
                    ObjectTransform=translateObject*rotateTriangle;
                    Matrices.model *= ObjectTransform;
                    MVP = VP * Matrices.model; // MVP = p * V * M

                    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
                    draw3DObject(Score[current].object);
                }
            }
        }
        total=moves;
        ones=total%10;
        total=total/10;
        tens=total%10;
        total=total/10;
        hundreds=total%10;
        val1=ones+'0';
        val2=tens+'0';
        val3=hundreds+'0';
        for(k=1;k<=3;k++)
        {
            float translation;
            if(k==1)
            {
                statusforscore(val1);
                translation=-0.2;
            }
            else if(k==2)
            {
                statusforscore(val2);
                translation=-0.4;
            }
            else if(k==3)
            {
                statusforscore(val3);
                translation=-0.6;
            }
            for(map<string,Game>::iterator it=Score.begin();it!=Score.end();it++){
                string current = it->first; 
                if(Score[current].status==1)
                {
                    glm::mat4 MVP;  // MVP = Projection * View * Model

                    Matrices.model = glm::mat4(1.0f);

                    /* Render your scene */
                    glm::mat4 ObjectTransform;
                    glm::mat4 translateObject = glm::translate (glm::vec3(Score[current].x+translation,Score[current].y-0.5,0.0f)); // glTranslatef
                    glm::mat4 rotateTriangle = glm::rotate((float)((Score[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
                    ObjectTransform=translateObject*rotateTriangle;
                    Matrices.model *= ObjectTransform;
                    MVP = VP * Matrices.model; // MVP = p * V * M

                    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
                    draw3DObject(Score[current].object);
                }
            }
        }
        for(k=1;k<=6;k++)
        {
            float translation;
            float translation1=-0.85;
            if(k==1)
            {
                statusforscore('S');
                translation=-0.6;
            }
            else if(k==2)
            {
                statusforscore('T');
                translation=-0.4;
            }
            else if(k==3)
            {
                statusforscore('A');
                translation=-0.2;
            }
            else if(k==4)
            {
                statusforscore('G');
                translation=0;
            }
            else if(k==5)
            {
                statusforscore('E');
                translation=0.2;
            }
            else if(k==6)
            {
                statusforscore(char(stage+'0'));
                translation=0.5;
            }
            for(map<string,Game>::iterator it=Score.begin();it!=Score.end();it++){
                string current = it->first; 
                if(Score[current].status==1)
                {
                    glm::mat4 MVP;  // MVP = Projection * View * Model

                    Matrices.model = glm::mat4(1.0f);

                    /* Render your scene */
                    glm::mat4 ObjectTransform;
                    glm::mat4 translateObject = glm::translate (glm::vec3(Score[current].x+translation,Score[current].y+translation1,0.0f)); // glTranslatef
                    glm::mat4 rotateTriangle = glm::rotate((float)((Score[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
                    ObjectTransform=translateObject*rotateTriangle;
                    Matrices.model *= ObjectTransform;
                    MVP = VP * Matrices.model; // MVP = p * V * M

                    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
                    draw3DObject(Score[current].object);
                }
            }
        }
    }
    if(partition==1 && gamelose==1)
    {
        doV=0;
        doP=0;
        glUseProgram(programID);
        glm::vec3 eye(0+cos(45*M_PI/180),0,20);
        //glm::vec3 eye ( 8*sin(camera_rotation_angle*M_PI/180.0f), 3, 8*sin(camera_rotation_angle*M_PI/180.0f) );
        // Target - Where is the camera looking at.  Don't change unless you are sure!!
        glm::vec3 target (0,0,0);
        // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
        glm::vec3 up (0, 1, 0);

        // Compute Camera matrix (view)
        if(doV)
        Matrices.view = glm::lookAt(eye, target, up); // Fixed camera for 2D (ortho) in XY plane
        else
        Matrices.view = glm::mat4(1.0f);

        // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
        glm::mat4 VP;
        if (doP)
        VP = Matrices.projection * Matrices.view;
        else
        VP = Matrices.view;

        // Send our transformation to the currently bound shader, in the "MVP" uniform
        // For each model you render, since the MVP will be different (at least the M part)
        glm::mat4 MVP;  // MVP = Projection * View * Model

        // Load identity to model matrix
        Matrices.model = glm::mat4(1.0f);
        for(map<string,Game>::iterator it=prestart.begin();it!=prestart.end();it++){
                string current = it->first; 
                glm::mat4 MVP;  // MVP = Projection * View * Model

                Matrices.model = glm::mat4(1.0f);

                /* Render your scene */
                glm::mat4 ObjectTransform;
                glm::mat4 translateObject = glm::translate (glm::vec3(prestart[current].x,prestart[current].y,0.0f)); // glTranslatef
                glm::mat4 rotateTriangle = glm::rotate((float)((prestart[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
                ObjectTransform=translateObject*rotateTriangle;
                Matrices.model *= ObjectTransform;
                MVP = VP * Matrices.model; // MVP = p * V * M

                glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
                draw3DObject(prestart[current].object);
        }
        clock1=0;
        int k;
        for(k=1;k<=4;k++)
        {
            float translation;
            float translation1=0;
            if(k==1)
            {
                statusforscore('L');
                translation=-0.3;
            }
            else if(k==2)
            {
                statusforscore('O');
                translation=-0.1;
            }
            else if(k==3)
            {
                statusforscore('S');
                translation=0.1;
            }
            else if(k==4)
            {
                statusforscore('E');
                translation=0.3;
            }
            for(map<string,Game>::iterator it=Score.begin();it!=Score.end();it++){
                string current = it->first; 
                if(Score[current].status==1)
                {
                    glm::mat4 MVP;  // MVP = Projection * View * Model

                    Matrices.model = glm::mat4(1.0f);

                    /* Render your scene */
                    glm::mat4 ObjectTransform;
                    glm::mat4 translateObject = glm::translate (glm::vec3(Score[current].x+translation,Score[current].y+translation1,0.0f)); // glTranslatef
                    glm::mat4 rotateTriangle = glm::rotate((float)((Score[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
                    ObjectTransform=translateObject*rotateTriangle;
                    Matrices.model *= ObjectTransform;
                    MVP = VP * Matrices.model; // MVP = p * V * M

                    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
                    draw3DObject(Score[current].object);
                }
            }
        }
    }
    if(partition==1 && gamewin==1)
    {
        doV=0;
        doP=0;
        glUseProgram(programID);
        glm::vec3 eye(0+cos(45*M_PI/180),0,20);
        //glm::vec3 eye ( 8*sin(camera_rotation_angle*M_PI/180.0f), 3, 8*sin(camera_rotation_angle*M_PI/180.0f) );
        // Target - Where is the camera looking at.  Don't change unless you are sure!!
        glm::vec3 target (0,0,0);
        // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
        glm::vec3 up (0, 1, 0);

        // Compute Camera matrix (view)
        if(doV)
        Matrices.view = glm::lookAt(eye, target, up); // Fixed camera for 2D (ortho) in XY plane
        else
        Matrices.view = glm::mat4(1.0f);

        // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
        glm::mat4 VP;
        if (doP)
        VP = Matrices.projection * Matrices.view;
        else
        VP = Matrices.view;

        // Send our transformation to the currently bound shader, in the "MVP" uniform
        // For each model you render, since the MVP will be different (at least the M part)
        glm::mat4 MVP;  // MVP = Projection * View * Model
        clock1=0;
        // Load identity to model matrix
        Matrices.model = glm::mat4(1.0f);
        for(map<string,Game>::iterator it=prestart.begin();it!=prestart.end();it++){
                string current = it->first; 
                glm::mat4 MVP;  // MVP = Projection * View * Model

                Matrices.model = glm::mat4(1.0f);

                /* Render your scene */
                glm::mat4 ObjectTransform;
                glm::mat4 translateObject = glm::translate (glm::vec3(prestart[current].x,prestart[current].y,0.0f)); // glTranslatef
                glm::mat4 rotateTriangle = glm::rotate((float)((prestart[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
                ObjectTransform=translateObject*rotateTriangle;
                Matrices.model *= ObjectTransform;
                MVP = VP * Matrices.model; // MVP = p * V * M

                glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
                draw3DObject(prestart[current].object);
        }
        int k;
        for(k=1;k<=3;k++)
        {
            float translation;
            float translation1=0;
            if(k==1)
            {
                statusforscore('W');
                translation=-0.2;
            }
            else if(k==2)
            {
                statusforscore('I');
                translation=0;
            }
            else if(k==3)
            {
                statusforscore('N');
                translation=0.2;
            }
            for(map<string,Game>::iterator it=Score.begin();it!=Score.end();it++){
                string current = it->first; 
                if(Score[current].status==1)
                {
                    glm::mat4 MVP;  // MVP = Projection * View * Model

                    Matrices.model = glm::mat4(1.0f);

                    /* Render your scene */
                    glm::mat4 ObjectTransform;
                    glm::mat4 translateObject = glm::translate (glm::vec3(Score[current].x+translation,Score[current].y+translation1,0.0f)); // glTranslatef
                    glm::mat4 rotateTriangle = glm::rotate((float)((Score[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
                    ObjectTransform=translateObject*rotateTriangle;
                    Matrices.model *= ObjectTransform;
                    MVP = VP * Matrices.model; // MVP = p * V * M

                    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
                    draw3DObject(Score[current].object);
                }
            }
        }
    }
    if(partition==1 && hello==1)
    {
        doV=0;
        doP=0;
        glUseProgram(programID);
        glm::vec3 eye(0+cos(45*M_PI/180),0,20);
        //glm::vec3 eye ( 8*sin(camera_rotation_angle*M_PI/180.0f), 3, 8*sin(camera_rotation_angle*M_PI/180.0f) );
        // Target - Where is the camera looking at.  Don't change unless you are sure!!
        glm::vec3 target (0,0,0);
        // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
        glm::vec3 up (0, 1, 0);

        // Compute Camera matrix (view)
        if(doV)
        Matrices.view = glm::lookAt(eye, target, up); // Fixed camera for 2D (ortho) in XY plane
        else
        Matrices.view = glm::mat4(1.0f);

        // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
        glm::mat4 VP;
        if (doP)
        VP = Matrices.projection * Matrices.view;
        else
        VP = Matrices.view;

        // Send our transformation to the currently bound shader, in the "MVP" uniform
        // For each model you render, since the MVP will be different (at least the M part)
        glm::mat4 MVP;  // MVP = Projection * View * Model
        clock1=300;
        // Load identity to model matrix
        Matrices.model = glm::mat4(1.0f);
        for(map<string,Game>::iterator it=prestart.begin();it!=prestart.end();it++){
                string current = it->first; 
                glm::mat4 MVP;  // MVP = Projection * View * Model

                Matrices.model = glm::mat4(1.0f);

                /* Render your scene */
                glm::mat4 ObjectTransform;
                glm::mat4 translateObject = glm::translate (glm::vec3(prestart[current].x,prestart[current].y,0.0f)); // glTranslatef
                glm::mat4 rotateTriangle = glm::rotate((float)((prestart[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
                ObjectTransform=translateObject*rotateTriangle;
                Matrices.model *= ObjectTransform;
                MVP = VP * Matrices.model; // MVP = p * V * M

                glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
                draw3DObject(prestart[current].object);
        }
        int k;
        for(k=1;k<=5;k++)
        {
            float translation;
            float translation1=0;
            if(k==1)
            {
                statusforscore('H');
                translation=-0.4;
            }
            else if(k==2)
            {
                statusforscore('E');
                translation=-0.2;
            }
            else if(k==3)
            {
                statusforscore('L');
                translation=0;
            }
            else if(k==4)
            {
                statusforscore('L');
                translation=0.2;
            }
            else if(k==5)
            {
                statusforscore('O');
                translation=0.4;
            }
            for(map<string,Game>::iterator it=Score.begin();it!=Score.end();it++){
                string current = it->first; 
                if(Score[current].status==1)
                {
                    glm::mat4 MVP;  // MVP = Projection * View * Model

                    Matrices.model = glm::mat4(1.0f);

                    /* Render your scene */
                    glm::mat4 ObjectTransform;
                    glm::mat4 translateObject = glm::translate (glm::vec3(Score[current].x+translation,Score[current].y+translation1,0.0f)); // glTranslatef
                    glm::mat4 rotateTriangle = glm::rotate((float)((Score[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
                    ObjectTransform=translateObject*rotateTriangle;
                    Matrices.model *= ObjectTransform;
                    MVP = VP * Matrices.model; // MVP = p * V * M

                    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
                    draw3DObject(Score[current].object);
                }
            }
        }
    }

    if(partition==1 && gamelose==0 && gamewin==0 && hello==0)
    {
    // Eye - Location of camera. Don't change unless you are sure!!
    /*camera_radius=1;
    angle=90;
    target_x=0;
    target_y=0;
    target_z=0;
    eye_x=-4;
    eye_y=12;
    eye_z=-4;*/
    glUseProgram(programID);
    float temp1,temp2,temp3;
    temp1= (cube["cube1"].x+cube["cube2"].x)/2;
    temp2 = (cube["cube1"].y+cube["cube2"].y)/2;
    temp3 = (cube["cube1"].z+cube["cube2"].z)/2;
    if(camera_top==1)
    {
        eye_x = 0+cos(45*M_PI/180);
        eye_z = 0;
        //+sin(45*M_PI/180);
        eye_y=13;
        target_x=0;
        target_y=0;
        target_z=0;
        /*eye_x = temp1;
        eye_z = temp3;
        eye_y= 10;
        target_x = temp1;
        target_y = 0;
        target_z = temp3;*/
        //fps_head_offset=0;
        //fps_head_offset_x=0;
        //camera_fov=1.3;
    }
    if(camera_tower==1)
    {
        eye_x = 12,
        eye_y = 12;
        eye_z = 0;
        target_z = 0;
        target_y = 0;
        target_x = 0;    
    }
    glfwGetCursorPos(window, &mouse_pos_x, &mouse_pos_y);
    if(camera_follow==1)
    {
        if(orient_left==1)
        {
            eye_x = temp1-5;
            eye_y = temp2;
            eye_z = temp3;
            target_x = 1000;
            target_y = temp2;
            target_z = temp3;
        }
        else if(orient_right==1)
        {
            eye_x = temp1+5;
            eye_y = temp2;
            eye_z = temp3;
            target_x = -1000;
            target_y = temp2;
            target_z = temp3;
        }
        else if(orient_backward==1)
        {
            eye_x = temp1;
            eye_y = temp2;
            eye_z = temp3+5;
            target_x = temp1;
            target_y = temp2;
            target_z = -1000;
        }
        else if(orient_forward==1)
        {
            eye_x = temp1;
            eye_y = temp2;
            eye_z = temp3-5;
            target_x = temp1;
            target_y = temp2;
            target_z = 1000;
        }
        if(mouse_click==1)
        {
            orient_forward=0;
            orient_left=0;
            orient_backward=0;
            orient_right=0;
            eye_x = temp1-5*cos((mouse_pos_x)*(160*M_PI)/(360*180.0f));
            eye_y = temp2;
            eye_z = temp3-5*sin((mouse_pos_x)*(160*M_PI)/(360*180.0f));
            target_x = temp1;
            target_y = temp2;
            target_z = temp3;
        }
    }
    if(camera_self==1)
    {
        if(orient_left==1)
        {
            eye_x = temp1-3;
            eye_y = temp2;
            eye_z = temp3;
            target_x = -1000;
            target_y = temp2;
            target_z = temp3;
        }
        else if(orient_right==1)
        {
            eye_x = temp1+3;
            eye_y = temp2;
            eye_z = temp3;
            target_x = 1000;
            target_y = temp2;
            target_z = temp3;
        }
        else if(orient_backward==1)
        {
            eye_x = temp1;
            eye_y = temp2;
            eye_z = temp3-3;
            target_x = temp1;
            target_y = temp2;
            target_z = -1000;
        }
        else
        {
            eye_x = temp1;          
            eye_y = temp2;
            eye_z = temp3+3;
            target_x = temp1;
            target_y = temp2;
            target_z = 1000;
        }
        if(mouse_click==1)
        {
            orient_forward=0;
            orient_left=0;
            orient_backward=0;
            orient_right=0;
            eye_x = temp1+3*cos((mouse_pos_x)*(160*M_PI)/(360*180.0f));
            eye_y = temp2;
            eye_z = temp3+3*sin((mouse_pos_x)*(160*M_PI)/(360*180.0f));
            target_x = temp1+5*cos((mouse_pos_x)*(160*M_PI)/(360*180.0f));
            target_y = temp2;
            target_z = temp3+5*sin((mouse_pos_x)*(160*M_PI)/(360*180.0f));
        }
    }
    glfwGetCursorPos(window, &mouse_pos_x, &mouse_pos_y);
    if(camera_helicopter==1)
    {
        if(mouse_click==1)
        {
            angle=(mouse_pos_x)*360/600;
            eye_x = 15*cos(angle*M_PI/180);
            eye_z = 15*sin(angle*M_PI/180);
            target_x = 0;
            target_z = 0;
            target_y = 0;
        }
        if(right_mouse_click==1)
        {
            angle = 90-(mouse_pos_y)*90/600;
            eye_y = 15*sin(angle*M_PI/180);
            target_x = 0;
            target_z = 0;
            target_y = 0;
        }
    }
    prev_mouse_pos_x = mouse_pos_x;
    prev_mouse_pos_y = mouse_pos_y;
    if(camera_self==0 && camera_follow==0)
    {
        orient_forward=1;
        orient_right=0;
        orient_left=0;
        orient_backward=0;
    }
    glm::vec3 eye(eye_x,eye_y,eye_z);
    //glm::vec3 eye ( 8*sin(camera_rotation_angle*M_PI/180.0f), 3, 8*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (target_x,target_y,target_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    if(doV)
	Matrices.view = glm::lookAt(eye, target, up); // Fixed camera for 2D (ortho) in XY plane
    else
	Matrices.view = glm::mat4(1.0f);

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    glm::mat4 VP;
    if (doP)
	VP = Matrices.projection * Matrices.view * glm::scale(glm::vec3(exp(camera_zoom)));
    else
	VP = Matrices.view;

    glfwSetScrollCallback(window, scroll_callback);

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    glm::mat4 MVP;	// MVP = Projection * View * Model

    // Load identity to model matrix
    Matrices.model = glm::mat4(1.0f);
    /*glm::mat4 translateRectangle = glm::translate (rect_pos);        // glTranslatef
    glm::mat4 rotateRectangle = glm::rotate((float)(rectangle_rotation*M_PI/180.0f), glm::vec3(0,0,1));
    Matrices.model *= (translateRectangle * rotateRectangle);
    if(floor_rel)
	Matrices.model = Matrices.model * glm::translate(floor_pos);
    if(doM)
	MVP = VP * Matrices.model;
    else
	MVP = VP;

    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    // draw3DObject draws the VAO given to it using current MVP matrix
    draw3DObject(rectangle);

    // Load identity to model matrix
    Matrices.model = glm::mat4(1.0f);

    glm::mat4 translateCam = glm::translate(eye);
    glm::mat4 rotateCam = glm::rotate((float)((90 - camera_rotation_angle)*M_PI/180.0f), glm::vec3(0,1,0));
    Matrices.model *= (translateCam * rotateCam);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    // draw3DObject draws the VAO given to it using current MVP matrix
    draw3DObject(cam);*/
    
    if(down1==1)
    {
        float ch1,ch2;
        ch1=cube["cube1"].y;
        ch2=cube["cube2"].y;
        if(ch1==ch2)
        {
            fl=1;
        }
        if(fl==1)
        {
            if(cube["cube1"].x>cube["cube2"].x)
            {
                //cube["cube2"].y=2.5;
                //cube["cube2"].x=cube["cube1"].x;
                cube["cube2"].x+=0.4;
                cube["cube1"].x+=0.2;
                cube["cube2"].y+=0.2;
            }
            else if(cube["cube1"].x<cube["cube2"].x)
            {
                cube["cube1"].y+=0.2;
                //cube["cube1"].x=cube["cube2"].x;
                cube["cube2"].x+=0.2;
                cube["cube1"].x+=0.4;
            }
            else
            {
                cube["cube1"].x+=0.2;
                cube["cube2"].x+=0.2;
                cube["cube1"].x=cube["cube2"].x;
            }
        }
        else
        {
            if(cube["cube1"].y>cube["cube2"].y)
            {
                cube["cube1"].x+=0.4;
                cube["cube2"].x+=0.2;
                cube["cube1"].y-=0.2;
                //cube["cube1"].y=cube["cube2"].y;

            }
            else
            {
                cube["cube2"].x+=0.4;
                cube["cube1"].x+=0.2;
                cube["cube2"].y-=0.2;
                //cube["cube2"].y=cube["cube1"].y;
            }
        }
        cube["cube1"].anglez-=9;
        cube["cube2"].anglez-=9;
        rotateTriangle1 = glm::rotate((float)(((cube["cube1"].anglez))*M_PI/180.0f), glm::vec3(0,0,1));
        //rotateTriangle2 = glm::rotate((float)(((cube["cube1"].anglex))*M_PI/180.0f), glm::vec3(1,0,0));
        rep++;
        if(rep==10)
        {
            rep=0;
            down1=0;
            roundi=1;
            if(fl==0)
            {
                cube["cube1"].y=cube["cube2"].y;
            }
            if(fl==1)
            {
                cube["cube1"].x=cube["cube2"].x;
            }
            fl=0;
        }
    }
    if(up1==1)
    {
        if(cube["cube1"].y==cube["cube2"].y)
        {
            fl=1;
        }
        if(fl==1)
        {
            if(cube["cube1"].x>cube["cube2"].x)
            {
                //cube["cube2"].y=2.5;
                //cube["cube2"].x=cube["cube1"].x;
                cube["cube2"].x-=0.2;
                cube["cube1"].x-=0.4;
                cube["cube1"].y+=0.2;
            }
            else if(cube["cube1"].x<cube["cube2"].x)
            {
                cube["cube2"].y+=0.2;
                //cube["cube1"].x=cube["cube2"].x;
                cube["cube1"].x-=0.2;
                cube["cube2"].x-=0.4;
            }
            else
            {
                cube["cube1"].x-=0.2;
                cube["cube2"].x-=0.2;
                cube["cube1"].x=cube["cube2"].x;
            }
        }
        else
        {
            if(cube["cube1"].y>cube["cube2"].y)
            {
                cube["cube1"].x-=0.4;
                cube["cube2"].x-=0.2;
                cube["cube1"].y-=0.2;
                //cube["cube1"].y=cube["cube2"].y;

            }
            else
            {
                cube["cube2"].x-=0.4;
                cube["cube1"].x-=0.2;
                cube["cube2"].y-=0.2;
                //cube["cube2"].y=cube["cube1"].y;
            }
        }
        cube["cube1"].anglez+=9;
        cube["cube2"].anglez+=9;
        rotateTriangle1 = glm::rotate((float)(((cube["cube1"].anglez))*M_PI/180.0f), glm::vec3(0,0,1));
        //rotateTriangle2 = glm::rotate((float)(((cube["cube1"].anglex))*M_PI/180.0f), glm::vec3(1,0,0));
        rep++;
        if(rep==10)
        {
            rep=0;
            roundi=1;
            up1=0;
            if(fl==0)
            {
                cube["cube1"].y=cube["cube2"].y;
            }
            if(fl==1)
            {
                cube["cube1"].x=cube["cube2"].x;
            }
            fl=0;
        }
    }
    if(left1==1)
    {
        if(cube["cube1"].y==cube["cube2"].y)
        {
            fl=1;
        }
        if(fl==1)
        {
            if(cube["cube1"].z>cube["cube2"].z)
            {
                //cube["cube2"].y=2.5;
                //cube["cube2"].x=cube["cube1"].x;
                cube["cube2"].z+=0.4;
                cube["cube1"].z+=0.2;
                cube["cube2"].y+=0.2;
            }
            else if(cube["cube1"].z<cube["cube2"].z)
            {
                cube["cube1"].y+=0.2;
                //cube["cube1"].x=cube["cube2"].x;
                cube["cube1"].z+=0.4;
                cube["cube2"].z+=0.2;
            }
            else
            {
                cube["cube1"].z+=0.2;
                cube["cube2"].z+=0.2;
                cube["cube1"].z=cube["cube2"].z;
            }
        }
        else
        {
            if(cube["cube1"].y>cube["cube2"].y)
            {
                cube["cube1"].z+=0.4;
                cube["cube2"].z+=0.2;
                cube["cube1"].y-=0.2;
                //cube["cube1"].y=cube["cube2"].y;

            }
            else
            {
                cube["cube2"].z+=0.4;
                cube["cube1"].z+=0.2;
                cube["cube2"].y-=0.2;
                //cube["cube2"].y=cube["cube1"].y;
            }
        }
        cube["cube1"].anglex+=9;
        cube["cube2"].anglex+=9;
        rotateTriangle1 = glm::rotate((float)(((cube["cube1"].anglex))*M_PI/180.0f), glm::vec3(1,0,0));
        //rotateTriangle2 = glm::rotate((float)(((cube["cube1"].anglez))*M_PI/180.0f), glm::vec3(1,0,0));
        rep++;
        if(rep==10)
        {
            rep=0;
            roundi=1;
            left1=0;
            if(fl==0)
            {
                cube["cube1"].y=cube["cube2"].y;
            }
            if(fl==1)
            {
                cube["cube1"].z=cube["cube2"].z;
            }
            fl=0;
        }
    }
    if(right1==1)
    {
        if(cube["cube1"].y==cube["cube2"].y)
        {
            fl=1;
        }
        if(fl==1)
        {
            if(cube["cube1"].z>cube["cube2"].z)
            {
                cube["cube1"].z-=0.4;
                cube["cube2"].z-=0.2;
                cube["cube1"].y+=0.2;
            }
            else if(cube["cube1"].z<cube["cube2"].z)
            {
                cube["cube2"].y+=0.2;
                //cube["cube1"].x=cube["cube2"].x;
                cube["cube2"].z-=0.4;
                cube["cube1"].z-=0.2;
            }
            else
            {
                cube["cube1"].z-=0.2;
                cube["cube2"].z-=0.2;
                cube["cube1"].z=cube["cube2"].z;
            }
        }
        else
        {
            if(cube["cube1"].y>cube["cube2"].y)
            {
                cube["cube1"].z-=0.4;
                cube["cube2"].z-=0.2;
                cube["cube1"].y-=0.2;
                //cube["cube1"].y=cube["cube2"].y;

            }
            else
            {
                cube["cube2"].z-=0.4;
                cube["cube1"].z-=0.2;
                cube["cube2"].y-=0.2;
                //cube["cube2"].y=cube["cube1"].y;
            }
        }
        cube["cube1"].anglex-=9;
        cube["cube2"].anglex-=9;
        rotateTriangle1 = glm::rotate((float)(((cube["cube1"].anglex))*M_PI/180.0f), glm::vec3(1,0,0));
        //rotateTriangle2 = glm::rotate((float)(((cube["cube1"].anglez))*M_PI/180.0f), glm::vec3(1,0,0));
        rep++;
        if(rep==10)
        {
            rep=0;
            roundi=1;
            right1=0;
            if(fl==0)
            {
                cube["cube1"].y=cube["cube2"].y;
            }
            if(fl==1)
            {
                cube["cube1"].z=cube["cube2"].z;
            }
            fl=0;
        }
    }
    if(roundi==1)
    {
        if(0.5>cube["cube1"].x && cube["cube1"].x>=-0.5)
        {
            cube["cube1"].x=0;
        }
        else
        {
            cube["cube1"].x=roundf(cube["cube1"].x);
        }
        if(0.5>cube["cube1"].y && cube["cube1"].y>=-0.5)
        {
            //cube["cube1"].y=0;
        }
        else
        {
            //cube["cube1"].y=roundf(cube["cube1"].y);
        }
        if(0.5>cube["cube1"].z && cube["cube1"].z>=-0.5)
        {
            cube["cube1"].z=0;
        }
        else
        {
            cube["cube1"].z=roundf(cube["cube1"].z);
        }
        if(0.5>cube["cube2"].x && cube["cube2"].x>=-0.5)
        {
            cube["cube2"].x=0;
        }
        else
        {
            cube["cube2"].x=roundf(cube["cube2"].x);
        }
        if(0.5>cube["cube2"].y && cube["cube2"].y>=-0.5)
        {
            //cube["cube2"].y=0;
        }
        else
        {
            //cube["cube2"].y=roundf(cube["cube2"].y);
        }
        if(0.5>cube["cube2"].z && cube["cube2"].z>=-0.5)
        {
            cube["cube2"].z=0;
        }
        else
        {
            cube["cube2"].z=roundf(cube["cube2"].z);
        }
        roundi=0;
        if(cube["cube1"].y!=cube["cube2"].y)
        {
            if(cube["cube1"].y<cube["cube2"].y)
            {
                if(gamemap[int(cube["cube1"].x/2)+6][int(cube["cube1"].z/2)+8]==2)
                {
	                if(cube["cube1"].y>-5)
		        	{
		        		roundi=1;
		        		cube["cube1"].y-=0.1;
		        		cube["cube2"].y-=0.1;
		        	}
		        	else
		        	{
		        		roundi=0;
	                    life--;
	                    bridge=0;
	                    bridge1=0;
	                    cube["cube1"].x=6;
	                    cube["cube2"].x=6;
	                    cube["cube2"].z=-14;
	                    cube["cube1"].z=-14;
	                    cube["cube1"].y=0.25;
	                    cube["cube2"].y=2.25;
	                }
                }
            }
            else
            {
                if(gamemap[int(cube["cube2"].x/2)+6][int(cube["cube2"].z/2)+8]==2)
                {
                    if(cube["cube1"].y>-5)
		        	{
		        		roundi=1;
		        		cube["cube1"].y-=0.1;
		        		cube["cube2"].y-=0.1;
		        	}
		        	else
		        	{
		        		roundi=0;
	                    life--;
	                    bridge=0;
	                    bridge1=0;
	                    cube["cube1"].x=6;
	                    cube["cube2"].x=6;
	                    cube["cube2"].z=-14;
	                    cube["cube1"].z=-14;
	                    cube["cube1"].y=0.25;
	                    cube["cube2"].y=2.25;
	                }
                }
            }
        }
        if(gamemap[int(cube["cube1"].x/2)+6][int(cube["cube1"].z/2)+8]==0 || (gamemap[int(cube["cube1"].x/2)+6][int(cube["cube1"].z/2)+8]==3 && bridge==0) || (gamemap[int(cube["cube1"].x/2)+6][int(cube["cube1"].z/2)+8]==5 && bridge1==0))
        {
            //quit(window);
            if(cube["cube1"].y>-5)
        	{
        		roundi=1;
        		cube["cube1"].y-=0.1;
        		cube["cube2"].y-=0.1;
        	}
        	else
        	{
        		roundi=0;
	            life--;
	            bridge=0;
	            bridge1=0;
	            cube["cube1"].x=6;
	            cube["cube2"].x=6;
	            cube["cube2"].z=-14;
	            cube["cube1"].z=-14;
	            cube["cube1"].y=0.25;
	            cube["cube2"].y=2.25;
	        }
        }
        else if(gamemap[int(cube["cube2"].x/2)+6][int(cube["cube2"].z/2)+8]==0 || (gamemap[int(cube["cube2"].x/2)+6][int(cube["cube2"].z/2)+8]==3 && bridge==0) || (gamemap[int(cube["cube2"].x/2)+6][int(cube["cube2"].z/2)+8]==5 && bridge1==0))
        {
            //quit(window);
        	if(cube["cube1"].y>-5)
        	{
        		roundi=1;
        		cube["cube1"].y-=0.1;
        		cube["cube2"].y-=0.1;
        	}
        	else
        	{
        		roundi=0;
	            life--;
	            bridge=0;
	            bridge1=0;
	            cube["cube1"].x=6;
	            cube["cube2"].x=6;
	            cube["cube2"].z=-14;
	            cube["cube1"].z=-14;;
	            cube["cube1"].y=0.25;
	            cube["cube2"].y=2.25;
	        }
        }
        if(gamemap[int(cube["cube1"].x/2)+6][int(cube["cube1"].z/2)+8]==8 && gamemap[int(cube["cube2"].x/2)+6][int(cube["cube2"].z/2)+8]==8)
        {
        	cube["cube1"].x=6;
        	cube["cube1"].z=14;
        	cube["cube2"].x=6;
        	cube["cube2"].z=14;
        }
        if(gamemap[int(cube["cube1"].x/2)+6][int(cube["cube1"].z/2)+8]==7 && gamemap[int(cube["cube2"].x/2)+6][int(cube["cube2"].z/2)+8]==7)
        {
        	if(cube["cube1"].y>-5)
        	{
        		roundi=1;
        		cube["cube1"].y-=0.1;
        		cube["cube2"].y-=0.1;
        	}
        	else
        	{
	            stage++;
	            roundi=0;
	            cube["cube1"].x=6;
	            cube["cube2"].x=6;
	            cube["cube2"].z=-14;
	            cube["cube1"].z=-14;
	            cube["cube1"].y=0.25;
	            cube["cube2"].y=2.25;
	            moves=100;
	            ISoundEngine* engine = createIrrKlangDevice();

	            if (!engine)
	            {
	                printf("Could not startup engine\n");
	            }

	            // To play a sound, we only to call play2D(). The second parameter
	            // tells the engine to play it looped.

	            // play some sound stream, looped
	            engine->play2D("irrKlang-64bit-1.5.0/media/bell.wav", false);
	        }
        }
        else if(gamemap[int(cube["cube2"].x/2)+6][int(cube["cube2"].z/2)+8]==7 || gamemap[int(cube["cube1"].x/2)+6][int(cube["cube1"].z/2)+8]==7)
        {
            //quit(window);
            if(cube["cube1"].y>-5)
        	{
        		roundi=1;
        		cube["cube1"].y-=0.1;
        		cube["cube2"].y-=0.1;
        	}
        	else
        	{
        		roundi=0;
	            life--;
	            bridge=0;
	            bridge1=0;
	            cube["cube1"].x=6;
	            cube["cube2"].x=6;
	            cube["cube2"].z=-14;
	            cube["cube1"].z=-14;
	            cube["cube1"].y=0.25;
	            cube["cube2"].y=2.25;
	        }
        }
    }
    if(gamemap[int(cube["cube1"].x/2)+6][int(cube["cube1"].z/2)+8]==6 || gamemap[int(cube["cube2"].x/2)+6][int(cube["cube2"].z/2)+8]==6)
    {
        if(bridge1==0 && toggle==0)
        {
            bridge1=1;
            toggle=1;
        }
        if(bridge1==1 && toggle==0)
        {
            bridge1=0;
            toggle=1;
        }
    }
    if(gamemap[int(cube["cube1"].x/2)+6][int(cube["cube1"].z/2)+8]!=6 && gamemap[int(cube["cube2"].x/2)+6][int(cube["cube2"].z/2)+8]!=6)
    {
        toggle=0;
    }
    //cout<<cube["cube1"].x<<" "<<cube["cube1"].z<<" "<<cube["cube2"].x<<" "<<cube["cube2"].z<<endl;
    //cout<<gamemap[int(cube["cube1"].x/2)+6][int(cube["cube1"].z/2)+8]<<" "<<gamemap[int(cube["cube2"].x/2)+6][int(cube["cube2"].z/2)+8]<<endl;
    if(gamemap[int(cube["cube1"].x/2)+6][int(cube["cube1"].z/2)+8]==4 || gamemap[int(cube["cube2"].x/2)+6][int(cube["cube2"].z/2)+8]==4)
    {

        if(bridge==0 && toggle1==0)
        {
            bridge=1;
            toggle1=1;
        }
        if(bridge==1 && toggle1==0)
        {
            bridge=0;
            toggle1=1;
        }
    }
    if(gamemap[int(cube["cube1"].x/2)+6][int(cube["cube1"].z/2)+8]!=4 && gamemap[int(cube["cube2"].x/2)+6][int(cube["cube2"].z/2)+8]!=4)
    {
        toggle1=0;
    }
    /*for(map<string,Game>::iterator it=background1.begin();it!=tiles.end();it++){
        string current = it->first; //The name of the current object
            glm::mat4 MVP;  // MVP = Projection * View * Model

            Matrices.model = glm::mat4(1.0f);

            glm::mat4 ObjectTransform;
            glm::mat4 translateObject = glm::translate (glm::vec3(background1[current].x,background1[current].y, background1[current].z)); 
            glm::mat4 rotateTriangle = glm::rotate((float)((background1[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));// glTranslatef
            ObjectTransform=translateObject*rotateTriangle;
            Matrices.model *= ObjectTransform;
            //MVP = VP * Matrices.model; // MVP = p * V * M
            if(doM)
                MVP = VP * Matrices.model;
            else
                MVP = VP;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

            draw3DObject(background1[current].object);
        }*/
    if(stage==1)
    {
        for(map<string,Game>::iterator it=tiles.begin();it!=tiles.end();it++){
            string current = it->first; //The name of the current object
            if(gamemap[int(tiles[current].numx)][int(tiles[current].numy)]==3 && bridge==0)
            {
                continue;
            }
            if(gamemap[int(tiles[current].numx)][int(tiles[current].numy)]==5 && bridge1==0)
            {
                continue;
            }
            glm::mat4 MVP;  // MVP = Projection * View * Model

            Matrices.model = glm::mat4(1.0f);

            glm::mat4 ObjectTransform;
            glm::mat4 translateObject = glm::translate (glm::vec3(tiles[current].x,tiles[current].y, tiles[current].z)); 
            glm::mat4 rotateTriangle = glm::rotate((float)((tiles[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));// glTranslatef
            ObjectTransform=translateObject*rotateTriangle;
            Matrices.model *= ObjectTransform;
            //MVP = VP * Matrices.model; // MVP = p * V * M
            if(doM)
                MVP = VP * Matrices.model;
            else
                MVP = VP;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

            draw3DObject(tiles[current].object);
            //glPopMatrix (); 
        }
        for(map<string,Game>::iterator it=tiles.begin();it!=tiles.end();it++){
            string current = it->first; //The name of the current object
            if(gamemap[int(tiles[current].numx)][int(tiles[current].numy)]==4 || gamemap[int(tiles[current].numx)][int(tiles[current].numy)]==6)
            {
                glm::mat4 MVP;  // MVP = Projection * View * Model

                Matrices.model = glm::mat4(1.0f);

                glm::mat4 ObjectTransform;
                glm::mat4 translateObject = glm::translate (glm::vec3(tiles[current].x,tiles[current].y+0.26, tiles[current].z)); 
                glm::mat4 rotateTriangle = glm::rotate((float)((tiles[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));// glTranslatef
                ObjectTransform=translateObject*rotateTriangle;
                Matrices.model *= ObjectTransform;
                //MVP = VP * Matrices.model; // MVP = p * V * M
                if(doM)
                    MVP = VP * Matrices.model;
                else
                    MVP = VP;
                glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

                draw3DObject(Bridges["bridge"].object);
            }
            //glPopMatrix (); 
        }
    }
    else if(stage==2)
    {
        for(map<string,Game>::iterator it=tiles1.begin();it!=tiles1.end();it++){
            string current = it->first; //The name of the current object
            if(gamemap[int(tiles1[current].numx)][int(tiles1[current].numy)]==3 && bridge==0)
            {
                continue;
            }
            if(gamemap[int(tiles1[current].numx)][int(tiles1[current].numy)]==5 && bridge1==0)
            {
                continue;
            }
            glm::mat4 MVP;  // MVP = Projection * View * Model

            Matrices.model = glm::mat4(1.0f);

            glm::mat4 ObjectTransform;
            glm::mat4 translateObject = glm::translate (glm::vec3(tiles1[current].x,tiles1[current].y, tiles1[current].z)); 
            glm::mat4 rotateTriangle = glm::rotate((float)((tiles1[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));// glTranslatef
            ObjectTransform=translateObject*rotateTriangle;
            Matrices.model *= ObjectTransform;
            //MVP = VP * Matrices.model; // MVP = p * V * M
            if(doM)
                MVP = VP * Matrices.model;
            else
                MVP = VP;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

            draw3DObject(tiles1[current].object);
            //glPopMatrix (); 
        }
          for(map<string,Game>::iterator it=tiles1.begin();it!=tiles1.end();it++){
            string current = it->first; //The name of the current object
            if(gamemap[int(tiles1[current].numx)][int(tiles1[current].numy)]==4 || gamemap[int(tiles1[current].numx)][int(tiles1[current].numy)]==6)
            {
                glm::mat4 MVP;  // MVP = Projection * View * Model

                Matrices.model = glm::mat4(1.0f);

                glm::mat4 ObjectTransform;
                glm::mat4 translateObject = glm::translate (glm::vec3(tiles1[current].x,tiles1[current].y+0.26, tiles1[current].z)); 
                glm::mat4 rotateTriangle = glm::rotate((float)((tiles1[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));// glTranslatef
                ObjectTransform=translateObject*rotateTriangle;
                Matrices.model *= ObjectTransform;
                //MVP = VP * Matrices.model; // MVP = p * V * M
                if(doM)
                    MVP = VP * Matrices.model;
                else
                    MVP = VP;
                glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

                draw3DObject(Bridges["bridge"].object);
            }
            //glPopMatrix (); 
        }
    }
    else if(stage==3)
    {
        for(map<string,Game>::iterator it=tiles2.begin();it!=tiles2.end();it++){
            string current = it->first; //The name of the current object
            if(gamemap[int(tiles2[current].numx)][int(tiles2[current].numy)]==3 && bridge==0)
            {
                continue;
            }
            if(gamemap[int(tiles2[current].numx)][int(tiles2[current].numy)]==5 && bridge1==0)
            {
                continue;
            }
            glm::mat4 MVP;  // MVP = Projection * View * Model

            Matrices.model = glm::mat4(1.0f);

            glm::mat4 ObjectTransform;
            glm::mat4 translateObject = glm::translate (glm::vec3(tiles2[current].x,tiles2[current].y,tiles2[current].z)); 
            glm::mat4 rotateTriangle = glm::rotate((float)((tiles2[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));// glTranslatef
            ObjectTransform=translateObject*rotateTriangle;
            Matrices.model *= ObjectTransform;
            //MVP = VP * Matrices.model; // MVP = p * V * M
            if(doM)
                MVP = VP * Matrices.model;
            else
                MVP = VP;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

            draw3DObject(tiles2[current].object);
            //glPopMatrix (); 
        }
          for(map<string,Game>::iterator it=tiles2.begin();it!=tiles2.end();it++){
            string current = it->first; //The name of the current object
            if(gamemap[int(tiles2[current].numx)][int(tiles2[current].numy)]==4 || gamemap[int(tiles2[current].numx)][int(tiles2[current].numy)]==6)
            {
                glm::mat4 MVP;  // MVP = Projection * View * Model

                Matrices.model = glm::mat4(1.0f);

                glm::mat4 ObjectTransform;
                glm::mat4 translateObject = glm::translate (glm::vec3(tiles2[current].x,tiles2[current].y+0.26, tiles2[current].z)); 
                glm::mat4 rotateTriangle = glm::rotate((float)((tiles2[current].anglex)*M_PI/180.0f), glm::vec3(0,0,1));// glTranslatef
                ObjectTransform=translateObject*rotateTriangle;
                Matrices.model *= ObjectTransform;
                //MVP = VP * Matrices.model; // MVP = p * V * M
                if(doM)
                    MVP = VP * Matrices.model;
                else
                    MVP = VP;
                glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

                draw3DObject(Bridges["bridge"].object);
            }
            //glPopMatrix (); 
        }
    }
    for(map<string,Game>::iterator it=cube.begin();it!=cube.end();it++){
        string current = it->first; //The name of the current object
        glm::mat4 MVP;  // MVP = Projection * View * Model
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 ObjectTransform;
        glm::mat4 translateObject = glm::translate (glm::vec3(cube[current].x,cube[current].y, cube[current].z));
        ObjectTransform=translateObject*rotateTriangle1;
        Matrices.model *= ObjectTransform;
        //MVP = VP * Matrices.model; // MVP = p * V * M
        if(doM)
            MVP = VP * Matrices.model;
        else
            MVP = VP;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

        draw3DObject(cube[current].object);
    }
    /*Matrices.model = glm::translate(floor_pos);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    // draw3DObject draws the VAO given to it using current MVP matrix
    draw3DObject(floor_vao);*/
}

}

/* Initialise glfw window, I/O callbacks and the renderer to use */
/* Nothing to Edit here */
GLFWwindow* initGLFW (int width, int height){
    GLFWwindow* window; // window desciptor/handle

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Sample OpenGL 3.3 Application", NULL, NULL);

    if (!window) {
	exit(EXIT_FAILURE);
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    //    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval( 1 );
    glfwSetFramebufferSizeCallback(window, reshapeWindow);
    glfwSetWindowSizeCallback(window, reshapeWindow);
    glfwSetWindowCloseCallback(window, quit);
    glfwSetKeyCallback(window, keyboard);      // general keyboard input
    glfwSetCharCallback(window, keyboardChar);  // simpler specific character handling
    glfwSetMouseButtonCallback(window, mouseButton); 

    return window;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL (GLFWwindow* window, int width, int height)
{
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    //createRectangle ();
    //createCam();
    //createFloor();
	
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders( "Sample_GL.vert", "Sample_GL.frag" );
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

	int k=0,i,j;
    createRectangle1("background",0,cratebrown2,cratebrown2,0,0,2,2,"background",0);
    for(i=0;i<12;i++)
    {
        for(j=0;j<17;j++)
        {
            if(gamemap1[i][j]==1 || gamemap1[i][j]==3 || gamemap1[i][j]==5 || gamemap1[i][j]==6 || gamemap1[i][j]==4)
            {
                string c="tile";
                char d=k+'0';
                string e=c+d;
                if((i+j)%2==0) 
                    createtile(e,0,brown1,brown1,brown1,brown2,2*(i-6),-1,2*(j-8),0.5,2,2,"tile",0,i,j);
                else
                    createtile(e,0,brown2,brown2,brown2,brown1,2*(i-6),-1,2*(j-8),0.5,2,2,"tile",0,i,j);
                k++;
                
            } 
            if(gamemap1[i][j]==2)
            {
                string c="tile";
                char d=k+'0';
                string e=c+d;
                if((i+j)%2==0) 
                    createtile(e,0,gold,gold,gold,coingold,2*(i-6),-1,2*(j-8),0.5,2,2,"tile",0,i,j);
                else
                    createtile(e,0,coingold,coingold,coingold,gold,2*(i-6),-1,2*(j-8),0.5,2,2,"tile",0,i,j);
                k++;            
            }  
            if(gamemap1[i][j]==8)
            {
                string c="tile";
                char d=k+'0';
                string e=c+d;
                createtile(e,0,grey,grey,grey,cloudwhite1,2*(i-6),-1,2*(j-8),0.5,2,2,"tile",0,i,j);
                k++;
            }  
        }
    }
    for(i=0;i<12;i++)
    {
        for(j=0;j<17;j++)
        {
            if(gamemap2[i][j]==1 || gamemap2[i][j]==3 || gamemap2[i][j]==5 || gamemap2[i][j]==6 || gamemap2[i][j]==4)
            {
                string c="tile";
                char d=k+'0';
                string e=c+d;
                if((i+j)%2==0) 
                    createtile(e,0,brown1,brown1,brown1,brown2,2*(i-6),-1,2*(j-8),0.5,2,2,"tile1",0,i,j);
                else
                    createtile(e,0,brown2,brown2,brown2,brown1,2*(i-6),-1,2*(j-8),0.5,2,2,"tile1",0,i,j);
                k++;
                
            } 
            if(gamemap2[i][j]==2)
            {
                string c="tile";
                char d=k+'0';
                string e=c+d;
                if((i+j)%2==0) 
                    createtile(e,0,gold,gold,gold,coingold,2*(i-6),-1,2*(j-8),0.5,2,2,"tile1",0,i,j);
                else
                    createtile(e,0,coingold,coingold,coingold,gold,2*(i-6),-1,2*(j-8),0.5,2,2,"tile1",0,i,j);
                k++;            
            }  
        }
    }
    for(i=0;i<12;i++)
    {
        for(j=0;j<17;j++)
        {
            if(gamemap3[i][j]==1 || gamemap3[i][j]==3 || gamemap3[i][j]==5 || gamemap3[i][j]==6 || gamemap3[i][j]==4)
            {
                string c="tile1";
                char d=k+'0';
                string e=c+d;
                if((i+j)%2==0) 
                    createtile(e,0,brown1,brown1,brown1,brown2,2*(i-6),-1,2*(j-8),0.5,2,2,"tile2",0,i,j);
                else
                    createtile(e,0,brown2,brown2,brown2,brown1,2*(i-6),-1,2*(j-8),0.5,2,2,"tile2",0,i,j);
                k++;
                
            } 
            if(gamemap3[i][j]==2)
            {
                string c="tile1";
                char d=k+'0';
                string e=c+d;
                if((i+j)%2==0) 
                    createtile(e,0,gold,gold,gold,coingold,2*(i-6),-1,2*(j-8),0.5,2,2,"tile2",0,i,j);
                else
                    createtile(e,0,coingold,coingold,coingold,gold,2*(i-6),-1,2*(j-8),0.5,2,2,"tile2",0,i,j);
                k++;            
            }  
        }
    }

    float ycoord=-1;
    for(k=1;k<=21;k++)
    {
        char t=k+'0';
        string u="wall";
        string v=u+t;
        COLOR wallcolor;
        if(k%2==0)
        {
            wallcolor.r=cratebrown.r;
            wallcolor.g=cratebrown.g;
            wallcolor.b=cratebrown.b;
        }
        else
        {
            wallcolor.r=cratebrown1.r;
            wallcolor.g=cratebrown1.g;
            wallcolor.b=cratebrown1.b;            
        }
        createRectangle1(v,0,wallcolor,wallcolor,-0.9,ycoord,0.1,0.2,"background",0);
        ycoord=ycoord+0.1;
    }
    float x[3],y[3];
    x[0]=0;
    x[1]=0.05;
    x[2]=-0.05;
    y[0]=0;
    y[1]=0.05;
    y[2]=0.05;
    createCircle("prestart1",0,skyblue4,0,0,0,2,2,500,"prestart",1);
    createCircle("prestart2",0,skyblue3,0,0,0,1.5,1.5,500,"prestart",1);
    createCircle("prestart3",0,skyblue1,0,0,0,1,1,500,"prestart",1);
    createCircle("prestart4",0,skyblue,0,0,0,0.5,0.5,500,"prestart",1);
    createCircle("bridge",0,grey,0,0,0,0.5,0.5,500,"bridge",1);
    createCircle("heartcircle1",0,red,0.025,0.05,0,0.025,0.025,200,"heart",1);
    //heart["heartcircle1"].status=1;
    createCircle("heartcircle2",0,red,-0.025,0.05,0,0.025,0.025,200,"heart",1);
    //heart["heartcircle2"].status=1;
    createTriangle ("hearttriangle",0,red,x,y,"heart",1);
    createRectangle("cube1",0,red,red,red,red,6,0.25,-14,2,2,2,"cube",0,0,0);
    createRectangle("cube2",0,red,red,red,red,6,2.25,-14,2,2,2,"cube",0,0,0);
    COLOR color=gold;
    float width1=0.1;
    float height1=0.02;
    createRectangle1("top",0,color,color,0,0.1,height1,width1,"score",0);
    createRectangle1("bottom",0,color,color,0,-0.1,height1,width1,"score",0);
    createRectangle1("middle",0,color,color,0,0,height1,width1,"score",0);
    createRectangle1("left1",0,color,color,-0.05,0.05,width1,height1,"score",0);
    createRectangle1("left2",0,color,color,-0.05,-0.05,width1,height1,"score",0);
    createRectangle1("right1",0,color,color,0.05,0.05,width1,height1,"score",0);
    createRectangle1("right2",0,color,color,0.05,-0.05,width1,height1,"score",0);
    createRectangle1("middle1",0,color,color,0,0.05,width1,height1,"score",0);
    createRectangle1("middle2",0,color,color,0,-0.05,width1,height1,"score",0);
    createRectangle1("diagonal1",(atan(0.5)*180/M_PI),color,color,-0.025,0.05,width1,height1,"score",0);
    createRectangle1("diagonal2",-(atan(0.5)*180/M_PI),color,color,0.025,0.05,width1,height1,"score",0);
    createRectangle1("diagonal3",-(atan(0.5)*180/M_PI),color,color,-0.025,-0.05,width1,height1,"score",0);
    createRectangle1("diagonal4",(atan(0.5)*180/M_PI),color,color,0.025,-0.05,width1,height1,"score",0);
    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (0.3f, 0.3f, 0.3f, 0.0f); // R, G, B, A
    //glClearColor (skyblue1.r, skyblue1.g, skyblue1.b, 0.0f);
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    // cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    // cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    // cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    // cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}
int flag=1;
int main (int argc, char** argv)
{
    ISoundEngine* engine = createIrrKlangDevice();
    if (!engine)
    {
        printf("Could not startup engine\n");
    }

    // To play a sound, we only to call play2D(). The second parameter
    // tells the engine to play it looped.

    // play some sound stream, looped
    engine->play2D("irrKlang-64bit-1.5.0/media/bell.wav", false);
    //ISoundEngine* engine = createIrrKlangDevice();
    if (!engine)
    {
        printf("Could not startup engine\n");
    }

    // To play a sound, we only to call play2D(). The second parameter
    // tells the engine to play it looped.

    // play some sound stream, looped
    engine->play2D("irrKlang-64bit-1.5.0/media/e.wav", true);
    int width = 1000;
    int height = 600;
    rect_pos = glm::vec3(0, 0, 0);
    floor_pos = glm::vec3(0, 0, 0);
    do_rot = 0;
    floor_rel = 1;
    int it1,it2;
    GLFWwindow* window = initGLFW(width, height);
    initGLEW();
    initGL (window, width, height);

    last_update_time = glfwGetTime();
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {

	// clear the color and depth in the frame buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // OpenGL Draw commands
	current_time = glfwGetTime();
    angle=135;
	/*if(do_rot)
	    camera_rotation_angle += 90*(current_time - last_update_time); // Simulating camera rotation
	if(camera_rotation_angle > 720)
	    camera_rotation_angle -= 720;*/
    if(current_time-last_update_time >= 1)
    {
        clock1--;
        last_update_time = current_time;
    }
    if(stage==1 && flag==1)
    {
        flag=0;
        bridge=0;
        bridge1=0;
        for(it1=0;it1<12;it1++)
        {
            for(it2=0;it2<17;it2++)
            {
                gamemap[it1][it2]=gamemap1[it1][it2];
            }
        }
    }
    if(stage==2 && flag==0)
    {
        flag=1;
        bridge1=0;
        bridge=0;
        for(it1=0;it1<12;it1++)
        {
            for(it2=0;it2<17;it2++)
            {
                gamemap[it1][it2]=0;
            }
        }
        for(it1=0;it1<12;it1++)
        {
            for(it2=0;it2<17;it2++)
            {
                gamemap[it1][it2]=gamemap2[it1][it2];
            }
        }
    }
    if(stage==3 && flag==1)
    {
        flag=0;
        bridge=0;
        bridge1=0;
        for(it1=0;it1<12;it1++)
        {
            for(it2=0;it2<17;it2++)
            {
                gamemap[it1][it2]=0;
            }
        }
        for(it1=0;it1<12;it1++)
        {
            for(it2=0;it2<17;it2++)
            {
                gamemap[it1][it2]=gamemap3[it1][it2];
            }
        }
    }
    if(life<0 || clock1<0 || moves<0)
    {
        gamelose=1;
    }
    if(stage==4)
    {
        stage=-1;
        gamewin=1;
    }
    partition=1;
	draw(window, 0, 0 , 0.8,1,1, 1, 1);
    partition=0;
	draw(window, 0.8,0,0.2, 1, 0, 0, 0);
	//draw(window, 0, 0.5, 0.5, 0.5, 1, 0, 1);
	//draw(window, 0.5, 0.5, 0.5, 0.5, 0, 0, 1);

        // Swap Frame Buffer in double buffering
        glfwSwapBuffers(window);

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    glfwTerminate();
    //    exit(EXIT_SUCCESS);
}
