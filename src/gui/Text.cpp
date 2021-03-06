/* Copyright (c) 2012, Kose Alexander
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by Kose Alexander.
 * 4. Neither the name of Kose Alexander nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY KOSE ALEXANDER ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL KOSE ALEXANDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "Text.h"

#include "GraphicHandler.h"
#if defined _WIN32 || defined __CYGWIN__
#include "../util/WiiFunction.h"
#else /* __wii__ */
#include <grrlib.h>
#endif /* __wii__ */

using namespace std;

Text::Text(float _x, float _y, string _text) {
	TextElement::setzeStandardWerte();

	pthread_mutex_init(&this->mutexColor, NULL);

	this->setX(_x);
	this->setY(_y);
	this->setText(_text);
	this->berechneAusmasse();
	this->setTextColor(0xffffffff);
	this->setBackgroundColor(0);
}

Text::~Text() {
	pthread_mutex_destroy(&this->mutexColor);
}

void Text::berechneAusmasse() {
	string _text = this->getText();

	this->setHeight(_text.size() ? 8 : 0);
	this->setWidth(8.0 * (float) _text.size());
}

void Text::drawElement() {
	if (this->isVisible()) {
		string _text = this->getText();
		_text = this->konvertiereAnzeigeText(_text);
		u32 _textColor = this->getTextColor();
		u32 _backgroundColor = this->getBackgroundColor();

		float _x = this->getX();
		float _y = this->getY();

		GRRLIB_2dMode();
		if (_backgroundColor > 0) {
			float _breite = this->getWidth();
			float _hoehe = this->getHeight();
			GRRLIB_Rectangle(_x, _y, _breite, _hoehe, _backgroundColor, 1);
		}
		GRRLIB_Printf(_x, _y,
				GraphicHandler::getGraphicHandler()->getTexture("font"),
				_textColor, 1, _text.data());
	}
}

void Text::setTextColor(u32 _textColor) {
	pthread_mutex_lock(&this->mutexColor);
	this->textColor = _textColor;
	pthread_mutex_unlock(&this->mutexColor);
}

u32 Text::getTextColor() {
	pthread_mutex_lock(&this->mutexColor);
	u32 _textColor = this->textColor;
	pthread_mutex_unlock(&this->mutexColor);

	return _textColor;
}

void Text::setBackgroundColor(u32 _backgroundColor) {
	pthread_mutex_lock(&this->mutexColor);
	this->backgroundColor = _backgroundColor;
	pthread_mutex_unlock(&this->mutexColor);
}

u32 Text::getBackgroundColor() {
	pthread_mutex_lock(&this->mutexColor);
	u32 _backgroundColor = this->backgroundColor;
	pthread_mutex_unlock(&this->mutexColor);

	return _backgroundColor;
}
