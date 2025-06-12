/**************************************************************************************************/
/** @file       gpio_demo.c
 *  @brief      GPIO Driver reference example
 *  @details    x
 *
 *  @section    Opens
 *      debounced interrupt response
 */
/**************************************************************************************************/


//************************************************************************************************//
//                                        COMPILER DIRECTIVES                                     //
//************************************************************************************************//

#pragma GCC diagnostic ignored "-Wformat-security"


//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//Standard Library Includes
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//Driver Includes
#include "esp32_gpio.h"

//Wakeup Demo Includes
#include "esp_sleep.h"
#include "esp_timer.h"

//Project Includes
#include "system.h"


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//

//Print Definitions
#define MAX_BUFF_LEN            (50)                /* enough to print string                     */
#define DEMO_DELAY_MS           (1000)

//Wakeup Demo Definitions
#define BOOT_BUTTON_NUM         (0)                 /* Freenove ESP32-S3 WROOM board              */
#define GPIO_WAKEUP_NUM         (BOOT_BUTTON_NUM)   /* Use boot button as gpio input              */
#define GPIO_WAKEUP_LEVEL       (0)                 /* Freenove "Boot" button is active low       */

#define BOOT0_INIT_DELAY_MS     (10)
#define DELAY_BEFORE_SLEEP_MS   (250)


//************************************************************************************************//
//                                            VARIABLES                                           //
//************************************************************************************************//

//Activity Count
static int demo_isr_ctr = 0;


//************************************************************************************************//
//                                       FUNCTION DECLARATIONS                                    //
//************************************************************************************************//

//Demo Routines
static void demo_light_sleep(void);

static void setup_boot0_gpio_wakeup(void);


//************************************************************************************************//
//                                          PUBLIC FUNCTIONS                                      //
//************************************************************************************************//

/**************************************************************************************************/
/** @fcn        void demo_gpio(void)
 *  @brief      Demo application routine
 *  @details    x
 *
 *  @pre    system_initialize()
 *  @post   no return
 */
/**************************************************************************************************/
void demo_gpio(void) {

	//Locals
	bool rd_val             = false;                /* Demo GPIO read value                       */
	char *driverVer         = NULL;                 /* Driver API request ptr                     */    
	char buff[MAX_BUFF_LEN] = {0};                  /* Console print buffer                       */


	//------------------------------------------- Init -------------------------------------------//

	//Init Variables
	memset(&buff[0], 0x00, MAX_BUFF_LEN);

	driverVer = gpio_getVersion();
	
	
    //----------------------------------------- Operate ------------------------------------------//
	
    for(;;) {
		
		//****************************************************************************************//
		//                                          WRITE                                         //
		//****************************************************************************************//

		//Write
		gpio_write(GPIO_DO_0, false);
		gpio_write(GPIO_DO_0, true);
		gpio_write(GPIO_DO_0, false);


		//****************************************************************************************//
		//                                         TOGGLE                                         //
		//****************************************************************************************//

		//Toggle
		gpio_toggle(GPIO_DO_0);
		gpio_toggle(GPIO_DO_0);
		gpio_toggle(GPIO_DO_0);


		//****************************************************************************************//
		//                                          READ                                          //
		//****************************************************************************************//

		//Read
		rd_val = gpio_read(GPIO_DI_0);


		//Response
		sprintf(&buff[0], "demo_gpio(v%s) - READ(GPIO%d): %d, ISR(GPIO%d): %d\n\n",
		                                                 driverVer,
		                                                 GPIO_PIN_DI_0_NUM, 
		                                                 rd_val, 
		                                                 GPIO_PIN_ISR_NUM,  
		                                                 demo_isr_ctr);						
		//Notify
		printf((const char *)&buff[0]);
		
		
		//****************************************************************************************//
		//                                         WAKEUP                                         //
		//****************************************************************************************//

		//Sleep Demo                                        
		demo_light_sleep();                         /* wake from boot0 button                     */

		
	    //------------------------------------------ Post ----------------------------------------//

	    //Loop
	    delay_ms(DEMO_DELAY_MS);

    }
}


/**************************************************************************************************/
/** @fcn        void demo_isr_handler(void)
 *  @brief      Example application interrupt response
 *  @details    Response to configured GPIO interrupt response activity
 *
 *  @section    Operation
 *      non-blocking routine
 *
 *  @note   application space interrupt handle with system module interface for gpio driver use
 */
/**************************************************************************************************/
void demo_isr_handler(void) {

    //Record
    demo_isr_ctr++;

    return;
}


/**************************************************************************************************/
/** @fcn        void demo_light_sleep(void)
 *  @brief      Light Sleep Example using BOOT0 button
 *  @details    x
 *
 *  @section    Opens
 *      migrate to esp32_system api & use
 */
/**************************************************************************************************/
static void demo_light_sleep(void) {
    
    //Locals
    int64_t                  t_after_us;            /* Time sleeping report                       */
    esp_sleep_wakeup_cause_t wake_src;              /* Source of wakeup report                    */
    

    //------------------------------------------ Setup -------------------------------------------//

    //Setup
    setup_boot0_gpio_wakeup();                      /* Enable wakeup from light sleep by gpio     */


    //------------------------------------------ Sleep -------------------------------------------//
    
    //Notify
    printf("Entering sleep mode, press BOOT/IO0 to resume\n");

    //Console
    delay_ms(DELAY_BEFORE_SLEEP_MS);                /* give console time to print before sleep    */

    //Sleep
    esp_light_sleep_start();                        /* Enter sleep mode                           */


    //----------------------------------------- Process ------------------------------------------//

    //Capture Timing
    t_after_us = esp_timer_get_time();

    
    //Check Source
    wake_src = esp_sleep_get_wakeup_cause();

    //Notify
    switch(wake_src) {
        
        case ESP_SLEEP_WAKEUP_GPIO:
            printf("demo_light_sleep(): GPIO Wakeup at %lld us\n", t_after_us);
            break;
            
        default:
            printf("demo_light_sleep(): Unknown Wakeup source report\n");
    }

    
    return;
}


/**************************************************************************************************/
/** @fcn        esp_err_t setup_boot0_gpio_wakeup(void)
 *  @brief      Prepare BOOT0/IOo pin for GPIO wakeup demo
 *  @details    x
 */
/**************************************************************************************************/
static void setup_boot0_gpio_wakeup(void) {

    //----------------------------------- ? ------------------------------------------------------//    

    /* Initialize GPIO */
    gpio_config_t config = {
            .pin_bit_mask = BIT64(GPIO_WAKEUP_NUM),
            .mode         = GPIO_MODE_INPUT,
            .pull_down_en = false,
            .pull_up_en   = false,
            .intr_type    = GPIO_INTR_DISABLE
    };
    
    
    gpio_config(&config);

    //--------------------------------- Enable ---------------------------------------------------//    

    /* Enable wake up from GPIO */
    gpio_wakeup_enable(GPIO_WAKEUP_NUM, GPIO_WAKEUP_LEVEL == 0 ? GPIO_INTR_LOW_LEVEL : GPIO_INTR_HIGH_LEVEL);
                        
    esp_sleep_enable_gpio_wakeup();

    
    //------------------------- Prepare IO for Wakeup --------------------------------------------//    
    printf("Waiting for GPIO%d to go high...\n", GPIO_WAKEUP_NUM);

    int rd_val = 0;
    
    /* Make sure the GPIO is inactive and it won't trigger wakeup immediately */    
    while(rd_val == GPIO_WAKEUP_LEVEL) {

        rd_val = gpio_get_level(GPIO_WAKEUP_NUM);

        delay_ms(BOOT0_INIT_DELAY_MS);
    }

        
    //Notify    
    printf("GPIO wakeup source is ready\n");

    return;
}


