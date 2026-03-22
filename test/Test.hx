package test;

import discord.Presence;
import discord.Api;

function main() {
	trace("Initializing RPC...");
	Api.init("1484144821701578855");
	
	trace("Creating presence...");
	Api.getPresence().setState("Rewind").setActivityType(Listening).setStatusDisplayType(State).refresh();

	// sys.thread.Thread.create(() -> while (true) {
	// 	Api.refresh();
	// 	Sys.sleep(0.4);
	// });

	trace("Press any button to shutdown");

	Sys.getChar(false);
	Api.shutdown();
}