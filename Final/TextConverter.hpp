#ifndef TEXT_CONVERTER
#define TEXT_CONVERTER

#include <fstream>
#include <sstream>
#include "TextData.hpp"

class TextConverter {
public:
	// 텍스트 파일을 불러오는 함수 load
	static TextData load(string fileName) {
		vector<vector<string> > text;
		ifstream readFile;
		string line;
		int line_index = 0;

		// 인자로 입력받은 파일을 열어서 load한다.
		readFile.open(fileName);
		if (readFile.is_open())
		{
			while (!readFile.eof())
			{
				getline(readFile, line);
				text.push_back(vector<string>());

				stringstream ss;
				ss << line;
				string word;
				while (getline(ss, word, ' ')) {
					text[line_index].push_back(word);
				}
				line_index++;
			}
			readFile.close();
		}
		// 정의한 hpp형으로 정보 리턴
		return TextData(fileName, text);
	}

	// 명령어 t를 입력했을 때 저장한 뒤 종료해야 하기 때문에, 저장하기 위해 따로 save라는 함수를 만들어준다.
	static void save(TextData model, string fileName) {
		ofstream writeFile;
		string content;
		vector<vector<string> > const& text = model.getText();

		writeFile.open(fileName);
		// 파일을 열어서 해당 정보를 새로 write해주면서 해당 파일에 새로 저장한다.
		if (writeFile.is_open()) {
			for (int line_idx = 0; line_idx < text.size(); line_idx++) {
				for (int word_idx = 0; word_idx < text[line_idx].size(); word_idx++) {
					content.append(text[line_idx][word_idx]);
					if (word_idx == text[line_idx].size() - 1) {
						content.append("\n");
					} else {
						content.append(" ");
					}
				}
			}
			writeFile.write(content.c_str(), content.size());
			writeFile.close();
		}
	}
};

#endif