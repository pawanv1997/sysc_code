#include <systemc.h>
#include "const.h"

// Half subtractor module
SC_MODULE(Halfsubtractor) {
    sc_in<sc_bv<1>> a, b;
    sc_out<sc_bv<1>> sub, carry;
    sc_in<bool> clk, reset;

    void half_subtractor_process() {
	    if(reset){
		    sub.write(0);
		    carry.write(0);
	    }
	    else {
		    sub.write(a.read() ^ b.read());        // XOR gate for sub
                    carry.write(~(a.read()) & b.read());     // AND gate for carry
	    }
    }

    SC_CTOR(Halfsubtractor) {
        SC_METHOD(half_subtractor_process);
        sensitive << a << b;
	sensitive << clk.pos();
    }
};

