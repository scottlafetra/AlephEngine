#include "Collision.h"
#include "../Core/Transform.h"

Collider::Collider(Entity* entity) :
	Component(entity, Component::Type<Collider>())
{
	if( (myKin = entity->FetchComponent<Kinematics>()) == NULL )
	{
		FatalError( "Collider component not attached to entity with Kinematics component." );
	}

	if( (myTransform = entity->FetchComponent<Transform>()) == NULL )
	{
		FatalError( "Transform component not attached to entity with Kinematics component." );
	}

	GetScene()->AddUpdateCallback( this );
}

void Collider::Update()
{
	updateBounds();
}

void Collider::getMomentum(){

}

void Collider::SetMesh( const std::vector<float>& collisionMesh )
{
	Collider::collisionMesh = collisionMesh;
}

void Collider::updateBounds(){

	gmtl::Vec<float, 3> firstPoint = myTransform->LocalToGlobal( gmtl::Vec<float, 3>{ collisionMesh[0], collisionMesh[1], collisionMesh[2] } );

	gmtl::Vec<float, 3> min = firstPoint;
	gmtl::Vec<float, 3> max = min;
	
	for (int i = 0; i < collisionMesh.size(); i += 3) {
		gmtl::Vec<float, 3> p = myTransform->LocalToGlobal(  gmtl::Vec<float, 3>(collisionMesh[i], collisionMesh[i + 1], collisionMesh[i + 2]) );

		for( int d = 0; d < 3; d++ )
		{
			// Max the max and min for each dimension d
			if( p[d] > max[d] )
			{ 
				max[d] = p[d];
			}
			else if( p[d] < min[d] )
			{
				min[d] = p[d];
			}
		}
	}

	BoundingBoxDems = *new gmtl::Vec<float, 3>(std::abs(max[0] - min[0]), std::abs(max[1] - min[1]), std::abs(max[2] - min[2]));
	BoundingBoxCenter = *new gmtl::Vec<float, 3>(max[0] - BoundingBoxDems[0] / 2, max[1] - BoundingBoxDems[1] / 2, max[2] - BoundingBoxDems[2] / 2);
}

Collision* Collider::checkCollision( Collider& other){
	
	//if X overlaps
	float X_Overlap = checkXOverlap(other);
	if (X_Overlap > 0) {
		//if X overlaps
		float Y_Overlap = checkYOverlap(other);
		if (Y_Overlap > 0) {
			//if Z overlaps
			float Z_Overlap = checkZOverlap(other);
			if (Z_Overlap > 0) {
				//if we get here then the two objects have collided
				//TODO: return usefull info with Coll
				return new Collision(this, &other, X_Overlap, Y_Overlap, Z_Overlap);
			}
		}
	}
	//return nothing if we haven't collided
	return nullptr;
}

float Collider::checkXOverlap( Collider& other){
	gmtl::Vec<float, 2> other_X = *other.getXBounds();
	gmtl::Vec<float, 2> this_X = *getXBounds();
	float overlap = 0;
	if (this_X[0] < other_X[0] && other_X[0] < this_X[1]) {
		//which ever is lower
		(this_X[1] - other_X[0]) > (other.getBoundingBoxDems()[0]) ? overlap = other.getBoundingBoxDems()[0] : overlap = this_X[1] - other_X[0];

	} else if (this_X[0] < other_X[1] && other_X[1] < this_X[1]) {
		overlap = other_X[1] - this_X[0];
	}

	return overlap;
}

float Collider::checkYOverlap( Collider& other){
	gmtl::Vec<float, 2> other_Y = *other.getYBounds();
	gmtl::Vec<float, 2> this_Y = *getYBounds();
	float overlap = 0;
	if (this_Y[0] < other_Y[0] && other_Y[0] < this_Y[1]) {
		//which ever is lower
		(this_Y[1] - other_Y[0]) > (other.getBoundingBoxDems()[1]) ? overlap = other.getBoundingBoxDems()[1] : overlap = this_Y[1] - other_Y[0];

	}
	else if (this_Y[0] < other_Y[1] && other_Y[1] < this_Y[1]) {
		overlap = other_Y[1] - this_Y[0];
	}

	return overlap;
}

float Collider::checkZOverlap( Collider& other){
	gmtl::Vec<float, 2> other_Z = *(other.getZBounds());
	gmtl::Vec<float, 2> this_Z = *getZBounds();
	float overlap = 0;
	if (this_Z[0] < other_Z[0] && other_Z[0] < this_Z[1]) {
		//which ever is lower
		(this_Z[1] - other_Z[0]) > (other.getBoundingBoxDems()[2]) ? overlap = other.getBoundingBoxDems()[2] : overlap = this_Z[1] - other_Z[0];

	}
	else if (this_Z[0] < other_Z[1] && other_Z[1] < this_Z[1]) {
		overlap = other_Z[1] - this_Z[0];
	}

	return overlap;
}

gmtl::Vec<float, 2>* Collider::getXBounds(){
	float Lower = BoundingBoxCenter[0] - BoundingBoxDems[0] / 2;
	float Upper = BoundingBoxCenter[0] + BoundingBoxDems[0] / 2;
	return new gmtl::Vec<float, 2>(Lower, Upper);
}

gmtl::Vec<float, 2>* Collider::getYBounds(){
	float Lower = BoundingBoxCenter[1] - BoundingBoxDems[1] / 2;
	float Upper = BoundingBoxCenter[1] + BoundingBoxDems[1] / 2;
	return new gmtl::Vec<float, 2>(Lower, Upper);
}

gmtl::Vec<float, 2>* Collider::getZBounds(){
	float Lower = BoundingBoxCenter[2] - BoundingBoxDems[2] / 2;
	float Upper = BoundingBoxCenter[2] + BoundingBoxDems[2] / 2;
	return new gmtl::Vec<float, 2>(Lower, Upper);
}
