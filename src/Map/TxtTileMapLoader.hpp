//
//  TxtTileMapLoader.hpp
//  Bomberman
//
//  Created on 09/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#ifndef __TxtTileMapLoader__hpp__
#define __TxtTileMapLoader__hpp__

#include <string>
#include <vector>

namespace Bomberman {
	class TileMapBuilder;
	
	class TxtTileMapLoader {
	public:
		~TxtTileMapLoader();
		
		std::shared_ptr<TileMapBuilder> load(std::string fileName);
		
	private:
		std::shared_ptr<TileMapBuilder> _builder;
		
		bool processCommand(std::string command, std::vector<std::string> arguments);
	};
}

#endif // __TxtTileMapLoader__hpp__
