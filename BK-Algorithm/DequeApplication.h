#pragma once
#include <algorithm>
#include <iostream>

#include "LinkedDeque.h"
#include "MazeManager.h"

using namespace std;

namespace algorithm
{
	class DequeApplication
	{
	public:
		template<typename unsigned int HEIGHT, unsigned int WIDTH>
		static void DFS_ExploreMaze(const char maze[][WIDTH]);

		template<typename unsigned int HEIGHT, unsigned int WIDTH>
		static void BFS_ExploreMaze(const char maze[][WIDTH]);
	};

	template<typename unsigned int HEIGHT, unsigned int WIDTH>
	inline void DequeApplication::DFS_ExploreMaze(const char maze[][WIDTH])
	{
		char copiedMaze[HEIGHT][WIDTH];
		memcpy_s(copiedMaze, sizeof(char) * HEIGHT * WIDTH, maze, sizeof(char) * HEIGHT * WIDTH);
		bkDS::LinkedDeque<Location2D> deque;

		Location2D entry = MazeManager::FindEntry<HEIGHT, WIDTH>(copiedMaze);

		if (entry == Location2D(-1, -1))
		{
			cout << "���� : �Ա��� ã�µ� ���� �߽��ϴ�." << endl;
			return;
		}

		deque.PushBack(entry);

		while (!deque.IsEmpty())
		{
			Location2D currentLoc = deque.Front();
			deque.PopFront();

			MazeManager::PrintMap<HEIGHT, WIDTH>(copiedMaze, currentLoc);
			cout << '(' << currentLoc.row << ", " << currentLoc.col << ") " << endl << endl;

			if (copiedMaze[currentLoc.row][currentLoc.col] == 'x')
			{
				cout << endl << "�ⱸ �߰�!" << endl;
				return;
			}

			copiedMaze[currentLoc.row][currentLoc.col] = '.';

			if (MazeManager::IsValidLoc<HEIGHT, WIDTH>(currentLoc.row + 1, currentLoc.col, copiedMaze))
			{
				deque.PushFront(Location2D(currentLoc.row + 1, currentLoc.col));
			}

			if (MazeManager::IsValidLoc<HEIGHT, WIDTH>(currentLoc.row - 1, currentLoc.col, copiedMaze))
			{
				deque.PushFront(Location2D(currentLoc.row - 1, currentLoc.col));
			}

			if (MazeManager::IsValidLoc<HEIGHT, WIDTH>(currentLoc.row, currentLoc.col + 1, copiedMaze))
			{
				deque.PushFront(Location2D(currentLoc.row, currentLoc.col + 1));
			}

			if (MazeManager::IsValidLoc<HEIGHT, WIDTH>(currentLoc.row, currentLoc.col - 1, copiedMaze))
			{
				deque.PushFront(Location2D(currentLoc.row, currentLoc.col - 1));
			}
		}

		cout << "���� : �ⱸ�� �߰��ϴµ� �����߽��ϴ�." << endl;
	}

	template<typename unsigned int HEIGHT, unsigned int WIDTH>
	inline void DequeApplication::BFS_ExploreMaze(const char maze[][WIDTH])
	{
		char copiedMaze[HEIGHT][WIDTH];
		memcpy_s(copiedMaze, sizeof(char) * HEIGHT * WIDTH, maze, sizeof(char) * HEIGHT * WIDTH);
		bkDS::LinkedDeque<Location2D> deque;

		Location2D entry = MazeManager::FindEntry<HEIGHT, WIDTH>(copiedMaze);

		if (entry == Location2D(-1, -1))
		{
			cout << "���� : �Ա��� ã�µ� ���� �߽��ϴ�." << endl;
			return;
		}

		deque.PushBack(entry);

		while (!deque.IsEmpty())
		{
			Location2D currentLoc = deque.Front();
			deque.PopFront();

			MazeManager::PrintMap<HEIGHT, WIDTH>(copiedMaze, currentLoc);
			cout << '(' << currentLoc.row << ", " << currentLoc.col << ") " << endl << endl;

			if (copiedMaze[currentLoc.row][currentLoc.col] == 'x')
			{
				cout << endl << "�ⱸ �߰�!" << endl;
				return;
			}

			copiedMaze[currentLoc.row][currentLoc.col] = '.';

			if (MazeManager::IsValidLoc<HEIGHT, WIDTH>(currentLoc.row + 1, currentLoc.col, copiedMaze))
			{
				deque.PushBack(Location2D(currentLoc.row + 1, currentLoc.col));
			}

			if (MazeManager::IsValidLoc<HEIGHT, WIDTH>(currentLoc.row - 1, currentLoc.col, copiedMaze))
			{
				deque.PushBack(Location2D(currentLoc.row - 1, currentLoc.col));
			}

			if (MazeManager::IsValidLoc<HEIGHT, WIDTH>(currentLoc.row, currentLoc.col + 1, copiedMaze))
			{
				deque.PushBack(Location2D(currentLoc.row, currentLoc.col + 1));
			}

			if (MazeManager::IsValidLoc<HEIGHT, WIDTH>(currentLoc.row, currentLoc.col - 1, copiedMaze))
			{
				deque.PushBack(Location2D(currentLoc.row, currentLoc.col - 1));
			}
		}

		cout << "���� : �ⱸ�� �߰��ϴµ� �����߽��ϴ�." << endl;
	}
}