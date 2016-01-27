//
//  MenuBarEntry.cpp
//  Bomberman
//
//  Created on 27/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#include "MenuBarEntry.hpp"

using namespace std;

namespace Bomberman {
    const int leftMargin = 5;
    const int rightMargin = 15;
    const int verticalMargin = leftMargin + rightMargin;
    
    const int topMargin = 5;
    const int bottomMargin = 5;
    const int horizontalMargin = topMargin + bottomMargin;
    
    const Color menuBarColor = Color(0xA0);
    const Color menuItemColor = Color(0x70);
    const Color menuBarSelectedColor = Color(0x40);
    
    MenuBarItem::MenuBarItem(Texture texture, Texture bg) : MenuBarItem(texture, bg, menuItemColor) {
        
    }
    
    MenuBarItem::MenuBarItem(Texture texture, Texture bg, Color normalColor) : texture(texture), bg(bg), visible(false), normalColor(normalColor), selected(false) {
        this->texture.position() = Coordinate(leftMargin, topMargin);
        
        this->bgRect.width = this->texture.rectangle().width + verticalMargin;
        this->bgRect.height = this->texture.rectangle().height + horizontalMargin;
    }
    
    MenuBarItem::~MenuBarItem() {
        
    }
    
    void MenuBarItem::setPosition(Coordinate position) {
        Coordinate delta = position - bgRect;
        
        bgRect += delta;
        texture.position() += delta;
        
        alignChildren(delta);
    }
    
    void MenuBarItem::draw() {
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
    
    void MenuBarItem::show() {
        visible = true;
    }
    
    void MenuBarItem::showSubMenu() {
        for (auto& subMenuEntry : subMenu) {
            subMenuEntry.visible = true;
        }
    }
    
    void MenuBarItem::hide() {
        visible = false;
        
        hideSubMenu();
    }
    
    void MenuBarItem::hideSubMenu() {
        for (auto& subMenuEntry : subMenu) {
            subMenuEntry.hide();
        }
    }
    
    void MenuBarItem::select() {
        selected = true;
    }
    
    void MenuBarItem::unselect() {
        selected = false;
        
        for (auto& subMenuEntry : subMenu) {
            subMenuEntry.unselect();
        }
    }
    
    bool MenuBarItem::click(Coordinate position) {
        return mouseAction(position, true);
    }
    
    void MenuBarItem::setWidth(int width) {
        bgRect.width = width;
    }
    
    int MenuBarItem::width() const {
        return bgRect.width;
    }
    
    void MenuBarItem::setOnClick(OnClickCallback callback) {
        onClick = callback;
    }
    
    bool MenuBarItem::isSelected() const {
        return selected;
    }
    
    void MenuBarItem::addDownSubMenuItem(MenuBarItem subMenuItem) {
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
    
    void MenuBarItem::mouseOver(Coordinate position) {
        mouseAction(position, false);
    }
    
    bool MenuBarItem::mouseAction(Coordinate position, bool click){
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
    
    void MenuBarItem::alignChildren(Coordinate delta) {
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
}
