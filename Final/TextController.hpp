#ifndef TEXT_CONTROLLER
#define TEXT_CONTROLLER

#include "TextData.hpp"
#include "TextConverter.hpp"
#include "TextView.hpp"
#include <cstdlib>


class TextController {
 private:
	 TextData test;
	 TextView view;
 public:
	 TextController() : test(TextConverter::load("test.txt")) { // txt파일인 test를 load해서
	}
	void run() {
		while (10) {
			//계속 반복해서 진행하다 t를 만나면 종료
			view.display(test);
			string line = "===========================================================================";
			string input;
			cout << line << endl;
			cout << "n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료" << endl;
			cout << line << endl;
			while (true) {
				try {
					cout << "입력: ";
					cin >> input;
					executeCommand(input);
					break;
				}
				catch (const char* msg) {
					cout << msg << endl;
				}
				catch (invalid_argument& exception) {
					//다른 명령어를 입력했을 때 나오는 오류 
					cout << "invalid argument." << endl;
				}
				catch (...) {
					// 다른 나머지 명령어들은 에러가 발생했다고 오류발생
					cout << "Unknown error occurred." << endl;
				}
			}

			cout << line << endl;
		}
	}
	//split함수를 이용해서 ,를 기준으로 함수로 전달된 인자를 나눠 저장
	vector<string> split(string st, char delimiter) {
		vector<string> inter;
		stringstream ss(st);
		string tmp;

		while (getline(ss, tmp, delimiter)) {
			inter.push_back(tmp);
		}
		return inter;
	}

	/*
	*	<spec>(digit, digit, word)
	*	<spec>(digit, digit)
	*	<spec>(word)
	*	<spec>(word, word)
	*	<spec>
	*/
	void executeCommand(string command) {
		// 만든 함수를 실행하는 함수 
		string str;
		str = command;

		char com = str.at(0);

		if (str.size() == 1) {
			if (com == 't') {
				// 변경파일저장
				TextConverter::save(test, "test.txt");
				// 종료
				exit(0);
			}
			else if (com == 'n') {
				// 다음 페이지 출력
				view.nextPage(test);
			}
			else if (com == 'p') {
				// 이전 페이지 출력
				view.prevPage(test);
			}
			else {
				// 다른 명령어를 입력하면 예외를 발생시킨다
				throw "Try again.";
			}
			return;
		}


		if (str.size() < 2) {
			// 페이지를 넘기는 것 이외의 명령어를 입력했을 떄 입력한 길이가 1이하이면 예외 발생 
			throw "Wrong input. Try again";
		}
		// str.at(1)이 가능하려면 str.size() >= 2임이 보장되어야 함
		// str.at(str.length() - 1)이 가능하려면 str.size() - 1 >= 0임이 보장되어야 함
		if (str.at(1) != '(' && str.at(str.length() - 1) != ')') {
			throw "invalid command. Try again";
			//다시입력요구
		}

		// 인자 세개 입력받아와서
		str.erase(str.begin()); // 명령어 삭제
		str.erase(str.begin()); // 괄호 삭제
		str.erase(str.end() - 1); // 괄호 삭제

		if (com == 'i') {
			vector<string> line = split(str, ',');
			//line.size() 검증 (== 3)
			if (line.size() != 3) {
				throw "Wrong input. Try again.";
			}

			test.insert(stoi(line[0]), stoi(line[1]), line[2]);
		}
		else if (com == 'd') {
			if (str.size() < 1) {
				throw "Wrong input. Try again";
			}

			vector<string> line = split(str, ',');
			//line.size() 검증 (== 2)
			if (line.size() != 2) {
				throw "Wrong input. Try again.";
			}

			test.remove(stoi(line[0]), stoi(line[1]));
		}
		else if (com == 's') {
			vector<string> line = split(str, ',');
			//line.size() 검증 (== 3)
			if (line.size() != 1) {
				throw "Wrong input. Try again.";
			}
		}
		else if (com == 'c') {
			vector<string> line = split(str, ',');
			if (line.size() != 2) {
				throw "Wrong input. Try again";
			}
			test.change(line[0], line[1]);
		}
		else {
			throw "Wrong command. Try again.";
		}
	}
};

#endif