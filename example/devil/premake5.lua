PROJECT_NAME = path.getname(os.getcwd())

if not minko.platform.supports { "windows32", "windows64", "linux32", "linux64", "osx64", "html5" } then
	return
end

minko.project.application("minko-example-" .. PROJECT_NAME)

	removeplatforms { "ios", "android" }

	files {
		"src/**.cpp",
		"src/**.hpp",
		"asset/**"
	}

	includedirs { "src" }

	-- plugins
	minko.plugin.enable("sdl")
	minko.plugin.enable("devil")
	--minko.plugin.enable("bullet")
	--minko.plugin.enable("jpeg")
	--minko.plugin.enable("mk")
	--minko.plugin.enable("particles")
