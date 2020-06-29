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
bool njson_serialize(JSON_Value *_doc_,const char *_key_ = NULL) const;
void njson_deserialize(JSON_Value *_doc_);
```

* Initial basic types to avoid a random value.
* The following code shows you how to support a self-define struct.

```c++
struct Res{
public:
    Res():
        c(DEFAULT_VALUE_CHAR),
        // b(DEFAULT_VALUE_BOOL),
        s(DEFAULT_VALUE_SHORT),
        i(DEFAULT_VALUE_INT),
        f(DEFAULT_VALUE_FLOAT),
        ll(DEFAULT_VALUE_LONG_LONG),
        d(DEFAULT_VALUE_DOUBLE),
        pc(DEFAULT_VALUE_CSTR),
        pir(DEFAULT_VALUE_POINTER),
        ppir(DEFAULT_VALUE_POINTER){
            /*init bool*/
            memset(&b,-1,sizeof(bool));
        }

    bool njson_serialize(JSON_Value *_doc_,const char *_key_ = NULL) const {
        JSON_Object *_root_obj_ = json_value_get_object(_doc_);
        {
            if(_key_==NULL){
                NJSON_SET(c);
                NJSON_SET(b);
                NJSON_SET(s);
                NJSON_SET(i);
                NJSON_SET(f);
                NJSON_SET(ll);
                NJSON_SET(d);
                NJSON_SET(pc);
                NJSON_SET(m);
                NJSON_SET(l);
                NJSON_SET(lm);
                NJSON_SET(ir);
                NJSON_SET(pir);
                NJSON_SET(ppir);
                NJSON_SET(mir);
            } else {
                NJSON_SET_IF_KEY(c)
                NJSON_SET_IF_KEY(b)
                NJSON_SET_IF_KEY(s)
                NJSON_SET_IF_KEY(i)
                NJSON_SET_IF_KEY(f)
                NJSON_SET_IF_KEY(ll)
                NJSON_SET_IF_KEY(d)
                NJSON_SET_IF_KEY(pc)
                NJSON_SET_IF_KEY(m)
                NJSON_SET_IF_KEY(l)
                NJSON_SET_IF_KEY(lm)
                NJSON_SET_IF_KEY(ir)
                NJSON_SET_IF_KEY(pir)
                NJSON_SET_IF_KEY(ppir)
                NJSON_SET_IF_KEY(mir)
                {
                    //TODO:error
                    return false;
                }
            }
        }

        return true;
    }
    void njson_deserialize(JSON_Value *_doc_){
        JSON_Object *_root_obj_ = json_value_get_object(_doc_);
        {
            NJSON_GET(c);
            NJSON_GET(b);
            NJSON_GET(s);
            NJSON_GET(i);
            NJSON_GET(f);
            NJSON_GET(ll);
            NJSON_GET(d);
            NJSON_GET(pc);
            NJSON_GET(m);
            NJSON_GET(l);
            NJSON_GET(lm);
            NJSON_GET(ir);
            NJSON_GET(pir);
            NJSON_GET(ppir);
            NJSON_GET(mir);
        }
    }

    ~Res(){
        if(pc)delete[] pc;
        if(pir)delete pir;
        if(ppir&&*ppir)delete *ppir;
        if(ppir)delete ppir;
        //TODO free mpir
    }

private:
    //basic types test
    char                         c;
    bool                         b;
    short                         s;
    int                         i;
    float                         f;
    long long                     ll;
    double                         d;

    //const char * test
    const char                     *pc;

    //map list test
    std::map<std::string,std::string>         m;
    std::list<int>                    l;
    std::list<std::map<std::string,std::string> >    lm;

    //inner object test
    InnerRes                     ir;
    InnerRes                     *pir;
    InnerRes                     **ppir;
    std::map<std::string,InnerRes>            mir;
    std::map<std::string,InnerRes*>            mpir;
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
        "key": "k",
        "val": "v"
    },
    "pir": {
        "type": 1,
        "key": "pir key"
    },
    "ppir": {
        "type": 0,
        "key": "ppir key",
        "val": "ppir val"
    },
    "mir": {
        "1": {
            "type": 1,
            "key": "k1",
            "val": "v1"
        },
        "2": {
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
bool is_default_value(const T &val);//ignore when serializing if it is a default value.
                    //Intrusive method return false on default.
void njson_set_value(JSON_Object *obj,const char *key,const T &val);//support the serialization of type "T".
void njson_set_value(JSON_Array *arr,T &val);//support the serialization of array type of T.
void njson_get_value(JSON_Object *obj,const char *key,T *val);//support the deserialization of type "T".
void njson_get_value(JSON_Array *arr,const T &val);//support the deserialization of array type of T.
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
    void njson_get_value(JSON_Array *arr,const std::list<_T> &val);//implements to support std::list<std::list<_T> >
```

See more examples at "[nJson/nJson/support](https://github.com/ABackerNINI/nJson/tree/master/nJson/support)".

## Contributing

* @ABacker:abacker.nini@foxmail.com

## License

[GNU GENERAL PUBLIC LICENSE](http://fsf.org/)
