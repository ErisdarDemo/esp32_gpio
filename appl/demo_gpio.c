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

//Project Includes
#include "system.h"


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//

//Print Definitions
#define MAX_BUFF_LEN            (50)                /* enough to print string                     */
#define DEMO_DELAY_MS           (1000)


//************************************************************************************************//
//                                            VARIABLES                                           //
//************************************************************************************************//

//Activity Count
static int demo_isr_ctr = 0;


//************************************************************************************************//
//                                       FUNCTION DECLARATIONS                                    //
//************************************************************************************************//


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

