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

    void set_mid(const std::map<int, double> &mid) { this->mid = mid; }

    void set_mcc(const std::map<char *, char *> &mcc) { this->mcc = mcc; }

    void set_l(const std::list<int> &l) { this->l = l; }

    void set_lm(const std::list<std::map<std::string, std::string> > &lm) { this->lm = lm; }

    void set_ir(const InnerRes &ir) { this->ir = ir; }

    void set_pir(InnerRes *pir) { this->pir = pir; }

    void set_ppir(InnerRes **ppir) { this->ppir = ppir; }

    void set_mir(const std::map<std::string, InnerRes> &mir) { this->mir = mir; }

    void set_mpir(const std::map<std::string, InnerRes *> &mpir) { this->mpir = mpir; }

    ~Res() {
        if (pc)delete[] pc;
        if (pir)delete pir;
        if (ppir && *ppir)delete *ppir;
        if (ppir)delete ppir;
        //TODO free mpir
    }

    bool njson_is_default() const {
        return false;
    }

    JSON_Value *njson_serialize() const {
        NJSON_SERIALIZE_INIT;
        {
            NJSON_SET(c);
            NJSON_SET(b);
            NJSON_SET(s);
            NJSON_SET(i);
            NJSON_SET(f);
            NJSON_SET(ll);
            NJSON_SET(d);
            NJSON_SET(pc);
            NJSON_SET(m);
            NJSON_SET(mid);
            NJSON_SET(mcc);
            NJSON_SET(l);
            NJSON_SET(lm);
            NJSON_SET(ir);
            NJSON_SET(pir);
            NJSON_SET(ppir);
            NJSON_SET(mir);
            NJSON_SET(mpir);
        }

        NJSON_RET;
    }

    void njson_deserialize(JSON_Value *njson_val) {
        NJSON_DESERIALIZE_INIT;

        NJSON_GET(c);
        NJSON_GET(b);
        NJSON_GET(s);
        NJSON_GET(i);
        NJSON_GET(f);
        NJSON_GET(ll);
        NJSON_GET(d);
        NJSON_GET(pc);
        NJSON_GET(m);
        NJSON_GET(mid);
        NJSON_GET(mcc);
        NJSON_GET(l);
        NJSON_GET(lm);
        NJSON_GET(ir);
        NJSON_GET(pir);
        NJSON_GET(ppir);
        NJSON_GET(mir);
        NJSON_GET(mpir);
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
    std::map<int, double> mid;
    std::map<char *, char *> mcc;
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