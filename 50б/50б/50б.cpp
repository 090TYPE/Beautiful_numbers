#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;
/// Удаляет незначащие нули в начале строки
void removeStartZeros(string& s) {
	if ((s.size() != 0) && (s[0] == '0')) {
		s.erase(s.begin(), find_if(s.begin(), s.end(), [](char c)->bool {return c != '0'; }));
	}
}

void removeEndZeros(string& s) {
	if (s.size() == 0)
		return;
	if (s.find('.') == -1)
		return;
	//Работаем далее только если данное число - дробное
	while (s[s.size() - 1] == '0')
		s.erase(s.size() - 1);
}

/// Удаляет незначащие нули (в начале и конце строки), а также разделитель (точку) если он находится в конце строки
void removalOfExcess(string& s) {
	removeStartZeros(s);
	removeEndZeros(s);
	//Удаляем точку, если она в конце строки
	if (s.size() != 0)
		if (s[s.size() - 1] == '.')
			s.erase(s.size() - 1);
}

void periodicTransform(string& s) {
	auto n = s.find('.');
	if (n == -1)
		return;
	auto sub = s.substr(n + 1);
	bool isEqual = true;
	char c = sub[0];
	for (auto& i : sub)
		if (i != c) {
			isEqual = false;
			break;
		}
	if (isEqual) {
		s.erase(n + 1);
		s += "(";
		s += c;
		s += ")";
	}
}

void addFirstZero(string& s) {
	if (s.size() != 0)
		if (s[0] == '.')
			s = "0" + s;
}

string slice(string& controlLine, char k) {
	string result;
	for (auto& i : controlLine)
		if (i == '.')
			result += '.';
		else if (i != '0') {
			result += k;
			--i;
		}
		else
			result += '0';
	periodicTransform(result);
	addFirstZero(result);
	removalOfExcess(controlLine);
	return result;
}

/// Вычисяет строку-результат решения задачи
string calcNiceNumbers(size_t val, size_t k) {
	double value = val;
	double d = value / k;
	stringstream ss;
	ss << setiosflags(ios::fixed);
	ss.precision(15);
	ss << d;

	string controlLine = ss.str();
	removalOfExcess(controlLine);
	if ((controlLine.find('.') != -1) && (controlLine.size() > 15))
		controlLine.erase(controlLine.size() - 1);
	removalOfExcess(controlLine);
	string result;
	char kChar = '0' + k;
	while (controlLine.size() != 0) {
		if (result.size() != 0)
			result += "+";
		result += slice(controlLine, kChar);
	}
	return to_string(val) + "=" + result;
}

/// Запрашивает натуральное число
///Возвращает true в случае удачного считывания, иначе false
bool getCorrectValue(size_t& value) {
	bool isCorrect = false;
	string str;
	cin >> str;
	if (str.size() == 0)
		return false;
	else {
		for (auto& i : str)
			if (!isdigit(i))
				return false;
	}
	stringstream ss(str);
	ss >> value;
	if (value == 0)
		return false;
	return true;
}

int main() {
	setlocale(LC_ALL, "RU");
	cout << "ведите красивые числа\n";
	size_t value, k;
	bool isCorrect;
	bool isFirstAttempt = true;
	do {
		if (!isFirstAttempt)
			cout << "вы ввели не те значения попробуйте снова\n";
		else
			isFirstAttempt = false;
		isCorrect = true;
		isCorrect &= getCorrectValue(value);
		isCorrect &= getCorrectValue(k);
		if (k >= 10)
			isCorrect = false;
	} while (!isCorrect);

	cout << calcNiceNumbers(value, k);

	return 0;
}
