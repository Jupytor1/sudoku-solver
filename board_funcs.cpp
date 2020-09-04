#include "header.h"

void board::init() {
	int i, j, k;

	for (i = 0; i < 9; i++) for (j = 0; j < 9; j++) {
		u[i][j] = 9;
	}

	for (i = 0; i < 3; i++) for (j = 0; j < 3; j++) {
		for (k = 1; k <= 9; k++) block[i][j][k] = 9;
	}

	for (i = 0; i < 9; i++) {
		for (k = 1; k <= 9; k++) row[i][k] = column[i][k] = 9;
	}

	for (i = 0; i < 9; i++) for (j = 0; j < 9; j++) {
		for (k = 1; k <= 9; k++) can[i][j][k] = true;
	}
}

void board::fill(int i, int j, int w) {
	int ii, jj, a, b;
	h[i][j] = w;
	a = i - i % 3;
	b = j - j % 3;

	//cout << i << ' ' << j << " -> " << w << endl;

	u[i][j] = 0;
	block[i / 3][j / 3][w] = 0;
	row[i][w] = 0;
	column[j][w] = 0;

	for (ii = 1; ii <= 9; ii++) {
		if (ii != w && can[i][j][ii]) {
			deny(i, j, ii);
		}
	}

	for (ii = 0; ii < 3; ii++) for (jj = 0; jj < 3; jj++) {
		if (h[a + ii][b + jj] == 0 && can[a + ii][b + jj][w]) {
			deny(a + ii, b + jj, w);
		}
	}

	for (ii = 0; ii < 9; ii++) {
		if (h[ii][j] == 0 && can[ii][j][w]) {
			deny(ii, j, w);
		}
	}

	for (jj = 0; jj < 9; jj++) {
		if (h[i][jj] == 0 && can[i][jj][w]) {
			deny(i, jj, w);
		}
	}
}

void board::deny(int i, int j, int w) {
	can[i][j][w] = false;
	u[i][j]--;
	block[i / 3][j / 3][w]--;
	row[i][w]--;
	column[j][w]--;
}

bool board::all_search() {
	int i, j, t;
	bool res = false;
	for (i = 0; i < 9; i++) for (j = 0; j < 9; j++) {
		if (h[i][j] == 0 && u[i][j] == 1) {
			res = true;
			t = 1;
			while (!can[i][j][t]) t++;
			fill(i, j, t);
		}
	}
	return res;
}

bool board::block_search() {
	int bi, bj, i, ii, jj, x, y;
	bool res = false;
	for (bi = 0; bi < 3; bi++) for (bj = 0; bj < 3; bj++) {
		for (i = 1; i <= 9; i++) {
			if (block[bi][bj][i] == 1) {
				res = true;
				for (ii = 0; ii < 3; ii++) for (jj = 0; jj < 3; jj++) {
					if (can[bi * 3 + ii][bj * 3 + jj][i]) {
						x = bi * 3 + ii;
						y = bj * 3 + jj;
					}
				}
				fill(x, y, i);
			}
		}
	}
	return res;
}

bool board::row_search() {
	int r, i, jj;
	bool res = false;
	for (r = 0; r < 9; r++) {
		for (i = 1; i <= 9; i++) {
			if (row[r][i] == 1) {
				res = true;
				for (jj = 0; jj < 9; jj++) {
					if (can[r][jj][i]) break;
				}
				fill(r, jj, i);
			}
		}
	}
	return res;
}

bool board::column_search() {
	int c, i, ii;
	bool res = false;
	for (c = 0; c < 9; c++) {
		for (i = 1; i <= 9; i++) {
			if (column[c][i] == 1) {
				res = true;
				for (ii = 0; ii < 9; ii++) {
					if (can[ii][c][i]) break;
				}
				fill(ii, c, i);
			}
		}
	}
	return res;
}

void board::assume() {
	int i, j, hi, hj, ymin = 10, w;
	bool con;

	board as;

	for (i = 0; i < 9; i++) for (j = 0; j < 9; j++) {
		if (h[i][j] == 0 && ymin > u[i][j]) {
			ymin = u[i][j];
			hi = i;
			hj = j;
		}
	}

	w = 1;

	while (1) {

		while (w <= 9 && !can[hi][hj][w]) w++;

		if (w == 10) return;

		as = *this;

		//cout << "as ";
		as.fill(hi, hj, w);

		con = true;
		while (con) {
			con = as.all_search() || as.block_search() || as.row_search() || as.column_search();
		}

		if (!as.wrong() && !as.end()) {
			as.assume();
		}

		if (as.end()) {
			*this = as;
			return;
		}
		else {
			deny(hi, hj, w);
		}

	}

}

bool board::wrong() {
	int i, j;

	for (i = 0; i < 9; i++) for (j = 0; j < 9; j++) {
		if (h[i][j] == 0 && u[i][j] == 0) return true;
	}

	return false;
}

bool board::end() {
	int i, j;

	for (i = 0; i < 9; i++) for (j = 0; j < 9; j++) {
		if (h[i][j] == 0) return false;
	}

	return true;
}

void board::output() {
	int i, j;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			cout << h[i][j];
			if (j == 2 || j == 5) cout << '|';
			else cout << ' ';
		}
		cout << endl;
		if (i == 2 || i == 5) cout << "-----+-----+-----" << endl;
	}
}