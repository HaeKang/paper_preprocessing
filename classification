#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main() {

	string fname = "drug_dis_3Line_score_fin.txt";
	string fname2 = "final_ctd_drug_dis_mod.txt";

	ifstream inf1(fname);
	ifstream inf2(fname2);
	ofstream of("3line_score_0812.txt");

	if (!inf1) {
		cout << "file open error" << endl;
	}


	map<string, map<string, string>> m;
	map<string, map<string, string>>::iterator it;
	map<string, string>::iterator it2;


	map<string, map<string, int>> count;

	string a[3];

	while (!inf1.eof()) {
		getline(inf1, a[0], '\t');

		if (a[0] != "") {
			getline(inf1, a[1], '\t');
			getline(inf1, a[2], '\n');

			
			if (m.find(a[0]) != m.end()) {
				if (m.find(a[0])->second.find(a[1]) != m.find(a[0])->second.end()) {
					string num1 = a[2];
					string num2 = m.find(a[0])->second.find(a[1])->second;

					float n1 = stof(num1);
					float n2 = stof(num2);

					if (n1 > n2) {
						m.find(a[0])->second.at(a[1]) = num1;
					}

					int c = count.find(a[0])->second.find(a[1])->second;
					c += 1;
					count.find(a[0])->second.at(a[1]) = c;

				}
				else {
					m.find(a[0])->second.insert(make_pair(a[1], a[2]));
					count.find(a[0])->second.insert(make_pair(a[1], 1));
				}

			}
			else {
				map<string, string> m2;
				m2.insert(make_pair(a[1], a[2]));
				m.insert(make_pair(a[0], m2));

				map<string, int> m3;
				m3.insert(make_pair(a[1], 1));
				count.insert(make_pair(a[0], m3));
			}

		}
	}


	map<string, vector<string>> drug_dis;
	string b[2];

	while (!inf2.eof()) {
		getline(inf2, b[0], '\t');
		if (b[0] != "") {
			getline(inf2, b[1], '\n');

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

	cout << "here " << endl;

	for (it = m.begin(); it != m.end(); it++) {
		for (it2 = it->second.begin(); it2 != it->second.end(); it2++) {
			vector<string> dis_list = drug_dis.find(it->first)->second;
			bool write_state = false;
			
			float score = stof(it2->second);

			int c2 = count.find(it->first)->second.find(it2->first)->second;

			for (int i = 0; i < dis_list.size(); i++) {
				if (it2->first == dis_list[i]) {
					of << it->first << '\t' << it2->first << '\t' << it2->second << '\t' << c2 << '\t' << "T" << "\n";
					write_state = true;
				}
			}

			if (!write_state) {
				of << it->first << '\t' << it2->first << '\t' << it2->second << '\t' << c2 << '\t' << "F" << "\n";
			}
		}
	}

	of.close();
	return 0;
}
