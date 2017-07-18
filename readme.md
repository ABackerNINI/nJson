## About
This is a C++0x serialize-to-json lib based on [parson](https://github.com/kgabis/parson.git).

## Features
* C++0x Compatible
* intrusive or non-intrusive

## Installation
* Run ```git clone https://github.com/ABackerNINI/nJson.git```.
* Copy [nJson/nJson](https://github.com/ABackerNINI/nJson/blob/master/nJson) to your source code tree.
* Run ```make``` to compile and run the test.

## Examples
### Intrusive
* Include header file [nJson/nJson/DEF.h](https://github.com/ABackerNINI/nJson/blob/master/nJson/DEF.h)
* Implement the following two member functions to support the serialization/deserialization of a structure or class.
```c++
bool serialize(JSON_Value *_doc_,const char *_key_ = NULL) const;
void deserialize(JSON_Value *_doc_);
```
* Initial basic types to avoid a random value.
The following code shows you how to support a self-define sturct.
See more at [nJson/resource](https://github.com/ABackerNINI/nJson/blob/master/resource).
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
### Non-Intrusive
* Implement the following five functions to support the serialization/deserialization of a structure or class.
```c++
bool is_default_value(const T &val);//ignore when serializing if it is a default value.
				    //Intrusive method return false on default.
void set_key_value(JSON_Object *obj,const char *key,const T &val);//support the serialization of type "T".
void set_key_value(JSON_Array *arr,T &val);//support the serialization of type "std::list<T>".
void get_value(JSON_Object *obj,const char *key,T *val);//support the deserialization of type "T".
value(JSON_Array *arr,const T &val);//support the deserialization of type "std::list<T>".
```
The following code shows you how to support the serialization/deserialization of type "std::list<T>".
See more examples at [nJson/nJson/support](https://github.com/ABackerNINI/nJson/blob/master/nJson/support).
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

@ABacker:abacker.nini@foxmail.com
