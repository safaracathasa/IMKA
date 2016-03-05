#include <LiquidCrystal.h> //import lcd library
#include <Keypad.h> //import keypad library

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); //lcd pins
const byte ROWS = 4; // four rows
const byte COLS = 3; // four columns

//define the keymap
char keys [ROWS] [COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','='}
};
byte rowPins[ROWS] = {
 13 ,0 ,12 ,11 }; //connect keypad ROW1, ROW2, ROW3, ROW4 to these arduino pins
byte colPins[COLS] = {
  10, 9, 8 }; //connect keypad COL1, COL2, COL3, COL4 to these arduino pins

//create the keypad
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
boolean one = false;
  boolean next = false;
  boolean final = false;
  boolean cls = false;
  String num1, num2;
  int ans;
  int i = -1;
  char op[4] = {'+','-','*','/'};
  
void setup(){
  //variables declaration
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(2,0);
  lcd.print("Calculator");
  delay(2500);
  lcd.clear(); //clears the LCD screen and positions the cursor in the upper-left corner. 
}

void loop(){
  char key = myKeypad.getKey();

  //Getting number input
  if (key != NO_KEY && (key=='1'||key=='2'||key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0')){
    if (one != true){
      num1 = num1 + key;
      int numLength = num1.length();
      lcd.setCursor(15 - numLength, 0); //to adjust one whitespace for operator
      lcd.print(num1);
      Serial.println(num1);
    }
    else {
      num2 = num2 + key;
      int numLength = num2.length();
      lcd.setCursor(15 - numLength, 1);
      lcd.print(num2);
      Serial.println(num2);
      final = true;
    }
  }
  //Getting operation
  else if (num1 !="" && key != NO_KEY && key == '*'){
      lcd.clear();
      i++; 
      one = true;
      if(i==4)
        i=0;
      lcd.setCursor(15,0); //operator on right corner
      lcd.print(op[i]);
      Serial.println(op[i]);
  }
  
  //Getting result
  else if (final == true && key != NO_KEY && key == '=' && cls == false){
    if (op[i] == '+'){
      ans = num1.toInt() + num2.toInt();
    }
    else if (op[i] == '-'){
      ans = num1.toInt() - num2.toInt();
    }
    else if (op[i] == '*'){
      ans = num1.toInt() * num2.toInt();
    }
    else if (op[i] == '/'){
      ans = num1.toInt() / num2.toInt();
    }    
      num2="";
      lcd.clear();
      lcd.setCursor(15,0);
      lcd.autoscroll();
      lcd.print(ans);
      lcd.noAutoscroll();
      Serial.println(ans);
      cls = true;
  }
  else if (key != NO_KEY && key == '=' && cls == true){
    lcd.clear();
    cls = false;
    one = false;
    final = false;
    num1 = "";
    num2 = "";
    ans = 0;
    i=-1;
  }
}
