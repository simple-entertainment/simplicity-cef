/*
 * Copyright © 2015 Simple Entertainment Limited
 *
 * This file is part of The Simplicity Engine.
 *
 * The Simplicity Engine is free software: you can redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * The Simplicity Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with The Simplicity Engine. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include <string>

#include <cef_browser.h>
#include <cef_command_line.h>
#include <wrapper/cef_helpers.h>

#include "SimpleApp.h"
#include "SimpleHandler.h"

namespace simplicity
{
	namespace simcef
	{
		CefRefPtr<CefBrowserProcessHandler> SimpleApp::GetBrowserProcessHandler()
		{
			return this;
		}

		void SimpleApp::OnContextInitialized()
		{
			CEF_REQUIRE_UI_THREAD();

			CefWindowInfo window_info;

			// SimpleHandler implements browser-level callbacks.
			CefRefPtr<SimpleHandler> handler(new SimpleHandler());

			// Specify CEF browser settings here.
			CefBrowserSettings browser_settings;

			std::string url;

			// Check if a "--url=" value was provided via the command-line. If so, use
			// that instead of the default URL.
			CefRefPtr <CefCommandLine> command_line =
					CefCommandLine::GetGlobalCommandLine();
			url = command_line->GetSwitchValue("url");
			if (url.empty())
				url = "http://www.google.com";
			url = "file:///home/simplegsb/workspaces/simplegsb.github.io/index.html";

			// Create the first browser window.
			CefBrowserHost::CreateBrowser(window_info, handler.get(), url,
										  browser_settings, NULL);
		}
	}
}
