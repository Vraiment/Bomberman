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
    const int menuFontSize = 20;
    
    const int leftMargin = 5;
    const int rightMargin = 15;
    const int verticalMargin = leftMargin + rightMargin;
    
    const int topMargin = 5;
    const int bottomMargin = 5;
    const int horizontalMargin = topMargin + bottomMargin;
    
    const Color menuBarColor = Color(0xA0);
    const Color menuItemColor = Color(0x70);
    const Color menuBarSelectedColor = Color(0x40);
    
    class MenuBarItem {
    public:
        MenuBarItem(Texture texture, Texture bg) : MenuBarItem(texture, bg, menuItemColor) {
            
        }
        
        MenuBarItem(Texture texture, Texture bg, Color normalColor) : texture(texture), bg(bg), visible(false), normalColor(normalColor), selected(false) {
            this->texture.position() = Coordinate(leftMargin, topMargin);
            
            this->bgRect.width = this->texture.rectangle().width + verticalMargin;
            this->bgRect.height = this->texture.rectangle().height + horizontalMargin;
        }
        
        virtual ~MenuBarItem() {
            
        }
        
        void setPosition(Coordinate position) {
            Coordinate delta = position - bgRect;
            
            bgRect += delta;
            texture.position() += delta;
            
            alignChildren(delta);
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
        
        void select() {
            selected = true;
        }
        
        void unselect() {
            selected = false;
            
            for (auto& subMenuEntry : subMenu) {
                subMenuEntry.unselect();
            }
        }
        
        bool click(Coordinate position) {
            if (!visible) {
                return false;
            }
            
            bool result = bgRect.contains(position);
            
            if (result) {
                if (onClick) {
                    onClick(this);
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
        
        void setOnClick(function<void(MenuBarItem *)> callback) {
            onClick = callback;
        }
        
        bool isSelected() const {
            return selected;
        }
        
        void addDownSubMenuItem(MenuBarItem subMenuItem) {
            int maxWidth = subMenuItem.texture.rectangle().width + verticalMargin;
            int j = bgRect.bottom() + 1;
            for (auto subMenuItem : subMenu) {
                int width = subMenuItem.width();
                if (width > maxWidth) {
                    maxWidth = width;
                }
                
                j = subMenuItem.bgRect.bottom() + 1;
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
        function<void(MenuBarItem *)> onClick;
        
        void alignChildren(Coordinate delta) {
            for (auto& subMenuItem : subMenu) {
                if (subMenuItem.bgRect.i == bgRect.i) {
                    // Child is aligned down
                    subMenuItem.bgRect.j += delta.j;
                    subMenuItem.texture.rectangle().j += delta.j;
                } else {
                    // Child is aligned rigth
                    subMenuItem.bgRect.i += delta.i;
                    subMenuItem.texture.rectangle().i += delta.i;
                }
                
                subMenuItem.alignChildren(delta);
            }
        }
    };
    
    class MapEditor::MenuBar {
    public:
        void draw() {
            background.setColor(menuBarColor);
            background.rectangle() = menuBarRectangle;
            background.draw();
            
            for (auto& menuBarEntry : menuBarEntries) {
                menuBarEntry.draw();
            }
        }
        
        void click(Coordinate position) {
            bool menuClicked = false;
            
            for (auto& menuBarEntry : menuBarEntries) {
                menuClicked = menuBarEntry.click(position);
                if (menuClicked) {
                    break;
                }
            }
            
            if (!menuClicked) {
                for (auto& menuBarEntry : menuBarEntries) {
                    menuBarEntry.unselect();
                    menuBarEntry.hideChildren();
                }
            }
        }
        
        void setBackground(Texture background) {
            this->background = background;
        }
        
        void setWidth(int width) {
            menuBarRectangle.width = width;
        }
        
        void setHeight(int height) {
            menuBarRectangle.height = height;
        }
        
        void addEntry(MenuBarItem menuBarItem) {
            Coordinate position;
            
            for (auto& menuBarEntries : menuBarEntries) {
                position.i += menuBarEntries.width();
            }
            
            menuBarItem.setPosition(position);
            menuBarItem.show();
            
            menuBarEntries.push_back(menuBarItem);
        }
        
        void hideAllChildren() {
            for (auto& menuBarEntry : menuBarEntries) {
                menuBarEntry.hideChildren();
            }
        }
        
        void unselectAll() {
            for (auto& menuBarEntry : menuBarEntries) {
                menuBarEntry.unselect();
            }
        }
        
    private:
        Rectangle menuBarRectangle;
        Texture background;
        vector<MenuBarItem> menuBarEntries;
    };
    
    template <typename T>
    bool _lock(weak_ptr<T> in, shared_ptr<T>& out, string component) {
        bool result = lockWeakPointer(in, out);
        
        if (!result) {
            Log::get() << "No " << component << " for MapEditor" << LogLevel::error;
        }
        
        return result;
    }
    
    MapEditor::MapEditor() : clicked(false), menuBar(make_shared<MenuBar>()) {
        
    }
    
    MapEditor::~MapEditor() {
        
    }
    
    void MapEditor::draw() {
        menuBar->draw();
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
            mouseMoved = true;
            mousePos.i = event.motion.x;
            mousePos.j = event.motion.y;
        }
    }
    
    void MapEditor::update() {
        if (clicked) {
            menuBar->click(mousePos);
        }
    }
    
    void MapEditor::postUpdate() {
        clicked = false;
        mouseMoved = false;
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
        Font font("PressStart2P.ttf", menuFontSize, renderer);
        auto background = Texture::createRectangle(1, 1, Color::WHITE, renderer);
        auto menuBar = this->menuBar;
        
        menuBar->setHeight(font.maxHeight() + horizontalMargin);
        menuBar->setBackground(background);
        
        function<void(MenuBarItem*)> onClickSubMenu = [menuBar] (MenuBarItem *self) {
            if (self->isSelected()) {
                self->hideChildren();
                self->unselect();
            } else {
                menuBar->hideAllChildren();
                menuBar->unselectAll();
                
                self->select();
                self->show(true);
            }
        };
        
        // File menu
        MenuBarItem fileMenu(font.write("File"), background, menuBarColor);
        fileMenu.setOnClick(onClickSubMenu);
        fileMenu.addDownSubMenuItem(MenuBarItem(font.write("New Map"), background));
        fileMenu.addDownSubMenuItem(MenuBarItem(font.write("Load Map"), background));
        fileMenu.addDownSubMenuItem(MenuBarItem(font.write("Save Map"), background));
        fileMenu.addDownSubMenuItem(MenuBarItem(font.write("Save Map As..."), background));
        fileMenu.addDownSubMenuItem(MenuBarItem(font.write("Exit Map Editor"), background));
        fileMenu.addDownSubMenuItem(MenuBarItem(font.write("Exit Bomberman"), background));
        menuBar->addEntry(fileMenu);
        
        MenuBarItem elementsMenu(font.write("Elements"), background, menuBarColor);
        elementsMenu.setOnClick(onClickSubMenu);
        elementsMenu.addDownSubMenuItem(MenuBarItem(font.write("Brick*"), background));
        elementsMenu.addDownSubMenuItem(MenuBarItem(font.write("Player"), background));
        elementsMenu.addDownSubMenuItem(MenuBarItem(font.write("Enemy*"), background));
        elementsMenu.addDownSubMenuItem(MenuBarItem(font.write("Door"), background));
        menuBar->addEntry(elementsMenu);
        
        MenuBarItem itemsMenu(font.write("Items"), background, menuBarColor);
        itemsMenu.setOnClick(onClickSubMenu);
        itemsMenu.addDownSubMenuItem(MenuBarItem(font.write("Extra bomb"), background));
        itemsMenu.addDownSubMenuItem(MenuBarItem(font.write("Increase range"), background));
        itemsMenu.addDownSubMenuItem(MenuBarItem(font.write("Remote"), background));
        menuBar->addEntry(itemsMenu);
    }
    
    void MapEditor::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
        menuBar->setWidth(newSize.width);
    }
    
    void MapEditor::setSignalSender(weak_ptr<SignalSender> signalSender) {
        this->signalSender = signalSender;
    }
}
