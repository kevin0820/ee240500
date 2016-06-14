#include "simpletools.h"
#include "servo.h"
#include "servodiffdrive.h"
#include "fdserial.h"
#include "talk.h"
#include "ping.h"                             // Include ping header
#include "abdrive.h"
#include "stdlib.h"

#define PIN_SOUND       26 // pin for the speaker, default=26
#define PIN_XBEE_RX      0
#define PIN_XBEE_TX      1
#define PIN_SERVO_LEFT  14
#define PIN_SERVO_RIGHT 15

char char2lowercase (char c);
void avoid(int x_move);
void position(int x, int y , int init_x, int init_y);

int main (void) {

	fdserial *xbee;
	xbee = fdserial_open(PIN_XBEE_RX, PIN_XBEE_TX, 0, 9600);
	drive_pins(PIN_SERVO_LEFT, PIN_SERVO_RIGHT);

	pause(1000);
	putchar(CLS);
	fdserial_rxFlush(xbee);
   int cmDist;
   int x_now=0;
   int y_now=0;

	while (1) {
		int ch = fdserial_rxChar(xbee);
		ch = char2lowercase(ch);
		fdserial_rxFlush(xbee);
		switch ((char) ch) {
			case '1':
				print("water\n");
          /*for (int i=0;i<20;i++){
           cmDist = ping_cm(18);                 // Get cm distance from Ping)))
           print("cmDist = %d\n", cmDist);           // Display distance
           drive_speeds(100, 100);
           pause(200);                               // Wait 1/5 second
          }          
				//pause(2000);
				drive_speeds(0, 0);*/
          position(-10,10,x_now,y_now);
          x_now=-10;
          y_now=10;
				break;
			case '2':
				print("product 2\n");
          position(6,6,x_now,y_now);
          x_now=6;
          y_now=6;
				break;
        case 'b':
				print("pay position\n");
          position(0,5,x_now,y_now);
          x_now=0;
          y_now=5;
			 break;
        case 'c':
				print("finish\n");
          position(0,0,x_now,y_now);
          x_now=0;
          y_now=0;
			 break;
			case 'r':
				print("Right\n");
				drive_speeds(50, -50);
				pause(900);
				drive_speeds(0, 0);
				break;
			case 'l':
				print("Left\n");
				drive_speeds(-50, 50);
          pause(900);
				drive_speeds(0, 0);
				break;
			case 's':
				print("Sing\n");
				talk_Start(PIN_SOUND);
				talk_Set_speaker(0, 100);
				talk_Say("#1aybee+7seedee++ee ef--jee, --aychae-jaykay--elemenoa--pee, +7kewar--esand-teeew--vee, +5dubul--yewand-ekswae--z%150ee%;");
				talk_Say("_nowyoov+7herdmae++aybee--sees, --telmee-wutyoo--thinkuv--m%200ee%...");
				pause(700);
				break;
			default:
				print("Invalid Command\n");
				pause(700);
				break;
		}
		//print("%c", (char) ch);
		pause(100);
		fdserial_txChar(xbee, ch);
		fdserial_txFlush(xbee);
	}

}

char char2lowercase (char c) {
	return 'A'<=c && c<='Z' ? c+32 : c;
}

void avoid(int x_move){
   if (ping_cm(18)<10){
     drive_speeds(50, -50);
		pause(900);
		drive_speeds(0, 0);
     for (int i=0;i<5;i++){
        drive_speeds(100, 100);
        pause(200);
     }
     x_move=x_move-5;       
     drive_speeds(0, 0);
     drive_speeds(-50, 50);
		pause(900);
		drive_speeds(0, 0);
   }     
}  

void position(int x, int y , int init_x, int init_y){
     int x_move=x-init_x;
     int y_move=y-init_y;
     if (y_move<0){
         drive_speeds(50, -50);
			  pause(1700);
         drive_speeds(0, 0); 
     }
     for (int i=0;i<abs(y_move);i++){
         //avoid(x_move);
         if (ping_cm(18)<10){
            drive_speeds(-50, 50);
		       pause(900);
		       drive_speeds(0, 0);
            drive_speeds(100, 100);
            pause(1000);
            drive_speeds(0, 0);
            if (y_move>0){
              x_move=x_move+5;
            }
            else {
              x_move=x_move-5;
            }              
            drive_speeds(0, 0);
            drive_speeds(50, -50);
		       pause(900);
		       drive_speeds(0, 0);
         }          
         drive_speeds(100, 100);       
         pause(200);                               // Wait 1/5 second
     }
     drive_speeds(0, 0);
     if (y_move>0){
      if (x_move>0){
         drive_speeds(50, -50);
			  pause(900);
         drive_speeds(0, 0); 
      }
      else{
         drive_speeds(-50, 50);
			  pause(900);
         drive_speeds(0, 0);
      }
     }
     else {
      if (x_move>0){
         drive_speeds(-50, 50);
			  pause(900);
         drive_speeds(0, 0); 
      }
      else{
         drive_speeds(50, -50);
			  pause(900);
         drive_speeds(0, 0);
      }
     }                   
     int a=0;
     for (int i=0;i<abs(x_move);i++){
         //avoid(y_move);
         if (ping_cm(18)<10){
            drive_speeds(50, -50);
		       pause(900);
		       drive_speeds(0, 0);
            drive_speeds(100, 100);
            pause(1000);
            drive_speeds(0, 0);
            a=a+5;
            drive_speeds(0, 0);
            drive_speeds(-50, 50);
		       pause(900);
		       drive_speeds(0, 0);
         }
         drive_speeds(100, 100);
         pause(200);                               // Wait 1/5 second
     }
     drive_speeds(0, 0);
     if (x_move>0){
         drive_speeds(-50, 50);
			  pause(900); 
     }
     else{
         drive_speeds(50, -50);
			  pause(900);
     }
     drive_speeds(0, 0);
     for (int i=0;i<a;i++){
         //avoid(x_move);
         if (ping_cm(18)<10){
            drive_speeds(50, -50);
		       pause(900);
		       drive_speeds(0, 0);
            drive_speeds(100, 100);
            pause(1000);
            drive_speeds(0, 0);
            drive_speeds(0, 0);
            drive_speeds(-50, 50);
		       pause(900);
		       drive_speeds(0, 0);
         }          
         if (x_move<0){
           drive_speeds(-100, -100);       
           pause(200);
         }                                        // Wait 1/5 second
         else{
           drive_speeds(100, 100);       
           pause(200);
         }
     }                     
	  drive_speeds(0, 0);
     freqout(4, 1000, 3000);
} 