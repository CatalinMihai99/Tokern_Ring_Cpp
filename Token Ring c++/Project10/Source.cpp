#include<iostream>
#include<string>
#include<vector>
#include<string.h>
#include<tuple>
using namespace std;
void creare_calculatoare(vector<string> &v, int nr)
{
	for (int index = 0; index < nr; index++)
	{
		auto s = std::to_string(index+1);
		v.push_back("198.192.10." + s);
	}
}
void afisare_calculatoare(vector<string>calculatoare)
{
	for (int index = 0; index < calculatoare.size(); index++)
	{
		auto s = std::to_string(index+1);
		cout << "Calculatorul " +s+" cu adresa IP : "<< calculatoare[index] << endl;
	}
}
int main()
{
	vector<string> calculatoare;
	int nr_calculatoare;
	tuple<string, string, string, bool, bool, vector<string>>jeton;
	string mesaj, sursa, destinatie;
	vector<string> vizitati = {};
	bool ajuns = false, liber = false;
	
	
	string decizie;
	cout << "\n Doriti sa creati o retea TokenRing? \n          [da/nu]\n";
	cin >> decizie;
	while (decizie == "da")
	{

		cout << "\n Cate calculatoare doriti sa aiba reteaua ? \n";
		cin >> nr_calculatoare;
		creare_calculatoare(calculatoare, nr_calculatoare);
		afisare_calculatoare(calculatoare);

		string sens;
		cout << "\n In ce sens doriti sa functioneze reteaua? \n          [sensul_acelor_de_ceaornic/opus_acelor_de_ceasornic] \n";
		cin >> sens;
		if (sens == "opus_acelor_de_ceasornic")
			reverse(calculatoare.begin(), calculatoare.end());

		cout << "\n Care este mesajul pe care doriti sa-l transmiteti? \n";
		cin >> mesaj;
		cout << "\n Care este id-ul calculatorului sursa?";
		cin >> sursa;
		cout << "\n Care este id-ul calculatorului destinatie?";
		cin >> destinatie;
		jeton = make_tuple(sursa, destinatie, mesaj, ajuns, liber, vizitati);

		int pozitie_sursa;
		for (int index = 0; index < calculatoare.size(); index++)
			if (calculatoare[index] == sursa)pozitie_sursa = index;

		for (int index = pozitie_sursa; index < calculatoare.size(); index++)
		{
			vizitati.push_back(calculatoare[index]);
			get<5>(jeton) = vizitati;
			if (vizitati.back() == destinatie)
			{
				cout << endl << mesaj<<endl;
				get<3>(jeton) = true;
			}
			cout  << get<0>(jeton) << "  " << get<1>(jeton) << "  " << get<2>(jeton) << "  " << get<3>(jeton) << "  " << get<4>(jeton) << "  ";
			for (int jdex = 0; jdex < vizitati.size(); jdex++)
				cout << get<5>(jeton)[jdex] << " , ";
			cout << endl;
		}
		int poz_vizitate = vizitati.size();
		for (int index = 0; index < calculatoare.size() - poz_vizitate; index++)
		{
			vizitati.push_back(calculatoare[index]);
			get<5>(jeton) = vizitati;
			if (vizitati.back() == destinatie)
			{
				cout << endl << mesaj<<endl;
				get<3>(jeton) = true;
			}
			cout  << get<0>(jeton) << "  " << get<1>(jeton) << "  " << get<2>(jeton) << "  " << get<3>(jeton) << "  " << get<4>(jeton) << "  ";
			for (int jdex = 0; jdex < vizitati.size(); jdex++)
				cout << get<5>(jeton)[jdex] << " , ";
			cout << endl;
		}
		get<0>(jeton) = "";
		get<1>(jeton) = "";
		get<2>(jeton) = "";
		get<3>(jeton) = false;
		get<4>(jeton) = true;
		vizitati.clear();
		get<5>(jeton) = vizitati;
		cout << endl <<"Token:"<< get<0>(jeton) << " , " << get<1>(jeton) << " , " << get<2>(jeton) << " , " << get<3>(jeton) << " , " << get<4>(jeton) << " , ";
		for (int jdex = 0; jdex < vizitati.size(); jdex++)
			cout << get<5>(jeton)[jdex] << " , ";
		calculatoare.clear();
		vizitati.clear();
		cout << "\n Doriti sa mai creati o retea TokenRing? \n          [da/nu]";
		cin >> decizie;
	}
	return 0;
}