//#define DEBUG 1
// 14B: H__T__S__C____

// ----------------------------------------------------------------------

// 온습도 센서
#define PIN_DHT11 A0
// 공기질 센서
#define PIN_MQ135 A1
// 토양 습도 센서
#define PIN_SOIL A2

// LED 모스펫
#define PIN_LED 8
// 팬 모스펫
#define PIN_FAN 9

// ----------------------------------------------------------------------

// 필요 라이브러리 (라이브러리 관리자에서 설치)
// DHT sensor library (by Adafruit)
// MQUnifiedsensor (by Miguel Califa, 등)

// DHT11 온습도 센서
#include <DHT.h>
DHT dht = DHT(PIN_DHT11, DHT11);

// MQ135 유해가스/공기질 센서 모듈
#include <MQUnifiedsensor.h>
// placa, volatage_resolution, ADC_bit_resolution, pin, type
// placa와 type은 디버그 출력용이기 때문에 정확한 값을 입력하지 않아도 됩니다.
MQUnifiedsensor MQ135("Arduino MEGA", 5, 10, PIN_MQ135, "MQ135");
  /*
  GAS      | a      | b
  CO       | 605.18 | -3.937  
  Alcohol  | 77.255 | -3.18 
  CO2      | 110.47 | -2.862
  Tolueno  | 44.947 | -3.445
  NH4      | 102.2  | -2.473
  Acetona  | 34.668 | -3.369
  */

// ----------------------------------------------------------------------

void setup() {
  Serial.begin(9600);

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  pinMode(PIN_FAN, OUTPUT);
  digitalWrite(PIN_FAN, LOW);
  
  // 온습도 센서
  dht.begin();

  // 토양 습도 센서
  pinMode(PIN_SOIL, INPUT);

  // MQ135
  // Set math model to calculate the PPM concentration and the value of constants
  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
  // Exponential regression (지수 회귀분석)
  // CO2
  MQ135.setA(110.47); MQ135.setB(-2.862);
  // Calibrated value
  MQ135.setR0(16000);
  
  MQ135.init(); 
}

// 센서 정보 보낼 시간 계산할 변수
int writeTimer = 0;
void loop() {
  if (Serial.available()) {
    char a = Serial.read();

    if (a == 'r') { // 센서값 바로 보내기
      writeTimer = 100;
    }else if (a == 'A') { // LED 켜기
      digitalWrite(PIN_LED, HIGH);
    }else if (a == 'a') { // LED 끄기
      digitalWrite(PIN_LED, LOW);
    }else if (a == 'B') { // 팬 켜기
      digitalWrite(PIN_FAN, HIGH);
    }else if (a == 'b') { // 팬 끄기
      digitalWrite(PIN_FAN, LOW);
    }
  }

  // 100ms마다 // 100ms마다 1씩 커짐, 100이 되면(== 10초) 값 전송
  if (writeTimer >= 100) { 
    writeTimer = 0;
    writeValues();
  }

  writeTimer++;
  delay(100);
}

void writeValues() {
  // 온습도 센서
  int humidity = dht.readHumidity();
  int temperature = dht.readTemperature();

#ifdef DEBUG
  Serial.print("h:");
  Serial.print(humidity);
  Serial.print(" / t:");\
  Serial.print(temperature);
#else
  Serial.write('H');
  Serial.write((byte*)&humidity, 2);
  Serial.write('T');
  Serial.write((byte*)&temperature, 2);
#endif


  // analogRead는 0 ~ Vcc(5V) 사이 전압값을 1024에 대응
  // 5V 전원, 0~3.6V 출력, 3.6V: 물에 잠김
  // 3.6V 정도 까지 밖에 쓰지 않기 때문에 출력값은 0~740 정도만 나옴
  // 0 ~ 630을 0 ~ 100으로 값을 조정한 다음(map)
  // 0 ~ 100을 벗어나지 않게(contrain) 값을 보정해서 사용 
  int soilValue = constrain(map(analogRead(PIN_SOIL), 0, 630, 0, 100), 0, 100);
#ifdef DEBUG
  Serial.print(" / s:");
  Serial.print(soilValue);
#else
  Serial.write('S');
  Serial.write((byte*)&soilValue, 2);
#endif

  // 공기질 센서
  MQ135.update();
  float mqValue = 0;
  // CO2
  mqValue = MQ135.readSensor();
#ifdef DEBUG
  Serial.print(" / CO2:");
  Serial.print(mqValue);
  Serial.println("");
#else
  Serial.write('C');
  //byte* b = (byte*)&mqValue;
  Serial.write((byte*)&mqValue, 4);
  Serial.write('\n');
#endif
}
