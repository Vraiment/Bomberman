//
//  Configuration.cpp
//  Bomberman
//
//  Created on 31/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Configuration.hpp"

#include <tinyxml2/tinyxml2.h>

#include "Log.hpp"

using namespace std;
using namespace tinyxml2;

namespace Bomberman {
	Configuration::Configuration() : _loaded(false) {
		defaults();
	}
	
	Configuration::Configuration(string fileName) : _loaded(false) {
		load(fileName);
	}
	
	bool Configuration::load(string fileName) {
		XMLDocument file;
		bool result = false;
		
		if (_loaded) {
			Log::get() << "Overwritting configuration file \"" << _fileName << "\"." << LogLevel::warning;
		}
		
		if (file.LoadFile(fileName.c_str()) == XML_NO_ERROR) {
			XMLElement *root = file.RootElement();
			
			loadViewport(root->FirstChildElement("viewport"));
			loadLoggers(root->FirstChildElement("loggers"));
			
			Log::get() << "Using configuration file \"" << fileName << "\"." << LogLevel::info;
			
			result = true;
			
			_fileName = fileName;
		} else {
			Log::get() << "Configuration file \"" << fileName << "\" not found, using defaults." << LogLevel::warning;
			
			defaults();
		}
		
		_loaded = true;
		
		return result;
	}
	
	bool Configuration::loaded() const {
		return _loaded;
	}
	
	string Configuration::viewportTitle() const {
		if (!loaded()) {
			Log::get() << "Using unloaded configuration!" << LogLevel::fatal;
		}
		
		return _viewportTitle;
	}
	
	int Configuration::viewportWidth() const {
		if (!loaded()) {
			Log::get() << "Using unloaded configuration!" << LogLevel::fatal;
		}
		
		return _viewportWidth;
	}
	
	int Configuration::viewportHeight() const {
		if (!loaded()) {
			Log::get() << "Using unloaded configuration!" << LogLevel::fatal;
		}
		
		return _viewportHeight;
	}
	
	std::vector<std::string> Configuration::loggers() const {
		if (!loaded()) {
			Log::get() << "Using unloaded configuration!" << LogLevel::fatal;
		}
		
		return _loggers;
	}
	
	void Configuration::defaults() {
		_fileName = ":no_file:";
		
		loadViewport(nullptr);
		loadLoggers(nullptr);
	}
	
	void Configuration::loadViewport(void *ptr) {
		XMLElement *node = (XMLElement *)ptr;
		
		if (node != nullptr) {
			XMLElement *viewportTitle = node->FirstChildElement("title");
			if (viewportTitle != nullptr) {
				_viewportTitle = viewportTitle->GetText();
			} else {
				Log::get() << "No title for viewport in configuration file." << LogLevel::info;
			}
			
			XMLElement *viewportWidth = node->FirstChildElement("width");
			if (viewportWidth != nullptr) {
				string value = viewportWidth->GetText();
				
				try {
					_viewportWidth = stoi(value);
				} catch (...) {
					_viewportWidth = 0;
				}
			} else {
				Log::get() << "No width for viewport in configuration file, using default." << LogLevel::info;
			}
			
			XMLElement *viewportHeight = node->FirstChildElement("height");
			if (viewportHeight != nullptr) {
				string value = viewportHeight->GetText();
				
				try {
					_viewportHeight = stoi(value);
				} catch (...) {
					_viewportHeight = 0;
				}
			} else {
				Log::get() << "No height for viewport in configuration file, using default." << LogLevel::info;
			}
		} else {
			_viewportWidth = 600;
			_viewportHeight = 460;
			
			return;
		}
		
		if (_viewportWidth < 1) {
			Log::get() << "Invalid value for viewport width in configuration file, using default." << LogLevel::warning;
			
			_viewportWidth = 600;
		}
		
		if (_viewportHeight < 1) {
			Log::get() << "Invalid value for viewport height in configuration file, using default." << LogLevel::warning;
			
			_viewportWidth = 460;
		}
	}
	
	void Configuration::loadLoggers(void *ptr) {
		XMLElement *node = (XMLElement *)ptr;
		
		if (node == nullptr) return;
		
		for (XMLElement *logger = node->FirstChildElement("logger"); logger != nullptr; logger = logger->FirstChildElement("logger")) {
			_loggers.push_back(logger->GetText());
		}
	}
}
