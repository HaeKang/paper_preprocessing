#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

int main() {
	string fname1 = "kegg_drug_map.txt";
	string fname2 = "drug_dis_kegg.txt";
	ofstream of("fin_drug_dis_kegg_0907.txt");

	ifstream inf1(fname1);
	ifstream inf2(fname2);

	if (!inf1 || !inf2) {
		cout << "file open error" << endl;
	}

	map<string, string> drugmap;
	string a[2];

	while (!inf1.eof()) {
		getline(inf1, a[0], '\t');	// kegg id
		if (a[0] != "") {
			getline(inf1, a[1], '\n');	// drugbank id
			drugmap.insert(make_pair(a[0], a[1]));
		}
	}

	string b[2];
	while (!inf2.eof()) {
		getline(inf2, b[0], '\t');	//dis
		if (b[0] != "") {
			getline(inf2, b[1], '\n');	//drug
			if (drugmap.find(b[1]) != drugmap.end()) {
				of << drugmap.find(b[1])->second << "\t" << b[0] << "\n";
			}
		}
	}


	return 0;
}
