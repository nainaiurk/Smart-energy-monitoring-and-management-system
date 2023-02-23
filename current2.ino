// float current(){
//   read_Amps(a);
 
//   Serial.println("current: "+ String(c));
//   return c;
// }

void read_Amps(byte a){ //get peak to peak value
  int cnt; //Counter
  High_peak = 0; //We first assume that our high peak is equal to 0 and low peak is 1024, yes inverted
  Low_peak = 4095;
  for(cnt=0 ; cnt<1000 ; cnt++){
    float ACS_Value = analogRead(a); //We read a single value from the module
    if(ACS_Value > High_peak){
      if(ACS_Value!=4095) High_peak = ACS_Value; //The high peak will change from 0 to that value found
    }
    if(ACS_Value < Low_peak){
      if(ACS_Value!=0) Low_peak = ACS_Value; //The low peak will change from 4096 to that value found
    }
  }

  float Amps_Peak_Peak = (High_peak - Low_peak) / 4095; //Calculate the difference
  double ampss[10];
  for(byte i = 0; i < 10; i++){
    ampss[i] = Amps_Peak_Peak;
  }
  double amp = 0;
  for(byte i = 0; i < 10; i++){
    amp += ampss[i];
  }
  amps = amp/10;
}