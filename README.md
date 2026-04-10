# hldiscord

Haxe/HashLink bindings for [discord-presence](https://github.com/EclipseMenu/discord-presence) - a C++ Discord Rich Presence library.

## Features

- Rich presence (state, details, large/small image keys, timestamps)
- Buttons (up to 2)
- Parties
- Activity types (`Game`, `Streaming`, `Listening`, `Watching`, `Custom`, `Competing`)
- Status display types (`Name`, `State`, `Details`)

## Requirements

- [CMake](https://cmake.org/) + [Ninja](https://ninja-build.org/)
- Haxe + HashLink
- [hl-idl](https://github.com/onehundredfeet/hl-idl.git) - `haxelib git hl-idl https://github.com/onehundredfeet/hl-idl.git`
- [hvector](https://github.com/onehundredfeet/hvector.git) - `haxelib git hvector https://github.com/onehundredfeet/hvector.git`

## Installation

```bash
haxelib git hldiscord https://github.com/gimmesoda/hldiscord.git
```

## Building the native library

```bat
make-hdll
```

This will produce `discord.hdll` in the root folder. Place it next to your compiled HashLink binary.

## Usage

> [!WARNING]
> `pumpEvents()` must be called from the **main thread**

```haxe
function main() {
  discord.Api.Init.init(ready);
}

function ready() {
	trace("ready");

	final man = discord.Api.RpcManager.get();

	man
		.setClientId("YOUR_CLIENT_ID")
		.initialize()
		.getPresence()
		.setLargeImageKey("main_icon")
		.setState("Rewind")
		.setActivityType(Listening)
		.setStatusDisplayType(State)
		.refresh();

	while (true) {
		man.pumpEvents();
		Sys.sleep(0.4);
	}
}
```
