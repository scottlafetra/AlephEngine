#include "LinkTester.h"



LinkTester::LinkTester( Entity* entity )
	: Component( entity, Type<LinkTester>() )
{
	GetScene()->AddUpdateCallback( this );
}


void LinkTester::Update()
{
	if( link == nullptr )
	{
		Error( "Link not created." );
	}
	else
	{
		std::cout << "SecretNum: " << secretNum << " Linked SecretNum: " << link->secretNum << std::endl;
	}
	
	GetScene()->RemoveUpdateCallback( this );
}
