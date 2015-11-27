class PushB extends Button{

PushB(float w, float h,color defult, color hover, color clicked, int ret){
 super(w,h,defult,hover,clicked,ret);
}
  

void resd(){
  clik = false;
}


void active() {
    if (mouseX > this.wid-30 && mouseX < this.wid+30 && 
      mouseY > this.hei-25 && mouseY < this.hei+25) {
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
      rect(this.wid,this.hei,60,50);
  }
  
 boolean isON(){
  return this.clik;
 }
  
}