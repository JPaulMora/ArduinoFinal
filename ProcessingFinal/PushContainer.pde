class Pcontainer extends Numpad{
  PushB[] Pbs;

Pcontainer(int c, int r, color bak,color def, color hover, color click){
  super(c,r,bak,def,hover,click);
  Pbs = new PushB[this.total];
  wid = (col*70)+(col*20);
  hei = (row*50)+(row*20);
}

  void build(float  wd,float hg, float ow, float oh) {
     this.wd = wd;
     this.hg = hg;
     
     int index = 0;

      for (int a = 0; a < this.row; a++) {
        for (int i=0 ; i < this.col; i++) { 
          /*rect((35*i+50*i)+wd+50,(35*a+50*a)+hg+50,70,70);*/
          
          this.Pbs[index++] = new PushB((i*(wid/col)+wd+35+ow ),(a*(hei/row)+hg+35+oh),def,hov,click,index);    
        }               
     } 
 }
 
  void updatebs(){
   for (int i= 0; i < total; i++){
    this.Pbs[i].active();
  }
 }
 
 void SendRels(){
    for (int i= 0; i < total; i++){
    this.Pbs[i].resd();
    }
 }

 void sendClick() {
   for (int i= 0; i < total; i++){
    this.Pbs[i].pressed();
  }
 }

}