#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace AlephEngine
{
	namespace Shaders
	{
		GLuint mvp_location, vpos_location, vcol_location;
		static class StdUnlit
		{
		public:
			static const char* vertexText;
			static const char* fragmentText;

			static void SetShaderInputs( GLuint program )
			{
				mvp_location = glGetUniformLocation( program, "MVP" );
				vpos_location = glGetAttribLocation( program, "vPos" );
				vcol_location = glGetAttribLocation( program, "vCol" );
			}
		};

		// To gennerate programs
		template<class T> 
		GLuint GetGLProgram()
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

		const char* StdUnlit::vertexText =
			"#version 400\n"
			"uniform mat4 MVP;\n"
			"attribute vec3 vCol;\n"
			"attribute vec2 vPos;\n"
			"varying vec3 color;\n"
			"void main()\n"
			"{\n"
			"    gl_PointSize = 100.0;"
			"    gl_Position = MVP * vec4(vPos, 0.f, 1.0);\n"
			"    color = vCol;\n"
			"}\n";

		const char* StdUnlit::fragmentText =
			"#version 400\n"
			"varying vec3 color;\n"
			"void main()\n"
			"{\n"
			"    gl_FragColor = vec4(color, 1.0);\n"
			"}\n";
	}
	
}