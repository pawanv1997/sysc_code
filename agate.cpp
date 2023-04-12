#include "systemc.h"
SC_MODULE(agate){
	sc_in<bool> a;
	sc_in<bool> b;
	sc_out<bool> out;

	void func(){
		out.write(a.read()&b.read());
	}
	SC_CTOR(agate){
		SC_METHOD(func);
		sensitive<< a;
		sensitive<< b;
	}

};
