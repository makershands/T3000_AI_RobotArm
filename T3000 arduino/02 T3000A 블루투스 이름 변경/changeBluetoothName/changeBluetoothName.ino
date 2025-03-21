void setup()
{
  Serial.begin(9600);  
}

void loop()
{
  delay(1000);
  Serial.write("AT+NAMETEST\n");
}
