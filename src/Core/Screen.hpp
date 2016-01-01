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

union SDL_Event;
class SDL_Renderer;
class SDL_Window;

namespace Bomberman {
    class EventListener;
    class Drawable;
    class ScreenManager;
    class Updatable;
    
    class Screen {
    public:
        Screen(int width, int height, std::string name);
        ~Screen();
        
        void listenEvent(SDL_Event event);
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
        
        std::shared_ptr<ScreenManager> getScreenManager();
        
        void refreshScreen();
        
    protected:
        virtual void nameChanged(std::string prevName);
        virtual void sizeChanged(Rectangle previousSize);
        
    private:
        void refreshSize(Rectangle previousSize);
        
        std::string _name;
        std::shared_ptr<SDL_Window> window;
        std::shared_ptr<SDL_Renderer> _renderer;
        Rectangle _rectangle;
        
        std::shared_ptr<ScreenManager> screenManager;
        
        std::list<std::shared_ptr<EventListener>> eventListeners;
        std::list<std::shared_ptr<Drawable>> drawables;
        std::list<std::shared_ptr<Updatable>> updatables;
    };
}

#endif //__Screen__hpp__
