#ifndef TEXT_CONVERTER
#define TEXT_CONVERTER

#include <fstream>
#include <sstream>
#include "TextData.hpp"

class TextConverter {
public:
	// �ؽ�Ʈ ������ �ҷ����� �Լ� load
	static TextData load(string fileName) {
		vector<vector<string> > text;
		ifstream readFile;
		string line;
		int line_index = 0;

		// ���ڷ� �Է¹��� ������ ��� load�Ѵ�.
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
		// ������ hpp������ ���� ����
		return TextData(fileName, text);
	}

	// ��ɾ� t�� �Է����� �� ������ �� �����ؾ� �ϱ� ������, �����ϱ� ���� ���� save��� �Լ��� ������ش�.
	static void save(TextData model, string fileName) {
		ofstream writeFile;
		string content;
		vector<vector<string> > const& text = model.getText();

		writeFile.open(fileName);
		// ������ ��� �ش� ������ ���� write���ָ鼭 �ش� ���Ͽ� ���� �����Ѵ�.
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