#include "Common.h"
#include "Graphics.h"
#include "Vertex.h"

Vertex verts[] = { { -0.5f, 0.5f, 0.5f, //xyz
1.0f, 0.0f, 0.0f, 1.0f }, //rgba
{ -0.5f, -0.5f, 0.5f, //xyz
0.0f, 1.0f, 0.0f, 1.0f }, //rgba
{ 0.5f, -0.5f, 0.5f, //xyz
0.0f, 0.0f, 1.0f, 1.0f },
{ 0.5f, 0.5f, 0.5f,
1.0f, 0.0f, 1.0f, 1.0f },

//back
{ -0.5f, 0.5f, -0.5f, //xyz
1.0f, 0.0f, 1.0f, 1.0f }, //rgba
{ -0.5f, -0.5f, -0.5f, //xyz
1.0f, 1.0f, 0.0f, 1.0f }, //rgba
{ 0.5f, -0.5f, -0.5f, //xyz
0.0f, 1.0f, 1.0f, 1.0f },
{ 0.5f, 0.5f, -0.5f,
1.0f, 0.0f, 1.0f, 1.0f }
};

GLuint indices[] = {
	//front
	0,1,2,
	0,3,2,

	//left
	4,5,1,
	4,1,0,

	//right
	3,7,2,
	7,6,2,

	//bottom
	1,5,2,
	6,2,5,

	//top
	4,0,7,
	0,7,3,

	//back
	4,5,6,
	4,7,6
};

GLuint VBO;
GLuint EBO;

void update()
{
}

void render()
{
    //old imediate mode!
    //Set the clear colour(background)
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    //clear the colour and depth buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);

}

void initScene()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void cleanUp()
{
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
}

int main(int argc, char * arg[])
{
    //Controls the game loop
    bool run=true;
    bool pause=false;
    // init everyting - SDL, if it is nonzero we have a problem
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR SDL_Init " <<SDL_GetError()<< std::endl;

        return -1;
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
    SDL_Quit();

    return 0;
}
