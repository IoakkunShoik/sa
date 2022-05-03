#include "includes/stdafx.hpp"
#include "includes/FileHandler.hpp"
using namespace std;

int main() {
    FileHandler *fileHandler = new FileHandler("inputFiles/test1.json");
    stack <char> test;
    test.push('{');
    test.push('[');
    test.push('(');
    
    cout << test.top();
    test.pop();
    cout << test.top();
    test.pop();
    cout << test.top();
}