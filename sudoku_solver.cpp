#include "header.h"

int main(void) {
	int i, j;
	string in[9];
	board base;

	base.init();

	for (i = 0; i < 9; i++) cin >> in[i];

	for (i = 0; i < 9; i++) for (j = 0; j < 9; j++) {
		if (in[i][j] != '.'){
			if (base.wrong_num(i, j, in[i][j] - '0')){
				cout << "No Answer" << endl;
				return 0;
			}
			base.fill(i, j, in[i][j] - '0');
		}
	}

	//cout << endl;
	
	bool con = true;
	while (con) {
		con = base.all_search() || base.block_search() || base.row_search() || base.column_search();
	}
	
	if (!base.end()) {
		//base.output();
		//cout << endl;
		base.assume();
	}

	if (base.wrong()){
		cout << "No Answer" << endl;
	}else{
		base.output();
	}

	return 0;
}