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
#include "../../Core/LoopQuiter.hpp"
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
        
        void show() {
            visible = true;
        }
        
        void showSubMenu() {
            for (auto& subMenuEntry : subMenu) {
                subMenuEntry.visible = true;
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
            return mouseAction(position, true);
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
        
        void mouseOver(Coordinate position) {
            mouseAction(position, false);
        }
        
    private:
        Color normalColor;
        bool selected, visible;
        Rectangle bgRect;
        Texture texture, bg;
        
        vector<MenuBarItem> subMenu;
        function<void(MenuBarItem *)> onClick;
        
        bool mouseAction(Coordinate position, bool click) {
            if (!visible) {
                selected = false;
                return false;
            }
            
            selected = false;
            visible = false;
            
            for (auto& subMenuEntry : subMenu) {
                selected |= subMenuEntry.mouseAction(position, click);
            }
            
            if (bgRect.contains(position)) {
                selected = true;
                visible = true;
                if (click && onClick) {
                    onClick(this);
                }
            }
            
            if (selected) {
                showSubMenu();
            }
            
            return selected;
        }
        
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
            menuClicked = false;
            
            for (auto& menuBarEntry : menuBarEntries) {
                if (menuBarEntry.click(position)) {
                    menuClicked = true;
                }
                menuBarEntry.show();
            }
        }
        
        void mouseOver(Coordinate position) {
            if (!menuClicked) {
                return;
            }
            
            for (auto& menuBarEntry : menuBarEntries) {
                menuBarEntry.mouseOver(position);
                menuBarEntry.show();
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
        bool menuClicked = false;
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
        } else if (mouseMoved) {
            menuBar->mouseOver(mousePos);
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
        auto lq = this->loopQuiter;
        auto ss = this->signalSender;
        
        menuBar->setHeight(font.maxHeight() + horizontalMargin);
        menuBar->setBackground(background);
        
        // File menu
        MenuBarItem fileMenu(font.write("File"), background, menuBarColor);
        
        MenuBarItem newMap(font.write("New Map"), background);
        fileMenu.addDownSubMenuItem(newMap);
        
        MenuBarItem loadMap(font.write("Load Map"), background);
        fileMenu.addDownSubMenuItem(loadMap);
        
        MenuBarItem saveMap(font.write("Save Map"), background);
        fileMenu.addDownSubMenuItem(saveMap);
        
        MenuBarItem saveMapAs(font.write("Save Map As..."), background);
        fileMenu.addDownSubMenuItem(saveMapAs);
        
        MenuBarItem exitEditor(font.write("Exit Map Editor"), background);
        exitEditor.setOnClick([ss, menuBar] (MenuBarItem *self) {
            shared_ptr<SignalSender> signalSender;
            if (_lock(ss, signalSender, "SignalSender")) {
                signalSender->sendSignal(Signal::MainMenu);
            }
            
            menuBar->hideAllChildren();
            menuBar->unselectAll();
        });
        fileMenu.addDownSubMenuItem(exitEditor);
        
        MenuBarItem exitBomberman(font.write("Exit Bomberman"), background);
        exitBomberman.setOnClick([lq, menuBar] (MenuBarItem *self) {
            shared_ptr<LoopQuiter> loopQuiter;
            if (_lock(lq, loopQuiter, "LoopQuiter")) {
                loopQuiter->quitLoop();
            }
            
            menuBar->hideAllChildren();
            menuBar->unselectAll();
        });
        fileMenu.addDownSubMenuItem(exitBomberman);
        
        menuBar->addEntry(fileMenu);
        
        MenuBarItem elementsMenu(font.write("Elements"), background, menuBarColor);
        elementsMenu.addDownSubMenuItem(MenuBarItem(font.write("Brick*"), background));
        elementsMenu.addDownSubMenuItem(MenuBarItem(font.write("Player"), background));
        elementsMenu.addDownSubMenuItem(MenuBarItem(font.write("Enemy*"), background));
        elementsMenu.addDownSubMenuItem(MenuBarItem(font.write("Door"), background));
        menuBar->addEntry(elementsMenu);
        
        MenuBarItem itemsMenu(font.write("Items"), background, menuBarColor);
        itemsMenu.addDownSubMenuItem(MenuBarItem(font.write("Extra bomb"), background));
        itemsMenu.addDownSubMenuItem(MenuBarItem(font.write("Increase range"), background));
        itemsMenu.addDownSubMenuItem(MenuBarItem(font.write("Remote"), background));
        menuBar->addEntry(itemsMenu);
    }
    
    void MapEditor::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
        menuBar->setWidth(newSize.width);
    }
    
    void MapEditor::setLoopQuiter(weak_ptr<LoopQuiter> loopQuiter) {
        this->loopQuiter = loopQuiter;
    }
    
    void MapEditor::setSignalSender(weak_ptr<SignalSender> signalSender) {
        this->signalSender = signalSender;
    }
}
