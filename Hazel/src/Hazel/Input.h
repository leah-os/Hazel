#pragma once

#include "Hazel/KeyCodes.h"
#include "Hazel/MouseCodes.h"

namespace Hazel
{
	class Input
	{
	public:
		Input() { s_Instance = this; }
		~Input() { ; }

		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		inline static void GetMousePos(float *xpos, float *ypos) { return s_Instance->GetMousePosImpl(xpos, ypos); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) const = 0;
		virtual bool IsMouseButtonPressedImpl(int button) const = 0;
		virtual float GetMouseXImpl() const = 0;
		virtual float GetMouseYImpl() const = 0;
		virtual void GetMousePosImpl(float* xpos, float *pos) const = 0;
	private:
		static Input* s_Instance;
	};
}