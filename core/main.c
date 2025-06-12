/**************************************************************************************************/
/** @file     main.c
 *  @brief    ESP32 GPIO Driver Development
 *  @details  For test & validation of esp32_gpio.c&h
 *
 *  @author   Justin Reina, Firmware Engineer
 *  @created  6/12/25
 *  @last rev 6/12/25
 *
 *  @section    Opens
 *      GPIO Interrupt
 *      GPIO Wake From Sleep
 *		...
 *		Demo publishes detailed narration & instruction for demo
 *      ...
 *      complete
 *		test
 *      publish
 *		...
 *		! use a wiki page to track & collect bug reports in your new sweep (including published 
 *		  procedure!)
 *
 *  @note   use esp32_system api for sleep modes
 *
 *  @section    Legal Disclaimer
 *      ©2025 Justin Reina. All rights reserved. All contents of this source file and/or any other
 *      related source files are the explicit property of Justin Reina. Do not distribute.
 *      Do not copy.
 */
/**************************************************************************************************/

//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//Standard Library Includes
#include <stdio.h>

//Project Includes
#include "system.h"

//Application Includes
#include "demo.h"


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//

//Timing
#define SLEEP_DELAY_MS      (2000)                  /* nice loop delay for runtime demo           */

//Demo
#define MAX_LOOP_CT         (5)                     /* reset after a few loops                    */


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//

//Base Template Version
#define BASE_TEMPL_VERS         "1"


//************************************************************************************************//
//                                       FUNCTION DECLARATIONS                                    //
//************************************************************************************************//

//Version API
static char *baseTempl_getVersion(void);


//************************************************************************************************//
//                                          PUBLIC FUNCTIONS                                      //
//************************************************************************************************//

/**************************************************************************************************/
/** @fcn        void app_main(void)
 *  @brief      FreeRTOS task for main application
 *  @details    Called by FreeRTOS scheduler when started, running on core for main thread
 *
 *  @section    Purpose
 *      Unlike normal FreeRTOS tasks, or embedded C main functions, the app_main() task is allowed 
 *      to return. If this happens, The task is cleaned up and the system will continue running 
 *      with other RTOS tasks scheduled normally. Therefore, it is possible to implement app_main 
 *      as either a function that creates other application tasks and then returns, or as a main 
 *      application task itself. app_main() has a fixed RTOS priority, one higher than the minimum
 *
 *  @pre    second stage bootloader
 *  @post   no return
 */
/**************************************************************************************************/
void app_main(void) {
    
    //Locals
    int ctr = 0;                                    /* loop counter                               */

	
	//Notify
    printf("Demonstration for esp32_base v%s", baseTempl_getVersion());
	
	
    //-------------------------------------- Initialization --------------------------------------//

    //Init
    system_initialize();

   
    //--------------------------------------- Application ----------------------------------------//
	
    for(;;) {

        //------------------------------------- Update -------------------------------------------//
        
        //C Operate 
        demo_routine(ctr);
        
        //Notify
        printf("app_main(): loop %d\n\n", ctr++);

        
        //------------------------------------- Reset --------------------------------------------//

        //Catch
        if(ctr > MAX_LOOP_CT) {
            break;
        }

        //Delay
        delay_ms(SLEEP_DELAY_MS);
    }
}


//************************************************************************************************//
//                                         PRIVATE FUNCTIONS                                      //
//************************************************************************************************//

/**************************************************************************************************/
/** @fcn        char *baseTempl_getVersion(void)
 *  @brief      Retrieve base template project version
 *  @details    major.minor.rev suffixed with "*" for in development from that version
 *
 *  @return   (char *) string reporting version
 *
 *  @note   Derivative identifiers may be omitted (e.g. "*" for published content)
 */
/**************************************************************************************************/
static char *baseTempl_getVersion(void) {
    return BASE_TEMPL_VERS;
}
