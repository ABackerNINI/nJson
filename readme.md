## About
This is a C++0x serialize-to-json lib based on [parson](https://github.com/kgabis/parson.git).

## Features
* C++0x Compatible
* intrusive or non-intrusive

## Installation
* Run ```git clone https://github.com/ABackerNINI/nJson.git```.
* Copy folder "[nJson/nJson](https://github.com/ABackerNINI/nJson/blob/master/nJson)" to your source code tree.
* Run ```make``` to compile and run the test.

## Documents
### files tree:
nJson─┬─doc─┬─tree.md</br>
      │     └─foo.md</br>
      ├─nJson─┬─parson─┬─parson.c</br>
      │       │        └─parson.h</br>
      │       ├─support─┬─basic_type.h</br>
      │       │         ├─cstr_type.h</br>
      │       │         ├─list_type.h</br>
      │       │         ├─map_type.h</br>
      │       │         ├─pointer_type.h</br>
      │       │         ├─string_to.h</br>
      │       │         ├─string_type.h</br>
      │       │         ├─to_string.h</br>
      │       │         └─userdef_type.h</br>
      │       ├─DEF.h</br>
      │       ├─makefile</br>
      │       ├─nJson.h</br>
      │       └─parson.h</br>
      ├─resource─┬─InnerRes.h</br>
      │          └─Res.h</br>
      ├─.gitignore</br>
      ├─compile.bat</br>
      ├─LICENSE</br>
      ├─main.cpp</br>
      ├─makefile</br>
      └─readme.md</br>
See more at "[nJson/doc](https://github.com/ABackerNINI/nJson/blob/master/doc)".

## Examples
### Intrusive
* Include header file "[nJson/nJson/DEF.h](https://github.com/ABackerNINI/nJson/blob/master/nJson/DEF.h)".
* Implement the following two member functions to support the serialization/deserialization of a structure or a class with intrusive method.
```c++
bool serialize(JSON_Value *_doc_,const char *_key_ = NULL) const;
void deserialize(JSON_Value *_doc_);
```
* Initial basic types to avoid a random value.
The following code shows you how to support a self-define sturct.</br>
See more at "[nJson/resource](https://github.com/ABackerNINI/nJson/blob/master/resource)".
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

	bool serialize(JSON_Value *_doc_,const char *_key_ = NULL) const {
		JSON_Object *_root_obj_ = json_value_get_object(_doc_);
		{
			if(_key_==NULL){
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
			} else {
				SET_IF_KEY(c)
				SET_IF_KEY(b)
				SET_IF_KEY(s)
				SET_IF_KEY(i)
				SET_IF_KEY(f)
				SET_IF_KEY(ll)
				SET_IF_KEY(d)
				SET_IF_KEY(pc)
				SET_IF_KEY(m)
				SET_IF_KEY(l)
				SET_IF_KEY(lm)
				SET_IF_KEY(ir)
				SET_IF_KEY(pir)
				SET_IF_KEY(ppir)
				SET_IF_KEY(mir)
				{
					//TODO:error
					return false;
				}
			}
		}

		return true;
	}
	void deserialize(JSON_Value *_doc_){
		JSON_Object *_root_obj_ = json_value_get_object(_doc_);
		{
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
	char 						c;
	bool 						b;
	short 						s;
	int 						i;
	float 						f;
	long long 					ll;
	double 						d;

	//const char * test
	const char 					*pc;

	//map list test
	std::map<std::string,std::string> 		m;
	std::list<int>					l;
	std::list<std::map<std::string,std::string> >	lm;

	//inner object test
	InnerRes 					ir;
	InnerRes 					*pir;
	InnerRes 					**ppir;
	std::map<std::string,InnerRes>			mir;
	std::map<std::string,InnerRes*>			mpir;
};
```
"[nJson/main.cpp](https://github.com/ABackerNINI/nJson/blob/master/main.cpp)" shows you how to serialize it.Output:
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
void set_key_value(JSON_Object *obj,const char *key,const T &val);//support the serialization of type "T".
void set_key_value(JSON_Array *arr,T &val);//support the serialization of type "std::list<T>".
void get_value(JSON_Object *obj,const char *key,T *val);//support the deserialization of type "T".
void get_value(JSON_Array *arr,const T &val);//support the deserialization of type "std::list<T>".
```
The following code shows you how to support the type "std::list<T>".</br>
See more examples at "[nJson/nJson/support](https://github.com/ABackerNINI/nJson/blob/master/nJson/support)".
```c++
template<typename _T>
inline bool is_default_value(const std::list<_T> &val){
	return val.size()==0;
}

template<typename _T>
	void set_key_value(JSON_Object *obj,const char *key,const std::list<_T> &val){
		json_object_set_value(obj,key,json_value_init_array());
		JSON_Array *arr = json_object_get_array(obj,key);
		typename std::list<_T>::const_iterator it;
		for(it = val.begin();it!=val.end();++it){
			set_key_value(arr,*it);
		}
	}
template<typename _T>
	void set_key_value(JSON_Array *arr,const std::list<_T> &val){
		typename std::list<_T>::const_iterator it;
		for(it = val.begin();it!=val.end();++it){
			set_key_value(arr,*it);
		}
	}

template<typename _T>
	void get_value(JSON_Object *obj,const char *key,std::list<_T> *val){
		JSON_Array *arr = json_object_get_array(obj,key);
		size_t n = json_array_get_count(arr);
		_T lval;
		for(int i=0;i<n;++i){
			get_value(arr,i,&lval);
			val->push_back(lval);
		}
	}
template<typename _T>
	void get_value(JSON_Array *arr,const std::list<_T> &val);//implements to support std::list<std::list<_T> >
```

## Contributing
@ABacker:abacker.nini@foxmail.com

## Lisence
[GNU GENERAL PUBLIC LICENSE](http://fsf.org/)