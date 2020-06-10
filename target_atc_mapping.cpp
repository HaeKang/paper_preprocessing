#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <set>
#include <windows.h>

using namespace std;

int main() {
   string fname1 = "drug_targets.txt";
   string fname2 = "drug_atc.txt";

   ifstream inf1(fname1);
   ifstream inf2(fname2);
   ofstream of("drug_atc_com.txt");


   // file open error
   if (!inf1 || !inf2) {
      printf("file open error\n");
   }

   string drug[2];
   string atc[7];
   set<string> drug_list;
   set<string>::iterator it;


   while (!inf1.eof()) {
      // drug id
      getline(inf1, drug[0], '\t');

      if (drug[0] != "") {
         // target name
         getline(inf1, drug[1], '\n');
         drug_list.insert(drug[0]);

      }
   }

   while (!inf2.eof()) {
      // drugbank id
      getline(inf2, atc[0], '\t');


      if (atc[0] != "" || atc[0] != "parnet_key") {
         //atc
         getline(inf2, atc[1], '\t');
         getline(inf2, atc[2], '\t');
         getline(inf2, atc[3], '\t');
         getline(inf2, atc[4], '\t');
         getline(inf2, atc[5], '\n');

         // drug bank id ������ ã��
         it = drug_list.find(atc[0]);

         // ������ ������
         if (it != drug_list.end()) {
            of << atc[0] << '\t' << atc[1] << '\t' << atc[2] << '\t' << atc[3] << '\t' << atc[4] << '\t' << atc[5] << endl;
         }
      }
   }

   of.close();
   return 0;
}
