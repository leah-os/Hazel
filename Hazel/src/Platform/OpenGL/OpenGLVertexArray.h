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

		Ref<IndexBuffer> GetIndexBuffer() const override;

		void AddVertexBuffer(Ref<VertexBuffer> vb) override;
		void SetIndexBuffer(Ref<IndexBuffer> ib) override;
	private:
		int m_LastIndex = 0;
		unsigned int m_RendererID;
		Ref<IndexBuffer> m_IndexBuffer = nullptr;
	};

}