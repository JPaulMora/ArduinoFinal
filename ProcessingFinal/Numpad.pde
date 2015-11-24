class Numpad {
   float wid, hei,wd,hg;
   color bak,def,hov,click;
   int col;
   int row;
   int total;
   Button[] Botones;
   
   
   Numpad(int c, int r, color bak,color def, color hover, color click) {
      col = c;
      row = r;
      this.bak = bak;
      wid = (col*70)+(col*20);
      hei = (row*70)+(row*20);
      total = c*r;
      Botones = new Button[this.total];
      this.def = def;
      hov = hover;
      this.click = click;
      
      
   }
   
 void build(float  wd,float hg) {
     this.wd = wd;
     this.hg = hg;
     
     int index = 0;

      for (int a = 0; a < this.row; a++) {
        for (int i=0 ; i < this.col; i++) { 
          /*rect((35*i+50*i)+wd+50,(35*a+50*a)+hg+50,70,70);*/
          
          this.Botones[index++] = new Button((i*(wid/col)+wd+45),(a*(hei/row)+hg+45),def,hov,click,index);    
        }               
      } 
 }
 void update(){
   fill(bak);
   rect(wd+(this.wid/2),hg+(this.hei/2),this.wid+20,this.hei+20);
  updatebs(); 
 }
 
 void updatebs(){
   for (int i= 0; i < total; i++){
    this.Botones[i].active();
  }
 }
 
 void sendClick() {
   for (int i= 0; i < total; i++){
    this.Botones[i].pressed();
  }
 }
}