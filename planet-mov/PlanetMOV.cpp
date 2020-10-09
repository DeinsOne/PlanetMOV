#include "PlanetMOV.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/Display.h"

static void __preSettingUp(ci::app::App::Settings* settings ) {
    settings->setWindowSize(glm::vec2(1060, 520) );
    settings->setFrameRate(60.0f );

}

CINDER_APP(PlanetMOV, ci::app::RendererGl(ci::app::RendererGl::Options().msaa(8 ) ), __preSettingUp )

