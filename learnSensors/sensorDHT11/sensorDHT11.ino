#include <DHT.h>

#define pin 2
#define type DHT11

DHT dht(pin, type);

void setup(){
    Serial.begin(9600);
    Serial.flush(); 
    Serial.println("Start Serial Printing");
}

void loop (){
    int i;
    float humi = dht.readHumidity();
    float temp = dht.readTemperature();

    Serial.println("==========================");
    print_line("airHumi : ", humi);
    print_line("airTemp : ", temp);
    Serial.println("==========================\n");
    delay(1000);
    
}

void print_line(String a, unsigned int b) { 
    Serial.print(a);
    Serial.println(b);
}