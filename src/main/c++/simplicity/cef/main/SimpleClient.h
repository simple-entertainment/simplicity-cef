/*
 * simple entertainment presents
 *      _                 _ _      _ _
 *     (_)               | (_)    (_) |
 *  ___ _ _ __ ___  _ __ | |_  ___ _| |_ _   _
 * / __| | '_ ` _ \| '_ \| | |/ __| | __| | | |
 * \__ \ | | | | | | |_) | | | (__| | |_| |_| |
 * |___/_|_| |_| |_| .__/|_|_|\___|_|\__|\__, |
 *                 | |                    __/ |
 *                 |_|                   |___/
 *
 * This file is part of simplicity.
 * See the LICENSE file for the full license governing this code.
 */
#ifndef SIMPLECLIENT_H_
#define SIMPLECLIENT_H_

#include <cef_client.h>

#include <simplicity/rendering/Texture.h>

namespace simplicity
{
    namespace simcef
    {
        class SimpleClient : public CefClient, public CefRenderHandler
        {
            public:
				SimpleClient(std::weak_ptr<Texture> texture);

				CefRefPtr<CefRenderHandler> GetRenderHandler() override;

				bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) override;

				void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects,
							 const void* buffer, int width, int height) override;

            private:
                std::weak_ptr<Texture> texture;

                IMPLEMENT_REFCOUNTING(SimpleClient);
        };
    }
}

#endif  /* SIMPLECLIENT_H_ */
