#include "includes/FileHandler.hpp"
#include "includes/JsonParser.hpp"
#include "includes/stdafx.hpp"
using namespace std;

int main() {
  string fileContent(FileHandler::getFileContentOnce("inputFiles/test1.json"));
  JsonParser *tmp = new JsonParser(fileContent);
  cout << "'stop'";
}

// stack<char> test;
//   test.push('{');
//   test.push('[');
//   test.push('(');

//   cout << test.top();
//   test.pop();
//   cout << test.top();
//   test.pop();
//   cout << test.top();