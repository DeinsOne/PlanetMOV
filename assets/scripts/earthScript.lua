-- Script for Earth planet in PlanetMOV
Earth = Planet(vec2(26, 0), 2.4 )


-- Function calls on script loading
function onSetup()
    Earth = Planet(vec2(26, 0), 2.4 )
    Earth:printFields()

    return Earth
end


-- Function calls before frame rendering
function onUpdate()
    s = 26
    Earth.pos = vec2(-math.sin(elapsedTime/3) * s, math.cos(elapsedTime/3) * s )

    return Earth
end


-- Function calls on frame rendering
function onRender()
end
