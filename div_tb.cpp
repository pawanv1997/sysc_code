#include "div.cpp"
//#include "const.h"

SC_MODULE(div_test){

	sc_signal<sc_uint<N>> a, b;
	sc_signal<sc_uint<N>> out;
	sc_signal<bool> rst;
	sc_clock clk;
	

	division div1;

	sc_trace_file *pTracefile;

	void stimulus();

	SC_CTOR(div_test):
		clk("test_clk", tp),
		a("test_a"),
		b("test_b"),
		rst("test_reset"),
		out("test_div"),
		div1("div1")
	{
		div1.a(a);
		div1.b(b);
		div1.out(out);
		div1.rst(rst);
		div1.clk(clk);

		pTracefile = sc_create_vcd_trace_file("division_vcd_waves");

		sc_trace(pTracefile, rst, "reset");
		sc_trace(pTracefile, clk, "clk");
		sc_trace(pTracefile, a, "input_a");
                sc_trace(pTracefile, b, "input_b");
                sc_trace(pTracefile, out, "out");
                


		SC_THREAD(stimulus)
	}

	~div_test(){
		sc_close_vcd_trace_file(pTracefile);
	}   ////  here ~ is known as destructor operator of module which is a member function of full_adder_test module that is automatically called by systemc framework. It performs any necessary cleanups like closing file, freeing memory, or releasing resources.
};


void div_test::stimulus(){

	//wait(tp/2);
	
	srand(time(NULL));
	while(true){
		rst.write(rand()%2);
		a.write(rand() );
		b.write(rand());
		
		
 
		cout << " reset= " << rst.read() << " input_a = " << a.read() << " input_b = " << b.read() << " division = " << out.read() << endl;
		wait(tp);
	}
}


int sc_main(int agrc, char* argv[]){
	div_test test("div_test");
	sc_start(15*tp);
	sc_stop();
	return 0;
}

