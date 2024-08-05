#pragma once

#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/VertexArray.h"


namespace Hazel {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const override;
		void Unbind() const override;

		IndexBuffer* GetIndexBuffer() const override;

		void AddVertexBuffer(VertexBuffer *vb) override;
		void SetIndexBuffer(IndexBuffer* ib) override;
	private:
		int m_LastIndex = 0;
		unsigned int m_RendererID;
		IndexBuffer* m_IndexBuffer = nullptr;
	};

}