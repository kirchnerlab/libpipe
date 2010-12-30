/*
 * Algorithm.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */
#include <mstk/algorithm/Algorithm.hpp>

using namespace mstk;

Algorithm::~Algorithm()
{
}

Request& Algorithm::processRequest(Request& req) {
    if (req.is(Request::UPDATE)) {
        req = this->update(req);
    }
    return req;
}

