#include "extension.h"

#include <mutex>
#include <queue>
#include <string>
#include <variant>

struct EvReady        { discord::User user; };
struct EvDisconnected { int code; std::string message; };
struct EvErrored      { int code; std::string message; };
struct EvJoinGame     { std::string secret; };
struct EvSpectateGame { std::string secret; };
struct EvJoinRequest  { discord::User user; };

using Event = std::variant<
	EvReady, EvDisconnected, EvErrored,
	EvJoinGame, EvSpectateGame, EvJoinRequest
>;

static std::mutex       s_queueMutex;
static std::queue<Event> s_queue;

static void push(Event e) {
	std::lock_guard<std::mutex> lock(s_queueMutex);
	s_queue.push(std::move(e));
}

struct UserPref {
	void (*finalize)(UserPref*);
	discord::User* value;

	static void destroy(UserPref* p) {
		delete p->value;
		p->value = nullptr;
	}
};

static pref<discord::User>* make_hl_user(discord::User const& user) {
	auto* p = (UserPref*)hl_gc_alloc_finalizer(sizeof(UserPref));
	p->finalize = UserPref::destroy;
	p->value    = new discord::User(user);
	return reinterpret_cast<pref<discord::User>*>(p);
}

static HL_UserCB   s_onReady        = nullptr;
static HL_IntStrCB s_onDisconnected = nullptr;
static HL_IntStrCB s_onErrored      = nullptr;
static HL_StrCB    s_onJoinGame     = nullptr;
static HL_StrCB    s_onSpectateGame = nullptr;
static HL_UserCB   s_onJoinRequest  = nullptr;

discord::RPCManager& RpcManager_pumpEvents(discord::RPCManager* m) {
	std::queue<Event> local;
	{
		std::lock_guard<std::mutex> lock(s_queueMutex);
		std::swap(local, s_queue);
	}
	while (!local.empty()) {
		std::visit([](auto&& ev) {
			using T = std::decay_t<decltype(ev)>;
			if constexpr (std::is_same_v<T, EvReady>) {
				if (s_onReady) s_onReady(make_hl_user(ev.user));
			} else if constexpr (std::is_same_v<T, EvDisconnected>) {
				if (s_onDisconnected) s_onDisconnected(ev.code, hl_utf8_to_hlstr(ev.message.c_str()));
			} else if constexpr (std::is_same_v<T, EvErrored>) {
				if (s_onErrored) s_onErrored(ev.code, hl_utf8_to_hlstr(ev.message.c_str()));
			} else if constexpr (std::is_same_v<T, EvJoinGame>) {
				if (s_onJoinGame) s_onJoinGame(hl_utf8_to_hlstr(ev.secret.c_str()));
			} else if constexpr (std::is_same_v<T, EvSpectateGame>) {
				if (s_onSpectateGame) s_onSpectateGame(hl_utf8_to_hlstr(ev.secret.c_str()));
			} else if constexpr (std::is_same_v<T, EvJoinRequest>) {
				if (s_onJoinRequest) s_onJoinRequest(make_hl_user(ev.user));
			}
		}, local.front());
		local.pop();
	}

	return *m;
}

discord::RPCManager& RpcManager_onReady(discord::RPCManager* m, HL_UserCB cb) {
	s_onReady = cb;
	m->onReady([](discord::User const& user) { push(EvReady{ user }); });
	return *m;
}

discord::RPCManager& RpcManager_onDisconnected(discord::RPCManager* m, HL_IntStrCB cb) {
	s_onDisconnected = cb;
	m->onDisconnected([](int code, std::string_view msg) { push(EvDisconnected{ code, std::string(msg) }); });
	return *m;
}

discord::RPCManager& RpcManager_onErrored(discord::RPCManager* m, HL_IntStrCB cb) {
	s_onErrored = cb;
	m->onErrored([](int code, std::string_view msg) { push(EvErrored{ code, std::string(msg) }); });
	return *m;
}

discord::RPCManager& RpcManager_onJoinGame(discord::RPCManager* m, HL_StrCB cb) {
	s_onJoinGame = cb;
	m->onJoinGame([](std::string_view secret) { push(EvJoinGame{ std::string(secret) }); });
	return *m;
}

discord::RPCManager& RpcManager_onSpectateGame(discord::RPCManager* m, HL_StrCB cb) {
	s_onSpectateGame = cb;
	m->onSpectateGame([](std::string_view secret) { push(EvSpectateGame{ std::string(secret) }); });
	return *m;
}

discord::RPCManager& RpcManager_onJoinRequest(discord::RPCManager* m, HL_UserCB cb) {
	s_onJoinRequest = cb;
	m->onJoinRequest([](discord::User const& user) { push(EvJoinRequest{ user }); });
	return *m;
}
