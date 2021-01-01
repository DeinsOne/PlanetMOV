-- Moon
function onSetup(argv)
    return { pos = vec2(35, 0), argv }
end



function onUpdate()
    Moon = getPlanet('Moon')
    -- Earth = getPlanet('Earth')
    -- print(Earth.EarthS)

    return { Moon }
end
