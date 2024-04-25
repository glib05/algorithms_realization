#include <string>
#include <functional>
#include <unordered_set>

#define FAILURE return false
#define SUCCESS return true

#ifndef PRO_ALG_4_TRAVEL_ANTS_MY_UNIT_TEST_H
#define PRO_ALG_4_TRAVEL_ANTS_MY_UNIT_TEST_H

using namespace std;

class UnitTest{
    string mName;
    function<bool()> mFunction;

    static unordered_set<UnitTest*> mAllTestsSet;

public:

    UnitTest(const string &name, const function<bool()>& func);
    ~UnitTest();

    void run() const;

    friend void runAllTests();
};

void runAllTests();

#endif //PRO_ALG_4_TRAVEL_ANTS_MY_UNIT_TEST_H
