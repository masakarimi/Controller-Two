
// set pin numbers:

int buttons[] = {2, 3, 4};


// variables will change:
int buttonState[] = {0, 0, 0};                                  // variable for reading the pushbutton status
int _buttonState[] = {0, 0, 0};
int lastButtonState[] = {0, 0, 0};

long lastSend;
void setup() {
  for (int i = 0; i <= 2; i++ ) {
    pinMode (buttons[i], INPUT);
  }

  Serial.begin(9600);
}

void loop() {

  for (int i = 0; i <= 2; i++ )
  { // read the state of the pushbutton value:
    _buttonState[i] = digitalRead(buttons[i]);
  }

  if (lastButtonState[0] != _buttonState[0]) {
    if (_buttonState[0] == 1) {
      buttonState[0] = 1;
      
      //Serial.println(buttonState[0]);
    } else {
      buttonState[0] = 0;
    }
    lastButtonState[0] = _buttonState[0];

  }

  if (lastButtonState[1] != _buttonState[1]) {
    if (_buttonState[1] == 1) {
      buttonState[1] = 2;
      
      //Serial.println(buttonState[0]);
    } else {
      buttonState[1] = 0;
    }
    lastButtonState[1] = _buttonState[1];

  }
 
  if (lastButtonState[2] != _buttonState[2]) {
    if (_buttonState[2] == 1) {
      buttonState[2] = 3;
      
      //Serial.println(buttonState[0]);
    } else {
      buttonState[2] = 0;
    }
    lastButtonState[2] = _buttonState[2];

  }


  /*
    if (_buttonState[1] == 1) {
      buttonState[1] = 2;
    } else {
      buttonState[1] = 0;
    }

    if (_buttonState[2] == 1) {
      buttonState[2] = 3;
    } else {
      buttonState[2] = 0;
    }
  */
  sendData(buttonState, (sizeof(buttonState) / sizeof(int)), 20); // sendData(buttonState, (sizeof(buttonState) / sizeof(int)), 20); //execute the sendData function
  //(sizeof(sensorVals)/sizeof(int)) is used because we are passing an
  //array into the function and arduino can't determine the size of the
  //array in that s0cope

}

void sendData(int sVal[], int arLength, int sDel)               //this is the function that sends data out the Serial port
{ //the format is   "sensorvalue1,sensorvalue2,sensorvalue3,..."
  if (millis() - lastSend >= sDel)                            //simple timer controls how often it sends
  {
    for (int i = 0; i < arLength; i++)                        //for loop is used to package up all the values in the array
    {
      if (i < arLength - 1)                                   //this checks what to do if it ISN'T the last value
      { //it uses Serial.print and adds the comma to the string
        Serial.print(sVal[i]);
        Serial.print(",");
      }
      else
      {
        Serial.println(sVal[i]);                              //there is a different command for the final value
      }                                                     //we use Serial.println because the server looks for the newline character to know the end of the messages
    }
    Serial.print('\n');                                      //it also doesn't need the comma because it is the last value
    lastSend = millis();                                      //save the time that the value is sent, so the timer will work
  }
}
