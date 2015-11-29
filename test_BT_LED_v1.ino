int led = 13;
byte inByte = 0;
bool ack = 0;
void setup() {  
  Serial.begin(9600); 
  pinMode(led,OUTPUT);
}

void loop() {
  while (!ack) {
    Serial.write("\r\nPress <c> for command list\r\n");
    Serial.write(">");
    inByte = Serial.read();

    if ( inByte == 'c' ) {
      Serial.write(inByte);
      ack = 1;
      printNewLn();
      printCommandList();
      printNewCmdLn();
      break;
    }
      
    delay(3000);
  }
  byte inByte;
  if (Serial.available()) {
    inByte = Serial.read();
    Serial.write(inByte);
    printNewLn();
  }
  
  if ( inByte == 'h' ) {
    digitalWrite(led, HIGH);
    Serial.write("    The LED is ON!");
    printNewCmdLn();
  } else if ( inByte == 'l') {
    digitalWrite(led, LOW);
    Serial.write("    The LED is OFF!");
    printNewCmdLn();
  } else if ( inByte == 'c') {
    printCommandList();
    printNewCmdLn();
  }
}

void printCommandList() {
  Serial.write("    Commands:\r\n");
  Serial.write("      <h>    Turn ON LED\r\n");
  Serial.write("      <l>    Turn OFF LED\r\n");  
  Serial.write("      <c>    Command List"); 
}

void printNewCmdLn() {
  printNewLn();
  Serial.write(">");
}

void printNewLn() {
  Serial.write("\r\n");
}

