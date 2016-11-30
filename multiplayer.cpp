#include "ddr.h"

// REMEMBER TO KEEP CALLING THESE FUNCTIONS IF TIMEOUT HAPPENS 


// Some necessary functions from eClass:
uint32_t read_from_serial3() { 
    uint32_t num;
    Serial3.readBytes( (char*)&num, 4);
    return num;
}
uint32_t write_to_serial3(uint32_t num){
    Serial3.write( (uint8_t*)&num, 4);
}    





/* This will be a modified version of the functions
we made for assignment 1 part b. This is the server mode. 
There will be no encyption, instead of sending keys we will 
send "songs"
The function will return the "song"
returns 0 if failed
*/
// function for server arduino to communicate with client and receive ckey
uint32_t server_setup(uint32_t skey) {

    // initializing variables 
    uint32_t CR;
    uint32_t ckey;
    uint32_t start_time2;
    uint32_t end_time2;
    uint8_t ACK = 'A';

    // clears buffer to ensure nothing is left over from previous code
    uint32_t start_time = millis(); // starts a timer to indicate timeout
    while(Serial3.available() < 0) { } // waits for initializing by client
    
    
    
    // waits for acknowledgement from client
    while(CR != 'C') {
        CR = Serial3.read();
uint32_t stop_time = millis(); // ends timer
    // if total time elapsed > 1000 returns 0 to cause timeout
    if((stop_time - start_time) > 1000) {
        return 0;
      
    }
    }
     
   
    ckey = read_from_serial3(); // read the ckey!
    
    start_time2 = millis(); // start timer for timeout
    Serial3.write(ACK);
    write_to_serial3(skey);

        while(Serial3.read() != 'A') {
        }


    return ckey;
}

// function for client to communicate with server
uint32_t client_setup(uint32_t ckey) {
  

    // initializing variables
    uint32_t AR;
    uint32_t skey;
   
    uint32_t end_time;
    // uint32_t ckey = index_compute(randomkey); // computes ckey
    uint8_t value = 'C';

    uint32_t start_time = millis(); // timer
    Serial3.write(value); // send a "C"
    write_to_serial3(ckey); // send ckey

    while( Serial3.read() != 'A') {
        end_time = millis();
        if((end_time - start_time) > 1000) {
            return 0;
        }
    }

    
    // reads exchanged skey
    skey = read_from_serial3();
    
    
    // sends over final acknowledgement
    uint8_t value2 = 'A';
    Serial3.write(value2);
    
    // clears buffer for data transfer and returns skey
    return skey;
    
}