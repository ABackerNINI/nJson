#include <iostream>
#include <map>
#include <list>
#include <string>
#include <string.h>
#include "resource/Res.h"

#define SET(M) njson_serialize(njson_val,#M,njson_var.get_##M())
#define GET(M) if(json_object_has_value(json_value_get_object(njson_val),#M)) \
    njson_deserialize(json_object_get_value(json_value_get_object(njson_val),#M),&(njson_var->get_##M()))

class foo {
public:
    void set_a(const int &a) { this->a = a; }

    const int &get_a() const { return a; }

    int &get_a() { return a; }

    int a;
};

template<>
struct njson_support<foo> {
    static bool is_default_value(const foo &f) {
        return false;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const foo &njson_var) {
        SET(a);
    }

    static void deserialize(JSON_Value *njson_val, foo *njson_var) {
        GET(a);
    }
};

int main() {
    foo f;
    f.set_a(10);
    char *s11 = njson_serialize(f);
    printf("%s\n", s11);

    foo f2;
    njson_deserialize(&f2, s11);

    printf("debug begin\n");
    //printf("%s %d %s %s %s\n", __FILE__, __LINE__, __DATE__,__TIME__,__func__);
    Res res;
    {
        res.set_c('c');
        res.set_b(false);
        res.set_s(159);
        res.set_i(10001);
        res.set_pc("1234567890");
        res.set_f((float) 1000000.2);
        res.set_ll(1234567890);
        res.set_d(1234567890.123456);
        res.get_l().push_back(1);
        res.get_l().push_back(2);
        res.get_l().push_back(3);
        res.get_l().push_back(4);
        res.get_m()["1"] = "2";
        res.get_m()["2"] = "3";
        res.get_m()["3"] = "4";
        res.get_m()["4"] = "5";
        std::map<std::string, std::string> m;
        {
            m["1"] = "2";
            m["2"] = "\\3";
            m["3"] = "4";
        }
        res.set_m(m);

        std::map<int, double> mid;
        {
            mid[1] = 2.0;
            mid[2] = 3.0;
        }
        res.set_mid(mid);

        std::map<char *, char *> mcc;
        {
            char *s1 = new char[10];
            char *s2 = new char[10];
            strcpy(s1, "123456");
            strcpy(s2, "7890");
            mcc[s1] = s2;
            mcc[s2] = s1;
        }
        res.set_mcc(mcc);

        res.get_lm().push_back(m);
        res.get_lm().push_back(m);
        res.get_lm().push_back(m);
        res.get_lm().push_back(m);
        res.get_ir().set_key("k");
        res.get_ir().set_val("v");
        res.get_ir().set_id(1);
        res.set_pir(new InnerRes());
        res.get_pir()->set_type(1);
        res.get_pir()->set_key("pir key");
        res.set_ppir(new InnerRes *());
        *(res.get_ppir()) = new InnerRes();
        (*(res.get_ppir()))->set_type(0);
        (*(res.get_ppir()))->set_key("ppir key");
        (*(res.get_ppir()))->set_val("ppir val");
        InnerRes ir1;
        {
            ir1.set_type(1);
            ir1.set_key("k1");
            ir1.set_val("v1");
        }
        res.get_mir()["1"] = ir1;
        InnerRes ir2;
        {
            ir2.set_type(2);
            ir2.set_key("k2");
            ir2.set_val("v2");
        }
        res.get_mir()["2"] = ir2;
    }

    const char *s = njson_serialize(res);

    printf("%s\n", s);

    Res res2;
    njson_deserialize<Res>(&res2, s);

    const char *s2 = njson_serialize(res2);

    printf("%s\n", s2);

    free((void *) s);
    free((void *) s2);

    printf("debug end\n");

    return 0;
}