package discord;

@:hlNative('discord')
class Api {
	public static function init(appId:String) {}

	public static function shutdown() {}

	public static function refresh() {}

	public static function setPresence(presence:Presence) {}

	public static function clearPresence() {}

	public static function getPresence():Presence {
		return null;
	}
}