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

#include "Block03BGetreide.h"

#include "../ItemManager.h"

using namespace std;

Item *Block03BGetreide::getInstance() {
	return new Block03BGetreide();
}

bool Block03BGetreide::registiereItem() {
	ItemManager::registriereItem(new Block03BGetreide());

	return true;
}

Block03BGetreide::Block03BGetreide() {
	this->setzeStandardWerte();

	Item::id = 0x03b;
}

void Block03BGetreide::zeichne(float x, float y, float z, byte meta) {
	// die verschieden groessen haben unterschiedliche Texturen
	if (meta == 1) {
		ItemBlock::zeichnePflanze(x, y, z, 89, 1);
	} else if (meta == 2) {
		ItemBlock::zeichnePflanze(x, y, z, 90, 1);
	} else if (meta == 3) {
		ItemBlock::zeichnePflanze(x, y, z, 91, 1);
	} else if (meta == 4) {
		ItemBlock::zeichnePflanze(x, y, z, 92, 1);
	} else if (meta == 5) {
		ItemBlock::zeichnePflanze(x, y, z, 93, 1);
	} else if (meta == 6) {
		ItemBlock::zeichnePflanze(x, y, z, 94, 1);
	} else if (meta == 7) {
		ItemBlock::zeichnePflanze(x, y, z, 95, 1);
	} else {
		ItemBlock::zeichnePflanze(x, y, z, 88, 1);
	}
}

bool Block03BGetreide::istDurchsichtig() {
	return true;
}
