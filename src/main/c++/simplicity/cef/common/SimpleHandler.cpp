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
#include <sstream>

#include "include/base/cef_bind.h"
#include "include/cef_app.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"

#include "SimpleHandler.h"

namespace simplicity
{
    namespace simcef
    {
        SimpleHandler* g_instance = NULL;

        SimpleHandler::SimpleHandler()
                : is_closing_(false)
        {
          DCHECK(!g_instance);
          g_instance = this;
        }

        SimpleHandler::~SimpleHandler()
        {
          g_instance = NULL;
        }

// static
        SimpleHandler* SimpleHandler::GetInstance()
        {
          return g_instance;
        }

        void SimpleHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
        {
          CEF_REQUIRE_UI_THREAD();

          // Add to the list of existing browsers.
          browser_list_.push_back(browser);
        }

        bool SimpleHandler::DoClose(CefRefPtr<CefBrowser> browser)
        {
          CEF_REQUIRE_UI_THREAD();

          // Closing the main window requires special handling. See the DoClose()
          // documentation in the CEF header for a detailed destription of this
          // process.
          if (browser_list_.size() == 1)
          {
            // Set a flag to indicate that the window close should be allowed.
            is_closing_ = true;
          }

          // Allow the close. For windowed browsers this will result in the OS close
          // event being sent.
          return false;
        }

        void SimpleHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
        {
          CEF_REQUIRE_UI_THREAD();

          // Remove from the list of existing browsers.
          BrowserList::iterator bit = browser_list_.begin();
          for (; bit != browser_list_.end(); ++bit)
          {
            if ((*bit)->IsSame(browser))
            {
              browser_list_.erase(bit);
              break;
            }
          }

          if (browser_list_.empty())
          {
            // All browser windows have closed. Quit the application message loop.
            CefQuitMessageLoop();
          }
        }

        void SimpleHandler::OnLoadError(CefRefPtr<CefBrowser> browser,
                                        CefRefPtr<CefFrame> frame,
                                        ErrorCode errorCode,
                                        const CefString& errorText,
                                        const CefString& failedUrl)
        {
          CEF_REQUIRE_UI_THREAD();

          // Don't display an error for downloaded files.
          if (errorCode == ERR_ABORTED)
            return;

          // Display a load error message.
          std::stringstream ss;
          ss << "<html><body bgcolor=\"white\">"
                  "<h2>Failed to load URL " << std::string(failedUrl) <<
          " with error " << std::string(errorText) << " (" << errorCode <<
          ").</h2></body></html>";
          frame->LoadString(ss.str(), failedUrl);
        }

        void SimpleHandler::CloseAllBrowsers(bool force_close)
        {
          if (!CefCurrentlyOn(TID_UI))
          {
            // Execute on the UI thread.
            CefPostTask(TID_UI,
                        base::Bind(&SimpleHandler::CloseAllBrowsers, this, force_close));
            return;
          }

          if (browser_list_.empty())
            return;

          BrowserList::const_iterator it = browser_list_.begin();
          for (; it != browser_list_.end(); ++it)
            (*it)->GetHost()->CloseBrowser(force_close);
        }

		void SimpleHandler::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
		{
		}
    }
}
