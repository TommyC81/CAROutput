/////////////////////////////////////////////////////////////////
/*
	CAROutput.cpp - Arduino Library to manage digital/analog output.
	Created by Tommy Carlsson.
*/
/////////////////////////////////////////////////////////////////

#pragma once

#ifndef CAROutput_h
#define CAROutput_h

/////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <elapsedMillis.h>

/////////////////////////////////////////////////////////////////

#define BLINK_STATE_DISABLE 0
#define BLINK_STATE_DELAY 1
#define BLINK_STATE_BLINK 2

/////////////////////////////////////////////////////////////////

class CAROutput
{
	private:
		byte _outputPin;
		byte _outputState;
		byte _blinkState;

		unsigned int _highTime;
		unsigned int _lowTime;
		unsigned int _delayTime;
		int _blinkTimes;
		elapsedMillis _elapsedMillis_sinceLastOutputChange;

	public:
		CAROutput(byte p_outputPin);
		void high(void);
		void low(void);
		void toggle(void);
		void blink(unsigned int p_lowTime, unsigned int p_highTime);
		void blink(unsigned int p_lowTime, unsigned int p_highTime, unsigned int p_delayTime);
		void blink(unsigned int p_lowTime, unsigned int p_highTime, unsigned int p_delayTime, int p_blinkTimes);
		byte getState(void);
		void loop(void);
};

#endif