#include "../includes/stdafx.hpp"

using namespace std;

class JsonParser {
private:
  string jsonString;
  vector <string> currentKey;
  stack <char> openBlocks;
  enum mode {
    openObject,       //{}
    openKeyQuote,     // key
    keyDefined,       // after :
    openValueQuote,   // value
    openArray,        //[]
    openArrayElement, //[""<-]

    aborting,
    error
  };
  int currentMode;
  map<string, string> jsonKeyValueMap;

  void parseJson() {
    for (unsigned long int letterKey = 0;
         letterKey <= this->jsonString.length(); letterKey++) {
      if (this->currentMode == mode::error) {
        this->jsonKeyValueMap.clear();
        cout << "error: incorrect json format";
        return;
      }
      if (this->currentMode != mode::aborting)
        this->processLetter(this->jsonString[letterKey]);
    }
  }

  void processLetter(char letter) {
    switch (letter) {
    case '{':
    case '[':
      this->openBlock(letter);
      break;
    case '}':
    case ']':
      this->closeBlock(letter);
      break;
    case '"':
      this->quoteBlockHandler(letter);
      break;
    case ':':
      cout << "=>";
      break;
    default:
      this->keyValueModesHandle(letter);
    }
  }

  void keyValueModesHandle(char letter) {
    if (this->currentMode == mode::openKeyQuote) {
      //this->currentKey[this->currentLevel()].push_back(letter);
    }
  }

  void quoteBlockHandler(char letter) {
    if (letter != '"') {
      this->currentMode = mode::error;
      return;
    }
    switch (this->currentMode) {
    case mode::openKeyQuote:
    case mode::openValueQuote:
      this->closeBlock(letter);
      // Change mode is not required, couse closeBlock call refresh
      break;
    case mode::openObject:
      this->openBlock(letter);
      this->currentMode = mode::openKeyQuote;
      this->openBlocks.push(letter);
      break;
    case mode::openArray:
    case mode::keyDefined:
      this->openBlock(letter);
      this->currentMode = mode::openValueQuote;
      this->openBlocks.push(letter);
    }
  }

  void openBlock(char letter) {
    switch (letter) {
    case '{':
      cout << " <object_open> ";
      this->openBlocks.push(letter);
      this->refreshMode();
      break;
    case '[':
      cout << " <array_open> ";
      this->openBlocks.push(letter);
      this->refreshMode();
      break;
    case '"':
      cout << " <quotes_open> ";
      break;
    default:
      cout << "error: unknown brackets";
      this->currentMode = mode::error;
    }
  }

  void refreshMode() {
    if (this->openBlocks.empty()) {
      this->currentMode = mode::aborting;
      return;
    }
    switch (this->openBlocks.top()) {
    case '{':
      this->currentMode = mode::openObject;
      break;
    case '[':
      this->currentMode = mode::openArray;
      break;
    case '"':
      break;
    default:
      cout << "error: unknown brackets";
      this->currentMode = mode::error;
    }
  }

  void closeBlock(char letter) {
    char lastOpenBlockType = this->openBlocks.top();
    switch (letter) {
    case '}':
      cout << " <close_object> ";
      break;
    case ']':
      cout << " <close_array> ";
      break;
    case '"':
      cout << " <close_quotes> ";
      break;
    default:
      cout << "error: unknown brackets";
      this->currentMode = mode::error;
    }
    this->openBlocks.pop();
    this->refreshMode();
  }

  void checkClosingObject(char letter) {
    char lastOpenBlockType = this->openBlocks.top();
    if (lastOpenBlockType == '{' && letter != '}' ||
        lastOpenBlockType == '[' && letter != ']' ||
        lastOpenBlockType == '"' && letter != '"') {

      cout << "error: incorrect brackets";
      this->currentMode = mode::error;
    }
  }

  int currentLevel() { return this->openBlocks.size(); }

public:
  JsonParser(string jsonString) {
    this->jsonString = jsonString;
    this->parseJson();
  }
};