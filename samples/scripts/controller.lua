-- Controller

function onUpdate(planets)
    planets.Earth.pos = vec2(
        planets.Sun.pos.x - (math.sin(elapsedTime/3) * planets.Earth.EarthS),
        planets.Sun.pos.y + (math.cos(elapsedTime/3) * planets.Earth.EarthS)
    )



    return planets
end
