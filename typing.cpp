#include <chrono>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

static const int TIME_LIMIT = 1500;
std::map<std::string, bool> result;

void signalHandler(int sig)
{
    if (sig == SIGINT) {
        std::cout << "\n\nCharacters that you can type quickly:\n  ";
        for (auto r : result) {
            if (r.second) {
                std::cout << r.first;
            }
        }
        std::cout << "\nCharacters that you can't type quickly:\n  ";
        for (auto r : result) {
            if (!r.second) {
                std::cout << r.first;
            }
        }
        std::cout << "\n";
    }
    exit(0);
}

int main()
{
    signal(SIGINT, signalHandler);

    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());

    std::vector<std::string> problems;
    for (int i = 33; i < 127; i++) {
        std::string s(1, char(i));
        problems.push_back(s);
    }

    while (true) {
        std::uniform_int_distribution<> rand(0, problems.size() - 1);
        auto i = rand(engine);
        auto start = std::chrono::system_clock::now();

        std::cout << "type " << problems[i] << ": ";
        std::string ans;
        getline(std::cin, ans);

        if (ans != problems[i]) {
            std::cout << "  type miss\n";
            result[problems[i]] = false;
            continue;
        }

        auto end = std::chrono::system_clock::now();
        if (end - start > std::chrono::milliseconds(TIME_LIMIT)) {
            std::cout << "  too slow\n";
            result[problems[i]] = false;
            continue;
        }

        result[problems[i]] = true;
        problems.erase(problems.begin() + i);
    }

    return 0;
}
