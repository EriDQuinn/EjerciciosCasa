
/*---------------------------------------------------------*/
/* ----------------   Pr�ctica 7 --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*-------------- Alumno: ERIKA DIAZ ACOSTA                    ---------------*/
/*-----------------Version de Visual 2017-------------------
----------------------Grupo 4------------------------------
--------------Instrucciones:--------------------------------------------------------------
---Mover con el raton y usar la rueda de scroll para acercar y alejar, ----------
------teclas extra:--------------------------------------------------------------------
 ---------------W: Acercar	-----------------------------------------------------------
 ---------------S: Alejar -----------------------------------------------------------
 ---------------A: Izquierda-----------------------------------------------------------
 ---------------D: Derecha -----------------------------------------------------------
 -------Para rotar usar las flechas
 -------Para la fuente de iluminacion:
 ------------L: luz en el Lado superior izquierdo
 ------------L + Shift: luz del lado inferior derecho
*/
#include "esfera.h"
#include "camera.h"

Esfera my_sphere(1.0);

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, lightVAO;

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
double	lastX = 0.0f,
lastY = 0.0f;
bool firstMouse = true;

//Timing
double	deltaTime = 0.0f,
lastFrame = 0.0f;

float posix = -10.0f, posiy = 10.0;
//Lighting
glm::vec3 lightPos(posix, posiy, 0.0f);
glm::vec3 lightPos2(10.0f, -10.0f, 0.0f);

void myData(void);
void display(void);
void getResolution(void);
void animate(void);
void luces(void);

//For Keyboard
float	
movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rotY = 0.0f,
rotX = 0.0f;

float	sol = 0.0f, electron2 = 0.0f, electron = 0.0f;


void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}

void myData()
{
	GLfloat vertices[] = {
		//Position				//Normals
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,//
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//To configure Second Objecto to represet Light
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

void animate(void)
{
	sol += 0.5f;
	electron += 0.9f;
	electron2 -= 0.9f;

}


void circulos2(float x, float y, float z) {
	//float x1 = 0.0f, y1 = 0.0f, z = 0.0f;
	glPointSize(3.0);
	glColor3f(0,0,0);
	for (double i = 0; i <= 360;) {
		
		glBegin(GL_POINTS);
		if (z == 0) {
			x = 6 * cos(i);
			y = 6 * sin(i);
			//z = 6 * sin(i);
			glVertex3d(x, y, z);
			i = i + .5;
			x = 6 * cos(i);
			y = 6 * sin(i);
			//z = 6 * sin(i);
			glVertex3d(x, y, z);
			glVertex3d(0, 0, 0);
		}
		else {
			if (x == 0) {
				y = 6 * cos(i);
				z = 6 * sin(i);
				glVertex3d(x, y, z);
				i = i + .5;
				y = 6 * cos(i);
				z = 6 * sin(i);
				glVertex3d(x, y, z);
				glVertex3d(0, 0, 0);
			}
			else {
				if (y == 0) {
					x = 6 * cos(i);
					z = 6 * sin(i);
					glVertex3d(x, y, z);
					i = i + .5;
					x = 6 * cos(i);
					z = 6 * sin(i);
					glVertex3d(x, y, z);
					glVertex3d(0, 0, 0);
				}
				else {
					x = 6 * cos(i);
					y = 3.5 * sin(i);
					z = (6) * sin(i);
					glVertex3d(x, y, z);
					i = i + .5;
					x = 6 * cos(i);
					y = 3.5 * sin(i);
					z = (6) *-sin(i);
					glVertex3d(x, y, z);
					glVertex3d(0, 0, 0);
					//---------------------


				}
			}

		}

		glEnd();
		i = i + 0.5;

	}
	glEnd();
	//glfwSwapBuffers();
}

void luces(void) {
	glm::vec3 lightPos2(10.0f, -10.0f, 0.0f);
	
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	//Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");
	Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	//Shader projectionShader("shaders/shader_light_Gouraud.vs", "shaders/shader_light_Gouraud.fs");
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");

	//To Use Lighting
	projectionShader.use();
	projectionShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("lightPos", lightPos2);
	
	
	glBindVertexArray(VAO);

	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
}

void display(void)
{
	
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	//Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");
	Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	//Shader projectionShader("shaders/shader_light_Gouraud.vs", "shaders/shader_light_Gouraud.fs");
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");

	//To Use Lighting
	projectionShader.use();
	projectionShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("lightPos", glm::vec3(posix, posiy, 0.0f));
	
	//temporal
	glm::mat4 temp01 = glm::mat4(1.0f); //Temp
	// create transformations and Projection
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" to inlcude Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	view = glm::translate(view, glm::vec3(movX, movY, movZ));
	view = glm::rotate(view, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
	// pass them to the shaders}
	projectionShader.setVec3("viewPos", camera.Position);
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);


	glBindVertexArray(VAO);
	//Colocar c�digo aqu�
	
//	model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.50f, 0.50f, 0.50f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.858, 0.694, 0.886);
	projectionShader.setVec3("diffuseColor", 0.858, 0.694, 0.886);
	projectionShader.setVec3("specularColor", 0.870, 0.584, 0.917);
	my_sphere.render();	//Sphere SOL
	circulos2(1, 1, 0);
	circulos2(0, 1, 1);
	circulos2(1, 0, 1);
	circulos2(1, 1, 1);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(.8, 0, 0));
	//model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.50f, 0.50f, 0.50f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.580, 0.270, 0.631);
	projectionShader.setVec3("diffuseColor", 0.768, 0.368, 0.831);
	projectionShader.setVec3("specularColor", 0.870, 0.584, 0.917);
	my_sphere.render();//nucleo

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-.8, 0, 0));
	//model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.50f, 0.50f, 0.50f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.580, 0.270, 0.631);
	projectionShader.setVec3("diffuseColor", 0.768, 0.368, 0.831);
	projectionShader.setVec3("specularColor", 0.870, 0.584, 0.917);
	my_sphere.render();	//nucleo

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-.5, .8, 0));
	//model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.50f, 0.50f, 0.50f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.580, 0.270, 0.631);
	projectionShader.setVec3("diffuseColor", 0.768, 0.368, 0.831);
	projectionShader.setVec3("specularColor", 0.870, 0.584, 0.917);
	my_sphere.render();	//nucleo

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(.5, -.8, 0));
	//model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.50f, 0.50f, 0.50f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.580, 0.270, 0.631);
	projectionShader.setVec3("diffuseColor", 0.768, 0.368, 0.831);
	projectionShader.setVec3("specularColor", 0.870, 0.584, 0.917);
	my_sphere.render();	//nucleo

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-.5, -.8, 0));
	//model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.50f, 0.50f, 0.50f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.580, 0.270, 0.631);
	projectionShader.setVec3("diffuseColor", 0.768, 0.368, 0.831);
	projectionShader.setVec3("specularColor", 0.870, 0.584, 0.917);
	my_sphere.render();	//nucleo

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(.5, .8, 0));
	//model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.50f, 0.50f, 0.50f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.580, 0.270, 0.631);
	projectionShader.setVec3("diffuseColor", 0.768, 0.368, 0.831);
	projectionShader.setVec3("specularColor", 0.870, 0.584, 0.917);
	my_sphere.render();	//nucleo

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-.5, 0, .8));
	//model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.50f, 0.50f, 0.50f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.580, 0.270, 0.631);
	projectionShader.setVec3("diffuseColor", 0.768, 0.368, 0.831);
	projectionShader.setVec3("specularColor", 0.870, 0.584, 0.917);
	my_sphere.render();	//nucleo
	
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(.5, 0, .8));
	//model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.50f, 0.50f, 0.50f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.580, 0.270, 0.631);
	projectionShader.setVec3("diffuseColor", 0.768, 0.368, 0.831);
	projectionShader.setVec3("specularColor", 0.870, 0.584, 0.917);
	my_sphere.render();//nucleo
	
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-.5, 0, -.8));
	//model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.50f, 0.50f, 0.50f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.580, 0.270, 0.631);
	projectionShader.setVec3("diffuseColor", 0.768, 0.368, 0.831);
	projectionShader.setVec3("specularColor", 0.870, 0.584, 0.917);
	my_sphere.render();//nucleo
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(.5, 0, -.8));
	//model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.50f, 0.50f, 0.50f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.580, 0.270, 0.631);
	projectionShader.setVec3("diffuseColor", 0.768, 0.368, 0.831);
	projectionShader.setVec3("specularColor", 0.870, 0.584, 0.917);
	my_sphere.render();//nucleo
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, .8, .8));
	//model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.50f, 0.50f, 0.50f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.580, 0.270, 0.631);
	projectionShader.setVec3("diffuseColor", 0.768, 0.368, 0.831);
	projectionShader.setVec3("specularColor", 0.870, 0.584, 0.917);
	my_sphere.render();	//nucleo
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, .8, -.8));
	//model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.50f, 0.50f, 0.50f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.580, 0.270, 0.631);
	projectionShader.setVec3("diffuseColor", 0.768, 0.368, 0.831);
	projectionShader.setVec3("specularColor", 0.870, 0.584, 0.917);
	my_sphere.render();	//nucleo
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, -.8, .8));
	//model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.50f, 0.50f, 0.50f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.580, 0.270, 0.631);
	projectionShader.setVec3("diffuseColor", 0.768, 0.368, 0.831);
	projectionShader.setVec3("specularColor", 0.870, 0.584, 0.917);
	my_sphere.render();	//nucleo
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, -.8, -.8));
	//model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.50f, 0.50f, 0.50f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.580, 0.270, 0.631);
	projectionShader.setVec3("diffuseColor", 0.768, 0.368, 0.831);
	projectionShader.setVec3("specularColor", 0.870, 0.584, 0.917);
	my_sphere.render();	//nucleo
	model = glm::mat4(1.0f);

	//electron
	model = glm::rotate(model, glm::radians(electron2), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(3, 0, 0));
	//model = glm::rotate(model, glm::radians(electron), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.30f, 0.30f, .30f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.4, 0.921, 0.850);
	projectionShader.setVec3("diffuseColor", 0.098, 0.784, 0.686);
	projectionShader.setVec3("specularColor", 0.552, 0.925, 0.796);
	my_sphere.render();

	model = glm::mat4(1.0f);
	//electron
	model = glm::rotate(model, glm::radians(electron2), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-3, 0, 0));
	//model = glm::rotate(model, glm::radians(electron), glm::vec3(0.1f, 0.1f, 0.1f));
	model = glm::scale(model, glm::vec3(0.30f, 0.30f, .30f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.4, 0.921, 0.850);
	projectionShader.setVec3("diffuseColor", 0.098, 0.784, 0.686);
	projectionShader.setVec3("specularColor", 0.552, 0.925, 0.796);
	my_sphere.render();
	model = glm::mat4(1.0f);

	//electron
	model = glm::rotate(model, glm::radians(electron), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0, 3, 0));
	//model = glm::rotate(model, glm::radians(electron), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.30f, 0.30f, .30f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.4, 0.921, 0.850);
	projectionShader.setVec3("diffuseColor", 0.098, 0.784, 0.686);
	projectionShader.setVec3("specularColor", 0.552, 0.925, 0.796);
	my_sphere.render();
	model = glm::mat4(1.0f);

	//electron
	model = glm::rotate(model, glm::radians(electron), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0, -3, 0));
	//model = glm::rotate(model, glm::radians(electron), glm::vec3(0.1f, 0.1f, 0.1f));
	model = glm::scale(model, glm::vec3(0.30f, 0.30f, .30f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.4, 0.921, 0.850);
	projectionShader.setVec3("diffuseColor", 0.098, 0.784, 0.686);
	projectionShader.setVec3("specularColor", 0.552, 0.925, 0.796);
	my_sphere.render();
	model = glm::mat4(1.0f);

	//electron
	model = glm::rotate(model, glm::radians(electron), glm::vec3(0.0f, 01.00f, 1.0f));
	model = glm::translate(model, glm::vec3(-3, 0, 0));
	//model = glm::rotate(model, glm::radians(electron), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.30f, 0.30f, .30f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.4, 0.921, 0.850);
	projectionShader.setVec3("diffuseColor", 0.098, 0.784, 0.686);
	projectionShader.setVec3("specularColor", 0.552, 0.925, 0.796);
	my_sphere.render();
	model = glm::mat4(1.0f);

	//electron
	model = glm::rotate(model, glm::radians(electron2), glm::vec3(0.0f, 01.00f, -1.0f));
	model = glm::translate(model, glm::vec3(3, 0, 0));
	//model = glm::rotate(model, glm::radians(electron), glm::vec3(0.1f, 0.1f, 0.1f));
	model = glm::scale(model, glm::vec3(0.30f, 0.30f, .30f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.4, 0.921, 0.850);
	projectionShader.setVec3("diffuseColor", 0.098, 0.784, 0.686);
	projectionShader.setVec3("specularColor", 0.552, 0.925, 0.796);
	my_sphere.render();
	model = glm::mat4(1.0f);

	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light


	//glBindVertexArray(0);

}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 7", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	my_sphere.init();
	glEnable(GL_DEPTH_TEST);

	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// input
		// -----
		my_input(window);
		animate();
		
		// render
		// Backgound color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi funci�n de dibujo
		display();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		rotX += 0.18f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		rotX -= 0.18f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotY -= 0.6f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotY += 0.6f;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		//luces();
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			posix = 5,
			posiy = -5;
		}
		else {
				posix = -5;
				posiy = 5;
		}
			

	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}