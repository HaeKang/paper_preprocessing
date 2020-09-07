#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
	string fname1 = "gba_dis_start_0824.txt";
	string fname2 = "gba_drug_start_0824.txt";
	string fname3 = "final_ctd_drug_dis_mod.txt";

	ofstream of("gba_score_0824_2.txt");

	ifstream inf1(fname1);
	ifstream inf2(fname2);
	ifstream inf3(fname3);

	string a[3];

	if (!inf1 || !inf2 || !inf3) {
		cout << "file open error" << endl;
	}
	else {
		cout << "file open" << endl;
	}

	map<string, map<string, float>> dis;
	map<string, map<string, int>> dis_count;

	map<string, map<string, float>> drug;
	map<string, map<string, int>> drug_count;

	// dis start
	while (!inf1.eof()) {
		getline(inf1, a[0], '\t');
		if (a[0] != "") {
			getline(inf1, a[1], '\t');
			getline(inf1, a[2], '\n');

			float score = stof(a[2]);


			if (dis.find(a[0]) != dis.end()) {
				if (dis.find(a[0])->second.find(a[1]) != dis.find(a[0])->second.end()) {
					float n1 = dis.find(a[0])->second.find(a[1])->second;

					if (score > n1) {
						dis.find(a[0])->second.at(a[1]) = score;
					}

					int c = dis_count.find(a[0])->second.find(a[1])->second;
					c += 1;
					dis_count.find(a[0])->second.at(a[1]) = c;

				}
				else {
					dis.find(a[0])->second.insert(make_pair(a[1], score));
					dis_count.find(a[0])->second.insert(make_pair(a[1], 1));
				}
			}
			else {
				map<string, float> m;
				m.insert(make_pair(a[1], score));
				dis.insert(make_pair(a[0], m));

				map<string, int> m2;
				int count = 1;
				m2.insert(make_pair(a[1], count));
				dis_count.insert(make_pair(a[0], m2));
			}

		}
	}

	cout << "dis end" << endl;

	// drug start
	while (!inf2.eof()) {
		getline(inf2, a[0], '\t');
		if (a[0] != "") {
			getline(inf2, a[1], '\t');
			getline(inf2, a[2], '\n');

			float score = stof(a[2]);

			if (drug.find(a[0]) != drug.end()) {
				if (drug.find(a[0])->second.find(a[1]) != drug.find(a[0])->second.end()) {
					float n1 = drug.find(a[0])->second.find(a[1])->second;

					if (score > n1) {
						drug.find(a[0])->second.at(a[1]) = score;
					}

					drug_count.find(a[0])->second.at(a[1]) = drug_count.find(a[0])->second.find(a[1])->second + 1;

				}
				else {
					drug.find(a[0])->second.insert(make_pair(a[1], score));
					drug_count.find(a[0])->second.insert(make_pair(a[1], 1));
				}
			}
			else {
				map<string, float> m4;
				m4.insert(make_pair(a[1], score));
				drug.insert(make_pair(a[0], m4)) ;

				map<string, int> m5;
				int count = 1;
				m5.insert(make_pair(a[1], count));
				drug_count.insert(make_pair(a[0], m5));
			}
		}
	}

	cout << "drug end" << endl;


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

					//int c1 = drug_count.find(drug_name)->second.find(dis_name)->second + dis_count.find(drug_name)->second.find(dis_name)->second;

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
