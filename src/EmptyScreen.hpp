//
//  EmptyScreen.hpp
//  Bomberman
//
//  Created on 06/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __EmptyScreen__hpp__
#define __EmptyScreen__hpp__

#include "Screen.hpp"

namespace Bomberman {
	class EmptyScreen : public Screen {
	public:
		EmptyScreen(int width, int height);
		
		void draw();
	};
}

#endif //__EmptyScreen__hpp__
