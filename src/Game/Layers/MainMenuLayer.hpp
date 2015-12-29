//
//  MainMenuLayer.hpp
//  Bomberman
//
//  Created on 27/12/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __MainMenuLayer__hpp__
#define __MainMenuLayer__hpp__

#include "../../Core/Layer.hpp"

#include "../../Core/Texture.hpp"

namespace Bomberman {
    class EventListenerQueue;
    class LayerQueue;
    class LoopQuiter;
    
    class MainMenuLayer : public Layer {
    public:
        MainMenuLayer();
        
        void update();
        void draw();
        
        void select(Coordinate position);
        void click(Coordinate position);
        
        void setEventListenerQueue(std::shared_ptr<EventListenerQueue> eventListenerQueue);
        void setLayerQueue(std::shared_ptr<LayerQueue> layerManager);
        void setLoopQuiter(std::shared_ptr<LoopQuiter> loopQuiter);
        
        void load(std::shared_ptr<SDL_Renderer> renderer);
        
        void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
        
    private:
        static const int ENTRIES_SPACING;
        
        bool shouldStartGame, shouldExit;
        Texture *selected;
        Texture startGame;
        Texture exit;
        std::shared_ptr<LayerQueue> layerQueue;
        std::shared_ptr<LoopQuiter> loopQuiter;
        std::shared_ptr<SDL_Renderer> renderer;
        std::shared_ptr<EventListenerQueue> eventListenerQueue;
    };
}

#endif //__MainMenuLayer__hpp__
