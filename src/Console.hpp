//
//  Console.hpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __Console__hpp__
#define __Console__hpp__

#include <memory>
#include <sstream>

#include "Console/Parser.hpp"

namespace Bomberman {
	class CommandFactory;
	class CommandQueue;
	
	class Console {
	public:
		Console(std::shared_ptr<CommandFactory> commandFactory, std::shared_ptr<CommandQueue> commandQueue);
		
		bool visible() const;
		
		void hide();
		void show();
		
		void addToBuffer(char character);
		void removeLastFromBuffer();
		void clearBuffer();
		void commitBuffer();
		
	private:
		std::stringstream buffer;
		std::shared_ptr<CommandQueue> commandQueue;
		
		bool isVisible;
		Parser parser;
	};
}

#endif //__Console__hpp__
