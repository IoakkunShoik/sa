
#include "../includes/stdafx.hpp"

using namespace std;

class FileHandler {
private:
  string filePath;
  size_t fileSize;
  ifstream file;

 
public:
  FileHandler(string filePath) {
    (*this).filePath = filePath;
    this->file.open(filePath);
    if (!this->file) {
      cout << "file not open";
    }
  }

   char* getFileContentAsCharArray() {
    this->file.seekg(0, ios::end);
    this->fileSize = this->file.tellg();
    char *fileContent = new char[this->fileSize];
    this->file.seekg(0);
    this->file.read(fileContent, this->fileSize);
    return fileContent;
  }

  static char* getFileContentOnce(string filePath) {
    FileHandler *self = new FileHandler(filePath);
    return self->getFileContentAsCharArray();
  }
};