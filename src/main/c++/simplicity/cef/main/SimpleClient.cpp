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
#include "SimpleClient.h"

namespace simplicity
{
    namespace simcef
    {
		SimpleClient::SimpleClient(Texture& texture) :
				texture(texture)
		{
		}

        CefRefPtr<CefRenderHandler> SimpleClient::GetRenderHandler()
        {
            return this;
        }

		bool SimpleClient::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
		{
			rect.x = 0;
			rect.y = 0;

			rect.height = texture.getHeight();
			rect.width = texture.getWidth();

			return true;
		}

		void SimpleClient::OnPaint(CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType type,
								   const CefRenderHandler::RectList& dirtyRects, const void* buffer, int width,
								   int height)
		{
			texture.setRawData(reinterpret_cast<const char*>(buffer));
		}
	}
}
