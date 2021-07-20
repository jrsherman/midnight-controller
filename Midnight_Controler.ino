//Writen by Jake Sherman 2015
//The Midnight Controlers main purpose is to help control a Light show with midi output.
//Running programs that help keep the triggering intresting and say take in half of the notes
//or only one note every 4 with a variable for notes skipped would be part of the control
//having access to a color database In which to help program each song will be added and can already
// be found in it's initial stages in colorValues.h
// grabbing the velocity from the output is the next task for this program
int inputRecieved=-1;
#include "Tlc5940.h"
#include "colorValues.h"
#include "midiClass.h"
#include "functions.h"

int index = 0;
int activeEnd=0;

int velocityValue = -1;
int noteActive=0;
int noteValueActive=0;
int noteValue = -1;
int counter=0;
int hueChange=0;
int pitchBendActivated=0;
double pitchBendValue=1;
int velocitySet = 0;
String setLetter;
void setup() {
  Serial1.begin(31250);
  Serial.begin(9600);
  Tlc.init();
  Tlc.clear();
}
void loop() {
while(Serial1.available()>0){ 
  inputRecieved=Serial1.read();
 if(inputRecieved==224){
        pitchBendActivated=1;
        }
 if(pitchBendActivated){
        if(inputRecieved!=224&&inputRecieved!=144)
          pitchBendValue=inputRecieved;
          pitchBendValue = map(pitchBendValue,0,127,0,100);
          printValueWithTabs("pitchBendValue",pitchBendValue,0);
          pitchBendValue = pitchBendValue/100;
        }
 if(inputRecieved==144 && noteActive==0){ 
        pitchBendActivated=0;
        //pitchBendValue=1;
        noteActive=1; 
        inputRecieved=-1;    
      }  
      if(noteActive&&inputRecieved>0&&inputRecieved!=144&&noteValueActive==0){ //reading inputs 12-120
        //printValueWithTabs("Note Value",inputRecieved,0);
        noteValue = inputRecieved;
        if(noteValue==121){//c# above c8 
          fade=1;
          //hueChange=1;   
        }
        if(noteValue==122){//c# above c8
          fade=0;
          //hueChange=0;//differnt colors for same notes
        }
        if(noteValue>=12&&noteValue<=120){
          int ocatve = noteValue/12; //truncates the decimal should round down giving the present octave
          int getNoteLetter = noteValue-12*ocatve;  
          setLetter=getLetter(getNoteLetter);//ref function.h   
          printLetter(setLetter);
        }
        noteValueActive=1;
        }
      else if(velocitySet==0&&noteActive&&inputRecieved>0&&inputRecieved!=144&&noteValue>=12&&noteValue<=120){//&&velocityValue<0
         
         if(!pitchBendActivated)
            velocityValue = inputRecieved;
         //printValueWithTabs("Velocity",velocityValue,0);             
         double velocityBlue=map(velocityValue,0,127,0,100);
         velocityBlue=velocityBlue/100;
         checkLetterWriteToOutput(setLetter,velocityBlue,pitchBendValue,hueChange);  //check letter and then write to led
         velocitySet = 1;
        }      
        if(inputRecieved==128){//check for noteoff
          Tlc.clear();//may want to take this set out
          Tlc.set(2, 0);
          Tlc.update();
          velocitySet = 0;
          noteActive=0;
          noteValue =-1;
          velocityValue = -1;
          inputRecieved=-1;
          noteValueActive=0;
          saveColorR=-1;
          saveColorG=-1;
          saveColorB=-1;
          fadeIn=0;
    }  
  }  
}
