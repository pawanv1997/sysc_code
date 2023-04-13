#include "design.cpp"

SC_MODULE(FS_TEST){

    sc_clock clk;
    sc_signal<bool> reset;
    sc_signal<sc_bv<1>> a[n_bit], b[n_bit], sub[n_bit], b_in;
    sc_signal<sc_bv<1>> b_out;

    // Instantiate the N-bit subtrct
    sc_trace_file *pTracefile;

    N_Fullsubtractor* subtrct;


    void stimulus();


    SC_CTOR(FS_TEST):
	    clk("clk", tp)
	{
	    // Connect the signals
	    subtrct = new N_Fullsubtractor("subtrct");

            subtrct->clk(clk);
            subtrct->reset(reset);

	    for(int i = 0; i< n_bit; i++){
		    subtrct->a[i](a[i]);
            	    subtrct->b[i](b[i]);
            	    subtrct->sub[i](sub[i]);
	    }

	    subtrct->b_in(b_in);
	    subtrct->b_out(b_out);


	    SC_THREAD(stimulus);
    }

    ~FS_TEST(){
	    sc_close_vcd_trace_file(pTracefile);
	    
    }
};


void FS_TEST::stimulus(){

	
	//wait(tp/2);
	srand(time(NULL));
	while (true){
		cout << "start" <<endl;
		reset.write(rand() % 2);
		for(int i = 0; i<n_bit;i++){
			a[i].write(rand() % 2);
		        b[i].write(rand() % 2);
		
		}
		b_in.write(rand() % 2);
		cout << "a = ";
		for(int i = n_bit-1; i>=0 ; i--){
			cout << a[i];
		}
		cout << "  ";

		cout << "b = ";
		for(int i = n_bit-1; i>=0 ; i--){
			cout << b[i];
		}
		cout << "  ";
		cout << " b_in = " << b_in.read() << endl;

		cout << "sub = ";
		for(int i = n_bit-1; i>=0 ; i--){
			cout << sub[i];
		}
		cout << " ";

		cout << " b_out = " << b_out.read() << endl;
		cout << " reset = " << reset.read() << endl;
		cout << "end " << endl;
		
		/////////////////////////////////////////  adding singals to waveform ////////////////////////////////////////////////
                sc_bv<n_bit> a0, b0, sub0;

	        pTracefile = sc_create_vcd_trace_file("fs_waveforms");
	        for(int i = 0; i< n_bit; i++){
			a0[i] = a[i].read().get_bit(0);   ///// gets the 0th bit of ith index of a
		        b0[i] = b[i].read().get_bit(0);
		        sub0[i] = sub[i].read().get_bit(0);
	        }

                sc_trace(pTracefile, clk, "clk");
                sc_trace(pTracefile, reset, "reset");
	        sc_trace(pTracefile, a0, "trace_a");
	        sc_trace(pTracefile, b0, "trace_b");
	        sc_trace(pTracefile, sub0, "trace_sub0");
                sc_trace(pTracefile, b_in, "b_in");
                sc_trace(pTracefile, b_out, "b_out");
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		wait(tp);
	}
}


int sc_main(int argc, char* argv[]){
       FS_TEST test("test");
       sc_start(15*tp);
       sc_stop();
       return 0;
} 
