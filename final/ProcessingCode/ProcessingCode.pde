import processing.serial.*;

Serial myPort;
String val; 
float[] nums = { 0, 0, 30 }; 

void setup(){
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600);

  size(800,800);
  background(0);
}

void draw(){
  fill(0,0,0,0.1);
  rect(0,0,795,795);
  for ( int i = 5; i<width; i += 10){
    fill(255);
    ellipse(i,795,10,10);
    ellipse(795,i,10,10);
  }
  if ( myPort.available() > 0) 
    {  // If data is available,
      val = myPort.readStringUntil('\n');         // read it and store it in val
    } 
  //println(val); //print it out in the console
  if (val != null){
    //println(val);
    nums = float(split(val, ' '));
  }
  if ( nums.length > 1){
    println(nums[0]);
    println(nums[1]);
    if (nums[0] < 7500 & nums[1] < 7500){
      float ydot = map(nums[0],0,7500,0,795);
      float xdot = map(nums[1],0,7500,0,795);
      fill(255,0,0);
      ellipse(xdot, ydot, 30, 30);
    }
  }
}