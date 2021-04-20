#pragma once

#include "json.h"

#include "basic.h"
#include "components2d.h"
#include "fluids2d.h"
#include "fluidlib2d.h"

namespace fio {
inline fluid::Point deserializePoint(const nlohmann::json &j) {
    fluid::Real value;
    j.at("value").get_to(value);

    bool isInArea;
    j.at("isInArea").get_to(isInArea);

    fluid::Point temp;
    temp.value = value;
    temp.isInArea = isInArea;
    return temp; // TODO: may be it is more reasonable to add an appropriate constructor to Point?
}

inline fluid::SField2D deserializeSField2D(const nlohmann::json &j) {
    // TODO: SField does not have constructor from points array
    // ...and honestly I don't get why there is no way to create non-const SField2D

    fluid::SField2D sField2D; // TODO: set values;
    return sField2D;
}

inline fluid::VField2D deserializeVField2D(const nlohmann::json &j) {
    fluid::SField2D componentX = deserializeSField2D(j.at("componentX"));
    fluid::SField2D componentY = deserializeSField2D(j.at("componentY"));
    // TODO: same

    fluid::VField2D vField2D;
    vField2D.x() = componentX;
    vField2D.y() = componentY; // is it a proper way to do it?
    return vField2D;
}

inline fluid::WallBorder2D deserializeWallBorder2D(const nlohmann::json &j) {
    fluid::WallBorder2D wallBorder2D;
    // TODO: fix, add constructor to WallBorder2D from VField2D
    wallBorder2D.wall2D = deserializeVField2D(j.at("wall2D"));
    return wallBorder2D; // TODO: inline it after fix
}

inline fluid::CavityBorder2D deserializeCavityBorder2D(const nlohmann::json &j) {
    fluid::CavityBorder2D cavityBorder2D;
    cavityBorder2D.border2D = deserializeVField2D(j.at("border2D"));
    cavityBorder2D.pressure2D = deserializeSField2D(j.at("pressure2D"));
    return cavityBorder2D; // TODO: same
}

inline fluid::GravityBorder2D deserializeGravityBorder2D(const nlohmann::json &j) {
    fluid::GravityBorder2D gravityBorder2D;
    j.at("gX").get_to(gravityBorder2D.gX);
    j.at("gY").get_to(gravityBorder2D.gY);
    return gravityBorder2D; // TODO: same
}

inline fluid::SpeedBorder2D deserializeSpeedBorder2D(const nlohmann::json &j) {
    fluid::SpeedBorder2D speedBorder2D;
    speedBorder2D.wallSpeed2D = deserializeVField2D(j.at("wallSpeed2D"));
    return speedBorder2D; // TODO: same
}

inline fluid::Border2D deserializeBorder2D(const nlohmann::json &j) {
    fluid::Border2D border2D;
    border2D.wall2D = deserializeWallBorder2D(j.at("wall2D"));
    border2D.cavity2D = deserializeCavityBorder2D(j.at("cavity2D"));
    border2D.gravity2D = deserializeGravityBorder2D(j.at("gravity2D"));
    border2D.speed2D = deserializeSpeedBorder2D(j.at("speed2D"));
    return border2D; // TODO: same
}

inline fluid::BasicFluid2D deserializeBasicFluid2D(const nlohmann::json &j) {
    fluid::BasicFluid2D basicFluid2D;
    basicFluid2D.force2D = deserializeVField2D(j.at("force2D"));
    basicFluid2D.speed2D = deserializeVField2D(j.at("speed2D"));
    basicFluid2D.pressure2D = deserializeSField2D(j.at("pressure2D"));
    j.at("viscosity").get_to(basicFluid2D.viscosity);
    j.at("density").get_to(basicFluid2D.density);
    return basicFluid2D; // TODO: same
}

inline fluid::Fluid2D deserializeFluid2D(const nlohmann::json &j) {
    fluid::Fluid2D fluid2D;
    fluid2D.basic2D = deserializeBasicFluid2D(j.at("basic2D"));
    return fluid2D; // TODO: same
}

inline fluid::Model2D deserializeModel2D(const nlohmann::json &j) {
    fluid::Model2D model2D;
    model2D.fluid2D = deserializeFluid2D(j.at("fluid2D"));
    model2D.border2D = deserializeBorder2D(j.at("border2D"));
    return model2D; // TODO: same
}
} // namespace fio
