#include "user_interface.h"
/*******************************************************************************
* Menu handler
* Buttons:
*           Right - scrolls right the menu
*           Left - scrolls left the menu
*           Up - increment current menu place
*           Down - decrement current menu place
*           Select - transiotion to On mode           
* Menu places: 
*           0=required velocity
*           1=Open angle
*           2=Close angle
*           3=servo_delay
*           4=HVLP enable
*           5=Feeder enable
*******************************************************************************/

void menu_handler()
{
  // poll the buttons
  get_button();

  if (current_button != NO_BUTTON)
  {
    // handle pressed button
    lcd.setCursor(0,1);
    lcd.print("               ");

    switch (current_button) {
      case RIGHT_BUTTON:
        // handle right button - update the menu place       
        menu_place_id = (menu_place_id+1) % MAX_MENU_PLACES;
        //lcd.print ("Right ");
        break;
      case LEFT_BUTTON:
        // Left button - update the menu place
        menu_place_id = (menu_place_id-1) % MAX_MENU_PLACES;
        if (menu_place_id<0)
          menu_place_id += MAX_MENU_PLACES;
        //lcd.print (menu_place_id);
        break;
      case UP_BUTTON:
        // Up button - increase/toggle the relevant menu place value
        switch (menu_place_id) {
          case MENU_REQ_VEL_WHL:
            required_pwm_whl = min(required_pwm_whl+REQ_VEL_WHL_STEP, MAX_REQ_VEL_WHL);
            break;
          case MENU_VEL_R_BRS:
            required_pwm_r_brs = min(required_pwm_r_brs+REQ_VEL_R_BRS_STEP, MAX_REQ_VEL_R_BRS);
            break;
          case MENU_VEL_L_BRS:
            required_pwm_l_brs = min(required_pwm_l_brs+REQ_VEL_L_BRS_STEP, MAX_REQ_VEL_L_BRS);
            break;
          case MENU_VEL_M_BRS:
            required_pwm_m_brs = min(required_pwm_m_brs+REQ_VEL_M_BRS_STEP,MAX_REQ_VEL_M_BRS);
            break;
          /*case MENU_HVLP_EN:
           is_hvlp_enabled = not(is_hvlp_enabled);
            break;
          case MENU_FEEDER_EN:
            is_feeder_enabled = not(is_feeder_enabled);
            break; */        
          default:
            // statements
            break;
        }        
        break;
      case DOWN_BUTTON:
        // Down button - decrease/toggle the relevant menu place value  
        switch (menu_place_id) {
          case MENU_REQ_VEL_WHL:
            required_pwm_whl = max(required_pwm_whl-REQ_VEL_WHL_STEP, 0);
            break;
          case MENU_VEL_R_BRS:
            required_pwm_r_brs = max(required_pwm_r_brs-REQ_VEL_R_BRS_STEP, 0);
            break;
          case MENU_VEL_L_BRS:
            required_pwm_l_brs = max(required_pwm_l_brs-REQ_VEL_L_BRS_STEP, 0);
            break;
          case MENU_VEL_M_BRS:
            required_pwm_m_brs = max(required_pwm_m_brs-REQ_VEL_M_BRS_STEP,0);
            break;
          /*case MENU_HVLP_EN:
           is_hvlp_enabled = not(is_hvlp_enabled);
            break;
          case MENU_FEEDER_EN:
            is_feeder_enabled = not(is_feeder_enabled);
            break;*/       
          default:
            // statements
            break;
        }   
        break;
      case SELECT_BUTTON:
        // Select button - toggle feeder mode        
        is_all_active = not(is_all_active);             
        break;          
      default:
        // statements
        break;
    }

    // reset current button
    current_button = NO_BUTTON;    
         
  }
}

/*******************************************************************************
* Loop function
*******************************************************************************/

void update_screen(float pwm_whl)
{/*
    // upper row
    lcd.setCursor(0,0);
    if (is_pump_active)
    {
      // Active pump display
      lcd.print ("Active ");      
      lcd.print (current_pressure);
      lcd.print ("mBar");
    }
    else
    {
      // Inactive pump display
      lcd.print ("Inactive        ");
    }
    */
    // lower row
    lcd.setCursor(0,1);
    switch (menu_place_id) {
        case MENU_REQ_VEL_WHL:
          lcd.print ("DRIVE PWM = ");
          lcd.print (required_pwm_whl);
          break;
        case MENU_VEL_R_BRS:
          lcd.print ("BRS R PWM = ");
          lcd.print (required_pwm_r_brs);
          break;
        case MENU_VEL_L_BRS:
          lcd.print ("BRS L PWM = ");
          lcd.print (required_pwm_l_brs);
          break;
        case MENU_VEL_M_BRS:
          lcd.print ("BRS M PWM = ");
          lcd.print (required_pwm_m_brs);
          break;
        /*case MENU_HVLP_EN:
          if (is_hvlp_enabled)
            lcd.print("HVLP enabled");
           else
            lcd.print("HVLP disabled");
          break;
        case MENU_FEEDER_EN:
          if (is_feeder_enabled)
            lcd.print("Feeder enabled");
           else
            lcd.print("Feeder disabled");
          break;*/       
        default:
          // statements
          break;
      }  
}


/*******************************************************************************
* Get button
*   Indicates if a new button was pressed (right after the button was released)
*   The using function is expected to set current_button to NO_BUTTON
*******************************************************************************/
void get_button() 
{
  
  static bool is_pressed_internal = false;
  static int last_button = NO_BUTTON;
  int x;

  // sample button analog pin
  x = analogRead (0); 

  if (is_pressed_internal)
  {
    // Wait for button release
    if (x>=800)
    {
      // button release - update current button
      current_button = last_button;
      last_button = NO_BUTTON;
      is_pressed_internal = false;     
    }
  }
  else // check if new button is pressed
  {     
    if (x<100)
      // Right button
      last_button = RIGHT_BUTTON;
    else if (x < 200)
      // Up button 
      last_button = UP_BUTTON;
    else if (x<400)
      // Down button
      last_button = DOWN_BUTTON;
    else if (x<600)
      // Left button
      last_button = LEFT_BUTTON;
    else if (x<800)
      // Select button
      last_button = SELECT_BUTTON;

     // indicate a button is pressed
     if (last_button > 0)
      is_pressed_internal = true;
  }
}
