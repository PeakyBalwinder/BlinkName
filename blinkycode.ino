const int buttonPin = 2;  // Change this to the pin you connect the button to
bool buttonPressed = false;

void dot()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}

void dash()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(600);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
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
      // Handle other characters if needed
      break;
  }
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Using internal pull-up resistor
  Serial.begin(9600);
}

void loop()
{
  buttonPressed = digitalRead(buttonPin) == LOW;

  if (buttonPressed)
  {
    Serial.println("Button pressed. Resetting...");
    delay(1000);  // Debounce delay
    
    // Clear any pending serial input
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
    String name = Serial.readString();
    name.toUpperCase();

    for (int i = 0; i < name.length(); i++)
    {
      if (name[i] == ' ')
      {
        delay(1000); // Gap for word separation
      }
      else
      {
        blinkCharacter(name[i]);
        delay(400); // Gap between characters
      }
    }
    delay(2000); // Gap between name transmissions
  }
}
