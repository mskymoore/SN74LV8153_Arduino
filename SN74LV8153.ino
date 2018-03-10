/*
 * Title:	 SN74LV8153.ino
 * Author:       Sky Moore (mskymoore@gmail.com)
 * Summary:      Arduino code to drive the outputs of the TI SN74LV8153 Serial-to-Parallel Interface
*/

int SERIAL_DATA = 2;//pushing data out on this pin
int NOT_OUTPUT_ENABLE = 8;//ic not output enable pin
int NOT_RESET = 9;//ic not reset pin
int stdDelay = 1;//ms to wait between bits, clock is determined automatically by ic
int byteToWrite = 0;//variable for outgoing shift register data
int shiftRegAddr = 0;//the "address" of the ic determined by pins 2-4 pulled high or low

/* initialize arduino and shift register
 *
 */
void setup() {
  //configure pins as output
  pinMode(SERIAL_DATA, OUTPUT);
  pinMode(NOT_OUTPUT_ENABLE, OUTPUT);
  pinMode(NOT_RESET, OUTPUT);
  //write desired configuration
  digitalWrite(NOT_RESET, LOW);
  digitalWrite(NOT_OUTPUT_ENABLE,LOW);
  digitalWrite(SERIAL_DATA, HIGH);
  //let things settle
  delay(100);
  //enable IC
  digitalWrite(NOT_RESET, HIGH);
}


/* the main loop
 *
 */
void loop() {

//Your code here

}



/* 
 * IC Functions, see datasheet for TI SN74LV8153 SERIAL-TO-PARALLEL INTERFACE pg. 3 for clarification
 */

/* initFrame
 * - prepares IC for writeAddress
 */
void initFrame(){
    digitalWrite(SERIAL_DATA, LOW);
    delay(stdDelay);
    digitalWrite(SERIAL_DATA, HIGH);
    delay(stdDelay);
}

/* writeAddress
 * - prepares IC for 4 bits
 */
void writeAddress(int addr){
    //for bits 0 to 2 of addr
    for ( int i = 0; i < 3; i++ ){ 
      //write addr's ith bit counting from lsb as 0 to SERIAL_DATA pin
      digitalWrite(SERIAL_DATA,bitRead(addr,i));
      delay(stdDelay);
    }
}

/* endFrame
 * - prepares IC for initFrame
 */
void endFrame(){
    digitalWrite(SERIAL_DATA, HIGH);
    delay(stdDelay);  
}

/* writeByte
 * - uses initFrame, writeAddress, and endFrame to write 8 bits to shift register
 */
void writeByte(int data, int addr){
    initFrame();
    writeAddress(addr);
    //for bits 0 to 3 of data
    for ( int i = 0; i < 4; i++ ){ 
      //write data's ith bit counting from lsb as 0 to SERIAL_DATA pin
      digitalWrite(SERIAL_DATA,bitRead(data,i));
      delay(stdDelay);
    }
    endFrame(); 
    initFrame();
    writeAddress(addr);
    //for bits 4 to 7 of data
    for ( int i = 4; i < 8; i++ ){
      //write addr's ith bit counting from lsb as 0 to SERIAL_DATA pin
      digitalWrite(SERIAL_DATA,bitRead(data,i));
      delay(stdDelay);
    }
    endFrame();
}

/*
 * END IC Functions
 */
