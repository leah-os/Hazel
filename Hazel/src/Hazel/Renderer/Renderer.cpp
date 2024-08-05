#include "Renderer.h"
#include "RenderCommand.h"

namespace Hazel
{
	void Renderer::BeginScene()
	{
		;
	}

	void Renderer::EndScene()
	{
		;
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& va, const std::shared_ptr<HzModel>& mesh)
	{
		va->Bind();
		RenderCommand::DrawArrays(va, mesh);
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& va)
	{
		HZ_CORE_ASSERT(va->GetIndexBuffer() && "Vertex arrays without index buffer");
		va->Bind();
		RenderCommand::DrawIndexed(va);
	}

}