Earth = Planet(vec2(26, 0), 2.4 )

function onSetup()
    Earth = Planet(vec2(26, 0), 2.4 )
    return Earth
end



function onUpdate()
    SunPos = getPlanet('Sun').pos

    EarthS = 26
    Earth.pos = vec2(SunPos.x - math.sin(elapsedTime/3) * EarthS, SunPos.y + math.cos(elapsedTime/3) * EarthS )
    return Earth
end
