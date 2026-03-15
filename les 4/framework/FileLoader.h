#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include <glm/glm.hpp>

#include "Face.h"
#include "Object.h"
#include "Bezier.h"

class FileLoader
{
public:
	FileLoader() = default;;
	static std::vector<std::string> SplitString(const std::string& string, char delim = ' ');
	static std::map<int, Object> LoadObjects(const std::string& filename);
	static std::map<int, Bezier> LoadCurves(const std::string& filename);
};

