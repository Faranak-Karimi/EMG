/* F5 TEST FOR ESP2PY
 * Written by Junicchi
 * https://github.com/KebabLord/esp_to_python
 * It simply increases and returns a variable everytime a python req came */

#include "ESP_MICRO.h" //Include the micro library 
int testvariable = 0;
int myArray[10];   //create array with however many spots you need
String my = "faranak";
int X = 0;         //place holder for the array index spot
//int x = 192;
void setup(){
  Serial.begin(115200); // Starting serial port for seeing details
  start("Ap","*srl*780#");  // EnAIt will connect to your wifi with given details
}
void loop(){
    waitUntilNewReq();  //Waits until a new request from python come
  /* increases index when a new request came
  //if(Serial.available()){*/
  
//if ( Serial.available () > 0 ) {
  my = Serial.read();   //put number into the array
 // X = X + 1;                         //change to the next array index for next number
//}
 //  x = Serial.read();
       delay(10);
  //testvariable += 1;
  returnThisStr(my); //Returns the data to python
//  delay(10);
}
