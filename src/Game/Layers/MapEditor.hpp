//
//  MapEditor.hpp
//  Bomberman
//
//  Created on 21/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#ifndef __MapEditor__hpp__
#define __MapEditor__hpp__

#include "../../Core/Drawable.hpp"
#include "../../Core/EventListener.hpp"
#include "../../Core/Updatable.hpp"
#include "../../Core/SignalHandler.hpp"
#include "../../Core/Texture.hpp"

#include <memory>
#include <vector>

struct SDL_Renderer;

namespace Bomberman {
    class SignalSender;
    
    class MapEditor : public Drawable, public EventListener, public Updatable, public SignalHandler {
    public:
        MapEditor();
        ~MapEditor();
        
        void draw();
        void listenEvent(SDL_Event event);
        void update();
        void postUpdate();
        void handleSignal(Signal signal);
        
        void load(std::shared_ptr<SDL_Renderer> renderer);
        void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
        
        void setSignalSender(std::weak_ptr<SignalSender> signalSender);
        
    private:
        class MenuBar;
        std::shared_ptr<MenuBar> menuBar;
        
        bool clicked, mouseMoved;
        Coordinate mousePos;
        
        std::weak_ptr<SignalSender> signalSender;
    };
}

#endif //__MapEditor__hpp__
