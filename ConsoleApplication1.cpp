#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

using std::fstream;
using std::cout;
using std::ostream;
using std::string;
using std::vector;
using std::regex;
using std::istringstream;
using std::smatch;

class Lesson {
public:
    string date;
    string time;
    string name;

	Lesson(string date, string time, string name) : date(date), time(time), name(name) {}

    friend ostream& operator<<(ostream& os, const Lesson& lesson) {
        os << lesson.date << " " << lesson.time << " " << lesson.name;
        return os;
    }
};

string getDate(const string& str) {
    regex dateRegex(R"(\d{4}\.\d{1,2}\.\d{1,2})");
    smatch match;
    if (regex_search(str, match, dateRegex)) {
        return match.str(0);
    }
    return "";
}

string getTime(const string& str) {
    regex timeRegex(R"(\d{1,2}:\d{1,2})");
    smatch match;
    if (regex_search(str, match, timeRegex)) {
        return match.str(0);
    }
    return "";
}

string getName(const string& str) {
    regex nameRegex(R"([A-Z][a-z]*\s[A-Z][a-z]*(\s[A-Z][a-z]*)?)");
    smatch match;
    if (regex_search(str, match, nameRegex)) {
        return match.str(0);
    }
    return "";
}

int main() {
    fstream in("input.txt");
    string s;
    vector<Lesson> lessons;
    while (getline(in, s)) {
        lessons.push_back({getDate(s), getTime(s), getName(s)});
    }
    in.close();
    for (const Lesson& lesson : lessons) {
        cout << lesson << "\n";
    }
}