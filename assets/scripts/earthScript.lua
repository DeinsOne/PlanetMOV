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
    a = Earth.pos.x - 1
    Earth.pos = vec2(a, 0)

    return Earth
end


-- Function calls on frame rendering
function onRender()
end
