#include "LoadSceneAfterTime.h"
#include "../SceneLoading/SceneLoader.h"
#include "../Core/EngineTime.h"

LoadSceneAfterTime::LoadSceneAfterTime( Entity* entity )
	: Component( entity, Type<LoadSceneAfterTime>() )
{
	GetScene()->AddUpdateCallback( this );
}

LoadSceneAfterTime::~LoadSceneAfterTime()
{
	GetScene()->RemoveUpdateCallback( this );
}

void LoadSceneAfterTime::Update()
{
	if( EngineTime::GetTime() > timeToWait )
	{
		SceneLoader::SwitchToScene( SceneLoader::LoadScene( sceneToLoad ), GetScene()->GetWindowHandle() );
	}
}