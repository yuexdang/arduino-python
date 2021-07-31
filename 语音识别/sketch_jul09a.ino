#include <Servo.h>
Servo myservo10;
Servo myservo7;
Servo myservo9;
Servo myservo6;
Servo myservo8;

int x = 50,y = 60;

//右眼
int center_x = x,center_y = y;
//左眼
int center_x_ano = x,center_y_ano = y;
//眼睑
int cover = 80;

int padding = 15; 
int multiple = 1;
 
//int i[4][4]=[[10,10],[10,50],[60,50],[60,10]];
void setup() {
  Serial.begin(9600);
// 右眼
  myservo10.attach(10);
  myservo7.attach(7);
//  左眼
  myservo9.attach(9);
  myservo6.attach(6);
//  眼睑
  myservo8.attach(8);
  
  boundary_scan_right();
  boundary_scan_left();
  boundary_eyeupon();
  myservo10.write(center_y);
  myservo7.write(center_x);
  myservo9.write(center_y_ano);
  myservo6.write(center_x_ano);
  myservo8.write(155);
}

void boundary_eyeupon() {
  // 眼皮
  myservo8.write(80);
  delay(500);
  myservo8.write(155);
  delay(500);
  }

void boundary_scan_right() {
  // 边界扫描 _右眼
  myservo10.write(center_x+padding*1);
  myservo7.write(center_x+(int)padding*0.8);
  delay(300);
  myservo10.write(center_x-padding*1);
  myservo7.write(center_x+(int)padding*0.8);
  delay(300);
  myservo10.write(center_x-padding*1);
  myservo7.write(center_x-(int)padding*0.8);
  delay(300);
  myservo10.write(center_x+padding*1);
  myservo7.write(center_x-(int)padding*0.8);
  delay(300);
}

void boundary_scan_left() {
  // 边界扫描 _左眼
  myservo9.write(center_x_ano+padding*1);
  myservo6.write(center_x_ano+(int)padding*0.8);
  delay(300);
  myservo9.write(center_x_ano-padding*1);
  myservo6.write(center_x_ano+(int)padding*0.8);
  delay(300);
  myservo9.write(center_x_ano-padding*1);
  myservo6.write(center_x_ano-(int)padding*0.8);
  delay(300);
  myservo9.write(center_x_ano+padding*1);
  myservo6.write(center_x_ano-(int)padding*0.8);
  delay(300);
}

void boundary_scan() {
//  伪同步
  myservo10.write(center_x+padding*1);
  myservo7.write(center_x+(int)padding*0.8);
  myservo9.write(center_x_ano+padding*1);
  myservo6.write(center_x_ano+(int)padding*0.8);
  delay(300);
  myservo10.write(center_x-padding*1);
  myservo7.write(center_x+(int)padding*0.8);
  myservo9.write(center_x_ano-padding*1);
  myservo6.write(center_x_ano+(int)padding*0.8);
  delay(300);
  myservo10.write(center_x-padding*1);
  myservo7.write(center_x-(int)padding*0.8);
  myservo9.write(center_x_ano-padding*1);
  myservo6.write(center_x_ano-(int)padding*0.8);
  delay(300);
  myservo10.write(center_x+padding*1);
  myservo7.write(center_x-(int)padding*0.8);
  myservo9.write(center_x_ano+padding*1);
  myservo6.write(center_x_ano-(int)padding*0.8);
  delay(300);
  }

void loop() {
// boundary_scan_left();
// boundary_scan_right();
//  boundary_scan();
//  boundary_eyeupon();

int read = Serial.read() ;
//Serial.println(read);
if (center_x > x+(int)padding*0.8 || center_x < x-(int)padding*0.8) {
 center_x = x;
 myservo7.write(center_x);    
 }
else if (center_y > y+padding || center_y < y-padding) {
 center_y = y;
 myservo10.write(center_y);    
 }
else{
 if(read == '1'){
   center_x += (int)(padding*multiple*0.8);
   myservo7.write(center_x);
   read = '\0';
   }
 else if(read == '2') {
   center_x -= (int)(padding*multiple*0.8);
   myservo7.write(center_x);
   read = '\0';
   }
 else if(read == '3') {
   center_y -= (int)padding*multiple;
   myservo10.write(center_y);
   read = '\0';
   }
 else if(read == '4') {
   center_y += (int)padding*multiple;
   myservo10.write(center_y);
   read = '\0';
   }
 else if(read == '5') {
   center_x = x;
   center_y = y;
   boundary_scan_right();
   myservo7.write(x);
   myservo10.write(y);
   read = '\0';
   }
}

}
