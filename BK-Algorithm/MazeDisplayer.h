#pragma once
#include <iostream>

#include "Location2D.h"

using namespace std;

namespace algorithm
{
	class MazeDisplayer
	{
	public:
		template<typename unsigned int HEIGHT, unsigned int WIDTH>
		static void PrintMap(const char maze[][WIDTH], const Location2D currentLoc);
	};

	template<typename unsigned int HEIGHT, unsigned int WIDTH>
	inline void MazeDisplayer::PrintMap(const char maze[][WIDTH], const Location2D currentLoc)
	{
		for (unsigned int i = 0; i < HEIGHT; i++)
		{
			for (unsigned int j = 0; j < WIDTH; j++)
			{
				if (i == currentLoc.row && j == currentLoc.col)
				{
					cout << "��";
				}
				else
				{
					switch (maze[i][j])
					{
					case '1':
						cout << "��";
						break;
					case '0':
						cout << "��";
						break;
					case '.':
						cout << "��";
						break;
					case 'x':
						cout << "��";
						break;
					case 'e':
						cout << "��";
						break;
					default:
						break;
					}
				}
			}
			cout << endl;
		}
	}
	
}