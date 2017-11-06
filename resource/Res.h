#pragma once

#ifndef _RESOURCE_RES_H_
#define _RESOURCE_RES_H_

#include <string.h>

#include "InnerRes.h"
#include "../nJson/DEF.h"

struct Res {
public:
    Res() :
            c(NJSON_DEFAULT_VALUE_CHAR),
            // b(NJSON_DEFAULT_VALUE_BOOL),
            s(NJSON_DEFAULT_VALUE_SHORT),
            i(NJSON_DEFAULT_VALUE_INT),
            f(NJSON_DEFAULT_VALUE_FLOAT),
            ll(NJSON_DEFAULT_VALUE_LONG_LONG),
            d(NJSON_DEFAULT_VALUE_DOUBLE),
            pc(NJSON_DEFAULT_VALUE_CSTR),
            pir(NJSON_DEFAULT_VALUE_POINTER),
            ppir(NJSON_DEFAULT_VALUE_POINTER) {
        /*init bool*/
        memset(&b, -1, sizeof(bool));
    }


    char &get_c() { return c; }

    bool &get_b() { return b; }

    short &get_s() { return s; }

    int &get_i() { return i; }

    float &get_f() { return f; }

    long long &get_ll() { return ll; }

    double &get_d() { return d; }

    const char *&get_pc() { return pc; }

    std::map<std::string, std::string> &get_m() { return m; }

    std::list<int> &get_l() { return l; }

    std::list<std::map<std::string, std::string> > &get_lm() { return lm; }

    InnerRes &get_ir() { return ir; }

    InnerRes *&get_pir() { return pir; }

    InnerRes **&get_ppir() { return ppir; }

    std::map<std::string, InnerRes> &get_mir() { return mir; }

    std::map<std::string, InnerRes *> &get_mpir() { return mpir; }

    void set_c(char c) { this->c = c; }

    void set_b(bool b) { this->b = b; }

    void set_s(short s) { this->s = s; }

    void set_i(int i) { this->i = i; }

    void set_f(float f) { this->f = f; }

    void set_ll(long long ll) { this->ll = ll; }

    void set_d(double d) { this->d = d; }

    void set_pc(const char *pc) { this->pc = strdup(pc); }

    void set_m(const std::map<std::string, std::string> &m) { this->m = m; }

    void set_l(const std::list<int> &l) { this->l = l; }

    void set_lm(const std::list<std::map<std::string, std::string> > &lm) { this->lm = lm; }

    void set_ir(const InnerRes &ir) { this->ir = ir; }

    void set_pir(InnerRes *pir) { this->pir = pir; }

    void set_ppir(InnerRes **ppir) { this->ppir = ppir; }

    void set_mir(const std::map<std::string, InnerRes> &mir) { this->mir = mir; }

    void set_mpir(const std::map<std::string, InnerRes *> &mpir) { this->mpir = mpir; }

    ~Res() {
//        if (pc)delete[] pc;
        if (pir)delete pir;
        if (ppir && *ppir)delete *ppir;
        if (ppir)delete ppir;
        //TODO free mpir
    }

    bool is_default_value() const {
        return false;
    }

    void njson_serialize(JSON_Value *njson_val) const {
        SET(c);
        SET(b);
        SET(s);
        SET(i);
        SET(f);
        SET(ll);
        SET(d);
        SET(pc);
        SET(m);
        SET(l);
        SET(lm);
        SET(ir);
        SET(pir);
        SET(ppir);
        SET(mir);
        SET(mpir);
    }

    void njson_deserialize(JSON_Value *njson_val) {
        GET(c);
        GET(b);
        GET(s);
        GET(i);
        GET(f);
        GET(ll);
        GET(d);
        GET(pc);
        GET(m);
        GET(l);
        GET(lm);
        GET(ir);
        GET(pir);
        GET(ppir);
        GET(mir);
        GET(mpir);
    }

private:
    //basic types test
    char c;
    bool b;
    short s;
    int i;
    float f;
    long long ll;
    double d;

    //const char * test
    const char *pc;

    //map list test
    std::map<std::string, std::string> m;
    std::list<int> l;
    std::list<std::map<std::string, std::string> > lm;

    //inner object test
    InnerRes ir;
    InnerRes *pir;
    InnerRes **ppir;
    std::map<std::string, InnerRes> mir;
    std::map<std::string, InnerRes *> mpir;
};

#endif//_RESOURCE_RES_H_