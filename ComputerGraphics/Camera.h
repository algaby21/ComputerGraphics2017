#pragma once

#include <glm/glm.hpp>
#include "Transform.h"

using namespace glm;
using namespace std;

class Camera {
	public:
		Camera();
		mat4 GetViewProjection();
		mat4 GetViewMatrix();
		mat4 GetProjectionMatrix();
		vec3 GetPosition();

		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);

		void MoveForward(float delta, bool world = false);
		void MoveUp(float delta, bool world = false);
		void MoveRight(float delta, bool world = false);

		// Rota la c�mara al rededor del eje y
		void Yaw(float degrees);
		// Rota la c�mara en el eje z
		void Roll(float degrees);
		// Rota la c�mara en el eje x
		void Pitch(float degrees);
		void Rotate(float x, float y, float z, bool world = false);

		// Qu� tan cerca y qu� tan lejos va a ver en el plano de corte,
		// el �ngulo de apertura de la c�mara y el aspect ratio
		void SetPerspective(float nearPlane, float farPlane, float fieldOfView, float aspectRatio);
		// Tama�o hacia arriba y hacia abajo de la c�mara y el aspect ratio
		void SetOrthographic(float size, float aspectRatio);

	private:
		Transform _transform;
		
		mat4 _viewMatrix;
		mat4 _projectionMatrix;

};