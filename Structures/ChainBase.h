//
// Created by Jeremy Cote on 2022-11-28.
//

#ifndef BEANS_CHAINBASE_H
#define BEANS_CHAINBASE_H


#include <iostream>
#include <vector>
#include "../Cards/Card.h"
#include "../CardFactory.h"
#include "ChainBase.h"
#include "../Exceptions/IllegalTypeException.h"
using namespace std;

class ChainBase {
public:
    virtual int sell() = 0;

    virtual void save(ostream& out) = 0;

    virtual void print(ostream& out) const = 0;

    friend ostream& operator<< (ostream& out, const ChainBase& chain) {
        chain.print(out);
        return out;
    }

    virtual ~ChainBase() = default;
};

#endif //BEANS_CHAINBASE_H
