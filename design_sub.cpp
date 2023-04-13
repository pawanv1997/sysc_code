#include "fsub.cpp"

SC_MODULE(N_Fullsubtractor){
	sc_in<sc_bv<1>> a[n_bit], b[n_bit], b_in;
	
        sc_out<sc_bv<1>> b_out;
        sc_out<sc_bv<1>> sub[n_bit];
        sc_in<bool> clk, reset;

	sc_signal<sc_bv<1>> carry[n_bit];

	Fullsubtractor* FS[n_bit];
	int i;

	


	SC_CTOR(N_Fullsubtractor){		
		for(i = 0; i<n_bit; i++){
			FS[i] = new Fullsubtractor(sc_gen_unique_name("FS"));
			FS[i]->a(a[i]);
			FS[i]->b(b[i]);

			if(i==0){
				FS[i]->b_in(b_in);
			}
			else{
				FS[i]->b_in(carry[i]);
				
			}

			FS[i]->sub(sub[i]);

			if(i==n_bit-1){
				FS[i]->b_out(b_out);
			}
			else{
				FS[i]->b_out(carry[i+1]);
			}

			FS[i]->clk(clk);
			FS[i]->reset(reset);
			
		}
		//SC_METHOD(n_fulladder_func);
	}

	/*~N_FullAdder(){
		for(i = 0; i<n_bit; i++){
			delete FS[i];
		}*/	
};
