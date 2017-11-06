#include <cstdio>

#include "nJson/DEF.h"

class foo {
public:
    JSON_Value *njson_serialize() {
        JSON_Value *njson_val = json_value_init_object();
        GET(a);
    }

public:
    int a;
};

int main() {
    foo f;
    f.a = 100;

    JSON_Value *njson_val = njson_serialize(f);

    char *s = json_serialize_to_string_pretty(njson_val);

    printf("%s\n", s);

    delete[]s;

    return 0;
}