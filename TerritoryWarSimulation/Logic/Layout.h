#pragma once
#include <vector>
#include <Core.h>
#include <fstream>
#include <sstream>
#include <string>

class Layout
{
public:
	int Controllers;
	float Width;
	float Height;
	std::vector<Core> Cores;

	Layout()
	{}

	Layout(int c, float w, float h, std::vector<Core> s = std::vector<Core>())
	{
		Controllers = c;
		Width = w;
		Height = h;
		Cores = s;
	}

	Layout(std::string s)
	{
		std::ifstream infile(s);
		std::string line;
		std::getline(infile, line);
		std::istringstream iss(line);
		iss >> Controllers >> Width >> Height;
		for(int i = 1; i <= Controllers; ++i)
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
			Cores.push_back(c);
		}
	}

private:
};

