/* Proyecto final de Taller de Introduccion a la Mecatronica
*   Juan Pablo Mora 15799, 
*   Irvin R. Oliva 15816
*   Universidad del Valle Guatemala
*/


#include <Servo.h>

//Servo
Servo Serv; //Objeto Servo.
int potps; //inicializacion de variables sin valor (para usar despues).

//LEDS
int led3 = 3;
int led5 = 5;
int led6 = 6;
int led11 = 11;

//Dips
int dip1 = 8;
int dip2 = 7;

//Push
int push1=2; //variables de los Push, son = al # de pin. (ver Breadboard).
int push2=4;

//Other
int pot = 0;
int intens=255;//Valor de intensidad para los leds. Empezar intensidad al 50%
int val=analogRead(pot);//Lee potenciometro de 0-1023;

//SERIAL COMM

byte Send[] = {0,0,0,0,0,0,0,0,0}; // Leds-4 (0/255) Pot (0/255) Dips-2 (0/1) Push2(0/3)
byte Recv[] = {0, 0, 0, 0, 0}; //Dip1,Dip2, Push1,Push2 (0/1), Slider (0/255)

void serialEvent(){
 Serial.readBytes(Recv,5);
 Serial.write(Send,9);
}

void setup() {
  Serial.begin(9600);
  Serv.attach(9);  //Pin donde se encuentra el Servo
           /*-----Inicializacion de LEDs -------*/
  pinMode(led3, OUTPUT);//LED1
  pinMode(led5, OUTPUT);//LED2   
  pinMode(led6, OUTPUT);//LED3
  pinMode(led11, OUTPUT);//LED4
  

           /*-----Inicializacion de Dips -------*/
  pinMode(dip1, INPUT_PULLUP);
  pinMode(dip2, INPUT_PULLUP);   //INPUT_PULLUP: El estado natural del pin es HIGH.


          /*-----Inicializacion de Push -------*/
  pinMode(push1,INPUT_PULLUP);
  pinMode(push2,INPUT_PULLUP);  //tenes que decirle al Arduino como usarlos.
                                //usamos INPUT_PULLUP Y NO INPUT, porque no tenemos 2k resistores (entonces usamos el interno como en los dip).

}

/************** Funciones ********************/

int funcNum()
{
  boolean updated = false;
  int suma = 4; //Dipswitch conecta pins a GND para ponerlos en LOW, hacemos conteo en reversa (if HIGH, restar a 'suma').
  if (digitalRead(dip1) == HIGH || Recv[0] == 1){
    UpdateStatus(5,B0);
    updated = true;
    suma -= 1; // si dip1 == HIGH (switch off), suma = 4 -1 = 3; correr funcion 3.
  }
  if (digitalRead(dip2) == HIGH || Recv[1] == 1){
    suma -= 2; // Si dip2 == HIGH, suma = 4 -2 = 2 correr funcion 2.
    UpdateStatus(6,0);
    updated = true;
  }                       
  return suma;  //si Ningun pin esta conectado a GND, significa que los 2 dipswitches estan en 'OFF' y el resultado de 4 -2-1 = 1; entonces correr funcion 1.
               //si los 2 switches estan en LOW (switches ON), significa que a 'suma' no se le resta nada y 4 -0 = 4; correr funcion 4.
 if (!updated){
   UpdateStatus(5,B1);
   UpdateStatus(6,B1);
 }
}

/************ Fin Funciones ******************/

void loop() 
{
  //Serial.println(funcNum());
  int iVal1=digitalRead(push1); //podemos iniciar las variables localmente.
  int iVal2=digitalRead(push2); //Apachado ahora conecta a low  o negativo (ver Breadboard).
  //Funcion 1
  //DIP1==HIGH, DIP2==HIGH;
  if (funcNum() == 1){
  val = map(val,0,1023,0,180); //convertir voltaje del potenciometro 'pot' {0,1023} -> {0,180}
  UpdateStatus(4,byte(200));

  //LEDS
  if (val <= 45 && val > 5){ // Activado si 'val' entre (0,45}.
    int valocal = map(val,0,45,0,255); //Variable local, convierte 'val' entre {0,45} -> {0,255}
    analogWrite(led3,valocal);
    UpdateStatus(0,valocal);
    digitalWrite(led5,LOW);
    UpdateStatus(1,0);
    digitalWrite(led6,LOW);
    UpdateStatus(2,0);
    digitalWrite(led11,LOW);
    UpdateStatus(3,0);
  }else if (val > 45 && val <= 90){ // Activado si 'val' entre (45,90}.
    int valocal = map(val,46,90,0,255);
    digitalWrite(led3,HIGH);
    UpdateStatus(0,255);
    analogWrite(led5,valocal);
    UpdateStatus(1,valocal);
    digitalWrite(led6,LOW);
    UpdateStatus(2,0);
    digitalWrite(led11,LOW);
    UpdateStatus(3,0);
  }else if(val > 90 && val <= 135){ // Activado si 'val' entre (90,135}.
    int valocal = map(val,90,135,0,255);
    digitalWrite(led3,HIGH);
    UpdateStatus(0,255);
    digitalWrite(led5,HIGH);
    UpdateStatus(1,255);
    analogWrite(led6,valocal);
    UpdateStatus(2,valocal);
    digitalWrite(led11,LOW);
    UpdateStatus(3,0);
  } else if(val >135 && val <= 180){ // Activado si 'val' entre (135,180}.
    int valocal = map(val,135,180,0,255);
    digitalWrite(led3,HIGH);
    UpdateStatus(0,255);
    digitalWrite(led5,HIGH);
    UpdateStatus(1,255);
    digitalWrite(led6,HIGH);
    UpdateStatus(2,255);
    analogWrite(led11,valocal);
    UpdateStatus(3,valocal);
  }else{     //       /      /      /  Si 'val' == 0 apagar todos los LEDs
    digitalWrite(led3,LOW);
    UpdateStatus(0,0);
    digitalWrite(led5,LOW);
    UpdateStatus(1,0);
    digitalWrite(led6,LOW);
    UpdateStatus(2,0);
    digitalWrite(led11,LOW);
    UpdateStatus(3,0);
  }
  Serv.write(val); //Enviar posicion de 'val' (0-180) al servo.

  //Funcion 2
    //Dip1==LOW; Dp2==High; 0 + 2 = 2
  }
  else if(funcNum() == 2)
  {
    if(iVal1==LOW && iVal2 == HIGH)   //Asegurarnos que **SOLO 1** se esta apachando o las dos condiciones se vuelven 'true'
                  //mientras el push esta apachado, es LOW 
                  //DigitalRead se tiene que comparar con HIGH o LOW, analog se compara con numeros.
  {
    digitalWrite(led3,HIGH);
    UpdateStatus(0,255);
    digitalWrite(led5,HIGH);
    UpdateStatus(1,255);
    digitalWrite(led6,HIGH);
    UpdateStatus(2,255);
    digitalWrite(led11,HIGH);
    UpdateStatus(3,255);
    delay(100);
  
  // LEDs estaran encendidos por 100ms, hay que apagarlos por 100ms para que 'titilen'. 
  
    digitalWrite(led3,LOW);
    UpdateStatus(0,0);
    digitalWrite(led5,LOW);
    UpdateStatus(1,0);
    digitalWrite(led6,LOW);
    UpdateStatus(2,0);
    digitalWrite(led11,LOW);
    UpdateStatus(3,0);
    delay(100);
  }
    else if(iVal2==LOW && iVal1==HIGH)
  {
    digitalWrite(led3,LOW);
    UpdateStatus(0,0);
    digitalWrite(led5,HIGH);
    UpdateStatus(1,255);
    digitalWrite(led6,LOW);
    UpdateStatus(2,0);
    digitalWrite(led11,HIGH);
    UpdateStatus(3,255);
    delay(100);
  
    digitalWrite(led3,HIGH);
    UpdateStatus(0,255);
    digitalWrite(led5,LOW);
    UpdateStatus(1,0);
    digitalWrite(led6,HIGH);
    UpdateStatus(2,255);
    digitalWrite(led11,LOW);
    UpdateStatus(3,0);
    delay(100);
  }
    else //mientras no pasada nada, todo apagado(high)
  {
    digitalWrite(led3,LOW);
    UpdateStatus(0,0);
    digitalWrite(led5,LOW);
    UpdateStatus(1,0);
    digitalWrite(led6,LOW);
    UpdateStatus(2,0);
    digitalWrite(led11,LOW);
    UpdateStatus(3,0);
  }
  
  }
  //Funcion 3
    //Dip1==HIGH;Dip2==Low; 4-1-0=3;
  else if(funcNum() == 3)
  {
    UpdateStatus(4,val);
    if (iVal1==LOW && iVal2==HIGH)
    //mientras push1 sea precionado, cumplira con la condicion
    {
      digitalWrite(led3,HIGH);
      UpdateStatus(0,255);
      digitalWrite(led5,HIGH);
      UpdateStatus(1,255);
      digitalWrite(led6,HIGH);
      UpdateStatus(2,255);
      digitalWrite(led11,HIGH);
      UpdateStatus(3,255);
      delay(val);
  
  // LEDs estaran encendidos por el valor del potenciometro y se apagaran por el valor del potenciometro 
  
      digitalWrite(led3,LOW);
      UpdateStatus(0,0);
      digitalWrite(led5,LOW);
      UpdateStatus(1,0);
      digitalWrite(led6,LOW);
      UpdateStatus(2,0);
      digitalWrite(led11,LOW);
      UpdateStatus(3,0);
      delay(val);
    }
    else if(iVal1==HIGH && iVal2==LOW)
    //Mientras Push2 sea precionado, cumplira con la siguiente condicion
    {
      val=map(val,0,1023,0,180);//conviete val de 0-1023 a 0-180
      digitalWrite(led3,HIGH);
      UpdateStatus(0,255);
      digitalWrite(led5,HIGH);
      UpdateStatus(1,255);
      digitalWrite(led6,HIGH);
      UpdateStatus(2,255);
      digitalWrite(led11,HIGH);
      UpdateStatus(3,255);
      Serv.write(val); //Enviar posicion de 'val' (0-180) al servo.
    }
    else//si ambos push==HIGH, mantener todo apagado
     {
      digitalWrite(led3,LOW);
      UpdateStatus(0,byte(0));
      digitalWrite(led5,LOW);
      UpdateStatus(1,0);
      digitalWrite(led6,LOW);
      UpdateStatus(2,0);
      digitalWrite(led11,LOW);
      UpdateStatus(3,0);
     }
  }
  //funcion 4
  else
  {
    //settea la intensidad a 15
    analogWrite(led3,intens);
    UpdateStatus(0,intens);
    analogWrite(led5,intens);
    UpdateStatus(1,intens);
    analogWrite(led6,intens);
    UpdateStatus(2,intens);
    analogWrite(led11,intens);
    UpdateStatus(3,intens);
    //Push 1 presionado, iniciara un conteo regresivo para quitarle intensidad al LED
    if(iVal1==LOW && iVal2==HIGH)
    {
      while(intens >5){
      intens -= 5;
        analogWrite(led3,intens);
        UpdateStatus(0,intens);
        analogWrite(led5,intens);
        UpdateStatus(1,intens);
        analogWrite(led6,intens);
        UpdateStatus(2,intens);
        analogWrite(led11,intens);
        UpdateStatus(3,intens);
        delay(5);
        break;
      }
      if (intens <= 5){
        digitalWrite(led3,LOW);
        UpdateStatus(0,0);
        digitalWrite(led5,LOW);
        UpdateStatus(1,0);
        digitalWrite(led6,LOW);
        UpdateStatus(2,0);
        digitalWrite(led11,LOW);
        UpdateStatus(3,0);
      }
    }
    //push2 presionado, iniciara un conteo para aumentar el birllo del LED
    else if(iVal1==HIGH && iVal2==LOW)
    {
      while(intens <250){
      intens += 5;
        analogWrite(led3,intens);
        UpdateStatus(0,intens);
        analogWrite(led5,intens);
        UpdateStatus(1,intens);
        analogWrite(led6,intens);
        UpdateStatus(2,intens);
        analogWrite(led11,intens);
        UpdateStatus(3,intens);
        delay(5);
        break;
      }
      if (intens >= 255){
        digitalWrite(led3,HIGH);
        UpdateStatus(0,255);
        digitalWrite(led5,HIGH);
        UpdateStatus(1,255);
        digitalWrite(led6,HIGH);
        UpdateStatus(2,255);
        digitalWrite(led11,HIGH);
        UpdateStatus(3,255);
      }
    }
    
  }

  serialEvent();
  delay(15);  //Esperara 15ms antes de reiniciar loop.
}

void UpdateStatus(int pos, byte val){
  Send[pos] = val;  // Esta funcion no sirve, la idea es correcta pero envia 'int's y no 'bytes',
                    // por eso la voy a cambiar por un switch que decida si hay control 'remoto' o local.
}


