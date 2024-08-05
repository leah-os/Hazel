#include "OpenGLVertexArray.h"

#include <glad/gl.h>

namespace Hazel {

	static GLenum ComponentTypeToOpenGLType(ComponentType type);

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(VertexBuffer *vb)
	{
		glBindVertexArray(m_RendererID);

		HZ_CORE_ASSERT(vb->GetLayout().GetComponents().size() && "Vertex buffer has no layout");

		vb->Bind();
		const std::vector<Component> components = vb->GetLayout().GetComponents();

		for (int index = 0; index < components.size(); index++, m_LastIndex++)
		{
			const Component comp = components[index];
			glEnableVertexAttribArray(m_LastIndex);
			glVertexAttribPointer(m_LastIndex,
				comp.GetComponentCount(),
				ComponentTypeToOpenGLType(comp.Type),
				comp.Normalized,
				vb->GetLayout().GetStride(), (const void*)comp.Offset
			);
		}

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::SetIndexBuffer(IndexBuffer* ib)
	{
		glBindVertexArray(m_RendererID);
		ib->Bind();
		glBindVertexArray(0);
		m_IndexBuffer = ib;
	}

	IndexBuffer* OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}

	static GLenum ComponentTypeToOpenGLType(ComponentType type) {
		switch (type) {
			case ComponentType::Int:		return GL_INT;
			case ComponentType::Int2:		return GL_INT;
			case ComponentType::Int3:		return GL_INT;
			case ComponentType::Int4:		return GL_INT;
			case ComponentType::Float:		return GL_FLOAT;
			case ComponentType::Float2:		return GL_FLOAT;
			case ComponentType::Float3:		return GL_FLOAT;
			case ComponentType::Float4:		return GL_FLOAT;
			case ComponentType::Mat3:		return GL_FLOAT;
			case ComponentType::Mat4:		return GL_FLOAT;
			case ComponentType::Boolean:	return GL_BOOL;
		}
		HZ_CORE_ASSERT(false && "Wrong component type");
		return 0;
	}

}