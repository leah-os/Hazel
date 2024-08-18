#pragma once

#include "Hazel/Core/Input.h"

namespace Hazel {

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) const override;
		virtual bool IsMouseButtonPressedImpl(int button) const override;
		virtual float GetMouseXImpl() const override;
		virtual float GetMouseYImpl() const override;
		virtual void GetMousePosImpl(float* xpos, float* pos) const override;
		virtual int GetWidthImpl() const override;
		virtual int GetHeightImpl() const override;
	};

}