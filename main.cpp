#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "bed.h"
#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "directionalLight.h"
#include "SpotLight.h"
#include "walls.h"
#include "bench.h"
#include "swing.h"
#include "stand.h"
#include "cube.h"
#include "stb_image.h"
#include "cylinderStand.h"
#include <iostream>
#include "sphere.h"
#include "cylinder.h"
#include "drawcylinder.h"
struct Point {
    float x;
    float y;
    float z;
};

//boat swing
float dz;
int flagR2 = 5;

//boat swing
float dy1;
int flagR3 = 5;

//Rideright1
float dy2;
int flagR4 = 5;

//Rideright2
float dx2;
int flagR5 = 5;

//TrainRide2
float dx3;
int flagR6 = 5;

//CupRide
float dy3;
int flagR7 = 5;

//CircleRide
float dy4;
int flagR8 = 5;

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
void processInput(GLFWwindow* window);
// settings
const unsigned int SCR_WIDTH = 1500;
const unsigned int SCR_HEIGHT = 800;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

vector<float> cntrlPoints
{
    -0.1200, 1.9950, 5.1000,
    -0.3150, 1.8950, 5.1000,
    -0.4600, 1.7800, 5.1000,
    -0.6000, 1.6600, 5.1000,
    -0.7050, 1.5650, 5.1000,
    -0.8500, 1.4550, 5.1000,
    -0.9550, 1.3800, 5.1000,
    -1.0550, 1.2850, 5.1000,
};

vector<float> cntrlPointsCylinder
{
-0.4500, 1.7950, 5.1000,
-0.4550, 1.4950, 5.1000,
-0.4550, 1.0000, 5.1000,
};

vector<float> cntrlPointsCircle
{
    -0.0550, 1.3700, 5.1000,
        -0.1750, 1.3900, 5.1000,
        -0.2700, 1.3900, 5.1000,
        -0.3700, 1.3700, 5.1000,
        -0.4600, 1.3550, 5.1000,
        -0.5150, 1.3150, 5.1000,
        -0.5450, 1.2800, 5.1000,
        -0.5450, 1.2350, 5.1000,
        -0.5250, 1.1800, 5.1000,
        -0.4750, 1.1550, 5.1000,
        -0.4250, 1.1350, 5.1000,
        -0.3550, 1.1150, 5.1000,
        -0.2850, 1.1000, 5.1000,
        -0.1800, 1.0950, 5.1000,
        -0.1400, 1.0950, 5.1000,
        -0.0900, 1.1000, 5.1000,
};

vector<float> cntrlPointsBoat
{

-0.6900, 1.5350, 5.1000,
-0.5950, 1.4300, 5.1000,
-0.4900, 1.3300, 5.1000,
-0.4100, 1.2250, 5.1000,
-0.4100, 1.2100, 5.1000,
-0.4150, 1.1900, 5.1000,
-0.4050, 1.1900, 5.1000,
-0.3850, 1.2300, 5.1000,
-0.3150, 1.2350, 5.1000,
-0.1950, 1.2350, 5.1000,
-0.0150, 1.2250, 5.1000,
0.1300, 1.2350, 5.1000,
0.3300, 1.2400, 5.1000,
};
vector<float> cntrlPointsCup
{
    -0.0450, 0.5150, 5.1000,
-0.0450, 0.5300, 5.1000,
-0.1200, 0.6300, 5.1000,
-0.1850, 0.8550, 5.1000,
-0.2350, 1.0550, 5.1000,
-0.2650, 1.2650, 5.1000,
};

vector<float> cntrlPointsParachute
{
  0.0100, 0.8600, 5.1000,
-0.1250, 1.0150, 5.1000,
-0.2350, 1.1700, 5.1000,
-0.3450, 1.2950, 5.1000,
-0.4050, 1.4450, 5.1000,
-0.4000, 1.6250, 5.1000,
-0.3200, 1.7750, 5.1000,
-0.1900, 1.8450, 5.1000,
-0.0300, 1.8600, 5.1000,
-0.0300, 1.8600, 5.1000,
};
vector<float> cntrlPointsBucket
{
    -0.6700, 1.3600, 5.1000,
        -0.5900, 1.2700, 5.1000,
        -0.5350, 1.1750, 5.1000,
        -0.4750, 1.0950, 5.1000,
        -0.5100, 1.0300, 5.1000,
        -0.5650, 0.9900, 5.1000,
        -0.6400, 0.9250, 5.1000,
        -0.5550, 0.9550, 5.1000,
        -0.4900, 0.9850, 5.1000,
        -0.4050, 0.9900, 5.1000,
        -0.3350, 0.9800, 5.1000,
        -0.7350, 1.4100, 5.1000,
        -0.7300, 1.4250, 5.1000,
        -0.6650, 1.4050, 5.1000,
        -0.5750, 1.3700, 5.1000,
        -0.4550, 1.3600, 5.1000,
        -0.3900, 1.3700, 5.1000,
        -0.3450, 1.3550, 5.1000,
};
vector<float> cntrlPointsFlower
{
    -0.3100, 1.8450, 5.1000,
        -0.5300, 1.8050, 5.1000,
        -0.7000, 1.7100, 5.1000,
        -0.8000, 1.5700, 5.1000,
        -0.9200, 1.3850, 5.1000,
        -0.9700, 1.2050, 5.1000,
        -1.0050, 1.0400, 5.1000,
        -1.0150, 0.8800, 5.1000,
        -1.0150, 0.8850, 5.1000,
        -0.9950, 0.9100, 5.1000,
        -0.9600, 0.9650, 5.1000,
        -0.8500, 1.0150, 5.1000,
        -0.6550, 1.0750, 5.1000,
        -0.5250, 1.1000, 5.1000,
        -0.4200, 1.1200, 5.1000,
        -0.2700, 1.1250, 5.1000,
};
vector<float> cntrlPointsTriangle
{
    -0.1150, 1.9150, 5.1000,
        -0.3800, 1.7250, 5.1000,
        -0.6900, 1.4500, 5.1000,
        -0.9650, 1.1850, 5.1000,
        -0.9750, 1.1800, 5.1000,
        -0.9650, 1.1800, 5.1000,
        -0.5500, 1.1950, 5.1000,
        -0.1250, 1.2300, 5.1000,
        -0.1200, 1.5600, 5.1000,
        -0.1200, 1.7600, 5.1000,
        -0.1150, 1.9300, 5.1000,
        -0.1150, 1.9300, 5.1000,
        -0.1100, 1.9100, 5.1000,
};
vector <float> coordinates;
vector <float> normals;
vector <int> indices;
vector <float> vertices;
class point
{
public:
    point()
    {
        x = 0;
        y = 0;
    }
    int x;
    int y;
} clkpt[2];
int mouseButtonFlag = 0;
FILE* fp;
const double pi = 3.14159265389;
const int nt = 40;
const int ntheta = 20;
bool showControlPoints = true;
bool loadBezierCurvePoints = false;
bool showHollowBezier = false;
bool lineMode = false;
unsigned int bezierVAO;
unsigned int bezierCylinderVAO;
unsigned int bezierCircleVAO;
unsigned int bezierBoatVAO;
unsigned int bezierCupVAO;
unsigned int bezierParachuteVAO;
unsigned int bezierBucketVAO;
unsigned int bezierFlowerVAO;
unsigned int bezierTriangleVAO;


// camera
Camera camera(glm::vec3(60.0f, 0.5f+5.0f, 70.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);


// positions of the point lights

glm::vec3 pointLightPositions[] = {
    glm::vec3(-5.5f+19.0f,  12.15f,  -20.0f),//-6.6+0.25f+20.0f
    glm::vec3(140.5f,  12.15f,   -20.0f),//6.6+0.25f+20.0f
    glm::vec3(60.5f,  12.15f,   -20.0f),//8.6 + 0.25f
    
};

PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
        // ambient
    0.3f, 0.3f, 0.3f,     // diffuse
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.014f,  //k_l
    0.0007, //k_q
    1       // light number
);


PointLight pointlight3(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.5f, 0.5f, 0.5f,     // ambient
    0.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.35f,  //k_l
    0.44f, //k_q
    2       // light number
);

PointLight pointlight4(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.5f, 0.5f, 0.5f,     // ambient
    0.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.35f,  //k_l
    0.44f, //k_q
    2       // light number
);



DirLight dirLight(
        -0.2f, -1.0f, -0.3f,
        0.05f, 0.05f, 0.05f,
        .5f, 0.5f, 0.5f,     // diffuse
        0.5f, 0.5f, 0.5f
);


SpotLight spotLight(
    -3.50f, 4.0f, -2.0f,
    0.6f, -1.0f, 0.5f,
    0.5f, 0.0f, 0.5f,
    1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,
    0.09f,
    0.032f,
    12.5f,
    15.0f
);



// light settings
bool PointToggle1 = true;
bool PointToggle3 = true;
bool PointToggle4 = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;


// timing
float deltaTime = 1.5f;    // time between current frame and last frame
float lastFrame = 0.0f;


long long nCr(int n, int r);
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L);
unsigned int hollowBezier(GLfloat ctrlpoints[], int L);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    //Shader lightingShader("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    
    //Shader lightingShader("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, //back side of cube, surface normal on -z 
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, //
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);
    bezierVAO = hollowBezier(cntrlPoints.data(), ((unsigned int)cntrlPoints.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();

    bezierCylinderVAO = hollowBezier(cntrlPointsCylinder.data(), ((unsigned int)cntrlPointsCylinder.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();
    bezierCircleVAO = hollowBezier(cntrlPointsCircle.data(), ((unsigned int)cntrlPointsCircle.size() / 3) - 1);

    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();
    bezierBoatVAO = hollowBezier(cntrlPointsBoat.data(), ((unsigned int)cntrlPointsBoat.size() / 3) - 1);

    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();
    bezierCupVAO = hollowBezier(cntrlPointsCup.data(), ((unsigned int)cntrlPointsCup.size() / 3) - 1);

    
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();
    bezierFlowerVAO = hollowBezier(cntrlPointsFlower.data(), ((unsigned int)cntrlPointsFlower.size() / 3) - 1);
    
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();
    bezierTriangleVAO = hollowBezier(cntrlPointsTriangle.data(), ((unsigned int)cntrlPointsTriangle.size() / 3) - 1);


    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //cylinder sadi points
    std::vector<Point> cylinder;
    //cylinder.push_back({ 0, 0, -8 });
    float radius1 = 2.0;
    float radius = 1.0;
    for (float theta = 0; theta <= 360; theta += 1) {
        float x = radius * glm::cos(glm::radians(theta));
        float y = radius * glm::sin(glm::radians(theta));

        float x1 = radius1 * glm::cos(glm::radians(theta));
        float y1 = radius1 * glm::sin(glm::radians(theta));

        cylinder.push_back({ x, y, 0.0f });
        cylinder.push_back({ x1, y1, -2.0f }); // normal cylinder
        //cylinder.push_back({ x * .5f, y * .5f, -8.0f }); // cylinder with different circle radius
    }

    unsigned int CVBO, CVAO;
    glGenVertexArrays(1, &CVAO);
    glGenBuffers(1, &CVBO);

    glBindVertexArray(CVAO);

    glBindBuffer(GL_ARRAY_BUFFER, CVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(struct Point) * cylinder.size(), cylinder.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Point), (void*)0);
    glEnableVertexAttribArray(0);
    //end of sadi cylinder point

    //CYLINDER CIRCLE POINTS START
    std::vector<Point> cylindercircle;
    cylindercircle.push_back({ 0, 0, -8 });
    float radiusC = 6.0;
    //float radius = 1.0;
    for (float theta = 0; theta <= 360; theta += 1) {
        float x = radiusC * glm::cos(glm::radians(theta));
        float y = radiusC * glm::sin(glm::radians(theta));

        //float x1 = radius1 * glm::cos(glm::radians(theta));
        //float y1 = radius1 * glm::sin(glm::radians(theta));

        cylindercircle.push_back({ x, y, -8.0f });
        //cylinder.push_back({ x1, y1, -2.0f }); // normal cylinder
        //cylinder.push_back({ x * .5f, y * .5f, -8.0f }); // cylinder with different circle radius
    }

    unsigned int CcVBO, CcVAO;
    glGenVertexArrays(1, &CcVAO);
    glGenBuffers(1, &CcVBO);

    glBindVertexArray(CcVAO);

    glBindBuffer(GL_ARRAY_BUFFER, CcVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(struct Point) * cylindercircle.size(), cylindercircle.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Point), (void*)0);
    glEnableVertexAttribArray(0);
    //end of sadi cylinderCIRCLE point







    // cylinder maku points start
    std::vector<Point> cylinderMaku;
    cylinderMaku.push_back({ 0, 0, -15 });
    float radiusM = 6.0;
    //float radius = 1.0;
    for (float theta = 0; theta <= 360; theta += 1) {
        float x = radiusM * glm::cos(glm::radians(theta));
        float y = radiusM * glm::sin(glm::radians(theta));

        //float x1 = radius1 * glm::cos(glm::radians(theta));
        //float y1 = radius1 * glm::sin(glm::radians(theta));

        cylinderMaku.push_back({ x, y, -8.0f });
        //cylinder.push_back({ x1, y1, -2.0f }); // normal cylinder
        //cylinder.push_back({ x * .5f, y * .5f, -8.0f }); // cylinder with different circle radius
    }

    unsigned int CMVBO, CMVAO;
    glGenVertexArrays(1, &CMVAO);
    glGenBuffers(1, &CMVBO);

    glBindVertexArray(CMVAO);

    glBindBuffer(GL_ARRAY_BUFFER, CMVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(struct Point) * cylinderMaku.size(), cylinderMaku.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Point), (void*)0);
    glEnableVertexAttribArray(0);
    //end of sadi cylinderMaku point


    //cylinder for rider shade
    std::vector<Point> cylinderShade;
    //cylinder.push_back({ 0, 0, -8 });
    float radiusSh = 3.0;
    for (float theta = 0; theta <= 360; theta += 1) {
        float x = radiusSh * glm::cos(glm::radians(theta));
        float y = radiusSh * glm::sin(glm::radians(theta));

        cylinderShade.push_back({ x, y, 0.0f });
        cylinderShade.push_back({ x, y, -2.0f }); // normal cylinder
        //cylinder.push_back({ x * .5f, y * .5f, -8.0f }); // cylinder with different circle radius
    }

    unsigned int CSVBO, CSVAO;
    glGenVertexArrays(1, &CSVAO);
    glGenBuffers(1, &CSVBO);

    glBindVertexArray(CSVAO);

    glBindBuffer(GL_ARRAY_BUFFER, CSVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(struct Point) * cylinderShade.size(), cylinderShade.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Point), (void*)0);
    glEnableVertexAttribArray(0);
    //end of cylinderShade point



    
    
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------

    // abrar er vdo dekhe ana code
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    //Shader ourShader("vertexShader.vs", "fragmentShader.fs");
    string diffuseMapPath = "./container2.jpg";
    string specularMapPath = "./container2.jpg";
    string diffuseMapRoad = "./road.bmp";
    string specularMapRoad = "./road.bmp";

    string diffuseMapfood1 = "./f1.bmp";
    string specularMapfood1 = "./f1.bmp";

    string diffuseMapfood2 = "./f2.bmp";
    string specularMapfood2 = "./f2.bmp";

    string diffuseMapfood3 = "./f3.bmp";
    string specularMapfood3 = "./f3.bmp";

    string diffuseMapfood4 = "./f4.bmp";
    string specularMapfood4 = "./f4.bmp";

    string diffuseMapfood5 = "./f5.bmp";
    string specularMapfood5 = "./f5.bmp";

    string diffuseMapfood6 = "./f6.bmp";
    string specularMapfood6 = "./f6.bmp";

    string diffuseMapfood7 = "./f7.bmp";
    string specularMapfood7 = "./f7.bmp";

    string diffuseMapfood8 = "./f8.jpg";
    string specularMapfood8 = "./f8.jpg";

    string diffuseMapfood9 = "./f9.bmp";
    string specularMapfood9 = "./f9.bmp";

    string diffuseMaptable = "./t.bmp";
    string specularMaptable = "./t.bmp";

    string diffuseMapboat = "./b1.bmp";
    string specularMapboat = "./b1.bmp";

    string diffuseMapskydrop = "./skydroplogo.bmp";
    string specularMapskydrop = "./skydroplogo.bmp";

    string diffuseMapwall = "./purplewall.bmp";
    string specularMapwall = "./purplewall.bmp";



    string diffuseMapWater = "./water.bmp";
    string specularMapWater = "./water.bmp";
    string diffuseMapWood = "./wood.bmp";
    string specularMapWood = "./wood.bmp";
    string diffuseMapSeeSaw = "./seesawseat.bmp";
    string specularMapSeeSaw = "./seesawseat.bmp";
    string diffuseMapGrass = "./grass.bmp";
    string specularMapGrass = "./grass.bmp";
    string diffuseMapCement = "./cement.bmp";
    string specularMapCement = "./cement.bmp";
    string diffuseMapBrick = "./brick.bmp";
    string specularMapBrick = "./brick.bmp";
    string diffuseMapBench = "./bench.bmp";
    string specularMapBench = "./bench.bmp";
    string diffuseMapMetal = "./metalPole.bmp";
    string specularMapMetal = "./metalPole.bmp";
    string diffuseMapRope = "./rope.bmp";
    string specularMapRope = "./rope.bmp";
    string diffuseMapSky = "./skyfront1.bmp";
    string specularMapSky = "./skyfront1.bmp";
    string diffuseMapSeat = "./planeSeat.bmp";
    string specularMapSeat = "./planeSeat.bmp";
    string diffuseMapStick = "./planeStick.bmp";
    string specularMapStick = "./planeStick.bmp";
    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap1 = loadTexture(diffuseMapRoad.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap1 = loadTexture(specularMapRoad.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap2 = loadTexture(diffuseMapWater.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap2 = loadTexture(specularMapWater.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap3 = loadTexture(diffuseMapWood.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap3 = loadTexture(specularMapWood.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap4 = loadTexture(diffuseMapSeeSaw.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap4 = loadTexture(specularMapSeeSaw.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap5 = loadTexture(diffuseMapGrass.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap5 = loadTexture(specularMapGrass.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap6 = loadTexture(diffuseMapCement.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap6 = loadTexture(specularMapCement.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap7 = loadTexture(diffuseMapBrick.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap7 = loadTexture(specularMapBrick.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap8 = loadTexture(diffuseMapBench.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap8 = loadTexture(specularMapBench.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap9 = loadTexture(diffuseMapMetal.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap9 = loadTexture(specularMapMetal.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap10 = loadTexture(diffuseMapRope.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap10 = loadTexture(specularMapRope.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap11 = loadTexture(diffuseMapSky.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap11 = loadTexture(specularMapSky.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap12 = loadTexture(diffuseMapSeat.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap12 = loadTexture(specularMapSeat.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap13 = loadTexture(diffuseMapStick.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap13 = loadTexture(specularMapStick.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);


    unsigned int diffMap14 = loadTexture(diffuseMapfood1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap14 = loadTexture(specularMapfood1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap15 = loadTexture(diffuseMapfood2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap15 = loadTexture(specularMapfood2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap16 = loadTexture(diffuseMapfood3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap16 = loadTexture(specularMapfood3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
   

    unsigned int diffMap17 = loadTexture(diffuseMapfood4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap17 = loadTexture(specularMapfood4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap18 = loadTexture(diffuseMapfood5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap18 = loadTexture(specularMapfood5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap19 = loadTexture(diffuseMapfood6.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap19 = loadTexture(specularMapfood6.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    unsigned int diffMap20 = loadTexture(diffuseMapfood7.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap20 = loadTexture(specularMapfood7.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap21 = loadTexture(diffuseMapfood8.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap21 = loadTexture(specularMapfood8.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap22 = loadTexture(diffuseMapfood9.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap22 = loadTexture(specularMapfood9.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    
    unsigned int diffMap23 = loadTexture(diffuseMaptable.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap23 = loadTexture(specularMaptable.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    
    unsigned int diffMap24 = loadTexture(diffuseMapboat.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap24 = loadTexture(specularMapboat.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    unsigned int diffMap25 = loadTexture(diffuseMapskydrop.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap25 = loadTexture(specularMapskydrop.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    unsigned int diffMap26 = loadTexture(diffuseMapwall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap26 = loadTexture(specularMapwall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube road = Cube(diffMap1, specMap1, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cylinder water = Cylinder(diffMap2, specMap2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube wood = Cube(diffMap3, specMap3, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube seesaw = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube grass = Cube(diffMap5, specMap5, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube cement = Cube(diffMap6, specMap6, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube brick = Cube(diffMap7, specMap7, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube bench = Cube(diffMap8, specMap8, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube metal = Cube(diffMap9, specMap9, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube rope = Cube(diffMap10, specMap10, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube sky = Cube(diffMap11, specMap11, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube seat = Cube(diffMap12, specMap12, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube stick = Cube(diffMap13, specMap13, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    Cube food1 = Cube(diffMap14, specMap14, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube food2 = Cube(diffMap15, specMap15, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube food3 = Cube(diffMap16, specMap16, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    Cube food4 = Cube(diffMap17, specMap17, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube food5 = Cube(diffMap18, specMap18, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube food6 = Cube(diffMap19, specMap19, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    Cube food7 = Cube(diffMap20, specMap20, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube food8 = Cube(diffMap21, specMap21, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube food9 = Cube(diffMap22, specMap22, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    Cube table = Cube(diffMap23, specMap23, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube boat = Cube(diffMap24, specMap24, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube skydrop = Cube(diffMap25, specMap25, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube wall = Cube(diffMap26, specMap26, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

  //  Cylinder rope = Cylinder(diffMap10, specMap10, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    //std::cout << diffMap << ' ' << specMap << std::endl;
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube cube1 = Cube();
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);
        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 2
        //pointlight2.setUpPointLight(lightingShader);
        // point light 3
        pointlight3.setUpPointLight(lightingShader);
        // point light 4
        pointlight4.setUpPointLight(lightingShader);
        dirLight.setUpDirLight(lightingShader);
        spotLight.setUpSpotLight(lightingShader);
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        
        
        glm::mat4 identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        
        
        /*------------------------------RIDERIGHT----------------------------*/
       
        //top flower
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(97, 13.0, 3.5));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(7, 2.5, 3));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierFlowerVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        // cylinder stand
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(97, -21.5, 3.5));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.5, 20.5, 3.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //cylilnder stand ends

         //draw a circle1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(97, 6.0+ dy2, 3.5));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(5, 2.0, 5.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        //draw a circle2
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(97, 6.5- dy2, 3.5));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(5, 2.0, 5.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends



        /*
                //draw a parachute
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(15, -3.5, 21));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(10.0, 5.5, 5.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierParachuteVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends


        
        
        //draw a circle
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(25, -3.5, 21));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(10, 3.5,12.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(25, -2.7, 21));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 1.5, 2.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        */
         //draw a Boat
        
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(8, 1, 24));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(4, 2.5, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierBoatVAO);
       // glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        
        //draw a boat ends
        

        //draw a cylinder
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(25, -11.5, 21));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.5, 10.5, 0.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends


        /*---------------------------CUPRIE*/
        //draw a cylinder
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5.0, -11.5f, 21.50));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.5, 10.5, 0.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.98f, 0.34f, 0.64f));//rgb(250, 86, 164)
        lightingShader.setVec3("material.diffuse", glm::vec3(0.98f, 0.34f, 0.64f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        
                //top mushroom
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5.0, 2.5- dy3, 21.5));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(5, 2.5, 3));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.87f, 0.19f, 0.39f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.87f, 0.19f, 0.39f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //draw a circle
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5, -3.75+ dy3, 21.5));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(10, 2.5, 7));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.75f, 0.75f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.75f, 0.81f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends

        //cup1
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(2.0, -1.5+ dy3, 22.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(5, 2.5, 3));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.34f, 0.75f, 0.97f));//rgb(87, 190, 247)
        lightingShader.setVec3("material.diffuse", glm::vec3(0.34f, 0.75f, 0.97f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCupVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //pirich1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(2, -1.5+ dy3, 22.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(3, 1.0, 2));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.34f, 0.75f, 0.97f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.34f, 0.75f, 0.97f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        

        //cup2
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(7.75, -1.5+ dy3, 22.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(5, 2.5, 3));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.34f, 0.75f, 0.97f));//rgb(87, 190, 247)
        lightingShader.setVec3("material.diffuse", glm::vec3(0.34f, 0.75f, 0.97f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCupVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //pirich2
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(7.75, -1.5+ dy3, 22.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(3, 1.0, 2));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.34f, 0.75f, 0.97f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.34f, 0.75f, 0.97f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends

        //cup3
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5.0, -1.5+ dy3, 23.5));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(5, 2.5, 3));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.34f, 0.75f, 0.97f));//rgb(87, 190, 247)
        lightingShader.setVec3("material.diffuse", glm::vec3(0.34f, 0.75f, 0.97f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCupVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //pirich3
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5.0, -1.5+ dy3, 23.5));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(3, 1.0, 2));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.34f, 0.75f, 0.97f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.34f, 0.75f, 0.97f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends

        //cup4
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5.0, -1.5+ dy3, 19.5));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(5, 2.5, 3));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.34f, 0.75f, 0.97f));//rgb(87, 190, 247)
        lightingShader.setVec3("material.diffuse", glm::vec3(0.34f, 0.75f, 0.97f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCupVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //pirich4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5.0, -1.5+ dy3, 19.5));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(3, 1.0, 2));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.34f, 0.75f, 0.97f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.34f, 0.75f, 0.97f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends




        /*------------------RIERIGHT2----------------------------*/
    //top mushroom
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(121+ dx2, 9.5, 1.5));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1.5, 1.0, 1.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //own muhroom
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(121+ dx2, 12.5, 1.5));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 2.0, 2));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 0.0f, 0.8f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 0.0f, 0.8f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //top triangle
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(121, 5.0, 1.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 7.0, 5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.5f));//204, 85, 0
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.5f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierTriangleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);


        /*------------------RollerCoaster----------------------------*/

                //cup
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(100.5+ dx3, 8.7, 23.5));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(4, 2.5, 3));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCupVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);


        //draw a circle1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(98+ dx3, 6.5, 24.55));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1, 2.75, 0.05));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.75f, 0.75f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.75f, 0.81f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends

        //draw a circle2
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(99.5+ dx3, 6.5, 24.55));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1, 2.75, 0.05));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.75f, 0.75f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.75f, 0.81f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends

        //draw a circle3
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(98+ dx3, 6.5, 22.45));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1, 2.75, 0.05));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.75f, 0.75f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.75f, 0.81f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends

        //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(99.5+ dx3, 6.5, 22.45));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1, 2.75, 0.05));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.75f, 0.75f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.75f, 0.81f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends

        //--------------------------TREE--------------------------------//
                //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-6, -11.0, 35.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-6, -9.5, 35.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        // 
        //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-6, -11.0, 25.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-6, -9.5, 25.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        // 
        //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-6, -11.0, 15.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-6, -9.5, 15.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        // 
        //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-6, -11.0, 5.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-6, -9.5, 5.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        // 
        //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-6, -11.0, -5.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-6, -9.5, -5.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        // 
        //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-5, -11.0, -10.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-5, -9.5, -10.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        // majhe
        //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(0, -11.0, -10.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(0, -9.5, -10.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(10, -11.0, -10.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(10, -9.5, -10.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(20, -11.0, -10.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(20, -9.5, -10.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        // 
        //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(30, -11.0, -10.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(30, -9.5, -10.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        // 
        //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(40, -11.0, -10.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(40, -9.5, -10.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        // 
        //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(50, -11.0, -10.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(50, -9.5, -10.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        // 
        //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(60, -11.0, -10.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(60, -9.5, -10.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(70, -11.0, -10.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(70, -9.5, -10.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        // 
        //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(80, -11.0, -10.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(80, -9.5, -10.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        // 
        //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(90, -11.0, -10.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(90, -9.5, -10.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        // 
        //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(100, -11.0, -10.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(100, -9.5, -10.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        // 
        //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(110, -11.0, -10.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(110, -9.5, -10.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(120, -11.0, -10.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(120, -9.5, -10.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(130, -11.0, -10.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(130, -9.5, -10.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
         //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(140, -11.0, -10.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(140, -9.5, -10.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
                //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(146.5, -11.0, 0.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(146.5, -9.5, 0.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
                        //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(146.5, -11.0, 10.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(146.5, -9.5, 10.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
        
                        //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(146.5, -11.0, 20.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(146.5, -9.5, 20.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
                        //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(146.5, -11.0, 30.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(146.5, -9.5, 30.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends
                        //         //         //         //                 //draw a cylinder1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(146.5, -11.0, 40.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.0, 10.0, 2.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.59f, 0.29f, 0.0f));//0.15f, 0.55f, 0.05f
        lightingShader.setVec3("material.diffuse", glm::vec3(0.59f, 0.29f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        // 
        //         // //draw a circle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(146.5, -9.5, 40.0));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6, 15.0, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends



        // camera/view transformation
        /*
        float degree = 0;
        glm::mat4 view = camera.GetViewMatrix();
        float r = glm::length(camera.Position - glm::vec3(view[3]));
        ourShader.setMat4("view", view);
       
       */

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first


        /*------------------------------ GROUND----------------------------*/
        glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
        translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-10, -1.1, -15.0));
        rotateXMatrix1 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix1 = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix1 = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix1 = glm::scale(identityMatrix, glm::vec3(160.0, 55.0, 0.0));
        model1 = translateMatrix1 * rotateXMatrix1 * rotateYMatrix1 * rotateZMatrix1 * scaleMatrix1;
        lightingShader.setMat4("model", model1);
        grass.drawCubeWithTexture(lightingShaderWithTexture, model1);



       

        /*------------------------------ ROAD----------------------------*/
       // glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
        translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-10, -1.1, 40.0));
        rotateXMatrix1 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix1 = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix1 = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix1 = glm::scale(identityMatrix, glm::vec3(160.0, 5.0, 0.0));
        model1 = translateMatrix1 * rotateXMatrix1 * rotateYMatrix1 * rotateZMatrix1 * scaleMatrix1;
        lightingShader.setMat4("model", model1);
        rope.drawCubeWithTexture(lightingShaderWithTexture, model1);
       
        /*----------------------------SKY----------------------------------*/
        glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
        //sky middle
        translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-10.0f, -1.1f, -15.0f));
        scaleMatrix2 = glm::scale(identityMatrix, glm::vec3(160.0f, 35.0f, 0.0f));
        model2 = translateMatrix2 * scaleMatrix2;
        sky.drawCubeWithTexture(lightingShaderWithTexture, model2);

        //skyleft
        translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-10.0f, -1.1f, -15.0f));
        scaleMatrix2 = glm::scale(identityMatrix, glm::vec3(0.0f, 35.0f, 60.0f));
        model2 = translateMatrix2 * scaleMatrix2;
        sky.drawCubeWithTexture(lightingShaderWithTexture, model2);

        //skyright
        translateMatrix2 = glm::translate(identityMatrix, glm::vec3(150.0f,-1.1f, -15.0f));
        scaleMatrix2 = glm::scale(identityMatrix, glm::vec3(0.0f, 35.0f,60.0f));
        model2 = translateMatrix2 * scaleMatrix2;
        sky.drawCubeWithTexture(lightingShaderWithTexture, model2);


        /*--------------------------RIDE RIGHT1------------------------*/

        //ground

        glm::mat4 translateMatrix3, rotateXMatrix3, rotateYMatrix3, rotateZMatrix3, scaleMatrix3, model3;

        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(87.0f, -1.05f, -4.50f));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(20.0f, 0.0f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        wood.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //fence(x-axis)
      //standmiddle
      //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(87.0, 0.0, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(30.0f, 0.15f, 0.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(87.0, 1.5, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(30.0f, 0.15f, 0.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standleft
        //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(87.0, 0.0, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(87.0, 1.5, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standright
        //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(107.0, 0.0, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.15f, 0.0f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(107.0, 1.5, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.15f, 0.0f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //fence(y-axis)
//standmile
// stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(87.0, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(89.5, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(92.0, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(94.5, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(97.0, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(99.5, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand7
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(102.0, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand8
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(104.5, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand9
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(107.0, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);


        //fence(y-axis)
         //standright
        // stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(107.0, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(107.0, -1.05, -2.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(107.0, -1.05, 0.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(107.0, -1.05, 3.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(107.0, -1.05, 5.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(107.0, -1.05, 7.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //stand8
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(107.0, -1.05, 10.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);
//standleft
        // stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(87.0, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(87.0, -1.05, -2.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(87.0, -1.05, 0.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(87.0, -1.05, 3.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(87.0, -1.05, 5.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(87.0, -1.05, 7.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //stand8
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(87.0, -1.05, 10.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

     
        //boy
        glm::mat4 translateMatrix4, rotateXMatrix4, rotateYMatrix4, rotateZMatrix4, scaleMatrix4, model4;
        //leg1
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(97.9, 8.5- dy2, 4.25));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.15, -8.0, 0.15));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model4);
        //leg2
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(96, 8.5+ dy2, 4.25));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.15, -8.0, 0.15));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //leg3
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(97.95, 8.5- dy2, 2.5));
        rotateYMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.15, -8.0, 0.15));
        model4 = translateMatrix4 * rotateYMatrix4 * scaleMatrix4;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model4);
        //leg4
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(96, 8.5+ dy2, 2.5));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.15, -8.0, 0.15));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model4);
        
        //1 floor1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(89.5, 1.5+ dy2, 0.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(2.8f, 0.5f, 6.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        table.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //1 handle1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(89.5, 2.5+ dy2, 0.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(2.5f, 0.5f, 0.5f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //1 handle2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(89.5, 2.5+ dy2, 6.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(2.5f, 0.5f, 0.5f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //1 handle3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(89.5, 2.5+ dy2, 0.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, 6.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //1 BACK1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(92.0, 1.5+ dy2, 0.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.5f, 2.8f, 6.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        table.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //2 floor1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(101.5, 1.5- dy2, 0.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(2.8f, 0.5f, 6.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        table.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //1 handle1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(102, 2.5- dy2, 0.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(2.5f, 0.5f, 0.5f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //1 handle2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(102, 2.5- dy2, 6.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(2.5f, 0.5f, 0.5f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //1 handle3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(104, 2.5- dy2, 0.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, 6.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //2 BACK1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(101.5, 1.5- dy2, 0.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.5f, 2.8f, 6.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        table.drawCubeWithTexture(lightingShaderWithTexture, model3);

        if (flagR4 == 1)
        {
            dy2 = dy2 + 0.1;
            if (dy2 >= 2.5)
            {
                flagR4 = 2;
            }

        }
        if (flagR4 == 2)
        {
            dy2 = dy2 - 0.1;
            if (dy2 <= -2.5 )
            {
                flagR4 = 3;
            }
        }
        if (flagR4 == 3)
        {
            dy2 = dy2 + 0.1;
            if (dy2 >= 2.5)
            {
                flagR4 = 4;
            }

        }
        if (flagR4 == 4)
        {
            dy2 = dy2 - 0.1;
            if (dy2 <= 0)
            {
                flagR4 = 7;
            }
        }
        /*--------------------------BENCHES------------------------*/

        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(48.0, -1.0 , 15.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(2.5f, 2.0f, 6.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        food7.drawCubeWithTexture(lightingShaderWithTexture, model3);
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(50.0, 1.0, 15.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.5f, 3.0f, 6.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        food7.drawCubeWithTexture(lightingShaderWithTexture, model3);


        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(83.0, -1.0, 15.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(2.5f, 2.0f, 6.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        food7.drawCubeWithTexture(lightingShaderWithTexture, model3);
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(83.0, 1.0, 15.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.5f, 3.0f, 6.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        food7.drawCubeWithTexture(lightingShaderWithTexture, model3);



        /*--------------------------RIDE RIGHT2------------------------*/

//groun
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(115.0f, -1.05f, -4.50f));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(30.0f, 0.0f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        wood.drawCubeWithTexture(lightingShaderWithTexture, model3);
       
        //fence(x-axis)
      //standmiddle
      //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(115.0, 0.0, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(30.0f, 0.15f, 0.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(115.0, 1.5, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(30.0f, 0.15f, 0.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standleft
        //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(115.0, 0.0, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(115.0, 1.5, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standright
        //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(145.0, 0.0, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.15f, 0.0f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(145.0, 1.5, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.15f, 0.0f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //fence(y-axis)
//standmile
// stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(115.0, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(117.5, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(120.0, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(122.5, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(125.0, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(127.5, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand7
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(130.0, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand8
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(132.5, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand9
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(135.0, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand10
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(137.5, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand11
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(140.0, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //stand12
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(142.5, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand13
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(145.0, -1.05, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);


        //fence(y-axis)
//standleft
        // stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(115.0, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(115.0, -1.05, -2.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(115.0, -1.05, 0.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(115.0, -1.05, 3.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(115.0, -1.05, 5.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(115.0, -1.05, 7.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        

        //stand8
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(115.0, -1.05, 10.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);


        //fence(y-axis)
        //standright
                // stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(145.0, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(145.0, -1.05, -2.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(145.0, -1.05, 0.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(145.0, -1.05, 3.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(145.0, -1.05, 5.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(145.0, -1.05, 7.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        

        //stand8
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(145.0, -1.05, 10.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        ////////////////////////////////////////////////////


        glm::mat4 translateMatrix10, rotateXMatrix10, rotateYMatrix10, rotateZMatrix10, scaleMatrix10, model10;
        // stand1
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(117.0, -1.05, 1.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.50f, 15.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand2
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(140.0, -1.05, 1.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.50f, 15.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand11
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(118.0, -1.05, -1.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.50f, 8.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand22
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(118.0, -1.05, 3.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.50f, 8.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand11
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(123.0, -1.05, -1.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.50f, 8.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand22
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(123.0, -1.05, 3.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.50f, 8.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand23
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(118.0, 6.95, -1.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(5.5f, 0.5f, 5.0f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand23back1
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(118.0, 8.5, -1.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(5.5f, 0.25f, 0.25f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand23back2
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(118.0, 10.25, -1.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(5.5f, 0.25f, 0.25f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand23leftback
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(118.0, 6.95, -1.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.25f, 7.0f, 0.25f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand23leftfront
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(118.0, 6.95, 3.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.25f, 7.0f, 0.25f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand23rightback
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(123.25, 6.95, -1.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.25f, 7.0f, 0.25f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand23rightfront
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(123.25, 6.95, 3.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.25f, 7.0f, 0.25f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand23front1
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(118.0, 8.5, 3.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(5.5f, 0.25f, 0.25f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand23front2
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(118.0, 10.25, 3.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(5.5f, 0.25f, 0.25f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);


        // stand23left11
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(118.0, 8.5, -1.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.25f, 0.25f, 5.0f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand23left22
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(118.0, 10.25, -1.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.25f, 0.25f, 5.0f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);

        //stairfront

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(123.0, 7.0, 3.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, -10.0, 0.5));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stairback

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(123.0, 7.0, -1.5));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, -10.0, 0.5));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair1

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(124.0, 6.0, 4.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -6.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair2

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(124.5, 5.0, 4.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -6.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair3

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(125.0, 4.0, 4.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -6.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair4

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(125.5, 3.0, 4.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -6.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair5

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(126.0, 2.0, 4.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -6.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair6

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(126.5, 1.0, 4.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -6.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair7

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(127.0, 0.0, 4.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -6.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);
        // stand3
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(117.0, 11.95, 1.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(23.5f, 0.05f, 0.3f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);

        
        glm::mat4 translateMatrix11, rotateXMatrix11, rotateYMatrix11, rotateZMatrix11, scaleMatrix11, model11;

        // stand4
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(121.0+ dx2, 8.5, 1.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.050f, 3.5f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model10);

        if (flagR5 == 1)
        {
            dx2 = dx2 + 0.1;
            if (dx2 >= 15)
            {
                flagR5 = 2;
            }

        }
        if (flagR5 == 2)
        {
            dx2 = dx2 - 0.1;
            if (dx2 <= -0.5)
            {
                flagR5 = 5;
            }
        }
        /*--------------------------TrainCoaster------------------------*/

//groun
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(95.0f, -1.05f, 14.50f));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(40.0f, 0.0f, 20.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        wood.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //fence(x-axis)
        //standmiddle
        //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(95.0, 0.0, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(40.0f, 0.15f, 0.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(95.0, 1.5, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(40.0f, 0.15f, 0.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standleft
        //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(95.0, 0.0, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 20.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(95.0, 1.5, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 20.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standright
        //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(135.0, 0.0, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.15f, 0.0f, 20.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(135.0, 1.5, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.15f, 0.0f, 20.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //fence(y-axis)
//standmile
// stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(95.0, -1.05, 14.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(97.5, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(100.0, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(102.5, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(105.0, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(107.5, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand7
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(110.0, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand8
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(112.5, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand9
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(115.0, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand10
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(117.5, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand11
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(120.0, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //stand12
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(122.5, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand13
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(125.0, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand14
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(127.5, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //stand15
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(130.0, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //stand16
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(132.5, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //stand17
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(135.0, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);


        //fence(y-axis)
//standright
        // stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(135.0, -1.05, 14.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(135.0, -1.05, 17.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(135.0, -1.05, 19.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(135.0, -1.05, 22.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(135.0, -1.05, 24.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(135.0, -1.05, 27.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand7
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(135.0, -1.05, 29.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand8
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(135.0, -1.05, 32.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //stand9
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(135.0, -1.05, 35.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);



        //fence(y-axis)
        //standleft
        // stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(95.0, -1.05, 14.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(95.0, -1.05, 17.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(95.0, -1.05, 19.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(95.0, -1.05, 22.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(95.0, -1.05, 24.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(95.0, -1.05, 27.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand7
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(95.0, -1.05, 29.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand8
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(95.0, -1.05, 32.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //stand7
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(95.0, -1.05, 35.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);
        // train cube
        // 
        glm::mat4 translateMatrix12, rotateXMatrix12, rotateYMatrix12, rotateZMatrix12, scaleMatrix12, model12;

        //1
        translateMatrix12 = glm::translate(identityMatrix, glm::vec3(97.25f+ dx3, 10.0f, 22.50f));
        scaleMatrix12 = glm::scale(identityMatrix, glm::vec3(1.0f, 1.8f, 2.0f));
        model12 = translateMatrix12 * scaleMatrix12;
        food6.drawCubeWithTexture(lightingShaderWithTexture, model12);

        //2
        translateMatrix12 = glm::translate(identityMatrix, glm::vec3(98.25f+ dx3, 10.0f, 22.50f));
        scaleMatrix12 = glm::scale(identityMatrix, glm::vec3(1.0f, 1.8f, 2.0f));
        model12 = translateMatrix12 * scaleMatrix12;
        food7.drawCubeWithTexture(lightingShaderWithTexture, model12);

        //3
        translateMatrix12 = glm::translate(identityMatrix, glm::vec3(99.25f+ dx3, 10.0f, 22.50f));
        scaleMatrix12 = glm::scale(identityMatrix, glm::vec3(1.0f, 1.8f, 2.0f));
        model12 = translateMatrix12 * scaleMatrix12;
        food6.drawCubeWithTexture(lightingShaderWithTexture, model12);

        if (flagR6 == 1)
        {
            dx3 = dx3 + 0.2;
            if (dx3 >= 28)
            {
                flagR6 = 2;
            }

        }
        if (flagR6 == 2)
        {
            dx3 = dx3 - 0.2;
            if (dx3 <= 0)
            {
                flagR6 = 5;
            }
        }
        // stand1
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(98.0, -1.05, 22.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.50f, 10.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand2
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(98.0, -1.05, 24.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.50f, 10.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand11
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(97.0, -1.05, 21.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.50f, 13.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand12
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(97.0, -1.05, 25.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.50f, 13.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand21
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(100.0, -1.05, 21.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.50f, 13.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand22
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(100.0, -1.05, 25.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.50f, 13.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        //floor
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(97.0, 8.95, 21.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(3.5f, 0.5f, 4.0f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        //floor1
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(97.0, 10.25, 21.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(3.5f, 0.1f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        //floor2
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(97.0, 11.5, 21.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(3.5f, 0.1f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        //floor3
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(97.0, 10.25, 25.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(3.5f, 0.1f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        //floor4
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(97.0, 11.5, 25.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(3.5f, 0.1f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        //floor5
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(97.0, 11.5, 21.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.05f, 0.1f, 4.0f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        //floor6
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(97.0, 10.25, 21.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.05f, 0.1f, 4.0f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        //left
        //stairfront

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(100.0, 8.95, 21.5));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, -11.5, 0.5));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stairback

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(100.0, 8.95, 25.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, -11.5, 0.5));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair1

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(101.0, 7.95, 26.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -5.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair2

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(101.5, 6.95, 26.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -5.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair3

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(102.0, 5.95, 26.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -5.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair4

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(102.5, 4.95, 26.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -5.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair5

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(103.0, 3.95, 26.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -5.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair6

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(103.5, 2.95, 26.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -5.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair7

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(104.0, 1.95, 26.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -5.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair8

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(104.5, 0.95, 26.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -5.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair9

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(105.0, -0.05, 26.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -5.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);


        //right
        //stairfront

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(128.0, 8.95, 21.5));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, -11.5, 0.5));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stairback

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(128.0, 8.95, 25.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, -11.5, 0.5));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair1

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(127.0, 7.95, 26.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -5.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair2

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(126.5, 6.95, 26.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -5.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair3

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(126.0, 5.95, 26.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -5.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair4

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(125.5, 4.95, 26.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -5.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair5

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(125.0, 3.95, 26.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -5.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair6

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(124.5, 2.95, 26.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -5.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair7

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(124.0, 1.95, 26.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -5.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair8

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(123.5, 0.95, 26.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -5.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //stair9

        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(123.0, -0.05, 26.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, -5.0));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model4);


        // stand3
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(130.0, -1.05, 22.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.50f, 10.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand4
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(130.0, -1.05, 24.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.50f, 10.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand5
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(98.0, 8.95, 22.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(32.5f, 0.5f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand6
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(98.0, 8.95, 24.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(32.5f, 0.5f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand7
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(98.0, 8.95, 22.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.05f, 0.5f, 2.0f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand8
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(100.5, 8.95, 22.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.05f, 0.5f, 2.0f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand9
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(103, 8.95, 22.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.05f, 0.5f, 2.0f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand8
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(105.5, 8.95, 22.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.05f, 0.5f, 2.0f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand8
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(108, 8.95, 22.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.05f, 0.5f, 2.0f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand8
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(110.5, 8.95, 22.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.05f, 0.5f, 2.0f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand8
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(113, 8.95, 22.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.05f, 0.5f, 2.0f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand8
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(115.5, 8.95, 22.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.05f, 0.5f, 2.0f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand8
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(118, 8.95, 22.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.05f, 0.5f, 2.0f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);
        
        //right

        // stand11
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(131.0, -1.05, 21.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.50f, 13.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand12
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(131.0, -1.05, 25.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.50f, 13.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand21
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(128.0, -1.05, 21.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.50f, 13.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand22
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(128.0, -1.05, 25.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.50f, 13.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        //floor
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(128.0, 8.95, 21.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(3.5f, 0.5f, 4.0f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        //floor1
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(128.0, 10.25, 21.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(3.5f, 0.1f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        //floor2
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(128.0, 11.5, 21.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(3.5f, 0.1f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        //floor3
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(128.0, 10.25, 25.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(3.5f, 0.1f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        //floor4
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(128.0, 11.5, 25.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(3.5f, 0.1f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        //floor5
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(131.0, 11.5, 21.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.05f, 0.1f, 4.0f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        //floor6
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(131.0, 10.25, 21.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(0.05f, 0.1f, 4.0f));
        model10 = translateMatrix10 * scaleMatrix10;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model10);

        /*--------------------------CUP------------------------*/

        //ground

        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.05f, 14.50f));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(15.0f, 0.0f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        wood.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //fence(x-axis)
        //standmiddle
        //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0, 0.0, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(15.0f, 0.15f, 0.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0, 1.5, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(15.0f, 0.15f, 0.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standleft
        //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0, 0.0, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0, 1.5, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standright
        //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(12.0, 0.0, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.15f, 0.0f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(12.0, 1.5, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.15f, 0.0f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //fence(y-axis)
//standmile
// stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0, -1.05, 14.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-0.5, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(2.0, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(4.5, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(7.0, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(9.5, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand7
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(12.0, -1.05, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);



        //fence(y-axis)
//standright
// stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(12.0, -1.05, 14.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(12.0, -1.05, 17.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(12.0, -1.05, 19.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(12.0, -1.05, 22.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(12.0, -1.05, 24.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(12.0, -1.05, 27.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand7
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(12.0, -1.05, 29.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);



        //fence(y-axis)
        //standleft
        // stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0, -1.05, 14.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0, -1.05, 17.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0, -1.05, 19.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0, -1.05, 22.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0, -1.05, 24.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0, -1.05, 27.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand7
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0, -1.05, 29.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

       // glm::mat4 translateMatrix10, rotateXMatrix10, rotateYMatrix10, rotateZMatrix10, scaleMatrix10, model10;
        // stand1
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(2.0, -0.5+ dy3, 22.0));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(-0.10f, 3.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand2
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(1.45, 2.5+ dy3, 22.0));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(1.0f, -0.10f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model10);
        //stan3
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(7.8, -0.5+ dy3, 22.0));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(-0.10f, 3.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand4
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(7.25, 2.5+ dy3, 22.0));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(1.0f, -0.10f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model10);

        //stan5
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(5.0, -0.5+ dy3, 23.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(-0.10f, 3.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand6
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(4.45, 2.5+ dy3, 23.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(1.0f, -0.10f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model10);

        //stan7
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(5.0, -0.5+ dy3, 19.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(-0.10f, 3.0f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model10);

        // stand8
        translateMatrix10 = glm::translate(identityMatrix, glm::vec3(4.45, 2.5+ dy3, 19.5));
        scaleMatrix10 = glm::scale(identityMatrix, glm::vec3(1.0f, -0.10f, 0.05f));
        model10 = translateMatrix10 * scaleMatrix10;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model10);

        if (flagR7 == 1)
        {
            dy3 = dy3 + 0.1;
            if (dy3 >= 2)
            {
                flagR7 = 2;
            }

        }
        if (flagR7 == 2)
        {
            dy3 = dy3 - 0.1;
            if (dy3 <= 0.0)
            {
                flagR7 = 5;
            }
        }


        /*--------------------------FOOD COURT------------------------*/

        //ground

        //glm::mat4 translateMatrix3, rotateXMatrix3, rotateYMatrix3, rotateZMatrix3, scaleMatrix3, model3;

        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(52.0f, -1.05f, 2.50f));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(30.0f, 0.0f, 20.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        wood.drawCubeWithTexture(lightingShaderWithTexture, model3);
        
        //fence(y-axis)
        //standleft
        // stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(52.0, -1.05, 2.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(52.0, -1.05, 5.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(52.0, -1.05, 7.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(52.0, -1.05, 10.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(52.0, -1.05, 12.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(52.0, -1.05, 15.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand7
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(52.0, -1.05, 17.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand8
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(52.0, -1.05, 20.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand9
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(52.0, -1.05, 22.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standright
        // stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(82.0, -1.05, 2.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(82.0, -1.05, 5.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(82.0, -1.05, 7.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(82.0, -1.05, 10.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(82.0, -1.05, 12.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(82.0, -1.05, 15.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand7
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(82.0, -1.05, 17.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand8
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(82.0, -1.05, 20.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand9
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(82.0, -1.05, 22.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standmiddle
        // stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(54.5, -1.05, 2.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);
        
        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(57.0, -1.05, 2.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);
       
        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(59.5, -1.05, 2.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(62.0, -1.05, 2.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(64.5, -1.05, 2.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(67.0, -1.05, 2.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand7
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(69.5, -1.05, 2.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand8
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(72.0, -1.05, 2.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand9
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(74.5, -1.05, 2.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand10
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(77.0, -1.05, 2.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand11
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(79.5, -1.05, 2.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //fence(x-axis)
        //standmiddle
        //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(52.0, 0.0, 2.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(30.0f, 0.15f, 0.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(52.0, 1.5, 2.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(30.0f, 0.15f, 0.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standleft
        //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(52.0, 0.0, 2.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 20.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(52.0, 1.5, 2.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 20.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standright
        //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(82.0, 0.0, 2.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.15f, 0.0f, 20.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(82.0, 1.5, 2.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.15f, 0.0f, 20.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //foodshop1

        //1 back
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(54.5, -1.05, 2.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(7.0f, 7.0f, 0.5f));
        model3 = translateMatrix3 * scaleMatrix3;
        food2.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //1 front1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(54.5, -1.05, 5.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(7.0f, 3.0f, 0.5f));
        model3 = translateMatrix3 * scaleMatrix3;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //1 front2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(54.5, 4.45, 5.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(7.0f, 2.0f, 0.5f));
        model3 = translateMatrix3 * scaleMatrix3;
        food1.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //1 floor
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(54.5, -1.05, 2.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(6.5f, 0.5f, 3.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        wall.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //1 floor1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(54.6, 1.95, 4.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(6.8f, 0.5f, 2.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        wood.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //1 ceiling
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(54.5, 5.95, 2.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(7.0f, 0.5f, 3.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        wall.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //1left
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(54.5f, -1.05f, 2.5f));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.5f, 7.0f, 3.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //1right
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(61.0f, -1.05f, 2.5f));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.5f, 7.0f, 3.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        food3.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //foodshop2
        
        //2 back
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(63.5, -1.05, 2.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(7.0f, 7.0f, 0.5f));
        model3 = translateMatrix3 * scaleMatrix3;
        food4.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //2 front1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(63.5, -1.05, 5.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(7.0f, 3.0f, 0.5f));
        model3 = translateMatrix3 * scaleMatrix3;
        food6.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //2 front2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(63.5, 4.45, 5.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(7.0f, 2.0f, 0.5f));
        model3 = translateMatrix3 * scaleMatrix3;
        food5.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //2 floor
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(63.5, -1.05, 2.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(6.5f, 0.5f, 3.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        wall.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //2 floor1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(63.6, 1.95, 4.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(6.8f, 0.5f, 2.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        wood.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //2 ceiling
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(63.5, 5.95, 2.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(7.0f, 0.5f, 3.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        wall.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //2left
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(63.5f, -1.05f, 2.5f));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.5f, 7.0f, 3.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        food6.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //2right
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(70.0f, -1.05f, 2.5f));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.5f, 7.0f, 3.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        food6.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //foodshop3
        // //3 back
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(72.5, -1.05, 2.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(7.0f, 7.0f, 0.5f));
        model3 = translateMatrix3 * scaleMatrix3;
        food8.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //3front1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(72.5, -1.05, 5.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(7.0f, 3.0f, 0.5f));
        model3 = translateMatrix3 * scaleMatrix3;
        food7.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //3 front2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(72.5, 4.45, 5.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(7.0f, 2.0f, 0.5f));
        model3 = translateMatrix3 * scaleMatrix3;
        food9.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //3 floor
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(72.5, -1.05, 2.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(6.5f, 0.5f, 3.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        wall.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //3 floor1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(72.6, 1.95, 4.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(6.8f, 0.5f, 2.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        wood.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //3 ceiling
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(72.5, 5.95, 2.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(7.0f, 0.5f, 3.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        wall.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //3left
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(72.5f, -1.05f, 2.5f));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.5f, 7.0f, 3.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        food7.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //3right
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(79.0f, -1.05f, 2.5f));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.5f, 7.0f, 3.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        food7.drawCubeWithTexture(lightingShaderWithTexture, model3);
        
        //table1

        float rotateAngle_Y = 0.0;


        glm::mat4 rotateY = glm::mat4(1.0f);
        glm::mat4 rotateZ = glm::mat4(1.0f);
       // glm::mat4 translateMatrix4, rotateXMatrix4, rotateYMatrix4, rotateZMatrix4, scaleMatrix4, model4;

        //base
        for (float i = 0.0f; i < 360.0f; i += 0.50f) {
            //Center

            translateMatrix4 = glm::translate(identityMatrix, glm::vec3(57.5, 1.5, 18.0));
            rotateYMatrix4 = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(2.5, 0.15, 0.5));
            model4 = translateMatrix4 * rotateYMatrix4 * scaleMatrix4;
            table.drawCubeWithTexture(lightingShaderWithTexture, model4);
        }
        //leg1
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(57.5, 1.6, 18.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.15, -3.0, 0.05));
        model4 =  translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);
        //leg2
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(57.5, 1.6, 18.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.15, -3.0, 0.05));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);
        //table2
        //base
        for (float i = 0.0f; i < 360.0f; i += 0.50f) {
            //Center

            translateMatrix4 = glm::translate(identityMatrix, glm::vec3(57.5, 1.5, 10.0));
            rotateYMatrix4 = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(2.5, 0.15, 0.5));
            model4 = translateMatrix4 * rotateYMatrix4 * scaleMatrix4;
            table.drawCubeWithTexture(lightingShaderWithTexture, model4);
        }
        //leg3
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(57.5, 1.6, 10.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.15, -3.0, 0.05));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);
        //leg4
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(57.5, 1.6, 10.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.15, -3.0, 0.05));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);
        //table3
        //base
        for (float i = 0.0f; i < 360.0f; i += 0.50f) {
            //Center

            translateMatrix4 = glm::translate(identityMatrix, glm::vec3(66.5, 1.5, 18.0));
            rotateYMatrix4 = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(2.5, 0.15, 0.5));
            model4 = translateMatrix4 * rotateYMatrix4 * scaleMatrix4;
            table.drawCubeWithTexture(lightingShaderWithTexture, model4);
        }
        //leg5
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(66.5, 1.6, 18.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.15, -3.0, 0.05));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);
        //leg6
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(66.5, 1.6, 18.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.15, -3.0, 0.05));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);
        //table4
        //base
        for (float i = 0.0f; i < 360.0f; i += 0.50f) {
            //Center

            translateMatrix4 = glm::translate(identityMatrix, glm::vec3(66.5, 1.5, 10.0));
            rotateYMatrix4 = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(2.5, 0.15, 0.5));
            model4 = translateMatrix4 * rotateYMatrix4 * scaleMatrix4;
            table.drawCubeWithTexture(lightingShaderWithTexture, model4);
        }
        //leg7
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(66.5, 1.6, 10.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.15, -3.0, 0.05));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);
        //leg8
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(66.5, 1.6, 10.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.15, -3.0, 0.05));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);
        //table5
       //base
        for (float i = 0.0f; i < 360.0f; i += 0.50f) {
            //Center

            translateMatrix4 = glm::translate(identityMatrix, glm::vec3(75.0, 1.5, 18.0));
            rotateYMatrix4 = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(2.5, 0.15, 0.5));
            model4 = translateMatrix4 * rotateYMatrix4 * scaleMatrix4;
            table.drawCubeWithTexture(lightingShaderWithTexture, model4);
        }
        //leg9
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(75.0, 1.6, 18.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.15, -3.0, 0.05));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);
        //leg10
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(75.0, 1.6, 18.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.15, -3.0, 0.05));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);
        //table6
       //base
        for (float i = 0.0f; i < 360.0f; i += 0.50f) {
            //Center

            translateMatrix4 = glm::translate(identityMatrix, glm::vec3(75.0, 1.5, 10.0));
            rotateYMatrix4 = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(2.5, 0.15, 0.5));
            model4 = translateMatrix4 * rotateYMatrix4 * scaleMatrix4;
            table.drawCubeWithTexture(lightingShaderWithTexture, model4);
        }
        //leg11
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(75.0, 1.6, 10.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.15, -3.0, 0.05));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);
        //leg12
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(75.0, 1.6, 10.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.15, -3.0, 0.05));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //Chair1

        glm::mat4 translateMatrix5, rotateXMatrix5, rotateYMatrix5, rotateZMatrix5, scaleMatrix5, model5;

        //upor
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(53.0f, -1.0f, 18.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.50f, 3.0f, -0.15f));
        model5 = translateMatrix5 * rotateZMatrix5 *  scaleMatrix5;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model5);


        //base
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(53.0f, 0.5f, 18.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.5f, .15f, 1.5f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        table.drawCubeWithTexture(lightingShaderWithTexture, model5);

        //chair7
        //upor
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(61.5f, -1.0f, 19.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.50f, 3.0f, -0.15f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model5);

        //base
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(61.5f, 0.5f, 19.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.5f, .15f, 1.5f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        table.drawCubeWithTexture(lightingShaderWithTexture, model5);


        //chair8
        //upor
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(61.5f, -1.0f, 11.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.50f, 3.0f, -0.15f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model5);

        //base
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(61.5f, 0.5f, 11.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.5f, .15f, 1.5f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        table.drawCubeWithTexture(lightingShaderWithTexture, model5);
        
        //chair2
        //upor
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(53.0f, -1.0f, 10.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.50f, 3.0f, -0.15f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model5);

        //base
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(53.0f, 0.5f, 10.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.5f, .15f, 1.5f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        table.drawCubeWithTexture(lightingShaderWithTexture, model5);

        //chair3
        //upor
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(62.0f, -1.0f, 18.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.50f, 3.0f, -0.15f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model5);

        //base
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(62.0f, 0.5f, 18.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.5f, .15f, 1.5f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        table.drawCubeWithTexture(lightingShaderWithTexture, model5);


        //chair9
        //upor
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(70.5f, -1.0f, 19.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.50f, 3.0f, -0.15f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model5);

        //base
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(70.5f, 0.5f, 19.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.5f, .15f, 1.5f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        table.drawCubeWithTexture(lightingShaderWithTexture, model5);


        //chair10
        //upor
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(70.5f, -1.0f, 11.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.50f, 3.0f, -0.15f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model5);

        //base
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(70.5f, 0.5f, 11.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.5f, .15f, 1.5f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        table.drawCubeWithTexture(lightingShaderWithTexture, model5);
        //chair4
        //upor
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(62.0f, -1.0f, 10.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.50f, 3.0f, -0.15f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model5);

        //base
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(62.0f, 0.5f, 10.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.5f, .15f, 1.5f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        table.drawCubeWithTexture(lightingShaderWithTexture, model5);

        //chair5
       //upor
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(71.0f, -1.0f, 18.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.50f, 3.0f, -0.15f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model5);

        //base
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(71.0f, 0.5f, 18.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.5f, .15f, 1.5f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        table.drawCubeWithTexture(lightingShaderWithTexture, model5);

        //chair11
    //upor
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(79.0f, -1.0f, 18.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.50f, 3.0f, -0.15f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model5);

        //base
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(79.0f, 0.5f, 18.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.5f, .15f, 1.5f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        table.drawCubeWithTexture(lightingShaderWithTexture, model5);

        //chair11
        //upor
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(79.0f, -1.0f, 11.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.50f, 3.0f, -0.15f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model5);

        //base
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(79.0f, 0.5f, 11.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.5f, .15f, 1.5f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        table.drawCubeWithTexture(lightingShaderWithTexture, model5);

        //chair6
        //upor
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(71.0f, -1.0f, 10.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.50f, 3.0f, -0.15f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model5);

        //base
        translateMatrix5 = glm::translate(identityMatrix, glm::vec3(71.0f, 0.5f, 10.0f));
        rotateZMatrix5 = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(1.5f, .15f, 1.5f));
        model5 = translateMatrix5 * rotateZMatrix5 * scaleMatrix5;
        table.drawCubeWithTexture(lightingShaderWithTexture, model5);

        /*--------------------------BOATSWING------------------------*/

        //ground

        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0f, -1.05f, -4.50f));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(15.0f, 0.0f, 12.5f));
        model3 = translateMatrix3 * scaleMatrix3;
        wood.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //floor
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(34.0f, -1.05f, -2.50f));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(9.0f, 0.3f, 8.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        drawCube(cubeVAO, lightingShader, model3, 1.0, 1.0f, 1.0f);

        //boat body starts
           //draw a Boat
        
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(38.5, -6.5, 1.50+ dz));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(5, 5, 2));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierBoatVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //draw a boat ends

        //boat
        
        glm::mat4 translateMatrix6, rotateXMatrix6, rotateYMatrix6, rotateZMatrix6, scaleMatrix6, model6;
       
        translateMatrix6 = glm::translate(identityMatrix, glm::vec3(35.05f , 1.2f, 0.25f+ dz));
        scaleMatrix6 = glm::scale(identityMatrix, glm::vec3(7.0f, 0.3f, 3.0f));
        model6 = translateMatrix6 * scaleMatrix6;
        boat.drawCubeWithTexture(lightingShaderWithTexture, model6);
        //leg1
        translateMatrix6 = glm::translate(identityMatrix, glm::vec3(38.5, 6.15, 1.0+ dz));
        rotateZMatrix6 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix6 = glm::scale(identityMatrix, glm::vec3(0.15, -5.5, 0.05));
        model6 = translateMatrix6 * rotateZMatrix6 * scaleMatrix6;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model6);
        //leg2
        translateMatrix6 = glm::translate(identityMatrix, glm::vec3(38.5 , 6.15, 1.0+ dz));
        rotateZMatrix6 = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix6 = glm::scale(identityMatrix, glm::vec3(0.15, -5.5, 0.05));
        model6 = translateMatrix6 * rotateZMatrix6 * scaleMatrix6;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model6);

        //leg3
        translateMatrix6 = glm::translate(identityMatrix, glm::vec3(38.5 , 6.15, 2.0+ dz));
        rotateZMatrix6 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix6 = glm::scale(identityMatrix, glm::vec3(0.15, -5.5, 0.05));
        model6 = translateMatrix6 * rotateZMatrix6 * scaleMatrix6;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model6);
        //leg4
        translateMatrix6 = glm::translate(identityMatrix, glm::vec3(38.5, 6.15, 2.0+ dz));
        rotateZMatrix6 = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix6 = glm::scale(identityMatrix, glm::vec3(0.15, -5.5, 0.05));
        model6 = translateMatrix6 * rotateZMatrix6 * scaleMatrix6;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model6);
        //boatbody ends
        
        //top
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(38.25f, 6.05f, -2.50f));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, 8.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        drawCube(cubeVAO, lightingShader, model3, 0.0, 0.0f, 0.0f);
        
        for (float i = 0.0f; i < 360.0f; i += 0.50f) {
            //Center

            translateMatrix4 = glm::translate(identityMatrix, glm::vec3(38.5f, 6.05f, 1.50f));
            rotateYMatrix4 = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.5, 0.65, 4.5));
            model4 = translateMatrix4 * rotateYMatrix4 * scaleMatrix4;
            table.drawCubeWithTexture(lightingShaderWithTexture, model4);
        }
        //leg1
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(38.5, 6.15, -2.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.25, -8.0, 0.5));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model4);
        //leg2
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(38.5, 6.15, -2.0));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.25, -8.0, 0.5));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model4);

        //leg3
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(38.5, 6.15, 4.5));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.25, -8.0, 0.5));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model4);
        //leg4
        translateMatrix4 = glm::translate(identityMatrix, glm::vec3(38.5, 6.15, 4.5));
        rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.25, -8.0, 0.5));
        model4 = translateMatrix4 * rotateZMatrix4 * scaleMatrix4;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model4);

        if (flagR2 == 1)
        {
            dz = dz + 0.4;
            if (dz >= 0.9)
            {
                flagR2 = 2;
            }

        }
        if (flagR2 == 2)
        {
            dz = dz - 0.4;
            if (dz <= -0.9)
            {
                flagR2 = 3;
            }
        }
        if (flagR2 == 3)
        {
            dz = dz + 0.4;
            if (dz >= 0)
            {
                flagR2 = 4;
            }

        }

        //fence(y-axis)
        //standleft
        // stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, -1.05, -2.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, -1.05, 0.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, -1.05, 3.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, -1.05, 5.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, -1.05, 8.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //fence(y-axis)
        //standright
       // stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(47.0, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(47.0, -1.05, -2.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(47.0, -1.05, 0.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(47.0, -1.05, 3.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(47.0, -1.05, 5.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(47.0, -1.05,8.0 ));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        

        //standmiddle
       // stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(34.5, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(37.0, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(39.5, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(42.0, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(44.5, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //fence(x-axis)
//standmiddle
//stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, 0.0, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(15.0f, 0.15f, 0.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, 1.5, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(15.0f, 0.15f, 0.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standleft
        //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, 0.0, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 12.5f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, 1.5, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 12.5f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standright
        //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(47.0, 0.0, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.15f, 0.0f, 12.50f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(47.0, 1.5, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.15f, 0.0f, 12.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        /*--------------------------SKYDROP------------------------*/

        //ground

        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(5.0f, -1.05f, -4.50f));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(15.0f, 0.0f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        wood.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //fence(y-axis)
        //standleft
        // stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(5.0, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(5.0, -1.05, -2.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(5.0, -1.05, 0.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(5.0, -1.05, 3.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(5.0, -1.05, 5.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(5.0, -1.05, 8.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand7
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(5.0, -1.05, 10.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standright
        // stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(20.0, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(20.0, -1.05, -2.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(20.0, -1.05, 0.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(20.0, -1.05, 3.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(20.0, -1.05, 5.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(20.0, -1.05, 8.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand7
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(20.0, -1.05, 10.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standmiddle
        // stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(7.5, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(10.0, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(12.5, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(15.0, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(17.5, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(20.0, -1.05, -4.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //fence(x-axis)
//standmiddle
//stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(5.0, 0.0, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(15.0f, 0.15f, 0.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(5.0, 1.5, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(15.0f, 0.15f, 0.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standleft
        //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(5.0, 0.0, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(5.0, 1.5, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standright
        //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(20.0, 0.0, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.15f, 0.0f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(20.0, 1.5, -4.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.15f, 0.0f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        glm::mat4 translateMatrix_b1, rotateXMatrix_b1, rotateYMatrix_b1, rotateZMatrix_b1, scaleMatrix_b1, model_b1;
        //skydrop starts
        //stand
        glm::mat4 translateMatrix7, rotateXMatrix7, rotateYMatrix7, rotateZMatrix7, scaleMatrix7, model7;
        //nicher part
        translateMatrix7 = glm::translate(identityMatrix, glm::vec3(11.0, -1.10, -2.50));
        scaleMatrix7 = glm::scale(identityMatrix, glm::vec3(3.5f, 18.0f, 0.5f));
        model7 = translateMatrix7 * scaleMatrix7;
        seat.drawCubeWithTexture(lightingShaderWithTexture, model7);
        //uporer part
        translateMatrix7 = glm::translate(identityMatrix, glm::vec3(11.0, 16.9, -2.50));
        scaleMatrix7 = glm::scale(identityMatrix, glm::vec3(3.5f, 2.0f, 0.5f));
        model7 = translateMatrix7 * scaleMatrix7;
        skydrop.drawCubeWithTexture(lightingShaderWithTexture, model7);

        //seat
        // 
        // holding base
        translateMatrix7 = glm::translate(identityMatrix, glm::vec3(11.0, 0.50+ dy1, -2.0));
        scaleMatrix7 = glm::scale(identityMatrix, glm::vec3(3.5f, 0.50f, 1.50f));
        model7 = translateMatrix7 * scaleMatrix7;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model7);

        // holding left
        translateMatrix7 = glm::translate(identityMatrix, glm::vec3(11.0, 0.50+ dy1, -2.0));
        scaleMatrix7 = glm::scale(identityMatrix, glm::vec3(0.5f, 3.5f, 0.25f));
        model7 = translateMatrix7 * scaleMatrix7;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model7);


        // holding right
        translateMatrix7 = glm::translate(identityMatrix, glm::vec3(14.0, 0.50+ dy1, -2.0));
        scaleMatrix7 = glm::scale(identityMatrix, glm::vec3(0.5f, 3.5f, 0.25f));
        model7 = translateMatrix7 * scaleMatrix7;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model7);

         // base
        translateMatrix7 = glm::translate(identityMatrix, glm::vec3(8.0, 1.0+ dy1, -1.75));
        scaleMatrix7 = glm::scale(identityMatrix, glm::vec3(10.0f, 0.50f, 1.60f));
        model7 = translateMatrix7 * scaleMatrix7;
        drawCube(cubeVAO, lightingShader, model7, 1.0, 1.0f, 0.5f);
        
        //uporer part
        translateMatrix7 = glm::translate(identityMatrix, glm::vec3(8.0f, 1.0f+ dy1, -1.75f));
        scaleMatrix7 = glm::scale(identityMatrix, glm::vec3(10.0f, 2.10f, .20f));
        //scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 2.10f, 5.0f));
        model7 = translateMatrix7 * scaleMatrix7;
        drawCube(cubeVAO, lightingShader, model7, 1.0, 1.0f, 0.5f);

        //handle left
        translateMatrix7 = glm::translate(identityMatrix, glm::vec3(8.0, 2.0+ dy1, -1.75));
        scaleMatrix7 = glm::scale(identityMatrix, glm::vec3(.50f, .50f, 1.50f));
        model7 = translateMatrix7 * scaleMatrix7;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model7);


        ////handle right
        translateMatrix7 = glm::translate(identityMatrix, glm::vec3(17.5, 2.0+ dy1, -1.75));
        scaleMatrix7 = glm::scale(identityMatrix, glm::vec3(.50f, .50f, 1.50f));
        model7 = translateMatrix7 * scaleMatrix7;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model7);

        //handle front
        translateMatrix7 = glm::translate(identityMatrix, glm::vec3(8.0, 2.0+ dy1, -0.25));
        scaleMatrix7 = glm::scale(identityMatrix, glm::vec3(10.0f, .50f, .50f));
        model7 = translateMatrix7 * scaleMatrix7;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model7);

        if (flagR3 == 1)
        {
            dy1 = dy1 + 0.5;
            if (dy1 >= 14)
            {
                flagR3 = 2;
            }

        }
        if (flagR3 == 2)
        {
            dy1 = dy1 - 0.5;
            if (dy1 <= -0.5)
            {
                flagR3 = 5;
            }
        }
        /*--------------------------Round ride------------------------*/
        
        //ground

        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(17.0f, -1.05f, 14.50f));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(15.0f, 0.0f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        wood.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //fence(x-axis)
//standmiddle
//stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(17.0, 0.0, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(15.0f, 0.15f, 0.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(17.0, 1.5, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(15.0f, 0.15f, 0.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standleft
       //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(17.0, 0.0, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(17.0, 1.5, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);



        //standright
       //stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, 0.0, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, 1.5, 14.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 15.0f));
        model3 = translateMatrix3 * scaleMatrix3;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //fence(y-axis)
        //standleft
        // stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, -1.05, 14.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, -1.05, 17.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, -1.05, 19.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, -1.05, 22.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, -1.05, 24.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, -1.05, 27.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand7
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, -1.05, 29.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);


        //standright
// stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(17.0, -1.05, 14.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(17.0, -1.05, 17.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(17.0, -1.05, 19.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(17.0, -1.05, 22.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(17.0, -1.05, 24.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(17.0, -1.05, 27.0));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand7
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(17.0, -1.05, 29.5));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //standmidle
        // stand1
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(17.0, -1.05, 14.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        // stand2
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(19.5, -1.05, 14.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand3
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(22.0, -1.05, 14.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand4
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(24.5, -1.05, 14.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand5
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(27.0, -1.05, 14.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand6
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(29.5, -1.05, 14.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);

        //stand7
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(32.0, -1.05, 14.50));
        scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model3 = translateMatrix3 * scaleMatrix3;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model3);
        //draw the cylinder stand

        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;


        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(25, -11.5, 21));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.5, 10.5, 0.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        // glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //draw a cylilnder ends
        

        //y-axis
         //draw the cylinder stand left
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(21, -6.5, 21));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.5, 7.5, 0.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends

         //draw the cylinder stand right
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(29, -6.5, 21));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.5, 7.5, 0.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends

        //draw the cylinder stand middle3
        
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(25, 6.75, 14.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(-270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.5, 7.0, 0.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        
        //draw the cylinder stand middle4
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(25, 6.75, 8.5));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(-270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.5, 7.0, 0.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends

        //draw the cylinder stand left
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(16.0, 6.75, 21.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.5, 5.0, 0.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends

        //draw the cylinder stand right
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(20.0, 6.75, 21.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.5, 5.0, 0.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends

        //draw the cylinder stand middle1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(25, -6.5, 26.5));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.5, 7.5, 0.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends

        //draw the cylinder stand middle2
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(25, -6.5, 15.5));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.5, 7.5, 0.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.15f, 0.55f, 0.05f));//rgb(39, 139, 14)
        lightingShader.setVec3("material.diffuse", glm::vec3(0.15f, 0.55f, 0.05f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends

        //draw a big circle
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(25, -3.5, 21));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(10, 3.5, 12.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.98f, 0.32f, 0.04f));//rgb(250, 82, 11)
        lightingShader.setVec3("material.diffuse", glm::vec3(0.98f, 0.32f, 0.04f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends

        //the small circle down
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(25, 5.25, 21));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 1.5, 2.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends

        //the small circle up
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(25, -2.7, 21));//17.0f, -1.05f, 14.50f
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 1.5, 2.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCircleVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a circle ends


        glm::mat4 translateMatrix8, rotateXMatrix8, rotateYMatrix8, rotateZMatrix8, scaleMatrix8, model8;
        // base1
        translateMatrix8 = glm::translate(identityMatrix, glm::vec3(23.75, 1.5, 19.25));
        rotateZMatrix8 = glm::rotate(identityMatrixCurve, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix8 = glm::scale(identityMatrix, glm::vec3(2.5f, 0.50f, 3.50f));
        model8 = translateMatrix8 * rotateZMatrix8 * scaleMatrix8;
        drawCube(cubeVAO, lightingShader, model8, 1.0, 1.0f, 0.0f);


        // base2
        translateMatrix8 = glm::translate(identityMatrix, glm::vec3(21.5, 1.5, 22.75));
        rotateXMatrix8 = glm::rotate(identityMatrix, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix8 = glm::scale(identityMatrix, glm::vec3(2.25f, 0.50f, 2.5f));
        model8 = translateMatrix8 * rotateXMatrix8 * scaleMatrix8;
        drawCube(cubeVAO, lightingShader, model8, 1.0, 1.0f, 0.0f);

        // base3
        translateMatrix8 = glm::translate(identityMatrix, glm::vec3(21.5, 1.5, 19.75));
        rotateXMatrix8 = glm::rotate(identityMatrix, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix8 = glm::scale(identityMatrix, glm::vec3(2.25f, 0.50f, 2.5f));
        model8 = translateMatrix8 * rotateXMatrix8 * scaleMatrix8;
        drawCube(cubeVAO, lightingShader, model8, 1.0, 1.0f, 0.0f);

        //uporer part1

        translateMatrix8 = glm::translate(identityMatrix, glm::vec3(21.75, 1.5, 19.25));
        rotateZMatrix8 = glm::rotate(identityMatrixCurve, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix8 = glm::scale(identityMatrix, glm::vec3(2.5f, 0.50f, 3.50f));
        model8 = translateMatrix8 * rotateZMatrix8 * scaleMatrix8;
        drawCube(cubeVAO, lightingShader, model8, 1.0, 1.0f, 0.0f);
        
        // base2
        translateMatrix8 = glm::translate(identityMatrix, glm::vec3(28.75, 1.5, 19.25));
        rotateZMatrix8 = glm::rotate(identityMatrixCurve, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix8 = glm::scale(identityMatrix, glm::vec3(2.5f, 0.50f, 3.50f));
        model8 = translateMatrix8 * rotateZMatrix8 * scaleMatrix8;
        drawCube(cubeVAO, lightingShader, model8, 1.0, 1.0f, 0.0f);

        // base3
        translateMatrix8 = glm::translate(identityMatrix, glm::vec3(26.25, 1.5, 22.75));
        rotateXMatrix8 = glm::rotate(identityMatrix, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix8 = glm::scale(identityMatrix, glm::vec3(2.25f, 0.50f, 2.5f));
        model8 = translateMatrix8 * rotateXMatrix8 * scaleMatrix8;
        drawCube(cubeVAO, lightingShader, model8, 1.0, 1.0f, 0.0f);

        // base4
        translateMatrix8 = glm::translate(identityMatrix, glm::vec3(26.25, 1.5, 19.75));
        rotateXMatrix8 = glm::rotate(identityMatrix, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix8 = glm::scale(identityMatrix, glm::vec3(2.25f, 0.50f, 2.5f));
        model8 = translateMatrix8 * rotateXMatrix8 * scaleMatrix8;
        drawCube(cubeVAO, lightingShader, model8, 1.0, 1.0f, 0.0f);

        //uporer part2

        translateMatrix8 = glm::translate(identityMatrix, glm::vec3(28.75, 1.5, 19.25));
        rotateZMatrix8 = glm::rotate(identityMatrixCurve, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix8 = glm::scale(identityMatrix, glm::vec3(2.5f, 0.50f, 3.50f));
        model8 = translateMatrix8 * rotateZMatrix8 * scaleMatrix8;
        drawCube(cubeVAO, lightingShader, model8, 1.0, 1.0f, 0.0f);

        // base3
        translateMatrix8 = glm::translate(identityMatrix, glm::vec3(23.25, 1.5, 23.8));
        rotateZMatrix8 = glm::rotate(identityMatrix, glm::radians(360.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix8 = glm::scale(identityMatrix, glm::vec3(3.5f, 0.50f, 2.50f));
        model8 = translateMatrix8 * rotateZMatrix8 * scaleMatrix8;
        drawCube(cubeVAO, lightingShader, model8, 1.0, 1.0f, 0.0f);

        //base4

        translateMatrix8 = glm::translate(identityMatrix, glm::vec3(23.75, 1.5, 23.8));
        rotateZMatrix8 = glm::rotate(identityMatrixCurve, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix8 = glm::scale(identityMatrix, glm::vec3(2.5f, 0.50f, 2.25f));
        model8 = translateMatrix8 * rotateZMatrix8 * scaleMatrix8;
        drawCube(cubeVAO, lightingShader, model8, 1.0, 1.0f, 0.0f);

        //base5

        translateMatrix8 = glm::translate(identityMatrix, glm::vec3(26.75, 1.5, 23.8));
        rotateZMatrix8 = glm::rotate(identityMatrixCurve, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix8 = glm::scale(identityMatrix, glm::vec3(2.5f, 0.50f, 2.25f));
        model8 = translateMatrix8 * rotateZMatrix8 * scaleMatrix8;
        drawCube(cubeVAO, lightingShader, model8, 1.0, 1.0f, 0.0f);
        //uporer part3

        translateMatrix8 = glm::translate(identityMatrix, glm::vec3(23.25, 1.5, 26.3));
        rotateXMatrix8 = glm::rotate(identityMatrix, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix8 = glm::scale(identityMatrix, glm::vec3(3.5f, 0.50f, 2.50f));
        model8 = translateMatrix8 * rotateXMatrix8 * scaleMatrix8;
        drawCube(cubeVAO, lightingShader, model8, 1.0, 1.0f, 0.0f);

        // base4
        translateMatrix8 = glm::translate(identityMatrix, glm::vec3(23.25, 1.5, 15.7));
        rotateZMatrix8 = glm::rotate(identityMatrix, glm::radians(360.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix8 = glm::scale(identityMatrix, glm::vec3(3.5f, 0.50f, 2.50f));
        model8 = translateMatrix8 * rotateZMatrix8 * scaleMatrix8;
        drawCube(cubeVAO, lightingShader, model8, 1.0, 1.0f, 0.0f);

        //base5

        translateMatrix8 = glm::translate(identityMatrix, glm::vec3(23.75, 1.5, 15.95));
        rotateZMatrix8 = glm::rotate(identityMatrixCurve, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix8 = glm::scale(identityMatrix, glm::vec3(2.5f, 0.50f, 2.25f));
        model8 = translateMatrix8 * rotateZMatrix8 * scaleMatrix8;
        drawCube(cubeVAO, lightingShader, model8, 1.0, 1.0f, 0.0f);

        //base6

        translateMatrix8 = glm::translate(identityMatrix, glm::vec3(26.75, 1.5, 15.95));
        rotateZMatrix8 = glm::rotate(identityMatrixCurve, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix8 = glm::scale(identityMatrix, glm::vec3(2.5f, 0.50f, 2.25f));
        model8 = translateMatrix8 * rotateZMatrix8 * scaleMatrix8;
        drawCube(cubeVAO, lightingShader, model8, 1.0, 1.0f, 0.0f);

        //uporer part4

        translateMatrix8 = glm::translate(identityMatrix, glm::vec3(23.25, 1.5, 16.2));
        rotateXMatrix8 = glm::rotate(identityMatrix, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix8 = glm::scale(identityMatrix, glm::vec3(3.5f, 0.50f, 2.50f));
        model8 = translateMatrix8 * rotateXMatrix8 * scaleMatrix8;
        drawCube(cubeVAO, lightingShader, model8, 1.0, 1.0f, 0.0f);

        // also draw the lamp object(s) && draw a cylinder with sadi
        // start of ourshader for complex object
//camera / view transformation

float degree = 0;
glm::mat4 view = camera.GetViewMatrix();
float r = glm::length(camera.Position - glm::vec3(view[3]));
ourShader.setMat4("view", view);
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        //Cylinder Circle code start
        glm::mat4 modelCircle = glm::mat4(1.0f);
 

        // we now draw as many light bulbs as we have point lights.
        

        ourShader.use();
        for (unsigned int i = 0; i < 2; i++)
        {
            glm :: mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(2.0f, 2.0f, 0.9f)); // Make it a smaller cube
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
        
        glBindVertexArray(lightCubeVAO);
        
        


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);
        lightingShaderWithTexture.setMat4("projection", projection);
        lightingShaderWithTexture.setMat4("view", view);
        //2nd part of cube draw
        lightingShaderWithTexture.use();
        // point light 1
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        // point light 3
        pointlight3.setUpPointLight(lightingShaderWithTexture);
       
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}




// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

   if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }
   // if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.001;
   // if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.001;
   // if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
   // if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
   // if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
   if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
   if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
   if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
   // if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
   // if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

   
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
    {
        flagR7 = 1;
    }

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
        flagR6 = 1;
    }

    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        flagR5 = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        flagR4 = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        flagR3 = 1;
    }

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    {
        flagR2 = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        pointlight1.turnOn();
        pointlight3.turnOn();
        pointlight4.turnOn();
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        pointlight1.turnOff();
        pointlight3.turnOff();
        pointlight4.turnOff();

    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        pointlight1.turnDiffuseOn();
        pointlight3.turnDiffuseOn();
       // pointlight4.turnDiffuseOn();
        spotLight.turnDiffuseOn();
        dirLight.turnDiffuseOn();

    }
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {
        
        pointlight1.turnOff();
        pointlight3.turnOff();
        pointlight3.turnOff();
        dirLight.turnOff();
        spotLight.turnOff();

    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        dirLight.turnOn();

    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        dirLight.turnOff();
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        spotLight.turnOn();

    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        spotLight.turnOff();
    }
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
    {
        pointlight1.turnAmbientOn();
        pointlight3.turnAmbientOn();
        spotLight.turnAmbientOn();
        dirLight.turnAmbientOn();
    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        pointlight1.turnSpecularOn();
        pointlight3.turnSpecularOn();
        spotLight.turnSpecularOn();
        dirLight.turnSpecularOn();
    }


 
    


}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
long long nCr(int n, int r)
{
    if (r > n / 2)
        r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for (i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//polynomial interpretation for N points
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L)
{
    double y = 0;
    double x = 0;
    t = t > 1.0 ? 1.0 : t;
    for (int i = 0; i < L + 1; i++)
    {
        long long ncr = nCr(L, i);
        double oneMinusTpow = pow(1 - t, double(L - i));
        double tPow = pow(t, double(i));
        double coef = oneMinusTpow * tPow * ncr;
        x += coef * ctrlpoints[i * 3];
        y += coef * ctrlpoints[(i * 3) + 1];

    }
    xy[0] = float(x);
    xy[1] = float(y);
}

unsigned int hollowBezier(GLfloat ctrlpoints[], int L)
{
    int i, j;
    float x, y, z, r;                //current coordinates
    float theta;
    float nx, ny, nz, lengthInv;    // vertex normal


    const float dtheta = 2 * pi / ntheta;        //angular step size

    float t = 0;
    float dt = 1.0 / nt;
    float xy[2];

    for (i = 0; i <= nt; ++i)              //step through y
    {
        BezierCurve(t, xy, ctrlpoints, L);
        r = xy[0];
        y = xy[1];
        theta = 0;
        t += dt;
        lengthInv = 1.0 / r;

        for (j = 0; j <= ntheta; ++j)
        {
            double cosa = cos(theta);
            double sina = sin(theta);
            z = r * cosa;
            x = r * sina;

            coordinates.push_back(x);
            coordinates.push_back(y);
            coordinates.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            // center point of the circle (0,y,0)
            nx = (x - 0) * lengthInv;
            ny = (y - y) * lengthInv;
            nz = (z - 0) * lengthInv;

            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            theta += dtheta;
        }
    }

    // generate index list of triangles
    // k1--k1+1
    // |  / |
    // | /  |
    // k2--k2+1

    int k1, k2;
    for (int i = 0; i < nt; ++i)
    {
        k1 = i * (ntheta + 1);     // beginning of current stack
        k2 = k1 + ntheta + 1;      // beginning of next stack

        for (int j = 0; j < ntheta; ++j, ++k1, ++k2)
        {
            // k1 => k2 => k1+1
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);

            // k1+1 => k2 => k2+1
            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k2 + 1);
        }
    }

    size_t count = coordinates.size();
    for (int i = 0; i < count; i += 3)
    {
        vertices.push_back(coordinates[i]);
        vertices.push_back(coordinates[i + 1]);
        vertices.push_back(coordinates[i + 2]);

        vertices.push_back(normals[i]);
        vertices.push_back(normals[i + 1]);
        vertices.push_back(normals[i + 2]);
    }

    unsigned int bezierVAO;
    glGenVertexArrays(1, &bezierVAO);
    glBindVertexArray(bezierVAO);

    // create VBO to copy vertex data to VBO
    unsigned int bezierVBO;
    glGenBuffers(1, &bezierVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bezierVBO);           // for vertex data
    glBufferData(GL_ARRAY_BUFFER,                   // target
        (unsigned int)vertices.size() * sizeof(float), // data size, # of bytes
        vertices.data(),   // ptr to vertex data
        GL_STATIC_DRAW);                   // usage

    // create EBO to copy index data
    unsigned int bezierEBO;
    glGenBuffers(1, &bezierEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bezierEBO);   // for index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
        (unsigned int)indices.size() * sizeof(unsigned int),             // data size, # of bytes
        indices.data(),               // ptr to index data
        GL_STATIC_DRAW);                   // usage

    // activate attrib arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // set attrib arrays with stride and offset
    int stride = 24;     // should be 24 bytes
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3));

    // unbind VAO, VBO and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return bezierVAO;
}
