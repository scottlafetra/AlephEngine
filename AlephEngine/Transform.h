#pragma once

#include <gmtl/Matrix.h>
#include <gmtl/VecBase.h>
#include <gmtl/Vec.h>
#include <gmtl/Quat.h>
#include <list>
#include "Component.h"

namespace AlephEngine
{
	class Transform : public Component
	{
	private:
		float scale;
		gmtl::Quat<float> rotation;
		gmtl::Vec<float, 3> position;
		gmtl::Matrix<float, 4, 4> transformMatrix;

		bool isUpdated;

		Transform* parent;
		std::list<Transform*> children;

	public:
		Transform(Entity* entity);

		gmtl::Matrix<float, 4, 4> GetTransfromMatrix();
		inline gmtl::Quat<float> GetRotation() { return rotation; }
		inline gmtl::Vec<float, 3> GetPosition() { return position; }

		void SetScale( float newScale );
		void Scale( float factor );

		void SetPosition( const gmtl::Vec<float, 3>& newPosition );
		void SetPosition( const float& x, const float& y, const float& z = 0.0 );
		void Move( const gmtl::Vec<float, 3>& dPosition );
		void Move( const float& dx, const float& dy, const float& dz = 0.0 );

		void SetRotation( const gmtl::Quat<float>& setRotation );
		void SetRotation( const float& x, const float& y, const float& z = 0.0 );
		void Rotate( const gmtl::Quat<float>& dRotation );
		void Rotate( const float& dx, const float& dy, const float& dz = 0.0 );

		void SetAsParent( Transform* newParent );
		void SetAsChild( Transform* newChild );

		inline Transform* GetParent() { return parent; }
		inline std::list<Transform*> GetChildren() { return children; }
	};
}
