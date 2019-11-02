#include <iostream>
using namespace std;
int main(){
	int lines;
	cout << "Triangle pattern by Zaeem Yousaf\n";
	cout << "Enter number of lines: ";
	cin >> lines;
	cout << "-------Fig a -------------\n";
		for(int line=0; line< lines; line++){
		for(int astrik=0; astrik <= line; astrik++) cout << "*";
		cout << endl;
	}
	cout << "--------Fig b-------------\n";
	for(int line=1; line<= lines; line++){
		for(int space=0; space < lines -line; space++) cout << " ";
		for(int astrik=1; astrik <= line; astrik++) cout << "*";
		cout << endl;
	}
	cout << "--------Fig c-------------\n";
		for(int line=0; line< lines; line++){
		for(int astrik=0; astrik < (lines -line); astrik++) cout << "*";
		cout << endl;
	}

	cout << "--------Fig d-------------\n";
		for(int line=0; line<= lines; line++){
		for(int space=0; space < line ; space++) cout << " ";
		for(int astrik=0; astrik < lines-(line); astrik++) cout << "*";
		cout << endl;
	}
	cout << "--------Fig e-------------\n";
		for(int line=0; line< lines; line++){
		for(int space=(lines-1); space >= (line+1) ; space--) cout << " ";
		for(int astrik=0; astrik < 2*(line+1)-1; astrik++) cout << "*";
		cout << endl;
	}
}