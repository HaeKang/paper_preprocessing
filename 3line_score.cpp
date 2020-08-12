#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

int main() {
	string fname1 = "disease_gene_score.txt";
	string fname2 = "disease_mesh_score.txt";
	string fname3 = "drug_atc_score.txt";
	string fname4 = "drug_Chem_sim.txt";
	string fname5 = "drug_se_score.txt";
	string fname6 = "drug_target_score.txt";
	string fname7 = "drug_dis_3line.txt";
	string fname8 = "final_ctd_drug_dis_mod.txt";
	string fname9 = "dis_go_score.txt";

	ofstream of("drug_dis_3Line_score_fin.txt");

	ifstream inf1(fname1);
	ifstream inf2(fname2);
	ifstream inf3(fname3);
	ifstream inf4(fname4);
	ifstream inf5(fname5);
	ifstream inf6(fname6);
	ifstream inf7(fname7);
	ifstream inf8(fname8);
	ifstream inf9(fname9);

	if (!inf1 || !inf2 || !inf3 || !inf4 || !inf5 || !inf6 || !inf7 || !inf8 || !inf9) {
		cout << "file open error" << endl;
		return 0;
	}

	string a[3];
	
		
	map<string, map<string, float>> dis_gene, dis_mesh, dis_go, drug_atc, drug_chem, drug_se, drug_target;

	string a2[2];	// 각 약물,질병이 공유하는 질병, 약물 구하는거 inf8
	map<string, vector<string>> drug_dis;


	int t_count = 0;


	// drug간 공유하는 dis , dis간 공유하는 drug 찾으려고 하는고
	while (!inf8.eof()) {
		getline(inf8, a2[0], '\t');
		if (a2[0] != "") {
			getline(inf8, a2[1], '\n');

			// key = drug
			if (drug_dis.find(a2[0]) == drug_dis.end()) {
				vector<string> v;
				v.push_back(a2[1]);
				drug_dis.insert(make_pair(a2[0], v));
			}
			else {
				drug_dis.find(a2[0])->second.push_back(a2[1]);
			}

			//key = dis
			if (drug_dis.find(a2[1]) == drug_dis.end()) {
				vector<string> v;
				v.push_back(a2[0]);
				drug_dis.insert(make_pair(a2[1], v));
			}
			else {
				drug_dis.find(a2[1])->second.push_back(a2[0]);
			}

		}
	}


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


	while (!inf9.eof()) {
		map<string, float> m1;
		map<string, float> m2;
		getline(inf9, a[0], '\t');
		if (a[0] != "") {
			getline(inf9, a[1], '\t');
			getline(inf9, a[2], '\n');

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


	string b[4];


	while (!inf7.eof()) {
		getline(inf7, b[0], '\t'); // d1
		if (b[0] != "") {
			getline(inf7, b[1], '\t'); // dis1
			getline(inf7, b[2], '\t'); // d2
			getline(inf7, b[3], '\n'); // dis2

			float drug_score = 0;
			float dis_score = 0;
			float final_score = 0;


			if (drug_atc.find(b[0]) != drug_atc.end() && drug_chem.find(b[0]) != drug_chem.end() &&
				drug_se.find(b[0]) != drug_se.end() && drug_target.find(b[0]) != drug_target.end()) {
				
				map<string, float>::iterator atc_two = drug_atc.find(b[0])->second.find(b[2]);
				map<string, float>::iterator chem_two = drug_chem.find(b[0])->second.find(b[2]);
				map<string, float>::iterator se_two = drug_se.find(b[0])->second.find(b[2]);
				map<string, float>::iterator target_two = drug_target.find(b[0])->second.find(b[2]);

				// durg
				if (atc_two != drug_atc.find(b[0])->second.end() && chem_two != drug_chem.find(b[0])->second.end() &&
					se_two != drug_se.find(b[0])->second.end() && target_two != drug_target.find(b[0])->second.end()) {
					
					drug_score = (atc_two->second + chem_two->second + se_two->second + target_two->second ) / 4;


					// dis
					if (dis_gene.find(b[1]) != dis_gene.end() && dis_mesh.find(b[1]) != dis_mesh.end() &&
						dis_go.find(b[1]) != dis_go.end() ) {
						map<string, float>::iterator gene_two = dis_gene.find(b[1])->second.find(b[3]);
						map<string, float>::iterator mesh_two = dis_mesh.find(b[1])->second.find(b[3]);
						map<string, float>::iterator go_two = dis_go.find(b[1])->second.find(b[3]);

						if (gene_two != dis_gene.find(b[1])->second.end() && mesh_two != dis_mesh.find(b[1])->second.end() &&
							go_two != dis_go.find(b[1])->second.end() ) {

							dis_score = (gene_two->second + mesh_two->second + go_two->second) / 3;
							final_score = drug_score * dis_score;

							of << b[0] << '\t' << b[3] << '\t' << final_score << '\n';
							
							
						}

					}

				}

			}


		}
	}


	of.close();
	return 0;

}
