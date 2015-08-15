//
//  Layer.hpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __Layer__hpp__
#define __Layer__hpp__

namespace Bomberman {
	class Layer {
	public:
		virtual ~Layer();
		
		virtual void update() = 0;
		virtual void draw() = 0;
		
		bool isZombie() const;
		
	protected:
		bool _isZombie;
	};
}

#endif //__Layer__hpp__
