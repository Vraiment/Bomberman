//
//  PauseMenu.hpp
//  Bomberman
//
//  Created on 13/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#ifndef __PauseMenu__hpp__
#define __PauseMenu__hpp__

#include "../../Core/Drawable.hpp"
#include "../../Core/EventListener.hpp"
#include "../../Core/Texture.hpp"
#include "../../Core/Updatable.hpp"
#include "../../Core/SignalHandler.hpp"

struct SDL_Renderer;

namespace Bomberman {
    class LoopQuiter;
    class SignalSender;
    
    class PauseMenu : public EventListener, public Drawable, public Updatable, public SignalHandler {
    public:
        PauseMenu();
        
        void listenEvent(SDL_Event event);
        void draw();
        void update();
        void handleSignal(Signal signal);
        
        void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
        
        void load(std::shared_ptr<SDL_Renderer> renderer);
        
        void setSignalSender(std::weak_ptr<SignalSender> signalSender);
        void setLoopQuiter(std::weak_ptr<LoopQuiter> loopQuitter);
        
        void show();
        void hide();
        
    private:
        void pushSelectedButton();
        void select(Coordinate position);
        
        std::weak_ptr<SignalSender> signalSender;
        std::weak_ptr<LoopQuiter> loopQuiter;
        
        int selected;
        bool clicking;
        
        Texture background;
        Texture continueGame;
        Texture quitToMainMenu;
        Texture quitToDesktop;
    };
}

#endif //__PauseMenu__hpp__
