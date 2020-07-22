#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;


// dise mesh score


int main() {
	string fname = "dise_mesh_tree_mod.txt";
	ofstream of("disease_mesh_score.txt");

	ifstream inf(fname);

	if (!inf) {
		cout << "file error" << endl;
	}

	string dis[11];
	
	map<string, vector<string>> m;

	map<string, vector<string>>::iterator it;
	map<string, vector<string>>::iterator it2;


	while (!inf.eof()) {
		// dis name
		getline(inf, dis[0], '\t');
		if (dis[0] != "") {
			getline(inf, dis[1], '\t');
			getline(inf, dis[2], '\t');
			getline(inf, dis[3], '\t');
			getline(inf, dis[4], '\t');
			getline(inf, dis[5], '\t');
			getline(inf, dis[6], '\t');
			getline(inf, dis[7], '\t');
			getline(inf, dis[8], '\t');
			getline(inf, dis[9], '\t');
			getline(inf, dis[10], '\n');
			
			// 업쓰면
			if (m.find(dis[0]) == m.end()) {
				vector<string> v;
				for (int i = 0; i < 10; i++) {
					if (dis[i + 1] != "") {
						v.push_back(dis[i + 1]);
					}
				}

				m.insert(make_pair(dis[0], v));
			} 
			else {
				for (int i = 0; i < 10; i++) {
					if (dis[i + 1] != "") {
						m.find(dis[0])->second.push_back(dis[i + 1]);
					}
				}
			}
		}

	}


	for (it = m.begin(); it != m.end(); it++) {
		if (it != m.end()) {
			for (it2 = next(it, 1); it2 != m.end(); it2++) {
				vector<string> v1 = it->second;
				vector<string> v2 = it2->second;

				float v_union = 0;
				float v_intersect = 0;

				v_union = v1.size() + v2.size();

				int vector_len = 0;

				for (int k = 0; k < v1.size(); k++) {
					for (int j = 0; j < v2.size(); j++) {
						if ( v1[k].compare(v2[j]) == 0) {
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
