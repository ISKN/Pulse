/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#ifndef SLATE_H
#define SLATE_H

#include "../general.h"
#include "ISKN_API.h"

class Slate : public ISKN_API::Listener
{
    public :

        Slate();

		void connect();
		void disconnect();

		enum class Position { Unknown, Left, Right };
		Position getPosition() const;

		std::deque<ofVec2f> fetchPoints();

		ofEvent<ofVec2f> newPoint;				//Only for right slate
		ofEvent<ofVec3f> newPointUnfiltered;	//Only for right slate
		ofEvent<float> newHeight;				//Only for left slate


	private :

		//API stuff
		std::unique_ptr<ISKN_API::SlateManager> _isknSlateManager;
		ISKN_API::Device *						_isknDevice;

		static unsigned _connectIndex;

		void processEvent(ISKN_API::Event & e, unsigned timecode);
		void connectionStatusChanged(bool connected);

		//Point processing stuff
        ofVec3f _lastPoint;
		ofVec3f _pointBackUpForFilter;
        FixedSizeList<ofVec3f> _lastPoints;
        FixedSizeList<float> _filterValues;

		void processPoint(ISKN_API::Vector3D const& position, ISKN_API::Vector2D const& rotation);

		ofVec3f slatePositionToOF(ISKN_API::Vector3D const& position) const;
		float slateZToHeight(float z) const;
		void rightSlateCorrectCoordinates(ofVec3f & point, ISKN_API::Vector2D & rotation) const; //Only for right slate
		ofVec3f slateRotationToDirection(ISKN_API::Vector2D const& rotation) const;
		ofVec3f projectPositionToEndOfStick(ofVec3f const& position, ofVec3f const& direction) const;
		float map(float value, float inMin, float inMax, float outMin, float outMax) const;

		ofVec3f filterPoint(ofVec3f const & point);
		bool isDifferentEnoughFromLastPoint(ofVec3f const& point);
		bool pointIsInsideWindow(ofVec2f const& point);
		ofVec2f transformPointToWindowCoordinates(ofVec3f const& point) const;

		std::deque<ofVec2f> _pointsBufferQueue;
		std::deque<ofVec3f> _rawPointsBufferQueue;
		std::deque<float> _heightsBufferQueue;
		std::mutex _mutex;

		//Specific stuff for the setup
		Position _slatePosition; //is it on left, on the right...
		std::string description() const;

		std::pair<float, float> _xLimits, _yLimits, _zLimits;
		const float _stickLength = 200.f; //millimeters

};

#endif // SLATE_H
