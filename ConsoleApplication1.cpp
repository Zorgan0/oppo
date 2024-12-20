#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

using std::fstream;
using std::cout;
using std::cin;
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

void LessonsByTeacher(const vector<Lesson>& lessons, const string& teacherName) {
    cout << "Lessons for teacher " << teacherName << ":\n";
    bool found = false;
    for (const Lesson& lesson : lessons) {
        if (lesson.name == teacherName) {
            cout << lesson << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No lessons found for teacher " << teacherName << ".\n";
    }
}

void printLessonsByDate(const vector<Lesson>& lessons, const string& date) {
    cout << "Lessons on date " << date << ":\n";
    bool found = false;
    for (const Lesson& lesson : lessons) {
        if (lesson.date == date) {
            cout << lesson << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No lessons found on this date.\n";
    }
}

int main() {
    fstream in("input.txt");
    string s;
    vector<Lesson> lessons;
    while (getline(in, s)) {
        lessons.push_back({ getDate(s), getTime(s), getName(s) });
    }
    in.close();

    int choice;
    do {
        cout << "\nChoose an option:\n";
        cout << "1. Show all lessons\n";
        cout << "2. Show lessons for a teacher\n";
        cout << "3. Show lessons for a date\n";
        cout << "4. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "All lessons:\n";
            for (const Lesson& lesson : lessons) {
                cout << lesson << "\n";
            }
            break;
        case 2: {
            string teacherName;
            cout << "Enter the teacher's name: ";
            cin.ignore();
            getline(cin, teacherName);
            LessonsByTeacher(lessons, teacherName);
            break;
        }
        case 3: {
            string date;
            cout << "Enter the date: ";
            cin >> date;
            printLessonsByDate(lessons, date);
            break;
        }
        case 4:
            break;
        default:
            cout << "You're stupid. There's no such option..\n";
            break;
        }
    } while (choice != 4);

    return 0;
}
