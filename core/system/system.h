#ifndef CORE_SYSTEM_SYSTEM_H_
#define CORE_SYSTEM_SYSTEM_H_

//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//

#define NUM_SYSTEM_STATUS_CODES     (4)


//------------------------------------------- Typedefs -------------------------------------------//

/**
 * @brief       General system status codes
 * @details     Naming generic for re-use
 */
typedef enum {
    STATUS_OK      = 0,
    STATUS_WARN    = 1,
    STATUS_ERR     = 2,
    STATUS_UNKNOWN = 3,
} status_code;


//************************************************************************************************//
//                                       FUNCTION DECLARATIONS                                    //
//************************************************************************************************//

//Public
extern status_code system_initialize(void);

//Handles
extern void demo_isr_handler(void);                 /* For ext. interrupt config to driver        */

extern void delay_ms(int t_ms);


#endif /* CORE_SYSTEM_SYSTEM_H_ */

