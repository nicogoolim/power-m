
#include <iostream>
#include <map>
#include <Windows.h>
#include <string>
#include <thread>

struct mapStruct {
    std::string id;
    std::map<std::string, std::string>* intern;
};

enum State {
    active,
    passive,
    off  
};

void fillMap(mapStruct *maps, int size) {
    for (int i = 0; i < size; i++)
    {
        int count = 1;
        for (auto& kv : *maps[i].intern)
        {
            kv.second = (maps[i].id + std::to_string(count));
            count++;
        }
    }
}

void trigger(int BA, int RMV, State& curState, std::chrono::system_clock::time_point& start) {
    int Y;
    while (true)
    {
        std::cin >> Y;

        if (Y >= BA + RMV)
        {
            if (curState!=active)
            {
                start = std::chrono::system_clock::now();
            }
            curState = active;
        }
        else if (Y <= BA - RMV)
        {
            if (curState != passive)
            {
                start = std::chrono::system_clock::now();
            }
           curState = passive;
        }
    }

}

int main()
{
    SetConsoleOutputCP(1251);
    mapStruct maps[3];
    std::map<std::string, std::string> intern;
    std::map<std::string, std::map<std::string, std::string>> ex;

    intern["YID"];
    intern["UAV"];
    intern["RDV"];
    ex.emplace("K", intern);
    ex.emplace("Z", intern);
    ex.emplace("B", intern);

    maps[0].id = "K";
    maps[0].intern = &ex["K"];
    maps[1].id = "Z";
    maps[1].intern = &ex["Z"];
    maps[2].id = "B";
    maps[2].intern = &ex["B"];

    fillMap(maps, 3);
    for (const auto& exEl : ex) {
        for (const auto& intEl : exEl.second) {
            std::cout << "Внешний ключ " << exEl.first << " Внутренний ключ " << intEl.first
                << " Внутреннее значение " << intEl.second << std::endl;
                
        }
        std::cout << std::endl;
    }

    int BA;
    int RMV;
    int RDV;

    std::cout << "Введите BA:";
    std::cin >> BA;
    std::cout << "Введите RMV:";
    std::cin >> RMV;
    std::cout << "Введите RDV:";
    std::cin >> RDV;

    std::chrono::seconds timer = std::chrono::seconds(RDV);
    auto timeStart  = std::chrono::system_clock::now();
    auto timeEnd = std::chrono::system_clock::now();
    auto curTimer = std::chrono::duration_cast<std::chrono::seconds>(timeEnd - timeStart);
    
    State curState = off;

    std::thread th(trigger, BA, RMV, std::ref(curState), std::ref(timeStart));
    th.detach();

    
    while (true)
    {
        curTimer = std::chrono::duration_cast<std::chrono::seconds>(timeEnd - timeStart);
        timeEnd = std::chrono::system_clock::now();
        if (curTimer.count() >= timer.count())
        {
            if (curState == active) {
                std::cout << "Активно" << std::endl;
            }
            if (curState == passive) {
                std::cout << "Пассивно" << std::endl;
            }
            curState = off;
            timeStart = std::chrono::system_clock::now();
        }
    }
  
   
    

}
