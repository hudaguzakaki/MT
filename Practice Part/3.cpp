//Гоголев Михаил Александрович
#include <iostream>
#include <algorithm>
#include <vector> 
#include <string>
#include <regex>

using namespace std;

string IsEmpty(string str, string value) {
	if (str.empty()) {
		return value;
	}
	else
		return str;
}

void Search(string str) {
	//cout <<"url: "<< str << endl;
	smatch match;
	regex r("(http|https)?(://)?([a-z\\.]+)(:)?(\\/)?(\\d+)?(\\/)?(\\/[a-z\\.]+)?");
	if (regex_match(str, match, r)) {

		string protocol = IsEmpty(match[1].str(), "http");
		string host = match[3].str();
		string port = IsEmpty(match[6].str(), "80");
		string page = IsEmpty(match[8].str(), "/");

		cout << "Protocol: " << protocol << " Host: " << host << " Port: " << port << " Page: " << page << endl;
	}
}

void main() {
	vector <string> urls;
	urls.push_back("http://mytona.com/index.html");
	urls.push_back("https://mytona.com:8080/");
	urls.push_back("mytona.com");

	for_each(urls.begin(), urls.end(), Search);
	cin.get();
}