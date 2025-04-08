#include <scheduler.h>
#define LED_PIN 48
#define D3 6
#define D4 7
#define D5 8
#define D6 9

int led_status = 0;
void test_blinky(){
  led_status = 1 - led_status;
  digitalWrite(LED_PIN, led_status);
}

// 0: green
// 1: yellow
// 2: red

int led_status1 = 1;
int led_status2 = 2;
int time1 = 5;
int time2 = 3;

void update_lights1() {
  time1--;
  if (time1 == 0 && led_status1 == 0) {
    digitalWrite(D3, LOW);
    digitalWrite(D4, HIGH);
    led_status1 = 1;
    time1 = 2;
  }
  if (time1 == 0 && led_status1 == 1) {
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH);
    led_status1 = 2;
    time1 = 5;
  }
  if (time1 == 0 && led_status1 == 2) {
    digitalWrite(D3, HIGH);
    digitalWrite(D4, LOW);
    led_status1 = 0;
    time1 = 3;
  }
}

void update_lights2() {
  time2--;
  if (time2 == 0 && led_status2 == 0) {
    digitalWrite(D5, LOW);
    digitalWrite(D6, HIGH);
    led_status2 = 1;
    time2 = 2;
  }
  if (time2 == 0 && led_status2 == 1) {
    digitalWrite(D5, HIGH);
    digitalWrite(D6, HIGH);
    led_status2 = 2;
    time2 = 5;
  }
  if (time2 == 0 && led_status2 == 2) {
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    led_status2 = 0;
    time2 = 3;
  }
}

void TIMER_ISR(void *pvParameters) {
  
  while(1) {
    SCH_Update();
    vTaskDelay(10);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, LOW);

  xTaskCreate(TIMER_ISR, "TIMER_ISR", 2048, NULL, 2, NULL);

  SCH_Init();
  SCH_Add_Task(test_blinky, 0, 100);
  SCH_Add_Task(update_lights1, 0, 100);
  SCH_Add_Task(update_lights2, 200, 100);
}

void loop() {
  SCH_Dispatch_Tasks();
}
