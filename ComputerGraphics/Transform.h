#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

using namespace glm;
using namespace std;

class Transform {
	public:
		Transform();
		mat4 GetModelMatrix();
		vec3 GetPosition();
		quat GetRotation();
		vec3 GetScale();

		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void SetScale(float x, float y, float z);

		void Translate(float x, float y, float z, bool world);
		void MoveForward(float delta, bool world);
		void MoveUp(float delta, bool world);
		void MoveRight(float delta, bool world);
		void Rotate(float x, float y, float z, bool world);


		static constexpr vec3 WORLD_FORWARD_VECTOR = vec3(0.0f, 0.0f, 1.0f);
		static constexpr vec3 WORLD_UP_VECTOR = vec3(0.0f, 1.0f, 0.0f);
		static constexpr vec3 WORLD_RIGHT_VECTOR = vec3(1.0f, 0.0f, 0.0f);

	private:
		void UpdateLocalVectors();
		void UpdateModelMatrixPosition();
		void UpdateModelMatrixRotationScale();

		mat4 _modelMatrix;
		
		vec3 _position;
		quat _rotation;
		vec3 _scale;

		vec3 _forward;
		vec3 _up;
		vec3 _right;
};