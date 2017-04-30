#pragma once
#include "gmtl/Generate.h"
using namespace AlephEngine;

template <class T>
MeshRenderer<T>::MeshRenderer( AlephEngine::Entity* entity )
	: Renderer( entity )
{
	shaderProgram = Shaders::GetGLProgram<T>();
}

template <class T>
void MeshRenderer<T>::SetVertices( const GLenum renderMode, GLint vertexCount, const GLfloat* vertices )
{
	// Init render variables
	this->renderMode = renderMode;
	this->vertexCount = vertexCount;
	this->vertices = new GLfloat[ vertexCount * ( T::GetVertexSize() / sizeof(float) ) ];
	memcpy( this->vertices, vertices, T::GetVertexSize() * vertexCount );

	vertexBuffer = T::AttachVertexArray( vertexCount, MeshRenderer<T>::vertices );
}

template <class T>
void MeshRenderer<T>::Render( gmtl::Matrix<float, 4, 4> view )
{

	// Attach things
	T::RebindVertexArray( vertexBuffer );

	glUseProgram( shaderProgram );

	glUniformMatrix4fv( T::mvp_location, 1, GL_FALSE, (const GLfloat*) view.mData );

	glDrawArrays( renderMode, 0, vertexCount );
}