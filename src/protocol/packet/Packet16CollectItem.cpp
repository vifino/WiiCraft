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

#include "Packet16CollectItem.h"

#include <cstdio>
#include "../../net/DataInputStream.h"
#include "../../entity/Entity.h"
#include "../PacketManager.h"
#include "../../util/Debug.h"

using namespace std;

Packet16CollectItem::Packet16CollectItem() {
	PacketServer::id = 0x16;
	PacketServer::prio = 50;
}

PacketServer *Packet16CollectItem::getInstance() {
	return new Packet16CollectItem();
}

bool Packet16CollectItem::registerPacket() {
	PacketManager::registerPacket(new Packet16CollectItem());

	return true;
}

void Packet16CollectItem::lesePacketInhalt(DataInputStream *in) {
	this->collectedEntityId = in->leseInt();
	this->collectorEntityId = in->leseInt();
}

void Packet16CollectItem::verarbeitePacket() {
#ifdef DEBUG_ON
	char *buffer = new char[100];
	sprintf(buffer, "collectedEntityId: %i, collectorEntityId: %i",
			this->collectedEntityId, this->collectorEntityId);
	Debug::schreibePacketLog("Packet16CollectItem", buffer);
	delete[] buffer;
#endif

	Entity::getEntity(this->collectedEntityId);
	Entity::getEntity(this->collectorEntityId);
	// TODO Packetverarbeitung implementieren
}
