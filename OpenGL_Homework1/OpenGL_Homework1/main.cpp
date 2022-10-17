#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include <vector>
#include "GameObject.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

float vertices[] = {
	// positions          
	   0.08f, -0.75f, 0.0f, // 0
	   0.08f, -1.0f, 0.0f, // 1
	  -0.08f, -1.0f, 0.0f, // 2  
	  -0.08f, -1.0f, 0.0f, // 2  
	  -0.08f, -0.75f, 0.0f,  // 3
	   0.08f, -0.75f, 0.0f, // 0
};

float player2[] = {
	   -0.84f, -0.75f, 0.0f, // 0
	   -0.84f, -1.0f, 0.0f, // 1
	   -1.0f, -1.0f, 0.0f, // 2  
		-1.0f, -1.0f, 0.0f, // 2 
	   -1.0f, -0.75f, 0.0f  // 3
		- 0.84f, -0.75f, 0.0f // 0
};

glm::vec3 triangle_pos[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(0.5f,	 2.0f, 0.0f), 
	glm::vec3(-0.5f, 3.0f, 0.0f),
	glm::vec3(-0.3f, 2.5f, 0.0f),
};

unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
};

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

bool CheckCollision(float player_x, float player_x_size, float player_y, float player_y_size, float coin_x,
	float coin_x_size, float coin_y, float coin_y_size) // AABB - AABB collision
{
	// collision x-axis?
	bool collisionX = player_x + player_x_size >= coin_x &&
		coin_x + coin_x_size >= player_x;
	// collision y-axis?
	bool collisionY = player_y + player_y_size >= coin_y &&
		coin_y + coin_y_size >= player_y;
	// collision only if on both axes
	return collisionX && collisionY;
}

vector<int> keys;
bool key_input = false;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//cout << key << endl;
	if (key == GLFW_KEY_LEFT) {
		switch (action) {
		case GLFW_PRESS:			
			//cout << "Left is pressed!" << endl;
			keys.push_back(263);
			key_input = true;
			break;
		case GLFW_REPEAT:
			//cout << "Left is being held down!" << endl;
			keys.push_back(263);
			key_input = true;
			break;
		case GLFW_RELEASE:
			//cout << "Left is released!" << endl;
			break;
		default:
			break;
		}
	}
	else if (key == GLFW_KEY_RIGHT) {
		switch (action) {
		case GLFW_PRESS:
			//cout << "Right is pressed!" << endl;
			keys.push_back(262);
			key_input = true;
			break;
		case GLFW_REPEAT:
			//cout << "Right is being held down!" << endl;
			keys.push_back(262);
			key_input = true;
			break;
		case GLFW_RELEASE:
			//cout << "Right is released!" << endl;
			break;
		default:
			break;
		}
	}
	else {
		switch (action) {
		case GLFW_PRESS:
			keys.push_back(key);
			key_input = true;
			break;
		case GLFW_REPEAT:
			break;
		case GLFW_RELEASE:
			break;
		default:
			break;
		}
	}
}

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1200, 720, "Coin Catcher", NULL, NULL);

	if (window == NULL) {
		printf("Open window failed");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		printf("Init GLEW failed");
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 1200, 720);

	Shader* testShader = new Shader("vertexSource.txt", "fragmentSource.txt");

	float player_positionx = vertices[9];
	float player_positionx_size = abs(vertices[9] - vertices[3]);
	float player_positiony = vertices[10];
	float player_positiony_size = abs(vertices[10] - vertices[4]);
	float points[] = { player_positionx, player_positionx_size, player_positiony, player_positiony_size };
	GameObject* player = new GameObject(points);


	unsigned int VAO;
	unsigned int VBO;
	//unsigned int EBO[2];
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(2, EBO);
	glBindVertexArray(VAO);	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);	
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glfwSetKeyCallback(window, keyCallback);
	bool coin_catch = 0;
	/*glm::mat4 trans;*/
	//trans = glm::translate(trans, glm::vec3(0.1f, 0.0f, 0));
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
			
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glBindVertexArray(VAO);
		for (int i = 0; i < 4; i++) {
			
			glm::mat4 trans;
			if (key_input && i == 0) {
				cout << "Received ";
				if (keys.front() == 263) {
					cout << "a Left key\n";
					triangle_pos[i].x -= 0.05f;
					keys.erase(keys.begin());
				}
				else if (keys.front() == 262) {
					cout << "a Right key\n";
					triangle_pos[i].x += 0.05f;
					keys.erase(keys.begin());
				}
				else {
					cout << "Nothing\n";
					keys.erase(keys.begin());
				}
				key_input = false;
			}
			if(i == 1 || i == 2 || i == 3) {
				triangle_pos[i].y -= 0.0001f;
			}
			if (coin_catch == 1 && i == 1) {
				triangle_pos[1] = glm::vec3(0.5f, 2.0f, 0.0f);
				coin_catch = 0;
				continue;
			}
			else if (coin_catch == 2 && i == 2) {
				triangle_pos[2] = glm::vec3(-0.5f, 3.0f, 0.0f);
				coin_catch = 0;
				continue;
			}
			else if (coin_catch == 3 && i == 3) {
				triangle_pos[3] = glm::vec3(-0.3f, 2.5f, 0.0f);
				coin_catch = 0;
				continue;
			}
			trans = glm::translate(trans, triangle_pos[i]);
			testShader->use();
			glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		float player_x = vertices[12] + triangle_pos[0].x;
		float player_x_size = abs(vertices[12] - vertices[0]);
		float player_y = vertices[13] + triangle_pos[0].y;
		float player_y_size = abs(vertices[13] - vertices[10]);

		for (int i = 1; i < 4;i++) {
			float coin_x = vertices[12] + triangle_pos[i].x;
			float coin_x_size = abs(vertices[12] - vertices[0]);
			float coin_y = vertices[13] + triangle_pos[i].y;
			float coin_y_size = abs(vertices[13] - vertices[10]);
			if (CheckCollision(player_x, player_x_size, player_y, player_y_size, coin_x, coin_x_size, coin_y, coin_y_size)) {
				cout << "+1 score!" << endl;
				coin_catch = i;
			}
		}
		
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));	
		//glBindVertexArray(VAO[1]);
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
		/*glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/

		
		glfwSwapBuffers(window);
		glfwPollEvents();
		
	}

	return 0;
}