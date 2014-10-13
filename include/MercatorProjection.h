#pragma once

#include "AbstractProjection.h"
#include "Transformation.h"

namespace cinder { namespace modestmaps {
	
class MercatorProjection : public AbstractProjection {

private:
    
	MercatorProjection(double _zoom=0): AbstractProjection(_zoom, Transformation()) { }
	MercatorProjection(double _zoom, Transformation t): AbstractProjection(_zoom,t) { }    
    
public:
	
    static ProjectionRef create(double zoom = 0)
    {
        return ProjectionRef( new MercatorProjection( zoom ) );
    }

    static ProjectionRef create(double zoom, Transformation t)
    {
        return ProjectionRef( new MercatorProjection( zoom, t ) );
    }
    
    static ProjectionRef createWebMercator()
    {
        Transformation t = Transformation::deriveTransformation( -M_PI,  M_PI, 0, 0, 
                                                                  M_PI,  M_PI, 1, 0, 
                                                                 -M_PI, -M_PI, 0, 1 );
        return ProjectionRef( new MercatorProjection( 0, t) );
    }
    	
	vec2 rawProject(const vec2 &point) {
		return vec2(point.x, log(tan(0.25 * M_PI + 0.5 * point.y)));
	}
	
	vec2 rawUnproject(const vec2 &point) {
		//BL return vec2(point.x, 2.0 * atan(pow(M_E, point.y)) - 0.5 * M_PI);
		return vec2(point.x, 2.0 * atan(pow(2.71828, point.y)) - 0.5 * M_PI);
	}
	
};

} } // namespace