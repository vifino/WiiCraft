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

#include "Packet01LoginRequest.h"

#include <cstdio>
#include "../../net/DataOutputStream.h"
#include "../../net/DataInputStream.h"
#include "../../exception/ExcSocketStringTooLong.h"
#include "../../entity/Player.h"
#include "../../world/World.h"
#include "../../protocol/Chat.h"
#include "../../protocol/ServerInfo.h"
#include "../PacketManager.h"
#include "../../util/Debug.h"

using namespace std;

Packet01LoginRequest::Packet01LoginRequest() {
	PacketServer::id = 0x01;
	PacketServer::prio = 0;
}

Packet01LoginRequest::Packet01LoginRequest(int _protocolVersion,
		string _userName) {
	PacketClient::id = 0x01;
	PacketClient::prio = 50;

	this->protocolVersion = _protocolVersion;
	this->userName = _userName;
}

PacketServer *Packet01LoginRequest::getInstance() {
	return new Packet01LoginRequest();
}

bool Packet01LoginRequest::registerPacket() {
	PacketManager::registerPacket(new Packet01LoginRequest());

	return true;
}

void Packet01LoginRequest::schreibePacketInhalt(DataOutputStream *out) {
	out->schreibeInt(this->protocolVersion);
	out->schreibeString(this->userName);
	out->schreibeString("");
	out->schreibeInt(0);
	out->schreibeInt(0);
	out->schreibeByte(0);
	out->schreibeByte(0);
	out->schreibeByte(0);
}

void Packet01LoginRequest::lesePacketInhalt(DataInputStream *in) {
	this->entityId = in->leseInt();

	try {
		in->leseString(16);
	} catch (ExcSocketStringTooLong &exception) {
		throw ExcSocketStringTooLong(PacketServer::id);
	}

	try {
		this->levelType = in->leseString(16);
	} catch (ExcSocketStringTooLong &exception) {
		throw ExcSocketStringTooLong(PacketServer::id);
	}

	this->serverMode = in->leseInt();
	this->dimension = in->leseInt();
	this->difficulty = in->readByte();
	this->worldHeight = in->readByte();
	this->maxPlayers = in->readByte();
}

void Packet01LoginRequest::verarbeitePacket() {
	Player::initializePlayer(this->entityId);
	World::initializeWorld(this->dimension, this->levelType, this->difficulty,
			this->serverMode, this->worldHeight);
	ServerInfo::initializeServerInfo(this->maxPlayers);
	Chat::initializeChat();

#ifdef DEBUG_ON
	char *buffer = new char[1000];
	sprintf(buffer,
			"entityId: %i, levelType: %s, serverMode: %i, dimension: %i, difficulty: %i, worldHeight: %i, maxPlayers: %i",
			this->entityId, this->levelType.data(), this->serverMode,
			this->dimension, this->difficulty, this->worldHeight,
			this->maxPlayers);
	Debug::schreibePacketLog("Packet01LoginRequest", buffer);
	delete[] buffer;
#endif
}
