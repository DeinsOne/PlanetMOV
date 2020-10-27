Earth = Planet(vec2(26, 0), 2.4 )


-- Function calls on script loading
function onSetup()
    return Earth
end


-- Function calls before frame rendering
function onUpdate()
    s = 26
    Earth.pos = vec2(-math.sin(elapsedTime/3) * s, math.cos(elapsedTime/3) * s )

    return Earth
end
