// umt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

class Calendar {
private:
	vector<tuple<int, int>> bookedMinutes;
	vector<tuple<int, int>> availableMinutes;
	tuple<int, int> workingMinutes;
public:
	Calendar() {}
	vector<tuple<int, int>> getBookedMinutes() {
		return bookedMinutes;
	}
	tuple<int, int> getWorkingMinutes() {
		return workingMinutes;
	}
	void addBookedMinutes(tuple<int, int> bookedMinutes) {
		this->bookedMinutes.push_back(bookedMinutes);
	}
	void setWorkingMinutes(tuple<int, int> workingMinutes) {
		this->workingMinutes = workingMinutes;
	}
	void calculateAvailableMinutes() {
		if (get<0>(bookedMinutes.at(0)) != get<0>(workingMinutes)) {
			availableMinutes.push_back(make_tuple(get<0>(workingMinutes), get<0>(bookedMinutes.at(0))));
		}
		for (size_t i = 0; i < bookedMinutes.size() - 1; i++) {
			availableMinutes.push_back(make_tuple(get<1>(bookedMinutes.at(i)), get<0>(bookedMinutes.at(i + 1))));
		}
		if (get<1>(bookedMinutes.at(bookedMinutes.size() - 1)) != get<1>(workingMinutes)) {
			availableMinutes.push_back(make_tuple(get<1>(bookedMinutes.at(bookedMinutes.size() - 1)), get<1>(workingMinutes)));
		}
	}
	vector<tuple<int, int>> getAvailableMinutes() {
		return availableMinutes;
	}
};

string regexParser(string line) {
	string result = regex_replace(line, regex(R"([a-zA-Z' \[\]])"), "");
	result = regex_replace(result, regex("(^[0-9]:)"), "");
	result = regex_replace(result, regex("(^:)"), "");
	result = regex_replace(result, regex("(,)"), " ");
	return result;
}

int main()
{
	string line;
	int lineNumber = 1;
	Calendar calendar1, calendar2;
	int minutesMeeting;
	while (getline(in, line)) {
		string lineParsed = regexParser(line);
		if (lineNumber != 5) {
			istringstream iss(lineParsed);
			string first, second;
			while (getline(iss, first, ' ') && getline(iss, second, ' '))
			{
				string firstHour, firstMinute, secondHour, secondMinute;
				istringstream issFirst(first), issSecond(second);
				getline(issFirst, firstHour, ':');
				getline(issFirst, firstMinute, ':');
				getline(issSecond, secondHour, ':');
				getline(issSecond, secondMinute, ':');
				if (lineNumber == 1) {
					calendar1.addBookedMinutes(make_tuple(stoi(firstHour) * 60 + stoi(firstMinute), stoi(secondHour) * 60 + stoi(secondMinute)));
				}
				else if (lineNumber == 2) {
					calendar1.setWorkingMinutes(make_tuple(stoi(firstHour) * 60 + stoi(firstMinute), stoi(secondHour) * 60 + stoi(secondMinute)));
				}
				else if (lineNumber == 3) {
					calendar2.addBookedMinutes(make_tuple(stoi(firstHour) * 60 + stoi(firstMinute), stoi(secondHour) * 60 + stoi(secondMinute)));
				}
				else if (lineNumber == 4) {
					calendar2.setWorkingMinutes(make_tuple(stoi(firstHour) * 60 + stoi(firstMinute), stoi(secondHour) * 60 + stoi(secondMinute)));
				}
			}
		}
		else if (lineNumber == 5) {
			minutesMeeting = stoi(lineParsed);
		}
		lineNumber += 1;
	}
	calendar1.calculateAvailableMinutes();
	calendar2.calculateAvailableMinutes();
	vector<tuple<int, int>> ret;
	for (size_t i = 0; i < calendar1.getAvailableMinutes().size(); i++) {
		for (size_t j = 0; j < calendar2.getAvailableMinutes().size(); j++) {
			int firstBegin = get<0>(calendar1.getAvailableMinutes().at(i));
			int firstEnd = get<1>(calendar1.getAvailableMinutes().at(i));
			int secondBegin = get<0>(calendar2.getAvailableMinutes().at(j));
			int secondEnd = get<1>(calendar2.getAvailableMinutes().at(j));
			if (secondBegin <= firstBegin && secondEnd <= firstEnd && firstBegin <= secondEnd) {
				if (secondEnd - firstBegin >= minutesMeeting) {
					tuple<int, int> aux(firstBegin, secondEnd);
					if (find(ret.begin(), ret.end(), aux) == ret.end()) {
						ret.push_back(aux);
					}
				}
			}
			else if (secondBegin <= firstBegin && secondEnd >= firstEnd) {
				if (firstEnd - firstBegin >= minutesMeeting) {
					tuple<int, int> aux(firstBegin, firstEnd);
					if (find(ret.begin(), ret.end(), aux) == ret.end()) {
						ret.push_back(aux);
					}
				}
			}
			else if (secondBegin >= firstBegin && secondEnd <= firstEnd) {
				if (secondEnd - secondBegin >= minutesMeeting) {
					tuple<int, int> aux(secondBegin, secondEnd);
					if (find(ret.begin(), ret.end(), aux) == ret.end()) {
						ret.push_back(aux);
					}
				}
			}
			else if (secondBegin >= firstBegin && secondEnd >= firstEnd && firstBegin <= secondEnd) {
				if (firstEnd - secondBegin >= minutesMeeting) {
					tuple<int, int> aux(secondBegin, firstEnd);
					if (find(ret.begin(), ret.end(), aux) == ret.end()) {
						ret.push_back(aux);
					}
				}
			}
		}
	}
	for (auto e : ret) {
		out << (int)(get<0>(e) / 60) << ":";
		if (get<0>(e) % 60 == 0) {
			out << "00";
		}
		else {
			out << get<0>(e) % 60;
		}
		out << "->" << (int)(get<1>(e) / 60) << ":";
		if (get<1>(e) % 60 == 0) {
			out << "00";
		}
		else {
			out << get<1>(e) % 60;
		}
		out << endl;
	}
}