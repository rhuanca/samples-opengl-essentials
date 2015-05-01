#pragma once

#include "Common.h"

namespace Library
{
	class MatrixHelper
	{
	public:
		static void GetForward(glm::mat4& matrix, glm::vec3& vector);
		static void GetUp(glm::mat4& matrix, glm::vec3& vector);
		static void GetRight(glm::mat4& matrix, glm::vec3& vector);
		static void GetTranslation(glm::mat4& matrix, glm::vec3& vector);

		static void SetForward(glm::mat4& matrix, glm::vec3& forward);
		static void SetUp(glm::mat4& matrix, glm::vec3& up);
		static void SetRight(glm::mat4& matrix, glm::vec3& right);
		static void SetTranslation(glm::mat4& matrix, glm::vec3& translation);

	private:
		MatrixHelper();
		MatrixHelper(const MatrixHelper& rhs);
		MatrixHelper& operator=(const MatrixHelper& rhs);
	};
}