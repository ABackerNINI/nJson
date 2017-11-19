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

    bool njson_is_default() const {
        return false;
    }

    JSON_Value *njson_serialize() const {
        NJSON_SERIALIZE_INIT;
        {
            NJSON_SET(id);
        }

        NJSON_RET;
    }

    void njson_deserialize(JSON_Value *njson_val) {
        NJSON_DESERIALIZE_INIT;
        {
            NJSON_GET(id);
        }
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

    bool njson_is_default() const {
        return false;
    }

    JSON_Value *njson_serialize() const {
        NJSON_SERIALIZE_INIT;
        {
            NJSON_SERIALIZE_SUPER_CLASS(Super);

            NJSON_SET(type);
            NJSON_SET(key);
            NJSON_SET(val);
        }

        NJSON_RET;
    }

    void njson_deserialize(JSON_Value *njson_val) {
        NJSON_DESERIALIZE_INIT;
        {
            NJSON_DESERIALIZE_SUPER_CLASS(Super);

            NJSON_GET(type);
            NJSON_GET(key);
            NJSON_GET(val);
        }
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