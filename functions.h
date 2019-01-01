#include <Arduino.h> // This include let's me use strings.

int fade=0;
int saveColorR;
int saveColorG;
int saveColorB;
double fadeIn=0;



void printValueWithTabs(String printVariableName,double variableValue, int spacing){         
           if(spacing==1)
            Serial.print("\t");
           if(spacing==2)
            Serial.print("\t");Serial.print("\t");
           if(spacing==3)
            Serial.print("\t");Serial.print("\t");Serial.print("\t");
           if(spacing=4)
            Serial.print("\t");Serial.print("\t");Serial.print("\t");Serial.print("\t");
           Serial.print(printVariableName);
           Serial.print(": ");
           Serial.println(variableValue); 
    }
void printLetter(String setLetter){
  Serial.print("Note played: ");Serial.println(setLetter);
}

void writeToOutput(int arrayNumber, double velocityBlue, double pitchBendValue, int hueChange){
    if(hueChange==0){
      
      Tlc.clear();
      Serial.println(colorTable[arrayNumber][0]);
      int tempArrayMapR = map(colorTable[arrayNumber][0],0,255,0,4095);
      int tempArrayMapG = map(colorTable[arrayNumber][1],0,255,0,4095);
      int tempArrayMapB = map(colorTable[arrayNumber][2],0,255,0,4095);
      if(saveColorR==-1){
        saveColorR = tempArrayMapR;
        saveColorG = tempArrayMapG;
        saveColorB = tempArrayMapB;
      }
      if(fade){
        while(fadeIn<=1){
        inputRecieved=Serial1.read();
        Tlc.set(2, int(fadeIn*tempArrayMapR*velocityBlue));//red
        Tlc.set(0, int(fadeIn*tempArrayMapG*velocityBlue));//green
        Tlc.set(1, int(fadeIn*tempArrayMapB*velocityBlue));//blue

          Serial.print(fadeIn);
          fadeIn+=.009;
           Tlc.update();
         if(inputRecieved==128)
            break;
         }
         
      }
      else{
      Tlc.set(2, int(tempArrayMapR*velocityBlue));//red
      Tlc.set(0, int(tempArrayMapG*velocityBlue));//green
      Tlc.set(1, int(tempArrayMapB*velocityBlue));//blue
      Tlc.update();
      }
      printValueWithTabs("velocityBlue",velocityBlue,0);
      
    
    }      
    else{
      analogWrite(2,colorTable[arrayNumber][0]*velocityBlue*pitchBendValue);
      analogWrite(3,colorTable[arrayNumber][1]*velocityBlue*pitchBendValue);
      analogWrite(5,colorTable[arrayNumber][2]*velocityBlue*pitchBendValue);
    }
}
String getLetter(int getNoteLetter){
  String setLetterTemp;
  switch(getNoteLetter){
     case 0:
       setLetterTemp="c";
       break;  
     case 1:
       setLetterTemp="c#";
       break;
      case 2:
        setLetterTemp="d";
       break;
     case 3:
       setLetterTemp="eb";
       break;
     case 4:
        setLetterTemp="e";
        break;
     case 5:
       setLetterTemp="f";
       break;
     case 6:
       setLetterTemp="f#";
        break;
      case 7:
        setLetterTemp="g";
        break;
      case 8:
        setLetterTemp="ab";
        break;
      case 9:
        setLetterTemp="a";
        break;
      case 10:
        setLetterTemp="a#";
        break;
      case 11:
        setLetterTemp="b";
        break;
      default:
       break;
      }
      return setLetterTemp;
}
void checkLetterWriteToOutput(String setLetter,double velocityBlue, double pitchBendValue, int hueChange){
  if(setLetter=="a"){
      writeToOutput(0,velocityBlue,pitchBendValue,hueChange);
      }
     else if(setLetter=="a#"){
      writeToOutput(1,velocityBlue,pitchBendValue,hueChange);
     }
     else if(setLetter=="b"){
      writeToOutput(2,velocityBlue,pitchBendValue,hueChange);
      }
     else if(setLetter=="c"){
      writeToOutput(3,velocityBlue,pitchBendValue,hueChange);
     }
     else if(setLetter=="c#"){
      writeToOutput(4,velocityBlue,pitchBendValue,hueChange);
     }
     else if(setLetter=="d"){
      writeToOutput(5,velocityBlue,pitchBendValue,hueChange);
     }
     else if(setLetter=="eb"){
      writeToOutput(6,velocityBlue,pitchBendValue,hueChange); 
     }
     else if(setLetter=="e"){
      writeToOutput(7,velocityBlue,pitchBendValue,hueChange);
     }
     else if(setLetter=="f"){
       Serial.print("\t \t \t");Serial.print("Pitch Bend value: ");
         Serial.println(pitchBendValue);
      Serial.print("\t \t \t");Serial.print("Analog Write value: ");
      Serial.println((colorWheelBlue[9][0]*velocityBlue)*pitchBendValue);
      writeToOutput(8,velocityBlue,pitchBendValue,hueChange);
     }
     else if(setLetter=="f#"){
        writeToOutput(9,velocityBlue,pitchBendValue,hueChange);
     }
     else if(setLetter=="g"){
      writeToOutput(10,velocityBlue,pitchBendValue,hueChange);  
      }
     
     else if(setLetter=="ab"){
      writeToOutput(11,velocityBlue,pitchBendValue,hueChange);
     }    
}
