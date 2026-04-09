#pragma once

#include <cstdio>
#include <string>

#include <discord-rpc.hpp>

// hl-idl generates valueToIndex1(int), but discord uses enum class which
// doesn't implicitly convert to int — these wrappers bridge that gap.
inline int Presence_getPartyPrivacy(discord::Presence* p) {
	return (int)p->getPartyPrivacy();
}
inline int Presence_getActivityType(discord::Presence* p) {
	return (int)p->getActivityType();
}
inline int Presence_getStatusDisplayType(discord::Presence* p) {
	return (int)p->getStatusDisplayType();
}

// setButton1/2(Button) overloads: hl-idl passes Button* but discord expects Button const&
inline discord::Presence& Presence_setButton1(discord::Presence* p, discord::Presence::Button* b) {
	return p->setButton1(*b);
}
inline discord::Presence& Presence_setButton2(discord::Presence* p, discord::Presence::Button* b) {
	return p->setButton2(*b);
}

// setPresence: hl-idl passes Presence* but discord expects Presence const&
inline discord::RPCManager& RpcManager_setPresence(discord::RPCManager* m, discord::Presence* p) {
	return m->setPresence(*p);
}
