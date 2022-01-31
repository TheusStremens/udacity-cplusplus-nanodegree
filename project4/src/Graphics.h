#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include "TrafficObject.h"

class Graphics
{
public:
    // constructor / desctructor

    // getters / setters
    inline void setBgFilename(std::string filename) { _bgFilename = filename; }
    inline void setTrafficObjects(std::vector<std::shared_ptr<TrafficObject>> &trafficObjects) { _trafficObjects = trafficObjects; };
    inline void setDownscale(float downscale) { _downscale = downscale; };

    // typical behaviour methods
    void simulate();

private:
    // typical behaviour methods
    void loadBackgroundImg();
    void drawTrafficObjects();

    // member variables
    std::vector<std::shared_ptr<TrafficObject>> _trafficObjects;
    std::string _bgFilename;
    std::string _windowName;
    std::vector<cv::Mat> _images;
    float _downscale{1.0};
};

#endif
