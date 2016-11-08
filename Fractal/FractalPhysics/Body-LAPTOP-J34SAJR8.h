#pragma once
#include <FractalMath\Math.h>
#include "Component.h"
namespace fractal {
	using namespace fmath;
	enum BodyType
	{
		StaticBody,
		DynamicBody,
		KinematicBody
	};

	class Body : public Component
	{
	public:
		Body();
		~Body();

	private:
		float _mass;
		Point3 _CenterOfMass;
		Vector3 _Vector;

	};

	struct DefaultBody {
		DefaultBody()
		{
				// Set all initial positions/velocties to zero
				axis.load();
				angle = float(0.0);
				position.load();
				linearVelocity.load();
				angularVelocity.load();

				gravityScale = float(1.0);

				// Common default values
				bodyType = StaticBody;
				layers = 0x000000001;
				userData = NULL;
				allowSleep = true;
				awake = true;
				active = true;
				lockAxisX = false;
				lockAxisY = false;
				lockAxisZ = false;

				linearDamping = float(0.0);
				angularDamping = float(0.1);
			}

			Point3 axis;			// Initial world transformation.
			float angle;				// Initial world transformation. Radians.
			Vector3 position;		// Initial world transformation.
			Vector3 linearVelocity;	// Initial linear velocity in world space.
			Vector3 angularVelocity;	// Initial angular velocity in world space.
			float gravityScale;		// Convenient scale values for gravity x, y and z directions.
			float layers;				// Bitmask of collision layers. Bodies matching at least one layer can collide.
			void* userData;			// Use to store application specific data.

			float linearDamping;
			float angularDamping;

			// Static, dynamic or kinematic. Dynamic bodies with zero mass are defaulted
			// to a mass of 1. Static bodies never move or integrate, and are very CPU
			// efficient. Static bodies have infinite mass. Kinematic bodies have
			// infinite mass, but *do* integrate and move around. Kinematic bodies do not
			// resolve any collisions.
			BodyType bodyType;

			bool allowSleep;	// Sleeping lets a body assume a non-moving state. Greatly reduces CPU usage.
			bool awake;			// Initial sleep state. True means awake.
			bool active;		// A body can start out inactive and just sits in memory.
			bool lockAxisX;		// Locked rotation on the x axis.
			bool lockAxisY;		// Locked rotation on the y axis.
			bool lockAxisZ;		// Locked rotation on the z axis.
		};
	};

