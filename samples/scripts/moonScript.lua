-- Moon
function onSetup(argv)
    return { pos = vec2(35, 0), size = 1.3, argv }
end



function onUpdate(planets)
    Moon = planets.Moon

    pos = vec2(
        planets.Earth.pos.x - (math.sin(elapsedTime/3) * Moon.MoonS),
        planets.Earth.pos.y + (math.cos(elapsedTime/3) * Moon.MoonS)
    )

    return { pos = pos }
end
