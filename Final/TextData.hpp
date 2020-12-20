#ifndef TEXT_DATA
#define TEXT_DATA

#include <vector>
#include <string>
using namespace std;

class TextData {
private:
	string _fileName; // ������ �������� ����
	vector<vector<string> > _text; // ������ ������ string�� ���Ϳ� ����
public:
	TextData(string fileName, vector<vector<string> > text) {
		_fileName = fileName;
		_text = text;
	}
	string const& getFileName() const { //������ ������ ����
		return _fileName;
	}
	vector<vector<string> > const& getText() const { // ������ ������ string�� ���ͷ� ����
		return _text;
	}
	void insert(int line, int index, string word) { // i�� �Է����� �� �Լ�
		_text[line - 1].insert(_text[line - 1].begin() + index, word);
	}

	void remove(int line, int index) { // d�� �Է����� �� �Լ�
		_text[line - 1].erase(_text[line - 1].begin() + index);
	}

	void change(string from, string to) { // c�� �� �Է����� �� �Լ�

		for (int line = 0; line < _text.size(); line++) { // ���� ���̸�ŭ �ݺ��ؼ� Ž��
			vector<string>::iterator it = _text[line].begin();
			vector<string>::iterator ite = _text[line].end();
		
			while (it != ite) { // �Է��� string���� �ٲ��ֱ�
				if (it->compare(from) == 0) {
					*it = to;
				}
				it++; // ������ Ž��
			}
		}
		
	}
};

#endif