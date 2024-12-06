
#ifndef HASHHISTORYMANAGER_H
#define HASHHISTORYMANAGER_H

#include <iostream>
#include <unordered_set>
#include <bits/stdc++.h>
#include "Grid/GridObject.hpp"

class HashHistoryManager {
private:
    std::unordered_set<size_t> previousStates ;
public:
    HashHistoryManager();
    bool hashAndCheck(GridObject*);
    void reset();
};





#endif //HASHHISTORYMANAGER_H