#ifndef KEYEVENT_HPP
#define KEYEVENT_HPP

#include <SDL/SDL.h>
#include <stdint.h>

class KeyEvent
{
	public:
		uint16_t getUnicode();
		SDLKey getKey();
		
		KeyEvent(uint16_t unicode,SDLKey key);
		
	private:
		uint16_t m_unicode;
		SDLKey m_key;
		
};

#endif // KEYEVENT_HPP
