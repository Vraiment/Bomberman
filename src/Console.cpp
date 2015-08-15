//
//  Console.cpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "Console.hpp"

#include "CommandQueue.hpp"

using namespace std;

namespace Bomberman {
	Console::Console(shared_ptr<CommandFactory> commandFactory, shared_ptr<CommandQueue> commandQueue) : parser(commandFactory), commandQueue(commandQueue) {
		
	}
	
	bool Console::visible() const {
		return isVisible;
	}
	
	void Console::hide() {
		isVisible = false;
	}
	
	void Console::show() {
		isVisible = true;
	}
	
	void Console::addToBuffer(char character) {
		buffer << character;
	}
	
	void Console::removeLastFromBuffer() {
		buffer.ignore();
	}
	
	void Console::clearBuffer() {
		buffer.str(string());
		buffer.clear();
	}
	
	void Console::commitBuffer() {
		string fullBuffer = buffer.str();
		clearBuffer();
		
		Log::get() << fullBuffer << LogLevel::info;
		auto cmds = parser.parse(buffer.str());
		
		while (!cmds.empty()) {
			auto cmd = cmds.front();
			commandQueue->addCommand(cmd);
			cmds.pop();
		}
	}
}
