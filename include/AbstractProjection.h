#pragma once

#include <cmath>
#include "cinder/Cinder.h"
#include "cinder/Vector.h"

#include "Transformation.h"
#include "Coordinate.h"
#include "Location.h"

namespace cinder { namespace modestmaps {
    
class AbstractProjection {

public:

	double zoom;
	Transformation transformation;

	AbstractProjection(double _zoom): zoom(_zoom), transformation(Transformation()) { }
	AbstractProjection(double _zoom, Transformation _t): zoom(_zoom), transformation(_t) { }

	virtual ~AbstractProjection() { std::cout << "Abstract Projection destroyed" << std::endl; }
	
	virtual vec2 rawProject(const vec2 &point) = 0;
	virtual vec2 rawUnproject(const vec2 &point) = 0;

	vec2 project(const vec2 &point) {
		return transformation.transform(rawProject(point));
	}

	vec2 unproject(const vec2 &point) {
		return rawUnproject(transformation.untransform(point));
	}

	Coordinate locationCoordinate(const Location &location) {
		vec2 point = project(vec2((M_PI / 180.0) * location.lon, (M_PI / 180.0) * location.lat));
		return Coordinate(point.y, point.x, zoom);
	}

	Location coordinateLocation(const Coordinate &coordinate) {
		// TODO: is this built into Cinder anyplace?
		static const double rad2deg = 180.0/M_PI;
		Coordinate zoomed = coordinate.zoomTo(zoom);
		vec2 point = unproject(vec2(zoomed.column, zoomed.row));
		return Location(rad2deg * point.y, rad2deg * point.x);
	}

};

typedef std::shared_ptr<AbstractProjection> ProjectionRef;
    
} } // namespace