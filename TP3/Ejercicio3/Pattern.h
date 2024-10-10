#ifndef TAYLOR_H
#define TAYLOR_H
#include <mutex>
#include <string>
class Pattern {
private:
    std::mutex mtx;
public:
    Pattern();
    void recognizePattern(std::string pattern, long int& res);
};

#endif
