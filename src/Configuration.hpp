//
//  Configuration.hpp
//  Bomberman
//
//  Created on 31/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Configuration__hpp__
#define __Configuration__hpp__

#include <string>
#include <vector>

namespace Bomberman {
	class Configuration {
	public:
		Configuration();
		Configuration(std::string fileName);
		
		bool load(std::string fileName);
		bool loaded() const;
		
		std::string viewportTitle() const;
		
		int viewportWidth() const;
		int viewportHeight() const;
		
	private:
		void defaults();
		void loadViewport(void *);
		void loadLoggers(void *);
		
		bool _loaded;
		std::string _fileName;
		std::string _viewportTitle;
		int _viewportWidth;
		int _viewportHeight;
	};
}

#endif //__Configuration__hpp__
