//
//  Screen.hpp
//  Bomberman
//
//  Created on 02/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Screen__hpp__
#define __Screen__hpp__

#include <memory>
#include <string>
#include <list>

#include "Math/Rectangle.hpp"

class SDL_Renderer;
class SDL_Window;

namespace Bomberman {
    class Layer;
    class LayerQueue;
    
    class Screen {
    public:
        Screen(int width, int height, std::string name);
        ~Screen();
        
        void draw();
        void update();
        
        std::string name() const;
        int width() const;
        int height() const;
        Rectangle rectangle() const;
        
        void setName(std::string name);
        void setWidth(int width);
        void setHeight(int height);
        void setSize(int width, int height);
        
        std::shared_ptr<SDL_Renderer> renderer() const;
        
        std::shared_ptr<LayerQueue> getLayerQueue() const;
        
        void refreshLayers();
        void clearLayers();
        
    protected:
        virtual void nameChanged(std::string prevName);
        virtual void sizeChanged(Rectangle previousSize);
        
    private:
        class LayerQueueImpl;
        
        void refreshSize(Rectangle previousSize);
        
        std::string _name;
        std::shared_ptr<SDL_Window> window;
        std::shared_ptr<SDL_Renderer> _renderer;
        Rectangle _rectangle;
        std::list<std::shared_ptr<Layer>> layers;
        std::shared_ptr<LayerQueueImpl> layerQueue;
    };
}

#endif //__Screen__hpp__
