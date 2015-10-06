#include "Common.h"
#include "Graphics.h"
#include "Vertex.h"

Vertex verts[] = { { 0.0f, 1.0f, 0.0f, //xyz
1.0f, 0.0f, 0.0f, 1.0f }, //rgba
{ -1.0f, -1.0f, 0.0f, //xyz
0.0f, 1.0f, 0.0f, 1.0f }, //rgba
{ 1.0f, -1.0f, 0.0f, //xyz
0.0f, 0.0f, 1.0f, 1.0f }//rgba
};

GLuint VBO;

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

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (void**)(3 * sizeof(float)));
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -6.0f);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(verts) / sizeof(Vertex));

    //Swith to ModelView
    glMatrixMode( GL_MODELVIEW );
    //Reset using the Indentity Matrix
    glLoadIdentity( );

	gluLookAt(0.0, 0.0, 6.0, 0.0, 0.0, -1.0f, 0.0, 1.0, 0.0);
    //Do translation, push the next bit of drawing 'back' 5 units
    //on z-zaxis
    //Everyting after this will be drawn at -5.0f on z-axis
    //until reset by glLoadIdentity!
    glTranslatef( 0.0f, 0.0f, -5.0f );

    //Begin drawing triangles
    glBegin( GL_TRIANGLES );
      glColor3f(1.0f, 0.0f, 0.0f); //Colour of the vertices
      glVertex3f(  0.0f,  1.0f, 0.0f ); // Top
      glVertex3f( -1.0f, -1.0f, 0.0f ); // Bottom Left
      glVertex3f(  1.0f, -1.0f, 0.0f ); // Bottom Right
    glEnd( );

}

void initScene()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
}

void cleanUp()
{
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
