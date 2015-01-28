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

#ifndef GRAFIKHANDLER_H_
#define GRAFIKHANDLER_H_

#include <map>
#include <string>
#include "../thread/Thread.h"
#if defined _WIN32 || defined __CYGWIN__
#include "../util/WiiFunction.h"
#include <pthread.h>
#else /* __wii__ */
#include "../util/pthread.h"
#include <grrlib.h>
#endif /* __wii__ */
#include "../util/Debug.h"

#include "GraphicElement.h"

namespace std {

struct TexturMatrix {
	f32 s1;
	f32 s2;
	f32 t1;
	f32 t2;
};

class GraphicHandler: public Thread {
public:
#ifdef DEBUG_ON
	static int blockAnzahl;
#endif

	static void initialize();
	static GraphicHandler *getGraphicHandler();

	int exec();
	void stop();
	virtual ~GraphicHandler();
	void setzeAnzeigeElement(GraphicElement *neuesElement);
	GRRLIB_texImg *gebeBild(string name);
	TexturMatrix gebeTexturMatrix(int nr);
	void setCursorPosition(float x, float y, float angle);
	void setzeAusgewaehltesElement(GraphicElement *_ausgewaehltesElement);
	GraphicElement *gebeAusgewaehltesElement();
	void gedrueckt(u32 gedrueckt);
private:
	static GraphicHandler *grafikHandler;

	bool gestoppt;
	GraphicElement *element;
	GraphicElement *ausgewaehltesElement;
	map<string, GRRLIB_texImg *> bilder;
	TexturMatrix *texturMatrix;
	pthread_mutex_t mutexStop;
	pthread_mutex_t mutexZeichne;

	bool istGestopped();
	GraphicHandler();
	void ladeBilder();
	void ladeTexturMatrix();
};

}
#endif /* GRAFIKHANDLER_H_ */
