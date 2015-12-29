//
//  Rectangle.hpp
//  Bomberman
//
//  Created on 12/3/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Rectangle__hpp__
#define __Rectangle__hpp__

#include "Coordinate.hpp"

namespace Bomberman {
    class Rectangle : public Coordinate {
    public:
        Rectangle();
        Rectangle(int i, int j, int width, int height);
        
        int width, height;
        
        int widthCenter() const;
        int heightCenter() const;
        int left() const;
        int right() const;
        int top() const;
        int bottom() const;
        
        Coordinate center() const;
        Coordinate leftTop() const;
        Coordinate rightTop() const;
        Coordinate rightBottom() const;
        Coordinate leftBottom() const;
        
        bool intersects(Rectangle other) const;
        bool contains(int i, int j) const;
        bool contains(Coordinate coordinate) const;
        
        bool operator==(Rectangle other) const;
        bool operator!=(Rectangle other) const;
        
        Rectangle& operator=(Coordinate other);
        
        std::string toString() const;
    };
}

#endif //__Rectangle__hpp__
