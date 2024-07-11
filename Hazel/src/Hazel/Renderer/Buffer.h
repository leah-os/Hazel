#pragma once

namespace Hazel {

	class VertexBuffer {
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData() { ; }

		static VertexBuffer* Create(void* data, unsigned int size);
	};

	class IndexBuffer {
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static IndexBuffer* Create(unsigned int *indices, unsigned int size);
	};

}