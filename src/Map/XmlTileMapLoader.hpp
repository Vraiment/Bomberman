//
//  XmlTileMapLoader.hpp
//  Bomberman
//
//  Created on 09/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __TileMapLoader__hpp__
#define __TileMapLoader__hpp__

#include <string>
#include <tinyxml2/tinyxml2.h>

namespace Bomberman {
	class TileMapBuilder;
	
	class XmlTileMapLoader {
	public:
		~XmlTileMapLoader();
		
		std::shared_ptr<TileMapBuilder> load(std::string fileName);
		
	private:
		void reset();
		
		void loadDimension(tinyxml2::XMLElement *root);
		void loadName(tinyxml2::XMLElement *nameNode);
		void loadPlayer(tinyxml2::XMLElement *playerNode);
		void loadBricks(tinyxml2::XMLElement *bricksNode);
		
		std::string fileName;
		tinyxml2::XMLDocument document;
		bool _error;
		std::shared_ptr<TileMapBuilder> builder;
	};
}

#endif //__TileMapLoader__hpp__
