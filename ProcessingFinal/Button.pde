class Button {
    boolean over,clicked,clik;

    color def,hov,cli; //default color

    float wid,hei; // Xpos, Ypos (currently in CENTER mode)
    
    int ret;    //return value (a number)

    
  Button(float w, float h,color defult, color hover, color clicked, int ret){
    def = defult;
    hov = hover;
    cli = clicked;
    this.ret = ret;
    
    this.wid = w;
    this.hei = h;
    
    this.over = false;
    this.clik = false;
    
  }
  
void pressed(){
if (over) {
  clik = !clik;
}
}

void active() {
    if (mouseX > this.wid-35 && mouseX < this.wid+35 && 
      mouseY > this.hei-35 && mouseY < this.hei+35) {
    over = true;
      } else {
    over = false;
      }

     if (!over && !clik) {
        fill(def); 
     } else if (!over && clik) {
       fill(cli);
     } else if (over && !clik) {
        fill(hov);
     } else if (over && clik) {
        fill(cli); 
     }
      rect(this.wid,this.hei,70,70);
  }
  boolean isON(){
  return this.clik;
  }
  
  
}

  