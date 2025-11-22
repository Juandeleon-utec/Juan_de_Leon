#include <Servo.h>
Servo servo;
const int pinServo = D5;  // Pin de señal del servo
//Constantes y definiciones
const int pinLDR = A0;
const int led_encendido = D4; //Pin interno de la wemos
const int led_alarma = D2;  // Pin rojo de la alarma



void setup() {
  
  //Seteos
  pinMode(led_encendido, OUTPUT);
  pinMode(led_alarma, OUTPUT);
  Serial.begin(115200);
  delay(100);
  Serial.println("Iniciando SErial....");  
  servo.attach(pinServo); // Iniciar servo en el pin D5
  //Muevo el servo cuando esta iniciando la placa para corroborar
  servo.write(90);    // Girar a 0°
  delay(1000);
  servo.write(0);   // Girar a 90°
  delay(1000);
  //cuando termina enciendo el LEd interno
  pinMode(led_encendido, HIGH); // Este siempre se enciende, porque indica que el sistema esta funcionando
}

void loop() {
  // put your main code here, to run repeatedly:
  int valorLDR = analogRead(pinLDR);   // Depende del dispositivo
  Serial.print("Lectura LDR: ");
  Serial.println(valorLDR);
  if (valorLDR > 950) {
    //Si llega enciendo
    digitalWrite(led_alarma, HIGH);  
    //Mueve el servo como una manga
    for (int ang = 45; ang <= 180; ang += 5) {
      servo.write(ang);
      delay(80);}
    for (int ang = 180; ang >=45; ang -= 5) {
        servo.write(ang);
        delay(80); }           
  
    } else {
     // Si baja apago
    digitalWrite(led_alarma, LOW);    
    servo.write(0); // vuelve a la posicion normal
    delay(1000);
  }
    
  delay(1000); // Loop de lectura y parpadeo

}
