#include "Common.h"
#include "Graphics.h"
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "FileSystem.h"
#include "Mesh.h"
#include "FBXLoader.h"

GLuint VBO;
GLuint EBO;
GLuint VAO;
GLuint shaderProgram = 0;
GLuint textureMap;
GLuint fontTexture;

mat4 viewMatrix;
mat4 projMatrix;
mat4 worldMatrix;
//mat4 rotMatrix;
mat4 MVPMatrix;

vec4 ambientMaterialColour(0.3f, 0.3f, 0.3f, 1.0f);
vec4 ambientLightColour(1.0f, 1.0f, 1.0f, 1.0f);

vec4 diffuseMaterialColour(0.5f, 0.3f, 0.3, 1.0f);
vec4 diffuseLightColour(1.0f, 1.0f, 1.0f, 1.0f);

vec3 lightDirection(0.0f, 0.0f, 1.0f);

MeshData currentMesh;

void update()
{
	projMatrix = perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
	viewMatrix = lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	worldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
	//rotMatrix = rotate(20.0f, 0.0f, 1.0f, 0);
	MVPMatrix = projMatrix * viewMatrix * worldMatrix;
}

void render()
{
    //old imediate mode!
    //Set the clear colour(background)
    glClearColor( 1.0f, 0.0f, 0.0f, 0.0f );
    //clear the colour and depth buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);

	GLint MVPLocation = glGetUniformLocation(shaderProgram, "MVP");
	GLint texture0Location = glGetUniformLocation(shaderProgram, "texture0");

	GLuint tempDMC = glGetUniformLocation(shaderProgram, "diffuseMaterialColour");
	glUniform4fv(tempDMC, 1, value_ptr(diffuseMaterialColour));

	GLuint tempDLC = glGetUniformLocation(shaderProgram, "diffuseLightColour");
	glUniform4fv(tempDLC, 1, value_ptr(diffuseLightColour));

	GLuint tempModel = glGetUniformLocation(shaderProgram, "Model");
	glUniform4fv(tempModel, 1, value_ptr(worldMatrix));

	GLuint tempAMC = glGetUniformLocation(shaderProgram, "ambientMaterialColour");
	glUniform4fv(tempAMC, 1, value_ptr(ambientMaterialColour));

	GLuint tempALC = glGetUniformLocation(shaderProgram, "ambientLightColour");
	glUniform4fv(tempALC, 1, value_ptr(ambientLightColour));

	GLuint tempLD = glGetUniformLocation(shaderProgram, "lightDirection");
	glUniform3fv(tempLD, 1, value_ptr(lightDirection));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fontTexture);

	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVPMatrix));
	glUniform1i(texture0Location, 0);

	glDrawElements(GL_TRIANGLES, currentMesh.getNumIndices(),
		GL_UNSIGNED_INT, 0);
}

void initScene()
{
	/*load texture & bind
	string texturePath = ASSET_PATH + TEXTURE_PATH + "/texture.png";
	textureMap = loadTextureFromFile(texturePath);

	glBindTexture(GL_TEXTURE_2D, textureMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);

	string fontPath = ASSET_PATH + FONT_PATH + "/OratorStd.otf";
	fontTexture = loadTextureFromFont(fontPath, 18, "Hello World");

	glBindTexture(GL_TEXTURE_2D, fontTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	*/
	
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		printf("%d - %s\n", __LINE__, gluErrorString(err));
	string modelPath = ASSET_PATH + MODELS_PATH + "/utah-teapot.fbx";
	loadFBXFromFile(modelPath, &currentMesh);
	printf("Verts:%d Inds:%d\n", currentMesh.vertices.size(), currentMesh.indices.size());
	err = glGetError();
	if (err != GL_NO_ERROR)
		printf("%d - %s\n", __LINE__, gluErrorString(err));

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, currentMesh.getNumVerts()*sizeof(vec3),
		&currentMesh.vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	err = glGetError();
	if (err != GL_NO_ERROR)
		printf("%d - %s\n", __LINE__, gluErrorString(err));

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		currentMesh.getNumIndices()*sizeof(int),
		&currentMesh.indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);

	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3)));

	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec4) + sizeof(vec3)));

	//glEnableVertexAttribArray(3);
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec4) + sizeof(vec3) + sizeof(vec2)));

	err = glGetError();
	if (err != GL_NO_ERROR)
		printf("%d - %s\n", __LINE__, gluErrorString(err));

	GLuint vertexShaderProgram = 0;
	string vsPath = ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
	checkForCompilerErrors(vertexShaderProgram);

	GLuint fragmentShaderProgram = 0;
	string fspath = ASSET_PATH + SHADER_PATH + "/simpleFS.glsl";
	fragmentShaderProgram = loadShaderFromFile(fspath, FRAGMENT_SHADER);
	checkForCompilerErrors(fragmentShaderProgram);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderProgram);
	glAttachShader(shaderProgram, fragmentShaderProgram);

	glBindAttribLocation(shaderProgram, 0, "vertexPosition");
	//glBindAttribLocation(shaderProgram, 1, "vertexColor");
	//glBindAttribLocation(shaderProgram, 2, "vertexTexCoords");

	glLinkProgram(shaderProgram);
	checkForLinkErrors(shaderProgram);

	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
	err = glGetError();
	if (err != GL_NO_ERROR)
		printf("%d - %s\n", __LINE__, gluErrorString(err));
}

void cleanUp()
{
	glDeleteTextures(1, &textureMap);
	glDeleteTextures(1, &fontTexture);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glDeleteProgram(shaderProgram);
}

int main(int argc, char * arg[])
{
	ChangeWorkingDirectory();

	//Controls the game loop
	bool run = true;
	bool pause = false;
	// init everyting - SDL, if it is nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init " << SDL_GetError() << std::endl;

		return -1;
	}

	int imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int returnInitFlags = IMG_Init(imageInitFlags);
	if (((returnInitFlags)& (imageInitFlags)) != imageInitFlags){
		cout << "ERROR SDL_Image Init" << IMG_GetError() << endl;
	}

	if (TTF_Init() == -1)    {
		std::cout << "ERROR    TTF_Init: " << TTF_GetError();
	}


	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //Create a window
    SDL_Window * window = SDL_CreateWindow(
                                           "SDL",             // window title
                                           SDL_WINDOWPOS_CENTERED,     // x position, centered
                                           SDL_WINDOWPOS_CENTERED,     // y position, centered
                                           640,                        // width, in pixels
                                           480,                        // height, in pixels
                                           SDL_WINDOW_OPENGL           // flags
                                           );
    // Create an OpenGL context associated with the window.
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	glewExperimental = true;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "GLEW INIT ERROR" << std::endl;
		std::cout << glewGetErrorString(err) << std::endl;
		return -1;
	}

    //Initialisation
    //Call our InitOpenGL Function
    initOpenGL();
    //Set our viewport
    setViewport(640,480);

	initScene();

    //Value to hold the event generated by SDL
    SDL_Event event;
    //Game Loop
    while(run)
    {
        //While we still have events in the queue
        while (SDL_PollEvent(&event)) {
            //Get event type
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                //set our boolean which controls the loop to false
                run = false;
            }
            if (event.type==SDL_WINDOWEVENT)
            {
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_MINIMIZED:
                            pause=true;
                        break;
                    default:
                        break;
                }

            }

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_RIGHT:
					//viewMatrix +=
					return 1;
				}
			}
        }

        //update
        update();
        //Then Draw
        render();

        //Call swap so that our GL back buffer is displayed
        SDL_GL_SwapWindow(window);

    }

    // clean up, reverse order!!!
	cleanUp();
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
    SDL_Quit();

    return 0;
}
