using namespace std;

class FileHandler {
private:
  string filePath;
  ifstream file;

  string getBlock(){
      
  }
public:
  FileHandler(string filePath) { 
      (*this).filePath = filePath;
      file.open(filePath);
      if(!file) {
          cout << "file not open";
      }
  }
//   string getValues() {

//   }
};