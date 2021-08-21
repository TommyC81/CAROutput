/////////////////////////////////////////////////////////////////
/*
	CAROutput.cpp - Arduino Library to manage digital/analog output.
	Created by Tommy Carlsson.
*/
/////////////////////////////////////////////////////////////////

#include <CAROutput.h>

/////////////////////////////////////////////////////////////////

CAROutput::CAROutput(byte p_outputPin) {
	_outputPin = p_outputPin;
	_outputState = LOW;
	_blinkState = BLINK_STATE_DISABLE;
	_highTime = 0;
	_lowTime  = 0;
	_blinkTimes  = -1;
	_elapsedMillis_sinceLastOutputChange = 0;
	pinMode(_outputPin, OUTPUT);
}

void CAROutput::high(void){
	_blinkState = BLINK_STATE_DISABLE;
	_outputState = HIGH;
	digitalWrite(_outputPin, _outputState);
}

void CAROutput::low(void){
	_blinkState = BLINK_STATE_DISABLE;
	_outputState = LOW;
	digitalWrite(_outputPin, _outputState);
}

void CAROutput::toggle(void) {
	_blinkState = BLINK_STATE_DISABLE;
	_outputState = (_outputState == LOW) ? HIGH : LOW;
	digitalWrite(_outputPin, _outputState);
}

void CAROutput::blink(unsigned int p_lowTime, unsigned int p_highTime, unsigned int p_delayTime, int p_blinkTimes) {
	_highTime = p_highTime;
	_lowTime = p_lowTime;
	_delayTime = p_delayTime;
	_blinkTimes = p_blinkTimes;
	_elapsedMillis_sinceLastOutputChange = 0;

	if(_blinkState == BLINK_STATE_DISABLE) {
		_blinkState = BLINK_STATE_DELAY;
	}
}

void CAROutput::blink(unsigned int p_lowTime, unsigned int p_highTime, unsigned int p_delayTime) {
	blink(p_lowTime, p_highTime, p_delayTime, -1);
}

void CAROutput::blink(unsigned int p_lowTime, unsigned int p_highTime) {
	blink(p_lowTime, p_highTime, 0, -1);
}

byte CAROutput::getState(void) {
	return _outputState;
}

void CAROutput::loop(void) {
	bool blinkIsDue = false;
	if(_blinkTimes == 0)
		_blinkState = BLINK_STATE_DISABLE;
	switch(_blinkState) {
		case BLINK_STATE_DISABLE:
			return;
		case BLINK_STATE_DELAY:
			if (_elapsedMillis_sinceLastOutputChange >= _delayTime) {
				blinkIsDue = true;
				_blinkState = BLINK_STATE_BLINK;
			}
			break;
		case BLINK_STATE_BLINK:
			if(_outputState == LOW && _elapsedMillis_sinceLastOutputChange >= _lowTime) {
				blinkIsDue = true;
			}
			else if(_outputState == HIGH && _elapsedMillis_sinceLastOutputChange >= _highTime) {
				blinkIsDue = true;
			}
			break;
		default:
			return;
	}
	if(blinkIsDue) {
		_outputState = (_outputState == LOW) ? HIGH : LOW;
		digitalWrite(_outputPin, _outputState);
		_elapsedMillis_sinceLastOutputChange = 0;
		if(_blinkTimes > 0)
			_blinkTimes--;
	}
}

