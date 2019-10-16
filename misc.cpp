#include "misc.h"



#ifdef _WIN32
void clearScreen() {
	system("cls"); system("cls");
}
#endif

#ifdef linux
void clearScreen() {
	system("clear"); system("clear");
}
#endif

vector<string> vectorString(string stringToVectorize, string separador) {
	vector<string> ret;
	size_t startPos = 0, endPos = 0;
	while (endPos < stringToVectorize.length()) {
        endPos = stringToVectorize.find(separador, startPos);
		if (endPos == stringToVectorize.npos) {
			ret.push_back(stringToVectorize.substr(startPos));
			break;
		}
		else {
			ret.push_back(stringToVectorize.substr(startPos, endPos - startPos));
		}
		startPos = endPos + separador.length();
	}
	if (ret.size() >= 3) {
		if (ret[2].size() == 0) {
			ret[2] = "-";
		}
	}
	return ret;
}

void clearBuffer(void) {
	cin.clear();
	cin.ignore(1000, '\n');
}

bool strIsNumber(string str) {
	if (str.size() == 0) {
		return false;
	}
	for (unsigned i = 0; i < str.length(); i++) {
		if (!isdigit(str[i])) {
			if (str[i] != '.') {
				return false;
			}
		}
	}
	return true;
}
