#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

namespace kozmic {
	struct Color {
		float r, g, b, a;
	};

	class RenderContext {
		public:
		virtual ~RenderContext() = default;

		virtual void ClearColor(Color clear_color) = 0;
		virtual const Color* ClearColor() = 0;

		virtual void Clear() = 0;
		virtual void Activate() = 0;
		virtual void SwapBuffers() = 0;
	};
}

#endif //RENDER_CONTEXT_H