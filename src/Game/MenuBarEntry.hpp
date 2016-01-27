//
//  MenuBarEntry.hpp
//  Bomberman
//
//  Created on 27/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#ifndef __MenuBarEntry__hpp__
#define __MenuBarEntry__hpp__

#include "../Core/Color.hpp"
#include "../Core/Texture.hpp"

#include <functional>
#include <vector>

namespace Bomberman {
    class MenuBarItem {
    public:
        using OnClickCallback = std::function<void(MenuBarItem*)>;
        
        MenuBarItem(Texture texture, Texture bg);
        MenuBarItem(Texture texture, Texture bg, Color normalColor);
        
        virtual ~MenuBarItem();
        
        void setPosition(Coordinate position);
        
        void draw();
        
        void show();
        void showSubMenu();
        
        void hide();
        void hideSubMenu();
        
        void select();
        void unselect();
        
        bool click(Coordinate position);
        
        void setWidth(int width);
        
        int width() const;
        
        void setOnClick(OnClickCallback callback);
        
        bool isSelected() const;
        
        void addDownSubMenuItem(MenuBarItem subMenuItem);
        
        void mouseOver(Coordinate position);
        
    private:
        Color normalColor;
        bool selected, visible;
        Rectangle bgRect;
        Texture texture, bg;
        
        std::vector<MenuBarItem> subMenu;
        OnClickCallback onClick;
        
        bool mouseAction(Coordinate position, bool click);
        void alignChildren(Coordinate delta);
    };
}

#endif //__MenuBarEntry__hpp__
