#include "SceneLoader.h"

#include <iostream>
#include <fstream>

#include <../rapidxml-1.13/rapidxml.hpp>
#include <../rapidxml-1.13/rapidxml_print.hpp>

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

	// TODO: Return Scene
	std::cout << "Printing scene:" << std::endl;
	std::cout << sceneDoc;
	return nullptr;
}
