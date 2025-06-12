/**************************************************************************************************/
/** @file       esp32_gpio.c
 *  @brief      ESP32 GPIO Driver following drivers.c/h model
 *  @details    See driver project for demo, validation & version history
 *
 *  @author     Justin Reina, Firmware Engineer
 *  @created    6/12/25
 *  @last rev   6/12/25
 *
 *  @section    Opens
 *		Wake
 *		Demo
 *		Publish
 *      
 *  @section    Legal Disclaimer
 *      ©2025 Justin Reina. All rights reserved. All contents of this source file and/or any other
 *      related source files are the explicit property of Justin Reina. Do not distribute.
 *      Do not copy.
 */
/**************************************************************************************************/

//************************************************************************************************//
//                                        COMPILER DIRECTIVES                                     //
//************************************************************************************************//

#pragma GCC diagnostic ignored "-Wunused-function"


//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//Standard Library Includes
#include <stdio.h>
#include <string.h>
#include <limits.h>

//Project Includes
#include "esp32_gpio.h"


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//

//Driver Version
#define GPIO_DRIVER_VERS        "0.3"


//-------------------------------------------- Macros --------------------------------------------//


//----------------------------------------- Enumerations -----------------------------------------//


//------------------------------------------- Typedefs -------------------------------------------//


//************************************************************************************************//
//                                       FUNCTION DECLARATIONS                                    //
//************************************************************************************************//

//Pin Initialization
static status_code gpio_pin_init(GpioPinConfig *pinCfg);

//Helpers
static uint32_t gpio_getPinMask(uint32_t pin_num);


//************************************************************************************************//
//                                            VARIABLES                                           //
//************************************************************************************************//

//Driver Config
static GpioConfig gpioCfg =  {

    //Pins
    .pins[GPIO_DI_0] = {
                        .pin_id       = GPIO_DI_0,
                        .pin_num      = GPIO_PIN_DI_0_NUM,
                        .mode         = GPIO_MODE_INPUT,            /* Input pin                  */
                        .pull_up_en   = GPIO_PULLUP_DISABLE,
                        .pull_down_en = GPIO_PULLDOWN_DISABLE,
                        .intr_type    = GPIO_INTR_DISABLE,
                       },
    .pins[GPIO_DO_0] = {
                        .pin_id       = GPIO_DO_0,
                        .pin_num      = GPIO_PIN_DO_0_NUM,
                        .pin_init     = false,
                        .mode         = GPIO_MODE_INPUT_OUTPUT ,    /* Output pin                 */
                        .pull_up_en   = GPIO_PULLUP_DISABLE,
                        .pull_down_en = GPIO_PULLDOWN_DISABLE,
                        .intr_type    = GPIO_INTR_DISABLE,
                       },
    .pins[GPIO_DI_ISR] =  {
                        .pin_id       = GPIO_DI_ISR,
                        .pin_num      = GPIO_PIN_ISR_NUM,
                        .mode         = GPIO_MODE_INPUT,            /* Input pin                  */
                        .pull_up_en   = GPIO_PULLUP_ENABLE,
                        .pull_down_en = GPIO_PULLDOWN_DISABLE,
                        .intr_type    = GPIO_INTR_POSEDGE,          /* Enable interrupt           */
                       }
};


//************************************************************************************************//
//                                       FUNCTION DECLARATIONS                                    //
//************************************************************************************************//


//************************************************************************************************//
//                                          PUBLIC FUNCTIONS                                      //
//************************************************************************************************//

/**************************************************************************************************/
/** @fcn        void gpio_init(void)
 *  @brief      Initialize GPIO driver & peripheral for use
 *  @details    x
 *
 *	@return (status_code) status of GPIO initialization for use
 *
 *  @pre    system_initialize()
 *  @post   GPIO driver is initialized for use
 *
 *  @section    Opens
 *      Define & implement routine
 *      Consider reporting status on post console/log report
 *		...
 *		Return value from status on pin inits
 */
/**************************************************************************************************/
status_code gpio_init(void) {

    //---------------------------------------- Initialize ----------------------------------------//

    //Init GPIO
    for(int i=0; (i<GPIO_NUM_PINS); i++) { 

        //Init Pin
        gpio_pin_init(&gpioCfg.pins[i]);        
    }


    //Notify
    printf("gpio_init(): GPIO Driver initialization complete\n");

    return STATUS_OK;
}


/**************************************************************************************************/
/** @fcn        void gpio_enable(void)
 *  @brief      Enable Peripheral for use
 *  @details    x
 *
 *  @pre    gpio_init()
 *  @post   peripheral is enabled for use & output is enabled
 *  
 *  @section    Opens
 *      Define & implement routine
 */
/**************************************************************************************************/
void gpio_enable(void) {

    //Notify
    printf("gpio_enable(): Driver was enabled\n");

    return;
}


/**************************************************************************************************/
/** @fcn        void gpio_disable(void)
 *  @brief      Disable peripheral from use
 *  @details    x
 *
 *  @pre    gpio_init()
 *  @post   peripheral is disabled from use & output is disabled
 *  
 *  @section    Opens
 *      Define & implement routine
 */
/**************************************************************************************************/
 void gpio_disable(void) {
    
    //Notify
    printf("gpio_enable(): Driver was disabled\n");

    return;
}


/**************************************************************************************************/
/** @fcn        void gpio_start(void)
 *  @brief      Begin driver operations
 *  @details    x
 *
 *  @pre    gpio_init()
 *  @post   Peripheral is operational & running
 *  
 *  @section    Opens
 *      Define & implement routine
 */
/**************************************************************************************************/
void gpio_start(void) {

    return;
}


/**************************************************************************************************/
/** @fcn        void gpio_stop(void)
 *  @brief      Stop driver operations
 *  @details    x
 *
 *  @pre    gpio_init()
 *  @post   Peripheral is stopped from operation
 *  
 *  @section    Opens
 *      Define & implement routine
 */
/**************************************************************************************************/
void gpio_stop(void) {
    
    return;
}


/**************************************************************************************************/
/** @fcn        void *gpio_status(void)
 *  @brief      Current status of API performance
 *  @details    x
 *
 *  @return   (void *) driver status for driver api
 *
 *  @pre    any
 *  @post   x
 *  
 *  @section    Opens
 *      Define & implement state & routine
 */
/**************************************************************************************************/
void *gpio_status(void) {
    
    return NULL;
}


/**************************************************************************************************/
/** @fcn        void gpio_reset(void)
 *  @brief      Reset peripheral state & operations
 *  @details    x
 *
 *  @pre    gpio_init()
 *  @post   Peripheral is reset to its initial state condition
 *  
 *  @section    Opens
 *      Define & implement state & routine
 */
/**************************************************************************************************/
void gpio_reset(void) {
    
    return;
}
 
 
/**************************************************************************************************/
/** @fcn        void gpio_setConfig(GpioConfig *cfg)
 *  @brief      Update configuration value
 *  @details    x
 *
 *  @param    [in]  (GpioConfig *) cfg - Driver configuration to apply
 *
 *  @pre    gpio_init()
 *  @post   config value is applied to the peripheral
 *  
 *  @section    Opens
 *      Define & implement state & routine
 */
/**************************************************************************************************/
void gpio_setConfig(GpioConfig *cfg) {

    //Copy value
    memcpy(cfg, &gpioCfg, sizeof(GpioConfig));
    
    //Apply to peripheral

    return;
}
 
 
/**************************************************************************************************/
/** @fcn        GpioConfig *gpio_getConfig(void)
 *  @brief      Applied configuration for use
 *  @details    x
 *
 *  @return   (GpioConfig *) driver configuration access handle
 *
 *  @pre    any
 *  @post   x
 */
/**************************************************************************************************/
GpioConfig *gpio_getConfig(void) {

    return &gpioCfg;
}


/**************************************************************************************************/
/** @fcn        void *gpio_getInfo(void)
 *  @brief      Retrieve peripheral information
 *  @details    e.g. identifiers & specs
 *
 *  @return   (void *) driver info access handle
 *
 *  @pre    any
 *  @post   x
 *
 *  @section    Opens
 *      Define & implement state & routine
 */
/**************************************************************************************************/
void *gpio_getInfo(void) {

    return NULL;
}


/**************************************************************************************************/
/** @fcn        int gpio_getState(void)
 *  @brief      Retrieve current operational state
 *  @details    e.g. output values
 *
 *  @return   (int) current driver value
 *
 *  @pre    any
 *  post    x
 *
 *  @section    Opens
 *      Define & implement state & routine
 */
/**************************************************************************************************/
int gpio_getState(void) {

    return 0;
}


/**************************************************************************************************/
/** @fcn        void gpio_setState(int val)
 *  @brief      Update operational state with new value
 *  @details    e.g. output values or peripheral config
 *
 *  @param    [in]  (int) val - update driver value to set
 *
 *  @pre    gpio_init()
 *  @post   state value update is applied to the peripheral
 *
 *  @section    Opens
 *      Define & implement state & routine
 */
/**************************************************************************************************/
 void gpio_setState(int val) {
    
    return;
}


/**************************************************************************************************/
/** @fcn        bool gpio_read(GpioPinId pin_id)
 *  @brief      Read GPIO pin value
 *  @details    read input (GPIO_MODE_INPUT) or output (GPIO_MODE_INPUT_OUTPUT) pin value
 *
 *  @param    [in]  (GpioPinId) pin_id - GPIO pin number
 * 
 *  @return   (bool) current pin value
 *
 *  @pre    gpio_init() & pin_id is configured for INPUT
 *  @post   x
 * 
 *  @section    Pin Operations
 *      when the pad is not configured for input or 'input+output', the returned value is always 0
 */ 
/**************************************************************************************************/
bool gpio_read(GpioPinId pin_id) {

    //Locals
    int pin_num = gpioCfg.pins[pin_id].pin_num;
    int pin_val = INT_MAX;

    //Read 
    pin_val = gpio_get_level(pin_num);
    
    return (pin_val != 0);
}


/**************************************************************************************************/
/** @fcn        bool gpio_write(GpioPinId pin_id, bool val)
 *  @brief      set GPIO pin output value
 *  @details    x
 *
 *  @param    [in]  (GpioPinId) pin_id - GPIO pin number
 *  @param    [in]  (bool) val - new pin output value to apply
 * 
 *  @return  (bool) new pin output value
 *
 *  @pre    gpio_init() & pin_id is configured for OUTPUT
 *  @post   written value is applied to the GPIO peripheral
 *
 *  @section    Opens
 *      Safety (check if write access enabled & pin configured before op)
 */
/**************************************************************************************************/
bool gpio_write(GpioPinId pin_id, bool val) {

    //Locals
    int pin_num = gpioCfg.pins[pin_id].pin_num;             /* e.g. '21' for GPIO_PIN_21          */
    int pin_val = (val == true) ? 1:0;                      /* api uses integers                  */

    //Update
    gpio_set_level(pin_num, pin_val);

    //Check
    return gpio_read(GPIO_DO_0);
}


/**************************************************************************************************/
/** @fcn        void gpio_toggle(GpioPinId pin_id)
 *  @brief      toggle GPIO pin output value
 *  @details    x
 *
 *  @param    [in]  (GpioPinId) pin_id - GPIO pin number
 * 
 *  @return  (bool) new pin output value
 *
 *  @pre    gpio_init() & pin_id is configured for OUTPUT
 *  @post   pin value is toggled
 *
 *  @section    Opens
 *      Safety (check if write access enabled & pin configured before op)
 */
/**************************************************************************************************/
bool gpio_toggle(GpioPinId pin_id) {

    //Locals
    bool pin_val = false;                                   /* monitored pin value                */

    //Read
    pin_val = gpio_read(GPIO_DO_0);

    //Update
    gpio_write(GPIO_DO_0, !pin_val);

    //Check
    pin_val = gpio_read(GPIO_DO_0);

    return pin_val;
}


/**************************************************************************************************/
/** @fcn        void *gpio_getLog(void)
 *  @brief      Retrieve log history for Driver operations
 *  @details    x
 *
 *  @return   (void *) log file access handle
 *  
 *  @pre    gpio_init()
 *
 *  @section    Opens
 *      Define & implement state & routine
 */
/**************************************************************************************************/
void *gpio_getLog(void) {

    return NULL;
}


/**************************************************************************************************/
/** @fcn        static void gpio_isr_handler(void* arg)
 *  @brief      Default peripheral interrupt callback
 *  @details    x
 *
 *  @param    [in]  (void *) arg - isr config handle
 * 
 *  @section    Purpose
 *      Default interrupt handler for secure driver use
 *
 *  @pre    gpio_init()
 *  @post   interrupt vector is reset
 *
 *  @section    Opens
 *      Consider IRAM ('IRAM_ATTR') loc for faster callback
 *      Debounce!!
 *      Pin specific interrupt responses
 */
/**************************************************************************************************/
static void gpio_isr_handler(void* arg) {

    //Record
    demo_isr_handler();

    return;
}


/**************************************************************************************************/
/** @fcn        char *gpio_getVersion(void)
 *  @brief      Retrieve published driver version
 *  @details    major.minor.rev suffixed with "*" for in development from that version
 *
 *  @return   (char *) string reporting driver version
 *
 *  @note 	Derivative identifiers may be omitted (e.g. "*" for published content)
 */
/**************************************************************************************************/
char *gpio_getVersion(void) {
    return GPIO_DRIVER_VERS;
}


//************************************************************************************************//
//                                         PRIVATE FUNCTIONS                                      //
//************************************************************************************************//

/**************************************************************************************************/
/** @fcn        static status_code gpio_pin_init(GpioPinConfig *pinCfg)
 *  @brief      x
 *  @details    x
 *
 *  @pre    gpio_init()
 *  @post   Pin selected is prepared for configured use
 *
 *  @rec    Specify output pin pin_init values 
 *
 *  @section    Opens
 *      Pin-specific isr response handles direct
 *      gpio_install_isr_service() for multiple pins
 */
/**************************************************************************************************/
static status_code gpio_pin_init(GpioPinConfig *pinCfg) {

    //Locals    
    gpio_config_t io_conf = {
                             .pin_bit_mask = (1<<pinCfg->pin_num),
                             .mode         = pinCfg->mode,
                             .pull_up_en   = pinCfg->pull_up_en,
                             .pull_down_en = pinCfg->pull_down_en,
                             .intr_type    = pinCfg->intr_type
                           };
    
    //Reset
    gpio_reset_pin(pinCfg->pin_num);                /* set to the known initial state   */
    
    //Configure
    gpio_config(&io_conf);


    //------------------------------------ Interrupt Support -------------------------------------//

	//Interrupt Setup
	if(pinCfg->intr_type != GPIO_INTR_DISABLE) {

	    //Change gpio interrupt type for pin
	    gpio_set_intr_type(pinCfg->pin_num, pinCfg->intr_type);

	    //Install gpio isr service
	    gpio_install_isr_service(pinCfg->intr_flags);

	    //Hook isr handler for specific gpio pin
	    gpio_isr_handler_add(pinCfg->pin_num, gpio_isr_handler, (void*) pinCfg->pin_num);
	}      


    //-------------------------------------- Output Config ---------------------------------------//
	
	//Output Setup
	if((pinCfg->mode == GPIO_MODE_OUTPUT)          | (pinCfg->mode == GPIO_MODE_OUTPUT_OD) |
	   (pinCfg->mode == GPIO_MODE_INPUT_OUTPUT_OD) | (pinCfg->mode == GPIO_MODE_INPUT_OUTPUT)) {

	    //Apply Output Value
	    gpio_write(pinCfg->pin_id, pinCfg->pin_init);
	}


    //Post
    printf("\n");

    return STATUS_OK;
}


//************************************************************************************************//
//                                         PRIVATE UTILITIES                                      //
//************************************************************************************************//

/**************************************************************************************************/
/** @fcn        static uint32_t gpio_getPinMask(uint32_t pin_num)
 *  @brief      Pin Mask for SDK use
 *  @details    x
 *
 *  @param    [in]  (uint32_t) pin_num - Pin Number for mask
 *
 *  @return   (uint32_t) pin mask value
 */
/**************************************************************************************************/
static uint32_t gpio_getPinMask(uint32_t pin_num) {

    return (1ULL<<pin_num);
}

