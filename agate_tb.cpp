#include "systemc.h"
#include "agate.cpp"

int sc_main(int argc,char* argv[])
{
	sc_signal<bool> a;
	sc_signal<bool> b;
	sc_signal<bool> out;
//trace file pointer to store the waveform in VCD
	sc_trace_file *tf;

	agate and1("And gate");
	and1.a(a);
	and1.b(b);
	and1.out(out);

	tf=sc_create_vcd_trace_file("and gate");
	tf->set_time_unit(1,SC_NS);

	//trace file signal
	sc_trace(tf,a,"a");
	sc_trace(tf,b,"b");
	sc_trace(tf,out,"out");

	a=0;
	b=0;
	sc_start(1,SC_NS);
	cout<<"a= "<<a<<"b= "<<b<<"out"<<out<<endl;

	a=1;
	b=0;
	sc_start(1,SC_NS);
	cout<<"a= "<<a<<"b= "<<b<<"out"<<out<<endl;


	a=0;
	b=1;
	sc_start(1,SC_NS);
	cout<<"a= "<<a<<"b= "<<b<<"out"<<out<<endl;


	a=1;
	b=1;
	sc_start(1,SC_NS);
	cout<<"a= "<<a<<"b= "<<b<<"out"<<out<<endl;


	a=0;
	b=1;
	sc_start(1,SC_NS);
	cout<<"a= "<<a<<"b= "<<b<<"out"<<out<<endl;

	sc_stop();

	sc_close_vcd_trace_file(tf);

	cout<<"Finished at time"<<sc_time_stamp<<endl;
	return 0;

}
