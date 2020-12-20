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
	 TextController() : test(TextConverter::load("test.txt")) { // txt������ test�� load�ؼ�
	}
	void run() {
		while (10) {
			//��� �ݺ��ؼ� �����ϴ� t�� ������ ����
			view.display(test);
			string line = "===========================================================================";
			string input;
			cout << line << endl;
			cout << "n:����������, p:����������, i:����, d:����, c:����, s:ã��, t:����������" << endl;
			cout << line << endl;
			while (true) {
				try {
					cout << "�Է�: ";
					cin >> input;
					executeCommand(input);
					break;
				}
				catch (const char* msg) {
					cout << msg << endl;
				}
				catch (invalid_argument& exception) {
					//�ٸ� ��ɾ �Է����� �� ������ ���� 
					cout << "invalid argument." << endl;
				}
				catch (...) {
					// �ٸ� ������ ��ɾ���� ������ �߻��ߴٰ� �����߻�
					cout << "Unknown error occurred." << endl;
				}
			}

			cout << line << endl;
		}
	}
	//split�Լ��� �̿��ؼ� ,�� �������� �Լ��� ���޵� ���ڸ� ���� ����
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
		// ���� �Լ��� �����ϴ� �Լ� 
		string str;
		str = command;

		char com = str.at(0);

		if (str.size() == 1) {
			if (com == 't') {
				// ������������
				TextConverter::save(test, "test.txt");
				// ����
				exit(0);
			}
			else if (com == 'n') {
				// ���� ������ ���
				view.nextPage(test);
			}
			else if (com == 'p') {
				// ���� ������ ���
				view.prevPage(test);
			}
			else {
				// �ٸ� ��ɾ �Է��ϸ� ���ܸ� �߻���Ų��
				throw "Try again.";
			}
			return;
		}


		if (str.size() < 2) {
			// �������� �ѱ�� �� �̿��� ��ɾ �Է����� �� �Է��� ���̰� 1�����̸� ���� �߻� 
			throw "Wrong input. Try again";
		}
		// str.at(1)�� �����Ϸ��� str.size() >= 2���� ����Ǿ�� ��
		// str.at(str.length() - 1)�� �����Ϸ��� str.size() - 1 >= 0���� ����Ǿ�� ��
		if (str.at(1) != '(' && str.at(str.length() - 1) != ')') {
			throw "invalid command. Try again";
			//�ٽ��Է¿䱸
		}

		// ���� ���� �Է¹޾ƿͼ�
		str.erase(str.begin()); // ��ɾ� ����
		str.erase(str.begin()); // ��ȣ ����
		str.erase(str.end() - 1); // ��ȣ ����

		if (com == 'i') {
			vector<string> line = split(str, ',');
			//line.size() ���� (== 3)
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
			//line.size() ���� (== 2)
			if (line.size() != 2) {
				throw "Wrong input. Try again.";
			}

			test.remove(stoi(line[0]), stoi(line[1]));
		}
		else if (com == 's') {
			vector<string> line = split(str, ',');
			//line.size() ���� (== 3)
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