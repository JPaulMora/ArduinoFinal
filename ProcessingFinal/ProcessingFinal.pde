import processing.serial.*;
Serial Se = new Serial(this, Serial.list()[2], 9600);

//Processing para Proyecto Final 
// Juan Pablo Mora 15799
// Irvin Oliva 

/* 1 Scrollbar
*  2 push buttons 
*  2 dips
*  
*  4 Leds
*  Servo pos.
*/

// Variables

Numpad Dips;
Pcontainer Pushs;
Scroller Sc;

int interval = 50;
int previousMillis = 0;
int currentMillis = 0;

//byte[] RecArd = new byte[9];
//int[] RecArdInt = {0,0,0,0,0,0,0,0,0};
byte[] RecArd = new byte[6];
int[] RecArdInt = {0,0,0,0,0,0};


byte[] SendArd = new byte[6];
int[] SendArdInt = {0,0,0,0,0,0};


int rads = 0;
int rads2 = 180;
color black = #000000; 
color yellow = #FFC30A; //Yellows
color red = #B01010; //red
color backg = #1E2832; //Blued-Dark-gray.
color c2 = #646E78; //Dark Gray
color c3 = #C8D2DC; //Light gray
color ArdBak = #1b717e;
color CPanel = #5fd331;

PShape Arduino,ArTail,ServoTail,ServoHead,LedC,Led1,Led2,Led3,Led4;  // Shapes objects

void setup(){
  rectMode(CENTER);
  colorMode(RGB);
  size(500,770); 
  Dips = new Numpad(2,1,backg,c2,c3,yellow);
  Pushs = new Pcontainer(2,1,backg,c2,c3,red);
  Sc = new Scroller(100,270,400,183,220,c2,black);
  Dips.build(50,60);
  Pushs.build(50,230,8,0);
  
   //Figuras Below           :)
       /************** Arduino CPanel *************/
  ArTail = createShape();
  ArTail.beginShape();
  ArTail.fill(ArdBak);
  ArTail.vertex(0, 0);
  ArTail.vertex(0,250);
  ArTail.vertex(25, 230);
  ArTail.vertex(25, 20);
  ArTail.noStroke();
  ArTail.endShape(CLOSE);
  
  Arduino = createShape(RECT,240,575,450,350);
  Arduino.setFill(ArdBak);
  Arduino.setStroke(false);
  
  LedC = createShape(RECT,340,590,250,80);
  LedC.setFill(yellow);
  LedC.setStroke(false);

  ServoHead = createShape(ELLIPSE, 100, 590, 70, 70);
  ServoHead.setFill(black);
  ServoTail = createShape(ELLIPSE, 100, 590, 30, 30);
  ServoTail.setFill(black);

   /************* Internals ***********/
   thread("serial_comm"); 
  
}

void draw(){
  fill(CPanel);
  rect(250,190,470,350);
  Dips.update();
  Pushs.update();
  Sc.makeScroll();
  shape(ArTail,465, 480);
  shape(Arduino);
  shape(ServoHead);
  fill(red);
  arc(100, 590, 60, 60, radians(rads), radians(rads2), CHORD);
  fill(black);
  arc(100, 590, 60, 60, radians(0), radians(180), CHORD);
  shape(ServoTail);
  shape(LedC);
  fill(RecArdInt[0]);
  rect(250,590,30,30);
  fill(RecArdInt[1]);
  rect(310,590,30,30);
  fill(RecArdInt[2]);
  rect(370,590,30,30);
  fill(RecArdInt[3]);
  rect(430,590,30,30);
  updateFuncs(Dips.whosON());
  updatePush(Pushs.whosON());
  readfrom();
  rads = RecArdInt[4];
  rads2 = rads + 180;
  println(RecArdInt);

}
void mouseClicked() {
  Dips.sendClick();
}

void mouseReleased() {
  Pushs.SendRels();
  Sc.sendOff();
  rads += 10;
  rads2 += 10;
  
}

void mousePressed() {
  Pushs.sendClick();
  Sc.sendClick();
  Arduino.rotateX(1);
}

void updateFuncs(int[] list){
  if (list[0] == 1){
    SendArdInt[0] = 1;
  }else if (list[0] == 0){
    SendArdInt[0] = 0;
  }
  
  if (list[1] == 1){
    SendArdInt[1] = 1;
  }else if (list[1] == 0){
    SendArdInt[1] = 0;
  }   
}

void updatePush(int[] list){
  if (list[0] == 1){
    SendArdInt[2] = 1;
  }else if (list[0] == 0){
    SendArdInt[2] = 0;
  }
  
  if (list[1] == 1){
    SendArdInt[3] = 1;
  }else if (list[1] == 0){
    SendArdInt[3] = 0;
  }   
}

//SERIAL COMM

void serial_comm() {
  // Escritura al puerto serial
  while (true) {
    currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      for (int i = 0; i < 6; i++)
        SendArd[i] = byte(SendArdInt[i]);
      Se.write(SendArd);
    }
  }
}


void readfrom() {
  while (Se.available() > 0) {
    RecArd = Se.readBytes();
    int i=0;
    for (byte b: RecArd){
    try{
        RecArdInt[i++] = parseInt(b);
      } catch(Exception e){
        RecArdInt[1] = 0;
      }
    }
  }
}