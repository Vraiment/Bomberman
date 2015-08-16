//
//  Console.cpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "Console.hpp"

#include "CommandQueue.hpp"
#include "EventListener.hpp"
#include "Layer.hpp"

using namespace std;

namespace Bomberman {
	Console::Console(shared_ptr<CommandFactory> commandFactory, shared_ptr<CommandQueue> commandQueue, shared_ptr<Layer> consoleLayer, shared_ptr<Layer> gameLayer, shared_ptr<EventListener> playerEvents) : parser(commandFactory), commandQueue(commandQueue), consoleLayer(consoleLayer), gameLayer(gameLayer), playerEvents(playerEvents) {
		
	}
	
	bool Console::visible() const {
		return consoleLayer->shouldDraw();
	}
	
	void Console::hide() {
		consoleLayer->shouldDraw(false);
		gameLayer->shouldUpdate(true);
		playerEvents->enable();
	}
	
	void Console::show() {
		consoleLayer->shouldDraw(true);
		gameLayer->shouldUpdate(false);
		playerEvents->disable();
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
