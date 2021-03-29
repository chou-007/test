/*
 * 发送给QT的是当前的摇杆的数值 
 * QT发送回来的是和目标值的差值以及是否启动震动开关
 */
int motorPin = 6; //振动马达控制引脚
char brightness; //设置震动强度,最大的强度是200
char motorSW ;
int value = 0;
bool tranSW = false;
long tranNUM = 0;
//int first;
//int second;
char temp; 
int flag=1;

int i=120;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600); //串口初始化函数 用来设置串口的波特率
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(1); 
  value = ceil(value/7); //距离目标值越近的时候，震动得越厉害

  temp=Serial.read(); //上位机发送到Arduino的数据
  //Serial.write(value); //发送给上位机的实际的摇杆的值
//  if(abs(value-47)>20){
//    tranSW = true;
//  }
  if(tranSW == true){
      //Serial.println(value, DEC);
      Serial.write(value);
  }
  //Serial.println(value, DEC); //经过测试得出Y方向的最小值是：0最大值是：1023(3FF)输入电压为5V的时候，输入电压为3.3V的时候，最小是：0，最大是：700
  if(temp!=-1)
  {
        if(temp == '}') //运行的标志位
        {
          flag=1;
        }
        else if(temp == '{') //停止的标志位
        {
          flag=3;
        }
        else if(temp == '|')
        {
          //flag=2;
          tranSW = true;
        }
        else
        {
            flag=2;
        }
          if(flag==1)
        {
          motorSW=temp;
        }
        if(flag==2)
        {
          brightness = temp;
        }
        if(flag==3)
        {
            motorSW=temp;
            brightness = 100;
            //Serial.write('f');
        }
        if(motorSW=='}')
        {
             analogWrite(motorPin, 200-2*(int(brightness)));   //这儿改变强度值
             //Serial.write('c');
        }
        else if(motorSW == '{')
        {
             analogWrite(motorPin, 0); 
             //Serial.write('r');
        }
  }
  else
  {
      analogWrite(motorPin, 0); 
  }
  //tranNUM++;
  delay(50);
}
