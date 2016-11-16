//
//  error.hpp
//  Compiler
//
//  Created by 马琛骁 on 11/8/16.
//  Copyright © 2016 Michael Ma. All rights reserved.
//

#ifndef error_hpp
#define error_hpp

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

#define LOG(x) do {cerr << "***LOG " << x << endl;} while(0);
#define ERR(x) do {cerr << "***ERR " << x << endl; exit(-1);} while(0);

#define UNEXPECTED_END 000
#define LINE_TOO_LONG 001
#define ILLEGAL_CHARACTER 100
#define ORPHAN_DOUBLE_QUOTE 101
#define ORPHAN_SINGLE_QUOTE 102
#define ILLEGAL_CHARACTER_CONST 103
#define NUMBER_TOO_LONG 104
#define DOUBLE_DECLARE 200
#define NO_DECLARE 201
#define MISSING_SEMI 202
#define MISSING_IDENTIFIER 203
#define MISSING_EQUAL 204
#define MISSING_VALUE 205


void error(int errNo);

#endif /* error_hpp */
