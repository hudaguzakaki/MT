//Гоголев Михаил Александрович
#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <sstream>

using namespace std;

void CheckIfExists(vector<string>& vec, string segment) {
	int copyCount = 0;
	if (find(vec.begin(), vec.end(), segment) != vec.end())
		copyCount++;
	if (copyCount > 0)
		vec.push_back(segment + to_string(copyCount));
	else
		vec.push_back(segment);
}

void PrintVec(vector<string>& vec) {
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		if (next(it) == vec.end())
		{
			cout << *it << " ";
		}
		else
			cout << *it << ":";
	}
}

void main() {
	ifstream ifs("input.txt");
	string segment;
	vector<string> keyList;
	vector<string> valueList;
	bool isKey = true;

	while (getline(ifs, segment, '\n')) {
		stringstream ss(segment);
		while (getline(ss, segment, ':')) {
			if (!segment.empty()) {
				if (isKey) {
					CheckIfExists(keyList, segment);
					isKey = false;
				}
				else {
					CheckIfExists(valueList, segment);
					isKey = true;
				}
			}
		}
	}


	PrintVec(keyList);
	PrintVec(valueList);
	cout << endl;
	cin.get();
}
