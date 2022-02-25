#pragma once

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

class board {
	private:
		int h[10][10] = {}, u[10][10] = {}, block[4][4][10] = {}, row[10][10] = {}, column[10][10] = {};
		bool can[10][10][10] = {};


	public:
		void init();

		void fill(int i, int j, int w);
		void deny(int i, int j, int w);

		bool all_search();
		bool block_search();
		bool row_search();
		bool column_search();

		void assume();
		bool wrong();
		bool wrong_num(int i, int j, int w);
		bool end();

		void output();

};