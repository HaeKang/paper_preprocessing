#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
	string fname1 = "gba_dis_start_0812.txt";
	string fname2 = "gba_drug_start_0812.txt";
	string fname3 = "final_ctd_drug_dis_mod.txt";

	ofstream of("gba_score_0812.txt");

	ifstream inf1(fname1);
	ifstream inf2(fname2);
	ifstream inf3(fname3);

	map<string, map<string, float>> dis;
	map<string, map<string, float>> drug;

	string a[3];

	while (!inf1.eof()) {
		getline(inf1, a[0], '\t');
		if (a[0] != "") {
			getline(inf1, a[1], '\t');
			getline(inf1, a[2], '\n');

			float score = stof(a[2]);

			if (dis.find(a[0]) != dis.end()) {
				dis.find(a[0])->second.insert(make_pair(a[1], score));
			}
			else {
				map<string, float> m;
				m.insert(make_pair(a[1], score));
				dis.insert(make_pair(a[0], m));
			}

		}
	}

	while (!inf2.eof()) {
		getline(inf2, a[0], '\t');
		if (a[0] != "") {
			getline(inf2, a[1], '\t');
			getline(inf2, a[2], '\n');

			float score = stof(a[2]);

			if (drug.find(a[0]) != drug.end()) {
				drug.find(a[0])->second.insert(make_pair(a[1], score));
			}
			else {
				map<string, float> m2;
				m2.insert(make_pair(a[1], score));
				drug.insert(make_pair(a[0], m2)) ;
			}
		}
	}

	string b[2];
	map<string, vector<string>> drug_dis;
	while (!inf3.eof()) {
		getline(inf3, b[0], '\t');
		if (b[0] != "") {
			getline(inf3, b[1], '\n');

			if (drug_dis.find(b[0]) != drug_dis.end()) {
				drug_dis.find(b[0])->second.push_back(b[1]);
			}
			else {
				vector<string> v;
				v.push_back(b[1]);
				drug_dis.insert(make_pair(b[0], v));
			}

		}
	}
	map<string, map<string, float>>::iterator it;
	map<string, float>::iterator it2;

	cout << "here" << endl;

	for (it = dis.begin(); it != dis.end(); it++) {

		string drug_name = it->first;
		map<string, float> m3 = it->second;

		for (it2 = m3.begin(); it2 != m3.end(); it2++) {
			string dis_name = it2->first;
			float score1 = it2->second;

			if (drug.find(drug_name) != drug.end()) {
				if (drug.find(drug_name)->second.find(dis_name) != drug.find(drug_name)->second.end()) {
					float score2 = drug.find(drug_name)->second.find(dis_name)->second;
					float fin_score = score1 * score2;
					bool write_state = false;

					vector<string> dis_list = drug_dis.find(drug_name)->second;
					for (int i = 0; i < dis_list.size(); i++) {
						if (dis_name == dis_list[i]) {
							of << drug_name << '\t' << dis_name << '\t' << fin_score <<'\t' << "T" << '\n';
							write_state = true;
						}
					}

					if (!write_state) {
						of << drug_name << '\t' << dis_name << '\t' << fin_score << '\t' << "F" << '\n';
					}
					
				}
			}

		}
	}

	of.close();
	return 0;
}
