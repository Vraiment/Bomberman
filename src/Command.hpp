//
//  Command.hpp
//  Bomberman
//
//  Created on 09/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Command__hpp__
#define __Command__hpp__

namespace Bomberman {
	class Command {
	public:
		virtual ~Command();
		
		virtual void execute() = 0;
		
		bool finished() const;
		
	protected:
		bool _finished;
	};
}

#endif //__Command__hpp__
