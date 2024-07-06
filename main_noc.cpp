// main.cpp
#include "systemc.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "packet.h"
#include "source.h"
#include "sink.h"
#include "router.h"


int sc_main(int argc, char *argv[])
{
	sc_signal<packet> si_source[16];
	sc_signal<packet> si_input[4]; // input packets
	sc_signal<packet> si_zero[16]; // zero packets
	sc_signal<packet> si_sink[16]; 
	sc_signal<packet> si_output[4];

	sc_signal<packet> dummy[128]; 
	sc_signal<bool> dummyack[128]; 

	sc_signal<bool>  si_ack_src[16],si_ack_ou[4];
	sc_signal<bool>  si_ack_sink[16],si_ack_in[4];
	sc_signal<bool>  si_ack_zero[16];
	sc_signal<sc_uint<4> >  id0,id1,id2,id3,id4,id5,id6,id7,id8,id9,id10;
	sc_clock s_clock("S_CLOCK", 5, SC_NS, 0.5, 0.0, SC_NS); // source clock
	sc_clock r_clock("R_CLOCK", 5, SC_NS, 0.5, 10.0, SC_NS);	// router clock
	sc_clock d_clock("D_CLOCK", 5, SC_NS, 0.5, 10.0, SC_NS);	// destination clock
	
	// Module instiatiations follow
	// Note that modules can be connected by hooking up ports 
	// to signals by name or by using a positional notation
	source source0("source0");
	source0(si_source[0], id0, si_ack_src[0], s_clock);
	//creating duplicate signals for sending more than 1 packet at at time from 1 source


	source source1("source1");
	source1(si_source[1], id1, si_ack_src[1], s_clock);
	
	source source2("source2");
	source2(si_source[2],id2,si_ack_src[2],s_clock);

	source source3("source3");
	source3(si_source[3],id3,si_ack_src[3],s_clock);
	
	source source4("source4");
	source4(si_source[4],id4,si_ack_src[4],s_clock);

	source source5("source5");
	source5(si_source[5],id5,si_ack_src[5],s_clock);

	sink sink0("sink0");
	sink0(si_sink[0], si_ack_sink[0],id0,d_clock);	

	sink sink1("sink1");
	sink1(si_sink[1], si_ack_sink[1],id1,d_clock);
	
	sink sink2("sink2");
	sink2(si_sink[2],si_ack_sink[2],id2,d_clock);

	sink sink3("sink3");
	sink3(si_sink[3],si_ack_sink[3],id3,d_clock);

	sink sink4("sink4");
	sink4(si_sink[4],si_ack_sink[4],id4,d_clock);

	sink sink5("sink5");
	sink5(si_sink[5], si_ack_sink[5],id5,d_clock);
	//need codes
	//need codes
	//need codes


	router router0("router0");
	// hooking up signals to ports by name
	router0.in0(si_source[0]);
	router0.in2(si_input[0]);
	router0.in3(si_input[3]);
	router0.in1(si_zero[0]); // this is a zero packet since there is in1 refers to North and there is no north in the first router
	router0.in4(si_zero[1]); // this is a zero packet since there is in4 refers to West and there is no west in the first router

	router0.router_id(id0);

	router0.out0(si_sink[0]);
	router0.out2(si_output[0]);
	router0.out3(si_output[3]);
	router0.out1(si_zero[2]);
	router0.out4(si_zero[3]);

	router0.inack0(si_ack_sink[0]);
	router0.inack2(si_ack_in[0]);
	router0.inack3(si_ack_in[3]);
	router0.inack1(si_ack_zero[0]);
	router0.inack4(si_ack_zero[1]);

	router0.outack0(si_ack_src[0]);
	router0.outack2(si_ack_ou[0]);
	router0.outack3(si_ack_ou[3]);
	router0.outack1(si_ack_zero[2]);
	router0.outack4(si_ack_zero[3]);

	router0.rclk(r_clock);

	router router1("router1");
	// hooking up signals to ports by name
	router1.in0(si_source[1]);
	router1.in2(si_zero[4]);	
	router1.in3(si_input[1]);
	router1.in4(si_output[0]);
	router1.in1(si_zero[5]);

	router1.router_id(id1);

	router1.out0(si_sink[2]);
	router1.out2(si_zero[6]);
	router1.out3(si_output[1]);
	router1.out4(si_input[0]);
	router1.out1(si_zero[7]);

	router1.inack0(si_ack_sink[2]);
	router1.inack2(si_ack_zero[4]);
	router1.inack3(si_ack_in[1]);
	router1.inack4(si_ack_ou[0]);
	router1.inack1(si_ack_zero[5]);

	router1.outack0(si_ack_src[1]);
	router1.outack2(si_ack_zero[6]);
	router1.outack3(si_ack_ou[1]);
	router1.outack4(si_ack_in[0]);
	router1.outack1(si_ack_zero[7]);

	router1.rclk(r_clock);
	router router2("router2");
	// hooking up signals to ports by name
	router2.in0(si_source[2]);
	router2.in2(dummy[0]);
	router2.in3(dummy[1]);
	router2.in4(dummy[2]);
	router2.in1(dummy[3]);

	router2.router_id(id2);

	router2.out0(dummy[4]);
	router2.out2(si_sink[3]); // east output going to sink 3
	router2.out3(dummy[5]);
	router2.out4(dummy[6]);
	router2.out1(dummy[7]);

	router2.inack0(dummyack[0]);
	router2.inack2(si_ack_sink[3]); // east 
	router2.inack3(dummyack[1]);
	router2.inack4(dummyack[2]);
	router2.inack1(dummyack[3]);

	router2.outack0(dummyack[4]);
	router2.outack2(si_ack_src[2]); // east
	router2.outack3(dummyack[5]);
	router2.outack4(dummyack[6]);
	router2.outack1(dummyack[7]);

	router2.rclk(r_clock);
	

	router router3("router3");
	// hooking up signals to ports by name
	router3.in0(si_source[3]);
	router3.in2(dummy[9]);// this cant be a port since there is no east in the furthermost router
	router3.in3(dummy[8]);
	router3.in4(dummy[10]);
	router3.in1(dummy[11]); // this cant be a port since there is no north in the 4th router

	router3.router_id(id3);

	router3.out0(dummy[12]);
	router3.out2(dummy[14]);
	router3.out3(dummy[13]);
	router3.out4(si_sink[4]); // south port
	router3.out1(dummy[15]);

	router3.inack0(dummyack[8]);
	router3.inack2(dummyack[10]);
	router3.inack3(dummyack[9]);
	router3.inack4(si_ack_sink[4]);
	router3.inack1(dummyack[11]);

	router3.outack0(dummyack[12]);
	router3.outack2(dummyack[14]);
	router3.outack3(dummyack[13]);
	router3.outack4(si_ack_src[3]);
	router3.outack1(dummyack[15]);

	router3.rclk(r_clock);
	

	router router4("router4");
	// hooking up signals to ports by name
	router4.in0(si_source[4]);
	router4.in2(dummy[17]);		// this cant be a port since there is no east in the furthermost router
	router4.in3(si_source[3]);
	router4.in4(dummy[18]); 
	router4.in1(dummy[19]); 	// this cant be a port since there is no north in the 4th router

	router4.router_id(id4);

	router4.out0(dummy[20]);
	router4.out2(dummy[21]);    // 2 - east
	router4.out3(dummy[22]);   // 3 - south
	router4.out4(si_sink[5]); // 4 - west
	router4.out1(dummy[23]); // 1 - north

	router4.inack0(dummyack[16]);
	router4.inack2(dummyack[17]);
	router4.inack3(dummyack[18]);
	router4.inack4(si_ack_sink[5]);
	router4.inack1(dummyack[19]);

	router4.outack0(dummyack[20]);
	router4.outack2(dummyack[21]);
	router4.outack3(dummyack[22]);
	router4.outack4(si_ack_src[4]);
	router4.outack1(dummyack[23]);

	router4.rclk(r_clock);



	router router5("router5");
	// hooking up signals to ports by name
	router5.in0(si_source[5]);
	router5.in2(dummy[25]);// this cant be a port since there is no east in the furthermost router
	router5.in3(dummy[26]);
	router5.in4(dummy[27]);
	router5.in1(dummy[28]); // this cant be a port since there is no north in the 4th router

	router5.router_id(id5);

	router5.out0(dummy[29]);
	router5.out2(dummy[30]); // east
	router5.out3(si_sink[6]); // south
	router5.out4(dummy[31]); // west
	router5.out1(dummy[32]); // north

	router5.inack0(dummyack[24]);
	router5.inack2(dummyack[25]);
	router5.inack3(si_ack_sink[6]);
	router5.inack4(dummyack[26]);
	router5.inack1(dummyack[27]);

	router5.outack0(dummyack[28]);
	router5.outack2(dummyack[29]);
	router5.outack3(si_ack_src[5]);
	router5.outack4(dummyack[30]);
	router5.outack1(dummyack[31]);

	router5.rclk(r_clock);

//need 64 code statement

  	//need codes

	//need codes
	//need codes

//sc_start(0, SC_NS);
  // tracing:
	// trace file creation
	sc_trace_file *tf = sc_create_vcd_trace_file("graph");
	// External Signals
	sc_trace(tf, s_clock, "s_clock");
	sc_trace(tf, d_clock, "d_clock");
	sc_trace(tf, si_source[0], "si_source[0]");
	sc_trace(tf, si_source[1], "si_source[1]");
	//need codes
	//need codes
	sc_trace(tf, si_sink[0], "si_sink[0]");
	sc_trace(tf, si_sink[1], "si_sink[1]");
	//need codes
	//need codes

	id0.write(0);
	id1.write(1);
	id2.write(2);
	id3.write(3);
	id4.write(4);
	id5.write(5);
	//need codes
	//need codes

	cout << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << endl << " 1X2 mesh NOC simulator containing 2 5x5 Wormhole router " << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "This is the simulation of a 1x2 Wormhole router.  " << endl; 
	cout << "We assume the router has 5 input/output ports, with 4 buffers per input port " << endl;
	cout << "and each flit has 21 bits width " << endl;
	cout << "  Press \"Return\" key to start the simulation..." << endl << endl;

	getchar();
	sc_start((10*25)+124, SC_NS); // during [(10*125)+124] ns 10 packets will be sent and received 

	sc_close_vcd_trace_file(tf);

	cout << endl << endl << "-------------------------------------------------------------------------------" << endl;
	cout << "End of switch operation..." << endl;
	cout << "Total number of packets sent:\n source0:" <<  source0.pkt_snt<< " source1: " << source1.pkt_snt << "\nsource2: " << source2.pkt_snt << "\nsource3: " << source3.pkt_snt << "\nsource4: "<< source4.pkt_snt << "\nsource5: "<< source5.pkt_snt<< endl;//need codes to be added
	cout << "\nTotal number of packets received:\n sink1:  " <<  sink1.pkt_recv << "\nsink2: " << sink2.pkt_recv << "\nsink3: " << sink3.pkt_recv <<  "\nsink4: " << sink4.pkt_recv << "\nsink5: " << sink5.pkt_recv<<endl;//need codes to be added
	cout << "-------------------------------------------------------------------------------" << endl;
    cout << "  Press \"Return\" key to end the simulation..." << endl << endl;
	getchar();
  return 0;

}



