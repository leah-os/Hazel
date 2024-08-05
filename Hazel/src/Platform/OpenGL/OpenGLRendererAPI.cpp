#include "OpenGLRendererAPI.h"

#include <glad/gl.h>

namespace Hazel
{
	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& va)
	{
		glDrawElements(GL_TRIANGLES, va->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	
	void OpenGLRendererAPI::DrawArrays(const std::shared_ptr<VertexArray>& va, const std::shared_ptr<HzModel>& mesh)
	{
		glDrawArrays(GL_TRIANGLES, 0, mesh->GetVertexCount());
	}

}