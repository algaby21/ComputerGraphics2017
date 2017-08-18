#pragma once
#include <string>

using namespace std;

class InputFile {
	private:
		string _contents;
	public:
		bool Read(string filename);
		string GetContents();
};