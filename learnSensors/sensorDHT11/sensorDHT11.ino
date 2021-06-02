#include <DHT.h>

#define DHTPIN A1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int airHumi_value;
int airTemp_value;

void setup(){
    Serial.begin(9600);
}

void loop(){
    airHumi_value = dht.readHumidity();
    airTemp_value = dht.readTemperature();

    print_lines();
    delay(1000);
}




void print_lines(){     //상태 출력
    Serial.println("==========================");
    print_line("airHumi : ", airHumi_value);
    print_line("airTemp : ", airTemp_value);
    Serial.println("==========================\n");
}

void print_line(String a, unsigned int b) { 
    Serial.print(a);
    Serial.println(b);
}