/*
 * adc_driver.h
 *
 *  Created on: Oct 11, 2017
 *      Author: kk
 */

#include "msp.h"

#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_




/* @name: ADC_confog_acclerometer
 * @brief: This configures the booster pack acclerometer and ADC channels
 *  XYZ are defined globals where the values can be accessed.
 *  access memory directly either through the ISR and save value into the global or
 *  you can access the memory directly in the main loop.Recommend the first method.
 * */
void ADC_CONFIG_Accelerometer(void);





#endif /* ADC_DRIVER_H_ */
