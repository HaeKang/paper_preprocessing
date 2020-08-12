#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

int main() {
	string fname1 = "final_ctd_drug_dis_mod.txt";
	string fname2 = "dis_sim_0812.txt";
	string fname3 = "drug_sim_0812.txt";

	ifstream inf1(fname1);
	ifstream inf2(fname2);
	ifstream inf3(fname3);

	ofstream of1("gba_drug_start_0812.txt");
	ofstream of2("gba_dis_start_0812.txt");

	string a[2];

	map<string, vector<string>> drug;
	map<string, vector<string>> dis;

	while (!inf1.eof()) {
		getline(inf1, a[0], '\t');
		if (a[0] != "") {
			getline(inf1, a[1], '\n');

			// drug
			if (drug.find(a[0]) == drug.end()) {
				vector<string> v;
				v.push_back(a[1]);
				drug.insert(make_pair(a[0], v));
			}
			else {
				drug.find(a[0])->second.push_back(a[1]);
			}

			// dis
			if (dis.find(a[1]) == dis.end()) {
				vector<string> v;
				v.push_back(a[0]);
				dis.insert(make_pair(a[1], v));
			}
			else {
				dis.find(a[1])->second.push_back(a[0]);
			}
		}
	}

	cout << "ctd" << endl;

	map<string, map<string, float>> dis_score;
	string b[3];
	while (!inf2.eof()) {
		getline(inf2, b[0], '\t');
		if (b[0] != "") {
			getline(inf2, b[1], '\t');
			getline(inf2, b[2], '\n');

			float score = stof(b[2]);

			if (dis_score.find(b[0]) != dis_score.end()) {
				dis_score.find(b[0])->second.insert(make_pair(b[1], score));
			}
			else {
				map<string, float> m;
				m.insert(make_pair(b[1], score));
				dis_score.insert(make_pair(b[0], m));
			}
		}
	}

	cout << "dis" << endl;

	map<string, map<string, float>> drug_score;
	while (!inf3.eof()) {
		getline(inf3, b[0], '\t');
		if (b[0] != "") {
			getline(inf3, b[1], '\t');
			getline(inf3, b[2], '\n');

			float score = stof(b[2]);

			if (drug_score.find(b[0]) != drug_score.end()) {
				drug_score.find(b[0])->second.insert(make_pair(b[1], score));
			}
			else {
				map<string, float> m;
				m.insert(make_pair(b[1], score));
				drug_score.insert(make_pair(b[0], m));
			}
		}
	}

	cout << "drug start" << endl;

	// drug start
	map<string, map<string, float>> drug_start;
	map<string, vector<string>>::iterator it_drug;
	map<string, vector<string>>::iterator it_drug2;

	for (it_drug = drug.begin(); it_drug != drug.end(); it_drug++) {
		for (it_drug2 = next(it_drug, 1); it_drug2 != drug.end(); it_drug2++) {
			string first_drug = it_drug->first;
			string second_drug = it_drug2->first;
			vector<string> dis_list = it_drug->second;

			if (drug_score.find(first_drug) != drug_score.end()) {
				if (drug_score.find(first_drug)->second.find(second_drug) != drug_score.find(first_drug)->second.end()) {
					float ds = drug_score.find(first_drug)->second.find(second_drug)->second;
					
					for (int i = 0; i < dis_list.size(); i++) {
						string dis_name = dis_list[i];
						of1 << second_drug << '\t' << dis_name << '\t' << ds << '\n';
					}

				}
			}

		}
	}

	cout << "dis start" << endl;

	// dis start
	map<string, map<string, float>> dis_start;
	map<string, vector<string>>::iterator it_dis;
	map<string, vector<string>>::iterator it_dis2;

	for (it_dis = dis.begin(); it_dis != dis.end(); it_dis++) {
		for (it_dis2 = next(it_dis, 1); it_dis2 != dis.end(); it_dis2++) {
			string first_dis = it_dis->first;
			string second_dis = it_dis2->first;
			vector<string> drug_list = it_dis->second;

			if (dis_score.find(first_dis) != dis_score.end()) {
				if (dis_score.find(first_dis)->second.find(second_dis) != dis_score.find(first_dis)->second.end()) {
					float ds2 = dis_score.find(first_dis)->second.find(second_dis)->second;

					for (int n = 0; n < drug_list.size(); n++) {
						string drug_name = drug_list[n];
						of2 << drug_name << "\t" << second_dis << '\t' << ds2 << '\n';
					}

				}
			}

		}
	}

	
	of1.close();
	of2.close();

	return 0;
}
