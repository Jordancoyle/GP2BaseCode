#include "Graphics.h"
#include "Common.h"

//Function to initialise OpenGL
void initOpenGL()
{
    //Smooth shading
    glShadeModel( GL_SMOOTH );

    //clear the background to black
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    //Clear the depth buffer
    glClearDepth( 1.0f );

    //Enable depth testing
    glEnable( GL_DEPTH_TEST );

    //The depth test to go
    glDepthFunc( GL_LEQUAL );

    //Turn on best perspective correction
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	GLenum err = glewInit();

	if (GLEW_OK != err)
	{
		std::cout << "error:" << glewGetErrorString(err) << std::endl;
	}

}

//Function to set/reset viewport
void setViewport( int width, int height )
{
    //Setup viewport
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );
}
