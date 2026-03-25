package discord;

import haxe.Int64;

enum abstract PartyPrivacy(Int) {
	var Private = 0;
	var Public = 1;
}

enum abstract ActivityType(Int) {
	var Playing = 0;
	var Streaming = 1;
	var Listening = 2;
	var Watching = 3;
	/** Only works for bot accounts **/
	var Custom = 4;
	var Competing = 5;
}

enum abstract StatusDisplayType(Int) {
	var Name = 0;
	var State = 1;
	var Details = 2;
}

@:hlNative('discord', 'presence_')
abstract Presence(hl.Abstract<"discord_presence">) {
	public function new() {
		this = cast alloc();
	}

	private static function alloc():Presence {
		return null;
	}

	public function setState(v:String):Presence {
		return null;
	}

	public function setDetails(v:String):Presence {
		return null;
	}

	public function setStartTimestamp(v:Int64):Presence {
		return null;
	}

	public function setEndTimestamp(v:Int64):Presence {
		return null;
	}

	public function setLargeImageKey(v:String):Presence {
		return null;
	}

	public function setLargeImageText(v:String):Presence {
		return null;
	}

	public function setSmallImageKey(v:String):Presence {
		return null;
	}

	public function setSmallImageText(v:String):Presence {
		return null;
	}

	public function setPartyId(v:String):Presence {
		return null;
	}

	public function setPartySize(v:Int):Presence {
		return null;
	}

	public function setPartyMax(v:Int):Presence {
		return null;
	}

	public function setPartyPrivacy(v:PartyPrivacy):Presence {
		return null;
	}

	public function setActivityType(v:ActivityType):Presence {
		return null;
	}

	public function setStatusDisplayType(v:StatusDisplayType):Presence {
		return null;
	}

	public function setMatchSecret(v:String):Presence {
		return null;
	}

	public function setJoinSecret(v:String):Presence {
		return null;
	}

	public function setSpectateSecret(v:String):Presence {
		return null;
	}

	public function setInstance(v:Bool):Presence {
		return null;
	}

	public function refresh() {}
}