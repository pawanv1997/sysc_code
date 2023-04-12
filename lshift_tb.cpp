#include "lshift.cpp"
int sc_main(int argc, char* argv[]) {
    sc_signal<sc_bv<16>> a;
    sc_signal<sc_bv<16>> o;

    lshift shifter("lshift");
    shifter.a(a);
    shifter.o(o);

    a =16'b01111; // set input value

    sc_start();

    cout << "Result: " << o.read() << endl;

    return 0;
}
