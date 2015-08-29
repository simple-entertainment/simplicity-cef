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
#include <cef_app.h>

#include "CEFEngine.h"
#include "SimpleClient.h"

using namespace std;

namespace simplicity
{
	namespace simcef
	{
		CEFEngine::CEFEngine(const Resource& htmlPage, Texture& texture) :
				htmlPage(htmlPage),
				texture(texture)
		{
		}

		void CEFEngine::advance()
		{
			CefDoMessageLoopWork();
		}

		void CEFEngine::onPlay()
		{
			CefSettings settings;
			CefString(&settings.browser_subprocess_path).FromASCII("lib/simplicity-cef-subprocess");
			CefString(&settings.locales_dir_path).FromASCII("assets/cef/locales");
			CefString(&settings.resources_dir_path).FromASCII("assets/cef");

			CefInitialize(CefMainArgs(0, nullptr), settings, nullptr, nullptr);

			CefWindowInfo windowInfo;

			// We are supposed to pass a handle to our window here but CEF never actually needs it on Linux.
			// TODO Fix this because it is needed on other platforms.
			windowInfo.SetAsWindowless(0, true);

			CefRefPtr<SimpleClient> client(new SimpleClient(texture));
			CefBrowserHost::CreateBrowserSync(windowInfo, client.get(), htmlPage.getUri().c_str(), CefBrowserSettings(),
											  nullptr);
		}

		void CEFEngine::onStop()
		{
			CefShutdown();
		}
	}
}
