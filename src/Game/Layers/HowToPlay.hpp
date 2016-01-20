//
//  HowToPlay.hpp
//  Bomberman
//
//  Created on 14/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#ifndef __HowToPlay__hpp__
#define __HowToPlay__hpp__

#include "../../Core/Drawable.hpp"
#include "../../Core/EventListener.hpp"
#include "../../Core/Texture.hpp"
#include "../../Core/Updatable.hpp"
#include "../../Core/SignalHandler.hpp"

#include <Vector>

struct SDL_Renderer;

namespace Bomberman {
    class Font;
    class Texture;
    class SignalSender;
    
    class HowToPlay : public EventListener, public Drawable, public Updatable, public SignalHandler {
    public:
        HowToPlay();
        
        void listenEvent(SDL_Event event);
        void draw();
        void update();
        void handleSignal(Signal signal);
        
        void load(std::shared_ptr<SDL_Renderer> renderer);
        
        void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
        
        void setSignalSender(std::weak_ptr<SignalSender> signalSender);
        
    private:
        void loadInstructions(Font font, std::shared_ptr<SDL_Renderer> renderer);
        void loadItems(Font font, std::shared_ptr<SDL_Renderer> renderer);
        void loadHud(Font font, std::shared_ptr<SDL_Renderer> hud);
        
        void setInstructionsPos(Rectangle screenSize);
        void setItemsPos(Rectangle screenSize);
        void setHudPos(Rectangle screenSize);
        
        void click(Coordinate position);
        void select(Coordinate position);
        
        bool isLeftButton(Coordinate position);
        bool isRightButton(Coordinate position);
        
        std::weak_ptr<SignalSender> signalSender;
        
        bool hide;
        enum class Page;
        Page page, nextPage;
        
        Texture mainMenu, instructionsText, itemsText, hudText;
        Texture *textRight, *textLeft;
        Texture prev, next;
        std::vector<Texture> instructions;
        std::vector<Texture> items;
        std::vector<Texture> hud;
    };
}

#endif //__HowToPlay__hpp__
