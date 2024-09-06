#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class scanner{
  public:
  string cont;
  int ind;
  scanner(string in){
    cont = in;
    ind = 0;
  }
  bool hasNext(){
    for(int i = ind; i < cont.length(); i++){
      if(cont.substr(i,1).compare(" ") == 0){
        return true;
      }
    }
    return false;
  }
  bool hasNextLine(){
    for(int i = ind; i < cont.length(); i++){
      if(cont.substr(i,1).compare("\n") == 0){
        return true;
      }
    }
    return false;
  }
  string next(){
    for(int i = ind; i < cont.length(); i++){
      if(cont.substr(i,1).compare(" ") == 0){
	ind += i;
        return cont.substr(ind, i-ind);
      }
    }
    return "";
  }
  string nextLine(){
    for(int i = ind; i < cont.length(); i++){
      if(cont.substr(i,1).compare("\n") == 0){
	ind += i;
        return cont.substr(ind, i-ind);
      }
    }
    return "";
  }
  void reset(){
    ind = 0;
  }
};
struct node{
  string data;
  int ind;
  struct node* next;
  struct node* prev;
};

int indexOf(string line, string eh){
  for(int i = 0; i < line.length(); i++){
    if(line.substr(i, eh.length()).compare(eh) == 0){
      return i;
    } 
  }
  return -1;
}


bool showoldcont = false;
bool showlexedcont = false;
bool showsortedcont = false;
bool showcommited = false;
string cont = "";
int main(int argc, char* argv[]){
  for(int i = 0; i < 3; i++){
    if(argv[i].substr(0, 1).compare("-") == 0){
      string mods = argv[i];
      for(int j = 0; j < sizeof(mods)/sizeof(char*); j++){
        if(mods.substr(j, 1).compare("o") == 0){
          showoldcont = true;
	}else if(mods.substr(j, 1).compare("l") == 0){
          showlexedcont = true;
	}else if(mods.substr(j, 1).compare("s") == 0){
          showsortedcont = true;
	}else if(mods.substr(j, 1).compare("c") == 0){
          showcommited = true;
	}
      }
    }else{
      if(i == 0){
        ifstream oldFile(argv[1]);
	string line;
	while(getline(oldFile, line)){
          cont += line;
	}
	oldFile.close();
	ofstream newFile(argv[2]);
	handle();
	lexer(newFile);
      }
    }
  }
}
bool stringCheck(string single){
  string specs[] = {"\'", "\"", "[", "]", ".", "~", "+", "=", "-", "*", "%", "(", ")", "!", ","}
  for(int i = 0; i < specs.length(); i++){
    if(single.compare(specs[i]) == 0){
      return true;
    }
  }
  return false;
}
void handle(){
  for(int i = 0; i < cont.length(); i++){
    if(stringCheck(cont.substr(i,1)) == true){
      cont = cont.substr(0,i) + " " + cont.substr(i+1);
      cont = cont.substr(0,i+1) + " " + cont.substr(i+2);
    }
  }
  for(int i = 0; i < cont.length(); i++){
    if(cont.substr(i,1).compare(";") == 0){
      cont = cont.substr(0,i) + cont.substr(i+1);
    }
  }
}
void lexer(ofstream newFile){
  int lineC = 0;
  scanner contI(cont);
  while(contI.hasNextLine()){
    contI.nextLine();
    lineC++;
  }
  string lines[lineC];
  lineC = 0;
  contI.reset();
  while(contI.hasNextLine()){
    string line = contI.nextLine();
    scanner lineI(line);
    string ex = lineI.next();
    if(ex.compare("var") == 0){
      lines[lineC] = "varDef_";
      string next = lineI.next();
      if(next.compare("string") == 0){
        lines[lineC] += "stringDef_";
      }
      lines[lineC] += lineI.next();
    }else if(ex.compare("fun") == 0){
      lines[lineC] = "funcDef_";
      lines[lineC] += lineI.next() + "_";
//parameters dont exist rn
    }else if(ex.compare("exit") == 0){
      lines[lineC] = "progEnd_";
      lines[lineC] += lineI.next() + "_";
    }else if(ex.compare("/") == 0){
      lines[lineC] = "funcDefEnd_";
    }else{
//funcCalls
      bool eh;
      for(int i = 0; i < line.length(); i++){
        if(line.substr(i,1).compare("(") == 0){
          eh = true;
	  break;
	}
      }
      if(eh){
        lines[lineC] = "funcCall_";
        lineI.next();
        string next = lineI.next() + "_";
        while(next.compare(")") != 0){
          lines[lineC] += next + "_";
  	  next = lineI.next();
        }
      }else{
        err(line, lineC);
      }
      lineC++;
    }
    sorter(lines, newFile);
  }
}
void err(string line, int lineN, string comment){
  cerr << line << endl;
  cerr << "error on line " << lineN << endl;
  exit(1);
}
void sorter(string lines[], ofstream newFile){
  int vars = 0;
  int func = 0;
  int main = 0;
  bool infunc = false;
  for(int i = 0; i < sizeof(lines)/sizeof(string); i++){
    string ex = lines[i].substr(0, lines[i].indexOf("_"));
    if(ex.compare("varDef") == 0){
      vars++;
    }else if(ex.compare("funcDef") == 0){
      string line = lines[i];
      line = line.substr(line.indexOf("_")+1);
      ex = line.substr(0, line.indexOf("_"));
      if(ex.compare("main") == 0){
	i++;
        while(true){
          string line = lines[i];
	  string ex = line.substr(0, line.indexOf("_"));
	  main++;
	  if(ex.compare("funcDefEnd")){
	    break;
	  }
        }
      }else{
        i++;
	while(true){
          string line = lines[i];
	  string ex = line.substr(0, line.indexOf("_"));
	  func++;
	  if(ex.compare("funcDefEnd")){
            break;
	  }
	}
      }
    }
  }
  vars++;
  string varlines[vars];
  string funclines[func];
  string mainlines[main];
  varlines[0] = "varDefStart_";
  for(int lineC = 0; lineC < sizeof(lines)/sizeof(string); lineC++){
    string line = lines[lineC];
    string ex = line.substr(0, line.indexOf("_"));
    if(ex.compare("varDef") == 0){
      for(int i = 0; i < sizeof(varlines)/sizeof(string); i++){
        if(varlines[i].compare("") == 0){
          varlines[i] = line;
	}
      }
    }else if(ex.compare("funcDef") == 0){
      line = line.substr(line.indexOf("_")+1);
      ex = line.substr(0, line.indexOf("_"));
      if(ex.compare("main") == 0){
        while(true){
	  line = lines[lineC];
	  ex = line.substr(0, line.indexOf("_"));
          mainlines[lineC] = line;
	  lineC++;
	  if(ex.compare("funcDefEnd") == 0){
            break;
	  }
	}
      }else{
        while(true){
          line = lines[lineC];
	  ex = line.substr(0, line.indexOf("_"));
	  funclines[lineC] = line;
	  lineC++;
	  if(ex.compare("funcDefEnd") == 0){
            break;
	  }
	}
      }
    }
//rtbm
  }
}
void comp(string lines[], ofstream newFile){
  newFile << "section .text" << endl;
  newFile << "global _start" << endl;
  newFile << "_start:" << endl;
  for(int i = 0; i < sizeof(lines)/sizeof(string); i++){
    string line = lines[i];
    string ex = line.substr(0, line.indexOf("_"));
  }
}
