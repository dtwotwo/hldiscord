#if eval
import idl.generator.Generate;
import idl.Options;

class Generator {
	private static inline final HL_INCLUDE:String = "
#ifdef _WIN32
#pragma warning(disable:4305)
#pragma warning(disable:4244)
#pragma warning(disable:4316)
#endif

#include \"extension.h\"
";

	private static final options:Options = {
		idlFile: "lib/discord.idl",
		target: null,
		packageName: "discord",
		autoGC: true,
		nativeLib: "discord",
		outputDir: "src",
	};

	public static function generateHl() {
		options.target = "hl";
		options.includeCode = HL_INCLUDE;
		Generate.generateCpp(options);
	}
}
#end
