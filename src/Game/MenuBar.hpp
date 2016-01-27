//
//  MenuBar.hpp
//  Bomberman
//
//  Created on 27/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#ifndef __MenuBar__hpp__
#define __MenuBar__hpp__

#include "../Core/Math/Rectangle.hpp"
#include "../Core/Texture.hpp"

#include <vector>

namespace Bomberman {
    class MenuBarItem;
    
    class MenuBar {
    public:
        void draw();
        
        void click(Coordinate position);
        void mouseOver(Coordinate position);
        
        void setBackground(Texture background);
        void setWidth(int width);
        void setHeight(int height);
        
        void addEntry(MenuBarItem menuBarItem);
        void hideAllSubMenus();
        void unselectAll();
        
    private:
        bool menuClicked = false;
        Rectangle menuBarRectangle;
        Texture background;
        std::vector<MenuBarItem> menuBarEntries;
    };
}

#endif //__MenuBar__hpp__
