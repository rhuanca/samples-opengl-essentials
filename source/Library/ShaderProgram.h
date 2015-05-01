#pragma once

#include "Common.h"
#include "Variable.h"

namespace Library
{
	class Model;
	class Mesh;

	typedef std::pair<GLenum, std::wstring> ShaderDefinition;

	class ShaderProgram : public RTTI
	{
		RTTI_DECLARATIONS(ShaderProgram, RTTI)

	public:
		ShaderProgram();
		virtual ~ShaderProgram();
		
		static GLuint CompileShaderFromFile(GLenum shaderType, const std::wstring& filename);

		Variable* operator[](const std::string& variableName);

		GLuint Program() const;	
		const std::vector<Variable*>& Variables() const;
		const std::map<std::string, Variable*>& VariablesByName() const;

		void BuildProgram(const std::vector<ShaderDefinition>& shaderDefinitions);

		virtual void Initialize(GLuint vertexArrayObject);
		virtual void Use() const;
		virtual void CreateVertexBuffer(const Model& model, std::vector<GLuint>& vertexBuffers) const;
		virtual void CreateVertexBuffer(const Mesh& mesh, GLuint& vertexBuffer) const;
		virtual UINT VertexSize() const;

	protected:
		GLuint mProgram;
		std::vector<Variable*> mVariables;
		std::map<std::string, Variable*> mVariablesByName;

	private:
		ShaderProgram(const ShaderProgram& rhs);
		ShaderProgram& operator=(const ShaderProgram& rhs);	
	};

	#define SHADER_VARIABLE_DECLARATION(VariableName)   \
		public:											\
		Variable& VariableName() const;					\
	private:											\
		Variable* m ## VariableName;

	#define SHADER_VARIABLE_DEFINITION(ShaderProgram, VariableName)	\
		Variable& ShaderProgram::VariableName() const				\
		{															\
			return *m ## VariableName;								\
		}

	#define SHADER_VARIABLE_INITIALIZATION(VariableName) m ## VariableName(NULL)

	#define SHADER_VARIABLE_INSTANTIATE(VariableName)															\
		m ## VariableName = new Variable(*this, #VariableName);													\
		mVariables.push_back(m ## VariableName);																\
		mVariablesByName.insert(std::pair<std::string, Variable*>(m ## VariableName->Name(), m ## VariableName));
}
