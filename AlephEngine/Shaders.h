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

			static void SetShaderInputs( GLuint program )
			{
				mvp_location  = glGetUniformLocation( program, "MVP" );
				vpos_location = glGetAttribLocation( program, "vPos" );
				vcol_location = glGetAttribLocation( program, "vCol" );
			}

			static GLuint AttachVertexArray( const int& count, const GLfloat* vertexArray )
			{
				//Bind vertex data into buffer
				GLuint vertexBuffer;
				glGenBuffers( 1, &vertexBuffer );
				glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
				glBufferData( GL_ARRAY_BUFFER, GetVertexSize() * count, vertexArray, GL_DYNAMIC_DRAW );

				// Set up arrays
				RebindVertexArray( vertexBuffer );

				return vertexBuffer;
			}

			static void RebindVertexArray( const GLuint vertexBuffer )
			{
				glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
				glEnableVertexAttribArray( vpos_location );
				glVertexAttribPointer( vpos_location, 3, GL_FLOAT, GL_FALSE, GetVertexSize(), (void*) 0 );

				glEnableVertexAttribArray( vcol_location );
				glVertexAttribPointer( vcol_location, 3, GL_FLOAT, GL_FALSE, GetVertexSize(), (void*) ( sizeof( float ) * 3 ) );
			}

			// TODO: Find a more elegant solution
			static void RebindTexture( const GLuint textureBuffer, GLenum wrapMode ) {}
		};

		const char* StdUnlit::vertexText =
			"#version 400\n"
			"uniform mat4 MVP;\n"
			"attribute vec3 vCol;\n"
			"attribute vec3 vPos;\n"
			"varying vec3 color;\n"
			"void main()\n"
			"{\n"
			"    gl_Position = MVP * vec4(vPos, 1.0);\n"
			"    color = vCol;\n"
			"}\n";

		const char* StdUnlit::fragmentText =
			"#version 400\n"
			"varying vec3 color;\n"
			"void main()\n"
			"{\n"
			"    gl_FragColor = vec4(color, 1.0);\n"
			"}\n";

		GLuint StdUnlit::mvp_location;
		GLuint StdUnlit::vpos_location;
		GLuint StdUnlit::vcol_location;

		static class UnlitTexture
		{
		public:
			static const char* vertexText;
			static const char* fragmentText;

			static GLuint mvp_location;
			static GLuint vpos_location;
			static GLuint texcoord_location;

			inline static int GetVertexSize() { return sizeof( float ) * 5; } // x, y, z | u, v

			static void SetShaderInputs( GLuint program )
			{
				mvp_location      = glGetUniformLocation( program, "MVP" );
				vpos_location     = glGetAttribLocation( program, "vPos" );
				texcoord_location = glGetAttribLocation( program, "texcoord" );
			}

			static GLuint AttachVertexArray( const int& count, const GLfloat* vertexArray )
			{
				//Bind vertex data into buffer
				GLuint vertexBuffer;
				glGenBuffers( 1, &vertexBuffer );
				glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
				glBufferData( GL_ARRAY_BUFFER, GetVertexSize() * count, vertexArray, GL_DYNAMIC_DRAW );

				// Set up arrays
				RebindVertexArray( vertexBuffer );

				return vertexBuffer;
			}

			static void RebindVertexArray( const GLuint vertexBuffer )
			{
				glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
				glEnableVertexAttribArray( vpos_location );
				glVertexAttribPointer( vpos_location, 3, GL_FLOAT, GL_FALSE, GetVertexSize(), (void*) 0 );

				glEnableVertexAttribArray( texcoord_location );
				glVertexAttribPointer( texcoord_location, 2, GL_FLOAT, GL_FALSE, GetVertexSize(), (void*) ( sizeof( float ) * 3 ) );
			}

			static GLuint AttachTexture( GLFWimage* texture, GLenum wrapMode )
			{
				GLuint textureBuffer;
				glGenTextures( 1, &textureBuffer );
				
				RebindTexture( textureBuffer, wrapMode );

				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height, 
							  0, GL_RGBA, GL_UNSIGNED_BYTE, texture->pixels );

				// Make mipmaps
				glGenerateMipmap( GL_TEXTURE_2D );

				// Set parameters
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

				return textureBuffer;
			}

			static void RebindTexture( const GLuint textureBuffer, GLenum wrapMode )
			{
				glBindTexture( GL_TEXTURE_2D, textureBuffer );
			}
		};

		const char* UnlitTexture::vertexText =
			"#version 400\n"
			"uniform mat4 MVP;\n"
			"attribute vec2 texcoord;\n"
			"attribute vec3 vPos;\n"
			"varying vec2 Texcoord;\n"
			"void main()\n"
			"{\n"
			"    gl_Position = MVP * vec4(vPos, 1.0);\n"
			"    Texcoord = texcoord;\n"
			"}\n";

		const char* UnlitTexture::fragmentText =
			"#version 400\n"
			"varying vec2 Texcoord;\n"
			"uniform sampler2D sampler;\n"
			"void main()\n"
			"{\n"
			"    gl_FragColor = texture(sampler, Texcoord);\n"
			"}\n";

		GLuint UnlitTexture::mvp_location;
		GLuint UnlitTexture::vpos_location;
		GLuint UnlitTexture::texcoord_location;

		// To gennerate programs
		template<class T>
		GLuint GetGLProgram()
		{
			// Create vertex Shader
			GLuint vertex_shader = glCreateShader( GL_VERTEX_SHADER );
			glShaderSource( vertex_shader, 1, &( T::vertexText ), NULL );
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
	}
	
}