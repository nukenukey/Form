#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

//H:\proj\form\form.cpp
// libraries will be in /usr/lib/form
//TODO
//packages
//	i think will be fun :>
//  test packages
//test sorter
//test scanner class
//	like multiple spaces, multiple lines, things like that
//	multiple line trimming will make giving the error message
//	line number difficult so maybe just make smarter .nextLine()
//	make it skip multiple lines
//	maybe make a .smartNextLine() that will return the next non
//	blank line?
//were doing static types now :>

class scanner {
//also make sure that this actually works reliably
public:
	string cont;
	int ind = 0;
	scanner(string in) {
		cont = in;
	}
	bool hasNextLine() {
		for (int i = ind; i < cont.length(); i++) {
			if (cont.substr(i, 1).compare("\n") == 0) {
				return true;
			}
		}
		return false;
	}
	void eatNextLine() {
		//consumes line and adds to ind
		for (int i = ind; i < cont.length(); i++) {
			if (cont.substr(i, 1).compare("\n") == 0) {
				ind += i;
				break;
			}
		}
	}
	string nextLine() {
		for (int i = ind; i < cont.length(); i++) {
			if (cont.substr(i, 1).compare("\n") == 0) {
				return cont.substr(ind, ind - i);
			}
		}
		return "";
	}
	bool hasNext(string in) {
		for (int i = ind; i < cont.length(); i++) {
			if (cont.substr(i, in.length()).compare(a) == 0) {
				return true;
			}
		}
		return false;
	}
	void eatNext(string in) {
		for (int i = ind; i < cont.length(); i++) {
			if (cont.substr(i, in.length()).compare(in) == 0) {
				ind += i;
			}
		}
	}
	//does .next("\s") work if there are two spaces?
	//maybe trim multiple spaces?
	//will make error messages wierd bc i wanna give line number :/
	string next(string in) {
		for (int i = ind; i < cont.length(); i++) {
			if (cont.substr(i, in.length()).compare == 0) {
				return cont.substr(ind, ind - i);
			}
		}
	}
	bool hasNextChar() {
		if (ind < cont.length()) {
			return true;
		}
		else {
			return false;
		}
	}
	void eatNextChar() {
		ind++;
	}
	char nextChar() {
		return char(cont.substr(ind, 1));
	}
	void restart() {
		ind = 0;
	}
	int index() {
		return ind;
	}
};
using namespace std;
string cont;
string scope = "";
int main(int argc, char** argv) {
	bool outP = false;
	bool packA = false;
	bool showH = false;
	bool showL = false;
	bool showS = false;
	bool showC = false;
	for (int i = 0; i < argc; i++) {
		string temp = argv[i];
		if (temp.substr(0, 1).compare("-") == 0) {
			for (int j = 1; j < temp.length(); j++) {
				switch (char(temp.substr(j, 1))) {
				case 'p':
					packA = true;
				case 'o':
					outP = true;
					break;
				case 'h':
					showH = true;
					break;
				case 'l':
					showL = true;
					break;
				case 's':
					showS = true;
					break;
				case 'c':
					showC = true;
					break;
				}
			}
		}
	}
	if (outP) {
		ifstream oldFile(argv[1]);
		ofstream newFile(argv[0]);
		vector<vector<string>> lines = tokener(oldFile);
		oldFile.close();
		if (showH) {
			for (string line : lines)
				cout << line << endl;
		}
		vector<string> lexed = lexer(lines);
		if (showL) {
			for (string line : lexed)
				cout << line << endl;
		}
		vector<string> sorted = sorter(lexed);
		if (showS) {
			for (string line : sorted)
				cout << line << endl;
		}
		vector<string> comped = comp(sorted, newFile);
		if (showC) {
			for (string line : comped)
				cout << line << endl;
		}
		for (string line : comped)
			newFile << line << endl;
	}
}
int sep(string line) {
	for (int i = 0; i < line.length(); i++) {
		if (line.substr(i, 1).compare(" ") == 0) {
			while (line.substr(i + 1, 1).compare(" ") == 0) {
				line = line.substr(0, i) + line.substr(i + 2);
			}
		}
	}
	int ret = 0;
	for (int i = 0; i < line.length(); i++) {
		if (line.substr(i, 1).compare(" ") == 0) {
			ret++;
		}
	}
	return ret;
}
vector<string> newTokens(ifstream oldFile) {
	string[] keys = { "string", "=", "fun", "(", ")", "exit", "println", "/" };
	int lineC = 0;
	for (string line; getline(oldFile, line); lineC++) {}
	vector<string> ret("", lineC);
	lineC = 0;
	for (string line; getline(oldFile, line); lineC++) {
		for (scanner lineI(line); lineI.hasNext(" "); string ex = lineI.next(" ")) {

		}
	}
}














vector<vector<string>> tokener(ifstream oldFile) {
	int lineC;
	int maxlen = 0;
	string line;
	for (lineC = 0; getline(oldFile, line); lineC++) {
		if (sep(line) > maxlen) {
			maxlen = sep(line);
		}
	}
	vector<vector<string>> ret(lineC, vector<string>(maxlen, ""));
	string[] spec = { "=", "/", "(", ")", ";" };
	while (getline(oldFile, line)) {
		for (; line.substr(0, 1).compare(" ") == 0 || line.substr(0, 1).compare("\t") == 0; line = line.substr(1)) {}
		for (int i = 0; i < line.length(); i++) {
			for (int j = 0; j < sizeof(spec) / sizeof(string); j++) {
				if (line.substr(j, 1).compare(spec[j]) == 0) {
					line = line.substr(0, j) + " " + spec[j] + " " + line.substr(j + 1);
				}
			}
		}
		for (int i = 0; i < line.length(); i++) {
			if (line.substr(i, 1).compare(" ") == 0) {
				if (line.substr(i + 1, 1).compare(" ") == 0) {
					line = line.substr(0, i) + 
				}
			}
		}
		for (scanner lineI(line); lineI.hasNext(" "); ret[lineC].push_back(lineI.next(" "))) {}
		lineC++;
	}
	return ret;
}
vector<string> handle(ifstream oldFile) {
//also needs multiple line trimming
//and multiple space trimming
//and also dont insert space in it isnt needed
//bunch of todo
	string line;
	string[] spec = { "=", "/", "(", ")", ";"};
	while (getline(oldFile, line)) {
		for (; line.substr(0, 1).compare(" ") == 0 || line.substr(0, 1).compare("\t") == 0; line = line.substr(1)) {}
		for (int i = 0; i < line.length(); i++) {
			for (int j = 0; j < sizeof(spec) / sizeof(string); j++) {
				if (line.substr(i, spec[j].length()).compare(spec[j]) == 0) {
					line = line.substr(0, i) + "\s" + line.substr(i);
					line = line.substr(0, i + 2) + "\s" + line.subtr(i + 2);
//check that this actualy works in a different program
//maybe make a fluff function?
				}
			}
		}
		cont += line;
	}
	int c = 0;
	for (int i = 0; i < cont.length(); i++) {
		if (cont.substr(i, 1).compare("\n") == 0) {
			c++;
		}
	}
	line = "";
	vector<string> lines(i, "");
	while (getline(cont, line)) {
		lines.push_back(line);
	}
	return lines;
}
vector<string> lexer(vector<vector<string>> lines) {
	vector<string> ret(lines.size(), "");
	for (int i = 0; i < lines.size(); i++) {
		vector<string> line(lines[i]);
		for (int j = 0; j < line.size(); j++) {
			if (line[0].compare("string") == 0) {
				ret.push_back("string_" + line[1] + "_" + line[4] + "_");
				continue;
			}
			if (line[0].compare("fun") == 0) {
				ret.push_back("funcDef_" + line[1] + "_");
				continue;
			}
			if (line[0].compare("println") == 0) {
				ret.push_back("printLine_" + line[3] + "_");
				continue;
// TODO make this not suck
			}
			if (line[0].compare("exit") == 0) {
				ret.push_back("exitProg_" + line[1] + "_");
				continue;
			}
			if (line[0].compare("import") == 0) {
				ret.push_back("import_" + line[1] + "_");
				continue;
			}
			if (line[0].compare("read") == 0) {
				ret.push_back("readTo_" + line[1]);
				continue;
			}
			else {
				cerr << "unknown token at line " << i << ": " << line[j] << endl;
				exit(1);
			}
		}
	}
	return ret;
}
vector<string> sorter(vector<string> lines) {
	int varl = 0;
	int funcl = 0;
	int imptl = 0;
	for (int i = 0; i < lines.size(); i++) {
		string ex = lines[i].substr(0, lines[i].find("_", 0));
		if (ex.compare("varDef") == 0) {
			varl++;
		}
		else if (ex.compare("import") == 0) {
			imptl++;
		}
	}
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].substr(0, lines[i].find("_")).compare("funcDef") == 0) {
			for (int j = i; j < lines.size(); j++) {
				funcl++;
				if (lines[j].substr(0, lines[i].find("_", 0)).compare("scopeEnd_")) {
					i += j;
					j = lines.size() - 1;
					continue;
				}
			}
		}
	}
	varl += 2;
	vector<string> varlines(varl, "");
	if (varl != 2) {
		varlines.push_back("varDefStart_");
	}
	vector<string> funclines(funcl, "");
	funclines.push_back("funcDefStart_");
	vector<string> importlines(imptl, "");
	for (int i = 0; i < lines.size(); i++) {
		string ex = lines[i].substr(0, lines[i].find("_", 0));
		if (ex.compare("varDef") == 0) {
			varlines.push_back(lines[i]);
		}
		else if (ex.compare("funcDef") == 0) {
			funclines.push_back(lines[i]);
			for (int j = i + 1; j < lines.size(); j++) {
				funclines.push_back(lines[j]);
				if(lines[j].substr(0, lines[j].find("_", 0)).compare("funcDefEnd") == 0){
					i += j;
					j = lines.size();
				}
			}
		}
	}
	varlines.push_back("varDefEnd_");
	vector<string> ret(varlines.size() + funclines.size() + importlines.size());
	int ind = 0;
	for (int i = 0; i < varlines.size(); i++)
		ret[i] = varlines[i];
	ind += varlines.size();
	for (int i = 0; i < funclines.size(); i++)
		ret[i + ind] = funclines[i];
	ind += funclines.size();
	for (int i = 0; i < importlines.size(); i++)
		ret[i + ind] = importlines[i];
	return ret;
}
vector<string> comp(vector<string> lines, ofstream newFile) {
	for (int i = 0; i < lines.size(); i++) {
		scanner lineI(lines[i]);
		string ex = lineI.next("_");
		lineI.eatNext("_");
		if (ex.compare("varDefStart")) {
			newFile << "section .data\n";
		}
		else if (ex.compare("string")) {
			lineI.eatNext("_");
			newFile << lineI.next("_") << " db ";
			lineI.eatNext("_");
			newFile << lineI.next("_") << ", 0xa" << endl;
			lineI.restart();
			lineI.eatNext("_");
			newFile << lineI.next("_") << "/ db $ - " << lineI.next("_") << endl;
		}
		else if (ex.compare("varDefEnd")) {
			newFile << "section .text" << endl;
			newFile << "global _start" << endl;
		}
		else if (ex.compare("mainDefStart")) {
			newFile << "_start:" << endl;
		}
		else if (ex.compare("exitProg")) {
			lineI.eatNext("_");
			newFile << "mov eax, 1" << endl;
			newFile << "mov ebx, " << lineI.next("_") << endl;
			newFile << "int 0x80" << endl;
			continue;
		}
		else if (ex.compare("scopeEnd") == 0) {
			//this is more important when local variables and stack comes in
		}
		else if (ex.compare("funcCall")) {
			lineI.eatNext("_");
			newFile << lineI.next("_") << endl;
//handle params :<
		}
		else if (ex.compare("funcDef")) {
			lineI.eatNext("_");
			newFile << lineI.next("_");
		}
		else if (ex.compare("printLine")) {
			newFile << "mov eax, 4" << endl;
			newFile << "mov ebx, 1" << endl;
			newFile << "mov ecx, " << lineI.next("_") << endl;
			newFile << "mov edx, " << lineI.next("_") << "/" << endl;
			newFile << "int 0x80" << endl;
		}
		else if (ex.compare("import") == 0) {
			lineI.eatNext("_");
			importEngine(lineI.next("_"));
		}
		else if (ex.compare("readTo") == 0) {
			lineI.eatNext("_");
			newFile << "mov eax, 3" << endl;
			newFile << "mov ebx, 0" << endl;
			newFile << "mov ecx, " << lineI.next("_") << endl;
			newFile << "mov edx, " << lineI.next("_") + "/" << endl;
			newFile << "int 0x80" << endl;
		}
	}
}
// import libs are in /usr/lib/form/
// 2 main families /usr/lib/form/form
// and /usr/lib/form/system
void importEngine(string ref, ofstream newFile) {
	string filepath = "/usr/lib/form/";
	string name = ref;
	for (int i = 0; i < ref.length(); i++) {
		if (ref.substr(i, 1).compare(".") == 0) {
			filepath += ref.substr(0, i);
			ref = ref.substr(i);
		}
	}
	ifstream file(filepath, std::ifstream::binary);
	if (!file.is_open()) {
		cerr << "error opening import file " << name << " at path " << path << endl;
		exit(1);
	}
	vector<string> ret("", file_size(path(filepath) / sizeof(string)));
	for (int i, ind = 0; i < ret.capacity(); i++) {
		if (file_size(path(filepath)) - ind > sizeof(string) {
			ret[i] = file.seekg(ind, sizeof(string));
		}
		else {
			ret[i] = file.seekg(ind, file.end);
		}
// i have no fukin clue if this works or not
// maybe filter out metadata if i put that in idk
	}
	for (int i = 0; i < ret.size(); i++) {
		newFile << ret[i];
	}
}