//
//  LevelListLayer.hpp
//  Bomberman
//
//  Created on 12/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#ifndef __LevelListLayer__hpp__
#define __LevelListLayer__hpp__

#include "../../Core/Drawable.hpp"
#include "../../Core/EventListener.hpp"
#include "../../Core/Updatable.hpp"
#include "../../Core/Texture.hpp"
#include "../../Core/Font.hpp"

#include <vector>
#include <utility>

struct SDL_Renderer;

namespace Bomberman {
    struct Coordinate;
    class Director;
    
    class LevelListLayer : public Drawable, public EventListener, public Updatable {
    public:
        LevelListLayer();
        
        void listenEvent(SDL_Event event);
        void draw();
        void update();
        
        bool loaded() const;
        void load(std::shared_ptr<SDL_Renderer> renderer);
        void fillMapList();
        
        void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
        
        void setDirector(std::weak_ptr<Director> director);
        
    private:
        enum class Button;
        
        void click(Coordinate position);
        void select(Coordinate position);
        
        Font font;
        
        Button selectedButton;
        Button clickedButton;
        
        int selected, newSelected;
        
        std::vector<std::pair<std::string, Texture>> maps;
        
        Texture background;
        
        Texture reload;
        Texture cancel;
        Texture ok;
        
        std::weak_ptr<Director> director;
    };
}

#endif //__LevelListLayer__hpp__
