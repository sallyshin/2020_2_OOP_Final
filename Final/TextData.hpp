#ifndef TEXT_DATA
#define TEXT_DATA

#include <vector>
#include <string>
using namespace std;

class TextData {
private:
	string _fileName; // 파일을 가져오는 변수
	vector<vector<string> > _text; // 파일을 가져와 string형 벡터에 저장
public:
	TextData(string fileName, vector<vector<string> > text) {
		_fileName = fileName;
		_text = text;
	}
	string const& getFileName() const { //파일을 가져와 리턴
		return _fileName;
	}
	vector<vector<string> > const& getText() const { // 파일을 가져와 string형 벡터로 리턴
		return _text;
	}
	void insert(int line, int index, string word) { // i를 입력했을 때 함수
		_text[line - 1].insert(_text[line - 1].begin() + index, word);
	}

	void remove(int line, int index) { // d를 입력했을 때 함수
		_text[line - 1].erase(_text[line - 1].begin() + index);
	}

	void change(string from, string to) { // c를 를 입력했을 때 함수

		for (int line = 0; line < _text.size(); line++) { // 벡터 길이만큼 반복해서 탐색
			vector<string>::iterator it = _text[line].begin();
			vector<string>::iterator ite = _text[line].end();
		
			while (it != ite) { // 입력한 string으로 바꿔주기
				if (it->compare(from) == 0) {
					*it = to;
				}
				it++; // 다음을 탐색
			}
		}
		
	}
};

#endif