#ifndef VROOM_SERIALIZATIONUTILITIES_H
#define VROOM_SERIALIZATIONUTILITIES_H

#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>

#include <Eigen/Dense>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


#include "Types/Sensor/LidarPoint.h"

static class SensorSerializationUtilities
{
	public:
		static std::string SerializeVector3d(Eigen::Vector3d vec)
		{
			std::stringstream stream;
			stream << vec.x() << "," << vec.y() << "," << vec.z();
			return stream.str();
		}

		static Eigen::Vector3d DeserializeVector3d(std::string input)
		{
			Eigen::Vector3d vec;

			size_t commaIndexes[2] = { -1, -1 };
			size_t currentCommaIndex = 0;

			for (size_t i = 0; i < input.size(); i++)
			{
				if (input[i] == ',')
				{
					if (currentCommaIndex >= 2)
					{
						throw std::runtime_error("Attempted to parse " + input + " as Vector3d");
					}
					commaIndexes[currentCommaIndex] = i;
					currentCommaIndex++;
				}
			}
			
			if (currentCommaIndex != 2)
			{
				throw std::runtime_error("Attempted to parse " + input + " as Vector3d");
			}

			vec(0) = stod(input.substr(0, commaIndexes[0]));
			vec(1) = stod(input.substr(commaIndexes[0] + 1, commaIndexes[1]));
			vec(2) = stod(input.substr(commaIndexes[1] + 1, std::string::npos));

			return vec;
		}

		static std::string SerializePointCloud(std::vector<LidarPoint> input)
		{
			std::stringstream stream;

			for (size_t i = 0; i < input.size(); i++)
			{
				stream << input[i].x << "," << input[i].y << "," << input[i].z << "\n";
			}

			return stream.str();
		}

		static std::vector<LidarPoint> DeserializePointCloud(std::string input)
		{
			/*TODO: Implement me*/
			std::vector<LidarPoint> cloud;
			return cloud;
		}

		/*TODO: This function needs to be perf tested and revisited*/
		static std::string SerializeImage(cv::Mat input)
		{
			std::stringstream stream;
			std::vector<uchar> data;
			cv::imencode(".png", input, data);

			for (unsigned int i = 0; i < data.size(); i++)
			{
				stream << data[i] << ",";
			}

			return stream.str();
			
		}

		static cv::Mat DeserializeImage(std::string input, int numRows, int numColumns)
		{
			/*TODO: Impelement me*/
			cv::Mat mat(numRows, numColumns, CV_8UC3, 0);
			return mat;
		}
};

#endif