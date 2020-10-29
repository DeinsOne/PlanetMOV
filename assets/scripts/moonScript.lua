Moon = Planet(vec2(30, 5), 1.3 )

function onSetup()
    Moon = Planet(vec2(30, 5), 1.3 )
    return Moon
end



function onUpdate()
    EarthPos = getPlanet('Earth').pos

    MoonS = 9
    Moon.pos = vec2( EarthPos.x + (math.sin(elapsedTime*2) * MoonS), EarthPos.y + (math.cos(elapsedTime*2) * MoonS)  )
    return Moon
end