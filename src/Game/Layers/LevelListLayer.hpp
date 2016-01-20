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
#include "../../Core/SignalHandler.hpp"

#include <vector>
#include <utility>

struct SDL_Renderer;

namespace Bomberman {
    struct Coordinate;
    class SignalSender;
    
    class LevelListLayer : public Drawable, public EventListener, public Updatable, public SignalHandler {
    public:
        LevelListLayer();
        
        void listenEvent(SDL_Event event);
        void draw();
        void update();
        void handleSignal(Signal signal);
        
        bool loaded() const;
        void load(std::shared_ptr<SDL_Renderer> renderer);
        void fillMapList();
        
        void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
        
        void setSignalSender(std::weak_ptr<SignalSender> signalSender);
        
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
        
        std::weak_ptr<SignalSender> signalSender;
    };
}

#endif //__LevelListLayer__hpp__
