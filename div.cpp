#include "systemc.h"
#include "const.h"
SC_MODULE(division){
	sc_in<sc_uint<N>> a;
	sc_in<sc_uint<N>> b;
	sc_out<sc_uint<N>> out;
	sc_in<bool> rst;
	sc_in<bool> clk;

	void process(){
	sc_uint<N> a1;
	sc_uint<N> b1;
		sc_uint<N> p1;
		a1=a.read();
		b1=b.read();
		p1=0;
		if(rst){
			out.write(0);
		}
		else{
		for(int i=0;i<N;i++){
			p1=p1<<1;
			p1[0]=a1[N-1];
			a1=a1<<1;
			p1 = p1-b1;
			if(p1[N-1] == 1){
				a1[0] = 0;
				p1 = p1 + b1;
			}
			else
				a1[0] = 1;
		}
		out.write(a1);
		}

	}

	SC_CTOR(division):
		clk("clk"),
		a("a"),
		b("b"),
		rst("reset"),
		out("div")

	{
		SC_METHOD(process);
		sensitive<<clk.pos();
		sensitive<<rst.pos();
		sensitive<<a<<b;
	}

};

