#include "Shaders.h"

void AlephEngine::Shaders::StdUnlit::SetShaderInputs( GLuint program )
{
	mvp_location = glGetUniformLocation( program, "MVP" );
	vpos_location = glGetAttribLocation( program, "vPos" );
	vcol_location = glGetAttribLocation( program, "vCol" );
}

GLuint AlephEngine::Shaders::StdUnlit::AttachVertexArray( const int& count, const GLfloat* vertexArray )
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

void AlephEngine::Shaders::StdUnlit::RebindVertexArray( const GLuint vertexBuffer )
{
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	glEnableVertexAttribArray( vpos_location );
	glVertexAttribPointer( vpos_location, 3, GL_FLOAT, GL_FALSE, GetVertexSize(), (void*)0 );

	glEnableVertexAttribArray( vcol_location );
	glVertexAttribPointer( vcol_location, 3, GL_FLOAT, GL_FALSE, GetVertexSize(), (void*)(sizeof( float ) * 3) );
}

const char* AlephEngine::Shaders::StdUnlit::vertexText =
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

const char* AlephEngine::Shaders::StdUnlit::fragmentText =
	"#version 400\n"
	"varying vec3 color;\n"
	"void main()\n"
	"{\n"
	"    gl_FragColor = vec4(color, 1.0);\n"
	"}\n";

GLuint AlephEngine::Shaders::StdUnlit::mvp_location;
GLuint AlephEngine::Shaders::StdUnlit::vpos_location;
GLuint AlephEngine::Shaders::StdUnlit::vcol_location;

void AlephEngine::Shaders::UnlitTexture::SetShaderInputs( GLuint program )
{
	mvp_location = glGetUniformLocation( program, "MVP" );
	vpos_location = glGetAttribLocation( program, "vPos" );
	texcoord_location = glGetAttribLocation( program, "texcoord" );
}

GLuint AlephEngine::Shaders::UnlitTexture::AttachVertexArray( const int& count, const GLfloat* vertexArray )
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

void AlephEngine::Shaders::UnlitTexture::RebindVertexArray( const GLuint vertexBuffer )
{
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	glEnableVertexAttribArray( vpos_location );
	glVertexAttribPointer( vpos_location, 3, GL_FLOAT, GL_FALSE, GetVertexSize(), (void*)0 );

	glEnableVertexAttribArray( texcoord_location );
	glVertexAttribPointer( texcoord_location, 2, GL_FLOAT, GL_FALSE, GetVertexSize(), (void*)(sizeof( float ) * 3) );
}

GLuint AlephEngine::Shaders::UnlitTexture::AttachTexture( GLFWimage* texture, GLenum wrapMode )
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

void AlephEngine::Shaders::UnlitTexture::RebindTexture( const GLuint textureBuffer, GLenum wrapMode )
{
	glBindTexture( GL_TEXTURE_2D, textureBuffer );
}

const char* AlephEngine::Shaders::UnlitTexture::vertexText =
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

const char* AlephEngine::Shaders::UnlitTexture::fragmentText =
"#version 400\n"
"varying vec2 Texcoord;\n"
"uniform sampler2D sampler;\n"
"void main()\n"
"{\n"
"    gl_FragColor = texture(sampler, Texcoord);\n"
"}\n";

GLuint AlephEngine::Shaders::UnlitTexture::mvp_location;
GLuint AlephEngine::Shaders::UnlitTexture::vpos_location;
GLuint AlephEngine::Shaders::UnlitTexture::texcoord_location;
