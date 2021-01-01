-- Earth
function onSetup(argv)
    return {
        pos = vec2(argv.EarthS, 0),
        size = 2.4,
        argv
    }
end



function onUpdate()
    SunPos = vec2(0,0)
    Earth = getPlanet('Earth')

    Earth.pos = vec2(
        SunPos.x - (math.sin(elapsedTime/3) * Earth.EarthS * Earth.velocity),
        SunPos.y + (math.cos(elapsedTime/3) * Earth.EarthS * Earth.velocity)
    )

    return Earth
end
