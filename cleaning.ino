
int whells = 3; // Arduino PWM output pin 3; connect to IBT-2 pin 1 (RPWM)
double required_pwm_whl = 80; // duty-cycle to PWM pump
int r_brush = 5; // Arduino PWM output pin 3; connect to IBT-2 pin 1 (RPWM)
double required_pwm_r_brs = 80; // duty-cycle to PWM pump
int l_brush = 6; // Arduino PWM output pin 3; connect to IBT-2 pin 1 (RPWM)
double required_pwm_l_brs = 80; // duty-cycle to PWM pump
int m_brush = 2; // Arduino PWM output pin 3; connect to IBT-2 pin 1 (RPWM)
double required_pwm_m_brs = 80; // duty-cycle to PWM pump
bool is_all_active = false;



void setup() {
  // put your setup code here, to run once:
  pinMode(whells, OUTPUT); // set pump pin at output
  pinMode(r_brush, OUTPUT); // set pump pin at output
  pinMode(l_brush, OUTPUT); // set pump pin at output
  pinMode(m_brush, OUTPUT); // set pump pin at output
  Serial.begin(9600);
  TCCR3B=(TCCR3B&0xF8) | 1;
  TCCR4B=(TCCR4B&0xF8) | 1;

  
}

void loop() {
  // put your main code here, to run repeatedly:
   // Handle the menu
  menu_handler();

  // Update the LCD
  update_screen(required_pwm_whl); //

  if (is_all_active)
  {
    analogWrite(whells, required_pwm_whl);
    analogWrite(r_brush, required_pwm_r_brs);
    analogWrite(l_brush, required_pwm_l_brs);
    analogWrite(m_brush, required_pwm_m_brs);
  }
  else 
  {
    analogWrite(whells, 0);
    analogWrite(r_brush, 0);
    analogWrite(l_brush, 0);
    analogWrite(m_brush, 0);
  }

}
