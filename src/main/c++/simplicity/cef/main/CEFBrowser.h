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
#ifndef CEFBROWSER_H_
#define CEFBROWSER_H_

#include <cef_app.h>

#include <simplicity/entity/Component.h>
#include <simplicity/messaging/Message.h>
#include <simplicity/rendering/Texture.h>
#include <simplicity/resources/Resource.h>

namespace simplicity
{
	namespace simcef
	{
		/**
		 * <p>
		 * An engine that renders HTML to a texture using the Chromium Embedded Framework.
		 * </p>
		 */
		class CEFBrowser : public Component
		{
			public:
				CEFBrowser(const Resource& htmlPage, std::weak_ptr<Texture> texture);

				void executeJavaScript(const std::string& code);

				void load();

				bool onKeyboardButton(const Message& message);

				bool onMouseButton(const Message& message);

				bool onMouseMove(const Message& message);

				void unload();

			private:
				CefRefPtr<CefBrowser> browser;

				const Resource& initialPage;

				std::weak_ptr<Texture> texture;
		};
	}
}

#endif /* CEFBROWSER_H_ */
