#include <Keypad.h>
const int row_num = 4;
const int col_num = 4;
long int current_time=0;
long int previous_time=0;
int threshold = 4000;
char keypressed = '\0';
int score = 0;
char keys[row_num][col_num]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte row_pins[row_num]={19,18,5,17};
byte col_pins[col_num]={16,4,2,15};
Keypad keypad = Keypad(makeKeymap(keys),row_pins,col_pins,row_num,col_num);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(150200);
  }

void loop() {
  // put your main code here, to run repeatedly:
  // this speeds up the simulation
  byte random_row= random(1,5);
  byte random_col = random(1,5);
  char random_elements = keys[random_row-1][random_col-1];
  String hint1="Row:"+String(random_row);
  String hint2="Colum:"+String(random_col);
  byte random_hint = random(1,3);
  if(random_hint==1){
    Serial.println(hint1+"\t"+hint2);
  }
  else{
    Serial.println(hint2+"\t"+hint1);
  }
  while(true){
  char key=keypad.getKey();
  if(key){ 
    keypressed = key;
  }
  current_time=millis();
  if(current_time-previous_time==threshold){
    if(keypressed == random_elements){
      score++;
      if(score>6){
        Serial.println("You Win");
        while(1);
      }
      Serial.println(String(score));
      threshold -= 500;
      if(threshold<500){
        threshold=500;
      } 
    }
    else{
      Serial.println("You Lose");
      while(1);
    }
    previous_time= current_time;
    break;
  }
  }
  
}
