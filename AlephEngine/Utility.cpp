#include "Utility.h"
using namespace std;
using namespace AlephEngine;

/// <summary>
/// Load a png image into a format that GLFW can read.
/// </summary>
/// <param name="filename">The filename/path to load.</param>
/// <returns>The imported GlFW image.</returns>
GLFWimage* Utility::LoadGLFWImage( const string& filename )
{
	GLFWimage* outImage = new GLFWimage;
	unsigned width;
	unsigned height;

	// Use the c function to load without a vector
	unsigned error = lodepng_decode32_file( &(outImage->pixels), &width, &height, filename.c_str() );

	if( error )
	{
		cout << "Error decoding image " << error << ": " << lodepng_error_text( error ) << endl;
	}

	// Convert to signed ints for GLFW
	outImage->width = width;
	outImage->height = height;

	return outImage;
}