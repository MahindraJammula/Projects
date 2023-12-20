#include <LiquidCrystal.h>
#include<Servo.h>
#include <SoftwareSerial.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
Servo myservo;
Servo myservo1;
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int cnt=0;
int buz = 8;
int s1 = A1;
int s2 = A2;
int s3 = A3;


 int pos;
int s1s=0;
int s2s=0;
int s3s=0;


int am1=100;
int am2=100;
int am3=100;
int vhno,ts1,ts2,ts3,tm,vhn=0;
int x;
 int bk1=0;
    int bk2=0;
    int bk3=0;
    int bk4=0;
 int xx=48;   
void setup() {
  
Serial.begin(9600);
lcd.begin(16,2);
lcd.print("WELCOME");
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
pinMode(s1,INPUT);
pinMode(s2,INPUT);
pinMode(s3,INPUT);

pinMode(buz,OUTPUT);
myservo.attach(A0);

delay(1000);

for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
     
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
    
void gate()
{
 
      for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(5000);
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}


void loop()
{    
    lcd.clear();
    lcd.print("WELCOME");
        
    int sl1=1-digitalRead(s1);
    int sl2=1-digitalRead(s2);
    int sl3=1-digitalRead(s3);
    
    if(Serial.available())
    {
      xx=Serial.read();
       delay(1);
    }
    
    if(xx=='1')
    {
      bk1=1;
      bk2=0;
      bk3=0;
      bk4=0;
    }

     if(xx=='2')
    {
      bk1=0;
      bk2=1;
      bk3=0;
      bk4=0;
    }

        if(xx=='3')
    {
      bk1=1;
      bk2=1;
      bk3=0;
      bk4=0;
    }

        if(xx=='4')
    {
      bk1=0;
      bk2=0;
      bk3=1;
      bk4=0;
    }

        if(xx=='5')
    {
      bk1=1;
      bk2=0;
      bk3=1;
      bk4=0;
    }

        if(xx=='6')
    {
      bk1=0;
      bk2=1;
      bk3=1;
      bk4=0;
    }

        if(xx=='7')
    {
      bk1=1;
      bk2=1;
      bk3=1;
      bk4=0;
    }
    
        if(xx=='0')
    {
      bk1=0;
      bk2=0;
      bk3=0;
      bk4=0;
    }
   
    if(bk1==1)
        sl1=2;
    if(bk2==1)
        sl2=2;
    if(bk3==1)
        sl3=2;
   
             
    lcd.setCursor(0,1);
    lcd.print("A:"+String(sl1) + " B:"+String(sl2) + " C:"+String(sl3) );
    if(cnt>5)
    {
      cnt=0;
    
    Serial.println(",0,"+String(sl1) + ","+String(sl2) + ","+String(sl3) + ","+"0");
    }
    scan_rfid();
    if(vhn>0)
    {
   
    if(sl1==0 || sl2==0 || sl3==0 )
    {
                if(vhn==1)
                {
                    vhno=1;
                    s1s=s1s+1;
                    
                    if(s1s==1)
                    {
                      lcd.clear();
                      lcd.print("ENTRY-1");
                        ts1=millis();
                        gate();
                    }
                    if(s1s==2)
                    {
                        s1s=0;
                        
                        tm=(millis()-ts1)/1000;
                       lcd.clear();
                       lcd.print("EXIT-1  "+ String(tm)+"/-");
                        delay(1000);
                        if(am1>=tm)
                          {
                             am1=am1-tm;
                             lcd.setCursor(0,1);
                             lcd.print("Amount deducted");
                          }
                        else
                        {
                            
                            lcd.clear();
                            lcd.print("No Balance");
                            digitalWrite(buz,1);
                             delay(1000);
                            digitalWrite(buz,0);
                        }
                            
                        gate();
                    }
                }
                        

                if(vhn==2)
                {
                    vhno=2;
                    s2s=s2s+1;
                    
                    if(s2s==1)
                    {
                      lcd.clear();
                      lcd.print("ENTRY-2");
                        ts2=millis();
                        gate();
                    }
                    if(s2s==2)
                    {
                        s2s=0;
                        
                        tm=(millis()-ts2)/1000;
                       lcd.clear();
                       lcd.print("EXIT-2  "+ String(tm)+"/-");
                        delay(1000);
                        if(am2>=tm)
                          {
                             am2=am2-tm;
                             lcd.setCursor(0,1);
                             lcd.print("Amount deducted");
                          }
                        else
                        {
                            
                            lcd.clear();
                            lcd.print("No Balance");
                            digitalWrite(buz,1);
                             delay(1000);
                            digitalWrite(buz,0);
                        }
                            
                        gate();
                    }
                }


                if(vhn==3)
                {
                    vhno=3;
                    s3s=s3s+1;
                    
                    if(s3s==1)
                    {
                      lcd.clear();
                      lcd.print("ENTRY-3");
                        ts3=millis();
                        gate();
                    }
                    if(s3s==2)
                    {
                        s3s=0;
                        
                        tm=(millis()-ts3)/1000;
                       lcd.clear();
                       lcd.print("EXIT-3  "+ String(tm)+"/-");
                        delay(1000);
                        if(am3>=tm)
                          {
                             am3=am3-tm;
                             lcd.setCursor(0,1);
                             lcd.print("Amount deducted");
                          }
                        else
                        {
                            
                            lcd.clear();
                            lcd.print("No Balance");
                            digitalWrite(buz,1);
                             delay(1000);
                            digitalWrite(buz,0);
                        }
                            
                        gate();
                    }
                }


      
    } 
                 
            else
            {
                
               lcd.clear();
               lcd.print(" Parking Full");
               digitalWrite(buz,1);
               delay(2000);
                digitalWrite(buz,0);
            }
vhn=0;
    }
    delay(500);
    cnt=cnt+1;
}

void scan_rfid()
 {
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  //Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    // Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  //Serial.println();
  //Serial.print("Message : ");
  content.toUpperCase();
 // Serial.println(content.substring(1));
  if(content.substring(1)=="EB 33 89 2B")
  {
   vhn=1;
  }

    if(content.substring(1)=="7B 73 1D 85")
  {
   vhn=2;
  }

    if(content.substring(1)=="CC 59 1D 85")
  {
    vhn=3;
  }

    if(content.substring(1)=="81 A6 57 40")
  {
    vhn=4;
  }
   delay(500);
  
 }
    
  
