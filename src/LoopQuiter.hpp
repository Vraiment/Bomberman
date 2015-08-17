//
//  LoopQuiter.hpp
//  Bomberman
//
//  Created on 17/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __LoopQuiter__hpp__
#define __LoopQuiter__hpp__

namespace Bomberman {
	class LoopQuiter {
	public:
		LoopQuiter();
		~LoopQuiter();
		
		bool shouldQuit() const;
		
		void quitLoop();
		
	private:
		bool _quitLoop;
	};
}

#endif //__LoopQuiter__hpp__
