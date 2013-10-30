//
//  NotImplementedException.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __NotImplementedException__hpp__
#define __NotImplementedException__hpp__

#include <exception>

namespace Bomberman {
	class NotImplementedException : public std::exception {
	public:
		virtual const char* what() const noexcept;
	};
}

#endif //__NotImplementedException__hpp__
