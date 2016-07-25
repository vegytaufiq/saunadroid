float temp; //Membuat hasil suhu dengan bilangan desimal
int temperaturePin = 5; //Mendefinisikan Output dari IC LM35 ke Analog input
float suhuawal = 0;
float maxi = -100,mini = 100;
const int PIN_MOT1 = 2;
const int PIN_MOT2 = 3;

void setup() {
  pinMode(PIN_MOT1,OUTPUT);
  pinMode(PIN_MOT2,OUTPUT);
  Serial.begin(9600); //Sesuaikan dengan Baudrate Modul Bluetooth anda!
}

void loop() {
  if (suhuawal==0){
    while (Serial.available() > 0) {
      suhuawal = (Serial.parseFloat());
    }
  }else{
  temp = analogRead(temperaturePin);
  temp = temp * 0.48828125; //Hasil LM35 dikali 0.48828125 (Dari Datasheet)
  if(temp > maxi) {maxi = temp;} // set max temperature
  if(temp < mini) {mini = temp;} // set min temperature
  Serial.print(suhuawal);
  Serial.print("|");
  Serial.print(temp); //Tampilkan hasil suhu sebenarnya
  Serial.print("|");
  Serial.print(mini);
  Serial.print("|");
  Serial.println(maxi);
  delay(1000); //Pergantian hasil suhu setiap 1 detik
  if(temp>int(suhuawal)){
    analogWrite(PIN_MOT1, 64);
    analogWrite(PIN_MOT2, 64);
  }
  if(temp==int(suhuawal)){
    analogWrite(PIN_MOT1, 128);
    analogWrite(PIN_MOT2, 128);
  }
  if(temp<int(suhuawal)){
    analogWrite(PIN_MOT1, 255);
    analogWrite(PIN_MOT2, 255);    
  }
  }
}
