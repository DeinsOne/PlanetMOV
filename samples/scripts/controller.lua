function onUpdate()
    planets = getPlanets()

    for key, value in pairs(planets ) do
        value:onSetup()
    end

    return planets
end
