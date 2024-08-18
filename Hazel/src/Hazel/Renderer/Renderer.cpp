#include "Renderer.h"
#include "RenderCommand.h"

namespace Hazel
{
	void Renderer::BeginScene(PerspectiveCamera &camera)
	{
		//m_ProjectionMatrix = camera.GetProjectionMatrix();
		//m_ViewMatrix = camera.GetViewMatrix();
		RenderCommand::Clear();
	}

	void Renderer::EndScene()
	{
		;
	}

	void Renderer::Clear()
	{
		RenderCommand::Clear();
	}

	void Renderer::Submit(const Ref<VertexArray>& va)
	{
		HZ_CORE_ASSERT(va->GetIndexBuffer() && "Vertex arrays without index buffer");
		va->Bind();
		RenderCommand::DrawIndexed(va);
	}

}