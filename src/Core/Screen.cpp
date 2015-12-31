    //
//  Screen.cpp
//  Bomberman
//
//  Created on 06/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Screen.hpp"

#include <SDL2/SDL.h>

#include "EventListener.hpp"
#include "EventListenerQueue.hpp"
#include "Layer.hpp"
#include "LayerQueue.hpp"
#include "Log/LogSystem.h"

using namespace std;

namespace Bomberman {
    class Screen::EventListenerQueueImpl : public EventListenerQueue {
    public:
        shared_ptr<EventListener> getNewEventListener() {
            shared_ptr<EventListener> nextEventListener;
            
            if (!eventListeners.empty()) {
                nextEventListener = eventListeners.front();
                eventListeners.pop();
            }
            
            return nextEventListener;
        }
    };
    
    class Screen::LayerQueueImpl : public LayerQueue {
    public:
        shared_ptr<Layer> getNewLayer() {
            shared_ptr<Layer> nextLayer;
            
            if (!layers.empty()) {
                nextLayer = layers.front();
                layers.pop();
            }
            
            return nextLayer;
        }
    };
    
    Screen::Screen(int width, int height, string name) : _name(name), _rectangle(0, 0, width, height), eventListenerQueue(new EventListenerQueueImpl()), layerQueue(new LayerQueueImpl()) {
        SDL_Window *w = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _rectangle.width, _rectangle.height, SDL_WINDOW_SHOWN);
        
        if (w == nullptr) {
            Log::get() << "Could not initialize window: \"" << name << "\": " << SDL_GetError() << "." << LogLevel::error;
            return;
        }
        
        window.reset(w, [](SDL_Window *w) {
            SDL_DestroyWindow(w);
        });
        
        SDL_Renderer *r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
        
        if (r == nullptr) {
            Log::get() << "Could not initialize renderer for window: \"" << name << "\": " << SDL_GetError() << "." << LogLevel::error;
            return;
        }
        
        _renderer.reset(r, [](SDL_Renderer *r) {
            SDL_DestroyRenderer(r);
        });
    }
    
    Screen::~Screen() {
        
    }
    
    void Screen::draw() {
        for (auto layer : layers) {
            if (layer->shouldDraw()) {
                layer->draw();
            }
        }
    }
    
    void Screen::listenEvent(SDL_Event event) {
        for (auto eventListener : eventListeners) {
            if (eventListener->isEnabled()) {
                eventListener->listenEvent(event);
            }
        }
    }
    
    void Screen::update() {
        for (auto layer : layers) {
            if (layer->shouldUpdate()) {
                layer->update();
            }
        }
    }
    
    string Screen::name() const {
        return _name;
    }
    
    int Screen::width() const {
        return _rectangle.width;
    }
    
    int Screen::height() const {
        return _rectangle.height;
    }
    
    Rectangle Screen::rectangle() const {
        return _rectangle;
    }
    
    void Screen::setName(string name) {
        if (name != _name) {
            string prev = _name;
            _name = name;
            
            if (window) {
                SDL_SetWindowTitle(window.get(), name.c_str());
            }
            
            nameChanged(prev);
        }
    }
    
    void Screen::setWidth(int width) {
        if (width != _rectangle.width) {
            auto prev = _rectangle;
            _rectangle.width = width;
            
            refreshSize(prev);
        }
    }
    
    void Screen::setHeight(int height) {
        if (height != _rectangle.height) {
            auto prev = _rectangle;
            _rectangle.height = height;
            
            refreshSize(prev);
        }
    }
    
    void Screen::setSize(int width, int height) {
        if (width != _rectangle.width || height != _rectangle.height) {
            auto prev = _rectangle;
            _rectangle.width = width;
            _rectangle.height = height;
            
            refreshSize(prev);
        }
    }
    
    shared_ptr<SDL_Renderer> Screen::renderer() const {
        return _renderer;
    }
    
    shared_ptr<EventListenerQueue> Screen::getEventListenerQueue() const {
        return eventListenerQueue;
    }
    
    shared_ptr<LayerQueue> Screen::getLayerQueue() const {
        return layerQueue;
    }
    
    void Screen::refreshScreen() {
        eventListeners.remove_if([] (shared_ptr<EventListener> eventListener) {
            return eventListener->isFinished();
        });
        
        auto newEventListener = eventListenerQueue->getNewEventListener();
        while (newEventListener) {
            eventListeners.push_back(newEventListener);
            
            newEventListener = eventListenerQueue->getNewEventListener();
        }
        
        layers.remove_if([] (shared_ptr<Layer> layer) {
            return layer->isZombie();
        });
        
        auto newLayer = layerQueue->getNewLayer();
        while (newLayer) {
            layers.push_back(newLayer);
            newLayer->screenSizeChanged(Rectangle(), rectangle());
            
            newLayer = layerQueue->getNewLayer();
        }
    }
    
    void Screen::clearEventListeners() {
        eventListeners.clear();
    }
    
    void Screen::clearLayers() {
        layers.clear();
    }
    
    void Screen::nameChanged(string prevName) {
        
    }
    
    void Screen::sizeChanged(Rectangle previousSize) {
        for (auto layer : layers) {
            layer->screenSizeChanged(previousSize, rectangle());
        }
    }
    
    void Screen::refreshSize(Rectangle previousSize) {
        if (window) {
            SDL_SetWindowSize(window.get(), _rectangle.width, _rectangle.height);
        }
        
        sizeChanged(previousSize);
    }
}
