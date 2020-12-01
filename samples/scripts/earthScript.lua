Earth = Planet(vec2(26, 0), 2.4 )


function onSetup()
    Earth = Planet(vec2(26, 0), 2.4 )
    print('\tEarth.onSetup()')
    return Earth
end


function onUpdate()
    EarthS = 26
    SunPos = getPlanet('Sun').pos 

    Earth.pos = vec2(SunPos.x - math.sin(elapsedTime/3) * EarthS, SunPos.y + math.cos(elapsedTime/3) * EarthS )

    return Earth
end
