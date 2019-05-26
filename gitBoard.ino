/*
  Add switches to the pins defined below here. pin > switch > ground
  You can use the modifier layer in 2 different ways:
  As a combination lock to print your username and or password.
  Or as a 2nd layer for more commands. Check the code to see what you need to comment out and fill in to enable this mode.
*/

#include "Keyboard.h"
#include "Secret.h" //don't forget to update this to the name of the file that holds your secret data!

// 2 -> top left
// 3 -> top mid
// 4 -> top right
// 5 -> big boy
// 6 -> bot left
// 7 -> bot mid
// 8 -> bot right

String commands[] = {"git add *","git commit -m ''<","git push origin ","|","git status|","git reset --hard","git checkout -b "};
String commands_lower[] = {"","","","","","",""}; //this array is empty because we're using the board in password mode
int modifier = 0;
int modDown = 0;
long oldMillis;
int pressedHistory[] = {0,0,0};

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
    if(i == 3) //we want to skip the 4th button being read because its the modifier key
    {
      if(digitalRead(5) == LOW)
      {
        if(modDown == 0)
        {
          modDown = 1;
          oldMillis = millis();
        }
        modifier = 1;
      }
      else
      {
        if(millis() - oldMillis < 200 && modDown == 1 && millis() - oldMillis > 50)
        {
          WriteString(commands[3]);
        }
        modifier = 0;
        modDown = 0;
      }
    }
    else if(digitalRead(i+2) == LOW)
    {
      delay(1);
      while(digitalRead(i+2) == LOW)
      {//idle till keyup
        delay(5);
      }
      if(modifier == 0)
      {
        WriteString(commands[i]);
      }
      else if(modifier == 1)
      {
        WriteString(commands_lower[i]);
        UpdatePressedHistory(i+2); 
        CheckSecretCombo(); //comment out this line if you want to use your modifier layer as extra commands instead of a pin for password / username
      }
      delay(5);
    }
  }
}

void UpdatePressedHistory(int key)
{
  pressedHistory[0] = pressedHistory[1];
  pressedHistory[1] = pressedHistory[2];
  pressedHistory[2] = key;
}

void CheckSecretCombo()
{
  if(pressedHistory[0] == USEONE && pressedHistory[1] == USETWO && pressedHistory[2] == USETHREE)
  {
    WriteString(USERNAME);
  }
  if(pressedHistory[0] == PASONE && pressedHistory[1] == PASTWO && pressedHistory[2] == PASTHREE)
  {
    WriteString(PASSWORD);
  }
}

void WriteString(String a)
{
  for(int i = 0; i < a.length(); i++)
  {
    if(a[i] == '<'){Keyboard.write(0xD8);}
    else if(a[i] == '>'){Keyboard.write(0xD7);}
    else if(a[i] == '|'){Keyboard.write(0xB0);}
    else
    {
    Keyboard.write(a[i]);
    }
  } 
}
