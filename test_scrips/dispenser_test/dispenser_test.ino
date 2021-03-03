/**
  Coin dispenser, test Program
  Name: dispenser_test
  Purpose: control a relay to simulate coins being thrown into the arcade machine
  Arduino IDE Version: 1.8.13
  @author Johannes Röring
  @version 1.0.0 03/03/21
  this script is not designed to be used in the final machine, its only used to test the giveCredits and initRelay functions seperately from the main code
  if questions regarding the code arise feel free to contact me on the mail address below 
  or check out my homepage under www.jroering.com which also has a contact page at the top.
  contact: mail@jroering.com
*/

//hardware configuration stuff
#define COIN_RELAY_PIN 0              //put the gpio pin here, that the relay is assigned to
#define COIN_RELAY_ON_STATE HIGH      //set this to LOW if your relay is a Low level trigger based relay

//timing stuff for the relay, values given in milliseconds
#define COIN_RELAY_ON_TIME 250        //set this to the time, the relay needs to be active in order to dispense a coin
#define COIN_RELAY_COOLDOWN_TIME 250  //this value defines how long the function waits after simulating a coin, so the machine can process the last coin signal first

//functional stuff for this test script
#define COIN_AMOUNT 1                 //how many coins should be given in this script

void setup() {
  //this function only runs once
  delay(1000);    //one second safety delay, just for easier recovery etc.
  initRelay();    //function to set up the relays hardware config etc.

  //simulate the defined amount of coins to the machine
  giveCredits(COIN_AMOUNT);

  //now enter the loop(); which is empty
}

void loop() {
  //this function runs infinetly, after setup 
  //nothing to see here
}

//function to initialize the relay in the setup routine
void initRelay() {
  //tell the controller that the GPIO pin should be used as a output
  pinMode(COIN_RELAY_PIN, OUTPUT);
  //set the relay to be off (so the state of the output is defined clearly)
  digitalWrite(COIN_RELAY_PIN, !COIN_RELAY_ON_STATE);
  //end of this function
}

void giveCredits(int val) {
  //control the coin acceptor interface
  //initialize variable i with 0 and check if its below the amount of coinse to dispense
  //then run the function to dispense one coin, add i + 1 and check again if its below the amount of coins to dispense
  //basically run the dispense function untill the amount has been dispensed
  for (int i = 0; i < val; i++) {
    digitalWrite(COIN_RELAY_PIN, COIN_RELAY_ON_STATE);  //turn on the relay
    delay(COIN_RELAY_ON_TIME);  //wait the defined amount of time so the machine can register the coin
    digitalWrite(COIN_RELAY_PIN, !COIN_RELAY_ON_STATE); //turn off the relay again
    delay(COIN_RELAY_COOLDOWN_TIME);  //wait the defined amount of time to prevent giving coins to fast
  }
  //end of this function
}
