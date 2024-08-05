#pragma once

#include "Hazel/Renderer/Buffer.h"

namespace Hazel {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const void* data, unsigned int size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;
		void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		const BufferLayout& GetLayout() const override { return m_Layout; }

	private:
		unsigned int m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const void* data, unsigned int size);
		virtual ~OpenGLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;
		
		unsigned int GetCount() const override { return m_Count; }


	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};

}