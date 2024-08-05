#pragma once

#include <string>
#include <vector>
#include <initializer_list>

#include "Hazel/Core.h"

namespace Hazel {

	enum class ComponentType {
		None = 0, Int, Int2, Int3, Int4, Float, Float1, Float2, Float3, Float4, Mat3, Mat4, Boolean
	};

	static unsigned int ComponentSize(ComponentType type)
	{
		switch (type) {
			case ComponentType::Int:		return 4;
			case ComponentType::Int2:		return 4 * 2;
			case ComponentType::Int3:		return 4 * 3;
			case ComponentType::Int4:		return 4 * 4;
			case ComponentType::Float:		return 4;
			case ComponentType::Float2:		return 4 * 2;
			case ComponentType::Float3:		return 4 * 3;
			case ComponentType::Float4:		return 4 * 4;
			case ComponentType::Mat3:		return 4 * 3 * 3;
			case ComponentType::Mat4:		return 4 * 4 * 4;
			case ComponentType::Boolean:	return 1;
		}
		HZ_CORE_ASSERT(false && "Wrong component type");
		return 0;
	}

	struct Component {
		ComponentType Type;
		std::string Name;
		unsigned int Size;
		unsigned int Offset;
		bool Normalized;

		Component(ComponentType type, std::string name, unsigned int size = 0, unsigned int offset = 0, bool normalized = false)
			: Type(type), Name(name), Size(ComponentSize(type)), Offset(offset), Normalized(normalized) { }

	public:
		unsigned int GetComponentCount() const {
			switch (Type) {
			case ComponentType::Int:			return 1;
				case ComponentType::Int2:		return 2;
				case ComponentType::Int3:		return 3;
				case ComponentType::Int4:		return 4;
				case ComponentType::Float:		return 1;
				case ComponentType::Float2:		return 2;
				case ComponentType::Float3:		return 3;
				case ComponentType::Float4:		return 4;
				case ComponentType::Mat3:		return 3 * 3;
				case ComponentType::Mat4:		return 4 * 4;
				case ComponentType::Boolean:	return 1;
			}
			HZ_CORE_ASSERT(false && "Wrong component type");
			return 0;
		}
	};

	class BufferLayout 
	{
	public:
		BufferLayout() { }
		BufferLayout(const std::initializer_list<Component>& elements)
			: m_Components(elements)
		{
			CalculateOffsetsAndStride();
		}
		inline const std::vector<Component>& GetComponents() const { return m_Components; }
		inline unsigned int GetStride() const { return m_Stride; };
	private:
		void CalculateOffsetsAndStride() {
			int offset = 0;
			for (int i = 0; i < m_Components.size(); i++) {
				m_Components[i].Offset = offset;
				offset += m_Components[i].Size;
			}
			m_Stride = offset;
		}
	private:
		int m_Stride = 0;
		std::vector<Component> m_Components;
	};

	class VertexBuffer {
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout &GetLayout() const = 0;

		static VertexBuffer* Create(const void* data, unsigned int size);
	};

	class IndexBuffer {
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual unsigned int GetCount() const = 0;

		static IndexBuffer* Create(const unsigned int *indices, unsigned int size);
	};

}