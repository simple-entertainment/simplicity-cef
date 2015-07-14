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

using namespace std;

namespace simplicity
{
    namespace simcef
    {
		SimpleClient::SimpleClient(weak_ptr<Texture> texture) :
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

			if (!texture.expired())
			{
				shared_ptr<Texture> sharedTexture = texture.lock();
				rect.height = sharedTexture->getHeight();
				rect.width = sharedTexture->getWidth();
			}

			return true;
		}

		void SimpleClient::OnPaint(CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType type,
								   const CefRenderHandler::RectList& dirtyRects, const void* buffer, int width,
								   int height)
		{
			if (!texture.expired())
			{
				texture.lock()->setRawData(reinterpret_cast<const char*>(buffer));
			}
		}
	}
}
