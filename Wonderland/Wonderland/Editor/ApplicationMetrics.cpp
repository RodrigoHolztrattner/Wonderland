////////////////////////////////////////////////////////////////////////////////
// Filename: FluxApplication.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ApplicationMetrics.h"

ApplicationMetrics::ApplicationMetrics()
{
	// Set the initial data
	m_MetricData.currentBuildNumber = -1;
	m_MetricData.lastBuildNormalizedFramerate = 0;
	m_MetricData.lastBuildNormalizedFrametime = 0;
	m_MetricData.normalizedFramerate = 0;
	m_MetricData.normalizedFrametime = 0;
}

ApplicationMetrics::~ApplicationMetrics()
{
}

bool ApplicationMetrics::Initialize(const char* _metricFile)
{
	// Set the metric file name
	m_MetricFile = _metricFile;

	// Load the metric data
	if (!LoadMetricData())
	{
		return false;
	}

	// Increment the current build number
	m_MetricData.currentBuildNumber++;

	return true;
}

void ApplicationMetrics::Release()
{
	// Swap the framerate and frametime
	m_MetricData.lastBuildNormalizedFramerate = m_MetricData.normalizedFramerate;
	m_MetricData.lastBuildNormalizedFrametime = m_MetricData.normalizedFrametime;

	// Save the metric data
	SaveMetricData();
}

void ApplicationMetrics::UpdateFrameData(uint32_t _fps, double _ft)
{
	// Insert the data
	m_FramerateVector.insert(m_FramerateVector.begin(), _fps);
	m_FrametimeVector.insert(m_FrametimeVector.begin(), _ft);

	// No more then 10 elements
	if (m_FrametimeVector.size() > 10)
	{
		m_FramerateVector.erase(m_FramerateVector.begin() + 10);
		m_FrametimeVector.erase(m_FrametimeVector.begin() + 10);
	}

	// Calc the data
	uint32_t fpsSum = 0;
	for (auto value : m_FramerateVector)
	{
		fpsSum += value;
	}
	double ftSum = 0;
	for (auto value : m_FrametimeVector)
	{
		ftSum += value;
	}

	// Set the data
	m_MetricData.normalizedFramerate = fpsSum / m_FramerateVector.size();
	m_MetricData.normalizedFrametime = ftSum / m_FrametimeVector.size();
}

bool ApplicationMetrics::LoadMetricData()
{
	// Open the file
	std::ifstream file(m_MetricFile);

	// Check if the file exist
	if (!file.is_open())
	{
		// The file doesnt exist, create a new one
		if (!SaveMetricData())
		{
			return false;
		}

		// Try again
		file = std::ifstream(m_MetricFile);
		if (!file.is_open())
		{
			return false;
		}
	}

	// Create an empty structure (null)
	nlohmann::json j;

	// Create the structure
	file >> j;

	// Get the json data
	m_MetricData.currentBuildNumber = j["currentBuildNumber"].get<uint32_t>();
	m_MetricData.lastBuildNormalizedFramerate = j["lastBuildNormalizedFramerate"].get<uint32_t>();
	m_MetricData.lastBuildNormalizedFrametime = j["lastBuildNormalizedFrametime"].get<double>();
	m_MetricData.normalizedFramerate = j["normalizedFramerate"].get<uint32_t>();
	m_MetricData.normalizedFrametime = j["normalizedFrametime"].get<double>();

	// Close the file
	file.close();

	return true;
}

bool ApplicationMetrics::SaveMetricData()
{
	// Create the file
	std::ofstream ifs(m_MetricFile);

	// create an empty structure (null)
	nlohmann::json j;

	// Set the json data
	j["currentBuildNumber"] = m_MetricData.currentBuildNumber;
	j["lastBuildNormalizedFramerate"] = m_MetricData.lastBuildNormalizedFramerate;
	j["lastBuildNormalizedFrametime"] = m_MetricData.lastBuildNormalizedFrametime;
	j["normalizedFramerate"] = m_MetricData.normalizedFramerate;
	j["normalizedFrametime"] = m_MetricData.normalizedFrametime;

	// Save the data
	ifs << j;

	// Close the file
	ifs.close();

	return true;
}