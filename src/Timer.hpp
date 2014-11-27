//
//  Timer.hpp
//  Bomberman
//
//  Created on 26/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#ifndef __Timer_hpp__
#define __Timer_hpp__

namespace Bomberman {
	class Timer {
	public:
		Timer();

		void start();
		void pause();
		void stop();
		void clear();
		
		int getTime() const;
		bool isCounting() const;
		bool isPaused() const;
	private:
		bool counting, paused;
		int startTime, pausedTime, stopedTime;
	};
}

#endif // __Timer_hpp__
