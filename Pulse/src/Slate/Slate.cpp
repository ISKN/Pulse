/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#include "Slate.h"

#define ENABLE_FILTER

#define FILTER_SIZE 5
#define MAX_DISTANCE_TO_LAST_POINT 0.6 //millimeters

unsigned Slate::_connectIndex = 0;

Slate::Slate()
{
	_lastPoint = ofVec3f(0, 0, 0);
	_pointBackUpForFilter = ofVec3f(0, 0, 0);
	_lastPoints = FixedSizeList<ofVec3f>(FILTER_SIZE);

	_filterValues = FixedSizeList<float>(FILTER_SIZE); //Must have the same length than _lastpoints!
	for (unsigned i = 0; i < FILTER_SIZE; i++)
		_filterValues.add_front(1.0f / (float)FILTER_SIZE);

	_slatePosition = Position::Unknown;

	_pointsBufferQueue.clear();
	_rawPointsBufferQueue.clear();

	//Slate limits (only for right slate which has the x and y inversed
	_xLimits.first = _stickLength / 2.f;
	_xLimits.second = 2.f * _stickLength;
	_yLimits.first = -50.f;
	_yLimits.second = 250.f;
	_zLimits.first = -1.1f * _stickLength;
	_zLimits.second = -0.2f * _stickLength;
}

void Slate::connect()
{
	_isknSlateManager = std::make_unique<ISKN_API::SlateManager>();
	_isknDevice = &_isknSlateManager->getDevice();
	_isknSlateManager->registerListener(this);

	DEBUG_MSG(this->description() << " Connecting slate");
	if (_isknSlateManager->connect())
	{
		DEBUG_MSG(this->description() << " Slate is connected");
	}
	else
	{
		EXCEPTION(this->description() << " Cannot connect slate");
	}
}

void Slate::disconnect()
{
	_isknSlateManager->disconnect();

}

std::deque<ofVec2f> Slate::fetchPoints()
{
	/*if (_slatePosition == Position::Left)
	{
		//Get all points (we only copy inside the mutex to avoid blocking the other thread for too long)
		_mutex.lock();

		std::deque<float> tmp(_heightsBufferQueue.size());
		std::copy(_heightsBufferQueue.begin(), _heightsBufferQueue.end(), tmp.begin());
		_pointsBufferQueue.clear();

		_mutex.unlock();

		//Send points
		for (unsigned i = 0; i < tmp.size(); i++)
		{
			ofNotifyEvent(newHeight, tmp.back());
			tmp.pop_back();
		}
	}
	else
	{*/
		//Get all points (we only copy inside the mutex to avoid blocking the other thread for too long)
		_mutex.lock();

		std::deque<ofVec2f> tmp(_pointsBufferQueue.size());
		std::copy(_pointsBufferQueue.begin(), _pointsBufferQueue.end(), tmp.begin());
		_pointsBufferQueue.clear();

		/*std::deque<ofVec3f> tmpUnfiltered(_rawPointsBufferQueue.size());
		std::copy(_rawPointsBufferQueue.begin(), _rawPointsBufferQueue.end(), tmpUnfiltered.begin());
		_rawPointsBufferQueue.clear();*/

		_mutex.unlock();

		return tmp;

		//Send points
		for (unsigned i = 0; i < tmp.size(); i++)
		{
			ofNotifyEvent(newPoint, tmp.back());
			tmp.pop_back();
		}
		/*for (unsigned i = 0; i < tmpUnfiltered.size(); i++)
		{
			ofNotifyEvent(newPointUnfiltered, tmpUnfiltered.back());
			tmpUnfiltered.pop_back();
		}*/
	//}
}

Slate::Position Slate::getPosition() const
{
	return _slatePosition;
}

void Slate::connectionStatusChanged(bool connected)
{
	try
	{
		if (connected)
		{
			DEBUG_MSG(this->description() << " Subscribing to blocks");

			_isknSlateManager->request(ISKN_API::REQ_DESCRIPTION);
			_isknSlateManager->subscribe(ISKN_API::AUTO_OBJECT_3D);
		}
		else
		{
			DEBUG_MSG(this->description() << " Cannot subscribe: slate is not connected");
		}
	}
	catch (ISKN_API::Error & err)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
		std::string converted_str = converter.to_bytes(err.Message());

		EXCEPTION(converted_str);
	}
}

void Slate::processEvent(ISKN_API::Event & e, unsigned timecode)
{
	switch (e.Type)
	{
		case ISKN_API::EVT_DESCRIPTION :
			DEBUG_MSG(this->description() << " Slate name is " << _isknDevice->getDeviceName());

		case ISKN_API::EVT_OBJECT_3D :
			processPoint(e.Object3D.getPosition(), e.Object3D.getRotation());
			break;

		default :
			//ERROR_MSG(this->description() << " Didn't expect to get event " << e.Type);
			break;
	}

	//Unused variable
	(void)timecode;
}

void Slate::processPoint(ISKN_API::Vector3D const& position, ISKN_API::Vector2D const& rotation)
{
	ofVec3f point = slatePositionToOF(position);

	if (_slatePosition == Position::Left)
	{
		_mutex.lock();
		_heightsBufferQueue.push_front(slateZToHeight(point.z));
		_mutex.unlock();
		return;
	}

	ISKN_API::Vector2D rotation_corrected(rotation);

	rightSlateCorrectCoordinates(point, rotation_corrected);

	/*_mutex.lock();
	_rawPointsBufferQueue.push_front(ofVec3f(point.x, point.y, -point.z) / 10.f);
	_mutex.unlock();*/

	ofVec3f direction = slateRotationToDirection(rotation_corrected);
	//direction *= -1.f; //TODO: delete this
	point = projectPositionToEndOfStick(point, direction);

	_mutex.lock();
	_rawPointsBufferQueue.push_front(ofVec3f(point.x, point.y, -point.z) / 10.f);
	_mutex.unlock();

	point = filterPoint(point);

	if (isDifferentEnoughFromLastPoint(point))
	{
		//DEBUG_MSG(this->description() << " New point: " << point.x << " " << point.y << " " << point.z);

		ofVec2f p = transformPointToWindowCoordinates(point);

		//DEBUG_MSG(this->description() << " After transform: " << p.x << " " << p.y);

		//if (pointIsInsideWindow(p))
		{
			//DEBUG_MSG(this->description() << " Ok to send");
			_lastPoint = point;
			_mutex.lock();
			_pointsBufferQueue.push_front(p);
			_mutex.unlock();
		}		
	}
}

ofVec3f Slate::slatePositionToOF(ISKN_API::Vector3D const& position) const
{
	return ofVec3f(position.X, position.Y, position.Z);
}

float Slate::slateZToHeight(float z) const
{
	z = -z;
	if (z <= 50.f) z = 50.f;
	if (z >= 200.f) z = 200.f;
	const float output = (z - 50.f) * (1.f - 0.f) / (200.f - 50.f) + 0.f; //Scale
	//DEBUG_MSG("Output " << output);
	return output;
}

void Slate::rightSlateCorrectCoordinates(ofVec3f & point, ISKN_API::Vector2D & rotation) const
{
	//DEBUG_MSG("Before correction: " << point.x << " " << point.y << " " << point.z << " " << rotation.X << " " << rotation.Y);
	point.x = 182.f - point.x;
	point.y = 242.f - point.y;
	rotation.Y = rotation.Y >= 0 ? rotation.Y - 180.f : rotation.Y + 180.f;
	//DEBUG_MSG("After correction: " << point.x << " " << point.y << " " << point.z << " " << rotation.X << " " << rotation.Y);
}

ofVec3f Slate::slateRotationToDirection(ISKN_API::Vector2D const& rotation) const
{
	//Compute angles for spherical coordinates
	float theta = rotation.Y >= 0 ? 180 - rotation.Y : -180 - rotation.Y;
	float phi = 180 - rotation.X;

	//Convert to radians
	theta = theta / 180.f * PI;
	phi = phi / 180.f * PI;

	//Return direction
	return ofVec3f(-sin(phi)*cos(theta), sin(phi)*sin(theta), -cos(phi)); //Watch out for x and z axes as they have the opposite sign!
}

ofVec3f Slate::projectPositionToEndOfStick(ofVec3f const& position, ofVec3f const& direction) const
{
	ofVec3f dir(direction);
	dir.normalize();
	return position + dir * _stickLength;
}

float Slate::map(float value, float inMin, float inMax, float outMin, float outMax) const
{
	return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

ofVec3f Slate::filterPoint(ofVec3f const & point)
{
	_pointBackUpForFilter = _lastPoints.back();
	_lastPoints.add_front(point);

	ofVec3f res(0, 0, 0);
	for (unsigned i = 0; i < _filterValues.size(); i++)
	{
		res += _lastPoints[i] * _filterValues[i];
	}

	return res;
}

bool Slate::isDifferentEnoughFromLastPoint(ofVec3f const& point)
{
	if (_lastPoint.distance(point) <= MAX_DISTANCE_TO_LAST_POINT)
	{
		//We won't keep the point so let's remove it from the point history by inserting the backup point at the end.
		_lastPoints.add_back(_pointBackUpForFilter);
		return false;
	}
	//else
		return true;
}

bool Slate::pointIsInsideWindow(ofVec2f const& point)
{
	return point.x >= 0 && point.x < WIDTH 
		&& point.y >= 0 && point.y < HEIGHT;
}

ofVec2f Slate::transformPointToWindowCoordinates(ofVec3f const& point) const
{
	//x is ignored (we never represent the depth)

	//y is turned into the x window coordinate
	const float x = map(point.y, _yLimits.first, _yLimits.second, 0, WIDTH);
	//const float x = map(point.y, 0, 200, 0, WIDTH); //test

	//z is turned into the y window coordinate
	const float y = map(point.z, _zLimits.first, _zLimits.second, 0, HEIGHT);
	//const float y = map(point.z, -200, 0, 0, HEIGHT); //test

	return ofVec2f(x, y);
}

std::string Slate::description() const
{
	switch (_slatePosition)
	{
	case Position::Left: return std::string("SlateLeft ->"); break;
	case Position::Right: return std::string("SlateRight ->"); break;
	case Position::Unknown: return std::string("SlateUnknown ->"); break;
	default: ERROR_MSG("Unknown slate position: " << (int)_slatePosition);
	}

	return std::string("ShouldNotBeHere");
}