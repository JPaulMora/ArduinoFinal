import processing.serial.*;
Serial s;

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
color black = #000000; 
color yellow = #FFC30A; //Yellow
color red = #B01010; //red
color backg = #1E2832; //Blued-Dark-gray.
color c2 = #646E78; //Dark Gray
color c3 = #C8D2DC; //Light gray
color ArdBak = #1b717e;
color CPanel = #5fd331;


void setup(){
  rectMode(CENTER);
  colorMode(RGB);
  size(500,770); 
  Dips = new Numpad(2,1,backg,c2,c3,yellow);
  Pushs = new Pcontainer(2,1,backg,c2,c3,red);
  Sc = new Scroller(100,270,400,183,220,c2,black);
  Dips.build(50,60);
  Pushs.build(50,230,8,0);
  
}

void draw(){
  fill(CPanel);
  rect(250,190,470,350);
  fill(ArdBak);
  rect(250,575,470,350);
  Dips.update();
  Pushs.update();
  Sc.makeScroll();

}
void mouseClicked() {
  Dips.sendClick();
  
}

void mouseReleased() {
  Pushs.SendRels();
  Sc.sendOff();
  
}

void mousePressed() {
  Pushs.sendClick();
  Sc.sendClick();
}