#ifndef MCU_GPIO_H
#define MCU_GPIO_H

//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//Standard Library Includes
#include <stdbool.h>

//SDK Includes
#include "driver/gpio.h"

//Project Includes
#include "system.h"


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//

//Definitions
#define GPIO_NUM_PINS                 (3)

//GPIO Pin Number
#define GPIO_PIN_DI_0_NUM             (GPIO_NUM_4)
#define GPIO_PIN_DO_0_NUM             (GPIO_NUM_5)
#define GPIO_PIN_ISR_NUM              (GPIO_NUM_6)


//------------------------------------------- Typedefs -------------------------------------------//

//Pin ID (also for array index access)
typedef enum {
    GPIO_DI_0    = 0,                               /* Demo Input Pin for manual DC value test    */
    GPIO_DO_0    = 1,                               /* Demo Output Pin for manual DC value test   */
    GPIO_DI_ISR  = 2,                               /* Demo ISR Input Pin for interrupt test      */
} GpioPinId;


//Pin Config
typedef struct {
    GpioPinId pin_id;                               /* Identifier for application use             */
    gpio_num_t pin_num;                             /* Integer pin number using ESP-IDF API       */
    bool pin_init;                                  /* GPIO initial value for output              */
    gpio_mode_t mode;                               /* Set input/output mode                      */
    gpio_pullup_t pull_up_en;                       /* GPIO pull-up enable in use                 */
    gpio_pulldown_t pull_down_en;                   /* GPIO pull-down enable in use               */
    gpio_int_type_t intr_type;                      /* GPIO interrupt type                        */
    int intr_flags;                                 /* e.g. ESP_INTR_FLAG_DEFAULT                 */
    void (*p_intr)(void);                           /* GPIO interrupt routine                     */
} GpioPinConfig;


//Setup
typedef struct {
    GpioPinConfig pins[GPIO_NUM_PINS];
} GpioConfig;


//************************************************************************************************//
//                                       FUNCTION DECLARATIONS                                    //
//************************************************************************************************//

//-------------------------------------------- Public --------------------------------------------//

//Setup
extern status_code gpio_init(void);

//Read-Write
extern bool gpio_read(GpioPinId pin_id);
extern bool gpio_write(GpioPinId pin_id, bool val);
extern bool gpio_toggle(GpioPinId pin_id);

//Util
extern char *gpio_getVersion(void);


#endif /*  MCU_GPIO_H */

