//
//  MenuBar.cpp
//  Bomberman
//
//  Created on 27/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#include "MenuBar.hpp"

#include "MenuBarEntry.hpp"

namespace Bomberman {
    const Color menuBarColor = Color(0xA0);
    const Color menuItemColor = Color(0x70);
    const Color menuBarSelectedColor = Color(0x40);
    
    void MenuBar::draw() {
        background.setColor(menuBarColor);
        background.rectangle() = menuBarRectangle;
        background.draw();
        
        for (auto& menuBarEntry : menuBarEntries) {
            menuBarEntry.draw();
        }
    }
    
    void MenuBar::click(Coordinate position) {
        menuClicked = false;
        
        for (auto& menuBarEntry : menuBarEntries) {
            if (menuBarEntry.click(position)) {
                menuClicked = true;
            }
            menuBarEntry.show();
        }
    }
    
    void MenuBar::mouseOver(Coordinate position) {
        if (!menuClicked) {
            return;
        }
        
        for (auto& menuBarEntry : menuBarEntries) {
            menuBarEntry.mouseOver(position);
            menuBarEntry.show();
        }
    }
    
    void MenuBar::setBackground(Texture background) {
        this->background = background;
    }
    
    void MenuBar::setWidth(int width) {
        menuBarRectangle.width = width;
    }
    
    void MenuBar::setHeight(int height) {
        menuBarRectangle.height = height;
    }
    
    void MenuBar::addEntry(MenuBarItem menuBarItem) {
        Coordinate position;
        
        for (auto& menuBarEntries : menuBarEntries) {
            position.i += menuBarEntries.width();
        }
        
        menuBarItem.setPosition(position);
        menuBarItem.show();
        
        menuBarEntries.push_back(menuBarItem);
    }
    
    void MenuBar::hideAllSubMenus() {
        for (auto& menuBarEntry : menuBarEntries) {
            menuBarEntry.hideSubMenu();
        }
    }
    
    void MenuBar::unselectAll() {
        for (auto& menuBarEntry : menuBarEntries) {
            menuBarEntry.unselect();
        }
    }
}
