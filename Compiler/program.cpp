//
//  program.cpp
//  Compiler
//
//  Created by 马琛骁 on 11/15/16.
//  Copyright © 2016 Michael Ma. All rights reserved.
//

#include "grammar.hpp"

symbolNo current_func_type;

void GrammarDecoder::Program() {
    if (ld -> LastSymbol() == constSym) {
        // FIXME: NextWord is not called
        ConstDeclare();
        LOG("Call ConstDeclare");
    }
    if (ld -> LastSymbol() == intSym || ld -> LastSymbol() == charSym) {
        symbolNo type = ld -> LastSymbol();
        ld -> NextWord();
        
        if (ld -> LastWordType() != identifiers) {
            error(MISSING_IDENTIFIER);
        }
        
        string name = ld -> LastStr();
        ld -> NextWord();
        
        if (ld -> LastSymbol() == lRoundSym) {
            LOG("Call FuncDeclare")
            ld -> NextWord();
            
            FuncDeclare(type, name);
        }
        else {
            LOG("Call StaticVarDeclare");
            StaticVarDeclare(type, name);
        }
    }
    while (ld -> LastSymbol() == intSym || ld -> LastSymbol() == charSym || ld -> LastSymbol() == voidSym) {
        symbolNo type = ld -> LastSymbol();
        ld -> NextWord();
        
        if (ld -> LastSymbol() == mainSym) {
            ld -> NextWord();
            
            Main();
            break;
        }
        
        string name = ld -> LastStr();
        ld -> NextWord();
        
        if (ld -> LastSymbol() != lRoundSym) {
            error(MISSING_LEFT_ROUND);
        }
        else ld -> NextWord();
        
        switch (type) {
            case intSym:
            case charSym:
                FuncDeclare(type, name);
                break;
            case voidSym:
                VoidFuncDeclare(name);
                break;
            default:
                break;
        }
    }
}

void GrammarDecoder::Main() {
    current_func_type = voidSym;
    
    Quaternary * temp = new Quaternary(mainIns, NULL, NULL, NULL);
    code_table.push_back(temp);
    
    id = new IdentifierTable();
    ge -> SetId(id);
    
    if (ld -> LastSymbol() != lRoundSym) {
        error(MISSING_LEFT_ROUND);
    }
    else ld -> NextWord();
    if (ld -> LastSymbol() != rRoundSym) {
        error(ORPHAN_ROUND);
    }
    else ld -> NextWord();
    if (ld -> LastSymbol() != lCurlySym) {
        error(MISSING_LEFT_CURLY);
    }
    else ld -> NextWord();
    
    try {
        Statements();
    } catch (bool returned) {
        ;
    }
    
    if (ld -> LastSymbol() != rCurlySym) {
        error(ORPHAN_CURLY);
    }
    
    LOG("Decoded main function");
    
//    delete id; FIXME
    id = NULL;
    
    ge -> SetId(gid);
    
    ge -> RET();
}
