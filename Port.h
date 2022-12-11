 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Ragab
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

#include "Common_Macros.h"
#include "Std_Types.h"

/* Id for the company in the AUTOSAR
 * for example Mohamed Tarek's ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* Dio Module Id */
#define PORT_MODULE_ID    (120U)

/* Dio Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Dio Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif
   
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"
   
/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
  /* Service ID for Port Init */
#define PORT_INIT_SID				        (uint8)0x00

/* Service ID for Port Set Pin Direction */
#define PORT_SET_PIN_DIR_SID				(uint8)0x01

/* Service ID for Port Refresh Port Direction */
#define PORT_REFRESH_PORT_DIR_SID			(uint8)0x02

/* Service ID for Port GetVersionInfo */
#define PORT_GET_VERSION_INFO_SID			(uint8)0x03

/* Service ID for Port Set Pin Mode */
#define PORT_SET_PIN_MODE_SID				(uint8)0x04 
/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/   
   
/* Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN                                 (uint8)0x0A  

/* Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE 		         (uint8)0x0B

/* API Port_Init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG				 (uint8)0x0C

/* API Port_SetPinMode service called when Port Pin Mode passed not valid */
#define PORT_E_PARAM_INVALID_MODE 			(uint8)0x0D

/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE 			(uint8)0x0E

/* API service called without module initialization */
#define PORT_E_UNINIT 					(uint8)0x0F

/* APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER 				(uint8)0x10
   
   
   
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
/* Description: Data type for the symbolic name of a port pin. */
typedef uint8 Port_PinType;
/* Description: Enum to hold PIN direction */
typedef enum
{
    INPUT,OUTPUT
}Port_PinDirectionType;

/* Description: Different port pin modes. */
typedef uint8 Port_PinModeType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;
/* Description: Port Pin Level value from Port pin list */
typedef enum
{
    PORT_PIN_LEVEL_LOW, PORT_PIN_LEVEL_HIGH
}Port_PinLevelValue;



/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
        3. the pin mode (ex: GPIO MODE)
 *      4. the direction of pin --> INPUT or OUTPUT
 *      5. the internal resistor --> Disable, Pull up or Pull down
        6. initial level value --> Ligh or Low
        7. mode is changable or not
        8. direction is changable of not
 */
typedef struct 
{
    uint8 port_num; 
    uint8 pin_num; 
    Port_PinModeType pin_mode;
    Port_PinDirectionType direction;
    Port_InternalResistor resistor;
    Port_PinLevelValue initial_value;
    uint8 changeable_mode;
    uint8 changeable_direction;
}Port_PinConfigType;


typedef struct Port_ConfigType
{
	Port_PinConfigType Pin[PORT_CONFIGURED_PINS];
} Port_ConfigType;
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant 
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
************************************************************************************/
void Port_Init(const Port_ConfigType *ConfigPtr );

/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: Reentrant 
* Parameters (in): Pin - Port Pin ID number , Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction.
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction);
#endif
/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant 
* Parameters (in): None 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection(void);

/* Function for DIO Get Version Info API */
#if (PORT_VERSION_INFO_API == STD_ON)
/************************************************************************************
* Service Name: Port_GetVersionInfo 
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant 
* Parameters (in): None 
* Parameters (inout): None
* Parameters (out): None
* Return value: versioninfo - Pointer to where to store the version information of this module. 
* Description: Returns the version information of this module.
************************************************************************************/
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: Reentrant 
* Parameters (in): Pin - Port Pin ID number , Mode - New Port Pin mode to be set on port pin 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode);
#endif
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Dio and other modules */
extern const Port_ConfigType Port_Configuration;


#endif /* PORT_H */
