#pragma once
#include <Matrix.h>
#include <VecBase.h>
#include <Vec.h>
#include <Quat.h>
#include "Component.h"

namespace AlephEngine
{
	class Transform : public Component
	{
	private:
		gmtl::Quat<float> rotation;
		gmtl::Vec<float, 3> position;
		gmtl::Matrix<float, 4, 4> transformMatrix;

		bool isUpdated;

	public:
		Transform(Entity* entity);

		gmtl::Matrix<float, 4, 4> GetTransfromMatrix();
		inline gmtl::Quat<float> GetRotation() { return rotation; }
		inline gmtl::Vec<float, 3> GetPosition() { return position; }

		void SetPosition( const gmtl::Vec<float, 3>& newPosition );
		void SetPosition( const float& x, const float& y, const float& z = 0.0 );
		void Move( const gmtl::Vec<float, 3>& dPosition );
		void Move( const float& dx, const float& dy, const float& dz = 0.0 );

		void SetRotation( const gmtl::Quat<float>& setRotation );
		void SetRotation( const float& x, const float& y, const float& z = 0.0 );
		void Rotate( const gmtl::Quat<float>& dRotation );
		void Rotate( const float& dx, const float& dy, const float& dz = 0.0 );
	};
}
