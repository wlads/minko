/*
Copyright (c) 2014 Aerys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "minko/Common.hpp"
#include "minko/Signal.hpp"
#include "minko/log/Logger.hpp"

#include "VRImpl.hpp"

extern "C"
{
    struct ovrHmdDesc_;
    typedef const ovrHmdDesc_* ovrHmd;
}

namespace minko
{
    namespace oculus
    {
        class NativeOculus : public VRImpl
        {
        private:
            static ovrHmd                                       _hmd;
            std::shared_ptr<scene::Node>                        _ppScene;
            std::shared_ptr<component::Renderer>                _ppRenderer;
            uint                                                _renderTargetWidth;
            uint                                                _renderTargetHeight;
            std::shared_ptr<render::Texture>                    _renderTarget;
            std::array<std::pair<math::vec2, math::vec2>, 2>    _uvScaleOffset;
            Signal<std::shared_ptr<component::SceneManager>, uint, std::shared_ptr<render::AbstractTexture>>::Slot      _renderEndSlot;
            float                                               _zNear;
            float                                               _zFar;

            std::shared_ptr<component::Renderer>                _leftRenderer;
            std::shared_ptr<component::Renderer>                _rightRenderer;
            math::ivec4                                         _leftRendererViewport;
            math::ivec4                                         _rightRendererViewport;

            void
            initializePostProcessingRenderer(std::shared_ptr<component::SceneManager> sceneManager);

            void
            renderEndHandler(
                std::shared_ptr<component::SceneManager> sceneManager,
                uint frameId,
                std::shared_ptr<render::AbstractTexture> renderTarget
            );

        public:
            typedef std::shared_ptr<NativeOculus> Ptr;

            void
            initialize(std::shared_ptr<component::SceneManager> sceneManager);

            void
            initializeVRDevice(std::shared_ptr<component::Renderer> leftRenderer, std::shared_ptr<component::Renderer> rightRenderer, void* window = nullptr);

            void
            targetAdded();

            void
            targetRemoved();

            std::array<std::shared_ptr<geometry::Geometry>, 2>
            createDistortionGeometry(std::shared_ptr<render::AbstractContext> context);

            void
            updateCameraOrientation(std::shared_ptr<scene::Node> target, std::shared_ptr<scene::Node> leftCamera, std::shared_ptr<scene::Node> rightCamera);

            void
            updateViewport(int viewportWidth, int viewportHeight);

            float
            getLeftEyeFov();

            float
            getRightEyeFov();

            inline
            float
            zNear()
            {
                return _zNear;
            }

            inline
            float
            zFar()
            {
                return _zFar;
            }

            static
            bool
            detected();

            inline static
            Ptr
            create(int viewportWidth, int viewportHeight, float zNear, float zFar)
            {
                LOG_INFO("Create a NativeOculus instance.");

                auto ptr = std::shared_ptr<NativeOculus>(new NativeOculus(viewportWidth, viewportHeight, zNear, zFar));

                return ptr;
            }

        private:
            NativeOculus(int viewportWidth, int viewportHeight, float zNear, float zFar);
        };
    }
}
