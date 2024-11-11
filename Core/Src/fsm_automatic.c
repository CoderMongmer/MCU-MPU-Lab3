#include "fsm_automatic.h"


int red_duration = 5;
int green_duration = 3;
int yellow_duration = 2;

int temp_red = 1;
int temp_green = 1;
int temp_yellow = 1;

// LED display counters
int led1 = 0;
int led2 = 0;

// Timer for state transitions
int timer;

int status = INIT;
int traffic_status = INIT;
int segment_status = SEG_01;
int ns_time_left = 0;
int ew_time_left = 0;
int segment_buffer[4];

int forfun;

int led_index = 0;

void set_lights(int red, int yellow, int green, GPIO_TypeDef* port, uint16_t red_pin, uint16_t yellow_pin, uint16_t green_pin) {
    HAL_GPIO_WritePin(port, red_pin, red ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(port, yellow_pin, yellow ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(port, green_pin, green ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void updateLED(){
	segment_buffer[0] = led1/10; //dozen
	segment_buffer[1] = led1%10; //digit
	segment_buffer[2] = led2/10;
	segment_buffer[3] = led2%10;
}


void auto_traffic() {
	updateLED();

    switch (traffic_status) {
    case INIT:
      	ns_time_left = green_duration;
    	ew_time_left = red_duration;
    	timer = green_duration;
    	traffic_status = NS_GREEN_EW_RED;
    	break;
    case NS_GREEN_EW_RED:
        set_lights(0, 0, 1, LED_RED_0_GPIO_Port, LED_RED_0_Pin, LED_YELLOW_0_Pin, LED_GREEN_0_Pin);  // North
        set_lights(1, 0, 0, LED_RED_1_GPIO_Port, LED_RED_1_Pin, LED_YELLOW_1_Pin, LED_GREEN_1_Pin);  // South
        if (timer == 0) {
            traffic_status = NS_YELLOW_EW_RED;
            ns_time_left = yellow_duration;
            timer = yellow_duration;
        }
        break;
    case NS_YELLOW_EW_RED:
        set_lights(0, 1, 0, LED_RED_0_GPIO_Port, LED_RED_0_Pin, LED_YELLOW_0_Pin, LED_GREEN_0_Pin);  // North
        set_lights(1, 0, 0, LED_RED_1_GPIO_Port, LED_RED_1_Pin, LED_YELLOW_1_Pin, LED_GREEN_1_Pin);  // South
        if (timer == 0) {
            traffic_status = NS_RED_EW_GREEN;
            ns_time_left = red_duration;
            ew_time_left = green_duration;
            timer = green_duration;
        }
        break;
    case NS_RED_EW_GREEN:
        set_lights(1, 0, 0, LED_RED_0_GPIO_Port, LED_RED_0_Pin, LED_YELLOW_0_Pin, LED_GREEN_0_Pin);  // North
        set_lights(0, 0, 1, LED_RED_1_GPIO_Port, LED_RED_1_Pin, LED_YELLOW_1_Pin, LED_GREEN_1_Pin);  // East/West
        if (timer == 0) {
            traffic_status = NS_RED_EW_YELLOW;
            ew_time_left = yellow_duration;
            timer = yellow_duration;
        }
        break;
    case NS_RED_EW_YELLOW:
        set_lights(1, 0, 0, LED_RED_0_GPIO_Port, LED_RED_0_Pin, LED_YELLOW_0_Pin, LED_GREEN_0_Pin);  // North
        set_lights(0, 1, 0, LED_RED_1_GPIO_Port, LED_RED_1_Pin, LED_YELLOW_1_Pin, LED_GREEN_1_Pin);  // East/West
        if (timer == 0) {
            traffic_status = NS_GREEN_EW_RED;
            ns_time_left = green_duration;
            ew_time_left = red_duration;
            timer = green_duration;
        }
        break;
    }
    ns_time_left--;
    ew_time_left--;
    timer--;
    led1 = ns_time_left;
    led2 = ew_time_left;

}




void fsm_automatic_run() {
    // Update timers
	switch (status){
	case INIT:
		if (isButtonPressed(0)){
	        set_lights(1, 0, 0, LED_RED_0_GPIO_Port, LED_RED_0_Pin, LED_YELLOW_0_Pin, LED_GREEN_0_Pin);  // North
	        set_lights(1, 0, 0, LED_RED_1_GPIO_Port, LED_RED_1_Pin, LED_YELLOW_1_Pin, LED_GREEN_1_Pin);  // South
	        status = MAN_RED;
	        timer4_flag = 1;
		}

		if (timer1_flag == 1){
			auto_traffic();
			setTimer_1(1000);
		}
		if (timer2_flag == 1){
			update7SEG(led_index);
			if (++led_index == 2) led_index = 0;
			setTimer_2(100);
		}
		break;
	case MAN_RED:
		if (isButtonPressed(0)){
	        set_lights(0, 1, 0, LED_RED_0_GPIO_Port, LED_RED_0_Pin, LED_YELLOW_0_Pin, LED_GREEN_0_Pin);  // North
	        set_lights(0, 1, 0, LED_RED_1_GPIO_Port, LED_RED_1_Pin, LED_YELLOW_1_Pin, LED_GREEN_1_Pin);  // South
	        status = MAN_YELLOW;
		}

		if (isButtonPressed(1)){
			temp_red++;
			if (temp_red > 99) temp_red = 1;
		}

		if (isButtonPressed(2)){
			red_duration = temp_red;
			temp_red = 1;
		}

		if (timer2_flag == 1){
			led1 = 1;
			led2 = temp_red;
			updateLED();
			update7SEG(led_index);
			if (++led_index == 2) led_index = 0;
			setTimer_2(100);
		}

		if (timer3_flag == 1){
			HAL_GPIO_TogglePin(LED_RED_0_GPIO_Port, LED_RED_0_Pin);
			HAL_GPIO_TogglePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin);
			setTimer_3(250);
		}
		break;
	case MAN_YELLOW:
		if (isButtonPressed(0)){
	        set_lights(0, 0, 1, LED_RED_0_GPIO_Port, LED_RED_0_Pin, LED_YELLOW_0_Pin, LED_GREEN_0_Pin);  // North
	        set_lights(0, 0, 1, LED_RED_1_GPIO_Port, LED_RED_1_Pin, LED_YELLOW_1_Pin, LED_GREEN_1_Pin);  // South
	        status = MAN_GREEN;
	        timer4_flag = 1;
		}

		if (timer2_flag == 1){
			led1 = 2;
			led2 = temp_yellow;
			updateLED();
			update7SEG(led_index);
			if (++led_index == 2) led_index = 0;
			setTimer_2(100);
		}

		if (isButtonLongPressed(1)){
			if (timer4_flag == 1){
				temp_yellow++;
				if (temp_yellow > 99) temp_yellow = 1;
				setTimer_4(500);
			}
		}

		if (isButtonPressed(1)){
			temp_yellow++;
			if (temp_yellow > 99) temp_yellow = 1;
		}



		if (isButtonPressed(2)){
			yellow_duration = temp_yellow;
			temp_yellow = 1;
		}

		if (timer3_flag == 1){
			HAL_GPIO_TogglePin(LED_YELLOW_0_GPIO_Port, LED_YELLOW_0_Pin);
			HAL_GPIO_TogglePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin);
			setTimer_3(250);
		}
		break;
	case MAN_GREEN:
		if (isButtonPressed(0)){
			//Swap yellow and green
			if (yellow_duration > green_duration) {
				forfun = yellow_duration;
				yellow_duration = green_duration;
				green_duration = forfun;
			}
			if (red_duration < green_duration + yellow_duration){
				red_duration = green_duration + yellow_duration;
			}
			if (red_duration >= green_duration + yellow_duration){
				green_duration = red_duration - yellow_duration;
			}
			status = INIT;
			traffic_status = INIT;
	        timer4_flag = 1;
		}

		if (isButtonLongPressed(1)){
			if (timer4_flag == 1){
				temp_green++;
				if (temp_green > 99) temp_green = 1;
				setTimer_4(500);
			}
		}

		if (isButtonPressed(1)){
			temp_green++;
			if (temp_green > 99) temp_green = 1;
		}



		if (isButtonPressed(2)){
			green_duration = temp_green;
			temp_green = 1;
		}

		if (timer2_flag == 1){
			led1 = 3;
			led2 = temp_green;
			updateLED();
			update7SEG(led_index);
			if (++led_index == 2) led_index = 0;
			setTimer_2(100);
		}

		if (timer3_flag == 1){
			HAL_GPIO_TogglePin(LED_GREEN_0_GPIO_Port, LED_GREEN_0_Pin);
			HAL_GPIO_TogglePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin);
			setTimer_3(250);
		}
		break;
	default:
		break;
	}


}
