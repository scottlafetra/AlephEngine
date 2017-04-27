#include "Shaders.h"
#include "TestRenderer.h"
#include "gmtl/Generate.h"

static const struct
{
	float x, y;
	float r, g, b;
} vertices[3] =
{
	{ -0.6f, -0.4f, 1.f, 0.f, 0.f },
	{ 0.6f, -0.4f, 0.f, 1.f, 0.f },
	{ 0.f,  0.6f, 0.f, 0.f, 1.f }
};

TestRenderer::TestRenderer( AlephEngine::Entity* entity )
	: Renderer( entity ) 
{
	shaderProgram = Shaders::GetGLProgram<Shaders::StdUnlit>();
}

void TestRenderer::Render( gmtl::Matrix<float, 4, 4> view )
{
	//Bind vertex data into buffer
	GLuint vertex_buffer;
	glGenBuffers( 1, &vertex_buffer );
	glBindBuffer( GL_ARRAY_BUFFER, vertex_buffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

	// Set up arrays
	glEnableVertexAttribArray(Shaders::vpos_location);
	glVertexAttribPointer(Shaders::vpos_location, 2, GL_FLOAT, GL_FALSE,
		sizeof(float)* 5, (void*)0);

	glEnableVertexAttribArray(Shaders::vcol_location);
	glVertexAttribPointer(Shaders::vcol_location, 3, GL_FLOAT, GL_FALSE,
		sizeof(float)* 5, (void*)(sizeof(float)* 2));

	glUseProgram( shaderProgram );
	glUniformMatrix4fv( Shaders::mvp_location, 1, GL_FALSE, (const GLfloat*) view.mData );

	glDrawArrays( GL_TRIANGLES, 0, 3 );
	//glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0 );
}