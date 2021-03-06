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
    class TileMap;
    class LoopQuiter;
    
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
        
        void setLoopQuiter(std::weak_ptr<LoopQuiter> loopQuiter);
        void setSignalSender(std::weak_ptr<SignalSender> signalSender);
        
    private:
        bool clicked, mouseMoved;
        bool lCtrl, rCtrl;
        Coordinate mousePos;
        Texture noMap;
        
        std::shared_ptr<TileMap> tileMap;
        
        std::weak_ptr<LoopQuiter> loopQuiter;
        std::weak_ptr<SignalSender> signalSender;
    };
}

#endif //__MapEditor__hpp__
