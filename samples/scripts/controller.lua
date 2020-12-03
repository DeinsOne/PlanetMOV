function onUpdate()
    planets = getPlanets()

    for key, value in pairs(planets ) do
        if key == 'Earth' then
            EarthS = 26
            SunPos = getPlanet('Sun').pos
            planets.Earth.pos = vec2(SunPos.x - math.sin(elapsedTime/3) * EarthS, SunPos.y + math.cos(elapsedTime/3) * EarthS )
        elseif key == 'Moon' then
            MooS = 9
            EarthPos = getPlanet('Earth').pos
            planets.Moon.pos = vec2(EarthPos.x - math.sin(elapsedTime*2) * MooS, EarthPos.y + math.cos(elapsedTime*2) * MooS )
        end
    end

    return planets
end
