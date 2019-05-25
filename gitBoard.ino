/*
  For Leonardo and Due boards only.
*/

#include "Keyboard.h"

// 2 -> top left
// 3 -> top mid
// 4 -> top right
// 5 -> big boy
// 6 -> bot left
// 7 -> bot mid
// 8 -> bot right

String commands[] = {"git add *","git commit -m ''<","4","KEY_RETURN","6","7","8"};

void setup() {
  for(int i = 2; i < 9; i++)
  {
    pinMode(i, INPUT_PULLUP);
  }
  // initialize control over the keyboard:
  Keyboard.begin();
}

void loop() {
  checkKeys();
}

void checkKeys()
{
  for(int i = 0; i < 7; i++)
  {
    if(digitalRead(i+2) == LOW)
    {
      delay(1);
      while(digitalRead(i+2) == LOW)
      {//idle till keyup
        delay(1);
      }
      WriteString(commands[i]);
    }
  }
}

void WriteString(String a)
{
  if(a == "KEY_RETURN")
  {
    Keyboard.write(0xB0);
  }
  else
  {
    for(int i = 0; i < a.length(); i++)
    {
      if(a[i] == '<'){Keyboard.write(0xD8);}
      else if(a[i] == '>'){Keyboard.write(0xD7);}
      else
      {
      Keyboard.write(a[i]);
      }
    } 
  }
}
