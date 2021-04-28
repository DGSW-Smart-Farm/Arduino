// 
// 센서의 값은 소숫점 한자리 이하로 나타낸다.
// 소숫점이하 자리의 값을 표현하는 방법은 10을 곱하여 나타낸다
//      ex) 11.5`C => 115
//      ex) 52.7 % => 527

//  ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//   Senser                 | Data Type      | Unit           | Etc                       
//  ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//   gnd_Humidity           | unsingned int  | percent        | 0~1000 (/10)
//   gnd_Acidity            | unsingned int  | ph             | 10~140 (/10)
//   air_Humidity           | unsingned int  | percent        | 0~1000 (/10)
//   air_Temperature        | unsingned int  | degree celcius | 0~1000 (/10)
//   air_carbonDioxide      | unsingned int  | ppm            | 0~2000 (none *10)
//   led_Status             | bool           | NONE           | True=On False=Off
//   led_OnTime             | bool           | NONE           | True=Start False=end
//  ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
// 

unsigned int gndHumi_value = 500;   //토양 수분
unsigned int gndAcid_value = 70;    //토양 산성도
unsigned int airHumi_value = 500;   //공기중 습도
unsigned int airTemp_value = 500;   //공기중 온도
unsigned int airCO2_value  = 1000;  //이산화탄소
bool ledStat = true;    //led 상태
bool ledTime = false;   //led 작동시간


void setup(){
    Serial.begin(9600);
    Serial.flush(); 
    Serial.println("Start Serial Printing");
}

void loop(){
    changevalueRandom();
    print_lines();
}

void changevalueRandom(){ 
    gndHumi_value += random(-10, 11);
    gndAcid_value += random(-10, 11);
    airHumi_value += random(-10, 11);
    airTemp_value += random(-10, 11);
    airCO2_value += random(-10, 11);
    ledStat += random(-10, 11);
    ledTime += random(-10, 11);
}

void print_lines(){     //상태 출력
    Serial.println("==========================");
    print_line("gndHumi : ", gndHumi_value);
    print_line("gndAcid : ", gndAcid_value);
    print_line("airHumi : ", airHumi_value);
    print_line("airTemp : ", airTemp_value);
    print_line("air_CO2 : ", airCO2_value);
    print_line("ledStat : ", ledStat);
    print_line("ledTime : ", ledTime);
    Serial.println("==========================\n");
    delay(1000);
}

void print_line(String a, unsigned int b) { 
    Serial.print(a);
    Serial.println(b);
}
