#pragma once

#include "json.h"
#include "basic.h"
#include "components2d.h"
#include "fluids2d.h"
#include "fluidlib2d.h"

namespace fio {
inline nlohmann::json serializePoint(const fluid::Point &point) {
    return {
            {"value",    point.value},
            {"isInArea", point.isInArea}
    };
}

inline nlohmann::json serializeSField2D(const fluid::SField2D &sField2D) {
    nlohmann::json points;

    const auto sizeX = sField2D.getSizeX();
    const auto sizeY = sField2D.getSizeY();
    for (std::size_t i = 0; i < sizeX; ++i) {
        nlohmann::json row;
        for (std::size_t j = 0; j < sizeY; ++j) {
            row.push_back(sField2D.field(i, j));
        }
        points.push_back(row);
    }
    return {
            {"points", points},
            {"sizeX",  sizeX},
            {"sizeY",  sizeY}
    };
}

inline nlohmann::json serializeVField2D(const fluid::VField2D &vField2D) {
    return {
            {"componentX", serializeSField2D(vField2D.x())},
            {"componentY", serializeSField2D(vField2D.y())}
    };
}

inline nlohmann::json serializeWallBorder2D(const fluid::WallBorder2D &wallBorder2D) {
    return {
            {"wall2D", serializeVField2D(wallBorder2D.wall2D)}
    };
}

inline nlohmann::json serializeCavityBorder2D(const fluid::CavityBorder2D &cavityBorder2D) {
    return {
            {"border2D",   serializeVField2D(cavityBorder2D.border2D)},
            {"pressure2D", serializeSField2D(cavityBorder2D.pressure2D)}
    };
}

inline nlohmann::json serializeGravityBorder2D(const fluid::GravityBorder2D &gravityBorder2D) {
    return {
            {"gX", gravityBorder2D.gX},
            {"gY", gravityBorder2D.gY}
    };
}

inline nlohmann::json serializeSpeedBorder2D(const fluid::SpeedBorder2D &speedBorder2D) {
    return {
            {"wallSpeed2D", serializeVField2D(speedBorder2D.wallSpeed2D)}
    };
}

inline nlohmann::json serializeBorder2D(const fluid::Border2D &border2D) {
    return {
            {"wall2D",    serializeWallBorder2D(border2D.wall2D)},
            {"cavity2D",  serializeCavityBorder2D(border2D.cavity2D)},
            {"gravity2D", serializeGravityBorder2D(border2D.gravity2D)},
            {"speed2D",   serializeSpeedBorder2D(border2D.speed2D)}
    };
}

inline nlohmann::json serializeBasicFluid2D(const fluid::BasicFluid2D &basicFluid2D) {
    return {
            {"force2D",    serializeVField2D(basicFluid2D.force2D)},
            {"speed2D",    serializeVField2D(basicFluid2D.speed2D)},
            {"pressure2D", serializeSField2D(basicFluid2D.pressure2D)},
            {"viscosity",  basicFluid2D.viscosity},
            {"density",    basicFluid2D.density}
    };
}

inline nlohmann::json serializeFluid2D(const fluid::Fluid2D &fluid2D) {
    return {
            {"basic2D", serializeBasicFluid2D(fluid2D.basic2D)}
    };
}

inline nlohmann::json serializeModel2D(const fluid::Model2D &model2D) {
    return {
            {"fluid2D",  serializeFluid2D(model2D.fluid2D)},
            {"border2D", serializeBorder2D(model2D.border2D)}
    };
}
} // namespace fio
