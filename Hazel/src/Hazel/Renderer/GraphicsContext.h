#pragma once

namespace Hazel {

	class GraphicsContext
	{
	public:
		GraphicsContext() { }
		virtual ~GraphicsContext() { }

		virtual void Init() = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual void SwapBuffers() = 0;
	};

}