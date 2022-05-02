#include <iostream>
#include <cmath>
// GLEW
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// Other Libs
#include "stb_image.h"
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//Load Models
#include "SOIL2/SOIL2.h"
// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

//Animacion
float puertaH1Rot = 0.0f;
bool puertaH1Anim = false;
bool puertaH1Cerrada = true;
float laptop1H1Rot = 0.0f;
bool laptop1H1Anim = false;
bool laptop1H1Cerrada = false;
float ventanaBH1Tra = 0.0f;
bool ventanaBH1Anim = false;
bool ventanaBH1Cerrada = true;
float pajaroXTra = 0.0f;
float pajaroZTra = 0.0f;
float pajaroRot = 0.0f;
float alasRot = 0.0f;
bool alasAba = false;
bool pajaroAnim = false;
bool recorrido1Pajaro = true;
bool recorrido2Pajaro = false;
bool recorrido3Pajaro = false;
bool recorrido4Pajaro = false;
bool recorrido5Pajaro = false;

int main()
{
	// Init GLFW
	glfwInit();

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");

	// Load models
	// Fachada
	Model barandillasMadFachada((char*)"Models/Fachada/Barandillas_Madera_Fachada.obj");
	Model barandillasMetFachada((char*)"Models/Fachada/Barandillas_Metal_Fachada.obj");
	Model baseFachada((char*)"Models/Fachada/Base_Fachada.obj");
	Model chimeneasFachada((char*)"Models/Fachada/Chimeneas_Fachada.obj");
	Model columnasFachada((char*)"Models/Fachada/Columnas_Fachada.obj");
	Model detallesFachada((char*)"Models/Fachada/Detalles_Fachada.obj");
	Model escalerasFachada((char*)"Models/Fachada/Escaleras_Fachada.obj");
	Model marcosFachada((char*)"Models/Fachada/Marcos_Fachada.obj");
	Model murosFachada((char*)"Models/Fachada/Muros_Fachada.obj");
	Model puertaAFachada((char*)"Models/Fachada/PuertaA_Fachada.obj");
	Model puertaB1Fachada((char*)"Models/Fachada/PuertaB1_Fachada.obj");
	Model puertaB2Fachada((char*)"Models/Fachada/PuertaB2_Fachada.obj");
	Model puertaSFachada((char*)"Models/Fachada/PuertaS_Fachada.obj");
	Model techoFachada((char*)"Models/Fachada/Techo_Fachada.obj");
	Model vidriosFachada((char*)"Models/Fachada/Vidrios_Fachada.obj");

	// Habitacion_1
	Model marcosH1((char*)"Models/Habitacion_1/Marcos_H1.obj");
	Model muroAtrH1((char*)"Models/Habitacion_1/Muro_Atr_H1.obj");
	Model muroDerH1((char*)"Models/Habitacion_1/Muro_Der_H1.obj");
	Model muroFreH1((char*)"Models/Habitacion_1/Muro_Fre_H1.obj");
	Model muroIzqH1((char*)"Models/Habitacion_1/Muro_Izq_H1.obj");
	Model pisoH1((char*)"Models/Habitacion_1/Piso_H1.obj");
	Model puertaH1((char*)"Models/Habitacion_1/Puerta_H1.obj");
	Model roperoH1((char*)"Models/Habitacion_1/Ropero_H1.obj");
	Model techoH1((char*)"Models/Habitacion_1/Techo_H1.obj");
	Model ventana1AH1((char*)"Models/Habitacion_1/VentanaA_H1.obj");
	Model ventana1BH1((char*)"Models/Habitacion_1/VentanaB_H1.obj");
	Model vidrioVentana1AH1((char*)"Models/Habitacion_1/Vidrio_VentanaA_H1.obj");
	Model vidrioVentana1BH1((char*)"Models/Habitacion_1/Vidrio_VentanaB_H1.obj");
	Model ventana2AH1((char*)"Models/Habitacion_1/VentanaA_H1.obj");
	Model ventana2BH1((char*)"Models/Habitacion_1/VentanaB_H1.obj");
	Model vidrioVentana2AH1((char*)"Models/Habitacion_1/Vidrio_VentanaA_H1.obj");
	Model vidrioVentana2BH1((char*)"Models/Habitacion_1/Vidrio_VentanaB_H1.obj");

	//Objetos Habitacion 1
	Model camaH1((char*)"Models/Objetos_H1/Cama/Cama_H1.obj");
	Model laptop1H1((char*)"Models/Objetos_H1/Laptop/Laptop1_H1.obj");
	Model laptop2H1((char*)"Models/Objetos_H1/Laptop/Laptop2_H1.obj");
	Model estanteH1((char*)"Models/Objetos_H1/Estante/Estante_H1.obj");
	Model escritorioH1((char*)"Models/Objetos_H1/Escritorio/Escritorio_H1.obj");
	Model libros1H1((char*)"Models/Objetos_H1/Libros/Libros1_H1.obj");
	Model libros2H1((char*)"Models/Objetos_H1/Libros/Libros2_H1.obj");
	Model sillaH1((char*)"Models/Objetos_H1/Silla/Silla_H1.obj");
	Model sofaH1((char*)"Models/Objetos_H1/Sofa/Sofa_H1.obj");
	Model alaDerPajaro((char*)"Models/Objetos_H1/Pajaro/Ala_Derecha_Pajaro.obj");
	Model alaIzqPajaro((char*)"Models/Objetos_H1/Pajaro/Ala_Izquierda_Pajaro.obj");
	Model cuerpoPajaro((char*)"Models/Objetos_H1/Pajaro/Cuerpo_Pajaro.obj");

	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// OpenGL options
		glEnable(GL_DEPTH_TEST);

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 1.0f, 1.0f, 1.0f);

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		view = camera.GetViewMatrix();

		//Carga de modelo Fachada
		glm::mat4 model(1);
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		barandillasMadFachada.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		barandillasMetFachada.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		baseFachada.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		chimeneasFachada.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		columnasFachada.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		detallesFachada.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		escalerasFachada.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		marcosFachada.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		murosFachada.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		puertaAFachada.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		puertaB1Fachada.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		puertaB2Fachada.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		puertaSFachada.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		techoFachada.Draw(lightingShader);

		//Carga de modelo Habitación_1 
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		marcosH1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		muroAtrH1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		muroDerH1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		muroFreH1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		muroIzqH1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		pisoH1.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(12.31f, 4.26f, -5.66f));
		model = glm::rotate(model, glm::radians(puertaH1Rot), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		puertaH1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		roperoH1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		techoH1.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(12.209f, 5.525f, -1.548f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		ventana1AH1.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(12.209f, 5.525f+ventanaBH1Tra, -1.548f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		ventana1BH1.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(13.255f, 5.525f, -1.548f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		ventana2AH1.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(13.255f, 5.525f+ventanaBH1Tra, -1.548f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		ventana2BH1.Draw(lightingShader);

		//Carga de modelos de objetos de la Habitacion_1
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		camaH1.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(12.008f, 4.827f, -1.868f));
		model = glm::rotate(model, glm::radians(47.256f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(laptop1H1Rot), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		laptop1H1.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(12.008f, 4.827f, -1.868f));
		model = glm::rotate(model, glm::radians(47.256f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		laptop2H1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		estanteH1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		escritorioH1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		libros1H1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		libros2H1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		sillaH1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		sofaH1.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(7.0f+pajaroXTra, 5.0f, 4.0f+pajaroZTra));
		model = glm::rotate(model, glm::radians(pajaroRot), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		cuerpoPajaro.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(7.0f + pajaroXTra, 5.0f, 4.0f + pajaroZTra));
		model = glm::rotate(model, glm::radians(pajaroRot), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(alasRot), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		alaDerPajaro.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(7.0f + pajaroXTra, 5.0f, 4.0f + pajaroZTra));
		model = glm::rotate(model, glm::radians(pajaroRot), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-alasRot), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		alaIzqPajaro.Draw(lightingShader);

		//Codigo para objetos semitrasnparentes
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Carga de modelo de Habitacion_1
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(12.209f, 5.525f, -1.548f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlfa"), 1.0f, 1.0f, 1.0f, 0.5f);
		vidrioVentana1AH1.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(12.209f, 5.525f+ventanaBH1Tra, -1.548f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlfa"), 1.0f, 1.0f, 1.0f, 0.5f);
		vidrioVentana1BH1.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(13.255f, 5.525f, -1.548f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlfa"), 1.0f, 1.0f, 1.0f, 0.5f);
		vidrioVentana2AH1.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(13.255f, 5.525f+ventanaBH1Tra, -1.548f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlfa"), 1.0f, 1.0f, 1.0f, 0.5f);
		vidrioVentana2BH1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlfa"), 1.0f, 1.0f, 1.0f, 0.5f);
		vidriosFachada.Draw(lightingShader);

		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlfa"), 1.0f, 1.0f, 1.0f, 1.0f);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}

	//Animacion Puerta H1
	if (puertaH1Anim && puertaH1Cerrada)
	{
		if(puertaH1Rot>-90.0f)
		{
			 puertaH1Rot -= 0.5f;
		}
		else
		{
			puertaH1Cerrada = false;
		}
	}
	else if(puertaH1Anim && !puertaH1Cerrada)
	{
		if (puertaH1Rot < 0.0f)
		{
			puertaH1Rot += 0.5f;
		}
		else
		{
			puertaH1Cerrada = true;
		}
	}

	//Animacion Laptop1_H1
	if (laptop1H1Anim && laptop1H1Cerrada)
	{
		if (laptop1H1Rot > -90.0f)
		{
			laptop1H1Rot -= 0.5f;
		}
		else
		{
			laptop1H1Cerrada = false;
		}
	}
	else if (laptop1H1Anim && !laptop1H1Cerrada)
	{
		if (laptop1H1Rot < 0.0f)
		{
			laptop1H1Rot += 0.5f;
		}
		else
		{
			laptop1H1Cerrada = true;
		}
	}

	//Animacion Ventanas_H1
	if (ventanaBH1Anim && ventanaBH1Cerrada)
	{
		if (5.525f+ventanaBH1Tra < 6.096f)
		{
			ventanaBH1Tra += 0.005f;
		}
		else
		{
			ventanaBH1Cerrada = false;
		}
	}
	else if (ventanaBH1Anim && !ventanaBH1Cerrada)
	{
		if (5.525f+ventanaBH1Tra > 5.525f)
		{
			ventanaBH1Tra -= 0.005f;
		}
		else
		{
			ventanaBH1Cerrada = true;
		}
	}

	//Animacion pajaro
	if (pajaroAnim)
	{
		if (alasAba)
		{
			if (alasRot < 45.0f)
			{
				alasRot += 0.5;
			}
			else
			{
				alasAba = false;
			}
		}
		if (!alasAba)
		{
			if (alasRot > -45.0f)
			{
				alasRot -= 0.5;
			}
			else
			{
				alasAba = true;
			}
		}

		if (recorrido1Pajaro)
		{
			pajaroZTra += 0.02f;

			if (pajaroZTra + 4.0f > 12.0f)
			{
				recorrido1Pajaro = false;
				recorrido2Pajaro = true;
			}
		}
		if (recorrido2Pajaro)
		{
			pajaroRot = 135.0f;
			pajaroXTra += 0.02f;
			pajaroZTra -= 0.02f;

			if (pajaroXTra + 7.0f > 12.0f && pajaroZTra + 4.0f < 4.0f)
			{
				recorrido2Pajaro = false;
				recorrido3Pajaro = true;

			}
		}
		if (recorrido3Pajaro)
		{
			pajaroRot = 0.0f;
			pajaroZTra += 0.02f;

			if (pajaroZTra + 4.0f > 12.0f)
			{
				recorrido3Pajaro = false;
				recorrido4Pajaro = true;
			}
		}

		if (recorrido4Pajaro)
		{
			pajaroRot = -135.0f;
			pajaroXTra -= 0.02f;
			pajaroZTra -= 0.02f;

			if (pajaroXTra + 7.0f < 7.0f && pajaroZTra + 4.0f < 4.0f)
			{
				recorrido4Pajaro = false;
				recorrido5Pajaro = true;
			}
		}
		if (recorrido5Pajaro)
		{
			pajaroRot = 0.0f;
			pajaroZTra += 0.02f;

			if (pajaroZTra + 4.0f > 4.0f)
			{
				recorrido5Pajaro = false;
				recorrido1Pajaro = true;
			}
		}
	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_1])
	{
		puertaH1Anim = !puertaH1Anim;
	}

	if (keys[GLFW_KEY_2])
	{
		laptop1H1Anim = !laptop1H1Anim;
	}

	if (keys[GLFW_KEY_3])
	{
		ventanaBH1Anim = !ventanaBH1Anim;
	}

	if (keys[GLFW_KEY_4])
	{
		pajaroAnim = !pajaroAnim;
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}