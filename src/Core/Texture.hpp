//
//  Texture.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Texture__hpp__
#define __Texture__hpp__

#include <memory>
#include <string>

#include "Math/Rectangle.hpp"

struct SDL_Renderer;
struct SDL_Texture;

namespace Bomberman {
    class Color;
    
    class Texture {
    friend class Font;
    public:
        static const uint8_t OPAQUE;
        static const uint8_t TRANSPARENT;
        
        Texture();
        Texture(std::string fileName, std::shared_ptr<SDL_Renderer> renderer);
        
        void draw();
        
        void clear();
        
        void setColor(Color color);
        void setAlpha(uint8_t alpha);
        
        bool isLoaded() const;
        std::string name() const;
        Coordinate& position();
        Rectangle& rectangle();
        void resetSize();
        
        static Texture createRectangle(int width, int height, Color color, std::shared_ptr<SDL_Renderer> renderer);
        
    private:
        bool _loaded;
        std::shared_ptr<SDL_Renderer> renderer;
        std::shared_ptr<SDL_Texture> texture;
        std::string _name;
        Rectangle _rectangle;
        
        Texture(SDL_Texture *t, std::string name, std::shared_ptr<SDL_Renderer> renderer);
        void loadTexture(SDL_Texture *t);
    };
}

#endif //__Texture__hpp__
