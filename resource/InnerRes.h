#pragma once

#ifndef _RESOURCE_INNER_RES_H_
#define _RESOURCE_INNER_RES_H_

#include <string.h>

#include "../nJson/DEF.h"

struct Super {
public:
    Super() :
            id(DEFAULT_VALUE_INT) {
    }

    bool serialize(JSON_Value *_doc_, const char *_key_ = NULL) const {
        JSON_Object *_root_obj_ = json_value_get_object(_doc_);
        {
            if (_key_ == NULL) {
                SET(id);
            } else {
                SET_IF_KEY(id) {
                    return false;
                }
            }
        }

        return true;
    }

    void deserialize(JSON_Value *_doc_) {
        JSON_Object *_root_obj_ = json_value_get_object(_doc_);
        {
            GET(id);
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
            type(DEFAULT_VALUE_INT) {
    }

    // bool isUninitialized() const {
    // 	return type==DEFAULT_VALUE_INT && key==DEFAULT_VALUE_CSTR && val == DEFAULT_VALUE_CSTR;
    // }

    bool serialize(JSON_Value *_doc_, const char *_key_ = NULL) const {
        SERIALIZE_SUPER_CLASS(Super);

        JSON_Object *_root_obj_ = json_value_get_object(_doc_);
        {
            if (_key_ == NULL) {
                SET(type);
                SET(key);
                SET(val);
            } else {
                SET_IF_KEY(type) SET_IF_KEY(key) SET_IF_KEY(val) {
                    return false;
                }
            }
        }

        return true;
    }

    void deserialize(JSON_Value *_doc_) {
        DESERIALIZE_SUPER_CLASS(Super);

        JSON_Object *_root_obj_ = json_value_get_object(_doc_);
        {
            GET(type);
            GET(key);
            GET(val);
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