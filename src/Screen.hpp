//
//  Screen.hpp
//  Bomberman
//
//  Created on 02/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Screen__hpp__
#define __Screen__hpp__

namespace Bomberman {
	class Screen {
	public:
		virtual ~Screen() { }
		
		virtual void draw(Renderer renderer) = 0;
	};
}

#endif //__Screen__hpp__
