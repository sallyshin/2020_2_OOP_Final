#ifndef TEXT_VIEW
#define TEXT_VIEW
#include <iostream>
#include <iomanip>
#include "TextData.hpp"
#include <stack>

// header guard to prevent double inclusion

class TextView {
private:
	const int line_per_page = 20;
	int _start_line; /* this is index (starts from zero)*/
	int	_start_word;
	stack<int> _line_stack;
	stack<int> _word_stack;
public:
	TextView() {
		_start_line = 0;
		_start_word = 0;
	}

	void search(TextData const& data, string target) {
		vector<vector<string> > const& text = data.getText();
		/* stack does not support searching */

	}

	void display(TextData const& data) {
		vector<vector<string> > const& text = data.getText(); // vector에 txt 파일 넣어주기
		int line_num = _start_line + 1; // 출력할 line number
		int line_idx = _start_line; // line index
		int word_idx = _start_word; // word index
		while (line_idx < text.size() && line_num < (_start_line + 1 + 20)) {
			size_t n_written = 0;
			cout << setw(to_string(text.size()).size()) << line_num << "| ";
			while (42) {
				/* 해당 line의 마지막에 도달한 경우 */
				if (text[line_idx].size() == word_idx) {
					cout << endl;
					line_num++;
					line_idx++;
					word_idx = 0;
					break;
				} else {
					// 한 line당 75바이트 이하일때
					if (n_written + 1 + text[line_idx][word_idx].size() <= 75) {
						n_written += text[line_idx][word_idx].size();
						cout << text[line_idx][word_idx] << " ";
						word_idx++;
						n_written++;
					}
					else if (n_written + text[line_idx][word_idx].size() <= 75) {
						n_written += text[line_idx][word_idx].size();
						cout << text[line_idx][word_idx] << " ";
						word_idx++;
					} else {
						// 한 line에 75바이트를 넘겼을 때
						line_num++;					
						cout << endl;
						break;
					}
					
				}

			}
		}
	}
	
	/* calculate start_line, start_word of next page */
	void nextPage(TextData const& data) {
		vector<vector<string> > const& text = data.getText();
		int line_printed = 0; /* number of lines printed in screen */
		int n_written = 0;

		// input to stack
		_line_stack.push(_start_line);
		_word_stack.push(_start_word);
		
		// per page
		while (line_printed < 20 && _start_line < text.size()) {
			// 20lines
			if (text[_start_line].size() == _start_word) {
				_start_line++;
				line_printed++;
				_start_word = 0;
			} else { // each line
				if (n_written + 1 + text[_start_line][_start_word].size() <= 75) {
					n_written += text[_start_line][_start_word].size();
					_start_word++;
					n_written++;
				} else if (n_written + text[_start_line][_start_word].size() <= 75) {
					n_written += text[_start_line][_start_word].size();
					_start_word++;
				} else {
					line_printed++;
					n_written = 0;
				}
			}
			// if we don't have next page.
			if (_start_line + 1 == text.size() && _start_word + 1 == text[_start_line].size()) {
				throw "This is last page";
			}
		}
	}

	/* calculate start_line, start_word of prev page */
	void prevPage(TextData const& data) { // 이전 페이지로 이동하는 것
		if (_word_stack.empty()) {
			//_start_line = 0;
			//_start_word = 0;
			throw "This is first page";
		}
		else {
			// input stack
			_start_line = _line_stack.top(); _line_stack.pop();
			_start_word = _word_stack.top(); _word_stack.pop();
		}
	}
};

#endif