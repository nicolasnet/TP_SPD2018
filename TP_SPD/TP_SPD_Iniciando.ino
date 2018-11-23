#include <LiquidCrystal.h>

#define LIGHT_MODE 0
#define SET_NUMBER_MODE 1
#define BUTTON_RIGHT 0
#define BUTTON_UP 1
#define BUTTON_DOWN 2
#define BUTTON_LEFT 3
#define BUTTON_SELECT 4
#define BUTTON_NONE 5

#define D_1 11 
#define D_2 A3
#define D_3 A4
#define D_4 A5

#define P_1 13
#define P_2 12
#define P_3 3

/*********** Declaración de variables ********/
int pos = 0;
int arrayBits[] = {-1,-1,-1,-1};
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int mode = LIGHT_MODE;



/*********** Prototipo de funciones **********/
int readButtons();
void setNumber();
void showSetNumber();
void showLigths();


/**************** VOID / LOOP ***************/
void setup()
{
    lcd.begin(16, 2);
//bits datos
    pinMode(11, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);
//bits de paridad.
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(3, OUTPUT);
}

int previousButton = BUTTON_NONE;
void loop()
{   
    showSetNumber();
    int currentButton = readButtons();
    if(currentButton==BUTTON_SELECT && previousButton==BUTTON_NONE){
        mode = !mode;
    }
    previousButton = currentButton;
    switch (mode)
    {
    case LIGHT_MODE:
        lcd.setCursor(0, 1);
        lcd.print("    ");
        showLigths();
        break;
        
    case SET_NUMBER_MODE:
        setNumber();  
        break;
    }
}


void showLigths(){

  if(arrayBits[0] != -1 && arrayBits[1] != -1 && arrayBits[2] != -1 && arrayBits[3] != -1){
  
    if(arrayBits[0] == 1){
      digitalWrite(D_1, HIGH);  
    }else{
      digitalWrite(D_1, LOW);  
    }
  
    if(arrayBits[1] == 1){
      digitalWrite(A3, HIGH);  
    }else{
      digitalWrite(A3, LOW);  
    }
  
    if(arrayBits[2] == 1){
      digitalWrite(A4, HIGH);  
    }else{
      digitalWrite(A4, LOW);  
    }
  
    if(arrayBits[3] == 1){
      digitalWrite(A5, HIGH);  
    }else{
      digitalWrite(A5, LOW);  
    }
  
  
  
    
  
  if(arrayBits[0] && !arrayBits[1]&& !arrayBits[3] ||  !arrayBits[0] && !arrayBits[1]&& arrayBits[3]  ||    arrayBits[0] && arrayBits[1]&& arrayBits[3]   ||    !arrayBits[0] && arrayBits[1]&& !arrayBits[3] ){
      digitalWrite(13, HIGH);  
    }else{
      digitalWrite(13, LOW);  
    }
  
    if(arrayBits[0] && !arrayBits[2]&& !arrayBits[3] ||  !arrayBits[0] && !arrayBits[2]&& arrayBits[3]  ||    arrayBits[0] && arrayBits[2]&& arrayBits[3]   ||    !arrayBits[0] && arrayBits[2]&& !arrayBits[3] ){
      digitalWrite(12, HIGH);  
    }else{
      digitalWrite(12, LOW);  
    }
  
    if(arrayBits[1] && !arrayBits[2]&& !arrayBits[3] ||  !arrayBits[1] && !arrayBits[2]&& arrayBits[3]  ||    arrayBits[1] && arrayBits[2]&& arrayBits[3]   ||    !arrayBits[1] && arrayBits[2]&& !arrayBits[3] ){
      digitalWrite(3, HIGH);  
    }else{
      digitalWrite(3, LOW);  
    }
    
  } 
  
}



void showSetNumber()
{
  lcd.setCursor(0, 0);
  for(int i = 0; i<4; i++){
    if(arrayBits[i]== -1){
      lcd.print("*");
    }else{
      lcd.print(arrayBits[i]);
    }    
  }       
    lcd.print("   "); // Estos espacios están para borrar los posibles caracteres que hayan quedado en el display
}


int previousButtonAlarm = BUTTON_NONE;
void setNumber()
{
    lcd.setCursor(0, 1);
    lcd.print("    ");
    lcd.setCursor(pos, 1);
    lcd.print("^");
    int currentButton = readButtons();
    if (previousButtonAlarm == BUTTON_NONE && currentButton != BUTTON_NONE)
    {
        switch (currentButton)
        {
        case BUTTON_UP:
            arrayBits[pos]++;
            if (arrayBits[pos] > 1)
                arrayBits[pos] = 0;          
            break;
            
        case BUTTON_DOWN:
            arrayBits[pos]--;
            if (arrayBits[pos] < 0)
                arrayBits[pos] = 1;            
            break;
            
        case BUTTON_LEFT:
            pos--;
            if (pos < 0)
                pos = 3;
            lcd.setCursor(0, 1);
            lcd.print("    ");
            lcd.setCursor(pos, 1);
            lcd.print("^");
            break;
            
        case BUTTON_RIGHT:
            pos++;            
            if (pos > 3)
                pos = 0;
            lcd.setCursor(0, 1);
            lcd.print("    ");
            lcd.setCursor(pos, 1);
            lcd.print("^");
            break;
        }
    }
    previousButtonAlarm = currentButton;
}

int readButtons()
{
    int value = analogRead(0); // Leemos A0
    // Mis botones dan:  0, 145, 329,507,743
    // Y ahora los comparamos con un margen comodo
    if (value > 900)
        return BUTTON_NONE; // Ningun boton pulsado
    if (value < 50)
        return BUTTON_RIGHT;
    if (value < 250)
        return BUTTON_UP;
    if (value < 450)
        return BUTTON_DOWN;
    if (value < 650)
        return BUTTON_LEFT;
    if (value < 850)
        return BUTTON_SELECT;
    return BUTTON_NONE; // Por si todo falla
}

