//
//  Texture.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Texture__hpp__
#define __Texture__hpp__

struct SDL_Texture;

namespace Bomberman {
	class Texture {
	public:
		Texture();
		Texture(std::string fileName, Renderer renderer);
		
		bool loaded() const;
		
		void draw(int i, int j);
		
	private:
		bool _loaded;
		Renderer renderer;
		std::shared_ptr<SDL_Texture> texture;
	};
}

#endif //__Texture__hpp__
