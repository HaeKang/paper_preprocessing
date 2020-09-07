#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;


//dis related gene

int main() {
	string fname = "disease_gene_mod.txt";
	ofstream of("disease_gene_score.txt");

	ifstream inf(fname);

	if (!inf) {
		cout << "file error" << endl;
	}

	string gene[2];

	map<string, vector<string>> m;
	map<string, vector<string>>::iterator it;
	map<string, vector<string>>::iterator it2;


	while (!inf.eof()) {
		// gene 
		getline(inf, gene[0], '\t');

		if (gene[0] != "") {
			// drug
			getline(inf, gene[1], '\n');

			// 이미 있음
			if (m.find(gene[1]) != m.end()) {
				m.find(gene[1])->second.push_back(gene[0]);
			}
			else {
				vector<string> v;
				v.push_back(gene[0]);
				m.insert(make_pair(gene[1], v));
			}
		}
	}


	for (it = m.begin(); it != m.end(); it++) {
		if (it != m.end()) {
			for (it2 = next(it, 1); it2 != m.end(); it2++) {
				vector<string> v1 = it->second;
				vector<string> v2 = it2->second;

				float v_union = v1.size() + v2.size();
				float v_intersect = 0;

				for (vector<int>::size_type i = 0; i < v1.size(); i++) {
					for (vector<int>::size_type k = 0; k < v2.size(); k++) {
						// same
						if (v1[i].compare(v2[k]) == 0) {
							v_intersect += 1;
							v2.erase(v2.begin() + k);
						}
					}
				}

				v_union -= v_intersect;

				float score = v_intersect / v_union;
				of << it->first << '\t' << it2->first << '\t' << score << '\n';
			}
		}
	}


	of.close();
	return 0;
}
