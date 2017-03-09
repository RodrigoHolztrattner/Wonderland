////////////////////////////////////////////////////////////////////////////////
// Filename: ApplicationMetrics.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Modules\VulkanWrapper\VulkanWrapper.h"
#include "ApplicationInstance.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////
#include <json.hpp>

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

////////////////
// FORWARDING //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: ApplicationMetrics
////////////////////////////////////////////////////////////////////////////////
class ApplicationMetrics
{
public:

	// Our metric data
	struct MetricData
	{
		// The current build number
		uint32_t currentBuildNumber;

		// The last build normalized framerate
		uint32_t lastBuildNormalizedFramerate;

		// The last build normalized frametime
		double lastBuildNormalizedFrametime;

		// The last build normalized framerate
		uint32_t normalizedFramerate;

		// The last build normalized frametime
		double normalizedFrametime;
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	ApplicationMetrics();
	~ApplicationMetrics();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize
	virtual bool Initialize(const char* _metricFile);

	// Release
	virtual void Release();

	// Return the metric data
	MetricData& GetMetricData() { return m_MetricData; }

public:

	// Process a frame data
	void UpdateFrameData(uint32_t _fps, double _ft);

private:

	// Load all metric data
	bool LoadMetricData();

	// Save all metric data
	bool SaveMetricData();

///////////////
// VARIABLES //
private: //////

	// A reference to the metric file name
	const char* m_MetricFile;

	// Our metric data
	MetricData m_MetricData;

	// Our frame info
	std::vector<uint32_t> m_FramerateVector;
	std::vector<double> m_FrametimeVector;
};