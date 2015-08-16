//
//  ConsoleLayer.hpp
//  Bomberman
//
//  Created on 16/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __ConsoleLayer__hpp__
#define __ConsoleLayer__hpp__

#include <deque>

#include "../Font.hpp"
#include "../Layer.hpp"
#include "../Log/Logger.hpp"
#include "../Texture.hpp"
#include "../Timer.hpp"

namespace Bomberman {
	class ConsoleLayer : public Layer, public Logger {
	public:
		ConsoleLayer();
		
		void update();
		void draw();
		
		void loadGraphics(std::shared_ptr<SDL_Renderer> renderer);
		
		void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
		
		void setInput(std::string input);
		void clearInput();
	
	protected:
		void recieveLog(std::string text, LogLevel level);
		
	private:
		static const int BLINK_TIME;
		static const int FONT_SIZE;
		static const int QUEUE_SIZE;
		
		Font font;
		Texture background, inputBackground;
		std::shared_ptr<SDL_Renderer> renderer;
		std::deque<Texture> lines;
		
		Texture prompt, inputLine, cursor;
		bool drawCursor;
		Timer cursorBlink;
	};
}

#endif //__ConsoleLayer__hpp__
