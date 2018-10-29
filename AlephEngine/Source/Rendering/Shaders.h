#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace AlephEngine
{
	namespace Shaders
	{
		
		static class StdUnlit
		{
		public:
			static const char* vertexText;
			static const char* fragmentText;

			static GLuint mvp_location;
			static GLuint vpos_location;
			static GLuint vcol_location;

			inline static int GetVertexSize() { return sizeof( float ) * 6; } // x, y, z | r, g, b

			static void SetShaderInputs( GLuint program );
			static GLuint AttachVertexArray( const int& count, const GLfloat* vertexArray );
			static void RebindVertexArray( const GLuint vertexBuffer );

			// TODO: Find a more elegant solution
			static void RebindTexture( const GLuint textureBuffer, GLenum wrapMode ) {}
		};

		static class UnlitTexture
		{
		public:
			static const char* vertexText;
			static const char* fragmentText;

			static GLuint mvp_location;
			static GLuint vpos_location;
			static GLuint texcoord_location;

			inline static int GetVertexSize() { return sizeof( float ) * 5; } // x, y, z | u, v
			static void SetShaderInputs( GLuint program );
			static GLuint AttachVertexArray( const int& count, const GLfloat* vertexArray );
			static void RebindVertexArray( const GLuint vertexBuffer );
			static GLuint AttachTexture( GLFWimage* texture, GLenum wrapMode );
			static void RebindTexture( const GLuint textureBuffer, GLenum wrapMode );
		};

		// To gennerate programs
		template<class T>
		GLuint GetGLProgram();
	}
	
}

// To gennerate programs
template<class T>
GLuint AlephEngine::Shaders::GetGLProgram()
{
	// Create vertex Shader
	GLuint vertex_shader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertex_shader, 1, &(T::vertexText), NULL );
	glCompileShader( vertex_shader );

	// Create fragment shader
	GLuint fragment_shader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragment_shader, 1, &T::fragmentText, NULL );
	glCompileShader( fragment_shader );

	// Create program
	GLuint program = glCreateProgram();
	glAttachShader( program, vertex_shader );
	glAttachShader( program, fragment_shader );
	glLinkProgram( program );

	// Set up the uniforms
	T::SetShaderInputs( program );

	return program;
}