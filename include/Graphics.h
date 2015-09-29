#ifndef _GRAPHICS_H
#define _GRAPHICS_H

void initOpenGL()
{
	GLenum err = glewInit();

	if (GLEW_OK != err)
	{
		std::cout << "error:" << glewGetErrorString(err) << std::endl;
	}
}

void setViewport( int width, int height );

#endif
