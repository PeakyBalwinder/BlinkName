const int buttonPin = 2;  
bool buttonPressed = false;  // Flag to track if the button is pressed

void dot()
{
  digitalWrite(LED_BUILTIN, HIGH);  // Turns on the built-in LED
  delay(200);  // Delay for 200 milliseconds
  digitalWrite(LED_BUILTIN, LOW);  // Turns off the built-in LED
  delay(100);  // Delay for 100 milliseconds
}

void dash()
{
  digitalWrite(LED_BUILTIN, HIGH);  // Turns on the built-in LED
  delay(600);  // Delay for 600 milliseconds 
  digitalWrite(LED_BUILTIN, LOW);  // Turns off the built-in LED
  delay(100);  // Delay for 100 milliseconds
}

void blinkCharacter(char c)
{
  switch (c)
  { 
    case 'X':
      dash();
      dot();
      dash();
      break;
    case 'A':
      dot();
      dash();
      break;
    case 'R':
      dot();
      dash();
      dot();
      break;
    case 'T':
      dash();
      break;
    case 'I':
      dot();
      dot();
      break;
    case 'K':
      dash();
      dot();
      dash();
      break;
    default:
      // Handles other characters if typed
      break;
  }
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);  // Sets the built-in LED pin as the output
  pinMode(buttonPin, INPUT_PULLUP);  // Sets the button pin as an input 
  Serial.begin(9600);  
}

void loop()
{
  buttonPressed = digitalRead(buttonPin) == LOW;  // Checks if the button is pressed 

  if (buttonPressed)
  {
    Serial.println("Button pressed. Resetting...");
    delay(1000);  // Delay to give gap in between button pressing
    
    // Clears any pending serial input
    while (Serial.available())
    {
      Serial.read();
    }

    // Clear any ongoing LED blinking
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
  
  if (Serial.available() > 0)
  {
    String name = Serial.readString();  // Reads the incoming serial data as a string
    name.toUpperCase();  // Convert the name to uppercase

    for (int i = 0; i < name.length(); i++)
    {
      if (name[i] == ' ')
      {
        delay(1000); // Gap for word separation
      }
      else
      {
        blinkCharacter(name[i]);  // Blinks the LED to represent the character
        delay(400); // Gap between characters
      }
    }
    delay(2000); // Gap between name transmissions
  }
}
