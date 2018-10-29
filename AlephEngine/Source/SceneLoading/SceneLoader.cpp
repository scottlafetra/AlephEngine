#include "SceneLoader.h"

#include <iostream>
#include <fstream>

#include <../rapidxml-1.13/rapidxml.hpp>
#include <../rapidxml-1.13/rapidxml_print.hpp>

#include "../Core/Scene.h"
#include "../Core/Entity.h"
#include "../Core/Transform.h"

#include "ComponentBuilder.h"

#include <exception>

using namespace AlephEngine;

// Just print the scene for milestone 1
Scene* SceneLoader::LoadScene( std::string path )
{
	std::ifstream sceneStream;
	sceneStream.open( path );

	// Read the file into memory
	std::string sceneXML( 
		(std::istreambuf_iterator<char>( sceneStream )),
		std::istreambuf_iterator<char>() 
	);

	sceneStream.close();

	rapidxml::xml_document<> sceneDoc;

	// Make a copy for string saftey
	std::string sceneXMLcpy( sceneXML );
	try 
	{
		sceneDoc.parse<0>( const_cast<char*>(sceneXMLcpy.c_str()) );
	}
	catch( rapidxml::parse_error error )
	{
		std::cerr << "XML Error loading scene: " << error.what() << std::endl;
		return nullptr;
	}

	// TODO: make windows not tied to scenes
	Scene* scene = new Scene();
	scene->CreateAlephWindow( 800, 600 );
	scene->SetWindowTitle( "Loaded Window" );
	
	rapidxml::xml_node<char>* currentEntity = sceneDoc.first_node( "scene", 0 )->first_node();

	while( currentEntity != nullptr )
	{
		// Do starting stuff
		std::string entityName( currentEntity->first_attribute( "name", 0 )->value() );

		if( entityName == "" )
		{
			std::cerr << "Error: Enitity does not have name" << std::endl;
			entityName = "No Name";
		}

		Entity* sceneEnity = scene->AddEntity( entityName );

		// Process Generic Components
		rapidxml::xml_node<char>* currentComponent = currentEntity->first_node();

		while( currentComponent != nullptr )
		{
			if( !strcmp( currentComponent->name() , "component" ) )
			{
				std::string className( currentComponent->first_attribute( "class", 0 )->value() );

				if( className == "" )
				{
					std::cerr << "Error: Component does not have class" << std::endl;
				}
				else
				{
					// Build Component
					IBuilder* builder = CreateComponentBuilder( sceneEnity, className );

					if( builder == nullptr )
					{
						std::cerr << "Error: Builder for class \"" + className + "\" not found.";
					}
					else 
					{
						// Add all attributes
						rapidxml::xml_attribute<char>* currentAttribute = currentComponent->first_attribute();

						while( currentAttribute != nullptr )
						{
							// If the attribute is not class
							if( std::strcmp( currentAttribute->name(), "class" ) )
							{
								builder->AddVar( currentAttribute->name(), currentAttribute->value() );
							}

							currentAttribute = currentAttribute->next_attribute();
						}

						delete builder;
					}
					
				}
			} // Process transform special case
			else if( !strcmp( currentComponent->name(), "transform" ) )
			{
				rapidxml::xml_attribute<char> * scale = currentComponent->first_attribute( "scale", 0 );
				if( scale != nullptr )
				{
					sceneEnity->FetchComponent<Transform>()->SetScale( std::stof( scale->value() ) );
				}

				rapidxml::xml_node<char> * transformNode = currentComponent->first_node();
				while( transformNode != nullptr )
				{
					if( !strcmp( transformNode->name(), "location" ) )
					{
						// Find attributes
						rapidxml::xml_attribute<char>* currentAttribute = transformNode->first_attribute();

						float x = 0;
						float y = 0;
						float z = 0;

						while( currentAttribute != nullptr )
						{
							if( !std::strcmp( currentAttribute->name(), "x" ) )
							{
								x = std::stof( currentAttribute->value() );
							}
							else if( !std::strcmp( currentAttribute->name(), "y" ) )
							{
								y = std::stof( currentAttribute->value() );
							}
							else if( !std::strcmp( currentAttribute->name(), "z" ) )
							{
								z = std::stof( currentAttribute->value() );
							}

							currentAttribute = currentAttribute->next_attribute();
						}

						// Set Values
						sceneEnity->FetchComponent<Transform>()->SetPosition(x, y, z);
					}

					transformNode = transformNode->next_sibling();
				}
			}

			currentComponent = currentComponent->next_sibling();
		}

		currentEntity = currentEntity->next_sibling();
	}

	// TODO: Return Scene
	std::cout << "Printing scene file:" << std::endl;
	std::cout << sceneDoc;
	std::cout <<  "----------------------------------------------" << std::endl;

	return scene;
}