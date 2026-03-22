#define HL_NAME(n) discord_##n
#include <hl.h>

#include <discord-rpc.hpp>

HL_PRIM void HL_NAME(init)(vstring* app_id) {
	discord::RPCManager::get().setClientID(hl_to_utf8(app_id->bytes));
	discord::RPCManager::get().initialize();
}
DEFINE_PRIM(_VOID, init, _STRING);

HL_PRIM void HL_NAME(shutdown)() {
	discord::RPCManager::get().shutdown();
}
DEFINE_PRIM(_VOID, shutdown, _NO_ARG);

HL_PRIM void HL_NAME(refresh)() {
	discord::RPCManager::get().refresh();
}
DEFINE_PRIM(_VOID, refresh, _NO_ARG);

HL_PRIM void HL_NAME(set_presence)(discord::Presence* presence) {
	discord::RPCManager::get().setPresence(*presence);
}
DEFINE_PRIM(_VOID, set_presence, _ABSTRACT(discord::Presence*));

HL_PRIM void HL_NAME(clear_presence)() {
	discord::RPCManager::get().clearPresence();
}
DEFINE_PRIM(_VOID, clear_presence, _NO_ARG);

HL_PRIM discord::Presence* HL_NAME(get_presence)() {
	return &discord::RPCManager::get().getPresence();
}
DEFINE_PRIM(_ABSTRACT(discord::Presence*), get_presence, _NO_ARG);

HL_PRIM discord::Presence* HL_NAME(presence_alloc)() {
	return (discord::Presence*)hl_gc_alloc_raw(sizeof(discord::Presence));
}
DEFINE_PRIM(_ABSTRACT(discord::Presence*), presence_alloc, _NO_ARG);

#define MAKE_STRING_SET(name, member) \
HL_PRIM discord::Presence* HL_NAME(presence_set_##name)(discord::Presence* presence, vstring* v) { \
	presence->set##member(hl_to_utf8(v->bytes)); \
	return presence; \
} \
DEFINE_PRIM(_ABSTRACT(discord::Presence*), presence_set_##name, _ABSTRACT(discord::Presence*) _STRING);

#define MAKE_INT64_SET(name, member) \
HL_PRIM discord::Presence* HL_NAME(presence_set_##name)(discord::Presence* presence, int64_t v) { \
	presence->set##member(v); \
	return presence; \
} \
DEFINE_PRIM(_ABSTRACT(discord::Presence*), presence_set_##name, _ABSTRACT(discord::Presence*) _I64);

#define MAKE_INT32_SET(name, member) \
HL_PRIM discord::Presence* HL_NAME(presence_set_##name)(discord::Presence* presence, int v) { \
	presence->set##member(v); \
	return presence; \
} \
DEFINE_PRIM(_ABSTRACT(discord::Presence*), presence_set_##name, _ABSTRACT(discord::Presence*) _I32);

MAKE_STRING_SET(state, State)
MAKE_STRING_SET(details, Details)
MAKE_INT64_SET(start_timestamp, StartTimestamp)
MAKE_INT64_SET(end_timestamp, EndTimestamp)
MAKE_STRING_SET(large_image_key, LargeImageKey)
MAKE_STRING_SET(large_image_text, LargeImageText)
MAKE_STRING_SET(small_image_key, SmallImageKey)
MAKE_STRING_SET(small_image_text, SmallImageText)
MAKE_STRING_SET(party_id, PartyID)
MAKE_INT32_SET(party_size, PartySize)
MAKE_INT32_SET(party_max, PartyMax)

HL_PRIM discord::Presence* HL_NAME(presence_set_party_privacy)(discord::Presence* presence, int v) {
	presence->setPartyPrivacy((discord::PartyPrivacy)v);
	return presence;
}
DEFINE_PRIM(_ABSTRACT(discord::Presence*), presence_set_party_privacy, _ABSTRACT(discord::Presence*) _I32);

HL_PRIM discord::Presence* HL_NAME(presence_set_activity_type)(discord::Presence* presence, int v) {
	presence->setActivityType((discord::ActivityType)v);
	return presence;
}
DEFINE_PRIM(_ABSTRACT(discord::Presence*), presence_set_activity_type, _ABSTRACT(discord::Presence*) _I32);

HL_PRIM discord::Presence* HL_NAME(presence_set_status_display_type)(discord::Presence* presence, int v) {
	presence->setStatusDisplayType((discord::StatusDisplayType)v);
	return presence;
}
DEFINE_PRIM(_ABSTRACT(discord::Presence*), presence_set_status_display_type, _ABSTRACT(discord::Presence*) _I32);

MAKE_STRING_SET(match_secret, MatchSecret)
MAKE_STRING_SET(join_secret, JoinSecret)
MAKE_STRING_SET(spectate_secret, SpectateSecret)

HL_PRIM discord::Presence* HL_NAME(presence_set_instance)(discord::Presence* presence, bool v) {
	presence->setInstance(v);
	return presence;
}
DEFINE_PRIM(_ABSTRACT(discord::Presence*), presence_set_instance, _ABSTRACT(discord::Presence*) _BOOL);

HL_PRIM void HL_NAME(presence_refresh)(discord::Presence* presence) {
	presence->refresh();
}
DEFINE_PRIM(_VOID, presence_refresh, _ABSTRACT(discord::Presence*));