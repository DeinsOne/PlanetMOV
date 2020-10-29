Earth = Planet(vec2(26, 0), 2.4 )


-- Function calls on script loading
function onSetup()
    Earth = Planet(vec2(26, 0), 2.4 )
    return Earth
end


-- Function calls before frame rendering
function onUpdate()
    EarthS = 26
    SunPos = getPlanet('Sun').pos
    Earth.pos = vec2(SunPos.x -math.sin(elapsedTime/3) * EarthS, SunPos.y + math.cos(elapsedTime/3) * EarthS ) 

    return Earth
end
