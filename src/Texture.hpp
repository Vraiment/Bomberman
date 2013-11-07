//
//  Texture.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Texture__hpp__
#define __Texture__hpp__

struct SDL_Renderer;
struct SDL_Texture;

namespace Bomberman {
	class Texture {
	public:
		Texture();
		Texture(std::string fileName, std::shared_ptr<SDL_Renderer> renderer);
		
		bool loaded() const;
		
		void draw(int i, int j);
		
		std::string getName() const;
		void getTileTextureWidth() const;
		void getTileTextureHeight() const;
		
	private:
		bool _loaded;
		std::shared_ptr<SDL_Renderer> renderer;
		std::shared_ptr<SDL_Texture> texture;
		std::string name;
	};
}

#endif //__Texture__hpp__
