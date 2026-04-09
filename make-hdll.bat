haxelib newrepo & haxelib state load gen.hl.hxml && haxe gen.hl.hxml && cmake --preset release && cmake --build out\build\release --config release && copy out\build\release\discord.hdll discord.hdll
