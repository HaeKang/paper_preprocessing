#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

//3LINE 

int main() {
	string fname = "final_ctd_drug_dis_mod.txt";
	ofstream of("drug_dis_3line_mod.txt");

	ifstream inf(fname);

	if (!inf) {
		cout << "file open error!" << endl;
	}

	string d[2];
	map<string, vector<string>> m_drug;
	map<string, vector<string>> m_dis;
	map<string, vector<string>>::iterator it;


	while (!inf.eof()) {
		getline(inf, d[0], '\t');	// drug name

		if (d[0] != "") {

			vector<string> v_drug;
			vector<string> v_dis;

			getline(inf, d[1], '\n');
			
			// drug map
			if (m_drug.find(d[0]) == m_drug.end()) {	
				v_drug.push_back(d[1]);
				m_drug.insert(make_pair(d[0], v_drug));
			}
			else {
				m_drug.find(d[0])->second.push_back(d[1]);
			}

			// dis map
			if (m_dis.find(d[1]) == m_dis.end()) {
				v_dis.push_back(d[0]);
				m_dis.insert(make_pair(d[1], v_dis));
			}
			else {
				m_dis.find(d[1])->second.push_back(d[0]);
			}
		}
	}

	
	string first_drug_name, first_dis_name, second_drug_name, second_dis_name;



	for (it = m_drug.begin(); it != m_drug.end(); it++) {
		first_drug_name = it->first;	//d1
		vector<string> first_drug_disList = it->second;

		// 1Line
		for (int k = 0; k < first_drug_disList.size(); k++) {
			first_dis_name = first_drug_disList[k];	//dis1
			vector<string> first_dis_drugList = m_dis.find(first_dis_name)->second;
			
			// 2Line
			for (int j = 0; j < first_dis_drugList.size(); j++) {
				second_drug_name = first_dis_drugList[j];	//d2
				if (first_drug_name != second_drug_name) {
					vector<string> second_drug_disList = m_drug.find(second_drug_name)->second;

					// 3Line
					for (int i = 0; i < second_drug_disList.size(); i++) {
						second_dis_name = second_drug_disList[i];	//dis2
						bool check;
						if (second_dis_name != first_dis_name) {
							of << first_drug_name << '\t' << first_dis_name << '\t' << second_drug_name << '\t' << second_dis_name << '\n';

						}
					}
				}
			}

		}
		
	}

	of.close();
	return 0;

}

