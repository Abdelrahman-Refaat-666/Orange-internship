#include<iostream>
#include<string>
#include <cstdlib>
using namespace std;

float co = 0.0;

struct equationValues {
	//int num = 100;
	float coff;
	string vars;
	int constco;
};
//function  checks for variable repition & sums
int varcount = 0;
bool exists(equationValues* arr, int size, string vars, float coeff) {
	
	for (int i = 0; i < size; ++i) {
		if (arr[i].vars == vars) {
			arr[i].coff += coeff;
			return true;
		}
	}
			for (int i = 0; i < size; ++i) {
				if (arr[i].vars.empty()) {
					arr[i].vars = vars;
					arr[i].coff = coeff;
					varcount++;
					return false;
					
				}
			}
		
	return false;
}
void print(equationValues* arr, int size) {
	//int size = 100;
	for (int i = 0; i < size; ++i) {
		if (!arr[i].vars.empty()) {
			cout << arr[i].coff << " " << arr[i].vars << " ";
		}
	}
	cout << endl;
}

void invertSign(string& ceq) {
	int i = ceq.find('=');
	ceq.replace(i, 1, 1, '+');

	for (; i < ceq.length(); ++i) {
		switch (ceq[i]) {

		case '+':
			ceq.replace(i, 1, 1,'-');
			break;
		case '-':
			ceq.replace(i, 1, 1, '+');
			break;
		}
	}
}



int firstParse(string& ceq, string* terms, int size) {

	invertSign(ceq);
	cout << ceq << endl;
	int idx = 0;
	int  count = 0;
	
	for (int i = 0; i <= ceq.length(); ++i) {

		if (ceq[i] == '+' || ceq[i] == '-' || i == ceq.length()) {
			terms[idx] = ceq.substr(0, i);
			ceq.erase(0, i);
			i = 0;
			count++;
			cout << terms[idx] << endl;
			idx++;
		}

	}

	for (int i = 0; i < count; ++i) {

		bool checkcons = true;
		for (int j = 0; j < terms[i].length(); ++j) {
			if (isalpha(terms[i][j])) {
				checkcons = false;
			}
		}
			if (checkcons == true) {
				co -= atof(terms[i].c_str());
				//cout << " constant is " << co << endl;
				checkcons = false;
			}
		}
	
	return count;
}

bool isArithmeticOp(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
void proper(equationValues* arr, int size) {

	bool firstTerm = true;
	float constantSum = 0;

	for (int i = 0; i < size; ++i) {
		
			if (!firstTerm) {

				if (arr[i].coff >= 0) { cout << "+"; }
				else { cout << "-"; }
			}
			else if (arr[i].coff < 0) { cout << "-"; }

			cout << abs(arr[i].coff) << arr[i].vars;
			firstTerm = false;

	}
	cout << "=" << co << endl;

}

void  secondParse(string ceq) {
	
	string* terms = new string[100];
	int count = firstParse(ceq, terms,100);

	/*for (int idx = 0; idx < count; idx++)
	{
		cout << "Idx= " << idx << terms[idx] << "  ";
	}
	cout << endl;
	*/
	string vars;
	float coeff;
	equationValues arr[100] = {};

	for (int i = 0; i < count; ++i) {
		for (int j = 0; j < terms[i].length(); ++j) {
			if (isArithmeticOp(terms[i][j])) {
				coeff = atof(terms[i].substr(0, j).c_str());
				vars = terms[i].substr(j);
				
				exists(arr, 100, vars, coeff);
			}

		}
	}
	print(arr,100);
	proper(arr, varcount);
}



void MultipleInput(int rep) {
	 
	string s;
	for (int i = 0; i < rep; ++i) {
		cout << "enter equation : " << endl; 
		cin >> s;
		secondParse(s);
	}
}

/*void addtwo(string st) {



	for (int i = 0; i < size; ++i) {
		if (arr[i] = " "){
		
		}
	}

}*/


int main() {
	cout << "Enter number of equations: " << endl;
	int num; cin >> num;
	MultipleInput(num);

}