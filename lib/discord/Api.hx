package discord;

private typedef Native = haxe.macro.MacroType<[
	idl.Module.build({
		idlFile: "discord.idl",
		target: #if hl "hl" #elseif js "js" #end,
		packageName: "discord",
		autoGC: true,
		nativeLib: "discord",
	})
]>;
