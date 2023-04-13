#include "hsub.cpp"

// Full subtractor module
SC_MODULE(Fullsubtractor) {
    sc_in<sc_bv<1>> a, b, b_in;
    sc_out<sc_bv<1>> b_out;
    sc_out<sc_bv<1>> sub;
    sc_in<bool> clk, reset;

    sc_signal<sc_bv<1>> sub_i;
    sc_signal<sc_bv<1>> carry_0, carry_1;

    Halfsubtractor* ha1;
    Halfsubtractor* ha2;

    void full_subtractor_process() {	    
	b_out.write(carry_1.read() | carry_0.read());
    }

    SC_CTOR(Fullsubtractor){

	    ha1 = new Halfsubtractor("ha1");
            ha2 = new Halfsubtractor("ha2");
	
	    ha1->a(a);
            ha1->b(b);
            ha1->sub(sub_i);
            ha1->carry(carry_0);
	    ha1->clk(clk);
	    ha1->reset(reset);

            ha2->a(sub_i);
            ha2->b(b_in);
            ha2->sub(sub);
            ha2->carry(carry_1);
	    ha2->clk(clk);
	    ha2->reset(reset);


            SC_METHOD(full_subtractor_process);
            sensitive << carry_0 << carry_1;
    }
};
