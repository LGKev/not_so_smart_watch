/*
 * watch_face_themes.h
 *
 *  Created on: Dec 9, 2017
 *      Author: kwat1
 */


#include "msp.h"
#include "Lcd.h"


#ifndef WATCH_FACE_THEMES_H_
#define WATCH_FACE_THEMES_H_

/* This is the most basic theme. Essentially just proves the RTC is working properly.
 * goals: be able to change background color.
 * */
void basic_watch(void);
/* only shows the time in a large font similar to this
 * */
void large_TIME(void);

void basic_Temperature();

#endif /* WATCH_FACE_THEMES_H_ */
