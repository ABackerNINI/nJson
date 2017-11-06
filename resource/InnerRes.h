#pragma once

#ifndef _RESOURCE_INNER_RES_H_
#define _RESOURCE_INNER_RES_H_

#include <string.h>

#include "../nJson/DEF.h"

struct Super {
public:
    Super() :
            id(NJSON_DEFAULT_VALUE_INT) {
    }

    bool is_default_value() const {
        return false;
    }

    void njson_serialize(JSON_Value *njson_val) const {
        SET(id);
    }

    void njson_deserialize(JSON_Value *njson_val) {
        GET(id);
    }

    int &get_id() { return id; }

    void set_id(int id) { this->id = id; }

private:
    int id;
};

struct InnerRes : public Super {
public:
    InnerRes() :
            type(NJSON_DEFAULT_VALUE_INT) {
    }

    bool is_default_value() const {
        return false;
    }

    void njson_serialize(JSON_Value *njson_val) const {
        SERIALIZE_SUPER_CLASS(Super);

        SET(type);
        SET(key);
        SET(val);
    }

    void njson_deserialize(JSON_Value *njson_val) {
        DESERIALIZE_SUPER_CLASS(Super);

        GET(type);
        GET(key);
        GET(val);
    }

    int &get_type() { return type; }

    std::string &get_key() { return key; }

    std::string &get_val() { return val; }

    void set_type(int type) { this->type = type; }

    void set_key(const std::string &key) { this->key = key; }

    void set_val(const std::string &val) { this->val = val; }

    ~InnerRes() {
    }

private:
    int type;
    std::string key;
    std::string val;
};

#endif//_RESOURCE_INNER_RES_H_