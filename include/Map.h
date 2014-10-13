#pragma once

#include <set>
#include <map>

#include "MapProvider.h"
#include "Location.h"
#include "MapExtent.h"
#include "Coordinate.h"
#include "QueueSorter.h"
#include "TileLoader.h"

#include "cinder/app/AppBasic.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Vector.h"

namespace cinder { namespace modestmaps {
	
// TODO: public getter/setting, and/or Settings object for these values?
    
// limit tiles in memory
// 256 would be 64 MB, you may want to lower this quite a bit for your app
// (we'll always keep as many images as needed to fill the screen though)
#define MAX_IMAGES_TO_KEEP 256

// upping this can help appearances when zooming out, but also loads many more tiles
#define GRID_PADDING 0


class Map {
	
private:

	// how big?
	vec2 size;
		
	// pan and zoom
	Coordinate centerCoordinate;
	
	// angle in radians
	double rotation;
		
	// about the tiles
	MapProviderRef mapProvider;
    
    // loading tiles
    TileLoaderRef tileLoader;

	// loaded tiles
	std::map<Coordinate, gl::TextureRef> images;
	
	// coords waiting to load
	std::vector<Coordinate> queue;
	
	// a list of the most recent MAX_IMAGES_TO_KEEP images we've seen
	std::vector<Coordinate> recentImages;
	
	// keep track of what we can see already:
	std::set<Coordinate> visibleKeys;

	void grabTile(const Coordinate &coord);
	
	void processQueue();

public:	
	
	Map() {}
	
	void setup(MapProviderRef _provider, vec2 size);
    
	void update();
	void draw();
    
	void panBy(const double &x, const double &y);
	void panBy(const vec2 &d);
	void scaleBy(const double &s);
	void scaleBy(const double &s, const double &x, const double &y);
	void scaleBy(const double &s, const vec2 &c);
	void rotateBy(const double &r, const double &x, const double &y);
	void rotateBy(const double &r, const vec2 &c);
	void zoomBy(const double &distance);

	void setZoom(const double &zoom);
	double getZoom() const; // TODO: maybe int getZoomLevel as well?
	Location getCenter() const;
	Coordinate getCenterCoordinate() const;
	
	void setCenter(const Coordinate &center);
	void setCenter(const Location &location);
	void panTo(const Location &location); // same as setCenter	
	void setCenterZoom(const Location &location, const double &zoom);
	
    void setExtent(const MapExtent &extent, bool forceIntZoom = true);
    MapExtent getExtent() const;
	
	MapProviderRef getMapProvider() const {
	    return mapProvider;
	}
	
    void setMapProvider( MapProviderRef _provider);
	
	vec2 coordinatePoint(const Coordinate &coord) const;
	Coordinate pointCoordinate(const vec2 &point) const;

	vec2 locationPoint(const Location &location) const;
	Location pointLocation(const vec2 &point) const;

	void zoomIn();	
	void zoomOut();
		
	void panUp();
	void panDown();
	void panLeft();
	void panRight();	

	void panAndZoomIn(const Location &location);
	
	void setSize(double _width, double _height);
	void setSize(vec2 size);
	vec2 getSize() const;
};

} } // namespace