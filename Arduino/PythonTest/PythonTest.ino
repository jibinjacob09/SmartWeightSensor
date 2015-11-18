long i;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int num = random(100);
  double num2 = random(500);
  i = i+1;
  Serial.print(i);
  Serial.print(",");
  Serial.print(num);
  Serial.print(",");
  Serial.println(num2);
  delay(50);

}
