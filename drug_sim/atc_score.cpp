#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;


// drug atc score

int main() {
	string fname = "drug_atc.txt";
	ofstream of("drug_atc_score.txt");

	ifstream inf(fname);

	if (!inf) {
		printf("file open error\n");
	}

	string atc[6];

	map<string, vector<string>> m;

	map<string, vector<string>>::iterator it;
	map<string, vector<string>>::iterator it2;

	while (!inf.eof()) {
		// drug name
		getline(inf, atc[0], '\t');

		if (atc[0] != "") {
			// atc code
			vector<string> v;
			getline(inf, atc[1], '\t');
			getline(inf, atc[2], '\t');
			getline(inf, atc[3], '\t');
			getline(inf, atc[4], '\t');
			getline(inf, atc[5], '\n');

			if (m.find(atc[0]) == m.end()) {
				for (int i = 0; i < 5; i++) {
					v.push_back(atc[i + 1]);
				}
				m.insert(make_pair(atc[0], v));
			}
			else {
				for (int k = 0; k < 5; k++) {
					m.find(atc[0])->second.push_back(atc[k]);
				}
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

				for (int k = 0; k < v1.size(); k++) {
					for (int j = 0; j < v2.size(); j++) {
						if (v1[k].compare(v2[j]) == 0) {
							v_intersect += 1;
							v2.erase(v2.begin() + j);
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
