
#include "my_unit_test.h"
#include <iostream>
#include <iomanip>

unordered_set<UnitTest*> UnitTest::mAllTestsSet;

UnitTest::UnitTest(const string &name, const function<bool()>& func) {
    mName = name;
    mFunction = func;

    mAllTestsSet.insert(this);
}

UnitTest::~UnitTest() {
    mAllTestsSet.erase(this);
}

void UnitTest::run() const{
    cout<<left;
    cout << std::setw(55);
    cout<<mName;
    if (mFunction())
        cout<<"\033[32m+"<<"\033[0m"<<endl;
    else
        cout<<"\033[31m-"<<"\033[0m"<<endl;
}

void runAllTests(){
    for (auto unit_test : UnitTest::mAllTestsSet) {
        unit_test->run();
    }
}



