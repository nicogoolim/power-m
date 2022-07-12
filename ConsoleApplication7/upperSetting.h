#pragma once
#include <chrono>

class upperSetting {
private:
	int BA;
	int RMV;
	std::chrono::seconds RDV;
	bool curState = false;
public:
	bool trigger() {
		int Y;
		std::cout << "Введите Y:";
		std::cin >> Y;
		if (Y>=BA)
		{
			curState = true;
		}
		auto start = std::chrono::system_clock::now();
		auto start1 = std::chrono::system_clock::now();
		auto end = std::chrono::system_clock::now();
		auto curTimer = std::chrono::duration_cast<std::chrono::seconds>(end - start);
		while (true)
		{
			end = std::chrono::system_clock::now();
			curTimer = std::chrono::duration_cast<std::chrono::seconds>(end - start);
			std::cout << "Ввести новый Y? ответ(y/n):";
			char input;
			std::cin >> input;
			if (input=='y')
			{
				std::cout << std::endl << "Y:";
				std::cin >> Y;
			}
			if (Y>=BA)
			{
				if (!curState)
				{
					curState = true;
					start = std::chrono::system_clock::now();
				}
				if (curTimer>=RDV)
				{
					std::cout << "С первого запуска прошло :" << std::chrono::duration_cast<std::chrono::seconds>(end - start1).count() << " секунд" << std::endl;
					return true;
				}
			}
			else if(Y<BA)
			{
				if (curState)
				{
					curState = false;
					start = std::chrono::system_clock::now();
				}
				if (curTimer >= RDV)
				{
					std::cout <<"Sec:"<< std::chrono::duration_cast<std::chrono::seconds>(end - start1).count() << " секунд" << std::endl;
					return false;
				}
			}
		}
	}
	upperSetting(int BA, int RMV, int RDV) {
		this->BA = BA;
		this->RMV = RMV;
		this->RDV = std::chrono::seconds(RDV);
	};
};