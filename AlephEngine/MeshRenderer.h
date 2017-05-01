#pragma once
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include "Renderer.h"
#include "Shaders.h"

namespace AlephEngine
{
	template< class T >
	class MeshRenderer : public Renderer
	{
	private:
		GLenum renderMode;
		GLint vertexCount;
		GLfloat* vertices;
		GLuint vertexBuffer;

		bool hasTexture;
		GLuint texureBuffer;
		GLenum texureWrapMode;

	public:
		MeshRenderer( AlephEngine::Entity* entity );
		void Render( gmtl::Matrix<float, 4, 4> view ) override;
		void SetVertices( const GLenum renderMode, GLint vertexCount, const GLfloat* vertexArray);
		void SetTexture( GLFWimage* texture, GLenum wrapMode = GL_REPEAT );
	};
}

#include "MeshRenderer.inl"