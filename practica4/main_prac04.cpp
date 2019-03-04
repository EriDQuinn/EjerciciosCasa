
/*---------------------------------------------------------*/
/* ----------------   Práctica 4 Casa--------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*------------- Computación gráfica e interacción humano computadora  ---------------*/
/*-------------Diaz Acosta Erika      Grupo 4 -------------- */	
/*---------------------Version visual 2017------------------------*/
/*---------Instrucciones-------------------------------------------*/
/*--------Use las teclas para mover el modelo----------------------*/
/*--------S acercar   W  alejar------------------------------------*/
/*--------flechas para rotar-----arriba abajo y a los lados--------*/


/*------------------PLUTO CROSSY ROAD---------------------------------------*/
#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

void myData(void);
void display(void);
void getResolution(void);

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movQ = 0.0f,
movZ = -5.0f;
float  angx = 0.0f,
angy = 0.0f;
void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{
	GLfloat vertices[] = {
		//Position				//Color
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V0 - Frontal
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V1
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V5
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V4

		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	//V3
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V7
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V6

		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V4 - Izq
		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	//V7
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	//V3
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V0

		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V5 - Der
		0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V1
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V2
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V6

		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V4 - Sup
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V5
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V6
		-0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V7

		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V0 - Inf
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	//V3
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V1
	};

	unsigned int indices[] =	//I am not using index for this session
	{
		0
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void display(void)
{
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");

	projectionShader.use();

	// create transformations and Projection
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection
	glm::mat4 modelTemp = glm::mat4(1.0f);

	//Use "projection" in order to change how we see the information
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	//projection = glm::ortho(-5.0f, 5.0f, -3.0f, 3.0f, 0.1f, 10.0f);

	//Use "view" in order to affect all models
	view = glm::translate(view, glm::vec3(movX, movY, movZ));
	view = glm::rotate(view, glm::radians(angx), glm::vec3(0, 1, 0));
	view = glm::rotate(view, glm::radians(angy), glm::vec3(1, 0, 0));


	// pass them to the shaders
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);


	glBindVertexArray(VAO);
	//projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	//glDrawArrays(GL_QUADS, 0, 24); //A lonely cube :(


	model = glm::translate(model, glm::vec3(0, 0, 0));
	model = glm::scale(model, glm::vec3(2,.5, 2));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24); //cabeza

	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -0.375, 0));
	model = glm::scale(model, glm::vec3(4, .25, 4));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24); //cabfrente
	
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -1.855, -.25));
	model = glm::scale(model, glm::vec3(2, 2.75, 3.5));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24); //cabatras
	
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(1.5, -1.86, -.25));
	model = glm::scale(model, glm::vec3(1, 2.75, 3.5 ));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//cab lado
	
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-1.5, -1.86, -.25));
	model = glm::scale(model, glm::vec3(1, 2.75, 3.5));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//cab lado
								  
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -5.75, 0));
	model = glm::scale(model, glm::vec3(4, 5, 4));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//nuca
		
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -.75, 1.75));
	model = glm::scale(model, glm::vec3(.5, .5, .5));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//enmedio ojos

	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0,-1.875 , 1.75));
	model = glm::scale(model, glm::vec3(.5, 1.75, .5));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//enmedio con ojos

	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -5, 4.25));
	model = glm::scale(model, glm::vec3(4, 2, 4.5));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//oscico
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(1.5, -5, 6.75));
	model = glm::scale(model, glm::vec3(1, 2, .5));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//oscico2
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-1.5, -5, 6.75));
	model = glm::scale(model, glm::vec3(1, 2, .5));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//oscico2
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -5, 6.75));
	model = glm::scale(model, glm::vec3(2, 2, .5));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//nariz-oscico 3 correccion
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -4, 7.5));
	model = glm::scale(model, glm::vec3(2, 2, 1));//escalas
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//nariz
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -3.5, 6.5));
	model = glm::scale(model, glm::vec3(2, 1, 1));//escalas
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//nariz

	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -6.25, 3.5));
	model = glm::scale(model, glm::vec3(3, .5, 3));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.8f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//lengua
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -7, 5.25));
	model = glm::scale(model, glm::vec3(3, 2, .5));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.8f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//lengua
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -7, 3.5));
	model = glm::scale(model, glm::vec3(4, 1, 3));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//oscico abajo

	
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-1.105, -1.625, 1.75));
	model = glm::scale(model, glm::vec3(1.75, 2.25, .5));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//parpado
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(1.105, -1.625, 1.75));
	model = glm::scale(model, glm::vec3(1.75, 2.25, .5));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//parpado
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(1, -3, 1.75));
	model = glm::scale(model, glm::vec3(.75, .5, .5));//escalas
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//ojo
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-1, -3, 1.75));
	model = glm::scale(model, glm::vec3(.75, .5, .5));//escalas
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//ojo

	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-1.67, -3, 1.75));
	model = glm::scale(model, glm::vec3(.625, .5, .5));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//lado ojo
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(1.67, -3, 1.75));
	model = glm::scale(model, glm::vec3(.625, .5, .5));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//lado ojo
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -3, 1.75));
	model = glm::scale(model, glm::vec3(1.25, .5, .5));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//lado ojo

	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(2.5, -1, 0));
	model = glm::scale(model, glm::vec3(1, 1, 1));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//oreja
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-2.5, -1, 0));
	model = glm::scale(model, glm::vec3(1, 1, 1));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//oreja
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(2.5, 1, 0));
	model = glm::scale(model, glm::vec3(1, 3, 1));//escalas
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//oreja
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-2.5, 1, 0));
	model = glm::scale(model, glm::vec3(1, 3, 1));//escalas
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//oreja
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(2.5, 3, .5));
	model = glm::scale(model, glm::vec3(1, 1, 2));//escalas
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//oreja
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-2.5, 3, .5));
	model = glm::scale(model, glm::vec3(1, 1, 2));//escalas
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//oreja

	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -8.75, 0));
	model = glm::scale(model, glm::vec3(6, 1, 5));//escalas
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.9f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//collar

	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -12.25, -1));
	model = glm::scale(model, glm::vec3(8, 6, 6));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//cuerpo1
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -12.25, -8));
	model = glm::scale(model, glm::vec3(6, 6, 8));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//cuerpo2

	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(3.5, -12.25, -11));
	model = glm::scale(model, glm::vec3(1, 6, 2));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//muslo1
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-3.5, -12.25, -11));
	model = glm::scale(model, glm::vec3(1, 6, 2));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//muslo2

	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(3, -18.25, -11));
	model = glm::scale(model, glm::vec3(2, 6, 2));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//piernita1
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-3, -18.25, -11));
	model = glm::scale(model, glm::vec3(2, 6, 2));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//piernita2
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-3, -18.25, 1));
	model = glm::scale(model, glm::vec3(2, 6, 2));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//piernita3
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(3, -18.25, 1));
	model = glm::scale(model, glm::vec3(2, 6, 2));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//piernita4

	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(3, -22.25, -10));
	model = glm::scale(model, glm::vec3(2, 2, 4));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//pata
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-3, -22.25, -10));
	model = glm::scale(model, glm::vec3(2, 2, 4));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//pata
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-3, -22.25, 2));
	model = glm::scale(model, glm::vec3(2, 2, 4));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//pata
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(3, -22.25, 2));
	model = glm::scale(model, glm::vec3(2, 2, 4));//escalas
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//pata

	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -7.25, -12.5));
	model = glm::scale(model, glm::vec3(1, 6, 1));//escalas
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//cola
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -3.75, -13));
	model = glm::scale(model, glm::vec3(1, 1, 2));//escalas
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);//

	glBindVertexArray(0);

}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 4", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	glEnable(GL_DEPTH_TEST);

	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		my_input(window);

		// render
		// Backgound color
		glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi función de dibujo
		display();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.08f;

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		angx -= 0.6f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		angx += 0.6f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		angy -= 0.6f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		angy += 0.6f;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}