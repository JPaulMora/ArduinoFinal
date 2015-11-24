class Scroller {
  boolean move;
  int Mlevel, Clvl;
  float Sx, Sy, X,Y;
  color cont,bar;
  
  Scroller(float SizeX, float SizeY,float X,float Y, int maxLevel, color container, color bar) {
      move = false;
      Mlevel = maxLevel;
      Clvl = maxLevel/2;
      Sx = SizeX;  // CuboX = X-Sx/2,X+Sx/2
      Sy = SizeY;  // CuboY = Y-Sy/2,Y+Sy/2
      this.X = X;  //centerX
      this.Y = Y;  //centerY
      cont = container;
      this.bar = bar;
  }
  
  void makeScroll() {
    fill(100,110,120);
    rect(X,Y,Sx,Sy); // Scroller "container"
    fill(0);
    
    if (!mousePressed || !move) {
    float Ymap = map(Clvl,0,Mlevel,Y+(Sy/2)-(Sy/Mlevel),Y-(Sy/2)+(Sy/Mlevel));
    rect(X,Ymap,Sx-5,(Sy)/Mlevel);
    } else if (move){
      scrollMove();
      float Ymap = map(Clvl,0,Mlevel,Y+(Sy/2)-(Sy/Mlevel),Y-(Sy/2)+(Sy/Mlevel));
      rect(X,Ymap,Sx-5,(Sy)/Mlevel);
    }
  }
  
  void scrollMove(){
    float mapval = map(mouseY,Y+(Sy/2),Y-(Sy/2),0,Mlevel);
    if (mapval > Mlevel) {
      Clvl = Mlevel;
    }else if (mapval < 0 ){
      Clvl = 0;
    }else{
    Clvl = (int)mapval;
    if (Clvl != (int)mapval){
      println(Clvl);
    }
    }

  }
  
  void sendOff() {
        move = false;
        println(Clvl);
  }
  
  void sendClick(){
    if ( mouseX >= (X-Sx/2) && mouseX <= (X+Sx/2) && mouseY >= (Y-Sy/2) && mouseY <= (Y+Sy/2)) {
      move = true;
      println(Clvl);
      
    }
      
      
  }
 
int getVal(){
    return Clvl;
 }
}