//
//  MapEditor.cpp
//  Bomberman
//
//  Created on 21/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#include "MapEditor.hpp"

#include <functional>
#include <SDL2/SDL.h>
#include <string>

#include "../../Core/Font.hpp"
#include "../../Core/Log/LogSystem.h"
#include "../../Core/Texture.hpp"
#include "../../Core/SignalSender.hpp"
#include "../../Core/Utils/PointerUtils.hpp"

#include "../Signal.hpp"

using namespace std;

namespace Bomberman {
    const int fontSize = 20;
    
    const int leftMargin = 5;
    const int rightMargin = 15;
    const int verticalMargin = leftMargin + rightMargin;
    
    const int topMargin = 5;
    const int bottomMargin = 5;
    const int horizontalMargin = topMargin + bottomMargin;
    
    const Color menuBarColor = Color(0xA0);
    const Color menuItemColor = Color(0x70);
    const Color menuBarSelectedColor = Color(0x40);
    
    class MapEditor::MenuBarItem {
    public:
        MenuBarItem(Texture texture, Texture bg) : MenuBarItem(texture, bg, menuItemColor) {
            
        }
        
        MenuBarItem(Texture texture, Texture bg, Color normalColor) : texture(texture), bg(bg), visible(false), normalColor(normalColor) {
            
        }
        
        virtual ~MenuBarItem() {
            
        }
        
        void setPosition(Coordinate position) {
            bgRect.i = position.i;
            bgRect.j = position.j;
            bgRect.width = texture.rectangle().width + verticalMargin;
            bgRect.height = texture.rectangle().height + horizontalMargin;
            
            texture.position().i = position.i + leftMargin;
            texture.position().j = position.j + topMargin;
        }
        
        void draw() {
            if (!visible) {
                return;
            }
            
            if (selected) {
                for (auto subMenuItem : subMenu) {
                    subMenuItem.draw();
                }
                
                bg.setColor(menuBarSelectedColor);
            } else {
                bg.setColor(normalColor);
            }
            
            bg.rectangle() = bgRect;
            bg.draw();
            
            texture.draw();
        }
        
        void show(bool showSubMenu = false) {
            visible = true;
            
            if (showSubMenu) {
                for (auto& subMenuEntry : subMenu) {
                    subMenuEntry.visible = true;
                }
            }
        }
        
        void hide() {
            visible = false;
            
            hideChildren();
        }
        
        void hideChildren() {
            for (auto& subMenuEntry : subMenu) {
                subMenuEntry.hide();
            }
        }
        
        bool select(Coordinate position) {
            selected = false;
            
            for (auto& subMenuItem : subMenu) {
                selected |= subMenuItem.select(position);
            }
            
            selected |= bgRect.contains(position);
            
            return selected;
        }
        
        bool click(Coordinate position) {
            if (!visible) {
                return false;
            }
            
            bool result = bgRect.contains(position);
            
            if (result) {
                if (callback) {
                    callback(this);
                }
            } else {
                for (auto& subMenuItem : subMenu) {
                    result = subMenuItem.click(position);
                    if (result) {
                        break;
                    }
                }
            }
            
            return result;
        }
        
        void setWidth(int width) {
            bgRect.width = width;
        }
        
        int width() {
            return bgRect.width;
        }
        
        void setCallback(function<void(MenuBarItem *)> callback) {
            this->callback = callback;
        }
        
        bool isSelected() const {
            return visible;
        }
        
        void addDownSubMenuItem(MenuBarItem subMenuItem) {
            int maxWidth = subMenuItem.texture.rectangle().width + verticalMargin;
            int j = bgRect.bottom();
            for (auto subMenuItem : subMenu) {
                int width = subMenuItem.width();
                if (width > maxWidth) {
                    maxWidth = width;
                }
                
                j = subMenuItem.bgRect.bottom();
            }
            
            subMenuItem.setPosition(Coordinate(bgRect.i, j));
            subMenu.push_back(subMenuItem);
            
            for (auto& subMenuItem : subMenu) {
                subMenuItem.setWidth(maxWidth);
            }
        }
        
    private:
        Color normalColor;
        bool selected, visible;
        Rectangle bgRect;
        Texture texture, bg;
        
        vector<MenuBarItem> subMenu;
        function<void(MenuBarItem *)> callback;
    };
    
    template <typename T>
    bool _lock(weak_ptr<T> in, shared_ptr<T>& out, string component) {
        bool result = lockWeakPointer(in, out);
        
        if (!result) {
            Log::get() << "No " << component << " for MapEditor" << LogLevel::error;
        }
        
        return result;
    }
    
    MapEditor::MapEditor() : clicked(false), menuClicked(false) {
        
    }
    
    MapEditor::~MapEditor() {
        
    }
    
    void MapEditor::draw() {
        background.setColor(menuBarColor);
        background.rectangle() = menuBarRect;
        background.draw();
        
        for (auto menuBarItem : menuBar) {
            menuBarItem->draw();
        }
    }
    
    void MapEditor::listenEvent(SDL_Event event) {
        shared_ptr<SignalSender> signalSender;
        if (SDL_KEYUP == event.type && _lock(this->signalSender, signalSender, "SignalSender")) {
            auto keysym = event.key.keysym.sym;
            
            if (SDLK_ESCAPE == keysym) {
                signalSender->sendSignal(Signal::MainMenu);
            }
        } else if (SDL_MOUSEBUTTONUP == event.type && event.button.button == SDL_BUTTON_LEFT) {
            clicked = true;
            mousePos.i = event.button.x;
            mousePos.j = event.button.y;
        } else if (SDL_MOUSEMOTION == event.type) {
            mousePos.i = event.motion.x;
            mousePos.j = event.motion.y;
        }
    }
    
    void MapEditor::update() {
        if (clicked) {
            menuClicked = false;
            
            for (auto menuBarEntry : menuBar) {
                menuClicked = menuBarEntry->click(mousePos);
                
                if (menuClicked) {
                    break;
                }
            }
            
            clicked = false;
        }
        
        if (menuClicked) {
            for (auto menuBarEntry : menuBar) {
                menuBarEntry->select(mousePos);
            }
        }
    }
    
    void MapEditor::handleSignal(Signal signal) {
        if (Signal::MapEditor == signal) {
            Drawable::enable();
            EventListener::enable();
            Updatable::enable();
        } else {
            Drawable::disable();
            EventListener::disable();
            Updatable::enable();
        }
    }
    
    void MapEditor::load(shared_ptr<SDL_Renderer> renderer) {
        Font font("PressStart2P.ttf", fontSize, renderer);
        
        menuBarRect.height = font.maxHeight() + horizontalMargin;
        
        background = Texture::createRectangle(1, 1, Color::WHITE, renderer);
        
        Coordinate position = Coordinate::ZERO;
        shared_ptr<MenuBarItem> menuBarItem;
        
        // File menu
        menuBarItem = make_shared<MenuBarItem>(font.write("File"), background, menuBarColor);
        menuBarItem->setPosition(position);
        menuBarItem->show();
        menuBarItem->setCallback([] (MenuBarItem *self) {
            self->show(true);
        });
        menuBarItem->addDownSubMenuItem(MenuBarItem(font.write("New Map"), background));
        menuBarItem->addDownSubMenuItem(MenuBarItem(font.write("Load Map"), background));
        menuBarItem->addDownSubMenuItem(MenuBarItem(font.write("Save Map"), background));
        menuBarItem->addDownSubMenuItem(MenuBarItem(font.write("Save Map As..."), background));
        menuBarItem->addDownSubMenuItem(MenuBarItem(font.write("Exit Map Editor"), background));
        menuBarItem->addDownSubMenuItem(MenuBarItem(font.write("Exit Bomberman"), background));
        this->menuBar.push_back(menuBarItem);
    }
    
    void MapEditor::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
        menuBarRect.width = newSize.width;
    }
    
    void MapEditor::setSignalSender(weak_ptr<SignalSender> signalSender) {
        this->signalSender = signalSender;
    }
}
