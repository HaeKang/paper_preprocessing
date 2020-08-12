#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

int main() {
	string fname1 = "disease_gene_score.txt";
	string fname2 = "disease_mesh_score.txt";
	string fname3 = "dis_go_score.txt";
	string fname9 = "final_ctd_drug_dis_mod.txt";

	ofstream of1("dis_sim_0812.txt");


	ifstream inf1(fname1);
	ifstream inf2(fname2);
	ifstream inf3(fname3);
	ifstream inf9(fname9);


	if (!inf1 || !inf2 || !inf3 || !inf9) {
		cout << "file open error" << endl;
		return 0;
	}

	map<string, map<string, float>> dis_gene, dis_mesh, dis_go;
	string a[3];

	// 기존에 구한 sim 파일들 저장하는고
	while (!inf1.eof()) {
		map<string, float> m1;
		map<string, float> m2;
		getline(inf1, a[0], '\t');
		if (a[0] != "") {
			getline(inf1, a[1], '\t');
			getline(inf1, a[2], '\n');

			float score = stof(a[2]);

			if (dis_gene.find(a[0]) == dis_gene.end()) {
				m1.insert(make_pair(a[1], score));
				dis_gene.insert(make_pair(a[0], m1));
			}
			else {
				dis_gene.find(a[0])->second.insert(make_pair(a[1], score));
			}

			if (dis_gene.find(a[1]) == dis_gene.end()) {
				m2.insert(make_pair(a[0], score));
				dis_gene.insert(make_pair(a[1], m2));
			}
			else {
				dis_gene.find(a[1])->second.insert(make_pair(a[0], score));
			}


		}
	}

	cout << "dis_gene end" << endl;

	while (!inf2.eof()) {
		map<string, float> m1;
		map<string, float> m2;
		getline(inf2, a[0], '\t');
		if (a[0] != "") {
			getline(inf2, a[1], '\t');
			getline(inf2, a[2], '\n');

			float score = stof(a[2]);

			if (dis_mesh.find(a[0]) == dis_mesh.end()) {
				m1.insert(make_pair(a[1], score));
				dis_mesh.insert(make_pair(a[0], m1));
			}
			else {
				dis_mesh.find(a[0])->second.insert(make_pair(a[1], score));
			}

			if (dis_mesh.find(a[1]) == dis_mesh.end()) {
				m2.insert(make_pair(a[0], score));
				dis_mesh.insert(make_pair(a[1], m2));
			}
			else {
				dis_mesh.find(a[1])->second.insert(make_pair(a[0], score));
			}

		}
	}

	cout << "dis_mesh" << endl;


	while (!inf3.eof()) {
		map<string, float> m1;
		map<string, float> m2;
		getline(inf3, a[0], '\t');
		if (a[0] != "") {
			getline(inf3, a[1], '\t');
			getline(inf3, a[2], '\n');

			float score = stof(a[2]);

			if (dis_go.find(a[0]) == dis_go.end()) {
				m1.insert(make_pair(a[1], score));
				dis_go.insert(make_pair(a[0], m1));
			}
			else {
				dis_go.find(a[0])->second.insert(make_pair(a[1], score));
			}

			if (dis_go.find(a[1]) == dis_go.end()) {
				m2.insert(make_pair(a[0], score));
				dis_go.insert(make_pair(a[1], m2));
			}
			else {
				dis_go.find(a[1])->second.insert(make_pair(a[0], score));
			}

		}
	}

	cout << "dis_go" << endl;



	string c[2];
	map<string,vector<string>> dis_list;

	while (!inf9.eof()) {
		getline(inf9, c[0], '\t');	// drug
		if (c[0] != "") {
			vector<string> v_drug;
			getline(inf9, c[1], '\n');	//dis
			
										// drug
			if (dis_list.find(c[1]) == dis_list.end()) {
				v_drug.push_back(c[0]);
				dis_list.insert(make_pair(c[1], v_drug));
			}
			else {
				dis_list.find(c[1])->second.push_back(c[0]);
			}

		}
	}

	cout << "ctd" << endl;

	map<string, map<string, float>> dis_score_list;
	map<string, vector<string>>::iterator it_drug;
	map<string, vector<string>>::iterator it2;

	for (it_drug = dis_list.begin(); it_drug != dis_list.end(); it_drug++) {
		for (it2 = next(it_drug, 1); it2 != dis_list.end(); it2++) {
			string first_dis = it_drug->first;
			string second_dis = it2->first;
			float dis_score = 0;

			// dis
			if (dis_gene.find(first_dis) != dis_gene.end() && dis_mesh.find(first_dis) != dis_mesh.end() &&
				dis_go.find(first_dis) != dis_go.end()) {
				map<string, float>::iterator gene_two = dis_gene.find(first_dis)->second.find(second_dis);
				map<string, float>::iterator mesh_two = dis_mesh.find(first_dis)->second.find(second_dis);
				map<string, float>::iterator go_two = dis_go.find(first_dis)->second.find(second_dis);

				if (gene_two != dis_gene.find(first_dis)->second.end() && mesh_two != dis_mesh.find(first_dis)->second.end() &&
					go_two != dis_go.find(first_dis)->second.end()) {

					dis_score = (gene_two->second + mesh_two->second + go_two->second) / 3;
					
					if (dis_score_list.find(first_dis) != dis_score_list.end()) {
						map<string, float> m2 = dis_score_list.find(first_dis)->second;
						if (m2.find(second_dis) != m2.end()) {
							float n = m2.find(second_dis)->second;
							if (dis_score > n) {
								dis_score_list.find(first_dis)->second.at(second_dis) = dis_score;
							}

						}
						else {
							dis_score_list.find(first_dis)->second.insert(make_pair(second_dis, dis_score));
						}
					}
					else {
						map<string, float> m;
						m.insert(make_pair(second_dis, dis_score));
						dis_score_list.insert(make_pair(first_dis, m));
					}


				}

			}

		}
	}

	

	cout << "here" << endl;

	map<string, map<string, float>>::iterator list_it;
	map<string, float>::iterator list2_it;
	for (list_it = dis_score_list.begin(); list_it != dis_score_list.end(); list_it++) {
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
