#include "systemc.h"
#include "const.h"
SC_MODULE(lshift){
	sc_in<sc_bv<16>> a;
	sc_out<sc_bv<16>> o;
//	sc_in<bool> clk,reset;

	void process()
	{
		o.write(a.read()<<1);
	}
	 SC_CTOR(lshift){
		 SC_THREAD(process);
		 sensitive<<a;
		// sensitive<<clk;
		 //sensitive<<reset;
	 }

};
