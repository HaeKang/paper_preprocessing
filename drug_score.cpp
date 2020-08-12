#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

int main() {
	string fname3 = "drug_atc_score.txt";
	string fname4 = "drug_Chem_sim.txt";
	string fname5 = "drug_se_score.txt";
	string fname6 = "drug_target_score.txt";
	string fname9 = "final_ctd_drug_dis_mod.txt";

	ofstream of1("drug_sim_0812.txt");


	ifstream inf3(fname3);
	ifstream inf4(fname4);
	ifstream inf5(fname5);
	ifstream inf6(fname6);
	ifstream inf9(fname9);


	if ( !inf3 || !inf4 || !inf5 || !inf6 || !inf9) {
		cout << "file open error" << endl;
		return 0;
	}

	map<string, map<string, float>> drug_atc, drug_chem, drug_se, drug_target;
	string a[3];



	while (!inf3.eof()) {
		map<string, float> m1;
		map<string, float> m2;
		getline(inf3, a[0], '\t');
		if (a[0] != "") {
			getline(inf3, a[1], '\t');
			getline(inf3, a[2], '\n');

			float score = stof(a[2]);

			if (drug_atc.find(a[0]) == drug_atc.end()) {
				m1.insert(make_pair(a[1], score));
				drug_atc.insert(make_pair(a[0], m1));
			}
			else {
				drug_atc.find(a[0])->second.insert(make_pair(a[1], score));
			}

			if (drug_atc.find(a[1]) == drug_atc.end()) {
				m2.insert(make_pair(a[0], score));
				drug_atc.insert(make_pair(a[1], m2));
			}
			else {
				drug_atc.find(a[1])->second.insert(make_pair(a[0], score));
			}

		}
	}

	cout << "drug_atc" << endl;

	while (!inf4.eof()) {
		map<string, float> m1;
		map<string, float> m2;
		getline(inf4, a[0], '\t');
		if (a[0] != "") {
			getline(inf4, a[1], '\t');
			getline(inf4, a[2], '\n');

			float score = stof(a[2]);

			if (drug_chem.find(a[0]) == drug_chem.end()) {
				m1.insert(make_pair(a[1], score));
				drug_chem.insert(make_pair(a[0], m1));
			}
			else {
				drug_chem.find(a[0])->second.insert(make_pair(a[1], score));
			}

			if (drug_chem.find(a[1]) == drug_chem.end()) {
				m2.insert(make_pair(a[0], score));
				drug_chem.insert(make_pair(a[1], m2));
			}
			else {
				drug_chem.find(a[1])->second.insert(make_pair(a[0], score));
			}

		}
	}

	cout << "drug_chem" << endl;


	while (!inf5.eof()) {
		map<string, float> m1;
		map<string, float> m2;
		getline(inf5, a[0], '\t');

		if (a[0] != "") {
			getline(inf5, a[1], '\t');
			getline(inf5, a[2], '\n');

			float score = stof(a[2]);

			if (drug_se.find(a[0]) == drug_se.end()) {
				m1.insert(make_pair(a[1], score));
				drug_se.insert(make_pair(a[0], m1));
			}
			else {
				drug_se.find(a[0])->second.insert(make_pair(a[1], score));
			}

			if (drug_se.find(a[1]) == drug_se.end()) {
				m2.insert(make_pair(a[0], score));
				drug_se.insert(make_pair(a[1], m2));
			}
			else {
				drug_se.find(a[1])->second.insert(make_pair(a[0], score));
			}
		}
	}

	cout << "drug se" << endl;

	while (!inf6.eof()) {
		map<string, float> m1;
		map<string, float> m2;
		getline(inf6, a[0], '\t');
		if (a[0] != "") {
			getline(inf6, a[1], '\t');
			getline(inf6, a[2], '\n');

			float score = stof(a[2]);

			if (drug_target.find(a[0]) == drug_target.end()) {
				m1.insert(make_pair(a[1], score));
				drug_target.insert(make_pair(a[0], m1));
			}
			else {
				drug_target.find(a[0])->second.insert(make_pair(a[1], score));
			}

			if (drug_target.find(a[1]) == drug_target.end()) {
				m2.insert(make_pair(a[0], score));
				drug_target.insert(make_pair(a[0], m2));
			}
			else {
				drug_target.find(a[1])->second.insert(make_pair(a[0], score));
			}
		}
	}

	cout << "drug target" << endl;


	string c[2];
	map<string,vector<string>> drug_dis;

	while (!inf9.eof()) {
		getline(inf9, c[0], '\t');	// drug
		if (c[0] != "") {
			vector<string> v_drug;

			getline(inf9, c[1], '\n');	//dis

			// drug
			if (drug_dis.find(c[0]) == drug_dis.end()) {
				v_drug.push_back(c[1]);
				drug_dis.insert(make_pair(c[0], v_drug));
			}
			else {
				drug_dis.find(c[0])->second.push_back(c[1]);
			}
		}
	}

	map<string, vector<string>>::iterator it_drug;
	map<string, vector<string>>::iterator it2;

	map<string, map<string, float>> drug_score_list;

	int count = 0;

	// drug score
	for (it_drug = drug_dis.begin(); it_drug != drug_dis.end(); it_drug++) {
		for (it2 = next(it_drug, 1); it2 != drug_dis.end(); it2++) {
			string first_drug = it_drug->first;
			string second_drug = it2->first;
			float drug_score = 0;

			if (drug_atc.find(first_drug) != drug_atc.end() && drug_chem.find(first_drug) != drug_chem.end() &&
				drug_se.find(first_drug) != drug_se.end() && drug_target.find(first_drug) != drug_target.end()) {

				map<string, float>::iterator atc_two = drug_atc.find(first_drug)->second.find(second_drug);
				map<string, float>::iterator chem_two = drug_chem.find(first_drug)->second.find(second_drug);
				map<string, float>::iterator se_two = drug_se.find(first_drug)->second.find(second_drug);
				map<string, float>::iterator target_two = drug_target.find(first_drug)->second.find(second_drug);

				if (atc_two != drug_atc.find(first_drug)->second.end() && chem_two != drug_chem.find(first_drug)->second.end() &&
					se_two != drug_se.find(first_drug)->second.end() && target_two != drug_target.find(first_drug)->second.end()) {

					drug_score = (atc_two->second + chem_two->second + se_two->second + target_two->second) / 4;
					count += 1;

					if (drug_score_list.find(first_drug) == drug_score_list.end()) {
						map<string, float> m;
						m.insert(make_pair(second_drug, drug_score));
						drug_score_list.insert(make_pair(first_drug, m));
					}
					else {
						map<string, float> m2 = drug_score_list.find(first_drug)->second;
						if (m2.find(second_drug) == m2.end()) {	
							
							drug_score_list.find(first_drug)->second.insert(make_pair(second_drug, drug_score));


						}else {
							float n = m2.find(second_drug)->second;

							if (drug_score > n) {
								drug_score_list.find(first_drug)->second.at(second_drug) = drug_score;
							}
						}
					}
				
				}
			}

		}
	}


	map<string, map<string, float>>::iterator list_it;
	map<string, float>::iterator list2_it;
	for (list_it = drug_score_list.begin(); list_it != drug_score_list.end(); list_it++) {
		string first_drug = list_it->first;
		map<string, float> list2 = list_it->second;

		for (list2_it = list2.begin(); list2_it != list2.end(); list2_it++) {
			string second_drug = list2_it->first;
			float score = list2_it->second;

			of1 << first_drug << "\t" << second_drug << "\t" << score << '\n';
		}

	}


	of1.close();
	return 0;
}
