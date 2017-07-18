## About
this is a C++0x serialize-to-json lib based on parson(https://github.com/kgabis/parson.git).

## Features
* C++0x Compatible
* intrusive or non-intrusive

## Installation
run ```git clone https://github.com/ABackerNINI/nJson.git```.
copy ```nJson/nJson``` to your source code tree.
see ```nJson/resource``` to know how to use it.
run ```make``` to compile and run the test.

## Examples
### Intrusive
* implement member function ```bool serialize(JSON_Value *_doc_,const char *_key_ = NULL) const;``` and ```void deserialize(JSON_Value *_doc_)``` to support the serialization/deserialization of a structure or class.
* initial basic types to avoid a random value.
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
	char 											c;
	bool 											b;
	short 											s;
	int 											i;
	float 											f;
	long long 										ll;
	double 											d;

	//const char * test
	const char 										*pc;

	//map list test
	std::map<std::string,std::string> 				m;
	std::list<int>									l;
	std::list<std::map<std::string,std::string> >	lm;

	//inner object test
	InnerRes 										ir;
	InnerRes 										*pir;
	InnerRes 										**ppir;
	std::map<std::string,InnerRes>					mir;
	std::map<std::string,InnerRes*>					mpir;
};
```
### Non-Intrusive
```c++

```

@ABacker:abacker.nini@foxmail.com
