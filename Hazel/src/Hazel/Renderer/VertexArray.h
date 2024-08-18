#pragma once

#include "Buffer.h"

namespace Hazel {

	class VertexArray
	{
	public:
		virtual ~VertexArray() { }

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual Ref<IndexBuffer> GetIndexBuffer() const = 0;

		virtual void AddVertexBuffer(Ref<VertexBuffer> vb) = 0;
		virtual void SetIndexBuffer(Ref<IndexBuffer> ib) = 0;

		static VertexArray* Create();
	};

}