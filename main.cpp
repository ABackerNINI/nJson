#include <stdio.h>
#include <iostream>
#include <map>
#include <list>
#include <string>
#include <string.h>
#include "resource/Res.h"

int main() {

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

    const char *s = serialize(res);

    printf("%s\n", s);

    Res res2;
    deserialize<Res>(&res2, s);

    const char *s2 = serialize(res2);

    printf("%s\n", s2);

    free((void *) s);
    free((void *) s2);

    printf("debug end\n");

    return 0;
}