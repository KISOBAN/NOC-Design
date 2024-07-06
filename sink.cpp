// sink.cpp
#include "sink.h"
void sink::receive_data(){
	double ptime;
	packet v_packet;
	if ( sclk.event() ) ack_out.write(false);
	if (packet_in.event() ) 
	{ 
		pkt_recv++ ;
		ack_out.write(true);
		v_packet= packet_in.read();
		ptime = sc_time_stamp().to_seconds() * 1e9; // ADDED LINE OF CODE TO RECORD THE SIMULATION TIME IN WHICH THE PACKET IS RECEIVED
		cout << "			New Pkt:  " << (int)v_packet.data<< " is received from source: " << (int)v_packet.id  << " by sink:  " << (int)sink_id.read() << endl;
		cout << "			Packet #" << (int)v_packet.data << " received time: " << ptime << " ns \n";

	}
}
