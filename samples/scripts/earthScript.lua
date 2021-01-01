-- Earth
function onSetup(argv)
    return { pos = vec2(argv.EarthS, 0), size = 2.4, argv }
end



function onUpdate(planets)
    Earth = getPlanet('Earth')

    pos = vec2(
        planets.Sun.pos.x - (math.sin(elapsedTime/3) * Earth.EarthS),
        planets.Sun.pos.y + (math.cos(elapsedTime/3) * Earth.EarthS)
    )

    return { pos = pos }
end
