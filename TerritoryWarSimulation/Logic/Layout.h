#pragma once
#include <vector>
#include <Core.h>
#include <fstream>
#include <sstream>
#include <string>

class Layout
{
private:

	int _controllers;
	float _width;
	float _height;
	std::vector<Core> _cores;

public:

	Layout()
	{}

	Layout(int c, float w, float h, std::vector<Core> s = std::vector<Core>())
	{
		_controllers = c;
		_width = w;
		_height = h;
		_cores = s;
	}

	Layout(std::string s)
	{
		std::ifstream infile(s);
		std::string line;
		std::getline(infile, line);
		std::istringstream iss(line);
		iss >> _controllers >> _width >> _height;
		for(int i = 1; i <= _controllers; ++i)
		{
			std::getline(infile, line);
			std::istringstream iss(line);
			std::string c1, c2, c3, c4;
			iss >> c1 >> c2 >> c3 >> c4;
			Core c = Core(i);
			c + Vector2(c1);
			c + Vector2(c2);
			c + Vector2(c3);
			c + Vector2(c4);
			c = Vector2(c1) + 10;
			_cores.push_back(c);
		}
	}

	int Controllers() const
	{
		return _controllers;
	}

	float Width() const
	{
		return _width;
	}

	float Height() const
	{
		return _height;
	}

	std::vector<Core> Cores() const
	{
		return _cores;
	}
};

