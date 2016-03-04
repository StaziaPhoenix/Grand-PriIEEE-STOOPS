
// Test LED
int led = 13;

// Byte (one character) read in from Virtual Serial COMM (Bluetooth)
byte inByte = 0;

// Acknowledgment variable (while-loop sentinel)
byte ack = 0;

// Setup
void setup() {  
  // Open up Bluetooth Virtual Serial COMM port
  Serial.begin(9600); 
  
  // Configure digital for OUTPUT
  pinMode(led,OUTPUT);
}

// Main
void loop() {
  while (!ack) {
    ack = getAck();    
    delay(3000);
  }
  //byte serialCmd = getSerialCmd();

  //doSerialCmd(serialCmd);

  doSerialCmd(getSerialCmd());

}

byte getAck() {
Serial.write("\r\nPress <c> for command list\r\n");
    Serial.write(">");
    byte inByte = Serial.read();

    if ( inByte == 'c' ) {
      Serial.write(inByte);
      ack = 1;
      printNewLn();
      printCmdList();
      printNewCmdLn();
      return 1;
    }   
    return 0;
}

// Performs serial command based on user input
void doSerialCmd( byte cmd ) {
  switch( cmd ) {
    // Turn LED HIGH
    case ('h'):
      ledON();
      printNewCmdLn();
      break;
  
    // Turn LED LOW
    case ('l'):
      ledOFF();
      printNewCmdLn();
      break;
  
    // Display CMD List
    case ('c'):
      printCmdList();
      printNewCmdLn();
      break;
  }
}

// Prompts User for input serial command
//    Returns serial command
byte getSerialCmd() {
  byte inByte;
  if (Serial.available()) {
    inByte = Serial.read();
    Serial.write(inByte);
    printNewLn();
    return inByte;
  }
}

// Turns LED ON and writes to Serial
void ledON() {
  digitalWrite(led, HIGH);
  Serial.write("    The LED is ON!");
}

// Turns LED OFF and writes to Serial
void ledOFF() {
  digitalWrite(led, LOW);
  Serial.write("    The LED is OFF!");
}

// Prints the command list
void printCmdList() {
  Serial.write("    Commands:\r\n");
  Serial.write("      <h>    Turn ON LED\r\n");
  Serial.write("      <l>    Turn OFF LED\r\n");  
  Serial.write("      <c>    Command List"); 
}

// Prints a new command line cursor
void printNewCmdLn() {
  printNewLn();
  Serial.write(">");
}

// Prints a modified new line
void printNewLn() {
  Serial.write("\r\n");
}
