//
//  Configuration.cpp
//  Bomberman
//
//  Created on 31/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Configuration.hpp"

#include "../tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

namespace Bomberman {
	Configuration::Configuration() : _loaded(false) {
		defaults();
	}
	
	Configuration::Configuration(string fileName) : _fileName(fileName), _loaded(false) {
		XMLDocument file;
		
		if (file.LoadFile(fileName.c_str()) == XML_NO_ERROR) {
			XMLElement *root = file.RootElement();
			
			loadViewport(root->FirstChildElement("viewport"));
			
			_loaded = true;
		} else {
			defaults();
		}
	}
	
	string Configuration::viewportTitle() const {
		return _viewportTitle;
	}
	
	int Configuration::viewportWidth() const {
		return _viewportWidth;
	}
	
	int Configuration::viewportHeight() const {
		return _viewportHeight;
	}
	
	void Configuration::defaults() {
		_fileName = ":no_file:";
		_viewportWidth = 600;
		_viewportHeight = 460;
	}
	
	void Configuration::loadViewport(void *ptr) {
		XMLElement *node = (XMLElement *)ptr;
		
		_viewportTitle = node->FirstChildElement("title")->GetText();
		_viewportWidth = stoi(node->FirstChildElement("width")->GetText());
		_viewportHeight = stoi(node->FirstChildElement("height")->GetText());
	}
}
