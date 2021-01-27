-- Directory to locate all binaries and intermediates 
outputDirectory = 'bin'


workspace 'PlanetMOV'
    configurations { 'Release', 'Debug' }
    libdirs {
        'bin'
    }

    project 'json'
        kind 'SharedLib'
        language 'C++'

        targetdir '%{outputDirectory}/%{cfg.buildcfg}'
        objdir '%{outputDirectory}/%{cfg.buildcfg}'

        location(outputDirectory)
        filename 'json'

        includedirs {
            'planet-mov/utils/jsoncpp/include'
        }

        files {
            'planet-mov/utils/jsoncpp/src/lib_json/*.cpp'
        }


    project 'lua'
        kind 'SharedLib'
        language 'C++'

        targetdir '%{outputDirectory}/%{cfg.buildcfg}'
        objdir '%{outputDirectory}/%{cfg.buildcfg}'

        location(outputDirectory)
        filename 'lua'

        includedirs {
            'planet-mov/utils/Lua'
        }

        files {
            'planet-mov/utils/Lua/*.c'
        }

        removefiles { 'planet-mov/utils/Lua/lua.c' }


    project 'mov'
        kind 'ConsoleApp'
        language 'C++'

        targetdir '%{outputDirectory}/%{cfg.buildcfg}'
        objdir '%{outputDirectory}/%{cfg.buildcfg}'

        location(outputDirectory)
        filename 'mov'

        includedirs {
            'planet-mov',
            'planet-mov/config',
            'planet-mov/context',
            'planet-mov/context/Controller',
            'planet-mov/context/Lua',
            'planet-mov/context/Shader',
            'planet-mov/utils/Lua',
            'planet-mov/utils/jsoncpp/include',
            'planet-mov/utils/LuaBridge/Source',
            '/home/deinsone/Cinder/include'
        }

        files {
            'planet-mov/*.cpp',
            'planet-mov/config/*.cpp',
            'planet-mov/context/*.cpp',
            'planet-mov/context/Lua/*.cpp',
            'planet-mov/context/Controller/*.cpp',
            'planet-mov/context/Shader/*.cpp'
        }

        links {
            'lua',
            'json',
            'cinder'
        }
