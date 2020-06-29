# NJSON

[![GitHub](https://img.shields.io/github/license/ABackerNINI/nJson)](https://github.com/ABackerNINI/nJson/blob/master/LICENSE)

* This is a C++98 serialize-to-json lib based on [parson](https://github.com/kgabis/parson.git).

## Features

* C++98 Compatible
* Intrusive or non-intrusive

## Installation

* Run ```git clone https://github.com/ABackerNINI/nJson.git```.
* Copy folder "[nJson/nJson](https://github.com/ABackerNINI/nJson/tree/master/nJson)" to your source code tree.
* Run ```make``` to compile and run the test.

## Documents

* See more at "[nJson/doc](https://github.com/ABackerNINI/nJson/tree/master/doc)".

## Examples

### Intrusive

* Include header file "[nJson/nJson/DEF.h](https://github.com/ABackerNINI/nJson/blob/master/nJson/DEF.h)".
* Implement the following two member functions to support the serialization/deserialization of a structure or a class with intrusive method.

```c++
bool njson_is_default() const; // optional
bool njson_serialize(JSON_Value *_doc_,const char *_key_ = NULL) const;
void njson_deserialize(JSON_Value *_doc_);
```

* Initial basic types to avoid a random value.
* The following code shows you how to support a self-define struct.

```c++

struct Res {
   public:
    Res()
        : c(0),
          b(false),
          s(0),
          i(0),
          f(0),
          ll(0),
          d(0),
          pc(NULL),
          pir(NULL),
          ppir(NULL) {}

    bool njson_is_default() const { return false; }

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
    // basic types test
    char c;
    bool b;
    short s;
    int i;
    float f;
    long long ll;
    double d;

    // const char * test
    const char *pc;

    // map list test
    std::map<std::string, std::string> m;
    std::map<int, double> mid;
    std::map<char *, char *> mcc;
    std::list<int> l;
    std::list<std::map<std::string, std::string> > lm;

    // inner object test
    InnerRes ir;
    InnerRes *pir;
    InnerRes **ppir;
    std::map<std::string, InnerRes> mir;
    std::map<std::string, InnerRes *> mpir;
};
```

See more at "[nJson/resource](https://github.com/ABackerNINI/nJson/tree/master/resource)".

* "[nJson/main.cpp](https://github.com/ABackerNINI/nJson/blob/master/main.cpp)" shows you how to serialize it. Output:

```json
{
    "c": "c",
    "b": false,
    "s": 159,
    "i": 10001,
    "f": 1000000.187500,
    "ll": 1234567890,
    "d": 1234567890.123456,
    "pc": "1234567890",
    "m": {
        "1": "2",
        "2": "\\3",
        "3": "4"
    },
    "mid": {
        "1": 2,
        "2": 3
    },
    "mcc": {
        "7890": "123456",
        "123456": "7890"
    },
    "l": [
        1,
        2,
        3,
        4
    ],
    "lm": [
        {
            "1": "2",
            "2": "\\3",
            "3": "4"
        },
        {
            "1": "2",
            "2": "\\3",
            "3": "4"
        },
        {
            "1": "2",
            "2": "\\3",
            "3": "4"
        },
        {
            "1": "2",
            "2": "\\3",
            "3": "4"
        }
    ],
    "ir": {
        "id": 1,
        "type": 0,
        "key": "k",
        "val": "v"
    },
    "pir": {
        "id": 0,
        "type": 1,
        "key": "pir key"
    },
    "ppir": {
        "id": 0,
        "type": 0,
        "key": "ppir key",
        "val": "ppir val"
    },
    "mir": {
        "1": {
            "id": 0,
            "type": 1,
            "key": "k1",
            "val": "v1"
        },
        "2": {
            "id": 0,
            "type": 2,
            "key": "k2",
            "val": "v2"
        }
    }
}
```

### Non-Intrusive

* Implement the following five functions to support a structure or a class with non-intrusive method.

```c++
bool is_default_value(const T &val);// ignore when serializing if it is a default value.
                    // Intrusive method return false on default.
void njson_set_value(JSON_Object *obj,const char *key,const T &val);// support the serialization of type "T".
void njson_set_value(JSON_Array *arr,T &val);// support the serialization of array type of T.
void njson_get_value(JSON_Object *obj,const char *key,T *val);// support the deserialization of type "T".
void njson_get_value(JSON_Array *arr,const T &val);// support the deserialization of array type of T.
```

* The following code shows you how to support the type "std::list\<T\>".

```c++
template<typename _T>
inline bool is_default_value(const std::list<_T> &val){
    return val.size()==0;
}

template<typename _T>
    void njson_set_value(JSON_Object *obj,const char *key,const std::list<_T> &val){
        json_object_set_value(obj,key,json_value_init_array());
        JSON_Array *arr = json_object_get_array(obj,key);
        typename std::list<_T>::const_iterator it;
        for(it = val.begin();it!=val.end();++it){
            njson_set_value(arr,*it);
        }
    }
template<typename _T>
    void njson_set_value(JSON_Array *arr,const std::list<_T> &val){
        typename std::list<_T>::const_iterator it;
        for(it = val.begin();it!=val.end();++it){
            njson_set_value(arr,*it);
        }
    }

template<typename _T>
    void njson_get_value(JSON_Object *obj,const char *key,std::list<_T> *val){
        JSON_Array *arr = json_object_get_array(obj,key);
        size_t n = json_array_get_count(arr);
        _T lval;
        for(int i=0;i<n;++i){
            njson_get_value(arr,i,&lval);
            val->push_back(lval);
        }
    }
template<typename _T>
    void njson_get_value(JSON_Array *arr,const std::list<_T> &val);// implements to support std::list<std::list<_T> >
```

See more examples at "[nJson/nJson/support](https://github.com/ABackerNINI/nJson/tree/master/nJson/support)".

## Contributing

* @ABacker:abacker.nini@foxmail.com

## License

* [GNU GENERAL PUBLIC LICENSE V3](http://fsf.org/)
